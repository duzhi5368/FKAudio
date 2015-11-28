//-------------------------------------------------------------------
// 
//
//
//-------------------------------------------------------------------

#include "stdafx.h"
#include "../include/SoundAudioBuffer.h"

namespace Ogre
{
	namespace FKAudio
	{
		//-------------------------------------------------------------------
		SoundAudioBuffer::SoundAudioBuffer(const SP_AUDIODATA& AudioData)
			: IAudioBuffer(AudioData)
		{
		
		}
		//-------------------------------------------------------------------
		SoundAudioBuffer::~SoundAudioBuffer()
		{
		
		}
		//-------------------------------------------------------------------
		bool SoundAudioBuffer::IsSound() const
		{
			return true;
		}
		//-------------------------------------------------------------------
		void SoundAudioBuffer::Reset()
		{
			// 首先复位缓冲区中数据对象，再自身复位
			this->Stop();
			m_AudioData->Reset();
			this->ResetBuffer();
		}
		//-------------------------------------------------------------------
	}
}