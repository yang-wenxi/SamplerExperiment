/*
  ==============================================================================

    GlobalProperties.h
    Created: 26 Mar 2022 7:54:02pm
    Author:  杨文希

  ==============================================================================
*/

#pragma once



static int busChannelVector[16] = { };
static int busAvailable[16] = { };

static void printingThings() {
    std::string toBePrinted = "";
    for (auto item : busAvailable) {
        toBePrinted += std::to_string(item);
    }
    DBG(toBePrinted);
}
