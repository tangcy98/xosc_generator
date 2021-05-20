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
    const char *maxSpeed;
    const char *maxAcceleration;
    const char *maxDeceleration;

    // <Axles> - <FrontAxle>
    const char *frontAxleMaxSteering;
    const char *frontAxleWheelDiameter;
    const char *frontAxleTrackWidth;
    const char *frontAxlePositionX;
    const char *frontAxlePositionZ;
    
    // <Axles> - <RearAxle>
    const char *rearAxleMaxSteering;
    const char *rearAxleWheelDiameter;
    const char *rearAxleTrackWidth;
    const char *rearAxlePositionX;
    const char *rearAxlePositionZ;

    // <Controller>
    const char *controllerName;

    // <Controller> - <Properties>
    vector< pair<const char*, const char*> > controllerprops;

    // <OverrideControllerValueAction>
    pair<const char*, const char*> Throttle;
    pair<const char*, const char*> Brake;
    pair<const char*, const char*> Clutch;
    pair<const char*, const char*> ParkingBrake;
    pair<const char*, const char*> SteeringWheel;
    pair<const char*, const char*> Gear;
};

struct Pedestrian {
    // <Pedestrian>
    const char *model;
    const char *mass;
};

struct MiscObject {
    // <MiscObject>
    const char *mass;
};

struct Actor {
    ACTORTYPE actortype;
    /* data */
    // <ScenarioObject>
    const char *objname;

    // <Vehicle>, <Pedestrian>, <MiscObject>
    const char *name;
    const char *category;

    // <ParameterDeclarations>
    vector< Parameter > paras;

    // <BoundingBox> - <Center>
    const char *boundingx;
    const char *boundingy;
    const char *boundingz;

    // <BoundingBox> - <Dimensions>
    const char *boundingw;
    const char *boundingl;
    const char *boundingh;

    // <Position>
    Position position;

    // <Properties>
    vector< pair<const char*, const char*> > props;

    Vehicle vehparas;
    Pedestrian pedparas;
    MiscObject miscparas;

    // Actor();
    ~Actor();
    SETRES setType(ACTORTYPE type);
    SETRES setObjName(const char *str);
    SETRES setName(const char *str);
    SETRES setCategory(const char *str);
    SETRES addPara(Parameter para);
    SETRES setBoundingBoxCenter(const char *x, const char *y, const char *z);
    SETRES setBoundingBoxDimensions(const char *w, const char *l, const char *h);
    SETRES setWorldPosition(WorldPosition pos);
    SETRES setLanePosition(LanePosition pos);
    SETRES addProp(pair<const char*, const char*> prop);
    SETRES setVehicle(Vehicle *v);
    SETRES setPedestrian(Pedestrian *p);
    SETRES setMiscObject(MiscObject *m);
};


#endif