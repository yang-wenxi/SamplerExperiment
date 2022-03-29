/*
  ==============================================================================

    EnvelopeEngine.h
    Created: 17 Mar 2022 12:36:04pm
    Author:  杨文希

  ==============================================================================
*/

#pragma once



#define EE_DEFAULT_STATE_TIME 1000
#include <cmath>


class EnvelopeEngine
{
public:
    EnvelopeEngine(void);
    
    int envelopeMode;
    enum { digital, analog };
    
    bool isControllingDCA;
    bool legatoMode;
    bool resetToZeroMode;
    
    void setEEMode(int envelopeMode);
    
    void calculateAttack();
    void calculateDecay();
    void calculateRelease();
    
    double getAttackTime() {
        return attackTime;
    }
    double getDecayTime() {
        return decayTime;
    }
    double getSustainLevel() {
        return sustainLevel;
    }
    double getReleaseTime() {
        return releaseTime;
    }
    
    inline int getState() {
        return envelopeState;
    }
    
    inline int getEnvOutput() {
        return envOutput;
    }
    
    inline bool isActive() {
        if (envelopeState != release && envelopeState != off)
            return true;
        return false;
    }
    
    inline bool noteOffOk() {
        if (envelopeState != release && envelopeState != off && envelopeState != shutdown)
            return true;
        return false;
    }
    
    void noteOff();
    
    void shutDown();
    
    void reset();
    
    inline void setSampleRate(double sampleRate) {
        this -> sampleRate = sampleRate;
    }
    
    inline void setAttackTimeInMilliSecond(double attackTime) {
        this -> attackTime = attackTime;
        calculateAttack();
    }
    
    inline void setDecayTimeInMilliSecond(double decayTime) {
        this -> decayTime = decayTime;
        calculateDecay();
    }
    
    inline void setReleaseTimeInMilliSecond(double releaseTime) {
        this -> releaseTime = releaseTime;
        calculateRelease();
    }
    
    inline void setSustainLevel(double sustained) {
        this -> sustainLevel = sustained;
        calculateDecay();
        
        if (envelopeState != release) {
            calculateRelease();
        }
    }
    
    inline void turnOn() {
        if (legatoMode && envelopeState != off && envelopeState != release) {
            return;
        }
        
        reset();
        envelopeState = attack;
    }
    
    inline void EETurnOff() {
        envelopeState = off;
    }
    
    inline double applyTo(double sample, double* biasedOutput = nullptr) {
        switch (envelopeState) {
            case off:
            {
                if (resetToZeroMode)
                    envOutput = 0.0;
                break;
            }
            case attack:
            {
                envOutput = attackOffset + envOutput * attackMultiplier;
                if (envOutput >= 1 || attackTime < 0.0) {
                    envOutput = 1.0;
                    envelopeState = decay;
                    break;
                }
                break;
            }
            case decay:
            {
                envOutput = decayOffset + envOutput * decayMultiplier;
                if (envOutput <= sustainLevel || decayTime < 0.0) {
                    envOutput = sustainLevel;
                    envelopeState = sustain;
                    break;
                }
                break;
            }
            case sustain:
                envOutput = sustainLevel;
                break;
            case release:
            {
                envOutput = releaseOffset + envOutput * releaseMultiplier;
                if (envOutput <= 0.0 || releaseTime <= 0.0) {
                    envOutput = 0.0;
                    envelopeState = off;
                    break;
                }
                break;
            }
            case shutdown:
            {
                if (resetToZeroMode) {
                    envOutput += incValueShutdown;
                    if (envOutput <= 0.0) {
                        envOutput = 0.0;
                        envelopeState = off;
                        break;
                    }
                }
                else {
                    envelopeState = off;
                }
                break;
            }
        }
        
        if (biasedOutput) {
            *biasedOutput = envOutput - sustainLevel;
        }
        
        return envOutput * sample;
    }
    
    
    
protected:
    double sampleRate;
    
    float envOutput;
    
    double attackOffset;
    double attackTCO;
    double attackMultiplier;
    double attackTime;
    
    double decayOffset;
    double decayTCO;
    double decayMultiplier;
    double decayTime;
    
    double releaseOffset;
    double releaseTCO;
    double releaseMultiplier;
    double releaseTime;
    
    double sustainLevel;
    
    double shutdownTime;
    
    double incValueShutdown;
    
    int envelopeState;
    enum { off, attack, decay, sustain, release, shutdown };
};
