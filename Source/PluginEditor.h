/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "foleys_gui_magic.h"
#include "NewWindow.h"
#include "DrumSetSelectWindow.h"
#include "OutputChannelSelectWindow.h"
#include "RoomSelectWindow.h"
#include "SampleSetSwitch.h"
#include "GlobalProperties.h"


class SamplerMAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer
{
public:
    SamplerMAudioProcessorEditor (SamplerMAudioProcessor&);
    ~SamplerMAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;
    
    juce::TextButton* getPlayButton(juce::String instrumentToPlay);
    
    void setCurrentRoom(int curRoom) {
        this->currentRoom = curRoom;
    }

private:
    SamplerMAudioProcessor& audioProcessor;

    juce::TextButton playSnareButton {"SNARE"};
    juce::TextButton playCrashButton { "CRASH" };
    juce::TextButton playTomButton { "TOM" };
    juce::TextButton playKickButton { "KICK" };

    juce::Slider parameterSlider;

    juce::ToggleButton roomSelectButton{ "Select a room" };
    RoomSelectWindow roomSelectWin{ &audioProcessor };
    int currentRoom = ROOM_A;

    juce::ToggleButton drumSelectButton{ "Select a drum set" };
    DrumSetSelectWindow drumSelectWindow{ &audioProcessor };

    juce::ToggleButton outputSelectButton_Snare{ "Select Snare Output" };
    juce::ToggleButton outputSelectButton_Crash{ "Select Crash Output" };
    OutputChannelSelectWindow outputSelectWindow{ &audioProcessor };

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> parameterSliderAttachment;
    
    std::vector<juce::Colour> roomColours{ juce::Colours::grey, juce::Colours::black, juce::Colours::white };
    
    void openNewWindow(juce::ToggleButton& button, juce::String buttonData);
    void attachParameters();

    enum RadioGroups {OUTPUT_CHANNEL_SELECT = 1010};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerMAudioProcessorEditor)
};
