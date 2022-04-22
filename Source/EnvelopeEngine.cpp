/*
  ==============================================================================

    EnvelopeEngine.cpp
    Created: 17 Mar 2022 12:36:04pm
    Author:  杨文希

  ==============================================================================
*/

#include <JuceHeader.h>
#include "EnvelopeEngine.h"

EnvelopeEngine::EnvelopeEngine (void) {
    sampleRate = 48000;
    attackTime = 0;
    decayTime = 0;
    releaseTime = 100000;
    sustainLevel = 1.0;
    envOutput = 0.0;
    incValueShutdown = 0.0;
    
    shutdownTime = 10.0;
    
    envelopeState = off;
    isControllingDCA = true;
    envelopeMode = digital;
    setEEMode(envelopeMode);
    resetToZeroMode = true;
    legatoMode = false;
}

void EnvelopeEngine::setEEMode(int envelopeMode) {
    this -> envelopeMode = envelopeMode;
    
    if (envelopeMode == analog) {
        attackTCO = exp(-1.5);
        decayTCO = exp(-4.95);
        releaseTCO = decayTCO;
    }
    else {
        attackTCO = 0.99999;
        decayTCO = exp(-11.05);
        releaseTCO = decayTCO;
    }
    calculateAttack();
    calculateDecay();
    calculateRelease();
}

void EnvelopeEngine::reset() {
    envelopeState = off;
    setEEMode(envelopeMode);
    calculateRelease();
    if (resetToZeroMode) {
        envOutput = 0.0;
    }
}

void EnvelopeEngine::calculateAttack() {
    double samples = sampleRate * (attackTime / 1000);
    
    attackMultiplier = exp(-log((1.0 + attackTCO) / attackTCO) / samples);
    attackOffset = (1.0 + attackTCO) * (1.0 - attackMultiplier);
}

void EnvelopeEngine::calculateDecay() {
    double samples = sampleRate * (decayTime / 1000);
    
    decayMultiplier = exp(-log((1.0 + decayTime) / decayTCO) / samples);
    decayOffset = (sustainLevel - decayTCO) * (1.0 - decayMultiplier);
}

void EnvelopeEngine::calculateRelease() {
    double samples = sampleRate * (releaseTime / 1000);
    
    releaseMultiplier = exp(-log((1.0 + releaseTCO) / releaseTCO) / samples);
    releaseOffset = -releaseTCO * (1.0 - releaseMultiplier);
}

void EnvelopeEngine::noteOff() {
    if (envOutput > 0.0) {
        envelopeState = release;
    }
    else
        envelopeState = off;
}

void EnvelopeEngine::shutDown() {
    if (legatoMode){
        return;
    }
    incValueShutdown = -(1000.0 * envOutput) / shutdownTime / releaseTime;
    envelopeState = shutdown;
}

inline juce::AudioBuffer<float> EnvelopeEngine::applyTo(juce::AudioBuffer<float> &buffer) {
    int numerOfSamples = buffer.getNumSamples();
    int currentSample = 0;
    float* writePointerL = buffer.getWritePointer(0, 0);
    float* writePointerL = buffer.getWritePointer(1, 0);
    while (++currentSample < numerOfSamples) {
        
    }
}
