/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SamplerMAudioProcessorEditor::SamplerMAudioProcessorEditor (SamplerMAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    playSnareButton.onClick = [&]() {audioProcessor.playSnare();};
    
    addAndMakeVisible(playSnareButton);
    setSize (500, 500);
}

SamplerMAudioProcessorEditor::~SamplerMAudioProcessorEditor()
{
}

//==============================================================================
void SamplerMAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void SamplerMAudioProcessorEditor::resized()
{
    playSnareButton.setBounds(20, 20, 180, 180);
}
