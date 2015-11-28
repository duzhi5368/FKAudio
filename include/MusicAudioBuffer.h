//-------------------------------------------------------------------
// 
//
// Comment: 重点处理流体音频数据
//-------------------------------------------------------------------

#pragma once


#include "Unorderly.h"
#include "IAudioBuffer.h"

namespace Ogre
{
	namespace FKAudio
	{
		class MusicAudioBuffer : public IAudioBuffer
		{
		/*public:
			MusicAudioBuffer(const SP_AUDIODATA& AudioData);
			virtual ~MusicAudioBuffer();

			virtual void Play(bool loop = false);
			virtual void Stop();
			virtual void Reset();
			virtual bool IsSound() const;
		protected:
			virtual void ResetBuffer() = 0;
			virtual void Play(bool loop) = 0;
			virtual void DoStop() = 0;

			// 每秒读取的次数
			static uint32_t	PreSecond;*/
		};
	}
}