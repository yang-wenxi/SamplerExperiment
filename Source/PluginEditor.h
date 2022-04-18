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


class SamplerMAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::AudioProcessorValueTreeState::Listener, public juce::Timer
{
public:
    SamplerMAudioProcessorEditor (SamplerMAudioProcessor&);
    ~SamplerMAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;
    
    juce::TextButton* getSnareButton() {
        return &playSnareButton;
    }
    
    juce::TextButton* getCrashButton() {
        return &playCrashButton;
    }
    
    juce::TextButton* getTomBotton() {
        return &playTomButton;
    }
    
    juce::TextButton* getKickButton() {
        return &playKickButton;
    }

    void parameterChanged(const juce::String &parameterID, float newValue) override;

private:
    SamplerMAudioProcessor& audioProcessor;

    juce::TextButton playSnareButton {"SNARE"};
    juce::TextButton playCrashButton { "CRASH" };
    juce::TextButton playTomButton { "TOM" };
    juce::TextButton playKickButton { "KICK" };
//    juce::TextButton playSnareAndCrashButton { "S C" };

    juce::ToggleButton openNewWindowButton{ "Open new window" };

    //std::vector<juce::ToggleButton> snareChannelControl;
    //std::vector<juce::ToggleButton> crashChannelControl;
    
    juce::Slider parameterSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> parameterSliderAttachment;
    
    std::vector<juce::Colour> roomColours{ juce::Colours::grey, juce::Colours::black, juce::Colours::white };

    juce::ToggleButton roomSelectButton{ "Select a room" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> roomSelectButtonAtachment;
    RoomSelectWindow roomSelectWin{ &audioProcessor };
    int currentRoom = ROOM_A;
    enum ROOM {ROOM_A = 0, ROOM_B = 1, ROOM_C = 2};

    juce::ToggleButton drumSelectButton{ "Select a drum set" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> drumSelectButtonAtachment;
    DrumSetSelectWindow drumSelectWindow{ &audioProcessor };

    juce::ToggleButton outputSelectButton_Snare{ "Select Snare Output" };
    juce::ToggleButton outputSelectButton_Crash{ "Select Crash Output" };
    OutputChannelSelectWindow outputSelectWindow{ &audioProcessor };

    NewWindow window_1;
    void openNewWindow(juce::ToggleButton& button, juce::String buttonData);

    void attachParameters();
    void linkParamChangeListeners();

    enum RadioGroups {OUTPUT_CHANNEL_SELECT = 1010};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SamplerMAudioProcessorEditor)
};
