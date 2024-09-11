/******************************************************************************/
/*!
\file		AudioEngine.h
\author 	Valerie Koh
\par    	email: v.koh\@digipen.edu
\date   	September 11, 2024
\brief

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 *
 /******************************************************************************/

#ifndef _AUDIO_ENGINE_H_
#define _AUDIO_ENGINE_H_

#include <BorealisPCH.hpp>
#include <FMOD/fmod.hpp>
#include <string>
#include <map>
#include <vector>
#include <math.h>
#include <iostream>

namespace Borealis
{
    struct Vector3
    {
        float x;
        float y;
        float z;
    };

    struct Implementation {
        Implementation();
        ~Implementation();

        void Update();

        FMOD::System* mpSystem;

        int mnNextChannelId;

        typedef std::map<std::string, FMOD::Sound*> SoundMap;
        typedef std::map<int, FMOD::Channel*> ChannelMap;

        SoundMap mSounds;
        ChannelMap mChannels;
    };

    class AudioEngine {
    public:
        static void Init();
        static void Update();
        static void Shutdown();
        static int ErrorCheck(FMOD_RESULT result);

        void LoadAudio(const std::string& strAudioName, bool b3d = true, bool bLooping = false, bool bStream = false);
        void UnLoadAudio(const std::string& strAudioName);
        void Set3dListenerAndOrientation(const Vector3& vPos = Vector3{ 0, 0, 0 }, float fVolumedB = 0.0f);
        int PlayAudio(const std::string& strAudioName, const Vector3& vPos = Vector3{ 0, 0, 0 }, float fVolumedB = 0.0f);
        void StopChannel(int nChannelId);
        void StopAllChannels();
        void SetChannel3dPosition(int nChannelId, const Vector3& vPosition);
        void SetChannelVolume(int nChannelId, float fVolumedB);
        bool IsPlaying(int nChannelId) const;
        float dbToVolume(float db);
        float VolumeTodb(float volume);
        FMOD_VECTOR VectorToFmod(const Vector3& vPosition);
    };
} // End of namespace Borealis
#endif
