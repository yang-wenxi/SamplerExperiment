/*
  ==============================================================================

    NewWindow.cpp
    Created: 18 Apr 2022 2:09:35pm
    Author:  WdYan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "NewWindow.h"

//==============================================================================
NewWindow::NewWindow()
{
    setAlwaysOnTop(true);
    setBounds(400, 500, 100, 100);
    imOn.setBounds(10, 30, 80, 40);
    addAndMakeVisible(imOn);
    setSize(100, 100);
}

NewWindow::~NewWindow()
{
}

void NewWindow::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::green);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::yellow);

}

void NewWindow::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
