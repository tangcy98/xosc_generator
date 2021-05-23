#include "xosc_generator.h"

static tinyxml2::XMLElement* newStopConditionElement(tinyxml2::XMLDocument *doc,  const char *name, const char *pararef = "", const char *value = "")
{
    // <Condition>
    tinyxml2::XMLElement *Condition = doc->NewElement("Condition");
    Condition->SetAttribute("name", name);
    Condition->SetAttribute("delay", "0");
    Condition->SetAttribute("conditionEdge", "rising");

    // <ByValueCondition>
    tinyxml2::XMLElement *ByValueCondition = doc->NewElement("ByValueCondition");

    // <ParameterCondition>
    tinyxml2::XMLElement *ParameterCondition = doc->NewElement("ParameterCondition");
    ParameterCondition->SetAttribute("parameterRef", pararef ? pararef : "");
    ParameterCondition->SetAttribute("value", value ? value : "");
    ParameterCondition->SetAttribute("rule", "lessThan");

    ByValueCondition->LinkEndChild(ParameterCondition);
    // </ParameterCondition>

    Condition->LinkEndChild(ByValueCondition);
    // </ByValueCondition>

    return Condition;
}

static tinyxml2::XMLElement* newConditionElement(tinyxml2::XMLDocument *doc, const Condition *c)
{
    // <Condition>
    tinyxml2::XMLElement *Condition = doc->NewElement("Condition");
    Condition->SetAttribute("name", c->name.c_str());
    Condition->SetAttribute("delay", c->delay.c_str());
    Condition->SetAttribute("conditionEdge", c->conditionEdge.c_str());

    switch (c->type) {
        /** ByValueCondition **/
        case PARAMETERCONDITION: {
            // <ByValueCondition>
            tinyxml2::XMLElement *ByValueCondition = doc->NewElement("ByValueCondition");
            
            // <ParameterCondition>
            tinyxml2::XMLElement *ParameterCondition = doc->NewElement("ParameterCondition");
            ParameterCondition->SetAttribute("parameterRef", c->parameterCondition.parameterRef.c_str());
            ParameterCondition->SetAttribute("value", c->parameterCondition.value.c_str());
            ParameterCondition->SetAttribute("rule", c->parameterCondition.rule.c_str());
            ByValueCondition->LinkEndChild(ParameterCondition);
            // </ParameterCondition>

            Condition->LinkEndChild(ByValueCondition);
            // </ByValueCondition>
            break;
        }
        case SIMULATIONTIMECONDITION: {
            // <ByValueCondition>
            tinyxml2::XMLElement *ByValueCondition = doc->NewElement("ByValueCondition");
            
            // <SimulationTimeCondition>
            tinyxml2::XMLElement *SimulationTimeCondition = doc->NewElement("SimulationTimeCondition");
            SimulationTimeCondition->SetAttribute("value", c->simulationTimeCondition.value.c_str());
            SimulationTimeCondition->SetAttribute("rule", c->simulationTimeCondition.rule.c_str());
            ByValueCondition->LinkEndChild(SimulationTimeCondition);
            // </SimulationTimeCondition>

            Condition->LinkEndChild(ByValueCondition);
            // </ByValueCondition>
            break;
        }
        case STORYBOARDELEMENTSTATECONDITION: {
            // <ByValueCondition>
            tinyxml2::XMLElement *ByValueCondition = doc->NewElement("ByValueCondition");
            
            // <StoryboardElementStateCondition>
            tinyxml2::XMLElement *StoryboardElementStateCondition = doc->NewElement("StoryboardElementStateCondition");
            StoryboardElementStateCondition->SetAttribute("storyboardElementType", c->storyboardElementStateCondition.storyboardElementType.c_str());
            StoryboardElementStateCondition->SetAttribute("storyboardElementRef", c->storyboardElementStateCondition.storyboardElementRef.c_str());
            StoryboardElementStateCondition->SetAttribute("state", c->storyboardElementStateCondition.state.c_str());
            ByValueCondition->LinkEndChild(StoryboardElementStateCondition);
            // </StoryboardElementStateCondition>

            Condition->LinkEndChild(ByValueCondition);
            // </ByValueCondition>
            break;
        }

        /** ByEntityCondition **/
        case STANDSTILLCONDITION: {
            // <ByEntityCondition>
            tinyxml2::XMLElement *ByEntityCondition = doc->NewElement("ByEntityCondition");
            
            // <TriggeringEntities>
            tinyxml2::XMLElement *TriggeringEntities = doc->NewElement("TriggeringEntities");
            TriggeringEntities->SetAttribute("triggeringEntitiesRule", "any");

            // <EntityRef>
            tinyxml2::XMLElement *EntityRef = doc->NewElement("EntityRef");
            EntityRef->SetAttribute("entityRef", c->triggeringEntityRef.c_str());
            TriggeringEntities->LinkEndChild(EntityRef);
            // </EntityRef>

            ByEntityCondition->LinkEndChild(TriggeringEntities);
            // </TriggeringEntities>

            // <EntityCondition>
            tinyxml2::XMLElement *EntityCondition = doc->NewElement("EntityCondition");

            // <StandStillCondition>
            tinyxml2::XMLElement *StandStillCondition = doc->NewElement("StandStillCondition");
            StandStillCondition->SetAttribute("duration", c->standStillCondition.duration.c_str());
            EntityCondition->LinkEndChild(StandStillCondition);
            // </StandStillCondition>

            ByEntityCondition->LinkEndChild(EntityCondition);
            // </EntityCondition>

            Condition->LinkEndChild(ByEntityCondition);
            // </ByEntityCondition>
            break;
        }
        case TRAVELEDDISTANCECONDITION: {
            // <ByEntityCondition>
            tinyxml2::XMLElement *ByEntityCondition = doc->NewElement("ByEntityCondition");
            
            // <TriggeringEntities>
            tinyxml2::XMLElement *TriggeringEntities = doc->NewElement("TriggeringEntities");
            TriggeringEntities->SetAttribute("triggeringEntitiesRule", "any");

            // <EntityRef>
            tinyxml2::XMLElement *EntityRef = doc->NewElement("EntityRef");
            EntityRef->SetAttribute("entityRef", c->triggeringEntityRef.c_str());
            TriggeringEntities->LinkEndChild(EntityRef);
            // </EntityRef>

            ByEntityCondition->LinkEndChild(TriggeringEntities);
            // </TriggeringEntities>

            // <EntityCondition>
            tinyxml2::XMLElement *EntityCondition = doc->NewElement("EntityCondition");

            // <TraveledDistanceCondition>
            tinyxml2::XMLElement *TraveledDistanceCondition = doc->NewElement("TraveledDistanceCondition");
            TraveledDistanceCondition->SetAttribute("value", c->traveledDistanceCondition.value.c_str());
            EntityCondition->LinkEndChild(TraveledDistanceCondition);
            // </TraveledDistanceCondition>

            ByEntityCondition->LinkEndChild(EntityCondition);
            // </EntityCondition>

            Condition->LinkEndChild(ByEntityCondition);
            // </ByEntityCondition>
            break;
        }
        case REACHPOSITIONCONDITION: {
            // <ByEntityCondition>
            tinyxml2::XMLElement *ByEntityCondition = doc->NewElement("ByEntityCondition");
            
            // <TriggeringEntities>
            tinyxml2::XMLElement *TriggeringEntities = doc->NewElement("TriggeringEntities");
            TriggeringEntities->SetAttribute("triggeringEntitiesRule", "any");

            // <EntityRef>
            tinyxml2::XMLElement *EntityRef = doc->NewElement("EntityRef");
            EntityRef->SetAttribute("entityRef", c->triggeringEntityRef.c_str());
            TriggeringEntities->LinkEndChild(EntityRef);
            // </EntityRef>

            ByEntityCondition->LinkEndChild(TriggeringEntities);
            // </TriggeringEntities>

            // <EntityCondition>
            tinyxml2::XMLElement *EntityCondition = doc->NewElement("EntityCondition");

            // <ReachPositionCondition>
            tinyxml2::XMLElement *ReachPositionCondition = doc->NewElement("ReachPositionCondition");
            ReachPositionCondition->SetAttribute("value", c->reachPositionCondition.tolerance.c_str());
            EntityCondition->LinkEndChild(ReachPositionCondition);
            // </ReachPositionCondition>

            ByEntityCondition->LinkEndChild(EntityCondition);
            // </EntityCondition>

            Condition->LinkEndChild(ByEntityCondition);
            // </ByEntityCondition>
            break;
        }
        case RELATIVEDISTANCECONDITION: {
            // <ByEntityCondition>
            tinyxml2::XMLElement *ByEntityCondition = doc->NewElement("ByEntityCondition");
            
            // <TriggeringEntities>
            tinyxml2::XMLElement *TriggeringEntities = doc->NewElement("TriggeringEntities");
            TriggeringEntities->SetAttribute("triggeringEntitiesRule", "any");

            // <EntityRef>
            tinyxml2::XMLElement *EntityRef = doc->NewElement("EntityRef");
            EntityRef->SetAttribute("entityRef", c->triggeringEntityRef.c_str());
            TriggeringEntities->LinkEndChild(EntityRef);
            // </EntityRef>

            ByEntityCondition->LinkEndChild(TriggeringEntities);
            // </TriggeringEntities>

            // <EntityCondition>
            tinyxml2::XMLElement *EntityCondition = doc->NewElement("EntityCondition");

            // <RelativeDistanceCondition>
            tinyxml2::XMLElement *RelativeDistanceCondition = doc->NewElement("RelativeDistanceCondition");
            RelativeDistanceCondition->SetAttribute("entityRef", c->relativeDistanceCondition.entityRef.c_str());
            RelativeDistanceCondition->SetAttribute("relativeDistanceType", c->relativeDistanceCondition.relativeDistanceType.c_str());
            RelativeDistanceCondition->SetAttribute("value", c->relativeDistanceCondition.value.c_str());
            RelativeDistanceCondition->SetAttribute("freespace", c->relativeDistanceCondition.freespace.c_str());
            RelativeDistanceCondition->SetAttribute("rule", c->relativeDistanceCondition.rule.c_str());
            EntityCondition->LinkEndChild(RelativeDistanceCondition);
            // </RelativeDistanceCondition>

            ByEntityCondition->LinkEndChild(EntityCondition);
            // </EntityCondition>

            Condition->LinkEndChild(ByEntityCondition);
            // </ByEntityCondition>
            break;
        }
        default: {
            break;
        }
    }

    return Condition;
}

