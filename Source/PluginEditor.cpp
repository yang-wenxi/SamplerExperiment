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
    Timer::startTimerHz(30);

    playSnareButton.onClick = [&]() {audioProcessor.playSample("SNARE", true);};
    playCrashButton.onClick = [&]() {audioProcessor.playSample("CRASH", true);};
    playTomButton.onClick = [&]() {audioProcessor.playSample("TOM", true);};
    playKickButton.onClick = [&]() {audioProcessor.playSample("KICK", true);};


    
//    snareButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree,
//                                                                                                   "SNARE_BUTTON", playSnareButton);
//    crashButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree,
//                                                                                                   "CRASH_BUTTON", playCrashButton);
//    tomButtonAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree,
//                                                                                                   "TOM_BUTTON", playTomButton);
    
    juce::String snareChannel = "SNARE_CHANNEL+";
    snareChannelAttachment_1 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree,
                                                                                                      snareChannel + "1", snareChannelControl_1);
    snareChannelAttachment_2 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree,
                                                                                                      snareChannel + "2", snareChannelControl_2);
    snareChannelAttachment_3 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree,
                                                                                                      snareChannel + "3", snareChannelControl_3);
    snareChannelAttachment_4 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree,
                                                                                                      snareChannel + "4", snareChannelControl_4);
    snareChannelAttachment_5 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree,
                                                                                                      snareChannel + "5", snareChannelControl_5);
    snareChannelAttachment_6 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree,
                                                                                                      snareChannel + "6", snareChannelControl_6);
    
    juce::String crashChannel = "CRASH_CHANNEL+";
    crashChannelAttachment_1 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree,
                                                                                                      crashChannel + "1", crashChannelControl_1);
    crashChannelAttachment_2 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree,
                                                                                                      crashChannel + "2", crashChannelControl_2);
    crashChannelAttachment_3 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree,
                                                                                                      crashChannel + "3", crashChannelControl_3);
    crashChannelAttachment_4 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree,
                                                                                                      crashChannel + "4", crashChannelControl_4);
    crashChannelAttachment_5 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree,
                                                                                                      crashChannel + "5", crashChannelControl_5);
    crashChannelAttachment_6 = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree,
                                                                                                      crashChannel + "6", crashChannelControl_6);
    
    
    parameterSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    parameterSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(parameterSlider);
    parameterSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree,
                                                                                                       "GAIN", parameterSlider);

    openNewWindowButton.setBounds(100, 550, 200, 25);
    openNewWindowButton.onClick = [this]() {openNewWindow(openNewWindowButton, "window_1"); };

    window_1.setAlwaysOnTop(true);

    addAndMakeVisible(snareChannelControl_6);
    addAndMakeVisible(snareChannelControl_5);
    addAndMakeVisible(snareChannelControl_4);
    addAndMakeVisible(snareChannelControl_3);
    addAndMakeVisible(snareChannelControl_2);
    addAndMakeVisible(snareChannelControl_1);

    addAndMakeVisible(crashChannelControl_1);
    addAndMakeVisible(crashChannelControl_2);
    addAndMakeVisible(crashChannelControl_3);
    addAndMakeVisible(crashChannelControl_4);
    addAndMakeVisible(crashChannelControl_5);
    addAndMakeVisible(crashChannelControl_6);

    addAndMakeVisible(openNewWindowButton);
    
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
    addAndMakeVisible(playTomButton);
    addAndMakeVisible(playKickButton);
    
    addAndMakeVisible(sampleSetSwitch);
    setSize (700, 700);
    
    audioProcessor.tree.addParameterListener("ROOM_A", this);
    audioProcessor.tree.addParameterListener("ROOM_B", this);
    audioProcessor.tree.addParameterListener("ROOM_C", this);
}

SamplerMAudioProcessorEditor::~SamplerMAudioProcessorEditor()
{
    Timer::stopTimer();
}

//==============================================================================
void SamplerMAudioProcessorEditor::paint (juce::Graphics& g)
{
    
    g.fillAll(roomColours[currentRoom]);
}


void SamplerMAudioProcessorEditor::resized()
{
    playSnareButton.setBounds(20, 20, 180, 180);
    playCrashButton.setBounds(220, 20, 180, 180);
    playTomButton.setBounds(20, 220, 180, 180);
    playKickButton.setBounds(220, 220, 180, 180);
    //playSnareAndCrashButton.setBounds(20, 220, 180, 180);
    
    snareChannelControl_1.setBounds(20, 420, 40, 40);
    snareChannelControl_2.setBounds(80, 420, 40, 40);
    snareChannelControl_3.setBounds(140, 420, 40, 40);
    snareChannelControl_4.setBounds(200, 420, 40, 40);
    snareChannelControl_5.setBounds(260, 420, 40, 40);
    snareChannelControl_6.setBounds(320, 420, 40, 40);
    
    crashChannelControl_1.setBounds(20, 480, 40, 40);
    crashChannelControl_2.setBounds(80, 480, 40, 40);
    crashChannelControl_3.setBounds(140, 480, 40, 40);
    crashChannelControl_4.setBounds(200, 480, 40, 40);
    crashChannelControl_5.setBounds(260, 480, 40, 40);
    crashChannelControl_6.setBounds(320, 480, 40, 40);
    
    sampleSetSwitch.setBounds(400, 0, 200, 200);
    
    parameterSlider.setBounds(420, 260, 100, 100);
}

void SamplerMAudioProcessorEditor::timerCallback() {
    repaint();
}

void SamplerMAudioProcessorEditor::parameterChanged(const juce::String &parameterID, float newValue) {
    if (parameterID.contains("ROOM") && newValue == 1.0f) {
        juce::String room = parameterID.substring(5, 6);
        if (room == "A") {
            currentRoom = ROOM_A;
        }
        else if (room == "B") {
            currentRoom = ROOM_B;
        }
        else if (room == "C") {
            currentRoom = ROOM_C;
        }
    }
}

void SamplerMAudioProcessorEditor::openNewWindow(juce::ToggleButton& button, juce::String buttonData) {
    if (buttonData == "window_1") {
        bool isToggled = button.getToggleState();
        if (isToggled) {
            addAndMakeVisible(window_1);
            window_1.setBounds(400, 500, 100, 100);
        }
        else {
            removeChildComponent(&window_1);
        }
    }
}
