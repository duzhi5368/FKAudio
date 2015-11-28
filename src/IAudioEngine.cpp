//-------------------------------------------------------------------
// 
//
//
//-------------------------------------------------------------------

#include "stdafx.h"
#include "../include/IAudioEngine.h"
#include <boost/bind.hpp>

namespace Ogre
{
	namespace FKAudio
	{
		//-------------------------------------------------------------------
		IAudioEngine::IAudioEngine()
			: m_fSoundVolume(1)
			, m_fMusicVolume(1)
		{
		
		}
		//-------------------------------------------------------------------
		IAudioEngine::~IAudioEngine()
		{
		
		}
		//-------------------------------------------------------------------
		// 获取音频引擎中的音频缓冲区的个数
		size_t IAudioEngine::GetBuffersNum() const
		{
			return m_AudioBuffers.size();
		}
		//-------------------------------------------------------------------
		// 获取指定编号的音频缓冲区
		SP_AUDIOBUFFERS IAudioEngine::GetBuffer(size_t uId) 
		{
			AUDIO_BUFFERS_MAP_ITE ite(m_AudioBuffers.find(uId));
			if (ite != m_AudioBuffers.end())
			{
				return ite->second;
			}
			return SP_AUDIOBUFFERS();
		}
		//-------------------------------------------------------------------
		// 获取音乐音量大小
		float IAudioEngine::GetMusicVolume() const
		{
			return m_fMusicVolume;
		}
		//-------------------------------------------------------------------
		// 获取声音音量大小
		float IAudioEngine::GetSoundVolume() const
		{
			return m_fSoundVolume;
		}
		//-------------------------------------------------------------------
		// 在音频引擎中增加管理一个音频缓冲区
		void IAudioEngine::AddBuffer(size_t uId, const SP_AUDIOBUFFERS& pBuffer)
		{
			m_AudioBuffers.insert(std::make_pair(uId, pBuffer));
		}
		//-------------------------------------------------------------------
		// 播放指定编号的音频缓冲区
		void IAudioEngine::Play(size_t uId, bool bLoop)
		{
			this->GetBuffer(uId)->Play(bLoop);
		}
		//-------------------------------------------------------------------
		// 停止指定编号的音频播放
		void IAudioEngine::Stop(size_t uId)
		{
			this->GetBuffer(uId)->Stop();
		}
		//-------------------------------------------------------------------
		// 播放缓冲区map表中的所有音频
		void IAudioEngine::PlayAll(bool bLoop)
		{
			std::for_each(m_AudioBuffers.begin(), m_AudioBuffers.end(),
				boost::bind(&IAudioBuffer::Play, boost::bind(select2nd<AUDIO_BUFFERS_MAP::value_type>(), _1), bLoop));
		}
		//-------------------------------------------------------------------
		// 停止缓冲区map表中的所有音频播放
		void IAudioEngine::StopAll()
		{
			std::for_each(m_AudioBuffers.begin(), m_AudioBuffers.end(), 
				boost::bind(&IAudioBuffer::Stop, boost::bind(select2nd<AUDIO_BUFFERS_MAP::value_type>(), _1)));
		}
		//-------------------------------------------------------------------
		// 设置音乐音量大小
		void IAudioEngine::SetMusicVolume(float fVol)
		{
			FK_ASSERT((fVol >= 0.0f) && (fVol <= 1.0f));
			m_fMusicVolume = fVol;

			for (AUDIO_BUFFERS_MAP_ITE ite = m_AudioBuffers.begin(); ite != m_AudioBuffers.end(); ++ite )
			{
				if (!(ite->second->IsSound()))
				{
					ite->second->SetVolume(fVol);
				}
			}			
		}
		//-------------------------------------------------------------------
		// 设置声音音量大小
		void IAudioEngine::SetSoundVolume(float fVol)
		{
			FK_ASSERT((fVol >= 0.0f) && (fVol <= 1.0f));
			m_fSoundVolume = fVol;

			for (AUDIO_BUFFERS_MAP_ITE ite = m_AudioBuffers.begin(); ite != m_AudioBuffers.end(); ++ite )
			{
				if (ite->second->IsSound())
				{
					ite->second->SetVolume(fVol);
				}
			}
		}
		//-------------------------------------------------------------------
	}
}