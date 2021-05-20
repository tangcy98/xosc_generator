#ifndef _STORY_
#define _STORY_

#include "common.h"
#include "Position.h"
#include "Environment.h"

using namespace std;

enum ActionType {
    ENVIRONMENTACTION,
    ENTITYACTION,           ///< unsupported
    PARAMETERACTION,        ///< unsupported
    INFRASTRUCTUREACTION,   ///< unsupported
    TRAFFICACTION,          ///< unsupported
    LONGITUDINALACTION,
    LATERALACTION,
    SYNCHRONIZEACTION,
    ROUTINGACTION,

    USERDEFINEDACTION,  ///< unsupported
};

/** GLOBALACTION **/
/**
  * Sets the weather state, road conditions, and time of the day.
  */
struct EnvironmentAction {
    Environment environment;
};
/** 
  * Unsupported
  * Removing or adding entities.
  */
struct EntityAction {};
/**
  * Unsupported
  * Setting/modifying values of parameters.
  */
struct ParameterAction {};
/**
  * Unsupported
  * Setting/modifying traffic signals.
  */
struct InfrastructureAction {};
/** 
  * Unsupported
  * Populating ambient traffic.
  */
struct TrafficAction {};




/** PRIVATEACTION **/
/**
  * Applies longitudinal control behavior on the reference entity/entities. Either a SpeedAction or a LongitudinalDistanceAction.
  */
struct LongitudinalAction {
    const char *dynamicsShape;
    const char *dynamicsvalue;
    const char *dynamicsDimension;
    const char *targetvalue;
};

/**
  * Applies lateral control behavior on the reference entity/entities. Either a LaneChangeAction, LaneOffsetAction or a LateralDistanceAction.
  */
struct LateralAction {
    const char *dynamicsShape;
    const char *dynamicsvalue;
    const char *dynamicsDimension;
    const char *targetentityRef;
    const char *targetvalue;
};

/**
  * Unsupported
  * Sets visibility attributes on the reference entity/entities.
  */
struct VisibilityAction{};
/**
  * Synchronizes the reference entity/entities with a master entity. A target position is provided for the entity and for the master entity to be reached at the same time.
  */
struct SynchronizeAction {
    const char *masterEntityRef;
    Position targetPositionMaster;
    Position targetPosition;
    const char *relativeSpeedToMasterValue;
    const char *speedTargetValueType;
};
/**
  * Unsupported
  * Activates/ deactivates a controller on the reference entity/entities.
  */
struct ActivateControllerAction{};
/** 
  * Unsupported
  * Assigns a controller to the reference entity/entities.
  */
struct ControllerAction{};
/**
  * Unsupported
  * Assigns a position to the reference entity/entities.
  */
struct TeleportAction{};
/**
  * Applies an AssignRouteAction, a FollowTrajectoryAction or an AcquirePositionAction to the reference entity/entities.
  * Now only AcquirePositionAction is supported
  */
struct RoutingAction {
    Position position;
};


struct Action {
    const char *name;
    ActionType actionType;
    EnvironmentAction environmentAction;
    LongitudinalAction longitudinalAction;
    LateralAction lateralAction;
    SynchronizeAction synchronizeAction;
    RoutingAction routingAction;
};


enum ConditionType {
    /** ByValueCondition **/
    PARAMETERCONDITION,
    TIMEOFDAYCONDITION,                 // unsupported
    SIMULATIONTIMECONDITION,
    STORYBOARDELEMENTSTATECONDITION,
    USERDEFINEDVALUECONDITION,          // unsupported
    TRAFFICSIGNALCONDITION,             // unsupported
    TRAFFICSIGNALCONTROLLERCONDITION,   // unsupported

    /** ByEntityCondition **/
    ENDOFROADCONDITION,                 // unsupported
    COLLISIONCONDITION,                 // unsupported
    OFFROADCONDITION,                   // unsupported
    TIMEHEADWAYCONDITION,               // unsupported
    TIMETOCOLLISIONCONDITION,           // unsupported
    ACCELERATIONCONDITION,              // unsupported
    STANDSTILLCONDITION,
    SPEEDCONDITION,                     // unsupported
    RELATIVESPEEDCONDITION,             // unsupported
    TRAVELEDDISTANCECONDITION,
    REACHPOSITIONCONDITION,
    DISTANCECONDITION,                  // unsupported
    RELATIVEDISTANCECONDITION,
};

/**
  * A current parameter value is compared to a reference value.
  */
