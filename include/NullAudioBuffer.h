//-------------------------------------------------------------------
// 
//
//
//-------------------------------------------------------------------

#pragma once


#include "Unorderly.h"
#include "IAudioBuffer.h"

namespace Ogre
{
	namespace FKAudio
	{
		class NullAudioBuffer : public IAudioBuffer
		{
		public:
			virtual ~NullAudioBuffer();
		public:
			// 播放控制函数：播放本音频缓冲区内信息
			virtual void Play(bool bLoop = false);
			// 播放控制函数：复位本音频缓冲区信息
			virtual void Reset();
			// 播放控制函数：停止播放本音频缓冲区内信息
			virtual void Stop();

			// 状态获取函数：是否在播放
			virtual bool IsPlaying() const;
			// 状态获取函数：是否是声音文件
			virtual bool IsSound() const;
			// 状态获取函数：获取声音位置
			virtual Vector3f GetPlayerPos() const;
			// 状态获取函数：获取声音速度
			virtual Vector3f GetVelocity() const = 0;
			// 状态获取函数：获取声音方向
			virtual Vector3f GetDirection() const = 0;

			// 属性设置函数：设置音量
			virtual void SetVolume(float fVolume);
			// 属性设置函数：设置播放位置
			virtual void SetPlayerPos(const Vector3f& Pos);
			// 属性设置函数：设置声音速度
			virtual void SetVelocity(const Vector3f& Pos);
			// 属性设置函数：设置声音方向
			virtual void SetDirection(const Vector3f& Pos);
		};
	}
}