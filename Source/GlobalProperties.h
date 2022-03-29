/*
  ==============================================================================

    GlobalProperties.h
    Created: 26 Mar 2022 6:56:38pm
    Author:  杨文希

  ==============================================================================
*/

#pragma once

static int busChannelVector[16] = {};
static int busAvailable[16] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

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