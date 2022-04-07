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
    playSnareAndCrashButton.onClick = [&]() {audioProcessor.playMultiple(new int[2] {62, 65}); };
    
    toggle_1_Attachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree, "CHANNEL_1", a1);
    
    addAndMakeVisible(a1);
    addAndMakeVisible(a2);
    addAndMakeVisible(a3);
    addAndMakeVisible(a4);
    addAndMakeVisible(a5);
    addAndMakeVisible(a6);
    
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

}


void SamplerMAudioProcessorEditor::resized()
{
    playSnareButton.setBounds(20, 20, 180, 180);
    playCrashButton.setBounds(220, 20, 180, 180);
    playSnareAndCrashButton.setBounds(20, 220, 180, 180);
    
    a1.setBounds(20, 420, 40, 40);
    a2.setBounds(80, 420, 40, 40);
    a3.setBounds(140, 420, 40, 40);
    a4.setBounds(200, 420, 40, 40);
    a5.setBounds(260, 420, 40, 40);
    a6.setBounds(320, 420, 40, 40);
    
}