XOSC::XOSC()
{
    savepath = NULL;
    doc = NULL;
    OpenSCENARIO = NULL;
    actornum = 0;
    saveflag = false;

    // environment, stopTrigger is already constructed;
}

XOSC::~XOSC()
{
    if (!saveflag) {
        if (tinyxml2::XML_SUCCESS != doc->SaveFile(savepath)) {
            printf("Save failed..\n");
        }
        else {
            printf("Save succeed!\n");
        }
    }
    delete doc;
}

void XOSC::initXML()
{
    char datetime[20];
    time_t rawtime;
    struct tm *ptminfo;
    time(&rawtime);
    ptminfo = localtime(&rawtime);
    sprintf(datetime, "%02d-%02d-%02dT%02d:%02d:%02d",
        ptminfo->tm_year + 1900, ptminfo->tm_mon + 1, ptminfo->tm_mday, ptminfo->tm_hour, ptminfo->tm_min, ptminfo->tm_sec);

    doc =  new tinyxml2::XMLDocument;
    tinyxml2::XMLDeclaration *declaration = doc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    OpenSCENARIO    = doc->NewElement("OpenSCENARIO");
    tinyxml2::XMLElement *FileHeader      = doc->NewElement("FileHeader");
    tinyxml2::XMLElement *ParameterDeclarations = doc->NewElement("ParameterDeclarations");
    tinyxml2::XMLElement *CatalogLocations = doc->NewElement("CatalogLocations");
    tinyxml2::XMLElement *RoadNetwork     = doc->NewElement("RoadNetwork");
    tinyxml2::XMLElement *Entities        = doc->NewElement("Entities");
    tinyxml2::XMLElement *Storyboard      = doc->NewElement("Storyboard");

    doc->LinkEndChild(declaration);
    doc->LinkEndChild(OpenSCENARIO);

    OpenSCENARIO->LinkEndChild(FileHeader);
    OpenSCENARIO->LinkEndChild(ParameterDeclarations);
    OpenSCENARIO->LinkEndChild(CatalogLocations);
    OpenSCENARIO->LinkEndChild(RoadNetwork);
    OpenSCENARIO->LinkEndChild(Entities);
    OpenSCENARIO->LinkEndChild(Storyboard);

    FileHeader->SetAttribute("revMajor","1");
    FileHeader->SetAttribute("revMinor","0");
    FileHeader->SetAttribute("date",datetime);
    FileHeader->SetAttribute("description","CARLA:NONAME");
    FileHeader->SetAttribute("author","xosc_generator");
}

void XOSC::cleanall()
{
    savepath = NULL;
    delete doc;
    doc = NULL;
    OpenSCENARIO = NULL;
    actornum = 0;
    Actor a1;
    actorlist.resize(0, a1);
}

