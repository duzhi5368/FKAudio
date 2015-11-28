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
		class NullAudioData : public IAudioData
		{
		protected:
			eAudioDataFormat		m_nDataFormat;
			uint32					m_nFrequency;
			const char*				m_szFilename;	
		public:
			NullAudioData();
			NullAudioData(const char* szFilename);
			virtual ~NullAudioData();

			eAudioDataFormat		GetFormat() const;
			uint32					GetFrequency() const;
			const char*				GetFilename() const;

			uint32	GetSize();
			uint32	Read(void* pAudioData, uint32 uSize);
			void	Reset();
		};
	}
}