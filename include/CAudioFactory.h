//-------------------------------------------------------------------
// 
//
//
//-------------------------------------------------------------------

#pragma once


#include "Unorderly.h"
#include "IAudioFactory.h"

namespace Ogre
{
	namespace FKAudio
	{
		template < typename AudioEngineType, typename SoundBufferType, typename MusicBufferType>
		class CAudioFactory : public IAudioFactory
		{
		private:
			const std::wstring m_strName;
		public:
			CAudioFactory(const std::wstring& strName) : m_strName(strName)
			{
			
			}
			//-------------------------------------------------------------------
			~CAudioFactory()
			{
			
			}
			//-------------------------------------------------------------------
			// 获取音频工厂名称
			const std::wstring GetName() const
			{
				return m_strName;
			}
			//-------------------------------------------------------------------
			// 获取该工厂的引擎实例
			IAudioEngine& GetAudioEngineInstance()
			{
				static AudioEngineType EngineInstance;
				return EngineInstance;
			}
			//-------------------------------------------------------------------
			// 新建一份声音缓冲区
			SP_AUDIOBUFFERS MakeSoundBuffer(const SP_AUDIODATA& pSourceData, uint32 uSourceNum)
			{
				return SP_AUDIOBUFFERS(new SoundBufferType(pSourceData, uSourceNum, this->GetAudioEngineInstance().GetSoundVolume()));
			}
			//-------------------------------------------------------------------
			// 新建一份音乐缓冲区
			SP_AUDIOBUFFERS MakeMusicBuffer(const SP_AUDIODATA& pSourceData, uint32 uBufferSeconds)
			{
				return SP_AUDIOBUFFERS(new MusicBufferType(pSourceData, uBufferSeconds, this->GetAudioEngineInstance().GetSoundVolume()));
			}
			//-------------------------------------------------------------------
		};
	}
}
	