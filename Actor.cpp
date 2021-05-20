#include "Actor.h"

// Actor::Actor()
// {
//     actortype = VEHICLE;
//     objname = NULL;
//     name = NULL;
//     category = NULL;
//     boundingx = NULL;
//     boundingy = NULL;
//     boundingz = NULL;
//     boundingw = NULL;
//     boundingl = NULL;
//     boundingh = NULL;
//     positiontype = WORLD;
//     worldPosition.x = NULL;
//     worldPosition.y = NULL;
//     worldPosition.z = NULL;
//     worldPosition.h = NULL;
//     lanePosition.roadId = NULL;
//     lanePosition.laneId = NULL;
//     lanePosition.offset = NULL;
//     lanePosition.s = NULL;
//     vehparas.maxSpeed = NULL;
//     vehparas.maxAcceleration = NULL;
//     vehparas.maxDeceleration = NULL;
//     vehparas.frontAxleMaxSteering = NULL;
//     vehparas.frontAxleWheelDiameter = NULL;
//     vehparas.frontAxleTrackWidth = NULL;
//     vehparas.frontAxlePositionX = NULL;
//     vehparas.frontAxlePositionZ = NULL;
//     vehparas.rearAxleMaxSteering = NULL;
//     vehparas.rearAxleWheelDiameter = NULL;
//     vehparas.rearAxleTrackWidth = NULL;
//     vehparas.rearAxlePositionX = NULL;
//     vehparas.rearAxlePositionZ = NULL;
//     vehparas.controllerName = NULL;
//     pedparas.mass = NULL;
//     pedparas.model = NULL;
//     miscparas.mass = NULL;

//     pair<const char*, const char*> tmp;
//     tmp.first = NULL;
//     tmp.second = NULL;
//     vehparas.Throttle = tmp;
//     vehparas.Brake = tmp;
//     vehparas.Clutch = tmp;
//     vehparas.ParkingBrake = tmp;
//     vehparas.SteeringWheel = tmp;
//     vehparas.Gear = tmp;
// }

Actor::~Actor()
{
    
}

SETRES Actor::setType(ACTORTYPE type)
{
    actortype = type;
    return SET_OK;
}

SETRES Actor::setObjName(const char *str)
{
    objname = str;
    return SET_OK;
}

SETRES Actor::setName(const char *str)
{
    name = str;
    return SET_OK;
}
SETRES Actor::setCategory(const char *str)
{
    category = str;
    return SET_OK;
}
SETRES Actor::addPara(Parameter para)
{
    paras.push_back(para);
    return SET_OK;
}
SETRES Actor::setBoundingBoxCenter(const char *x, const char *y, const char *z)
{
    boundingx = x;
    boundingy = y;
    boundingz = z;
    return SET_OK;
}
SETRES Actor::setBoundingBoxDimensions(const char *w, const char *l, const char *h)
{
    boundingw = w;
    boundingl = l;
    boundingh = h;
    return SET_OK;
}
SETRES Actor::setWorldPosition(WorldPosition pos)
{
    position.worldPosition = pos;
    return SET_OK;
}
SETRES Actor::setLanePosition(LanePosition pos)
{
    position.lanePosition = pos;
    return SET_OK;
}
SETRES Actor::addProp(pair<const char*, const char*> prop)
{
    props.push_back(prop);
    return SET_OK;
}
SETRES Actor::setVehicle(Vehicle *v)
{
    vehparas = *v;
    return SET_OK;
}
SETRES Actor::setPedestrian(Pedestrian *p)
{
    pedparas = *p;
    return SET_OK;
}
SETRES Actor::setMiscObject(MiscObject *m)
{
    miscparas = *m;
    return SET_OK;
}