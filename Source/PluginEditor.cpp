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
    playSnareButton.onClick = [&]() {audioProcessor.playSample(61);};
    playCrashButton.onClick = [&]() {audioProcessor.playSample(66);};
    playSnareAndCrashButton.onClick = [&]() {audioProcessor.playMultiple(61, 66); };
    a1.onClick = [this] {audioProcessor.updateToggleState(&a1, "1"); };
    a2.onClick = [this] {audioProcessor.updateToggleState(&a2, "2"); };
    a3.onClick = [this] {audioProcessor.updateToggleState(&a3, "3"); };
    addAndMakeVisible(a1);
    addAndMakeVisible(a2);
    addAndMakeVisible(a3);
    addAndMakeVisible(playSnareButton);
    addAndMakeVisible(playCrashButton);
    addAndMakeVisible(playSnareAndCrashButton);
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
    playCrashButton.setBounds(220, 20, 180, 180);
    playSnareAndCrashButton.setBounds(20, 220, 180, 180);

    a1.setBounds(20, 420, 20, 20);
    a2.setBounds(60, 420, 20, 20);
    a3.setBounds(100, 420, 20, 20);
}
