/*
  ==============================================================================

    SampleLoaderController.h
    Created: 29 Mar 2022 5:19:26pm
    Author:  WdYan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SampleLoaderController  : public juce::Component
{
public:
    SampleLoaderController();
    ~SampleLoaderController() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SampleLoaderController)
};
