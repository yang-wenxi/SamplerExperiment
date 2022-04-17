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
SampleSetSwitch::SampleSetSwitch ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    roomC.reset (new juce::TextButton ("Room C"));
    addAndMakeVisible (roomC.get());
    roomC->setRadioGroupId (1001);
    roomC->setColour (juce::TextButton::buttonColourId, juce::Colours::white);

    roomC->setBounds (50, 150, 100, 24);

    roomB.reset (new juce::TextButton ("Room B"));
    addAndMakeVisible (roomB.get());
    roomB->setRadioGroupId (1001);
    roomB->setColour (juce::TextButton::buttonColourId, juce::Colours::white);

    roomB->setBounds (50, 100, 100, 24);

    roomA.reset (new juce::TextButton ("Room A"));
    addAndMakeVisible (roomA.get());
    roomA->setRadioGroupId (1001);
    roomA->setColour (juce::TextButton::buttonColourId, juce::Colours::white);

    roomA->setBounds (50, 50, 100, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (200, 200);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

SampleSetSwitch::~SampleSetSwitch()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    roomC = nullptr;
    roomB = nullptr;
    roomA = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

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
  <TEXTBUTTON name="Room C" id="486c3f9de0419895" memberName="roomC" virtualName=""
              explicitFocusOrder="0" pos="50 150 100 24" bgColOff="ffffffff"
              buttonText="Room C" connectedEdges="0" needsCallback="0" radioGroupId="1001"/>
  <TEXTBUTTON name="Room B" id="8899a207c5597c6c" memberName="roomB" virtualName=""
              explicitFocusOrder="0" pos="50 100 100 24" bgColOff="ffffffff"
              buttonText="Room B" connectedEdges="0" needsCallback="0" radioGroupId="1001"/>
  <TEXTBUTTON name="Room A" id="9c4f085414802b21" memberName="roomA" virtualName=""
              explicitFocusOrder="0" pos="50 50 100 24" bgColOff="ffffffff"
              buttonText="Room A" connectedEdges="0" needsCallback="0" radioGroupId="1001"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

