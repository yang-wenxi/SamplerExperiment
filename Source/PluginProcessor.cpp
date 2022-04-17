/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "GlobalProperties.h"

//==============================================================================
SamplerMAudioProcessor::SamplerMAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput("OutputL0", juce::AudioChannelSet::stereo(), true)
                       .withOutput("OutputL1", juce::AudioChannelSet::stereo(), true)
                       .withOutput("OutputL2", juce::AudioChannelSet::stereo(), true)
                       .withOutput("OutputL3", juce::AudioChannelSet::stereo(), true)
                       .withOutput("OutputL4", juce::AudioChannelSet::stereo(), true)
                       .withOutput("OutputL5", juce::AudioChannelSet::stereo(), true)
                       .withOutput("OutputL6", juce::AudioChannelSet::stereo(), true)
                       .withOutput("OutputL7", juce::AudioChannelSet::stereo(), true)
                       .withOutput("OutputL8", juce::AudioChannelSet::stereo(), true)
                       .withOutput("OutputL9", juce::AudioChannelSet::stereo(), true)
                       .withOutput("OutputL10", juce::AudioChannelSet::stereo(), true)
                       .withOutput("OutputL11", juce::AudioChannelSet::stereo(), true)
                       .withOutput("OutputL12", juce::AudioChannelSet::stereo(), true)
                       .withOutput("OutputL13", juce::AudioChannelSet::stereo(), true)
                       .withOutput("OutputL14", juce::AudioChannelSet::stereo(), true)
                       .withOutput("OutputL15", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), tree(*this, nullptr, "ParamListTree", createParams())
 #endif
{
    gSampler.prepare();
    addParamListener();
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

    return true;
}
#endif

void SamplerMAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    juce::MidiBuffer processedMessages = midiHandler(midiMessages);
    gSampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

juce::MidiBuffer SamplerMAudioProcessor::midiHandler(juce::MidiBuffer messages) {
    SamplerMAudioProcessorEditor* editor = dynamic_cast<SamplerMAudioProcessorEditor*>(getActiveEditor());
    juce::MidiBuffer processedMsg;
    juce::MidiMessage currentMsg;
    
    for (auto msg : messages) {
        currentMsg = msg.getMessage();
        int noteNumber = currentMsg.getNoteNumber();
        int samplePos = currentMsg.getTimeStamp();
        
        if (currentMsg.isNoteOn()) {
            switch (noteNumber) {
            case (60):
                editor->getKickButton()->triggerClick();
                break;
            case (61):
                editor->getSnareButton()->triggerClick();
                break;
            case (62):
                editor->getTomBotton()->triggerClick();
                break;
            case (66):
                editor->getCrashButton()->triggerClick();
                break;
            default:
                break;
            }
        }
    }
    
    return processedMsg;
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
    juce::String visualStudio = "a piece of fucking shit";
    gSampler.brodcastBusCondition(&conditionSender);
}

void SamplerMAudioProcessor::playSample(juce::String instrument) {
    int noteNum = gSampler.getInstrumentMidi(instrument);
    gSampler.noteOn(1, noteNum, 1.0f);
}

juce::AudioProcessorValueTreeState::ParameterLayout SamplerMAudioProcessor::createParams() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> paramVec;
    paramVec.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN", "Gain", 0.0f, 1.0f, 0.65f));
    paramVec.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK_ADSR", "Attack", 0.0f, 1.0f, 0.27f));
    paramVec.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY_ADSR", "Decay", 0.0f, 1.0f, 0.45f));
    paramVec.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN_ADSR", "Sustain", 0.0f, 1.0f, 0.45f));
    paramVec.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE_ADSR", "Release", 0.0f, 20000.0f, 455.5f));
    
    paramVec.push_back(std::make_unique<juce::AudioParameterBool>("ROOM_A", "room A", true));
    paramVec.push_back(std::make_unique<juce::AudioParameterBool>("ROOM_B", "room B", false));
    paramVec.push_back(std::make_unique<juce::AudioParameterBool>("ROOM_C", "room C", false));
    
    juce::StringArray instrumentsSet {"KICK", "SNARE", "TOM", "OPH", "CLH", "RIDE", "CRASH", "CLAP", "PERC"};
    
    //Channel Control
    for (int i = 0; i < instrumentsSet.size(); i++) {
        juce::String instrument = instrumentsSet[i];
//        paramVec.push_back(std::make_unique<juce::AudioParameterBool>(instrument + "_BUTTON", instrument.toLowerCase(), false));
        channelControl(instrument, &paramVec);
    }

    return {paramVec.begin(), paramVec.end()};
}

void SamplerMAudioProcessor::channelControl(juce::String instrument, std::vector<std::unique_ptr<juce::RangedAudioParameter>> *paramVec) {
    for (int i = 1; i <= 6; i++) {
        juce::String pID = instrument + "_CHANNEL+" + std::to_string(i);
        juce::String pName = instrument.toLowerCase() + " channel " + std::to_string(i);
        paramVec -> push_back(std::make_unique<juce::AudioParameterBool>(pID, pName, false));
    }
}

void SamplerMAudioProcessor::addParamListener() {
    int sampleSetSize = gSampler.getNumSampleSet();
    for (int i = 0; i < sampleSetSize; i++) {
        if (auto* v = dynamic_cast<MappedSamplerVoice*>(gSampler.getVoice(i))) {
            juce::String instrument = v->getInstrument();
            tree.addParameterListener("GAIN", v);
            for (int chn = 1; chn <= 6; chn++) {
                tree.addParameterListener(instrument + "_CHANNEL+" + std::to_string(chn), v);
            }
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SamplerMAudioProcessor();
}
