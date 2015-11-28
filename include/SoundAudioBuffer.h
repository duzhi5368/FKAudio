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
		class SoundAudioBuffer : public IAudioBuffer
		{
		public:
			SoundAudioBuffer(const SP_AUDIODATA& AudioData);
			virtual ~SoundAudioBuffer();
			// 复位缓冲区以及其中数据
			virtual void Reset();
			// 判断是否是声音类型
			virtual bool IsSound() const;
		protected:
			// 仅仅复位缓冲区自身,没写在IAudioBuffer是为了隐藏本接口
			virtual void ResetBuffer() = 0;
		};
	}
}