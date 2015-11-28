//-------------------------------------------------------------------
// 
//
// Comment:	Ogg是一个音频流文件，它由最小的包packet进行传输，之后自动
//			焊接组装为一个个Ogg页，在第一个Ogg页中保存了其流序列信息。
//			一个Vorbis核心解码器支持分解为多个局部解码器，允许同时解码。
//-------------------------------------------------------------------

#pragma once


#include "Unorderly.h"
#include "IAudioData.h"
#include "../external/include/vorbis/codec.h"
#include <iostream>

namespace Ogre
{
	namespace FKAudio
	{
		class OggAudioData : public IAudioData
		{
		public:
			explicit OggAudioData(const SP_ISTREAM& file);
			~OggAudioData();

			// 获取Ogg文件大小
			uint32	GetSize();
			// 读取Ogg流文件
			uint32	Read(void* pAudioData, uint32 uSize);
			// 复位Ogg流文件
			void	Reset();
		private:
			// 初始化Vorbis
			void Init();
			// 释放Vorbis
			void Destory();
		private:
			SP_ISTREAM				m_pOggFile;		// Ogg文件流指针
			std::istream::off_type	m_cDataOffset;	// 数据偏移字节量

			ogg_sync_state   m_oy;	// Ogg音效流同步机状态		
			ogg_stream_state m_os;	// Ogg音效流焊接机状态		
			ogg_page         m_og;	// Ogg页单元				
			ogg_packet       m_op;	// Ogg包单元				

			vorbis_info      m_vi;	// vorbis的配置信息结构		
			vorbis_comment   m_vc;	// vorbis用户注释信息结构	
			vorbis_dsp_state m_vd;	// 中央解码器工作状态		
			vorbis_block     m_vb;	// 局部解码器工作空间		
		};
	}
}