/*
  ==============================================================================

    SampleBundle.h
    Created: 6 Apr 2022 12:21:55pm
    Author:  WdYan

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "OneSample.h"

class SampleBundle
{
public:
	SampleBundle(int instrument);
	~SampleBundle();

    std::vector<OneSample>* getBundle() {
        return &sampleBundle;
    }

    int getInstrument() {
        return instrument;
    }

    void addSample(OneSample* sample) {
        sampleBundle.push_back(*sample);
    }

    int getNumSamples() {
        return sampleBundle.size();
    }

    bool isEmpty() {
        return sampleBundle.empty();
    }

    void clearBundle() {
        sampleBundle.clear();
    }

    OneSample* getASamplePtr() {
        int max = sampleBundle.size();
        int target = rand.nextInt(max);
        return &sampleBundle[target];
    }

    OneSample getASample() {
        int max = sampleBundle.size();
        int target = rand.nextInt(max);
        return sampleBundle[target];
    }

private:
    int instrument;
    std::vector<OneSample> sampleBundle;
    juce::Random rand;
};

SampleBundle::SampleBundle(int instrument)
{
    this->instrument = instrument;
}

SampleBundle::~SampleBundle()
{
}