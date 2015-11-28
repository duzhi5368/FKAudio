//-------------------------------------------------------------------
// 
//
//
//-------------------------------------------------------------------

#pragma once


#include "Unorderly.h"
#include <map>
#include "Vector3.h"
#include "../include/IAudioBuffer.h"

namespace Ogre
{
	namespace FKAudio
	{
		class IAudioEngine
		{
			typedef std::map<size_t, SP_AUDIOBUFFERS>		AUDIO_BUFFERS_MAP;
			typedef AUDIO_BUFFERS_MAP::iterator			AUDIO_BUFFERS_MAP_ITE;
		protected:
			AUDIO_BUFFERS_MAP	m_AudioBuffers;			// 保存的音频缓冲区表
			float				m_fSoundVolume;			// 声音音量大小
			float				m_fMusicVolume;			// 音乐音量大小
		public:
			IAudioEngine();
			virtual ~IAudioEngine();

			// 获取音频引擎名称
			virtual const std::wstring& GetName() const = 0;
			// 获取音频引擎中的音频缓冲区的个数
			virtual size_t GetBuffersNum() const;
			// 获取指定编号的音频缓冲区
			virtual SP_AUDIOBUFFERS GetBuffer(size_t uId);
			// 获取音乐音量大小
			virtual float GetMusicVolume() const;
			// 获取声音音量大小
			virtual float GetSoundVolume() const;
			// 获取3D接收者位置
			virtual Vector3f GetListenerPos() const = 0;
			// 获取3D接收者速度
			virtual Vector3f GetListenerVel() const = 0;
			// 获取3D接收者方向
			virtual void GetListenerOri(Vector3f& Face, Vector3f& Up) const = 0;

			// 在音频引擎中增加管理一个音频缓冲区
			virtual void AddBuffer(size_t uId, const SP_AUDIOBUFFERS& pBuffer);
			// 播放指定编号的音频缓冲区
			virtual void Play(size_t uId, bool bLoop = false);
			// 停止指定编号的音频播放
			virtual void Stop(size_t uId);
			// 播放缓冲区map表中的所有音频
			virtual void PlayAll(bool bLoop = false);
			// 停止缓冲区map表中的所有音频播放
			virtual void StopAll();
			// 设置音乐音量大小，0.0f-1.0f之间
			virtual void SetMusicVolume(float fVol);
			// 设置声音音量大小，0.0f-1.0f之间
			virtual void SetSoundVolume(float fVol);
			// 设置3D接收者位置
			virtual void SetListenerPos(const Vector3f& Pos) = 0;
			// 设置3D接收者速度
			virtual void SetListenerVel(const Vector3f& Vel) = 0;
			// 设置3D接收者方向
			virtual void SetListenerOri(const Vector3f& Face, const Vector3f& Up) = 0;
		};
	}
}