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
    string dynamicsShape;
    string dynamicsvalue;
    string dynamicsDimension;
    string targetvalue;
};

/**
  * Applies lateral control behavior on the reference entity/entities. Either a LaneChangeAction, LaneOffsetAction or a LateralDistanceAction.
  */
struct LateralAction {
    string dynamicsShape;
    string dynamicsvalue;
    string dynamicsDimension;
    string targetentityRef;
    string targetvalue;
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
    string masterEntityRef;
    Position targetPositionMaster;
    Position targetPosition;
    string relativeSpeedToMasterValue;
    string speedTargetValueType;
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
    string name;
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
    string parameterRef;
    string value;
    string rule;
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
    string value;
    string rule;
};
/**
  * Condition becomes true if the referenced StoryboardElement terminates according to the given rule.
  */
struct StoryboardElementStateCondition {
    string storyboardElementType;
    string storyboardElementRef;
    string state;

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
    string duration;
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
    string value;
};
/**
  * Condition checking whether the reference entity has reached a given position within a given uncertainty.
  */
struct ReachPositionCondition {
    string tolerance;
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
    string entityRef;
    string relativeDistanceType;
    string value;
    string freespace;
    string rule;
};


struct Condition {
    string name;
    string delay;
    string conditionEdge;
    string triggeringEntityRef;
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
    string name;
    string priority;
    Action action;
    vector<Condition> condition;
};

// TODO: multi-maneuver in a single maneuvergroup is not supported yet
struct Story
{
    /* data */
    string storyName;
    string actName;
    string maneuverGroupName;
    string maximumExecutionCount;
    string selectTriggeringEntities;
    string entityRef;
    string maneuverName;
    vector<Event> eventlist; 
    vector<Condition> startCondition;
    vector<Condition> stopCondition;

    Story(
      string istoryName= "",
      string iactName= "",
      string imaneuverGroupName= "",
      string imaximumExecutionCount= "",
      string iselectTriggeringEntities= "",
      string ientityRef= "",
      string imaneuverName= "") {
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