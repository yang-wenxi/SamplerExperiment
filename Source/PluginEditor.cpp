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
    
    snareChannelAttachment_1 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree, 
        "SNARE_CHANNEL+1", snareChannelControl_1);
    snareChannelAttachment_2 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree,
        "SNARE_CHANNEL+2", snareChannelControl_2);
    snareChannelAttachment_3 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree,
        "SNARE_CHANNEL+3", snareChannelControl_3);
    snareChannelAttachment_4 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree,
        "SNARE_CHANNEL+4", snareChannelControl_4);
    snareChannelAttachment_5 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree,
        "SNARE_CHANNEL+5", snareChannelControl_5);
    snareChannelAttachment_6 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree,
        "SNARE_CHANNEL+6", snareChannelControl_6);
    
    parameterSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    parameterSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(parameterSlider);
    parameterSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree,
                                                                                                       "ATTACK_ADSR", parameterSlider);
    addAndMakeVisible(snareChannelControl_6);
    addAndMakeVisible(snareChannelControl_5);
    addAndMakeVisible(snareChannelControl_4);
    addAndMakeVisible(snareChannelControl_3);
    addAndMakeVisible(snareChannelControl_2);
    addAndMakeVisible(snareChannelControl_1);

 /*   for (int i = 1; i <= 6; i++) {
        juce::ToggleButton snareButton{ std::to_string(i) };
        snareChannelControl.push_back(snareButton);
        snareChannelAttachment.push_back(std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree,
            "SNARE_CHANNEL+" + std::to_string(i), snareChannelControl[i - 1]));

        juce::ToggleButton crashButton{ std::to_string(i) };
        crashChannelControl.push_back(crashButton);
    }*/
    
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
    
    snareChannelControl_1.setBounds(20, 420, 40, 40);
    snareChannelControl_2.setBounds(80, 420, 40, 40);
    snareChannelControl_3.setBounds(140, 420, 40, 40);
    snareChannelControl_4.setBounds(200, 420, 40, 40);
    snareChannelControl_5.setBounds(260, 420, 40, 40);
    snareChannelControl_6.setBounds(320, 420, 40, 40);
    
    parameterSlider.setBounds(260, 220, 100, 100);
}
