/*
  ==============================================================================

    GlobalProperties.h
    Created: 26 Mar 2022 7:54:02pm
    Author:  杨文希

  ==============================================================================
*/

#pragma once


/*
static int busChannelVector[16] = { };
static int busAvailable[16] = { };

static void printingThings() {
    std::string toBePrinted = "";
    for (auto item : busAvailable) {
        toBePrinted += std::to_string(item);
    }
    DBG(toBePrinted);
}
*/

class busConditionSender {
public:
    busConditionSender() {
        busAvailable[0] = 1;
    }

    void printVecInfo() {
        DBG("--------------------");
        std::string v = "";
        for (auto a : busChannelVec) {
            v += (std::to_string(a) + " ");
        }
        DBG(v);
    }

    void printAvail() {
        DBG("--------------------");
        std::string v = "";
        for (auto a : busAvailable) {
            v += (std::to_string(a) + " ");
        }
        DBG(v);
    }

    int busChannelVec[16] = { };
    int busAvailable[16] = { };
};