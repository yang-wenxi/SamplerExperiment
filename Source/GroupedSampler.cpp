/*
  ==============================================================================

    GroupedSampler.cpp
    Created: 17 Mar 2022 10:51:18pm
    Author:  杨文希

  ==============================================================================
*/
#include <JuceHeader.h>
#include "GroupedSampler.h"

void GroupedSampler::prepare() {
    setMap();
    samplesFolder = juce::File::getSpecialLocation(juce::File::userHomeDirectory).getChildFile("Development").getChildFile("Samples");
    
    for(int i = 0; i < instruments.size(); i++) {
        sampleGroup.add(new SampleGroup(i));
        auto* voice = new MappedSamplerVoice(i);
        voice -> setMidiNote(instrumentToNoteMap[instruments[i]]);
        addVoice(voice);
    }
    
    MappedSamplerVoice* v = dynamic_cast<MappedSamplerVoice*> (getVoice(1));

    v = dynamic_cast<MappedSamplerVoice*> (getVoice(6));
    v->addPlaybackChannel(10);
    v->addPlaybackChannel(11);
    v->addPlaybackChannel(12);


    formatManager.registerBasicFormats();
    loadSamples("A");
}

void GroupedSampler::setMap() {

    instrumentToNoteMap["KICK"] = kick;
    instrumentToNoteMap["SNARE"] = snare;
    instrumentToNoteMap["TOM"] = tom;
    instrumentToNoteMap["OPH"] = ophat;
    instrumentToNoteMap["CLH"] = clhat;
    instrumentToNoteMap["CRASH"] = crash;
    instrumentToNoteMap["RIDE"] = ride;
    instrumentToNoteMap["CLAP"] = clap;
    instrumentToNoteMap["PERC"] = perc;
    
    for (int i = 0; i < instruments.size(); i++) {
        juce::String itr = instruments[i];
        int midiNote = instrumentToNoteMap[itr];
        noteToIndexMap[midiNote] = i;
    }
}

void GroupedSampler::addSample(juce::String instrument, juce::String fileName) {
    const juce::ScopedLock sl (lock);
    
    int midiNote = instrumentToNoteMap[instrument];
    juce::File* file = new juce::File(samplesFolder.getChildFile(instrument).getChildFile(fileName));
    fmtReader = formatManager.createReaderFor(*file);
    juce::BigInteger note;
    note.setBit(midiNote);
    sampleGroup.getObjectPointer(noteToIndexMap[midiNote]) -> addSample(new OneSample(instrument, *fmtReader, note, midiNote, 0.0f, 10.0f, 10.0f));
}

void GroupedSampler::loadSamples(juce::String rootNote) {
    for (int i = 0; i < instruments.size(); i++){
        juce::String instr = instruments[i];
        if(!sampleGroup.getObjectPointer(i) -> isGroupEmpty())
            sampleGroup.getObjectPointer(i) -> clear();
        for(int j = 1; j < 6; j++) {
            juce::String fName {instr + std::to_string(j)+ ".wav"};
            addSample(instr, fName);
        }
    }
}


void GroupedSampler::brodcastBusCondition(busConditionSender* cond) {
    for (int i = 0; i < instruments.size(); i++) {
        MappedSamplerVoice* v = dynamic_cast<MappedSamplerVoice*>(getVoice(i));
        v->receiveBusCondition(cond);
    }
}

void GroupedSampler::toggleOutputChannel(int voiceID, int chanID, bool state) {
    MappedSamplerVoice* v = dynamic_cast<MappedSamplerVoice*>(getVoice(voiceID));
    if (state)
        v->addPlaybackChannel(chanID);
    else
        v->removePlaybackChannel(chanID);
}


void GroupedSampler::noteOn(int midiChannel, int midiNoteNumber, float velocity) {
    if (isNoteMapped(midiNoteNumber)) {
        int soundIndex = noteToIndexMap[midiNoteNumber];
        DBG(midiNoteNumber);
        OneSample* sample = sampleGroup.getObjectPointer(soundIndex) -> getASample();
        auto* voice = dynamic_cast<MappedSamplerVoice*>(getVoice(soundIndex));
        if (voice -> getCurrentlyPlayingSound()) {
            stopVoice(voice, 0.0f, true);
        }
        startVoice(voice, sample, midiChannel, midiNoteNumber, velocity);
    }
}

bool GroupedSampler::isNoteMapped(int midiNoteNumber) {
    return (noteToIndexMap.find(midiNoteNumber) == noteToIndexMap.end()) ? false : true;
}



