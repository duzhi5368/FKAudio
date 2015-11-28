//-------------------------------------------------------------------
// 
//
//
//-------------------------------------------------------------------

#include "stdafx.h"
#include "../include/NullAudioData.h"

namespace Ogre
{
	namespace FKAudio
	{
		//-------------------------------------------------------------------
		NullAudioData::NullAudioData()
			: m_szFilename(NULL)
			, m_nDataFormat(EADF_Unknown)
			, m_nFrequency(0)
		{		
		}
		//-------------------------------------------------------------------
		NullAudioData::NullAudioData(const char* szFilename)
			: m_szFilename(szFilename)
			, m_nDataFormat(EADF_Unknown)
			, m_nFrequency(0)
		{	

		}
		//-------------------------------------------------------------------
		NullAudioData::~NullAudioData()
		{
			
		}
		//-------------------------------------------------------------------
		uint32 NullAudioData::GetSize()
		{
			return 0;
		}
		//-------------------------------------------------------------------
		uint32 NullAudioData::Read(void* pAudioData, uint32 uSize)
		{
			return 0;
		}
		//-------------------------------------------------------------------
		void NullAudioData::Reset()
		{
		
		}
		//-------------------------------------------------------------------
		const char* NullAudioData::GetFilename() const
		{
			return this->m_szFilename;
		}
		//-------------------------------------------------------------------
	}
}