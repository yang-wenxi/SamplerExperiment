/*
  ==============================================================================

    OutputChannelSelectWindow.cpp
    Created: 18 Apr 2022 8:08:18pm
    Author:  WdYan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OutputChannelSelectWindow.h"

//==============================================================================
OutputChannelSelectWindow::OutputChannelSelectWindow(juce::AudioProcessor* processor)
{
    audioProcessor = dynamic_cast<SamplerMAudioProcessor*>(processor);

    setAlwaysOnTop(true);
    setBounds(100, 300, 500, 200);

    snareChannelControl_1.setBounds(20, 120, 40, 40);
    snareChannelControl_2.setBounds(80, 120, 40, 40);
    snareChannelControl_3.setBounds(140, 120, 40, 40);
    snareChannelControl_4.setBounds(200, 120, 40, 40);
    snareChannelControl_5.setBounds(260, 120, 40, 40);
    snareChannelControl_6.setBounds(320, 120, 40, 40);

    crashChannelControl_1.setBounds(20, 120, 40, 40);
    crashChannelControl_2.setBounds(80, 120, 40, 40);
    crashChannelControl_3.setBounds(140, 120, 40, 40);
    crashChannelControl_4.setBounds(200, 120, 40, 40);
    crashChannelControl_5.setBounds(260, 120, 40, 40);
    crashChannelControl_6.setBounds(320, 120, 40, 40);

    attachParameters();

}

OutputChannelSelectWindow::~OutputChannelSelectWindow()
{
}

void OutputChannelSelectWindow::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (juce::Colours::black);
}

void OutputChannelSelectWindow::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void OutputChannelSelectWindow::instrumentToSelect(juce::String instrument) {
    removeAllChildren();
    if (instrument == "snare") {
        addAndMakeVisible(snareChannelControl_6);
        addAndMakeVisible(snareChannelControl_5);
        addAndMakeVisible(snareChannelControl_4);
        addAndMakeVisible(snareChannelControl_3);
        addAndMakeVisible(snareChannelControl_2);
        addAndMakeVisible(snareChannelControl_1);
    }
    else if (instrument == "kick") {

    }
    else if (instrument == "crash") {
        addAndMakeVisible(crashChannelControl_1);
        addAndMakeVisible(crashChannelControl_2);
        addAndMakeVisible(crashChannelControl_3);
        addAndMakeVisible(crashChannelControl_4);
        addAndMakeVisible(crashChannelControl_5);
        addAndMakeVisible(crashChannelControl_6);
    }
    else if (instrument == "tom") {

    }
    else if (instrument == "ophat" || instrument == "clhat") {

    }
    else if (instrument == "clap") {

    }
}

void OutputChannelSelectWindow::attachParameters()
{
    juce::String snareChannel = "SNARE_CHANNEL+";
    snareChannelAttachment_1 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor->tree,
        snareChannel + "1", snareChannelControl_1);
    snareChannelAttachment_2 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor->tree,
        snareChannel + "2", snareChannelControl_2);
    snareChannelAttachment_3 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor->tree,
        snareChannel + "3", snareChannelControl_3);
    snareChannelAttachment_4 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor->tree,
        snareChannel + "4", snareChannelControl_4);
    snareChannelAttachment_5 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor->tree,
        snareChannel + "5", snareChannelControl_5);
    snareChannelAttachment_6 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor->tree,
        snareChannel + "6", snareChannelControl_6);

    juce::String crashChannel = "CRASH_CHANNEL+";
    crashChannelAttachment_1 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor->tree,
        crashChannel + "1", crashChannelControl_1);
    crashChannelAttachment_2 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor->tree,
        crashChannel + "2", crashChannelControl_2);
    crashChannelAttachment_3 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor->tree,
        crashChannel + "3", crashChannelControl_3);
    crashChannelAttachment_4 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor->tree,
        crashChannel + "4", crashChannelControl_4);
    crashChannelAttachment_5 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor->tree,
        crashChannel + "5", crashChannelControl_5);
    crashChannelAttachment_6 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor->tree,
        crashChannel + "6", crashChannelControl_6);
}
