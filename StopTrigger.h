#ifndef _STOPTRIGGER_
#define _STOPTRIGGER_

#include "common.h"

struct StopTrigger {
    bool criteria_RunningStopTest;
    bool criteria_RunningRedLightTest;
    bool criteria_WrongLaneTest;
    bool criteria_OnSidewalkTest;
    bool criteria_KeepLaneTest;
    bool criteria_CollisionTest;
    bool criteria_DrivenDistanceTest;
    const char *DrivenDistance;
    StopTrigger() {
        criteria_RunningStopTest = true;
        criteria_RunningRedLightTest = true;
        criteria_WrongLaneTest = true;
        criteria_OnSidewalkTest = true;
        criteria_KeepLaneTest = true;
        criteria_CollisionTest = true;
        criteria_DrivenDistanceTest = true;
        DrivenDistance = "100";
    };
};

#endif