#ifndef _ACTOR_
#define _ACTOR_

#include "common.h"
#include "Position.h"

using namespace std;

enum ACTORTYPE {
    VEHICLE,
    PEDESTRIAN,
    MISCOBJECT,
};

struct Vehicle {

    // <Performance>
    std::string maxSpeed;
    std::string maxAcceleration;
    std::string maxDeceleration;

    // <Axles> - <FrontAxle>
    std::string frontAxleMaxSteering;
    std::string frontAxleWheelDiameter;
    std::string frontAxleTrackWidth;
    std::string frontAxlePositionX;
    std::string frontAxlePositionZ;
    
    // <Axles> - <RearAxle>
    std::string rearAxleMaxSteering;
    std::string rearAxleWheelDiameter;
    std::string rearAxleTrackWidth;
    std::string rearAxlePositionX;
    std::string rearAxlePositionZ;

    // <Controller>
    std::string controllerName;

    // <Controller> - <Properties>
    vector< pair<std::string , std::string > > controllerprops;

    // <OverrideControllerValueAction>
    pair<std::string , std::string > Throttle;
    pair<std::string , std::string > Brake;
    pair<std::string , std::string > Clutch;
    pair<std::string , std::string > ParkingBrake;
    pair<std::string , std::string > SteeringWheel;
    pair<std::string , std::string > Gear;
};

struct Pedestrian {
    // <Pedestrian>
    std::string model;
    std::string mass;
};

struct MiscObject {
    // <MiscObject>
    std::string mass;
};

struct Actor {
    ACTORTYPE actortype;
    /* data */
    // <ScenarioObject>
    std::string objname;

    // <Vehicle>, <Pedestrian>, <MiscObject>
    std::string name;
    std::string category;

    // <ParameterDeclarations>
    vector< Parameter > paras;

    // <BoundingBox> - <Center>
    std::string boundingx;
    std::string boundingy;
    std::string boundingz;

    // <BoundingBox> - <Dimensions>
    std::string boundingw;
    std::string boundingl;
    std::string boundingh;

    // <Position>
    Position position;

    // <Properties>
    vector< pair<std::string , std::string > > props;

    Vehicle vehparas;
    Pedestrian pedparas;
    MiscObject miscparas;

    // Actor();
};


#endif