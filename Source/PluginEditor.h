/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class SamplerMAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SamplerMAudioProcessorEditor (SamplerMAudioProcessor&);
    ~SamplerMAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SamplerMAudioProcessor& audioProcessor;
    
    juce::TextButton playSnareButton {"SNARE"};
    juce::TextButton playCrashButton { "CRASH" };
    juce::TextButton playSnareAndCrashButton { "S C" };
    /*
    juce::ToggleButton a1{ "1" };
    juce::ToggleButton a2{ "2" };
    juce::ToggleButton a3{ "3" };
    juce::ToggleButton a4{ "4" };
    juce::ToggleButton a5{ "5" };
    juce::ToggleButton a6{ "6" };
    */
    juce::ToggleButton *snareSet[10];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerMAudioProcessorEditor)
};