SETRES XOSC::setFilename(const char *file)
{
    savepath = file;
    char *description = new char[strlen(file) + 7];
    char *pos;
    strcpy(description, "CARLA:");
    strcpy(description + 6, file);
    pos = strchr(description, '.');
    if (pos) {
        *pos = 0;
    }
    
    tinyxml2::XMLElement *elem;
    elem = OpenSCENARIO->FirstChildElement("FileHeader");
    if (!elem) return SET_ERROR;
    elem->SetAttribute("description", description);

    // TODO: Set Maneuver name
    return SET_OK;
}

SETRES XOSC::setGlobalParaDeclaration(const char *name, const char *paratype, const char *value)
{
    tinyxml2::XMLElement *ParameterDeclarations, *sub;
    ParameterDeclarations = OpenSCENARIO->FirstChildElement("FileHeader");
    if (!ParameterDeclarations) return SET_ERROR;
    sub = doc->NewElement("ParameterDeclaration");
    sub->SetAttribute("name", name?name:"");
    sub->SetAttribute("parameterType", paratype?paratype:"");
    sub->SetAttribute("value", value?value:"");
    ParameterDeclarations->LinkEndChild(sub);
    return SET_OK;
}

SETRES XOSC::setMap(const char *mapname)
{
    tinyxml2::XMLElement *RoadNetwork;
    tinyxml2::XMLElement *LogicFile       = doc->NewElement("LogicFile");
    tinyxml2::XMLElement *SceneGraphFile  = doc->NewElement("SceneGraphFile");
    
    RoadNetwork = OpenSCENARIO->FirstChildElement("RoadNetwork");
    if (!RoadNetwork) return SET_ERROR;
    LogicFile->SetAttribute("filepath", mapname);
    SceneGraphFile->SetAttribute("filepath", "");

    RoadNetwork->LinkEndChild(LogicFile);
    RoadNetwork->LinkEndChild(SceneGraphFile);

    return SET_OK;
}

SETRES XOSC::setActorNum(const int num)
{
    if (num < 0) {
        return SET_ERROR;
    }
    actornum = num;
    Actor a1;
    actorlist.resize(num, a1);
    return SET_OK;
}

/**
  * @note   Should be called after actornum and environment is set
  */
