/******************************************************************************/
/*!
\file		AudioEngine.cpp
\author 	Valerie Koh
\par    	email: v.koh\@digipen.edu
\date   	September 11, 2024
\brief

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 *
 /******************************************************************************/

#include <BorealisPCH.hpp>
#include "Audio/AudioEngine.hpp"
#include <FMOD/fmod.hpp>

namespace Borealis
{

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

    static FMOD_VECTOR VectorToFmod(const Vector3& vPosition)
    {
        FMOD_VECTOR fVec;
        fVec.x = vPosition.x;
        fVec.y = vPosition.y;
        fVec.z = vPosition.z;
        return fVec;
    }


    static int ErrorCheck(FMOD_RESULT result)
    {
        if (result != FMOD_OK)
        {
            std::cout << "FMOD ERROR " << result << std::endl;
            return 1;
        }
        // cout << "FMOD all good" << endl;
        return 0;
    }

    Implementation::Implementation()
    {
        mpSystem = NULL;
        mnNextChannelId = 1;
        // Create FMOD Core system
        ErrorCheck(FMOD::System_Create(&mpSystem));
        // Initialize FMOD Core system
        ErrorCheck(mpSystem->init(32, FMOD_INIT_PROFILE_ENABLE, NULL));
    }

    Implementation::~Implementation()
    {
        // Release FMOD Core system
        ErrorCheck(mpSystem->release());
    }

    void Implementation::Update()
    {
        /*AudioEngine::PlayAudio(".\assets\audio\meow.mp3");*/
        std::vector<ChannelMap::iterator> pStoppedChannels;
        for (auto it = mChannels.begin(), itEnd = mChannels.end(); it != itEnd; ++it)
        {
            bool bIsPlaying = false;
            it->second->isPlaying(&bIsPlaying);
            if (!bIsPlaying)
            {
                pStoppedChannels.push_back(it);
            }
        }

        for (auto& it : pStoppedChannels)
        {
            mChannels.erase(it);
        }
        ErrorCheck(mpSystem->update());
    }

    Implementation* sgpImplementation = nullptr;

    void AudioEngine::Init()
    {
        sgpImplementation = new Implementation;
    }

    void AudioEngine::Update()
    {
        sgpImplementation->Update();
    }

    void AudioEngine::LoadAudio(const std::string& strSoundName, bool b3d, bool bLooping, bool bStream)
    {
        auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
        if (tFoundIt != sgpImplementation->mSounds.end())
            return;

        FMOD_MODE eMode = FMOD_DEFAULT;
        eMode |= b3d ? FMOD_3D : FMOD_2D;
        eMode |= bLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
        eMode |= bStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;

        FMOD::Sound* pSound = nullptr;
        ErrorCheck(sgpImplementation->mpSystem->createSound(strSoundName.c_str(), eMode, nullptr, &pSound));
        if (pSound)
        {
            sgpImplementation->mSounds[strSoundName] = pSound;
        }
    }

    void AudioEngine::UnLoadAudio(const std::string& strSoundName)
    {
        auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
        if (tFoundIt == sgpImplementation->mSounds.end())
            return;

        ErrorCheck(tFoundIt->second->release());
        sgpImplementation->mSounds.erase(tFoundIt);
    }

    int AudioEngine::PlayAudio(const std::string& strSoundName, const Vector3& vPosition, float fVolumedB, bool bMute, bool bLoop)
    {
        int nChannelId = sgpImplementation->mnNextChannelId++;

        // Load the sound if it hasn't been loaded yet
        auto tFoundIt = sgpImplementation->mSounds.find(strSoundName);
        if (tFoundIt == sgpImplementation->mSounds.end())
        {
            AudioEngine::LoadAudio(strSoundName, true, bLoop);  // Load with loop if needed
            tFoundIt = sgpImplementation->mSounds.find(strSoundName);
            if (tFoundIt == sgpImplementation->mSounds.end())
            {
                return -1;  // Error: Sound not found or failed to load
            }
        }

        FMOD::Channel* pChannel = nullptr;
        ErrorCheck(sgpImplementation->mpSystem->playSound(tFoundIt->second, nullptr, true, &pChannel));

        if (pChannel)
        {
            FMOD_MODE currMode;
            tFoundIt->second->getMode(&currMode);
            if (currMode & FMOD_3D)
            {
                FMOD_VECTOR position = VectorToFmod(vPosition);
                ErrorCheck(pChannel->set3DAttributes(&position, nullptr));
            }

            // Set the volume, mute, and loop properties
            ErrorCheck(pChannel->setVolume(dbToVolume(fVolumedB)));
            ErrorCheck(pChannel->setPaused(false));
            ErrorCheck(pChannel->setMute(bMute));  // Mute the sound if necessary
            ErrorCheck(pChannel->setMode(bLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF));  // Set loop mode

            // Store the channel in the channel map
            sgpImplementation->mChannels[nChannelId] = pChannel;
        }

        return nChannelId;  // Return the channel ID for tracking
    }

    bool AudioEngine::isSoundPlaying(int nChannelId)
    {
        // Find the channel using the channel ID
        auto tFoundChannel = sgpImplementation->mChannels.find(nChannelId);
        if (tFoundChannel == sgpImplementation->mChannels.end())
            return false; // Channel not found

        bool bIsPlaying = false;
        // Check if the channel is currently playing
        ErrorCheck(tFoundChannel->second->isPlaying(&bIsPlaying));

        return bIsPlaying;
    }

    void AudioEngine::SetChannel3DPosition(int nChannelId, const Vector3& vPosition)
    {
        auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
        if (tFoundIt == sgpImplementation->mChannels.end())
            return;

        FMOD_VECTOR position = VectorToFmod(vPosition);
        ErrorCheck(tFoundIt->second->set3DAttributes(&position, NULL));
    }

    void AudioEngine::SetChannelVolume(int nChannelId, float fVolumedB)
    {
        auto tFoundIt = sgpImplementation->mChannels.find(nChannelId);
        if (tFoundIt == sgpImplementation->mChannels.end())
            return;

        ErrorCheck(tFoundIt->second->setVolume(dbToVolume(fVolumedB)));
    }

  
    float AudioEngine::dbToVolume(float dB)
    {
        return powf(10.0f, 0.05f * dB);
    }

    float AudioEngine::VolumeTodb(float volume)
    {
        return 20.0f * log10f(volume);
    }

    void AudioEngine::Shutdown()
    {
        delete sgpImplementation;
    }
} // End of namespace Borealis