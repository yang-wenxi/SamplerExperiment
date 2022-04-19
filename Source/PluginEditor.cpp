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
    DBG("++++++ editor");
    Timer::startTimerHz(30);

    playSnareButton.onClick = [&]() {audioProcessor.playSample("SNARE");};
    playCrashButton.onClick = [&]() {audioProcessor.playSample("CRASH");};
    playTomButton.onClick = [&]() {audioProcessor.playSample("TOM");};
    playKickButton.onClick = [&]() {audioProcessor.playSample("KICK");};
    
    outputSelectButton_Crash.onClick = [this]() {openNewWindow(outputSelectButton_Crash, "outputSelect+crash"); };
    outputSelectButton_Snare.onClick = [this]() {openNewWindow(outputSelectButton_Snare, "outputSelect+snare"); };
    roomSelectButton.onClick = [this]() {openNewWindow(roomSelectButton, "roomSelect"); };
    
    parameterSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    parameterSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 50);

    playSnareButton.setBounds(20, 20, 180, 180);
    playCrashButton.setBounds(220, 20, 180, 180);
    playTomButton.setBounds(20, 220, 180, 180);
    playKickButton.setBounds(220, 220, 180, 180);


    parameterSlider.setBounds(420, 260, 100, 100);

    roomSelectButton.setBounds(550, 100, 100, 40);
    outputSelectButton_Snare.setBounds(550, 150, 100, 40);
    outputSelectButton_Crash.setBounds(550, 200, 100, 40);
    drumSelectButton.setBounds(550, 250, 100, 40);

    

    
    
    addAndMakeVisible(parameterSlider);
    addAndMakeVisible(roomSelectButton);
    addAndMakeVisible(outputSelectButton_Snare);
    addAndMakeVisible(outputSelectButton_Crash);
    addAndMakeVisible(drumSelectButton);

    addAndMakeVisible(playSnareButton);
    addAndMakeVisible(playCrashButton);
    addAndMakeVisible(playTomButton);
    addAndMakeVisible(playKickButton);

    //outputSelectButton_Crash.setRadioGroupId(OUTPUT_CHANNEL_SELECT);
    //outputSelectButton_Snare.setRadioGroupId(OUTPUT_CHANNEL_SELECT);
    //outputNotShowButton.setRadioGroupId(OUTPUT_CHANNEL_SELECT);
    
    setSize (705, 700);

    attachParameters();
    linkParamChangeListeners();
}

SamplerMAudioProcessorEditor::~SamplerMAudioProcessorEditor()
{
    Timer::stopTimer();
    DBG("aaaa------------ editor");
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

    if (buttonData.contains("outputSelect")) {
        int instrumentIndex = buttonData.indexOfChar('+') + 1;
        juce::String instrumentName = buttonData.substring(instrumentIndex, buttonData.length()).toLowerCase();
        if (isToggled) {
            if (instrumentName != "snare")
                outputSelectButton_Snare.setToggleState(false, juce::NotificationType::dontSendNotification);
            if (instrumentName != "crash")
                outputSelectButton_Crash.setToggleState(false, juce::NotificationType::dontSendNotification);
            
            outputSelectWindow.instrumentToSelect(instrumentName);
            addAndMakeVisible(outputSelectWindow);
        }
        else
            removeChildComponent(&outputSelectWindow);
    }
    
    if (buttonData == "roomSelect") {
        if (isToggled) addAndMakeVisible(roomSelectWin);
        else removeChildComponent(&roomSelectWin);
    }
}


void SamplerMAudioProcessorEditor::parameterChanged(const juce::String &parameterID, float newValue) {
    if (parameterID.contains("ROOM")) {
        DBG("ppppaaaarameeeterrr channawefgjiaw");
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
}

void SamplerMAudioProcessorEditor::attachParameters()
{
    parameterSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.tree,
        "GAIN", parameterSlider);
}

void SamplerMAudioProcessorEditor::linkParamChangeListeners()
{
    DBG("listener add");
    audioProcessor.tree.addParameterListener("ROOM_A", this);
    audioProcessor.tree.addParameterListener("ROOM_B", this);
    audioProcessor.tree.addParameterListener("ROOM_C", this);
}

juce::TextButton* SamplerMAudioProcessorEditor::getPlayButton(juce::String instrumentToPlay) {
    if (instrumentToPlay == "kick") {
        return &playKickButton;
    }
    if (instrumentToPlay == "snare") {
        return &playSnareButton;
    }
    if (instrumentToPlay == "tom") {
        return &playTomButton;
    }
    if (instrumentToPlay == "crash") {
        return &playCrashButton;
    }
    return nullptr;
}