SETRES XOSC::setActor(const int n, const Actor *actor)
{
    if (n >= actornum) {
        return SET_ERROR;
    }

    if (actor->actortype != VEHICLE && actor->actortype != PEDESTRIAN && actor->actortype !=MISCOBJECT) {
        return SET_ERROR;
    }

    actorlist[n] = *actor;
    tinyxml2::XMLElement *Entities;
    
    Entities = OpenSCENARIO->FirstChildElement("Entities");
    if (!Entities) return SET_ERROR;
    // <ScenarioObject>
    tinyxml2::XMLElement *ScenarioObject = doc->NewElement("ScenarioObject");
    ScenarioObject->SetAttribute("name", actor->objname.c_str());
    tinyxml2::XMLElement *ActorElem;

    // <Vehicle>, <Pedestrian>, <MiscObject>
    if (actor->actortype == VEHICLE) {
        ActorElem = doc->NewElement("Vehicle");
        ActorElem->SetAttribute("name", actor->name.c_str());
        ActorElem->SetAttribute("vehicleCategory", actor->category.c_str());
    }
    else if (actor->actortype == PEDESTRIAN) {
        ActorElem = doc->NewElement("Pedestrian");
        ActorElem->SetAttribute("model", actor->pedparas.model.c_str());
        ActorElem->SetAttribute("mass", actor->pedparas.mass.c_str());
        ActorElem->SetAttribute("name", actor->name.c_str());
        ActorElem->SetAttribute("pedestrianCategory", actor->category.c_str());
    }
    else if (actor->actortype == MISCOBJECT) {
        ActorElem = doc->NewElement("MiscObject");
        ActorElem->SetAttribute("mass", actor->miscparas.mass.c_str());
        ActorElem->SetAttribute("name", actor->name.c_str());
        ActorElem->SetAttribute("miscObjectCategory", actor->category.c_str());
    }

    // <ParameterDeclarations>
    tinyxml2::XMLElement *ParameterDeclarations = doc->NewElement("ParameterDeclarations");
    for (auto iter = actor->paras.begin(); iter != actor->paras.end(); iter++) {
        // <ParameterDeclaration>
        tinyxml2::XMLElement *ParameterDeclaration = doc->NewElement("ParameterDeclaration");
        ParameterDeclaration->SetAttribute("name", iter->name);
        ParameterDeclaration->SetAttribute("parameterType", iter->parameterType);
        ParameterDeclaration->SetAttribute("value", iter->value);
        ParameterDeclarations->LinkEndChild(ParameterDeclaration);
        // </ParameterDeclaration>
    }
    ActorElem->LinkEndChild(ParameterDeclarations);
    // </ParameterDeclarations>

    if (actor->actortype == VEHICLE) {
        // <Performance>
        tinyxml2::XMLElement *Performance = doc->NewElement("Performance");
        Performance->SetAttribute("maxSpeed", actor->vehparas.maxSpeed.c_str());
        Performance->SetAttribute("maxAcceleration", actor->vehparas.maxAcceleration.c_str());
        Performance->SetAttribute("maxDeceleration", actor->vehparas.maxDeceleration.c_str());
        ActorElem->LinkEndChild(Performance);
        // </Performance>
    }
    
    // <BoundingBox>
    tinyxml2::XMLElement *BoundingBox = doc->NewElement("BoundingBox");

    // <Center>
    tinyxml2::XMLElement *Center = doc->NewElement("Center");
    Center->SetAttribute("x", actor->boundingx.c_str());
    Center->SetAttribute("y", actor->boundingy.c_str());
    Center->SetAttribute("z", actor->boundingz.c_str());
    BoundingBox->LinkEndChild(Center);
    // </Center>

    // <Dimensions>
    tinyxml2::XMLElement *Dimensions = doc->NewElement("Dimensions");
    Dimensions->SetAttribute("width", actor->boundingw.c_str());
    Dimensions->SetAttribute("length", actor->boundingl.c_str());
    Dimensions->SetAttribute("height", actor->boundingh.c_str());
    BoundingBox->LinkEndChild(Dimensions);
    // </Dimensions>

    ActorElem->LinkEndChild(BoundingBox);
    // </BoundingBox>

    if (actor->actortype == VEHICLE) {
        // <Axles>
        tinyxml2::XMLElement *Axles = doc->NewElement("Axles");

        // <FrontAxle>
        tinyxml2::XMLElement *FrontAxle = doc->NewElement("FrontAxle");
        FrontAxle->SetAttribute("maxSteering", actor->vehparas.frontAxleMaxSteering.c_str());
        FrontAxle->SetAttribute("wheelDiameter", actor->vehparas.frontAxleWheelDiameter.c_str());
        FrontAxle->SetAttribute("trackWidth", actor->vehparas.frontAxleTrackWidth.c_str());
        FrontAxle->SetAttribute("positionX", actor->vehparas.frontAxlePositionX.c_str());
        FrontAxle->SetAttribute("positionZ", actor->vehparas.frontAxlePositionZ.c_str());
        Axles->LinkEndChild(FrontAxle);
        // </FrontAxle>

        // <RearAxle>
        tinyxml2::XMLElement *RearAxle = doc->NewElement("RearAxle");
        RearAxle->SetAttribute("maxSteering", actor->vehparas.rearAxleMaxSteering.c_str());
        RearAxle->SetAttribute("wheelDiameter", actor->vehparas.rearAxleWheelDiameter.c_str());
        RearAxle->SetAttribute("trackWidth", actor->vehparas.rearAxleTrackWidth.c_str());
        RearAxle->SetAttribute("positionX", actor->vehparas.rearAxlePositionX.c_str());
        RearAxle->SetAttribute("positionZ", actor->vehparas.rearAxlePositionZ.c_str());
        Axles->LinkEndChild(RearAxle);
        // </RearAxle>
        
        ActorElem->LinkEndChild(Axles);
        // </Axles>
    }


    // <Properties>
    tinyxml2::XMLElement *Properties = doc->NewElement("Properties");
    for (auto iter = actor->props.begin(); iter != actor->props.end(); iter++) {
        // <Property>
        tinyxml2::XMLElement *Property = doc->NewElement("Property");
        Property->SetAttribute("name", iter->first.c_str());
        Property->SetAttribute("value", iter->second.c_str());
        Properties->LinkEndChild(Property);
        // </Property>
    }
    ActorElem->LinkEndChild(Properties);
    // </Properties>

    ScenarioObject->LinkEndChild(ActorElem);
    // </Vehicle>, </Pedestrian>, </MiscObject>

    Entities->LinkEndChild(ScenarioObject);
    // </ScenarioObject>


    tinyxml2::XMLElement *Storyboard, *Init, *Actions;
    Storyboard = OpenSCENARIO->FirstChildElement("Storyboard");
    if (!Storyboard) return SET_ERROR;
    Init = Storyboard->FirstChildElement("Init");
    if (!Init) return SET_ERROR;
    Actions = Init->FirstChildElement("Actions");
    if (!Actions) return SET_ERROR;

    // <Private>
    tinyxml2::XMLElement *Private = doc->NewElement("Private");
    Private->SetAttribute("entityRef", actor->objname.c_str());

    // <PrivateAction>
    tinyxml2::XMLElement *PrivateAction = doc->NewElement("PrivateAction");
    
    // <TeleportAction>
    tinyxml2::XMLElement *TeleportAction = doc->NewElement("TeleportAction");

    // <Position>
    tinyxml2::XMLElement *Position = doc->NewElement("Position");

    // <WorldPosition>, <LanePosition>
    if (actor->position.positiontype == WORLD) {
        tinyxml2::XMLElement *WorldPosition = doc->NewElement("WorldPosition");
        WorldPosition->SetAttribute("x", actor->position.worldPosition.x.c_str());
        WorldPosition->SetAttribute("y", actor->position.worldPosition.y.c_str());
        WorldPosition->SetAttribute("z", actor->position.worldPosition.z.c_str());
        WorldPosition->SetAttribute("h", actor->position.worldPosition.h.c_str());
        Position->LinkEndChild(WorldPosition);
    }
    else if (actor->position.positiontype == LANE) {
        tinyxml2::XMLElement *LanePosition = doc->NewElement("LanePosition");
        LanePosition->SetAttribute("roadId", actor->position.lanePosition.roadId.c_str());
        LanePosition->SetAttribute("laneId", actor->position.lanePosition.laneId.c_str());
        LanePosition->SetAttribute("offset", actor->position.lanePosition.offset.c_str());
        LanePosition->SetAttribute("s", actor->position.lanePosition.s.c_str());
        Position->LinkEndChild(LanePosition);
    }
    // </WorldPosition>, </LanePosition>

    TeleportAction->LinkEndChild(Position);
    // </Position>

    PrivateAction->LinkEndChild(TeleportAction);
    // </TeleportAction>

    Private->LinkEndChild(PrivateAction);
    // </PrivateAction>

    if (actor->actortype == VEHICLE && 
      actor->vehparas.controllerprops.begin() != actor->vehparas.controllerprops.end()
    ) {
        // <PrivateAction>
        PrivateAction = doc ->NewElement("PrivateAction");
        
        // <ControllerAction>
        tinyxml2::XMLElement *ControllerAction = doc ->NewElement("ControllerAction");

        // <AssignControllerAction>
        tinyxml2::XMLElement *AssignControllerAction = doc ->NewElement("AssignControllerAction");

        // <Controller>
        tinyxml2::XMLElement *Controller = doc ->NewElement("Controller");
        Controller->SetAttribute("name", actor->vehparas.controllerName.c_str());

        // <Properties>
        tinyxml2::XMLElement *Properties = doc ->NewElement("Properties");
        for (auto iter = actor->vehparas.controllerprops.begin(); iter != actor->vehparas.controllerprops.end(); iter++) {
            // <Property>
            tinyxml2::XMLElement *Property = doc->NewElement("Property");
            Property->SetAttribute("name", iter->first.c_str());
            Property->SetAttribute("value", iter->second.c_str());
            Properties->LinkEndChild(Property);
            // </Property>
        }
        Controller->LinkEndChild(Properties);
        // </Properties>

        AssignControllerAction->LinkEndChild(Controller);
        // </Controller>

        ControllerAction->LinkEndChild(AssignControllerAction);
        // </AssignControllerAction>

        // <OverrideControllerValueAction>
        tinyxml2::XMLElement *OverrideControllerValueAction = doc->NewElement("OverrideControllerValueAction");

        // <Throttle>, <Brake>, <Clutch>, <ParkingBrake>, <SteeringWheel>, <Gear>
        tinyxml2::XMLElement *Throttle = doc->NewElement("Throttle");
        tinyxml2::XMLElement *Brake = doc->NewElement("Brake");
        tinyxml2::XMLElement *Clutch = doc->NewElement("Clutch");
        tinyxml2::XMLElement *ParkingBrake = doc->NewElement("ParkingBrake");
        tinyxml2::XMLElement *SteeringWheel = doc->NewElement("SteeringWheel");
        tinyxml2::XMLElement *Gear = doc->NewElement("Gear");

        Throttle->SetAttribute("value", actor->vehparas.Throttle.first.c_str());
        Throttle->SetAttribute("active", actor->vehparas.Throttle.second.c_str());
        Brake->SetAttribute("value", actor->vehparas.Brake.first.c_str());
        Brake->SetAttribute("active", actor->vehparas.Brake.second.c_str());
        Clutch->SetAttribute("value", actor->vehparas.Clutch.first.c_str());
        Clutch->SetAttribute("active", actor->vehparas.Clutch.second.c_str());
        ParkingBrake->SetAttribute("value", actor->vehparas.ParkingBrake.first.c_str());
        ParkingBrake->SetAttribute("active", actor->vehparas.ParkingBrake.second.c_str());
        SteeringWheel->SetAttribute("value", actor->vehparas.SteeringWheel.first.c_str());
        SteeringWheel->SetAttribute("active", actor->vehparas.SteeringWheel.second.c_str());
        Gear->SetAttribute("number", actor->vehparas.Gear.first.c_str());
        Gear->SetAttribute("active", actor->vehparas.Gear.second.c_str());

        OverrideControllerValueAction->LinkEndChild(Throttle);
        OverrideControllerValueAction->LinkEndChild(Brake);
        OverrideControllerValueAction->LinkEndChild(Clutch);
        OverrideControllerValueAction->LinkEndChild(ParkingBrake);
        OverrideControllerValueAction->LinkEndChild(SteeringWheel);
        OverrideControllerValueAction->LinkEndChild(Gear);
        // </Throttle>, </Brake>, </Clutch>, </ParkingBrake>, </SteeringWheel>, </Gear>

        ControllerAction->LinkEndChild(OverrideControllerValueAction);
        // </OverrideControllerValueAction>

        PrivateAction->LinkEndChild(ControllerAction);
        // </ControllerAction>

        Private->LinkEndChild(PrivateAction);
        // </PrivateAction>
    }
    Actions->LinkEndChild(Private);
    // </Private>

    return SET_OK;
}

