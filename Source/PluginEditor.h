/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "foleys_gui_magic.h"


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
    
    juce::ToggleButton snareChannelControl_1{ "1" };
    juce::ToggleButton snareChannelControl_2{ "2" };
    juce::ToggleButton snareChannelControl_3{ "3" };
    juce::ToggleButton snareChannelControl_4{ "4" };
    juce::ToggleButton snareChannelControl_5{ "5" };
    juce::ToggleButton snareChannelControl_6{ "6" };

    //std::vector<juce::ToggleButton> snareChannelControl;
    //std::vector<juce::ToggleButton> crashChannelControl;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> snareChannelAttachment_1;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> snareChannelAttachment_2;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> snareChannelAttachment_3;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> snareChannelAttachment_4;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> snareChannelAttachment_5;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> snareChannelAttachment_6;
    //std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>> snareChannelAttachment;
    //std::vector<std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment>> crashChannelAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerMAudioProcessorEditor)
};
