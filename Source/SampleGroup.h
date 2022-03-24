/*
  ==============================================================================

    SampleGroup.h
    Created: 18 Mar 2022 11:37:20pm
    Author:  杨文希

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "OneSample.h"

class SampleGroup : public juce::ReferenceCountedObject
{
private:
    juce::ReferenceCountedArray<OneSample> group;
    int instrument;

public:
    SampleGroup(int instrument) {
        this -> instrument = instrument;
    }
    
    int getInstrument() {
        return instrument;
    }
    
    juce::ReferenceCountedArray<OneSample>* getGroup() {
        return &group;
    }
    
    void addSample(OneSample* sample) {
        //DBG("added" + std::to_string(instrument));
        group.add(sample);
    }
    
    int getNumSamples() {
        return group.size();
    }
    
    bool isGroupEmpty() {
        return group.isEmpty();
    }
    
    void clear() {
        group.clear();
    }
    
    OneSample* getASample() {
        juce::Random r;
        int max = getNumSamples();
        int target = r.nextInt(max);
        return group.getObjectPointer(target);
    }
};
