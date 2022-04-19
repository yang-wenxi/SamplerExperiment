/*
  ==============================================================================

    DrumSetSelectWindow.cpp
    Created: 18 Apr 2022 8:08:02pm
    Author:  WdYan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DrumSetSelectWindow.h"

//==============================================================================
DrumSetSelectWindow::DrumSetSelectWindow(juce::AudioProcessor* processor)
{
    audioProcessor = dynamic_cast<SamplerMAudioProcessor*>(processor);
    setAlwaysOnTop(true);
}

DrumSetSelectWindow::~DrumSetSelectWindow()
{

}

void DrumSetSelectWindow::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);

}

void DrumSetSelectWindow::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
