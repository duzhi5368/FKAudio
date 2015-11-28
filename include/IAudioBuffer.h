//-------------------------------------------------------------------
// 
//
//
//-------------------------------------------------------------------

#pragma once


#include "Unorderly.h"
#include "IAudioData.h"
#include "Vector3.h"
#include  <algorithm>

namespace Ogre
{
	namespace FKAudio
	{
		class IAudioBuffer
		{
		public:
			IAudioBuffer( const SP_AUDIODATA& AudioData ) 
				: m_AudioData(AudioData)
				, m_nFrequency(AudioData->GetFrequency())
				, m_nDataFormat(AudioData->GetFormat()) 
			{};
			  virtual ~IAudioBuffer(){};

		public:
			// 播放控制函数：播放本音频缓冲区内信息
			virtual void Play(bool bLoop = false) = 0;
			// 播放控制函数：复位本音频缓冲区内信息
			virtual void Reset() = 0;
			// 播放控制函数：停止播放本音频缓冲区内信息
			virtual void Stop() = 0;

			// 状态获取函数：是否在播放
			virtual bool IsPlaying() const = 0;
			// 状态获取函数：是否是声音文件
			virtual bool IsSound() const = 0;
			// 状态获取函数：获取声音位置
			virtual Vector3f GetPlayerPos() const = 0;
			// 状态获取函数：获取声音速度
			virtual Vector3f GetVelocity() const = 0;
			// 状态获取函数：获取声音方向
			virtual Vector3f GetDirection() const = 0;

			// 属性设置函数：设置音量(0.0f - 1.0f)
			virtual void SetVolume(float fVolume) = 0;
			// 属性设置函数：设置播放位置
			virtual void SetPlayerPos(const Vector3f& Pos) = 0;
			// 属性设置函数：设置声音速度
			virtual void SetVelocity(const Vector3f& Pos) = 0;
			// 属性设置函数：设置声音方向
			virtual void SetDirection(const Vector3f& Pos) = 0;
		protected:
			SP_AUDIODATA			m_AudioData;	// 音频数据文件指针
			eAudioDataFormat		m_nDataFormat;	// 音频数据文件类型	
			uint32					m_nFrequency;	// 音频数据频率
		};
		// 音效数据缓冲区的智能指针
		typedef boost::shared_ptr<IAudioBuffer> SP_AUDIOBUFFERS;
	}
}


