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
    std::string DrivenDistance;
    StopTrigger(
      bool icriteria_RunningStopTest = true,
      bool icriteria_RunningRedLightTest = true,
      bool icriteria_WrongLaneTest = true,
      bool icriteria_OnSidewalkTest = true,
      bool icriteria_KeepLaneTest = true,
      bool icriteria_CollisionTest = true,
      bool icriteria_DrivenDistanceTest = true,
      std::string iDrivenDistance = "100"
    ) {
        criteria_RunningStopTest = icriteria_RunningStopTest;
        criteria_RunningRedLightTest = icriteria_RunningRedLightTest;
        criteria_WrongLaneTest = icriteria_WrongLaneTest;
        criteria_OnSidewalkTest = icriteria_OnSidewalkTest;
        criteria_KeepLaneTest = icriteria_KeepLaneTest;
        criteria_CollisionTest = icriteria_CollisionTest;
        criteria_DrivenDistanceTest = icriteria_DrivenDistanceTest;
        DrivenDistance = iDrivenDistance;
    };
};

#endif