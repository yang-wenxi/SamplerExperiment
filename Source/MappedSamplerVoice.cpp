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

void MappedSamplerVoice::renderNextBlock(juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) {
    if (auto* playingSound = dynamic_cast<OneSample*>(getCurrentlyPlayingSound().get())) {
        //DBG("------fetching things-----");
        //printingThings();
        
        auto& data = *playingSound -> getAudioData();
        const float* const inL = data.getReadPointer(0);
        const float* const inR = data.getNumChannels() > 1 ? data.getReadPointer(1) : nullptr;
        
        int key = getInstrument();
        float* out;

        if (outputBuffer.getNumChannels() > key) {
            out = outputBuffer.getWritePointer(key, startSample);
            while (--numSamples >= 0) {
                auto pos = (int) sourceSamplePosition;
                auto alpha = (float)(sourceSamplePosition - pos);
                auto invAlpha = 1.0f - alpha;
                
                float l = (inL[pos] * invAlpha + inL[pos + 1] * alpha);
                float r = (inR != nullptr) ? (inR[pos] * invAlpha + inR[pos + 1] * alpha)
                    : l;
                
                l = EE.applyTo(l);
                r = EE.applyTo(r);
                
                if (out != nullptr)
                    *out++ += l;
                else {
                    clearCurrentNote();
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