struct ParameterCondition {
    const char *parameterRef;
    const char *value;
    const char *rule;
};
/**
  * Unsupported
  * The current time of day is compared to a reference value.
  */
struct TimeOfDayCondition {

};
/**
  * The current simulation time is compared to a reference value.
  */
struct SimulationTimeCondition {
    const char *value;
    const char *rule;
};
/**
  * Condition becomes true if the referenced StoryboardElement terminates according to the given rule.
  */
struct StoryboardElementStateCondition {
    const char *storyboardElementType;
    const char *storyboardElementRef;
    const char *state;

};
/**
  * Unsupported
  * The current value of an externally defined named value is compared to a reference value (less, greater, equal).zz
  */
struct UserDefinedValueCondition {

};
/**
  * Unsupported
  * Condition becomes true if the referenced signal reaches the indicated state.
  */
struct TrafficSignalCondition {

};
/**
  * Unsupported
  * Condition becomes true if the referenced signal controller reaches the indicated state.
  */
struct TrafficSignalControllerCondition {

};
/**
  * Unsupported
  * Condition checking for how long the reference entity has reached the end of the road.
  */
struct EndOfRoadCondition {

};
/**
  * Unsupported
  * Condition checking whether the reference entity was involved in a collision.
  */
struct CollisionCondition {

};
/**
  * Unsupported
  * Condition checking for how long the reference entity has left the road.
  */
struct OffroadCondition {

};
/**
  * Unsupported
  * Condition checking the time headway between two entities.
  */
struct TimeHeadwayCondition {

};
/**
  * Unsupported
  * Condition checking the time to collision between two entities.
  */
struct TimeToCollisionCondition {

};
/**
  * Unsupported
  * Condition checking the current acceleration of an entity.
  */
struct AccelerationCondition {

};
/**
  * Condition checking for how long the reference entity has not moved.
  */
struct StandStillCondition {
    const char *duration;
};
/**
  * Unsupported
  * Condition checking the current speed of the referenced entities.
  */
struct SpeedCondition {

};
/**
  * Unsupported
  * Condition checking the relative speed between two entity.
  */
struct RelativeSpeedCondition {

};
/**
  * Condition checking the total traveled distance of the reference entity since the start of the scenario.
  */
struct TraveledDistanceCondition {
    const char *value;
};
/**
  * Condition checking whether the reference entity has reached a given position within a given uncertainty.
  */
struct ReachPositionCondition {
    const char *tolerance;
    Position position;
};
/**
  * Unsupported
  * Condition checking the distance between two entities or an entity and a position.
  */
struct DistanceCondition {

};
/**
  * Condition checking the relative distance between two entities.
  */
struct RelativeDistanceCondition {
    const char *entityRef;
    const char *relativeDistanceType;
    const char *value;
    const char *freespace;
    const char *rule;
};


struct Condition {
    const char *name;
    const char *delay;
    const char *conditionEdge;
    const char *triggeringEntityRef;
    ConditionType type;
    ParameterCondition parameterCondition;
    SimulationTimeCondition simulationTimeCondition;
    StoryboardElementStateCondition storyboardElementStateCondition;
    StandStillCondition standStillCondition;
    TraveledDistanceCondition traveledDistanceCondition;
    ReachPositionCondition reachPositionCondition;
    RelativeDistanceCondition relativeDistanceCondition;
};

struct Event {
    const char *name;
    const char *priority;
    Action action;
    vector<Condition> condition;
};

// TODO: multi-maneuver in a single maneuvergroup is not supported yet
struct Story
{
    /* data */
    const char *storyName;
    const char *actName;
    const char *maneuverGroupName;
    const char *maximumExecutionCount;
    const char *selectTriggeringEntities;
    const char *entityRef;
    const char *maneuverName;
    vector<Event> eventlist; 
    vector<Condition> startCondition;
    vector<Condition> stopCondition;

    Story(
      const char *istoryName = NULL,
      const char *iactName = NULL,
      const char *imaneuverGroupName = NULL,
      const char *imaximumExecutionCount = NULL,
      const char *iselectTriggeringEntities = NULL,
      const char *ientityRef = NULL,
      const char *imaneuverName = NULL) {
        storyName = istoryName;
        actName = iactName;
        maneuverGroupName = imaneuverGroupName;
        maximumExecutionCount = imaximumExecutionCount;
        selectTriggeringEntities = iselectTriggeringEntities;
        entityRef = ientityRef;
        maneuverName = imaneuverName;
    };
};





#endif