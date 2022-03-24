/*
  ==============================================================================

    OneSample.h
    Created: 18 Mar 2022 11:33:37am
    Author:  杨文希

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "MappedSamplerVoice.h"
#include "SoundMap.h"


class OneSample : public juce::SamplerSound
{
public:
    friend class MappedSamplerVoice;
    OneSample(const juce::String &name, juce::AudioFormatReader &source, const juce::BigInteger &midiNotes, int midiNoteForNormalPitch, double attackTimeSecs, double releaseTimeSecs, double maxSampleLengthSeconds) : SamplerSound(name, source, midiNotes, midiNoteForNormalPitch, attackTimeSecs, releaseTimeSecs, maxSampleLengthSeconds),
    sourceSampleRate(source.sampleRate), length(source.lengthInSamples), midiRootNote(midiNoteForNormalPitch), assignedNote(midiNotes){}
    
    int getMidiNote() {
        return assignedNote.getHighestBit();
    }

private:
    double sourceSampleRate;
    long long length;
    int midiRootNote;
    juce::BigInteger assignedNote;
};
