/*
  ==============================================================================

    DrumSetSelectWindow.h
    Created: 18 Apr 2022 8:08:02pm
    Author:  WdYan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class DrumSetSelectWindow  : public juce::Component
{
public:
    DrumSetSelectWindow(juce::AudioProcessor* processor);
    ~DrumSetSelectWindow() override;

    void paint (juce::Graphics&) override;
    void resized() override;


private:
    SamplerMAudioProcessor* audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DrumSetSelectWindow)
};
