/*
  ==============================================================================

    NewWindow.h
    Created: 18 Apr 2022 2:09:35pm
    Author:  WdYan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class NewWindow  : public juce::Component
{
public:
    NewWindow();
    ~NewWindow() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    juce::ToggleButton imOn{ "I'm on" };

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewWindow)
};