SETRES XOSC::setEnvironment(const Environment *env)
{
    environment = *env;
    tinyxml2::XMLElement *Storyboard = OpenSCENARIO->FirstChildElement("Storyboard");
    
    // <Init>
    tinyxml2::XMLElement *Init = doc->NewElement("Init");

    // <Actions>
    tinyxml2::XMLElement *Actions = doc->NewElement("Actions");

    // <GlobalAction>
    tinyxml2::XMLElement *GlobalAction = doc->NewElement("GlobalAction");

    // <EnvironmentAction>
    tinyxml2::XMLElement *EnvironmentAction = doc->NewElement("EnvironmentAction");

    // <Environment>
    tinyxml2::XMLElement *EnvironmentElem = doc->NewElement("Environment");
    EnvironmentElem->SetAttribute("name", env->name.c_str());

    // <TimeOfDay>
    tinyxml2::XMLElement *TimeOfDay = doc->NewElement("TimeOfDay");
    TimeOfDay->SetAttribute("animation", env->animation.c_str());
    TimeOfDay->SetAttribute("dateTime", env->dateTime.c_str());
    EnvironmentElem->LinkEndChild(TimeOfDay);
    // </TimeOfDay>

    // <Weather>
    tinyxml2::XMLElement *Weather = doc->NewElement("Weather");
    Weather->SetAttribute("cloudState", env->cloudState.c_str());

    // <Sun>
    tinyxml2::XMLElement *Sun = doc->NewElement("Sun");
    Sun->SetAttribute("intensity", env->sunintensity.c_str());
    Sun->SetAttribute("azimuth", env->azimuth.c_str());
    Sun->SetAttribute("elevation", env->elevation.c_str());
    Weather->LinkEndChild(Sun);
    // </Sun>

    // <Fog>
    tinyxml2::XMLElement *Fog = doc->NewElement("Fog");
    Fog->SetAttribute("visualRange", env->visualRange.c_str());
    Weather->LinkEndChild(Fog);
    // </Fog>

    // <Precipitation>
    tinyxml2::XMLElement *Precipitation = doc->NewElement("Precipitation");
    Precipitation->SetAttribute("precipitationType", env->precipitationType.c_str());
    Precipitation->SetAttribute("intensity", env->precipitationintensity.c_str());
    Weather->LinkEndChild(Precipitation);
    // </Precipitation>

    EnvironmentElem->LinkEndChild(Weather);
    // </Weather>

    // <RoadCondition>
    tinyxml2::XMLElement *RoadCondition = doc->NewElement("RoadCondition");
    RoadCondition->SetAttribute("frictionScaleFactor", env->frictionScaleFactor.c_str());
    EnvironmentElem->LinkEndChild(RoadCondition);
    // </RoadCondition>

    EnvironmentAction->LinkEndChild(EnvironmentElem);
    // </Environment>

    GlobalAction->LinkEndChild(EnvironmentAction);
    // </EnvironmentAction>

    Actions->LinkEndChild(GlobalAction);
    // </GlobalAction>

    Init->LinkEndChild(Actions);
    // </Actions>

    Storyboard->LinkEndChild(Init);
    // </Init>

    return SET_OK;
}
/**
  * @note   Should be called after actornum, environment and Story is set
  */
SETRES XOSC::setStopTrigger(const StopTrigger *trig)
{
    stopTrigger = *trig;
    tinyxml2::XMLElement *Storyboard;
    Storyboard = OpenSCENARIO->FirstChildElement("Storyboard");
    if (!Storyboard) {return SET_ERROR;}

    // <StopTrigger>
    tinyxml2::XMLElement *StopTrigger = doc->NewElement("StopTrigger");

    // <ConditionGroup>
    tinyxml2::XMLElement *ConditionGroup = doc->NewElement("ConditionGroup");
    if (stopTrigger.criteria_RunningStopTest) {
        // <Condition>
        tinyxml2::XMLElement *Condition = newStopConditionElement(doc, "criteria_RunningStopTest");
        ConditionGroup->LinkEndChild(Condition);
        // </Condition>
    }
    if (stopTrigger.criteria_RunningRedLightTest) {
        // <Condition>
        tinyxml2::XMLElement *Condition = newStopConditionElement(doc, "criteria_RunningRedLightTest");
        ConditionGroup->LinkEndChild(Condition);
        // </Condition>
    }
    if (stopTrigger.criteria_WrongLaneTest) {
        // <Condition>
        tinyxml2::XMLElement *Condition = newStopConditionElement(doc, "criteria_WrongLaneTest");
        ConditionGroup->LinkEndChild(Condition);
        // </Condition>
    }
    if (stopTrigger.criteria_OnSidewalkTest) {
        // <Condition>
        tinyxml2::XMLElement *Condition = newStopConditionElement(doc, "criteria_OnSidewalkTest");
        ConditionGroup->LinkEndChild(Condition);
        // </Condition>
    }
    if (stopTrigger.criteria_KeepLaneTest) {
        // <Condition>
        tinyxml2::XMLElement *Condition = newStopConditionElement(doc, "criteria_KeepLaneTest");
        ConditionGroup->LinkEndChild(Condition);
        // </Condition>
    }
    if (stopTrigger.criteria_CollisionTest) {
        // <Condition>
        tinyxml2::XMLElement *Condition = newStopConditionElement(doc, "criteria_CollisionTest");
        ConditionGroup->LinkEndChild(Condition);
        // </Condition>
    }
    if (stopTrigger.criteria_DrivenDistanceTest) {
        // <Condition>
        tinyxml2::XMLElement *Condition = newStopConditionElement(doc, "criteria_DrivenDistanceTest", "distance_success", "100");
        ConditionGroup->LinkEndChild(Condition);
        // </Condition>
    }
    StopTrigger->LinkEndChild(ConditionGroup);
    // </ConditionGroup>

    Storyboard->LinkEndChild(StopTrigger);
    // </StopTrigger>
    return SET_OK;
}



