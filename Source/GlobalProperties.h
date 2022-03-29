/*
  ==============================================================================

    GlobalProperties.h
    Created: 26 Mar 2022 7:54:02pm
    Author:  杨文希

  ==============================================================================
*/

#pragma once

class busConditionSender {
public:
    busConditionSender() {
        busAvailable[0] = 1;
    }

    int busChannelVec[16] = { };
    int busAvailable[16] = { };
};