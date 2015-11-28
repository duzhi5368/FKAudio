//-------------------------------------------------------------------
// 
//
// 
//-------------------------------------------------------------------

#pragma once

#include "Unorderly.h"
#include "IAudioData.h"


namespace Ogre
{
	namespace FKAudio
	{	
		// Wave数据单元结构
		class WaveAudioData : public IAudioData
		{
		public:
			explicit WaveAudioData(const SP_ISTREAM& file);
			~WaveAudioData();

			// 获取当前文件大小
			uint32		GetSize();
			// 读取指定音频文件
			uint32		Read(void* pAudioData, uint32 uSize);
			// 复位音频数据
			void		Reset();
		private:
			// 读取WAVE文件头
			void		LoadFileHdr();
		private:
			SP_ISTREAM				m_pWavFile;		// WAVE文件指针
			std::istream::off_type	m_cDataOffset;	// 数据偏移字节量
			uint32					m_uSize;		// WAVE文件大小
		};
	}
}