SETRES XOSC::setStory(const Story *s)
{
    if (!s) {return SET_ERROR;}
    story = *s;
    tinyxml2::XMLElement *Storyboard = OpenSCENARIO->FirstChildElement("Storyboard");
    if (!Storyboard) {return SET_ERROR;}

    // <Story>
    tinyxml2::XMLElement *Story = doc->NewElement("Story");
    Story->SetAttribute("name", s->storyName.c_str());

    // <Act>
    tinyxml2::XMLElement *Act = doc->NewElement("Act");
    Act->SetAttribute("name", s->actName.c_str());

    // <ManeuverGroup>
    tinyxml2::XMLElement *ManeuverGroup = doc->NewElement("ManeuverGroup");
    ManeuverGroup->SetAttribute("maximumExecutionCount", s->maximumExecutionCount.c_str());
    ManeuverGroup->SetAttribute("name", s->maneuverGroupName.c_str());

    // <Actors>
    tinyxml2::XMLElement *Actors = doc->NewElement("Actors");
    Actors->SetAttribute("selectTriggeringEntities", s->selectTriggeringEntities.c_str());

    // <EntityRef>
    tinyxml2::XMLElement *EntityRef = doc->NewElement("EntityRef");
    EntityRef->SetAttribute("entityRef", s->entityRef.c_str());
    Actors->LinkEndChild(EntityRef);
    // </EntityRef>

    ManeuverGroup->LinkEndChild(Actors);
    // </Actors>

    // <Maneuver>
    tinyxml2::XMLElement *Maneuver = doc->NewElement("Maneuver");
    Maneuver->SetAttribute("name", s->maneuverName.c_str());

    for (auto iter = s->eventlist.begin(); iter != s->eventlist.end(); iter++) {
        // <Event>
        tinyxml2::XMLElement *Event = doc->NewElement("Event");
        Event->SetAttribute("name", iter->name.c_str());
        Event->SetAttribute("priority", iter->priority.c_str());

        // <Action>
        tinyxml2::XMLElement *Action = doc->NewElement("Action");
        Action->SetAttribute("name", iter->action.name.c_str());

        switch (iter->action.actionType) {
            case ENVIRONMENTACTION: {
                // <GlobalAction>
                tinyxml2::XMLElement *GlobalAction = doc->NewElement("GlobalAction");
                // <EnvironmentAction>
                tinyxml2::XMLElement *EnvironmentAction = doc->NewElement("EnvironmentAction");

                // <Environment>
                tinyxml2::XMLElement *EnvironmentElem = doc->NewElement("Environment");
                EnvironmentElem->SetAttribute("name", iter->action.environmentAction.environment.name.c_str());

                // <TimeOfDay>
                tinyxml2::XMLElement *TimeOfDay = doc->NewElement("TimeOfDay");
                TimeOfDay->SetAttribute("animation", iter->action.environmentAction.environment.animation.c_str());
                TimeOfDay->SetAttribute("dateTime", iter->action.environmentAction.environment.dateTime.c_str());
                EnvironmentElem->LinkEndChild(TimeOfDay);
                // </TimeOfDay>

                // <Weather>
                tinyxml2::XMLElement *Weather = doc->NewElement("Weather");
                Weather->SetAttribute("cloudState", iter->action.environmentAction.environment.cloudState.c_str());

                // <Sun>
                tinyxml2::XMLElement *Sun = doc->NewElement("Sun");
                Sun->SetAttribute("intensity", iter->action.environmentAction.environment.sunintensity.c_str());
                Sun->SetAttribute("azimuth", iter->action.environmentAction.environment.azimuth.c_str());
                Sun->SetAttribute("elevation", iter->action.environmentAction.environment.elevation.c_str());
                Weather->LinkEndChild(Sun);
                // </Sun>

                // <Fog>
                tinyxml2::XMLElement *Fog = doc->NewElement("Fog");
                Fog->SetAttribute("visualRange", iter->action.environmentAction.environment.visualRange.c_str());
                Weather->LinkEndChild(Fog);
                // </Fog>

                // <Precipitation>
                tinyxml2::XMLElement *Precipitation = doc->NewElement("Precipitation");
                Precipitation->SetAttribute("precipitationType", iter->action.environmentAction.environment.precipitationType.c_str());
                Precipitation->SetAttribute("intensity", iter->action.environmentAction.environment.precipitationintensity.c_str());
                Weather->LinkEndChild(Precipitation);
                // </Precipitation>

                EnvironmentElem->LinkEndChild(Weather);
                // </Weather>

                // <RoadCondition>
                tinyxml2::XMLElement *RoadCondition = doc->NewElement("RoadCondition");
                RoadCondition->SetAttribute("frictionScaleFactor", iter->action.environmentAction.environment.frictionScaleFactor.c_str());
                EnvironmentElem->LinkEndChild(RoadCondition);
                // </RoadCondition>

                EnvironmentAction->LinkEndChild(EnvironmentElem);
                // </Environment>

                GlobalAction->LinkEndChild(EnvironmentAction);
                // </EnvironmentAction>

                Action->LinkEndChild(GlobalAction);
                // </GlobalAction>
                break;
            }
            case LONGITUDINALACTION: {
                // <PrivateAction>
                tinyxml2::XMLElement *PrivateAction = doc->NewElement("PrivateAction");
                // TODO: Add support for LongitudinalDistanceAction
                // <LongitudinalAction>
                tinyxml2::XMLElement *LongitudinalAction = doc->NewElement("LongitudinalAction");
                
                // <SpeedAction>
                tinyxml2::XMLElement *SpeedAction = doc->NewElement("SpeedAction");

                // <SpeedActionDynamics>
                tinyxml2::XMLElement *SpeedActionDynamics = doc->NewElement("SpeedActionDynamics");
                SpeedActionDynamics->SetAttribute("dynamicsShape", iter->action.longitudinalAction.dynamicsShape.c_str());
                SpeedActionDynamics->SetAttribute("value", iter->action.longitudinalAction.dynamicsvalue.c_str());
                SpeedActionDynamics->SetAttribute("dynamicsDimension", iter->action.longitudinalAction.dynamicsDimension.c_str());
                SpeedAction->LinkEndChild(SpeedActionDynamics);
                // </SpeedActionDynamics>

                // <SpeedActionTarget>
                tinyxml2::XMLElement *SpeedActionTarget = doc->NewElement("SpeedActionTarget");
                
                // <AbsoluteTargetSpeed>
                tinyxml2::XMLElement *AbsoluteTargetSpeed = doc->NewElement("AbsoluteTargetSpeed");
                AbsoluteTargetSpeed->SetAttribute("value", iter->action.longitudinalAction.targetvalue.c_str());
                SpeedActionTarget->LinkEndChild(AbsoluteTargetSpeed);
                // </AbsoluteTargetSpeed>

                SpeedAction->LinkEndChild(SpeedActionTarget);
                // <SpeedActionTarget>

                LongitudinalAction->LinkEndChild(SpeedAction);
                // </SpeedAction>

                PrivateAction->LinkEndChild(LongitudinalAction);
                // </LongitudinalAction>

                Action->LinkEndChild(PrivateAction);
                // </PrivateAction>
                break;
            }
            case LATERALACTION: {
                // <PrivateAction>
                tinyxml2::XMLElement *PrivateAction = doc->NewElement("PrivateAction");
                
                // <LateralAction>
                tinyxml2::XMLElement *LateralAction = doc->NewElement("LateralAction");
                
                // <LaneChangeAction>
                tinyxml2::XMLElement *LaneChangeAction = doc->NewElement("LaneChangeAction");

                // <LaneChangeActionDynamics>
                tinyxml2::XMLElement *LaneChangeActionDynamics = doc->NewElement("LaneChangeActionDynamics");
                LaneChangeActionDynamics->SetAttribute("dynamicsShape", iter->action.lateralAction.dynamicsShape.c_str());
                LaneChangeActionDynamics->SetAttribute("value", iter->action.lateralAction.dynamicsvalue.c_str());
                LaneChangeActionDynamics->SetAttribute("dynamicsDimension", iter->action.lateralAction.dynamicsDimension.c_str());
                LaneChangeAction->LinkEndChild(LaneChangeActionDynamics);
                // </LaneChangeActionDynamics>

                // <LaneChangeTarget>
                tinyxml2::XMLElement *LaneChangeTarget = doc->NewElement("LaneChangeTarget");

                // <RelativeTargetLane>
                tinyxml2::XMLElement *RelativeTargetLane = doc->NewElement("RelativeTargetLane");
                RelativeTargetLane->SetAttribute("entityRef", iter->action.lateralAction.targetentityRef.c_str());
                RelativeTargetLane->SetAttribute("value", iter->action.lateralAction.targetvalue.c_str());
                LaneChangeTarget->LinkEndChild(RelativeTargetLane);
                // </RelativeTargetLane>

                LaneChangeAction->LinkEndChild(LaneChangeTarget);
                // </LaneChangeTarget>

                LateralAction->LinkEndChild(LaneChangeAction);
                // </LaneChangeAction>

                PrivateAction->LinkEndChild(LateralAction);
                // </LateralAction>
                
                Action->LinkEndChild(PrivateAction);
                // </PrivateAction>
                break;
            }
            case SYNCHRONIZEACTION: {
                // <PrivateAction>
                tinyxml2::XMLElement *PrivateAction = doc->NewElement("PrivateAction");
                
                // <SynchronizeAction>
                tinyxml2::XMLElement *SynchronizeAction = doc->NewElement("SynchronizeAction");
                SynchronizeAction->SetAttribute("masterEntityRef", iter->action.synchronizeAction.masterEntityRef.c_str());

                // <TargetPositionMaster>
                tinyxml2::XMLElement *TargetPositionMaster = doc->NewElement("TargetPositionMaster");
                // <WorldPosition>, <LanePosition>
                if (iter->action.synchronizeAction.targetPositionMaster.positiontype == WORLD) {
                    tinyxml2::XMLElement *WorldPosition = doc->NewElement("WorldPosition");
                    WorldPosition->SetAttribute("x", iter->action.synchronizeAction.targetPositionMaster.worldPosition.x.c_str());
                    WorldPosition->SetAttribute("y", iter->action.synchronizeAction.targetPositionMaster.worldPosition.y.c_str());
                    WorldPosition->SetAttribute("z", iter->action.synchronizeAction.targetPositionMaster.worldPosition.z.c_str());
                    WorldPosition->SetAttribute("h", iter->action.synchronizeAction.targetPositionMaster.worldPosition.h.c_str());
                    TargetPositionMaster->LinkEndChild(WorldPosition);
                }
                else if (iter->action.synchronizeAction.targetPositionMaster.positiontype == LANE) {
                    tinyxml2::XMLElement *LanePosition = doc->NewElement("LanePosition");
                    LanePosition->SetAttribute("roadId", iter->action.synchronizeAction.targetPositionMaster.lanePosition.roadId.c_str());
                    LanePosition->SetAttribute("laneId", iter->action.synchronizeAction.targetPositionMaster.lanePosition.laneId.c_str());
                    LanePosition->SetAttribute("offset", iter->action.synchronizeAction.targetPositionMaster.lanePosition.offset.c_str());
                    LanePosition->SetAttribute("s", iter->action.synchronizeAction.targetPositionMaster.lanePosition.s.c_str());
                    TargetPositionMaster->LinkEndChild(LanePosition);
                }
                // </WorldPosition>, </LanePosition>

                SynchronizeAction->LinkEndChild(TargetPositionMaster);
                // </TargetPositionMaster>

                // <TargetPosition>
                tinyxml2::XMLElement *TargetPosition = doc->NewElement("TargetPosition");
                // <WorldPosition>, <LanePosition>
                if (iter->action.synchronizeAction.targetPosition.positiontype == WORLD) {
                    tinyxml2::XMLElement *WorldPosition = doc->NewElement("WorldPosition");
                    WorldPosition->SetAttribute("x", iter->action.synchronizeAction.targetPosition.worldPosition.x.c_str());
                    WorldPosition->SetAttribute("y", iter->action.synchronizeAction.targetPosition.worldPosition.y.c_str());
                    WorldPosition->SetAttribute("z", iter->action.synchronizeAction.targetPosition.worldPosition.z.c_str());
                    WorldPosition->SetAttribute("h", iter->action.synchronizeAction.targetPosition.worldPosition.h.c_str());
                    TargetPosition->LinkEndChild(WorldPosition);
                }
                else if (iter->action.synchronizeAction.targetPosition.positiontype == LANE) {
                    tinyxml2::XMLElement *LanePosition = doc->NewElement("LanePosition");
                    LanePosition->SetAttribute("roadId", iter->action.synchronizeAction.targetPosition.lanePosition.roadId.c_str());
                    LanePosition->SetAttribute("laneId", iter->action.synchronizeAction.targetPosition.lanePosition.laneId.c_str());
                    LanePosition->SetAttribute("offset", iter->action.synchronizeAction.targetPosition.lanePosition.offset.c_str());
                    LanePosition->SetAttribute("s", iter->action.synchronizeAction.targetPosition.lanePosition.s.c_str());
                    TargetPosition->LinkEndChild(LanePosition);
                }
                // </WorldPosition>, </LanePosition>

                SynchronizeAction->LinkEndChild(TargetPosition);
                // </TargetPosition>

                // <FinalSpeed>
                tinyxml2::XMLElement *FinalSpeed = doc->NewElement("FinalSpeed");

                // <RelativeSpeedToMaster>
                tinyxml2::XMLElement *RelativeSpeedToMaster = doc->NewElement("RelativeSpeedToMaster");
                RelativeSpeedToMaster->SetAttribute("value", iter->action.synchronizeAction.relativeSpeedToMasterValue.c_str());
                RelativeSpeedToMaster->SetAttribute("speedTargetValueType", iter->action.synchronizeAction.speedTargetValueType.c_str());
                FinalSpeed->LinkEndChild(RelativeSpeedToMaster);
                // </RelativeSpeedToMaster>

                SynchronizeAction->LinkEndChild(TargetPosition);
                // </FinalSpeed>

                PrivateAction->LinkEndChild(SynchronizeAction);
                // </SynchronizeAction>

                Action->LinkEndChild(PrivateAction);
                // </PrivateAction>
                break;
            }
            case ROUTINGACTION: {
                // <PrivateAction>
                tinyxml2::XMLElement *PrivateAction = doc->NewElement("PrivateAction");
                
                // <RoutingAction>
                tinyxml2::XMLElement *RoutingAction = doc->NewElement("RoutingAction");
                
                // <AcquirePositionAction>
                tinyxml2::XMLElement *AcquirePositionAction = doc->NewElement("AcquirePositionAction");
                
                // <Position>
                tinyxml2::XMLElement *Position = doc->NewElement("Position");
                
                // <WorldPosition>, <LanePosition>
                if (iter->action.routingAction.position.positiontype == WORLD) {
                    tinyxml2::XMLElement *WorldPosition = doc->NewElement("WorldPosition");
                    WorldPosition->SetAttribute("x", iter->action.routingAction.position.worldPosition.x.c_str());
                    WorldPosition->SetAttribute("y", iter->action.routingAction.position.worldPosition.y.c_str());
                    WorldPosition->SetAttribute("z", iter->action.routingAction.position.worldPosition.z.c_str());
                    WorldPosition->SetAttribute("h", iter->action.routingAction.position.worldPosition.h.c_str());
                    Position->LinkEndChild(WorldPosition);
                }
                else if (iter->action.routingAction.position.positiontype == LANE) {
                    tinyxml2::XMLElement *LanePosition = doc->NewElement("LanePosition");
                    LanePosition->SetAttribute("roadId", iter->action.routingAction.position.lanePosition.roadId.c_str());
                    LanePosition->SetAttribute("laneId", iter->action.routingAction.position.lanePosition.laneId.c_str());
                    LanePosition->SetAttribute("offset", iter->action.routingAction.position.lanePosition.offset.c_str());
                    LanePosition->SetAttribute("s", iter->action.routingAction.position.lanePosition.s.c_str());
                    Position->LinkEndChild(LanePosition);
                }
                // </WorldPosition>, </LanePosition>
                
                PrivateAction->LinkEndChild(Position);
                // </Position>
                
                PrivateAction->LinkEndChild(AcquirePositionAction);
                // </AcquirePositionAction>
                
                PrivateAction->LinkEndChild(RoutingAction);
                // </RoutingAction>

                Action->LinkEndChild(PrivateAction);
                // </PrivateAction>
                break;
            }
            default: {
                break;
            }
        }

        Event->LinkEndChild(Action);
        // </Action>

        // <StartTrigger>
        tinyxml2::XMLElement *StartTrigger = doc->NewElement("StartTrigger");

        // <ConditionGroup>
        tinyxml2::XMLElement *ConditionGroup = doc->NewElement("ConditionGroup");
        for (auto it = iter->condition.begin(); it != iter->condition.end(); ++it) {
            // <Condition>
            tinyxml2::XMLElement *Condition = newConditionElement(doc, &(*it));
            ConditionGroup->LinkEndChild(Condition);
            // </Condition>
        }
        StartTrigger->LinkEndChild(ConditionGroup);
        // </ConditionGroup>

        Event->LinkEndChild(StartTrigger);
        // </StartTrigger>

        Maneuver->LinkEndChild(Event);
        // </Event>

        // </ParameterDeclaration>
    }

    ManeuverGroup->LinkEndChild(Maneuver);
    // </Maneuver>

    Act->LinkEndChild(ManeuverGroup);
    // </ManeuverGroup>

    // <StartTrigger>
    tinyxml2::XMLElement *StartTrigger = doc->NewElement("StartTrigger");

    // <ConditionGroup>
    tinyxml2::XMLElement *ConditionGroup = doc->NewElement("ConditionGroup");

    for (auto iter = s->startCondition.begin(); iter != s->startCondition.end(); ++iter) {
        // <Condition>
        tinyxml2::XMLElement *Condition = newConditionElement(doc, &(*iter));
        ConditionGroup->LinkEndChild(Condition);
        // </Condition>
    }
    
    // </ConditionGroup>
    StartTrigger->LinkEndChild(ConditionGroup);

    // </StartTrigger>
    Act->LinkEndChild(StartTrigger);

    // <StopTrigger>
    tinyxml2::XMLElement *StopTrigger = doc->NewElement("StopTrigger");

    // <ConditionGroup>
    ConditionGroup = doc->NewElement("ConditionGroup");

    for (auto iter = s->stopCondition.begin(); iter != s->stopCondition.end(); ++iter) {
        // <Condition>
        tinyxml2::XMLElement *Condition = newConditionElement(doc, &(*iter));
        ConditionGroup->LinkEndChild(Condition);
        // </Condition>
    }
    
    // </ConditionGroup>
    StopTrigger->LinkEndChild(ConditionGroup);

    // </StopTrigger>
    Act->LinkEndChild(StopTrigger);

    return SET_OK;
}

bool XOSC::saveXOSC()
{
    if (tinyxml2::XML_SUCCESS != doc->SaveFile(savepath)) {
        return false;
    }
    saveflag = true;
    return true;
}


void XOSC::test()
{
    tinyxml2::XMLElement  *elem = doc->FirstChildElement()->FirstChildElement();
    cout << elem->Name() << endl;
}
