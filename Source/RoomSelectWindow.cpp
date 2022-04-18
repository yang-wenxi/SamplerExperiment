/*
  ==============================================================================

    RoomSelectWindow.cpp
    Created: 18 Apr 2022 8:08:30pm
    Author:  WdYan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RoomSelectWindow.h"

//==============================================================================

RoomSelectWindow::RoomSelectWindow(juce::AudioProcessor* processor) {
    audioProcessor = dynamic_cast<SamplerMAudioProcessor*>(processor);

    setAlwaysOnTop(true);

    addAndMakeVisible(roomA);
    roomA.setRadioGroupId(1001);

    addAndMakeVisible(roomB);
    roomB.setRadioGroupId(1001);

    addAndMakeVisible(roomC);
    roomC.setRadioGroupId(1001);

    roomA.setBounds(50, 50, 100, 24);
    roomB.setBounds(50, 80, 100, 24);
    roomC.setBounds(50, 110, 100, 24);

    setBounds(200, 200, 200, 200);
    setSize(200, 200);


    roomAttachment_A = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor->tree,
        "ROOM_A", roomA);
    roomAttachment_B = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor->tree,
        "ROOM_B", roomB);
    roomAttachment_C = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor->tree,
        "ROOM_C", roomC);
}

RoomSelectWindow::~RoomSelectWindow()
{
}

void RoomSelectWindow::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);   // clear the background
}

void RoomSelectWindow::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
