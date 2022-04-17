/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.1.6

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "SampleSetSwitch.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SampleSetSwitch::SampleSetSwitch (juce::AudioProcessor* processor)
{
    audioProcessor = dynamic_cast<SamplerMAudioProcessor*>(processor);
    
    roomA.reset (new juce::ToggleButton ("Room A"));
    addAndMakeVisible (roomA.get());
    roomA->setRadioGroupId (1001);
    roomA->addListener (this);

    roomA->setBounds (50, 50, 100, 24);

    roomB.reset (new juce::ToggleButton ("Room B"));
    addAndMakeVisible (roomB.get());
    roomB->setRadioGroupId (1001);
    roomB->addListener (this);

    roomB->setBounds (50, 80, 100, 24);

    roomC.reset (new juce::ToggleButton ("Room C"));
    addAndMakeVisible (roomC.get());
    roomC->setRadioGroupId (1001);
    roomC->addListener (this);

    roomC->setBounds (50, 110, 100, 24);

    setSize (200, 200);
    
    roomAttachment_A = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor->tree,
                                                                                                      "ROOM_A", &roomA);
    roomAttachment_B = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor->tree,
                                                                                                      "ROOM_B", &roomB);
    roomAttachment_C = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor->tree,
                                                                                                      "ROOM_C", &roomC);
}

SampleSetSwitch::~SampleSetSwitch()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    roomA = nullptr;
    roomB = nullptr;
    roomC = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//void SampleSetSwitch::receiveTree(juce::AudioProcessorValueTreeState* tree) {
//    parentTree = tree;
//}

//==============================================================================
void SampleSetSwitch::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colours::grey);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SampleSetSwitch::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SampleSetSwitch::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == roomA.get())
    {
        //[UserButtonCode_roomA] -- add your button handler code here..
        //[/UserButtonCode_roomA]
    }
    else if (buttonThatWasClicked == roomB.get())
    {
        //[UserButtonCode_roomB] -- add your button handler code here..
        //[/UserButtonCode_roomB]
    }
    else if (buttonThatWasClicked == roomC.get())
    {
        //[UserButtonCode_roomC] -- add your button handler code here..
        //[/UserButtonCode_roomC]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SampleSetSwitch" componentName=""
                 parentClasses="public juce::Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="200" initialHeight="200">
  <BACKGROUND backgroundColour="ff808080"/>
  <TOGGLEBUTTON name="Room A" id="cf600e062c008c2a" memberName="roomA" virtualName=""
                explicitFocusOrder="0" pos="50 50 100 24" buttonText="Room A"
                connectedEdges="0" needsCallback="1" radioGroupId="1001" state="0"/>
  <TOGGLEBUTTON name="Room B" id="93ac68dfac82b749" memberName="roomB" virtualName=""
                explicitFocusOrder="0" pos="50 80 100 24" buttonText="Room B"
                connectedEdges="0" needsCallback="1" radioGroupId="1001" state="0"/>
  <TOGGLEBUTTON name="Room C" id="f1a9e5a30768e2b8" memberName="roomC" virtualName=""
                explicitFocusOrder="0" pos="50 110 100 24" buttonText="Room C"
                connectedEdges="0" needsCallback="1" radioGroupId="1001" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

