//-------------------------------------------------------------------
// 
//
//
//-------------------------------------------------------------------

#include "stdafx.h"
#include "../include/OggAudioData.h"
#include <vector>

#ifdef _DEBUG
#pragma comment(lib, "../external/bin/ogg_static_d.lib")
#pragma comment(lib, "../external/bin/vorbis_static_d.lib")
#else
#pragma comment(lib, "../external/bin/ogg_static.lib")
#pragma comment(lib, "../external/bin/vorbis_static.lib")
#endif

namespace Ogre
{
	namespace FKAudio
	{
		//-------------------------------------------------------------------
		// 构造
		OggAudioData::OggAudioData(const SP_ISTREAM& file)
			: m_pOggFile(file)
		{
			Init();
		}
		//-------------------------------------------------------------------
		// 初始化Vorbis
		void OggAudioData::Init()
		{
			// 初始化同步ogg流
			ogg_sync_init(&m_oy);

			// 为Ogg分配缓冲区
			char* buffer(ogg_sync_buffer(&m_oy, OGG_BUFFUR));
			m_pOggFile->read(buffer, OGG_BUFFUR);
			int bytes(static_cast<int>(m_pOggFile->gcount()));
			ogg_sync_wrote(&m_oy, bytes);

			// 获取第一个Ogg信息页,确认是不是Vorbis数据
			FK_ASSERT(1 == ogg_sync_pageout(&m_oy, &m_og));

			// 持续接收顺序编号的Ogg流包，并且解码排序，使其成为一个序列化的流
			ogg_stream_init(&m_os, ogg_page_serialno(&m_og));

			vorbis_info_init(&m_vi);
			vorbis_comment_init(&m_vc);
			// 确认版本号是否正确
			FK_ASSERT(ogg_stream_pagein(&m_os, &m_og) >= 0);

			// 确认是正确的Vorbis
			FK_ASSERT(1 == ogg_stream_packetout(&m_os ,&m_op));

			// 确认是Vorbis头
			FK_ASSERT(vorbis_synthesis_headerin(&m_vi, &m_vc, &m_op) >= 0);

			// 获取类型和频率
			m_nDataFormat = (1 == m_vi.channels) ? EADF_Mono_16 : EADF_Stereo_16;
			m_nFrequency = m_vi.rate;

			int i(0);
			while (i < 2)
			{
				while (i < 2)
				{
					int nResult(ogg_sync_pageout(&m_oy, &m_og));

					// 无数据则返回，等待获得更多的Ogg数据包以组成完整的页
					if (0 == nResult)
					{
						break;
					}

					// 可能会丢包或序列不正确，我们先获取其序号等整个页传完再处理
					if (1 == nResult)
					{
						// 这里在装页时可能会有一些错误，但我们暂时不理睬
						ogg_stream_pagein(&m_os, &m_og);
						// 继续页输出
						while (i < 2)
						{
							nResult = ogg_stream_packetout(&m_os,&m_op);
							if (0 == nResult)
							{
								break;
							}
							vorbis_synthesis_headerin(&m_vi, &m_vc, &m_op);
							++ i;
						}
					}
				}

				// 这里我们额外又添加了一次“可能是空”的接收信息，不过即使是空信息也没有任何坏处，反而更加安全，可以防止丢包
				buffer = ogg_sync_buffer(&m_oy, OGG_BUFFUR);
				m_pOggFile->read(buffer, OGG_BUFFUR);
				bytes = static_cast<int>(m_pOggFile->gcount());
				ogg_sync_wrote(&m_oy, bytes);
			}

			// 好了，三个头全部接收完毕，初始化Vorbis开始解码
			// 因为多个解码块可以同时工作。我们在这里也可以初始化多个局部解码器
			vorbis_synthesis_init(&m_vd, &m_vi);	// 初始化核心解码器
			vorbis_block_init(&m_vd, &m_vb);		// 为局部解码器初始化空间

			m_cDataOffset = m_pOggFile->tellg();

			this->Reset();	
		}
		//-------------------------------------------------------------------
		// 析构函数
		OggAudioData::~OggAudioData()
		{
			Destory();
		}
		//-------------------------------------------------------------------
		// 释放Vorbis
		void OggAudioData::Destory()
		{
			ogg_stream_clear(&m_os);
			vorbis_block_clear(&m_vb);
			vorbis_dsp_clear(&m_vd);
			vorbis_comment_clear(&m_vc);
			// 最后才可以清空vorbis配置结构
			vorbis_info_clear(&m_vi); 
			// 释放Ogg同步机
			ogg_sync_clear(&m_oy);
		}
		//-------------------------------------------------------------------
		// 获取Ogg文件大小
		uint32 OggAudioData::GetSize()
		{	
			// 流式结构，所以返回0
			return 0;	
		}
		//-------------------------------------------------------------------
		// 读取Ogg流文件
		uint32 OggAudioData::Read(void* pAudioData, uint32 uSize)
		{
			FK_ASSERT(NULL != pAudioData);

			// 分配一个指定大小的对流空间
			std::vector<ogg_int16_t> vecConvBuffer( uSize / sizeof(ogg_int16_t));
			// 初始化剩余波段总数
			int nLeftChannelNums(static_cast<int>(vecConvBuffer.size() / m_vi.channels));
			// 初始化当前进度记录数
			uint32 uCurSize(0);			

			while (nLeftChannelNums > 0)
			{
				while (nLeftChannelNums > 0)
				{
					int nResult(ogg_sync_pageout(&m_oy , &m_og));

					// 无法获取Ogg页，需要更多数据包
					if (0 == nResult)
					{
						break;
					}

					if (nResult > 0)
					{
						// 此处不要对返回值做处理，即使有些错误也没有关系，等包全部达到后再组页也是可以的。
						ogg_stream_pagein(&m_os, &m_og); 

						while (nLeftChannelNums > 0)
						{
							nResult = ogg_stream_packetout(&m_os, &m_op);

							// 数据不足，所以组页失败，需要循环等包
							if (0 == nResult)
							{
								break;
							}

							if (nResult > 0)
							{
								// 获得了一个完整的页，开始解码
								if (0 == vorbis_synthesis(&m_vb, &m_op))
								{
									vorbis_synthesis_blockin(&m_vd, &m_vb);
								}

								// ppPcm是一个多波段的浮点向量。例如在立体声中，pcm[0]是左声道，pcm[1]是右声道。
								// 我们需要将ppPcm这个[-1, 1]的浮点型转换成PCM格式再写出。
								// nChannelNum是Pcm每个波段的大小。
								float** ppPcm;
								int nChannelNums;
								while ((nLeftChannelNums > 0) && ((nChannelNums = vorbis_synthesis_pcmout(&m_vd, &ppPcm)) > 0))
								{
									// 获得当前剩余未处理完的波段个数
									int nReadyChannelNums = FKMin(nChannelNums, nLeftChannelNums);
									nLeftChannelNums -= nReadyChannelNums;

									// 将浮点类型转换为16位有符号整形
									for (int i = 0; i < m_vi.channels; ++ i)
									{
										ogg_int16_t* ptr(&vecConvBuffer[i]);
										float const * mono(ppPcm[i]);

										for (int j = 0; j < nReadyChannelNums; ++ j)
										{
											*ptr = FKClamp< ogg_int16_t >(static_cast<ogg_int16_t>(mono[j] * 32767.0f), -32768, 32767);
											ptr += m_vi.channels;
										}
									}

									// 将已经处理完的波段交由Vorbis解码处理
									vorbis_synthesis_read(&m_vd, nReadyChannelNums);

									// 当前已经解码的数据空间大小
									uint32 const uReadyBufZize = nReadyChannelNums * m_vi.channels;
									// 把解码后的数据放入缓冲区
									std::copy(vecConvBuffer.begin(), vecConvBuffer.begin() + uReadyBufZize,
										static_cast<ogg_int16_t*>(pAudioData) + uCurSize);

									// 更改当前位置记录点
									uCurSize += uReadyBufZize;
								}
							}
						}
					}
				}

				if (nLeftChannelNums > 0)
				{
					char* buffer(ogg_sync_buffer(&m_oy, OGG_BUFFUR));
					m_pOggFile->read(buffer, OGG_BUFFUR);
					int bytes(static_cast<int>(m_pOggFile->gcount()));

					if (m_pOggFile->fail())
					{
						m_pOggFile->clear();
						nLeftChannelNums = 0;
					}

					ogg_sync_wrote(&m_oy, bytes);
				}
			}

			return uCurSize * sizeof(ogg_int16_t);
		}
		//-------------------------------------------------------------------
		// 复位Ogg文件
		void OggAudioData::Reset()
		{
			FK_ASSERT(NULL != m_pOggFile);

			m_pOggFile->clear();
			m_pOggFile->seekg(m_cDataOffset);
		}
		//-------------------------------------------------------------------
	}
}