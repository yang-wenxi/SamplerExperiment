/*
  ==============================================================================

    MappedSamplerVoice.cpp
    Created: 17 Mar 2022 10:04:33pm
    Author:  杨文希

  ==============================================================================
*/

#include "MappedSamplerVoice.h"
#include "GlobalProperties.h"


bool MappedSamplerVoice::canPlaySound(juce::SynthesiserSound* sampSound) {
    return ((dynamic_cast<OneSample*>(sampSound)) != nullptr);
}


void MappedSamplerVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sampSound, int pitchWheel) {
    if (auto* sound = dynamic_cast<const OneSample*> (sampSound))
    {
        pitchRatio = std::pow (2.0, (midiNoteNumber - sound -> midiRootNote) / 12.0)
                        * sound->sourceSampleRate / getSampleRate();

        sourceSamplePosition = 0.0;
        EE.setSampleRate(sound -> sourceSampleRate);
        EE.turnOn();
    }
    else
    {
        jassertfalse; // this object can only play SamplerSounds!
    }
}




void MappedSamplerVoice::stopNote(float velocity, bool allowTailOff) {
    if (allowTailOff) {
        if (EE.noteOffOk())
            EE.noteOff();
    }
    else if (!allowTailOff && velocity == 0.0f) {
        EE.shutDown();
        clearCurrentNote();
    }
    else if (!allowTailOff && velocity == 1.0f) {
        if (EE.noteOffOk()) 
            EE.noteOff();
    }
}

void MappedSamplerVoice::pitchWheelMoved(int newValue) {
    
}

void MappedSamplerVoice::controllerMoved(int controllerNumber, int newValue) {
    
}

void MappedSamplerVoice::addPlaybackChannel(int chan) {
    channelList.push_back(chan);
}

void MappedSamplerVoice::removePlaybackChannel(int chan) {
    for (int i = 0; i < channelList.size(); i++) {
        if (channelList.at(i) == chan) {
            channelList.erase(channelList.begin() + i);
            break;
        }
    }
}

void MappedSamplerVoice::renderNextBlock(juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) {
    if (auto* playingSound = dynamic_cast<OneSample*>(getCurrentlyPlayingSound().get())) {

        auto& data = *playingSound -> getAudioData();
        const float* const inL = data.getReadPointer(0);
        const float* const inR = data.getNumChannels() > 1 ? data.getReadPointer(1) : nullptr;
        
        int key = getInstrument();

        std::vector<int> hasPlaybackChannel;
        std::vector<float*> out;
        
        for (auto c : playToChannel) {
            if (busAvailable[c]) {
                hasPlaybackChannel.push_back(busChannelVector[c] - 1);
            }
        }
        
        DBG("Thread Voice------------------------------------");
        DBG("busAvailable");
        juce::String baS = "";
        for (auto ba : busAvailable) {
            baS = baS + (std::to_string(ba) + "  ");
        }
        DBG(baS);
        
        DBG("busChannelVec");
        juce::String bcV = "";
        for (auto bc : busChannelVector) {
            bcV = bcV + (std::to_string(bc) + "  ");
        }
        DBG(bcV);
        
        if (!hasPlaybackChannel.empty()) {
            for (auto c : hasPlaybackChannel) {
                out.push_back(outputBuffer.getWritePointer(c, startSample));
            }
            
            while (--numSamples >= 0) {
                auto pos = (int) sourceSamplePosition;
                auto alpha = (float)(sourceSamplePosition - pos);
                auto invAlpha = 1.0f - alpha;
                
                float l = (inL[pos] * invAlpha + inL[pos + 1] * alpha);
                float r = (inR != nullptr) ? (inR[pos] * invAlpha + inR[pos + 1] * alpha)
                    : l;
                
                l = EE.applyTo(l);
                r = EE.applyTo(r);
                
                for (auto o : out) {
                    *o++ += l;
                }
                
                sourceSamplePosition += pitchRatio;
                
                if (sourceSamplePosition > playingSound -> length || EE.getState() == 0) {
                    clearCurrentNote();
                    break;
                }
            }
        }
        else {
            stopNote(0, true);
        }
    }
}

void MappedSamplerVoice::addPlayToChannel(int chan) {
    playToChannel.push_back(chan);
}

void MappedSamplerVoice::removePlayToChannel(int chan) {
    for (int d = 0; d < playToChannel.size(); d++) {
        if (playToChannel.at(d) == chan) {
            playToChannel.erase(playToChannel.begin() + d);
            break;
        }
    }
}
