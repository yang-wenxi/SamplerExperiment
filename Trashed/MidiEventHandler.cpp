/*
  ==============================================================================

    MidiEventProcessor.cpp
    Created: 16 Apr 2022 10:16:23pm
    Author:  WdYan

  ==============================================================================
*/

#include "MidiEventHandler.h"
#include "PluginEditor.h"

void MidiEventHandler::setEditor(juce::AudioProcessorEditor* editor) {
	this->editor = editor;
}

juce::MidiBuffer MidiEventHandler::processNotes(juce::MidiBuffer& buffer) {
	juce::MidiBuffer processed;
	juce::MidiBuffer::Iterator it(buffer);
	juce::MidiMessage currentMessage;
	int samplePos;

	while (it.getNextEvent(currentMessage, samplePos)) {
		if (currentMessage.isNoteOn())
			triggerDrumhit(currentMessage.getNoteNumber());
	}
}

void MidiEventHandler::triggerDrumhit(int noteNumber) {
	SamplerMAudioProcessorEditor* sEditor = dynamic_cast<SamplerMAudioProcessorEditor*>(editor);
	switch (noteNumber)
	{
	case (60):
		sEditor->getKickButton()->triggerClick();
	case (61):
		sEditor->getSnareButton()->triggerClick();
	case (62):
		sEditor->getTomBotton()->triggerClick();
	case (66):
		sEditor->getCrashButton()->triggerClick();
	default:
		break;
	}
}
