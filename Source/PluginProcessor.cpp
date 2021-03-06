/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SamplerMAudioProcessor::SamplerMAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput("OutputL", juce::AudioChannelSet::mono(), true)
                       .withOutput("OutputL2", juce::AudioChannelSet::mono(), true)
                       .withOutput("OutputL3", juce::AudioChannelSet::mono(), true)
                       .withOutput("OutputL4", juce::AudioChannelSet::mono(), true)
                       .withOutput("OutputL5", juce::AudioChannelSet::mono(), true)
                       .withOutput("OutputL6", juce::AudioChannelSet::mono(), true)
                       .withOutput("OutputL7", juce::AudioChannelSet::mono(), true)
                       .withOutput("OutputL8", juce::AudioChannelSet::mono(), true)
                       .withOutput("OutputL9", juce::AudioChannelSet::mono(), true)
                       .withOutput("OutputL10", juce::AudioChannelSet::mono(), true)
                       .withOutput("OutputL11", juce::AudioChannelSet::mono(), true)
                       .withOutput("OutputL12", juce::AudioChannelSet::mono(), true)
                       .withOutput("OutputL13", juce::AudioChannelSet::mono(), true)
                       .withOutput("OutputL14", juce::AudioChannelSet::mono(), true)
                       .withOutput("OutputL15", juce::AudioChannelSet::mono(), true)
                       .withOutput("OutputL16", juce::AudioChannelSet::mono(), true)
                     #endif
                       ), tree(*this, nullptr, "ParamList", createParams())
 #endif
{
    gSampler.prepare();
    busLayoutCondition.clear();
}

SamplerMAudioProcessor::~SamplerMAudioProcessor()
{
}

//==============================================================================
const juce::String SamplerMAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SamplerMAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SamplerMAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SamplerMAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SamplerMAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SamplerMAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SamplerMAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SamplerMAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SamplerMAudioProcessor::getProgramName (int index)
{
    return {};
}

void SamplerMAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SamplerMAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    gSampler.setCurrentPlaybackSampleRate(sampleRate);
}

void SamplerMAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SamplerMAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    /*
    for (int m = 0; m < 16; m++) {
        //busChannelVector[m] = 0;
        busAvailable[m] = 0;
    }
     
    
    DBG("-----------------------------------------------------------");
    int openedChannels = 0;;
    for (int i = 0; i < 16; i++) {
        if (layouts.getChannelSet(false, i) != juce::AudioChannelSet::disabled()) {
            busAvailable[i] = 1;
            busChannelVector[i] = openedChannels;
            openedChannels++;
            DBG("bus " + std::to_string(i) + " avail");
>>>>>>> Stashed changes
        }
        
        else {
            busAvailable[i] = 0;
<<<<<<< Updated upstream
            busChannelVec[i] = openedChannels;
        }
    }
=======
            busChannelVector[i] = openedChannels;
        
    }
    
    
    DBG("---------------------------------------------------------------------------");
    DBG("busAvailable");
    juce::String baS = "";
    for (auto ba : busAvailable) {
        baS = baS + (std::to_string(ba) + "     ");
    }
    DBG(baS);
    
    DBG("busChannelVec");
    juce::String bcV = "";
    for (auto bc : busChannelVector) {
        bcV = bcV + (std::to_string(bc) + "     ");
    }
    DBG(bcV);
    */
    return true;
}
#endif

void SamplerMAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    

    gSampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool SamplerMAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SamplerMAudioProcessor::createEditor()
{
    return new SamplerMAudioProcessorEditor (*this);
}

//==============================================================================
void SamplerMAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SamplerMAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void SamplerMAudioProcessor::playSample(int noteNum) {
    MappedSamplerVoice* mVoice = dynamic_cast<MappedSamplerVoice*>(gSampler.getVoice(1));
    mVoice -> addPlaybackChannel(5);
    
    gSampler.noteOn(1, noteNum, 1.0f);
}

void SamplerMAudioProcessor::playMultiple(int one, int two) {
    playSample(one);
    playSample(two);
}

juce::AudioProcessorValueTreeState::ParameterLayout SamplerMAudioProcessor::createParams() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> paramVec;
    paramVec.push_back(std::make_unique<juce::AudioParameterFloat>("FORCE_1", "Force", 0.0f, 1.0f, 0.27f));
    return {paramVec.begin(), paramVec.end()};
}

void SamplerMAudioProcessor::updateToggleState(juce::Button* button, juce::String name) {
    auto state = button->getToggleState();
    gSampler.toggleOutputChannel(1, std::stoi(name.toStdString()), state);
}

void SamplerMAudioProcessor::numChannelsChanged() {
    int numChannelTurnedOn = 0;
    for (int i = 0; i < 16; i++) {
        Bus* b = getBus(false, i);
        if (b->getCurrentLayout() != juce::AudioChannelSet::disabled()) {
            conditionSender.busAvailable[i] = 1;
            conditionSender.busChannelVec[i] = numChannelTurnedOn;
            numChannelTurnedOn++;
        }
        else {
            conditionSender.busAvailable[i] = 0;
            conditionSender.busChannelVec[i] = numChannelTurnedOn;
        }
    }
    gSampler.brodcastBusCondition(&conditionSender);
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SamplerMAudioProcessor();
}
