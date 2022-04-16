/*
  ==============================================================================

    MidiEventProcessor.h
    Created: 16 Apr 2022 10:16:23pm
    Author:  WdYan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginEditor.h"

class MidiEventHandler {
public:
    void setEditor(juce::AudioProcessorEditor* editor);
    juce::MidiBuffer processNotes(juce::MidiBuffer& buffer);
    void triggerDrumhit(int noteNumber);

private:
    juce::AudioProcessorEditor* editor;
};