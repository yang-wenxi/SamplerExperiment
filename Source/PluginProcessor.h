/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GroupedSampler.h"
#include "GlobalProperties.h"
#include "foleys_gui_magic.h"


//==============================================================================
/**
*/
class SamplerMAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    SamplerMAudioProcessor();
    ~SamplerMAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    void numChannelsChanged() override;
    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void playSample(juce::String instrumentName);

    juce::AudioProcessorValueTreeState::ParameterLayout createParams();
    void addParamListener();
    void channelControl(juce::String instrument, std::vector<std::unique_ptr<juce::RangedAudioParameter>>* paramVec);
    
    juce::MidiBuffer midiHandler(juce::MidiBuffer messages);

    juce::MidiBuffer buttonBuffer;
    juce::AudioProcessorValueTreeState tree;

    busConditionSender conditionSender;
    
private:
    GroupedSampler gSampler;
    juce::MidiMessage currentMsg;
    float currentNoteOnVelocity = 1.0f;
    float currentNoteOffVelocity = 1.0f;
    bool triggerFromMidi = false;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerMAudioProcessor)
};