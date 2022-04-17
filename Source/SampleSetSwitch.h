/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.1.6

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "PluginProcessor.h"
#include <JuceHeader.h>
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SampleSetSwitch  : public juce::Component,
                         public juce::Button::Listener
{
public:
    //==============================================================================
    SampleSetSwitch (juce::AudioProcessor* processor);
    ~SampleSetSwitch() override;

    //==============================================================================

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;
//    void receiveTree(juce::AudioProcessorValueTreeState* tree);

    SamplerMAudioProcessor* audioProcessor;
private:
    std::unique_ptr<juce::ToggleButton> roomA;
    std::unique_ptr<juce::ToggleButton> roomB;
    std::unique_ptr<juce::ToggleButton> roomC;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> roomAttachment_A;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> roomAttachment_B;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> roomAttachment_C;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SampleSetSwitch)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

