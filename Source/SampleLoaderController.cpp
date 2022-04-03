/*
  ==============================================================================

    SampleLoaderController.cpp
    Created: 29 Mar 2022 5:19:26pm
    Author:  WdYan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SampleLoaderController.h"

//==============================================================================
SampleLoaderController::SampleLoaderController()
{

}

SampleLoaderController::~SampleLoaderController()
{
}

void SampleLoaderController::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("SampleLoaderController", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void SampleLoaderController::resized()
{

}
