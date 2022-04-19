/*
  ==============================================================================

    RoomSelectWindow.h
    Created: 18 Apr 2022 8:08:30pm
    Author:  WdYan

  ==============================================================================
*/

#pragma once

#include "PluginProcessor.h"
#include <JuceHeader.h>

//==============================================================================
/*
*/
class RoomSelectWindow  : public juce::Component
{
public:
    RoomSelectWindow(juce::AudioProcessor* processor);
    ~RoomSelectWindow() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    SamplerMAudioProcessor* audioProcessor;
    
    juce::ToggleButton roomA{ "Room A" };
    juce::ToggleButton roomB{ "Room B" };
    juce::ToggleButton roomC{ "Room C" };

    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> roomAttachment_A;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> roomAttachment_B;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> roomAttachment_C;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RoomSelectWindow)
};
