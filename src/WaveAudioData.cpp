//-------------------------------------------------------------------
// 
//
//
//-------------------------------------------------------------------

#include "stdafx.h"
#include "../include/WaveAudioData.h"

namespace Ogre
{
	namespace FKAudio
	{
		//-------------------------------------------------------------------
		// WavChunk标志格式
		enum eWaveFileStyle
		{
			EWFS_RIFF = MakeFourCC<'R', 'I', 'F', 'F'>::value,	
			EWFS_WAVE = MakeFourCC<'W', 'A', 'V', 'E'>::value,
			EWFS_FMT  = MakeFourCC<'f', 'm', 't', ' '>::value,
			EWFS_DATA = MakeFourCC<'d', 'a', 't', 'a'>::value,
		};

		// 开启单字节对齐
		#pragma pack(push, 1)
		// Chunk中所有块通用的头信息
		struct WAVEChunkHdr
		{
			eWaveFileStyle		uId;			// 块中的头类型标志 
			uint32				uSize;			// 本块的大小
		};

		// WaveChunk的内容结构
		struct WAVEFileHdr
		{
			eWaveFileStyle		uId;			// 块中的头类型标志 
			uint32				uSize;			// 本块的大小
			eWaveFileStyle		eType;			// Tape字段
		};

		// FormatChunk的主要内容结构
		struct WaveFmt
		{
			unsigned short		formatTag;		// 编码方式
			unsigned short		channels;		// 单/双 声道的判定数
			uint32				samplesPerSec;	// 采样频率
			uint32				avgBytesPerSec;	// 音频数据传输速率
			unsigned short		blockAlign;		// 每个采样的对齐数
		};

		// FormatChunk的16字节大小版本的内容结构
		struct PCMWaveFmt
		{
			WaveFmt				wf;
			unsigned short		bitsPerSample;	// 每个采样需要的Bit数
		};

		// FormatChunk的18字节大小版本的内容结构
		struct WaveFmtEx
		{
			WaveFmt				wf;	
			unsigned short		bitsPerSample;	// 每个采样需要的Bit数
			unsigned short		extraSize;		// 格外补充的俩字节
		};
		// 关闭单字节对齐
		#pragma pack(pop)
		//-------------------------------------------------------------------
		// 构造函数
		WaveAudioData::WaveAudioData(const SP_ISTREAM& file)
			: m_pWavFile(file)
			, m_cDataOffset(0)
			, m_uSize(0)
		{
			this->LoadFileHdr();
			this->Reset();
		}
		//-------------------------------------------------------------------
		// 析构函数
		WaveAudioData::~WaveAudioData()
		{
			m_pWavFile->clear();
		}
		//-------------------------------------------------------------------
		// 获取当前文件大小
		uint32 WaveAudioData::GetSize()
		{
			return m_uSize;
		}
		//-------------------------------------------------------------------
		// 读取指定音频文件
		uint32 WaveAudioData::Read(void* pAudioData, uint32 uSize)
		{
			FK_ASSERT(NULL != pAudioData);
			m_pWavFile->read(static_cast<char*>(pAudioData), static_cast<std::streamsize>(uSize));
			return m_pWavFile->gcount();
		}
		//-------------------------------------------------------------------
		// 复位音频数据
		void WaveAudioData::Reset()
		{
			m_pWavFile->clear();
			m_pWavFile->seekg(m_cDataOffset);	
		}
		//-------------------------------------------------------------------
		// 读取WAVE文件头
		void WaveAudioData::LoadFileHdr()
		{
			m_pWavFile->seekg(0);

			WAVEFileHdr tagFileHdr;
			m_pWavFile->read(reinterpret_cast<char*>(&tagFileHdr), sizeof(tagFileHdr));

			// 检查是否是一个有效的 Wave 文件
			FK_ASSERT(EWFS_RIFF == tagFileHdr.uId); 
			FK_ASSERT(EWFS_WAVE == tagFileHdr.eType);

			PCMWaveFmt tagPcmWaveFmt;
			WAVEChunkHdr tagChunkHdr;

			for ( ; ; )
			{
				// 读取Chunk头,若失败则跳出
				m_pWavFile->read(reinterpret_cast<char*>(&tagChunkHdr), sizeof(tagChunkHdr));
				if (m_pWavFile->fail())
				{
					m_pWavFile->clear();
					break;
				}

				// 循环读取WAVE的每个Chunk块
				switch(tagChunkHdr.uId)
				{
				case EWFS_FMT:
					// 读取Wave的完整格式信息
					m_pWavFile->read(reinterpret_cast<char*>(&tagPcmWaveFmt), sizeof(tagPcmWaveFmt));
					FK_ASSERT(0x0001 == tagPcmWaveFmt.wf.formatTag);
					m_pWavFile->seekg(tagChunkHdr.uSize - sizeof(tagPcmWaveFmt), std::ios_base::cur);
					m_nFrequency = tagPcmWaveFmt.wf.samplesPerSec;
					if (1 == tagPcmWaveFmt.wf.channels)	
					{
						if (8 == tagPcmWaveFmt.bitsPerSample)
						{
							m_nDataFormat = EADF_Mono_8;
						}
						else
						{
							m_nDataFormat = EADF_Mono_16;
						}
					}
					else
					{
						if (8 == tagPcmWaveFmt.bitsPerSample)
						{
							m_nDataFormat = EADF_Stereo_8;
						}
						else
						{
							m_nDataFormat = EADF_Stereo_16;
						}
					}
					break;
				case EWFS_DATA:
					m_cDataOffset = m_pWavFile->tellg();
					m_uSize = tagChunkHdr.uSize;
					m_pWavFile->seekg(tagChunkHdr.uSize, std::ios_base::cur);
					break;
				default:
					m_pWavFile->seekg(tagChunkHdr.uSize, std::ios_base::cur);
					break;					
				}
			}
			m_pWavFile->seekg(tagChunkHdr.uSize, std::ios_base::cur);
		}
		//-------------------------------------------------------------------
	}
}