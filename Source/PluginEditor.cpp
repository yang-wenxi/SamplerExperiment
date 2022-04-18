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

    playSnareButton.onClick = [&]() {audioProcessor.playSample("SNARE");};
    playCrashButton.onClick = [&]() {audioProcessor.playSample("CRASH");};
    playTomButton.onClick = [&]() {audioProcessor.playSample("TOM");};
    playKickButton.onClick = [&]() {audioProcessor.playSample("KICK");};
    
    parameterSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    parameterSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 50);

    playSnareButton.setBounds(20, 20, 180, 180);
    playCrashButton.setBounds(220, 20, 180, 180);
    playTomButton.setBounds(20, 220, 180, 180);
    playKickButton.setBounds(220, 220, 180, 180);
    //playSnareAndCrashButton.setBounds(20, 220, 180, 180);

    parameterSlider.setBounds(420, 260, 100, 100);

    roomSelectButton.setBounds(550, 100, 100, 40);
    outputSelectButton_Snare.setBounds(550, 150, 100, 40);
    outputSelectButton_Crash.setBounds(550, 200, 100, 40);
    drumSelectButton.setBounds(550, 250, 100, 40);

    openNewWindowButton.setBounds(100, 550, 200, 25);
    openNewWindowButton.onClick = [this]() {openNewWindow(openNewWindowButton, "window_1"); };

    outputSelectButton_Crash.onClick = [this]() {openNewWindow(outputSelectButton_Crash, "outputselect+crash"); };
    outputSelectButton_Snare.onClick = [this]() {openNewWindow(outputSelectButton_Snare, "outputselect+snare"); };

    addAndMakeVisible(parameterSlider);
    addAndMakeVisible(roomSelectButton);
    addAndMakeVisible(outputSelectButton_Snare);
    addAndMakeVisible(outputSelectButton_Crash);
    addAndMakeVisible(drumSelectButton);
    addAndMakeVisible(openNewWindowButton);

    addAndMakeVisible(playSnareButton);
    addAndMakeVisible(playCrashButton);
    addAndMakeVisible(playTomButton);
    addAndMakeVisible(playKickButton);

    //outputSelectButton_Crash.setRadioGroupId(OUTPUT_CHANNEL_SELECT);
    //outputSelectButton_Snare.setRadioGroupId(OUTPUT_CHANNEL_SELECT);
    //outputNotShowButton.setRadioGroupId(OUTPUT_CHANNEL_SELECT);
    
    setSize (700, 700);

    attachParameters();
    linkParamChangeListeners();
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
    
    parameterSlider.setBounds(420, 260, 100, 100);
}

void SamplerMAudioProcessorEditor::timerCallback() {
    repaint();
}

void SamplerMAudioProcessorEditor::openNewWindow(juce::ToggleButton& button, juce::String buttonData) {
    bool isToggled = button.getToggleState();
    if (buttonData == "window_1") {
        if (isToggled) {
            addAndMakeVisible(window_1);
        }
        else {
            removeChildComponent(&window_1);
        }
    }

    if (buttonData.contains("outputselect")) {
        int instrumentIndex = buttonData.indexOfChar('+') + 1;
        juce::String instrumentName = buttonData.substring(instrumentIndex, buttonData.length()).toLowerCase();
        if (isToggled) {
            if (instrumentName != "snare") {
                outputSelectButton_Snare.setToggleState(false, juce::NotificationType::dontSendNotification);
                DBG("new Snare Value Set");
            }
            if (instrumentName != "crash") {
                outputSelectButton_Crash.setToggleState(false, juce::NotificationType::dontSendNotification);
                DBG("new Crash Value Set");
            }
            outputSelectWindow.instrumentToSelect(instrumentName);
            addAndMakeVisible(outputSelectWindow);
        }
        else
            removeChildComponent(&outputSelectWindow);
    }
}


void SamplerMAudioProcessorEditor::parameterChanged(const juce::String &parameterID, float newValue) {
    if (parameterID.contains("ROOM")) {
        if (newValue == 1.0f) {
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

    if (parameterID == "BUTTON_SELECT_ROOM") {
        if (newValue == 1.0f)
            addAndMakeVisible(roomSelectWin);
        else
            removeChildComponent(&roomSelectWin);
    }
}

void SamplerMAudioProcessorEditor::attachParameters()
{
    parameterSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree,
        "GAIN", parameterSlider);

    roomSelectButtonAtachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree,
        "BUTTON_SELECT_ROOM", roomSelectButton);
    drumSelectButtonAtachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.tree,
        "BUTTON_SELECT_DRUMSET", drumSelectButton);
}

void SamplerMAudioProcessorEditor::linkParamChangeListeners()
{
    audioProcessor.tree.addParameterListener("ROOM_A", this);
    audioProcessor.tree.addParameterListener("ROOM_B", this);
    audioProcessor.tree.addParameterListener("ROOM_C", this);

    audioProcessor.tree.addParameterListener("BUTTON_SELECT_ROOM", this);
    audioProcessor.tree.addParameterListener("button_select_drumset", this);
    //audioProcessor.tree.addParameterListener("BUTTON_SELECT_SNARE", this);

}