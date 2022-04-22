/*
  ==============================================================================

    MappedSamplerVoice.h
    Created: 17 Mar 2022 10:04:33pm
    Author:  杨文希

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "OneSample.h"
#include "EnvelopeEngine.h"
#include "GlobalProperties.h"

class MappedSamplerVoice : public juce::SamplerVoice, public juce::AudioProcessorValueTreeState::Listener
{
public:
    MappedSamplerVoice(int i, juce::String instrument) {
        instrumentIndex = i;
        this->instrument = instrument;
        currentSampleRate = 48000;
        pitchVal = 0;
        playbackChannel.push_back(0);
    }
    
    int getInstrumentIndex() {
        return instrumentIndex;
    }
    
    juce::String getInstrument() {
        return instrument;
    }
    
    void setPitchVal(int pitchV) {
        pitchVal = pitchV;
    }
    
    void setMidiNote(int note) {
        midiNotes.setBit(note);
    }
    
    bool canPlaySample(int note) const {
        return midiNotes[note];
    }

    void receiveBusCondition(busConditionSender* cond) {
        busCondition = *cond;
    }

    void addPlaybackChannel(int chan);
    void removePlaybackChannel(int chan);

    bool canPlaySound(juce::SynthesiserSound* sampSound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sampSound, int pitchWheel) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newValue) override;
    void controllerMoved(int controllerNumber, int newValue) override;
    void renderNextBlock(juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
    void renderNextBlockI(juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples);
    void parameterChanged(const juce::String &parameterID, float newValue) override;

    void renderNextBlockBySample(juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples);
    void renderNextBlockByBuffer(juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples);
    
    std::vector<int> playbackChannel;
    busConditionSender busCondition;

private:
    juce::AudioBuffer<float> processedBuffer;
    float currentNoteOnVel = 1.0f;
    float gain = 0.6f;
    int instrumentIndex;
    juce::String instrument;
    int pitchVal;
    juce::BigInteger midiNotes;
    double currentSampleRate;
    double pitchRatio = 0;
    double sourceSamplePosition = 0;
    EnvelopeEngine EE;
};
