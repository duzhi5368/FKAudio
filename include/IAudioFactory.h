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
		class IAudioFactory
		{
		public:
			IAudioFactory();
			virtual ~IAudioFactory();

			// 获取音频工厂名称
			virtual const std::wstring & GetName() const = 0;
			// 获取本工厂所捆绑的引擎实例
			virtual IAudioEngine& GetAudioEngineInstance() = 0;
			// 新建一份声音缓冲区
			virtual SP_AUDIOBUFFERS MakeSoundBuffer(const SP_AUDIODATA& pSourceData, uint32 uSourceNum = 1) = 0;
			// 新建一份音乐缓冲区
			virtual SP_AUDIOBUFFERS MakeMusicBuffer(const SP_AUDIODATA& pSourceData, uint32 uBufferSeconds = 2) = 0;
		};
	}
}