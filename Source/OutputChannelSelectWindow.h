/*
  ==============================================================================

    OutputChannelSelectWindow.h
    Created: 18 Apr 2022 8:08:18pm
    Author:  WdYan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class OutputChannelSelectWindow  : public juce::Component
{
public:
    OutputChannelSelectWindow(juce::AudioProcessor* processor);
    ~OutputChannelSelectWindow() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void instrumentToSelect(juce::String instrument);

private:
    SamplerMAudioProcessor* audioProcessor;

    juce::ToggleButton snareChannelControl_1{ "s1" };
    juce::ToggleButton snareChannelControl_2{ "s2" };
    juce::ToggleButton snareChannelControl_3{ "s3" };
    juce::ToggleButton snareChannelControl_4{ "s4" };
    juce::ToggleButton snareChannelControl_5{ "s5" };
    juce::ToggleButton snareChannelControl_6{ "s6" };

    juce::ToggleButton crashChannelControl_1{ "c1" };
    juce::ToggleButton crashChannelControl_2{ "c2" };
    juce::ToggleButton crashChannelControl_3{ "c3" };
    juce::ToggleButton crashChannelControl_4{ "c4" };
    juce::ToggleButton crashChannelControl_5{ "c5" };
    juce::ToggleButton crashChannelControl_6{ "c6" };

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> snareChannelAttachment_1;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> snareChannelAttachment_2;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> snareChannelAttachment_3;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> snareChannelAttachment_4;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> snareChannelAttachment_5;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> snareChannelAttachment_6;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> crashChannelAttachment_1;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> crashChannelAttachment_2;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> crashChannelAttachment_3;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> crashChannelAttachment_4;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> crashChannelAttachment_5;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> crashChannelAttachment_6;

    void attachParameters();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OutputChannelSelectWindow)
};
