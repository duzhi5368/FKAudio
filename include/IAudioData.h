//-------------------------------------------------------------------
// 
//
//
//-------------------------------------------------------------------

#pragma once


#include "Unorderly.h"

namespace Ogre
{
	namespace FKAudio
	{
		// 枚举pcm音频数据存放格式
		enum eAudioDataFormat
		{
			EADF_Mono_8 = 0x84,		// 8位采样率  单声道
			EADF_Mono_16,			// 16位采样率 单声道
			EADF_Stereo_8,			// 8位采样率  立体声	
			EADF_Stereo_16,			// 16位采样率 立体声
			EADF_Unknown			// 未知类型
		};

		// 音频数据类接口
		class IAudioData
		{
		protected:
			eAudioDataFormat		m_nDataFormat;	// 音频文件数据格式
			uint32					m_nFrequency;	// 音频频率
			const char*				m_szFilename;	// 音频文件名称
		public:
			IAudioData()
				: m_szFilename(NULL)
				, m_nDataFormat(EADF_Unknown)
				, m_nFrequency(0)
			{}
			IAudioData(const char* szFilename)
				: m_szFilename(szFilename)
				, m_nDataFormat(EADF_Unknown)
				, m_nFrequency(0)
			{}
			virtual ~IAudioData(){}

			// 获取当前文件格式
			eAudioDataFormat		GetFormat() const	{return this->m_nDataFormat;}
			// 获取当前文件频率
			uint32					GetFrequency() const{return this->m_nFrequency;}
			// 获取当前文件名称
			const char*				GetFilename() const {return this->m_szFilename;}

			// 获取当前文件大小
			virtual uint32		GetSize() const = 0;
			// 读取指定音频文件
			virtual uint32		Read(void* pAudioData, uint32 uSize) = 0;
			// 重置整个音频数据
			virtual void		Reset() = 0;
		};

		// 音效数据单元的智能指针
		typedef boost::shared_ptr<IAudioData> SP_AUDIODATA;
	}
}
