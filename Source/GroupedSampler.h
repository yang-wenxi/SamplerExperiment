/*
  ==============================================================================

    GroupedSampler.h
    Created: 17 Mar 2022 10:51:18pm
    Author:  杨文希

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "OneSample.h"
#include "MappedSamplerVoice.h"
#include "SampleGroup.h"
#include "EnvelopeEngine.h"
#include "GlobalProperties.h"
#include "SampleBundle.h"

class GroupedSampler : public juce::Synthesiser
{
    const int kick = 60;
    const int snare = 61;
    const int tom = 62;
    const int ophat= 63;
    const int clhat = 64;
    const int ride = 65;
    const int crash = 66;
    const int clap = 67;
    const int perc = 68;
    
public:
    void addSample(juce::String instrument, juce::String fileName);
    
    void addSampleVoice(MappedSamplerVoice* newVoice);
    
    //void parameterChanged(const juce::String &parameterID, float newValue) override;
    void noteOn(int midiChannel, int midiNoteNumber, float velocity);
    
    void prepare();
    void setMap();
    
    void loadSamples(juce::String rootNote);
    bool isNoteMapped (int midiNote);
    
    void brodcastBusCondition(busConditionSender* cond);
    void toggleChannelState(int voiceID, int chanID, bool state);
    
    juce::ReferenceCountedArray<SampleGroup>* getGroup () {
        return &sampleGroup;
    }

    std::vector<SampleBundle>* getBundleVector() {
        return &sampleBundleVector;
    }
    
    typedef enum Instruments { KICK = 0, SNARE, CLAP, TOM, CLHAT, PERC, OPHAT, CRASH, RIDE }Instruments_t;
    
    std::map<int, int> noteToIndexMap;
    std::map<juce::String, int> instrumentToNoteMap;
    
    juce::StringArray instruments {"KICK", "SNARE", "TOM", "OPH", "CLH", "RIDE", "CRASH", "CLAP", "PERC"};
    juce::StringArray noteName {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
    busConditionSender busCondition;

private:
    juce::AudioFormatManager formatManager;
    juce::AudioFormatReader* fmtReader {nullptr};
    juce::ReferenceCountedArray<SampleGroup> sampleGroup;
    std::vector<SampleBundle> sampleBundleVector;
    juce::File samplesFolder;
};

