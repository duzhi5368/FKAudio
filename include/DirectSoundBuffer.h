//-------------------------------------------------------------------
// 
//
// Comment: 重点处理非流体音频数据
//-------------------------------------------------------------------

#pragma once


#include "Unorderly.h"
#include "IAudioBuffer.h"

namespace Ogre
{
	namespace FKAudio
	{
		class DirectSoundBuffer : public MusicAudioBuffer
		{
		public:
			DirectSoundBuffer(const SP_AUDIOBUFFERS& pSourceData, uint32 uBufferSeconds, float fVolume);
			~DirectSoundBuffer();

			// 状态获取函数：是否在播放
			bool IsPlaying() const;
			// 状态获取函数：获取声音位置
			Vector3f GetPlayerPos() const;
			// 状态获取函数：获取声音速度
			Vector3f GetVelocity() const;
			// 状态获取函数：获取声音方向
			Vector3f GetDirection() const;

			// 属性设置函数：设置音量( 0.0f - 1.0f )
			void SetVolume(float fVolume);
			// 属性设置函数：设置播放位置
			void SetPlayerPos(const Vector3f& Pos);
			// 属性设置函数：设置声音速度
			void SetVelocity(const Vector3f& Pos);
			// 属性设置函数：设置声音方向
			void SetDirection(const Vector3f& Pos);
			// 播放控制函数：播放本音频缓冲区内信息
			void Play(bool bLoop = false);
			// 播放控制函数：复位本音频缓冲区内信息
			void Reset();
			// 播放控制函数：停止播放本音频缓冲区内信息
			void Stop();
		private:
			
		};
	}
}
