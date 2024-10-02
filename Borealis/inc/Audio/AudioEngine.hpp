/******************************************************************************/
/*!
\file		AudioEngine.hpp
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

    //struct Implementation {
    //    Implementation();
    //    ~Implementation();

    //    void Update();

    //    FMOD::System* mpSystem;

    //    int mnNextChannelId;

    //    typedef std::map<std::string, FMOD::Sound*> SoundMap;
    //    typedef std::map<int, FMOD::Channel*> ChannelMap;

    //    SoundMap mSounds;
    //    ChannelMap mChannels;
    //};

    class AudioEngine {
    public:
        static void Init();
        static void Update();
        static void Shutdown();

        static void LoadAudio(const std::string& strAudioName, bool b3d = true, bool bLooping = false, bool bStream = false);
        static void UnLoadAudio(const std::string& strAudioName);
        static void Set3DListenerAndOrientation(const Vector3& vPos = Vector3{ 0, 0, 0 }, float fVolumedB = 0.0f);
        static int PlayAudio(const std::string& strSoundName, const Vector3& vPosition = Vector3{ 0, 0, 0 }, float fVolumedB = 5.0f, bool bMute = false, bool bLoop = false);
        static bool isSoundPlaying(int nChannelId);
        static void StopChannel(int nChannelId);
        static void StopAllChannels();
        static void SetChannel3DPosition(int nChannelId, const Vector3& vPosition);
        static void SetChannelVolume(int nChannelId, float fVolumedB);
        bool IsPlaying(int nChannelId) const;
        static float dbToVolume(float db);
        static float VolumeTodb(float volume);
    };
} // End of namespace Borealis
#endif
