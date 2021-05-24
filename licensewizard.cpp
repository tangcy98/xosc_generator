#include "licensewizard.h"
#include <QtWidgets>

static QVector< QString >  childfieldname;
static QVector< QWidget* >  childfieldwidget;
static QVector< const char * >  childfieldproperty;
static const char * vehname[] = {
    "vehicle.lincoln.mkz2017",
    "vehicle.tesla.model3",
    "vehicle.nissan.micra",
    "vehicle.audi.a2",
    "vehicle.audi.tt",
    "vehicle.bmw.grandtourer",
    "vehicle.citroen.c3",
    "vehicle.jeep.wrangler_rubicon",
    "vehicle.mercedes-benz.coupe"
    "vehicle.mini.cooperst",
    "vehicle.mustang.mustang",
    "vehicle.nissan.patrol",
    "vehicle.seat.leon",
    "vehicle.volkswagen.t2",
    "vehicle.toyota.prius",
    "vehicle.audi.etron"
};
static const char * pedname[] = {
    "walker.pedestrian.0001",
    "walker.pedestrian.0002",
    "walker.pedestrian.0003",
    "walker.pedestrian.0004",
    "walker.pedestrian.0005",
    "walker.pedestrian.0006",
    "walker.pedestrian.0007",
    "walker.pedestrian.0008",
    "walker.pedestrian.0009",
    "walker.pedestrian.0010",
    "walker.pedestrian.0011",
    "walker.pedestrian.0012",
    "walker.pedestrian.0013",
    "walker.pedestrian.0014",
    "walker.pedestrian.0015",
    "walker.pedestrian.0016",
    "walker.pedestrian.0017",
    "walker.pedestrian.0018",
    "walker.pedestrian.0018",
    "walker.pedestrian.0019",
    "walker.pedestrian.0020",
    "walker.pedestrian.0021",
    "walker.pedestrian.0022",
    "walker.pedestrian.0023",
    "walker.pedestrian.0024",
    "walker.pedestrian.0025",
    "walker.pedestrian.0026",
};
static const char * miscname[] = {
    "static.prop.container",
    "static.prop.advertisement",
    "static.prop.atm",
    "static.prop.barbeque",
    "static.prop.barrel"
    "static.prop.bench01",
    "static.prop.bench02",
    "static.prop.bench03",
    "static.prop.bike helmet",
    "static.prop.bin",
};
static const char * category[] = {
    "car",
    "pedestrian",
    "obstacle",
    "bicycle",
};

static QComboBox* BooleanQComboBox(bool defaultopt = true, QWidget *parent = nullptr)
{
    QComboBox *box = new QComboBox(parent);
    if (defaultopt) {
        box->addItem("true");
        box->addItem("false");
    }
    else {
        box->addItem("false");
        box->addItem("true");
    }
    return box;
}

static QComboBox* NumberQComboBox(int bottom, int top, QWidget *parent = nullptr)
{
    QComboBox *box = new QComboBox(parent);
    if (bottom >= top) return box;
    for (int i = bottom; i < top; ++i) {
        box->addItem(QString::number(i));
        box->setItemData(i, QVariant(i));
    }
    return box;
}

static QComboBox* RuleComboBox(int defaultopt = -1, QWidget *parent = nullptr)
{
    QComboBox *ruleComboBox = new QComboBox(parent);
    
    if (defaultopt < 0) {
        ruleComboBox->addItem("lessThan");
        ruleComboBox->addItem("greaterThan");
        ruleComboBox->addItem("equalTo");
    }
    else if (defaultopt > 0) {
        ruleComboBox->addItem("greaterThan");
        ruleComboBox->addItem("lessThan");
        ruleComboBox->addItem("equalTo");
    }
    else {
        ruleComboBox->addItem("equalTo");
        ruleComboBox->addItem("greaterThan");
        ruleComboBox->addItem("lessThan");
    }
    return ruleComboBox;
}

LicenseWizard::LicenseWizard(QWidget *parent)
    : QWizard(parent)
{
    tinyxml2::XMLDocument *doc = new tinyxml2::XMLDocument;
    tinyxml2::XMLDeclaration *declaration = doc->NewDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
    tinyxml2::XMLElement *OpenSCENARIO = doc->NewElement("OpenSCENARIO");
    doc->LinkEndChild(declaration);
    doc->LinkEndChild(OpenSCENARIO);

    setPage(Page_Intro, new IntroPage);
    setPage(Page_Filename, new FilenamePage);
    setPage(Page_Map, new MapPage);
    setPage(Page_Environment, new EnvironmentPage);
    setPage(Page_Actor, new ActorPage);
    setPage(Page_Story, new StoryPage);
    setPage(Page_Event, new EventPage);
    setPage(Page_StoryCondition, new StoryConditionPage);
    setPage(Page_StopTrigger, new StopTriggerPage);

    setStartId(Page_Intro);
    // if (doc->SaveFile("G:\\TiEV\thesis\\xosc_generator\\qt\\test.xosc") == 0) {
    //     setStartId(Page_Intro);
    // }
    // else {
    //     setStartId(Page_Filename);
    // }
    // setStartId(Page_Intro);

#ifndef Q_OS_MAC
    setWizardStyle(ModernStyle);
#endif
    setWindowTitle(tr("License Wizard"));
}

void LicenseWizard::accept()
{
    XOSC xosc;
    xosc.initXML();

    // begin - Filename
    string filename = field("Filename.filename").toString().toStdString();
    xosc.setFilename(filename.c_str());
    // end - Filename

    // begin - Map
    string map = field("Map.name").toString().toStdString();
    xosc.setMap(map.c_str());
    // end - Map

    // begin - Environment
    Environment env;
    env.name = field("Environment.name").toString().toStdString();
    env.animation = field("Environment.animation").toString().toStdString();
    env.dateTime = field("Environment.dateTime").toString().toStdString();
    env.cloudState = field("Environment.cloudState").toString().toStdString();
    env.sunintensity = field("Environment.sunintensity").toString().toStdString();
    env.azimuth = field("Environment.azimuth").toString().toStdString();
    env.elevation = field("Environment.elevation").toString().toStdString();
    env.visualRange = field("Environment.visualRange").toString().toStdString();
    env.precipitationType = field("Environment.precipitationType").toString().toStdString();
    env.precipitationintensity = field("Environment.precipitationintensity").toString().toStdString();
    env.frictionScaleFactor = field("Environment.frictionScaleFactor").toString().toStdString();
    xosc.setEnvironment(&env);
    // end - Environment

    // begin - Actor
    int actornum = field("Actor.num").toInt();
    xosc.setActorNum(actornum);
    QVector< Actor > actors(actornum);

    for (int i = 0; i < actornum; ++i) {
        QString prefix = "Actor.Actor"+QString::number(i)+".";
        QString type = field(prefix+"type").toString();
        if (type == "Vehicle") {
            actors[i].actortype = VEHICLE;
        }
        else if (type == "Pedestrian") {
            actors[i].actortype = PEDESTRIAN;
        }
        else {
            actors[i].actortype = MISCOBJECT;
        }
        actors[i].objname = field(prefix+"objectname").toString().toStdString();
        actors[i].name = field(prefix+"name").toString().toStdString();
        actors[i].category = field(prefix+"category").toString().toStdString();
        actors[i].boundingx = field(prefix+"boundingx").toString().toStdString();
        actors[i].boundingy = field(prefix+"boundingy").toString().toStdString();
        actors[i].boundingz = field(prefix+"boundingz").toString().toStdString();
        actors[i].boundingw = field(prefix+"boundingw").toString().toStdString();
        actors[i].boundingl = field(prefix+"boundingl").toString().toStdString();
        actors[i].boundingh = field(prefix+"boundingh").toString().toStdString();
        
        
        type = field(prefix+"Position.type").toString();
        if (type == "WorldPosition") {
            actors[i].position.positiontype = WORLD;
        }
        else {
            actors[i].position.positiontype = LANE;
        }
        actors[i].position.worldPosition.x = field(prefix+"Position.WorldPostion.x").toString().toStdString();
        actors[i].position.worldPosition.y = field(prefix+"Position.WorldPostion.y").toString().toStdString();
        actors[i].position.worldPosition.z = field(prefix+"Position.WorldPostion.z").toString().toStdString();
        actors[i].position.worldPosition.h = field(prefix+"Position.WorldPostion.h").toString().toStdString();
        actors[i].position.lanePosition.laneId = field(prefix+"Position.LanePosition.laneId").toString().toStdString();
        actors[i].position.lanePosition.roadId = field(prefix+"Position.LanePosition.roadId").toString().toStdString();
        actors[i].position.lanePosition.offset = field(prefix+"Position.LanePosition.offset").toString().toStdString();
        actors[i].position.lanePosition.s = field(prefix+"Position.LanePosition.s").toString().toStdString();

        int propsnum = field(prefix+"Properties.propertynumber").toInt();
        QString propprefix = prefix + "Properties.property";
        for (int j = 0; j < propsnum; ++j) {
            string name = field(propprefix+QString::number(j)+".name").toString().toStdString();
            string value = field(propprefix+QString::number(j)+".value").toString().toStdString();
            actors[i].props.push_back(make_pair(name, value));
        }

        QString vehprefix = prefix+"Vehicle.";
        
        actors[i].vehparas.maxSpeed = field(vehprefix+"maxSpeed").toString().toStdString();
        actors[i].vehparas.maxAcceleration = field(vehprefix+"maxAcceleration").toString().toStdString();
        actors[i].vehparas.maxDeceleration = field(vehprefix+"maxDeceleration").toString().toStdString();
        actors[i].vehparas.frontAxleMaxSteering = field(vehprefix+"frontAxleMaxSteering").toString().toStdString();
        actors[i].vehparas.frontAxleWheelDiameter = field(vehprefix+"frontAxleWheelDiameter").toString().toStdString();
        actors[i].vehparas.frontAxleTrackWidth = field(vehprefix+"frontAxleTrackWidth").toString().toStdString();
        actors[i].vehparas.frontAxlePositionX = field(vehprefix+"frontAxlePositionX").toString().toStdString();
        actors[i].vehparas.frontAxlePositionZ = field(vehprefix+"frontAxlePositionZ").toString().toStdString();
        actors[i].vehparas.rearAxleMaxSteering = field(vehprefix+"rearAxleMaxSteering").toString().toStdString();
        actors[i].vehparas.rearAxleWheelDiameter = field(vehprefix+"rearAxleWheelDiameter").toString().toStdString();
        actors[i].vehparas.rearAxleTrackWidth = field(vehprefix+"rearAxleTrackWidth").toString().toStdString();
        actors[i].vehparas.rearAxlePositionX = field(vehprefix+"rearAxlePositionX").toString().toStdString();
        actors[i].vehparas.rearAxlePositionZ = field(vehprefix+"rearAxlePositionZ").toString().toStdString();
        actors[i].vehparas.controllerName = field(vehprefix+"controllerName").toString().toStdString();
        
        propsnum = field(vehprefix+"ControllerProperties.propertynumber").toInt();
        propprefix = vehprefix + "ControllerProperties.property";
        for (int j = 0; j < propsnum; ++j) {
            string name = field(propprefix+QString::number(j)+".name").toString().toStdString();
            string value = field(propprefix+QString::number(j)+".value").toString().toStdString();
            actors[i].vehparas.controllerprops.push_back(make_pair(name, value));
        }
        actors[i].vehparas.Throttle = make_pair(field(vehprefix+"ThrottleValue").toString().toStdString(), field(vehprefix+"ThrottleActive").toString().toStdString());
        actors[i].vehparas.Brake = make_pair(field(vehprefix+"BrakeValue").toString().toStdString(), field(vehprefix+"BrakeActive").toString().toStdString());
        actors[i].vehparas.Clutch = make_pair(field(vehprefix+"ClutchValue").toString().toStdString(), field(vehprefix+"ClutchActive").toString().toStdString());
        actors[i].vehparas.ParkingBrake = make_pair(field(vehprefix+"ParkingBrakeValue").toString().toStdString(), field(vehprefix+"ParkingBrakeActive").toString().toStdString());
        actors[i].vehparas.SteeringWheel = make_pair(field(vehprefix+"SteeringWheelValue").toString().toStdString(), field(vehprefix+"SteeringWheelActive").toString().toStdString());
        actors[i].vehparas.Gear = make_pair(field(vehprefix+"GearNumber").toString().toStdString(), field(vehprefix+"GearActive").toString().toStdString());
        
        actors[i].pedparas.mass = field(prefix+"Pedestrian.mass").toString().toStdString();
        actors[i].pedparas.model = field(prefix+"name").toString().toStdString();

        actors[i].miscparas.mass = field(prefix+"MiscObject.mass").toString().toStdString();
        xosc.setActor(i, &actors[i]);
    }
    // end - Actor

    // begin - Story
    Story story;
    story.storyName = field("Story.storyName").toString().toStdString();
    story.actName = field("Story.actName").toString().toStdString();
    story.maneuverGroupName = field("Story.maneuverGroupName").toString().toStdString();
    story.maximumExecutionCount = field("Story.maximumExecutionCount").toString().toStdString();
    story.selectTriggeringEntities = field("Story.selectTriggeringEntities").toString().toStdString();
    story.entityRef = field("Actor."+field("Story.entityRef").toString()+".objectname").toString().toStdString();
    story.maneuverName = field("Story.maneuverName").toString().toStdString();
    
    int eventnum = field("Event.eventNum").toInt();
    for (int i = 0; i < eventnum; ++i) {
        Event event;
        event.condition.clear();
        QString prefix = "Event.Event"+QString::number(i)+".";
        event.name = field(prefix+"name").toString().toStdString();
        event.priority = field(prefix+"priority").toString().toStdString();
        event.action.name = field(prefix+"Action.name").toString().toStdString();
        QString type = field(prefix+"Action.type").toString();
        if (type == "EnvironmentAction") {
            event.action.actionType = ENVIRONMENTACTION;
        }
        else if (type == "LongitudinalAction") {
            event.action.actionType = LONGITUDINALACTION;
        }
        else if (type == "LateralAction") {
            event.action.actionType = LATERALACTION;
        }
        else if (type == "SynchronizeAction") {
            event.action.actionType = SYNCHRONIZEACTION;
        }
        else if (type == "RoutingAction") {
            event.action.actionType = ROUTINGACTION;
        }

        // EnvironmentAction
        event.action.environmentAction.environment.name = field(prefix+"Action.EnvironmentAction.Environment.name").toString().toStdString();
        event.action.environmentAction.environment.animation = field(prefix+"Action.EnvironmentAction.Environment.animation").toString().toStdString();
        event.action.environmentAction.environment.dateTime = field(prefix+"Action.EnvironmentAction.Environment.dateTime").toString().toStdString();
        event.action.environmentAction.environment.cloudState = field(prefix+"Action.EnvironmentAction.Environment.cloudState").toString().toStdString();
        event.action.environmentAction.environment.sunintensity = field(prefix+"Action.EnvironmentAction.Environment.sunintensity").toString().toStdString();
        event.action.environmentAction.environment.azimuth = field(prefix+"Action.EnvironmentAction.Environment.azimuth").toString().toStdString();
        event.action.environmentAction.environment.elevation = field(prefix+"Action.EnvironmentAction.Environment.elevation").toString().toStdString();
        event.action.environmentAction.environment.visualRange = field(prefix+"Action.EnvironmentAction.Environment.visualRange").toString().toStdString();
        event.action.environmentAction.environment.precipitationType = field(prefix+"Action.EnvironmentAction.Environment.precipitationType").toString().toStdString();
        event.action.environmentAction.environment.precipitationintensity = field(prefix+"Action.EnvironmentAction.Environment.precipitationintensity").toString().toStdString();
        event.action.environmentAction.environment.frictionScaleFactor = field(prefix+"Action.EnvironmentAction.Environment.frictionScaleFactor").toString().toStdString();

        // LongitudinalAction
        event.action.longitudinalAction.dynamicsShape = field(prefix+"Action.LongitudinalAction.dynamicsShape").toString().toStdString();
        event.action.longitudinalAction.dynamicsvalue = field(prefix+"Action.LongitudinalAction.dynamicsvalue").toString().toStdString();
        event.action.longitudinalAction.dynamicsDimension = field(prefix+"Action.LongitudinalAction.dynamicsDimension").toString().toStdString();
        event.action.longitudinalAction.targetvalue = field(prefix+"Action.LongitudinalAction.targetvalue").toString().toStdString();

        // LateralAction
        event.action.lateralAction.dynamicsShape = field(prefix+"Action.LateralAction.dynamicsShape").toString().toStdString();
        event.action.lateralAction.dynamicsvalue = field(prefix+"Action.LateralAction.dynamicsvalue").toString().toStdString();
        event.action.lateralAction.dynamicsDimension = field(prefix+"Action.LateralAction.dynamicsDimension").toString().toStdString();
        event.action.lateralAction.targetentityRef = field("Actor."+field(prefix+"Action.LateralAction.targetentityRef").toString()+".objectname").toString().toStdString();
        event.action.lateralAction.targetvalue = field(prefix+"Action.LateralAction.targetvalue").toString().toStdString();

        // SynchronizeAction
        event.action.synchronizeAction.masterEntityRef = field("Actor."+field(prefix+"Action.SynchronizeAction.masterEntityRef").toString()+".objectname").toString().toStdString();
        event.action.synchronizeAction.relativeSpeedToMasterValue = field(prefix+"Action.SynchronizeAction.relativeSpeedToMasterValue").toString().toStdString();
        event.action.synchronizeAction.speedTargetValueType = field(prefix+"Action.SynchronizeAction.speedTargetValueType").toString().toStdString();
        type = field(prefix+"Action.SynchronizeAction.targetPositionMaster.type").toString();
        if (type == "WorldPosition") {
            event.action.synchronizeAction.targetPositionMaster.positiontype = WORLD;
        }
        else {
            event.action.synchronizeAction.targetPositionMaster.positiontype = LANE;
        }
        event.action.synchronizeAction.targetPositionMaster.worldPosition.x = field(prefix+"Action.SynchronizeAction.targetPositionMaster.WorldPostion.x").toString().toStdString();
        event.action.synchronizeAction.targetPositionMaster.worldPosition.y = field(prefix+"Action.SynchronizeAction.targetPositionMaster.WorldPostion.y").toString().toStdString();
        event.action.synchronizeAction.targetPositionMaster.worldPosition.z = field(prefix+"Action.SynchronizeAction.targetPositionMaster.WorldPostion.z").toString().toStdString();
        event.action.synchronizeAction.targetPositionMaster.worldPosition.h = field(prefix+"Action.SynchronizeAction.targetPositionMaster.WorldPostion.h").toString().toStdString();
        event.action.synchronizeAction.targetPositionMaster.lanePosition.laneId = field(prefix+"Action.SynchronizeAction.targetPositionMaster.LanePosition.laneId").toString().toStdString();
        event.action.synchronizeAction.targetPositionMaster.lanePosition.roadId = field(prefix+"Action.SynchronizeAction.targetPositionMaster.LanePosition.roadId").toString().toStdString();
        event.action.synchronizeAction.targetPositionMaster.lanePosition.offset = field(prefix+"Action.SynchronizeAction.targetPositionMaster.LanePosition.offset").toString().toStdString();
        event.action.synchronizeAction.targetPositionMaster.lanePosition.s = field(prefix+"Action.SynchronizeAction.targetPositionMaster.LanePosition.s").toString().toStdString();
        type = field(prefix+"Action.SynchronizeAction.targetPosition.type").toString();
        if (type == "WorldPosition") {
            event.action.synchronizeAction.targetPosition.positiontype = WORLD;
        }
        else {
            event.action.synchronizeAction.targetPosition.positiontype = LANE;
        }
        event.action.synchronizeAction.targetPosition.worldPosition.x = field(prefix+"Action.SynchronizeAction.targetPosition.WorldPostion.x").toString().toStdString();
        event.action.synchronizeAction.targetPosition.worldPosition.y = field(prefix+"Action.SynchronizeAction.targetPosition.WorldPostion.y").toString().toStdString();
        event.action.synchronizeAction.targetPosition.worldPosition.z = field(prefix+"Action.SynchronizeAction.targetPosition.WorldPostion.z").toString().toStdString();
        event.action.synchronizeAction.targetPosition.worldPosition.h = field(prefix+"Action.SynchronizeAction.targetPosition.WorldPostion.h").toString().toStdString();
        event.action.synchronizeAction.targetPosition.lanePosition.laneId = field(prefix+"Action.SynchronizeAction.targetPosition.LanePosition.laneId").toString().toStdString();
        event.action.synchronizeAction.targetPosition.lanePosition.roadId = field(prefix+"Action.SynchronizeAction.targetPosition.LanePosition.roadId").toString().toStdString();
        event.action.synchronizeAction.targetPosition.lanePosition.offset = field(prefix+"Action.SynchronizeAction.targetPosition.LanePosition.offset").toString().toStdString();
        event.action.synchronizeAction.targetPosition.lanePosition.s = field(prefix+"Action.SynchronizeAction.targetPosition.LanePosition.s").toString().toStdString();

        // RoutingAction
        type = field(prefix+"Action.RoutingAction.Position.type").toString();
        if (type == "WorldPosition") {
            event.action.routingAction.position.positiontype = WORLD;
        }
        else {
            event.action.routingAction.position.positiontype = LANE;
        }
        event.action.routingAction.position.worldPosition.x = field(prefix+"Action.RoutingAction.Position.WorldPostion.x").toString().toStdString();
        event.action.routingAction.position.worldPosition.y = field(prefix+"Action.RoutingAction.Position.WorldPostion.y").toString().toStdString();
        event.action.routingAction.position.worldPosition.z = field(prefix+"Action.RoutingAction.Position.WorldPostion.z").toString().toStdString();
        event.action.routingAction.position.worldPosition.h = field(prefix+"Action.RoutingAction.Position.WorldPostion.h").toString().toStdString();
        event.action.routingAction.position.lanePosition.laneId = field(prefix+"Action.RoutingAction.Position.LanePosition.laneId").toString().toStdString();
        event.action.routingAction.position.lanePosition.roadId = field(prefix+"Action.RoutingAction.Position.LanePosition.roadId").toString().toStdString();
        event.action.routingAction.position.lanePosition.offset = field(prefix+"Action.RoutingAction.Position.LanePosition.offset").toString().toStdString();
        event.action.routingAction.position.lanePosition.s = field(prefix+"Action.RoutingAction.Position.LanePosition.s").toString().toStdString();

        int conditionnum = field(prefix+"conditionNum").toInt();
        for (int j = 0; j < conditionnum; ++j) {
            Condition condition;
            QString conditionprefix = prefix+"StartCondition"+QString::number(j)+".";
            condition.name = field(conditionprefix+"name").toString().toStdString();
            condition.delay = field(conditionprefix+"delay").toString().toStdString();
            condition.conditionEdge = field(conditionprefix+"conditionEdge").toString().toStdString();
            condition.triggeringEntityRef = field("Actor."+field(conditionprefix+"triggeringEntityRef").toString()+".objectname").toString().toStdString();
            QString type = field(conditionprefix+"type").toString();
            if (type == "ParameterCondition") {
                condition.type = PARAMETERCONDITION;
            }
            else if (type == "SimulationTimeCondition") {
                condition.type = SIMULATIONTIMECONDITION;
            }
            else if (type == "StoryboardElementStateCondition") {
                condition.type = STORYBOARDELEMENTSTATECONDITION;
            }
            else if (type == "StandStillCondition") {
                condition.type = STANDSTILLCONDITION;
            }
            else if (type == "TraveledDistanceCondition") {
                condition.type = TRAVELEDDISTANCECONDITION;
            }
            else if (type == "ReachPositionCondition") {
                condition.type = REACHPOSITIONCONDITION;
            }
            else if (type == "RelativeDistanceCondition") {
                condition.type = RELATIVEDISTANCECONDITION;
            }
            // ParameterCondition
            condition.parameterCondition.parameterRef = field(conditionprefix+"ParameterCondition.parameterRef").toString().toStdString();
            condition.parameterCondition.value = field(conditionprefix+"ParameterCondition.value").toString().toStdString();
            condition.parameterCondition.rule = field(conditionprefix+"ParameterCondition.rule").toString().toStdString();

            // SimulationTimeCondition
            condition.simulationTimeCondition.value = field(conditionprefix+"SimulationTimeCondition.value").toString().toStdString();
            condition.simulationTimeCondition.rule = field(conditionprefix+"SimulationTimeCondition.rule").toString().toStdString();

            // StoryboardElementStateCondition
            condition.storyboardElementStateCondition.storyboardElementType = field(conditionprefix+"StoryboardElementStateCondition.storyboardElementType").toString().toStdString();
            condition.storyboardElementStateCondition.storyboardElementRef = field("Event."+field(conditionprefix+"StoryboardElementStateCondition.storyboardElementRef").toString()+".Action.name").toString().toStdString();
            condition.storyboardElementStateCondition.state = field(conditionprefix+"StoryboardElementStateCondition.state").toString().toStdString();

            // StandStillCondition
            condition.standStillCondition.duration = field(conditionprefix+"StandStillCondition.duration").toString().toStdString();

            // TraveledDistanceCondition
            condition.traveledDistanceCondition.value = field(conditionprefix+"TraveledDistanceCondition.value").toString().toStdString();

            // ReachPositionCondition
            condition.reachPositionCondition.tolerance = field(conditionprefix+"ReachPositionCondition.tolerance").toString().toStdString();
            type = field(conditionprefix+"ReachPositionCondition.Position.type").toString();
            if (type == "WorldPosition") {
                condition.reachPositionCondition.position.positiontype = WORLD;
            }
            else {
                condition.reachPositionCondition.position.positiontype = LANE;
            }
            condition.reachPositionCondition.position.worldPosition.x = field(conditionprefix+"ReachPositionCondition.Position.WorldPostion.x").toString().toStdString();
            condition.reachPositionCondition.position.worldPosition.y = field(conditionprefix+"ReachPositionCondition.Position.WorldPostion.y").toString().toStdString();
            condition.reachPositionCondition.position.worldPosition.z = field(conditionprefix+"ReachPositionCondition.Position.WorldPostion.z").toString().toStdString();
            condition.reachPositionCondition.position.worldPosition.h = field(conditionprefix+"ReachPositionCondition.Position.WorldPostion.h").toString().toStdString();
            condition.reachPositionCondition.position.lanePosition.laneId = field(conditionprefix+"ReachPositionCondition.Position.LanePosition.laneId").toString().toStdString();
            condition.reachPositionCondition.position.lanePosition.roadId = field(conditionprefix+"ReachPositionCondition.Position.LanePosition.roadId").toString().toStdString();
            condition.reachPositionCondition.position.lanePosition.offset = field(conditionprefix+"ReachPositionCondition.Position.LanePosition.offset").toString().toStdString();
            condition.reachPositionCondition.position.lanePosition.s = field(conditionprefix+"ReachPositionCondition.Position.LanePosition.s").toString().toStdString();

            // RelativeDistanceCondition
            condition.relativeDistanceCondition.entityRef = field("Actor."+field(conditionprefix+"RelativeDistanceCondition.entityRef").toString()+".objectname").toString().toStdString();
            condition.relativeDistanceCondition.relativeDistanceType = field(conditionprefix+"RelativeDistanceCondition.relativeDistanceType").toString().toStdString();
            condition.relativeDistanceCondition.value = field(conditionprefix+"RelativeDistanceCondition.value").toString().toStdString();
            condition.relativeDistanceCondition.freespace = field(conditionprefix+"RelativeDistanceCondition.freespace").toString().toStdString();
            condition.relativeDistanceCondition.rule = field(conditionprefix+"RelativeDistanceCondition.rule").toString().toStdString();
            event.condition.push_back(condition);
        }
        story.eventlist.push_back(event);
    }

    int conditionnum = field("Story.startConditionNum").toInt();
    for (int i = 0; i < conditionnum; ++i) {
        Condition condition;
        QString conditionprefix = "Story.StartCondition"+QString::number(i)+".";
        condition.name = field(conditionprefix+"name").toString().toStdString();
        condition.delay = field(conditionprefix+"delay").toString().toStdString();
        condition.conditionEdge = field(conditionprefix+"conditionEdge").toString().toStdString();
        condition.triggeringEntityRef = field("Actor."+field(conditionprefix+"triggeringEntityRef").toString()+".objectname").toString().toStdString();
        QString type = field(conditionprefix+"type").toString();
        if (type == "ParameterCondition") {
            condition.type = PARAMETERCONDITION;
        }
        else if (type == "SimulationTimeCondition") {
            condition.type = SIMULATIONTIMECONDITION;
        }
        else if (type == "StoryboardElementStateCondition") {
            condition.type = STORYBOARDELEMENTSTATECONDITION;
        }
        else if (type == "StandStillCondition") {
            condition.type = STANDSTILLCONDITION;
        }
        else if (type == "TraveledDistanceCondition") {
            condition.type = TRAVELEDDISTANCECONDITION;
        }
        else if (type == "ReachPositionCondition") {
            condition.type = REACHPOSITIONCONDITION;
        }
        else if (type == "RelativeDistanceCondition") {
            condition.type = RELATIVEDISTANCECONDITION;
        }
        // ParameterCondition
        condition.parameterCondition.parameterRef = field(conditionprefix+"ParameterCondition.parameterRef").toString().toStdString();
        condition.parameterCondition.value = field(conditionprefix+"ParameterCondition.value").toString().toStdString();
        condition.parameterCondition.rule = field(conditionprefix+"ParameterCondition.rule").toString().toStdString();

        // SimulationTimeCondition
        condition.simulationTimeCondition.value = field(conditionprefix+"SimulationTimeCondition.value").toString().toStdString();
        condition.simulationTimeCondition.rule = field(conditionprefix+"SimulationTimeCondition.rule").toString().toStdString();

        // StoryboardElementStateCondition
        condition.storyboardElementStateCondition.storyboardElementType = field(conditionprefix+"StoryboardElementStateCondition.storyboardElementType").toString().toStdString();
        condition.storyboardElementStateCondition.storyboardElementRef = field("Event."+field(conditionprefix+"StoryboardElementStateCondition.storyboardElementRef").toString()+".Action.name").toString().toStdString();
        condition.storyboardElementStateCondition.state = field(conditionprefix+"StoryboardElementStateCondition.state").toString().toStdString();

        // StandStillCondition
        condition.standStillCondition.duration = field(conditionprefix+"StandStillCondition.duration").toString().toStdString();

        // TraveledDistanceCondition
        condition.traveledDistanceCondition.value = field(conditionprefix+"TraveledDistanceCondition.value").toString().toStdString();

        // ReachPositionCondition
        condition.reachPositionCondition.tolerance = field(conditionprefix+"ReachPositionCondition.tolerance").toString().toStdString();
        type = field(conditionprefix+"ReachPositionCondition.Position.type").toString();
        if (type == "WorldPosition") {
            condition.reachPositionCondition.position.positiontype = WORLD;
        }
        else {
            condition.reachPositionCondition.position.positiontype = LANE;
        }
        condition.reachPositionCondition.position.worldPosition.x = field(conditionprefix+"ReachPositionCondition.Position.WorldPostion.x").toString().toStdString();
        condition.reachPositionCondition.position.worldPosition.y = field(conditionprefix+"ReachPositionCondition.Position.WorldPostion.y").toString().toStdString();
        condition.reachPositionCondition.position.worldPosition.z = field(conditionprefix+"ReachPositionCondition.Position.WorldPostion.z").toString().toStdString();
        condition.reachPositionCondition.position.worldPosition.h = field(conditionprefix+"ReachPositionCondition.Position.WorldPostion.h").toString().toStdString();
        condition.reachPositionCondition.position.lanePosition.laneId = field(conditionprefix+"ReachPositionCondition.Position.LanePosition.laneId").toString().toStdString();
        condition.reachPositionCondition.position.lanePosition.roadId = field(conditionprefix+"ReachPositionCondition.Position.LanePosition.roadId").toString().toStdString();
        condition.reachPositionCondition.position.lanePosition.offset = field(conditionprefix+"ReachPositionCondition.Position.LanePosition.offset").toString().toStdString();
        condition.reachPositionCondition.position.lanePosition.s = field(conditionprefix+"ReachPositionCondition.Position.LanePosition.s").toString().toStdString();

        // RelativeDistanceCondition
        condition.relativeDistanceCondition.entityRef = field("Actor."+field(conditionprefix+"RelativeDistanceCondition.entityRef").toString()+".objectname").toString().toStdString();
        condition.relativeDistanceCondition.relativeDistanceType = field(conditionprefix+"RelativeDistanceCondition.relativeDistanceType").toString().toStdString();
        condition.relativeDistanceCondition.value = field(conditionprefix+"RelativeDistanceCondition.value").toString().toStdString();
        condition.relativeDistanceCondition.freespace = field(conditionprefix+"RelativeDistanceCondition.freespace").toString().toStdString();
        condition.relativeDistanceCondition.rule = field(conditionprefix+"RelativeDistanceCondition.rule").toString().toStdString();
        story.startCondition.push_back(condition);
    }

    conditionnum = field("Story.stopConditionNum").toInt();
    for (int i = 0; i < conditionnum; ++i) {
        Condition condition;
        QString conditionprefix = "Story.StopCondition"+QString::number(i)+".";
        condition.name = field(conditionprefix+"name").toString().toStdString();
        condition.delay = field(conditionprefix+"delay").toString().toStdString();
        condition.conditionEdge = field(conditionprefix+"conditionEdge").toString().toStdString();
        condition.triggeringEntityRef = field("Actor."+field(conditionprefix+"triggeringEntityRef").toString()+".objectname").toString().toStdString();
        QString type = field(conditionprefix+"type").toString();
        if (type == "ParameterCondition") {
            condition.type = PARAMETERCONDITION;
        }
        else if (type == "SimulationTimeCondition") {
            condition.type = SIMULATIONTIMECONDITION;
        }
        else if (type == "StoryboardElementStateCondition") {
            condition.type = STORYBOARDELEMENTSTATECONDITION;
        }
        else if (type == "StandStillCondition") {
            condition.type = STANDSTILLCONDITION;
        }
        else if (type == "TraveledDistanceCondition") {
            condition.type = TRAVELEDDISTANCECONDITION;
        }
        else if (type == "ReachPositionCondition") {
            condition.type = REACHPOSITIONCONDITION;
        }
        else if (type == "RelativeDistanceCondition") {
            condition.type = RELATIVEDISTANCECONDITION;
        }
        // ParameterCondition
        condition.parameterCondition.parameterRef = field(conditionprefix+"ParameterCondition.parameterRef").toString().toStdString();
        condition.parameterCondition.value = field(conditionprefix+"ParameterCondition.value").toString().toStdString();
        condition.parameterCondition.rule = field(conditionprefix+"ParameterCondition.rule").toString().toStdString();

        // SimulationTimeCondition
        condition.simulationTimeCondition.value = field(conditionprefix+"SimulationTimeCondition.value").toString().toStdString();
        condition.simulationTimeCondition.rule = field(conditionprefix+"SimulationTimeCondition.rule").toString().toStdString();

        // StoryboardElementStateCondition
        condition.storyboardElementStateCondition.storyboardElementType = field(conditionprefix+"StoryboardElementStateCondition.storyboardElementType").toString().toStdString();
        condition.storyboardElementStateCondition.storyboardElementRef = field("Event."+field(conditionprefix+"StoryboardElementStateCondition.storyboardElementRef").toString()+".Action.name").toString().toStdString();
        condition.storyboardElementStateCondition.state = field(conditionprefix+"StoryboardElementStateCondition.state").toString().toStdString();

        // StandStillCondition
        condition.standStillCondition.duration = field(conditionprefix+"StandStillCondition.duration").toString().toStdString();

        // TraveledDistanceCondition
        condition.traveledDistanceCondition.value = field(conditionprefix+"TraveledDistanceCondition.value").toString().toStdString();

        // ReachPositionCondition
        condition.reachPositionCondition.tolerance = field(conditionprefix+"ReachPositionCondition.tolerance").toString().toStdString();
        type = field(conditionprefix+"ReachPositionCondition.Position.type").toString();
        if (type == "WorldPosition") {
            condition.reachPositionCondition.position.positiontype = WORLD;
        }
        else {
            condition.reachPositionCondition.position.positiontype = LANE;
        }
        condition.reachPositionCondition.position.worldPosition.x = field(conditionprefix+"ReachPositionCondition.Position.WorldPostion.x").toString().toStdString();
        condition.reachPositionCondition.position.worldPosition.y = field(conditionprefix+"ReachPositionCondition.Position.WorldPostion.y").toString().toStdString();
        condition.reachPositionCondition.position.worldPosition.z = field(conditionprefix+"ReachPositionCondition.Position.WorldPostion.z").toString().toStdString();
        condition.reachPositionCondition.position.worldPosition.h = field(conditionprefix+"ReachPositionCondition.Position.WorldPostion.h").toString().toStdString();
        condition.reachPositionCondition.position.lanePosition.laneId = field(conditionprefix+"ReachPositionCondition.Position.LanePosition.laneId").toString().toStdString();
        condition.reachPositionCondition.position.lanePosition.roadId = field(conditionprefix+"ReachPositionCondition.Position.LanePosition.roadId").toString().toStdString();
        condition.reachPositionCondition.position.lanePosition.offset = field(conditionprefix+"ReachPositionCondition.Position.LanePosition.offset").toString().toStdString();
        condition.reachPositionCondition.position.lanePosition.s = field(conditionprefix+"ReachPositionCondition.Position.LanePosition.s").toString().toStdString();

        // RelativeDistanceCondition
        condition.relativeDistanceCondition.entityRef = field("Actor."+field(conditionprefix+"RelativeDistanceCondition.entityRef").toString()+".objectname").toString().toStdString();
        condition.relativeDistanceCondition.relativeDistanceType = field(conditionprefix+"RelativeDistanceCondition.relativeDistanceType").toString().toStdString();
        condition.relativeDistanceCondition.value = field(conditionprefix+"RelativeDistanceCondition.value").toString().toStdString();
        condition.relativeDistanceCondition.freespace = field(conditionprefix+"RelativeDistanceCondition.freespace").toString().toStdString();
        condition.relativeDistanceCondition.rule = field(conditionprefix+"RelativeDistanceCondition.rule").toString().toStdString();
        story.stopCondition.push_back(condition);
    }
    xosc.setStory(&story);
    // end - Story

    // begin - StopTrigger
    string DrivenDistance = field("StopTrigger.DrivenDistanceLineEdit").toString().toStdString();
    StopTrigger stoptrigger(
        field("StopTrigger.criteria_RunningStopTestCheckBox").toBool(),
        field("StopTrigger.criteria_RunningRedLightTestCheckBox").toBool(),
        field("StopTrigger.criteria_WrongLaneTestCheckBox").toBool(),
        field("StopTrigger.criteria_OnSidewalkTestCheckBox").toBool(),
        field("StopTrigger.criteria_KeepLaneTestCheckBox").toBool(),
        field("StopTrigger.criteria_CollisionTestCheckBox").toBool(),
        field("StopTrigger.criteria_DrivenDistanceTestCheckBox").toBool(),
        DrivenDistance.c_str()
    );
    xosc.setStopTrigger(&stoptrigger);
    // end - StopTrigger

    QDialog::accept();
}

IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Introduction"));

    topLabel = new QLabel(tr("This wizard will help you create your own "
                             "<i>OpenScenario</i>&trade; file "
                             "for test in Carla."));
    topLabel->setWordWrap(true);


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(topLabel);
    setLayout(layout);
}
int IntroPage::nextId() const
{
    return LicenseWizard::Page_Filename;
}

FilenamePage::FilenamePage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Set <i>OpenScenario</i>&trade; file name"));
    setSubTitle(tr("Please set the file name which can "
                   "simply describe the scenario."));

    filenameLabel = new QLabel(tr("Filename:"));
    filenameLineEdit = new QLineEdit;
    filenameExampleLabel = new QLabel(tr("(Example: FollowLeadingVehicle.xosc)"));

    fieldprefix = "Filename.";
    registerField(fieldprefix+"filename*", filenameLineEdit);

    QVector<QString>::iterator itername;
    QVector<QWidget*>::iterator iterwidget;
    QVector<const char*>::iterator iterproperty;
    for (itername = childfieldname.begin(), iterwidget = childfieldwidget.begin(), iterproperty = childfieldproperty.begin();
      itername != childfieldname.end() && iterwidget!= childfieldwidget.end() && iterproperty != childfieldproperty.end();
      ++itername, ++iterwidget, ++iterproperty
    ) {
        registerField(*itername, *iterwidget, *iterproperty);
    }
    childfieldname.clear();
    childfieldwidget.clear();
    childfieldproperty.clear();

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(filenameLabel, 0, 0);
    layout->addWidget(filenameLineEdit, 0, 1);
    layout->addWidget(filenameExampleLabel, 1, 1);
    setLayout(layout);
}

int FilenamePage::nextId() const
{
    return LicenseWizard::Page_Map;
    // if (field("filename.filename").toString() == "123") {
    //     return LicenseWizard::Page_Environment;
    // }
    // else {
    //     return LicenseWizard::Page_Actor;
    // }
}

MapPage::MapPage(QWidget *parent)
    : QWizardPage(parent)
{
    const char *towns[] = { "Town01", "Town02", "Town03", "Town04", 
                            "Town05", "Town06", "Town07", "Town10HD" };
    setTitle(tr("Choose a map in Carla"));
    setSubTitle(tr("Firstly you have to choose a map."));

    nameLabel = new QLabel(tr("Map:"));
    nameComboBox = new QComboBox;
    for (size_t i = 0; i < sizeof(towns) / sizeof(const char *); ++i) {
        nameComboBox->addItem(towns[i]);
    }
    fieldprefix = "Map.";
    registerField(fieldprefix + "name", nameComboBox, "currentText");
    QVector<QString>::iterator itername;
    QVector<QWidget*>::iterator iterwidget;
    QVector<const char*>::iterator iterproperty;
    for (itername = childfieldname.begin(), iterwidget = childfieldwidget.begin(), iterproperty = childfieldproperty.begin();
      itername != childfieldname.end() && iterwidget!= childfieldwidget.end() && iterproperty != childfieldproperty.end();
      ++itername, ++iterwidget, ++iterproperty
    ) {
        registerField(*itername, *iterwidget, *iterproperty);
    }
    childfieldname.clear();
    childfieldwidget.clear();
    childfieldproperty.clear();

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameComboBox, 0, 1);
    setLayout(layout);
}

int MapPage::nextId() const
{
    return LicenseWizard::Page_Environment;
}

EnvironmentGroupBox::EnvironmentGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    nameLabel = new QLabel(tr("name:"));
    nameLineEdit = new QLineEdit;
    nameLineEdit->setText("Environment1");

    animationLabel = new QLabel(tr("animation:"));
    animationComboBox = BooleanQComboBox(false);

    dateTimeLabel = new QLabel(tr("dateTime:"));
    dateTimeLineEdit = new QLineEdit;
    dateTimeLineEdit->setText("2019-06-25T12:00:00");

    cloudStateLabel = new QLabel(tr("cloudState:"));
    cloudStateComboBox = new QComboBox;
    cloudStateComboBox->addItem("free");
    cloudStateComboBox->addItem("skyOff");
    cloudStateComboBox->addItem("cloudy");
    cloudStateComboBox->addItem("overcast");
    cloudStateComboBox->addItem("rainy");

    sunintensityLabel = new QLabel(tr("sunintensity[0,inf):"));
    sunintensityLineEdit = new QLineEdit;
    sunintensityLineEdit->setText("0.35");
    sunintensityLineEdit->setValidator(new QDoubleValidator(this));

    azimuthLabel = new QLabel(tr("azimuth[0,2PI]:"));
    azimuthLineEdit = new QLineEdit;
    azimuthLineEdit->setText("0");
    azimuthLineEdit->setValidator(new QDoubleValidator(this));

    elevationLabel = new QLabel(tr("elevation:[-PI,PI]"));
    elevationLineEdit = new QLineEdit;
    elevationLineEdit->setText("1.31");
    elevationLineEdit->setValidator(new QDoubleValidator(this));

    visualRangeLabel = new QLabel(tr("visualRange[0,inf):"));
    visualRangeLineEdit = new QLineEdit;
    visualRangeLineEdit->setText("100000.0");
    visualRangeLineEdit->setValidator(new QDoubleValidator(this));

    precipitationTypeLabel = new QLabel(tr("precipitationType:"));
    precipitationTypeComboBox = new QComboBox;
    precipitationTypeComboBox->addItem("dry");
    precipitationTypeComboBox->addItem("rain");
    precipitationTypeComboBox->addItem("snow");

    precipitationintensityLabel = new QLabel(tr("precipitationintensity[0,1]:"));
    precipitationintensityLineEdit = new QLineEdit;
    precipitationintensityLineEdit->setText("0.1");
    precipitationintensityLineEdit->setValidator(new QDoubleValidator(this));

    frictionScaleFactorLabel = new QLabel(tr("frictionScaleFactor[0,inf):"));
    frictionScaleFactorLineEdit = new QLineEdit;
    frictionScaleFactorLineEdit->setText("1.0");
    frictionScaleFactorLineEdit->setValidator(new QDoubleValidator(this));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(animationLabel, 1, 0);
    layout->addWidget(dateTimeLabel, 2, 0);
    layout->addWidget(cloudStateLabel, 3, 0);
    layout->addWidget(sunintensityLabel, 4, 0);
    layout->addWidget(azimuthLabel, 5, 0);
    layout->addWidget(elevationLabel, 6, 0);
    layout->addWidget(visualRangeLabel, 7, 0);
    layout->addWidget(precipitationTypeLabel, 8, 0);
    layout->addWidget(precipitationintensityLabel, 9, 0);
    layout->addWidget(frictionScaleFactorLabel, 10, 0);

    layout->addWidget(nameLineEdit, 0, 1);
    layout->addWidget(animationComboBox, 1, 1);
    layout->addWidget(dateTimeLineEdit, 2, 1);
    layout->addWidget(cloudStateComboBox, 3, 1);
    layout->addWidget(sunintensityLineEdit, 4, 1);
    layout->addWidget(azimuthLineEdit, 5, 1);
    layout->addWidget(elevationLineEdit, 6, 1);
    layout->addWidget(visualRangeLineEdit, 7, 1);
    layout->addWidget(precipitationTypeComboBox, 8, 1);
    layout->addWidget(precipitationintensityLineEdit, 9, 1);
    layout->addWidget(frictionScaleFactorLineEdit, 10, 1);

    registerField(fieldprefix + "name", nameLineEdit);
    registerField(fieldprefix + "animation", animationComboBox, "currentText");
    registerField(fieldprefix + "dateTime", dateTimeLineEdit);
    registerField(fieldprefix + "cloudState", cloudStateComboBox, "currentText");
    registerField(fieldprefix + "sunintensity", sunintensityLineEdit);
    registerField(fieldprefix + "azimuth", azimuthLineEdit);
    registerField(fieldprefix + "elevation", elevationLineEdit);
    registerField(fieldprefix + "visualRange", visualRangeLineEdit);
    registerField(fieldprefix + "precipitationType", precipitationTypeComboBox, "currentText");
    registerField(fieldprefix + "precipitationintensity", precipitationintensityLineEdit);
    registerField(fieldprefix + "frictionScaleFactor", frictionScaleFactorLineEdit);

    setLayout(layout);
}
EnvironmentPage::EnvironmentPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Fill In Your Environment"));
    setSubTitle(tr("Please fill all the fields. Make sure to provide a valid "
                   "input and recommended values are already given."));
    fieldprefix = "Environment.";
    environmentGroupBox = new EnvironmentGroupBox(fieldprefix, this);
    QVector<QString>::iterator itername;
    QVector<QWidget*>::iterator iterwidget;
    QVector<const char*>::iterator iterproperty;
    for (itername = childfieldname.begin(), iterwidget = childfieldwidget.begin(), iterproperty = childfieldproperty.begin();
      itername != childfieldname.end() && iterwidget!= childfieldwidget.end() && iterproperty != childfieldproperty.end();
      ++itername, ++iterwidget, ++iterproperty
    ) {
        registerField(*itername, *iterwidget, *iterproperty);
    }
    childfieldname.clear();
    childfieldwidget.clear();
    childfieldproperty.clear();
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(environmentGroupBox, 0, 0);
    setLayout(layout);
}

int EnvironmentPage::nextId() const
{
    return LicenseWizard::Page_Actor;
}
XOSCGroupBox::XOSCGroupBox(QString str, QWidget *parent) : QGroupBox(parent)
{
    fieldprefix = str;
}

void XOSCGroupBox::registerField(QString str, QWidget *widget,const char * property)
{
    childfieldname.append(str);
    childfieldwidget.append(widget);
    childfieldproperty.append(property);
}

WorldPositionGroupBox::WorldPositionGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    setTitle("WorldPosition");
    xLabel = new QLabel(tr("x:"));
    xLineEdit = new QLineEdit(tr("0.0"));
    yLabel = new QLabel(tr("y:"));;
    yLineEdit = new QLineEdit(tr("0.0"));;
    zLabel = new QLabel(tr("z:"));;
    zLineEdit = new QLineEdit(tr("0.0"));;
    hLabel = new QLabel(tr("h:"));;
    hLineEdit = new QLineEdit(tr("0.0"));;

    registerField(fieldprefix + "x", xLineEdit);
    registerField(fieldprefix + "y", yLineEdit);
    registerField(fieldprefix + "z", zLineEdit);
    registerField(fieldprefix + "h", hLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(xLabel, 0, 0);
    layout->addWidget(xLineEdit, 0, 1);
    layout->addWidget(yLabel, 1, 0);
    layout->addWidget(yLineEdit, 1, 1);
    layout->addWidget(zLabel, 2, 0);
    layout->addWidget(zLineEdit, 2, 1);
    layout->addWidget(hLabel, 3, 0);
    layout->addWidget(hLineEdit, 3, 1);
    setLayout(layout);
}
LanePositionGroupBox::LanePositionGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    setTitle("LanePosition");
    roadIdLabel = new QLabel(tr("roadId:"));
    roadIdLineEdit = new QLineEdit(tr("4"));
    laneIdLabel = new QLabel(tr("laneId:"));;
    laneIdLineEdit = new QLineEdit(tr("-1"));;
    offsetLabel = new QLabel(tr("offset:"));;
    offsetLineEdit = new QLineEdit(tr("1.0"));;
    sLabel = new QLabel(tr("s:"));;
    sLineEdit = new QLineEdit(tr("48.58"));;

    registerField(fieldprefix + "roadId", roadIdLineEdit);
    registerField(fieldprefix + "laneId", laneIdLineEdit);
    registerField(fieldprefix + "offset", offsetLineEdit);
    registerField(fieldprefix + "s", sLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(roadIdLabel, 0, 0);
    layout->addWidget(roadIdLineEdit, 0, 1);
    layout->addWidget(laneIdLabel, 1, 0);
    layout->addWidget(laneIdLineEdit, 1, 1);
    layout->addWidget(offsetLabel, 2, 0);
    layout->addWidget(offsetLineEdit, 2, 1);
    layout->addWidget(sLabel, 3, 0);
    layout->addWidget(sLineEdit, 3, 1);
    setLayout(layout);
}
PositionGroupBox::PositionGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    setTitle("Position");
    typeLabel = new QLabel(tr("type:"));
    typeComboBox = new QComboBox;
    typeComboBox->addItem("WorldPosition");
    typeComboBox->addItem("LanePosition");
    worldPositionGroupBox = new WorldPositionGroupBox(fieldprefix + "WorldPostion.", this);
    lanePositionGroupBox = new LanePositionGroupBox(fieldprefix + "LanePosition.", this);

    registerField(fieldprefix + "type", typeComboBox, "currentText");

    connect(typeComboBox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(updatePositionType()));

    if (typeComboBox->currentText() == "WorldPosition") {
        worldPositionGroupBox->setVisible(true);
        lanePositionGroupBox->setVisible(false);
    }
    else {
        worldPositionGroupBox->setVisible(false);
        lanePositionGroupBox->setVisible(true);
    }
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(typeLabel, 0, 0);
    layout->addWidget(typeComboBox, 0, 1);
    layout->addWidget(worldPositionGroupBox, 1, 0, 1, 2);
    layout->addWidget(lanePositionGroupBox, 2, 0, 1, 2);
    setLayout(layout);
}
void PositionGroupBox::updatePositionType()
{
    if (typeComboBox->currentText() == "WorldPosition") {
        worldPositionGroupBox->setVisible(true);
        lanePositionGroupBox->setVisible(false);
    }
    else {
        worldPositionGroupBox->setVisible(false);
        lanePositionGroupBox->setVisible(true);
    }
}

PropertiesGroupBox::PropertiesGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    propertynumberLabel = new QLabel(tr("number of properties:"));
    propertynumberComboBox = NumberQComboBox(MINPROPNUM, MAXPROPNUM);
    registerField(fieldprefix + "propertynumber", propertynumberComboBox, "currentText");
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(propertynumberLabel, 0, 0);
    layout->addWidget(propertynumberComboBox, 0, 1);
    connect(propertynumberComboBox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(updateProperties()));
    int currentnum = propertynumberComboBox->currentText().toInt();
    for (int i = 0; i < MAXPROPNUM; ++i) {
        QLabel *nameLabel = new QLabel("property" + QString::number(i) + " name:");
        QLabel *valueLabel = new QLabel("property" + QString::number(i) + " value:");;
        QLineEdit *nameLineEdit = new QLineEdit;
        QLineEdit *valueLineEdit = new QLineEdit;

        propertynameLabel.append(nameLabel);
        propertynameLineEdit.append(nameLineEdit);
        propertyvalueLabel.append(valueLabel);
        propertyvalueLineEdit.append(valueLineEdit);
        if (i < currentnum) {
            nameLabel->setVisible(true);
            nameLineEdit->setVisible(true);
            valueLabel->setVisible(true);
            valueLineEdit->setVisible(true);
        }
        else {
            nameLabel->setVisible(false);
            nameLineEdit->setVisible(false);
            valueLabel->setVisible(false);
            valueLineEdit->setVisible(false);
        }
        registerField(fieldprefix + "property" + QString::number(i) + ".name", nameLineEdit);
        registerField(fieldprefix + "property" + QString::number(i) + ".value", valueLineEdit);
        layout->addWidget(nameLabel, 2*i + 1, 0);
        layout->addWidget(nameLineEdit, 2*i + 1, 1);
        layout->addWidget(valueLabel, 2*i + 2, 0);
        layout->addWidget(valueLineEdit, 2*i + 2, 1);
    }
    setLayout(layout);
}
void PropertiesGroupBox::updateProperties()
{
    int currentnum = propertynumberComboBox->currentText().toInt();
    for (int i = 0; i < MAXPROPNUM; ++i) {
        if (i < currentnum) {
            propertynameLabel[i]->setVisible(true);
            propertynameLineEdit[i]->setVisible(true);
            propertyvalueLabel[i]->setVisible(true);
            propertyvalueLineEdit[i]->setVisible(true);
        }
        else {
            propertynameLabel[i]->setVisible(false);
            propertynameLineEdit[i]->setVisible(false);
            propertyvalueLabel[i]->setVisible(false);
            propertyvalueLineEdit[i]->setVisible(false);
        }
    }
}
VehicleGroupBox::VehicleGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    setTitle("Vehicle Parameters");
    controllerPropertiesGroupBox = new PropertiesGroupBox(fieldprefix + "ControllerProperties.", this);

    controllerPropertiesGroupBox->setTitle("Controller Properties");

    maxSpeedLabel = new QLabel("maxSpeed:");
    maxAccelerationLabel = new QLabel("maxAcceleration:");
    maxDecelerationLabel = new QLabel("maxDeceleration:");
    frontAxleMaxSteeringLabel = new QLabel("frontAxleMaxSteering:");
    frontAxleWheelDiameterLabel = new QLabel("frontAxleWheelDiameter:");
    frontAxleTrackWidthLabel = new QLabel("frontAxleTrackWidth:");
    frontAxlePositionXLabel = new QLabel("frontAxlePositionX:");
    frontAxlePositionZLabel = new QLabel("frontAxlePositionZ:");
    rearAxleMaxSteeringLabel = new QLabel("rearAxleMaxSteering:");
    rearAxleWheelDiameterLabel = new QLabel("rearAxleWheelDiameter:");
    rearAxleTrackWidthLabel = new QLabel("rearAxleTrackWidth:");
    rearAxlePositionXLabel = new QLabel("rearAxlePositionX:");
    rearAxlePositionZLabel = new QLabel("rearAxlePositionZ:");
    controllerNameLabel = new QLabel("controllerName:");
    ThrottleValueLabel = new QLabel("ThrottleValue[0,1]:");
    ThrottleActiveLabel = new QLabel("ThrottleActive:");
    BrakeValueLabel = new QLabel("BrakeValue[0,1]:");
    BrakeActiveLabel = new QLabel("BrakeActive:");
    ClutchValueLabel = new QLabel("ClutchValue[0,1]:");
    ClutchActiveLabel = new QLabel("ClutchActive:");
    ParkingBrakeValueLabel = new QLabel("ParkingBrakeValue[0,1]:");
    ParkingBrakeActiveLabel = new QLabel("ParkingBrakeActive:");
    SteeringWheelValueLabel = new QLabel("SteeringWheelValue(rad):");
    SteeringWheelActiveLabel = new QLabel("SteeringWheelActive:");
    GearNumberLabel = new QLabel("GearNumber:");
    GearActiveLabel = new QLabel("GearActive:");

    maxSpeedLineEdit = new QLineEdit("69.444");
    maxAccelerationLineEdit = new QLineEdit("200");
    maxDecelerationLineEdit = new QLineEdit("10.0");
    frontAxleMaxSteeringLineEdit = new QLineEdit("0.5");
    frontAxleWheelDiameterLineEdit = new QLineEdit("0.6");
    frontAxleTrackWidthLineEdit = new QLineEdit("1.8");
    frontAxlePositionXLineEdit = new QLineEdit("3.1");
    frontAxlePositionZLineEdit = new QLineEdit("0.3");
    rearAxleMaxSteeringLineEdit = new QLineEdit("0.0");
    rearAxleWheelDiameterLineEdit = new QLineEdit("0.6");
    rearAxleTrackWidthLineEdit = new QLineEdit("1.8");
    rearAxlePositionXLineEdit = new QLineEdit("0.0");
    rearAxlePositionZLineEdit = new QLineEdit("0.3");
    controllerNameLineEdit = new QLineEdit;
    controllerNameLineEdit->setPlaceholderText("HeroAgent/AdversaryAgent/..");
    ThrottleValueLineEdit = new QLineEdit("0");
    ThrottleActiveComboBox = BooleanQComboBox(false);
    BrakeValueLineEdit = new QLineEdit("0");
    BrakeActiveComboBox = BooleanQComboBox(false);
    ClutchValueLineEdit = new QLineEdit("0");
    ClutchActiveComboBox = BooleanQComboBox(false);
    ParkingBrakeValueLineEdit = new QLineEdit("0");
    ParkingBrakeActiveComboBox = BooleanQComboBox(false);
    SteeringWheelValueLineEdit = new QLineEdit("0");
    SteeringWheelActiveComboBox = BooleanQComboBox(false);
    GearNumberLineEdit = new QLineEdit("0");
    GearActiveComboBox = BooleanQComboBox(false);

    registerField(fieldprefix + "maxSpeed", maxSpeedLineEdit);
    registerField(fieldprefix + "maxAcceleration", maxAccelerationLineEdit);
    registerField(fieldprefix + "maxDeceleration", maxDecelerationLineEdit);
    registerField(fieldprefix + "frontAxleMaxSteering", frontAxleMaxSteeringLineEdit);
    registerField(fieldprefix + "frontAxleWheelDiameter", frontAxleWheelDiameterLineEdit);
    registerField(fieldprefix + "frontAxleTrackWidth", frontAxleTrackWidthLineEdit);
    registerField(fieldprefix + "frontAxlePositionX", frontAxlePositionXLineEdit);
    registerField(fieldprefix + "frontAxlePositionZ", frontAxlePositionZLineEdit);
    registerField(fieldprefix + "rearAxleMaxSteering", rearAxleMaxSteeringLineEdit);
    registerField(fieldprefix + "rearAxleWheelDiameter", rearAxleWheelDiameterLineEdit);
    registerField(fieldprefix + "rearAxleTrackWidth", rearAxleTrackWidthLineEdit);
    registerField(fieldprefix + "rearAxlePositionX", rearAxlePositionXLineEdit);
    registerField(fieldprefix + "rearAxlePositionZ", rearAxlePositionZLineEdit);
    registerField(fieldprefix + "controllerName", controllerNameLineEdit);
    registerField(fieldprefix + "ThrottleValue", ThrottleValueLineEdit);
    registerField(fieldprefix + "ThrottleActive", ThrottleActiveComboBox, "currentText");
    registerField(fieldprefix + "BrakeValue", BrakeValueLineEdit);
    registerField(fieldprefix + "BrakeActive", BrakeActiveComboBox, "currentText");
    registerField(fieldprefix + "ClutchValue", ClutchValueLineEdit);
    registerField(fieldprefix + "ClutchActive", ClutchActiveComboBox, "currentText");
    registerField(fieldprefix + "ParkingBrakeValue", ParkingBrakeValueLineEdit);
    registerField(fieldprefix + "ParkingBrakeActive", ParkingBrakeActiveComboBox, "currentText");
    registerField(fieldprefix + "SteeringWheelValue", SteeringWheelValueLineEdit);
    registerField(fieldprefix + "SteeringWheelActive", SteeringWheelActiveComboBox, "currentText");
    registerField(fieldprefix + "GearNumber", GearNumberLineEdit);
    registerField(fieldprefix + "GearActive", GearActiveComboBox, "currentText");

    QGridLayout *layout = new QGridLayout;

    layout->addWidget(maxSpeedLabel, 0, 0);
    layout->addWidget(maxAccelerationLabel, 1, 0);
    layout->addWidget(maxDecelerationLabel, 2, 0);
    layout->addWidget(frontAxleMaxSteeringLabel, 3, 0);
    layout->addWidget(frontAxleWheelDiameterLabel, 4, 0);
    layout->addWidget(frontAxleTrackWidthLabel, 5, 0);
    layout->addWidget(frontAxlePositionXLabel, 6, 0);
    layout->addWidget(frontAxlePositionZLabel, 7, 0);
    layout->addWidget(rearAxleMaxSteeringLabel, 8, 0);
    layout->addWidget(rearAxleWheelDiameterLabel, 9, 0);
    layout->addWidget(rearAxleTrackWidthLabel, 10, 0);
    layout->addWidget(rearAxlePositionXLabel, 11, 0);
    layout->addWidget(rearAxlePositionZLabel, 12, 0);
    layout->addWidget(controllerNameLabel, 13, 0);
    layout->addWidget(controllerPropertiesGroupBox, 14, 0, 1, 2);
    layout->addWidget(ThrottleValueLabel, 15, 0);
    layout->addWidget(ThrottleActiveLabel, 16, 0);
    layout->addWidget(BrakeValueLabel, 17, 0);
    layout->addWidget(BrakeActiveLabel, 18, 0);
    layout->addWidget(ClutchValueLabel, 19, 0);
    layout->addWidget(ClutchActiveLabel, 20, 0);
    layout->addWidget(ParkingBrakeValueLabel, 21, 0);
    layout->addWidget(ParkingBrakeActiveLabel, 22, 0);
    layout->addWidget(SteeringWheelValueLabel, 23, 0);
    layout->addWidget(SteeringWheelActiveLabel, 24, 0);
    layout->addWidget(GearNumberLabel, 25, 0);
    layout->addWidget(GearActiveLabel, 26, 0);

    layout->addWidget(maxSpeedLineEdit, 0, 1);
    layout->addWidget(maxAccelerationLineEdit, 1, 1);
    layout->addWidget(maxDecelerationLineEdit, 2, 1);
    layout->addWidget(frontAxleMaxSteeringLineEdit, 3, 1);
    layout->addWidget(frontAxleWheelDiameterLineEdit, 4, 1);
    layout->addWidget(frontAxleTrackWidthLineEdit, 5, 1);
    layout->addWidget(frontAxlePositionXLineEdit, 6, 1);
    layout->addWidget(frontAxlePositionZLineEdit, 7, 1);
    layout->addWidget(rearAxleMaxSteeringLineEdit, 8, 1);
    layout->addWidget(rearAxleWheelDiameterLineEdit, 9, 1);
    layout->addWidget(rearAxleTrackWidthLineEdit, 10, 1);
    layout->addWidget(rearAxlePositionXLineEdit, 11, 1);
    layout->addWidget(rearAxlePositionZLineEdit, 12, 1);
    layout->addWidget(controllerNameLineEdit, 13, 1);
    layout->addWidget(ThrottleValueLineEdit, 15, 1);
    layout->addWidget(ThrottleActiveComboBox, 16, 1);
    layout->addWidget(BrakeValueLineEdit, 17, 1);
    layout->addWidget(BrakeActiveComboBox, 18, 1);
    layout->addWidget(ClutchValueLineEdit, 19, 1);
    layout->addWidget(ClutchActiveComboBox, 20, 1);
    layout->addWidget(ParkingBrakeValueLineEdit, 21, 1);
    layout->addWidget(ParkingBrakeActiveComboBox, 22, 1);
    layout->addWidget(SteeringWheelValueLineEdit, 23, 1);
    layout->addWidget(SteeringWheelActiveComboBox, 24, 1);
    layout->addWidget(GearNumberLineEdit, 25, 1);
    layout->addWidget(GearActiveComboBox, 26, 1);

    setLayout(layout);

}
PedestrianGroupBox::PedestrianGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    setTitle("Pedestrian Parameters");
    QGridLayout *layout = new QGridLayout;
    massLabel = new QLabel("mass(kg):");
    massLineEdit = new QLineEdit("90.0");
    registerField(fieldprefix + "mass", massLineEdit);
    layout->addWidget(massLabel, 0, 0);
    layout->addWidget(massLineEdit, 0, 1);
    setLayout(layout);
}
MiscObjectGroupBox::MiscObjectGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    setTitle("MiscObject Parameters");
    QGridLayout *layout = new QGridLayout;
    massLabel = new QLabel("mass(kg):");
    massLineEdit = new QLineEdit("500.0");
    registerField(fieldprefix + "mass", massLineEdit);
    layout->addWidget(massLabel, 0, 0);
    layout->addWidget(massLineEdit, 0, 1);
    setLayout(layout);
}
ActorGroupBox::ActorGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    typeLabel = new QLabel(tr("type"));
    typeComboBox = new QComboBox;
    typeComboBox->addItem("Vehicle");
    typeComboBox->addItem("Pedestrian");
    typeComboBox->addItem("MiscObject");

    objectnameLabel = new QLabel(tr("objectname:"));
    objectnameLineEdit = new QLineEdit;
    objectnameLineEdit->setPlaceholderText("hero/adversary/...");

    nameLabel = new QLabel(tr("name"));
    nameComboBox = new QComboBox;
    positionGroupBox = new PositionGroupBox(fieldprefix + "Position.", this);
    propertiesGroupBox = new PropertiesGroupBox(fieldprefix + "Properties.", this);
    vehiclegroupbox = new VehicleGroupBox(fieldprefix + "Vehicle.", this);
    pedestriangroupbox = new PedestrianGroupBox(fieldprefix + "Pedestrian.", this);
    miscObjectgroupbox = new MiscObjectGroupBox(fieldprefix + "MiscObject.", this);
    propertiesGroupBox->setTitle("Properties");
    if (typeComboBox->currentText() == "Vehicle") {
        nameComboBox->clear();
        for (size_t i = 0; i < sizeof(vehname) / sizeof(const char *); ++i) {
            nameComboBox->addItem(vehname[i]);
        }
        vehiclegroupbox->setVisible(true);
        pedestriangroupbox->setVisible(false);
        miscObjectgroupbox->setVisible(false);
    }
    else if (typeComboBox->currentText() == "Pedestrian") {
        nameComboBox->clear();
        for (size_t i = 0; i < sizeof(pedname) / sizeof(const char *); ++i) {
            nameComboBox->addItem(pedname[i]);
        }
        vehiclegroupbox->setVisible(false);
        pedestriangroupbox->setVisible(true);
        miscObjectgroupbox->setVisible(false);
    }
    else {
        nameComboBox->clear();
        for (size_t i = 0; i < sizeof(miscname) / sizeof(const char *); ++i) {
            nameComboBox->addItem(miscname[i]);
        }
        vehiclegroupbox->setVisible(false);
        pedestriangroupbox->setVisible(false);
        miscObjectgroupbox->setVisible(true);
    }

    connect(typeComboBox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(updateName()));

    categoryLabel = new QLabel(tr("category"));
    categoryComboBox = new QComboBox;
    for (size_t i = 0; i < sizeof(category) / sizeof(const char *); ++i) {
        categoryComboBox->addItem(category[i]);
    }

    boundingxLabel = new QLabel(tr("BoundingBox Center x:"));
    boundingxLineEdit = new QLineEdit;
    boundingyLabel = new QLabel(tr("BoundingBox Center y:"));
    boundingyLineEdit = new QLineEdit;
    boundingzLabel = new QLabel(tr("BoundingBox Center z:"));
    boundingzLineEdit = new QLineEdit;
    boundingwLabel = new QLabel(tr("BoundingBox Dimensions w:"));
    boundingwLineEdit = new QLineEdit;
    boundinglLabel = new QLabel(tr("BoundingBox Dimensions l:"));
    boundinglLineEdit = new QLineEdit;
    boundinghLabel = new QLabel(tr("BoundingBox Dimensions h:"));
    boundinghLineEdit = new QLineEdit;

    if (typeComboBox->currentText() != "MiscObject") {
        boundingxLineEdit->setText("1.5");
        boundingyLineEdit->setText("0.0");
        boundingzLineEdit->setText("0.9");
        boundingwLineEdit->setText("2.1");
        boundinglLineEdit->setText("4.5");
        boundinghLineEdit->setText("1.8");
    }
    else {
        boundingxLineEdit->setText("-1.0");
        boundingyLineEdit->setText("0.0");
        boundingzLineEdit->setText("0.85");
        boundingwLineEdit->setText("1.0");
        boundinglLineEdit->setText("2.0");
        boundinghLineEdit->setText("1.7");
    }

    registerField(fieldprefix + "type", typeComboBox, "currentText");
    registerField(fieldprefix + "objectname", objectnameLineEdit);
    registerField(fieldprefix + "name", nameComboBox, "currentText");
    registerField(fieldprefix + "category", categoryComboBox, "currentText");
    registerField(fieldprefix + "boundingx", boundingxLineEdit);
    registerField(fieldprefix + "boundingy", boundingyLineEdit);
    registerField(fieldprefix + "boundingz", boundingzLineEdit);
    registerField(fieldprefix + "boundingw", boundingwLineEdit);
    registerField(fieldprefix + "boundingl", boundinglLineEdit);
    registerField(fieldprefix + "boundingh", boundinghLineEdit);

    QGridLayout *layout = new QGridLayout;

    layout->addWidget(typeLabel, 0, 0);
    layout->addWidget(typeComboBox, 0, 1);
    layout->addWidget(objectnameLabel, 1, 0);
    layout->addWidget(objectnameLineEdit, 1, 1);
    layout->addWidget(nameLabel, 2, 0);
    layout->addWidget(nameComboBox, 2, 1);
    layout->addWidget(categoryLabel, 3, 0);
    layout->addWidget(categoryComboBox, 3, 1);
    layout->addWidget(boundingxLabel, 4, 0);
    layout->addWidget(boundingxLineEdit, 4, 1);
    layout->addWidget(boundingyLabel, 5, 0);
    layout->addWidget(boundingyLineEdit, 5, 1);
    layout->addWidget(boundingzLabel, 6, 0);
    layout->addWidget(boundingzLineEdit, 6, 1);
    layout->addWidget(boundingwLabel, 7, 0);
    layout->addWidget(boundingwLineEdit, 7, 1);
    layout->addWidget(boundinglLabel, 8, 0);
    layout->addWidget(boundinglLineEdit, 8, 1);
    layout->addWidget(boundinghLabel, 9, 0);
    layout->addWidget(boundinghLineEdit, 9, 1);
    layout->addWidget(positionGroupBox, 10, 0, 1, 2);
    layout->addWidget(propertiesGroupBox, 11, 0, 1, 2);
    layout->addWidget(vehiclegroupbox, 12, 0, 1, 2);
    layout->addWidget(pedestriangroupbox, 13, 0, 1, 2);
    layout->addWidget(miscObjectgroupbox, 14, 0, 1, 2);
    setLayout(layout);
}

void ActorGroupBox::updateName()
{
    if (typeComboBox->currentText() == "Vehicle") {
        nameComboBox->clear();
        for (size_t i = 0; i < sizeof(vehname) / sizeof(const char *); ++i) {
            nameComboBox->addItem(vehname[i]);
        }
        vehiclegroupbox->setVisible(true);
        pedestriangroupbox->setVisible(false);
        miscObjectgroupbox->setVisible(false);
    }
    else if (typeComboBox->currentText() == "Pedestrian") {
        nameComboBox->clear();
        for (size_t i = 0; i < sizeof(pedname) / sizeof(const char *); ++i) {
            nameComboBox->addItem(pedname[i]);
        }
        vehiclegroupbox->setVisible(false);
        pedestriangroupbox->setVisible(true);
        miscObjectgroupbox->setVisible(false);
    }
    else {
        nameComboBox->clear();
        for (size_t i = 0; i < sizeof(miscname) / sizeof(const char *); ++i) {
            nameComboBox->addItem(miscname[i]);
        }
        vehiclegroupbox->setVisible(false);
        pedestriangroupbox->setVisible(false);
        miscObjectgroupbox->setVisible(true);
    }
    if (typeComboBox->currentText() != "MiscObject") {
        boundingxLineEdit->setText("1.5");
        boundingyLineEdit->setText("0.0");
        boundingzLineEdit->setText("0.9");
        boundingwLineEdit->setText("2.1");
        boundinglLineEdit->setText("4.5");
        boundinghLineEdit->setText("1.8");
    }
    else {
        boundingxLineEdit->setText("-1.0");
        boundingyLineEdit->setText("0.0");
        boundingzLineEdit->setText("0.85");
        boundingwLineEdit->setText("1.0");
        boundinglLineEdit->setText("2.0");
        boundinghLineEdit->setText("1.7");
    }
}

ActorPage::ActorPage(QWidget *parent)
    : QWizardPage(parent)
{
    QScrollArea* scrollArea = new QScrollArea;
    QWidget *widget = new QWidget;
    setTitle(tr("Set Your Actors"));
    setSubTitle(tr("Please set the basic information of actors "
                   "and be sure to give legitimate input."));
    // setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));

    actornumLabel = new QLabel("The number of actor(s):");
    actornumComboBox = NumberQComboBox(MINACTORNUM, MAXACTORNUM);
    fieldprefix = "Actor.";
    registerField(fieldprefix+"num", actornumComboBox, "currentText");
    QGridLayout *layout = new QGridLayout;
    connect(actornumComboBox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(updateActorPage()));
    layout->addWidget(actornumLabel, 0, 0);
    layout->addWidget(actornumComboBox, 0, 1);
    for (int i = 0; i < MAXACTORNUM; ++i) {
        ActorGroupBox* box = new ActorGroupBox(fieldprefix + "Actor" + QString::number(i) + ".", this);
        actorGroupBox.append(box);
        box->setTitle("~Actor" + QString::number(i) + " Settings");

        layout->addWidget(box, i + 1, 0, 1, 2);
    }
    QVector<QString>::iterator itername;
    QVector<QWidget*>::iterator iterwidget;
    QVector<const char*>::iterator iterproperty;
    for (itername = childfieldname.begin(), iterwidget = childfieldwidget.begin(), iterproperty = childfieldproperty.begin();
      itername != childfieldname.end() && iterwidget!= childfieldwidget.end() && iterproperty != childfieldproperty.end();
      ++itername, ++iterwidget, ++iterproperty
    ) {
        registerField(*itername, *iterwidget, *iterproperty);
    }
    childfieldname.clear();
    childfieldwidget.clear();
    childfieldproperty.clear();
    layout->setAlignment(Qt::AlignTop);
    widget->setLayout(layout);
    scrollArea->setWidget(widget);
    scrollArea->setWidgetResizable(true);

    QGridLayout *wholelayout = new QGridLayout;
    wholelayout->addWidget(scrollArea, 0, 0);
    wholelayout->setAlignment(Qt::AlignTop);
    setLayout(wholelayout);
}

void ActorPage::initializePage()
{
    int actornum = actornumComboBox->currentText().toInt();
    for (int i = 0; i < MAXACTORNUM; ++i) {
        actorGroupBox[i]->setVisible(i < actornum ? true : false);
    }
}

void ActorPage::updateActorPage()
{
    int actornum = actornumComboBox->currentText().toInt();
    for (int i = 0; i < MAXACTORNUM; ++i) {
        actorGroupBox[i]->setVisible(i < actornum ? true : false);
    }
}

int ActorPage::nextId() const
{
    return LicenseWizard::Page_Story;
}

ParameterConditionGroupBox::ParameterConditionGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    setTitle("ParameterCondition");
    parameterRefLabel = new QLabel("parameterRef:");
    valueLabel = new QLabel("value:");
    ruleLabel = new QLabel("rule:");

    parameterRefLineEdit = new QLineEdit;
    valueLineEdit = new QLineEdit;
    ruleComboBox = RuleComboBox();

    registerField(fieldprefix + "parameterRef", parameterRefLineEdit);
    registerField(fieldprefix + "value", valueLineEdit);
    registerField(fieldprefix + "rule", ruleComboBox, "currentText");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(parameterRefLabel, 0, 0);
    layout->addWidget(valueLabel, 1, 0);
    layout->addWidget(ruleLabel, 2, 0);

    layout->addWidget(parameterRefLineEdit, 0, 1);
    layout->addWidget(valueLineEdit, 1, 1);
    layout->addWidget(ruleComboBox, 2, 1);
    setLayout(layout);
}
SimulationTimeConditionGroupBox::SimulationTimeConditionGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    setTitle("SimulationTimeCondition");
    valueLabel = new QLabel("value:");
    ruleLabel = new QLabel("rule:");

    valueLineEdit = new QLineEdit;
    ruleComboBox = RuleComboBox();

    registerField(fieldprefix + "value", valueLineEdit);
    registerField(fieldprefix + "rule", ruleComboBox, "currentText");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(valueLabel, 0, 0);
    layout->addWidget(ruleLabel, 1, 0);

    layout->addWidget(valueLineEdit, 0, 1);
    layout->addWidget(ruleComboBox, 1, 1);
    setLayout(layout);
}
StoryboardElementStateConditionGroupBox::StoryboardElementStateConditionGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    setTitle("StoryboardElementStateCondition");

    storyboardElementTypeLabel = new QLabel("storyboardElementType:");
    storyboardElementRefLabel = new QLabel("storyboardElementRef:");
    stateLabel = new QLabel("state:");

    storyboardElementTypeComboBox = new QComboBox;
    storyboardElementRefComboBox = new QComboBox;
    stateComboBox = new QComboBox;

    storyboardElementTypeComboBox->addItem("action");
    storyboardElementTypeComboBox->addItem("story");
    storyboardElementTypeComboBox->addItem("act");
    storyboardElementTypeComboBox->addItem("maneuver");
    storyboardElementTypeComboBox->addItem("event");
    storyboardElementTypeComboBox->addItem("maneuverGroup");

    for (int i = 0; i < MAXEVENTNUM; ++i) {
        storyboardElementRefComboBox->addItem("Event"+QString::number(i));
    }
    stateComboBox->addItem("completeState");
    stateComboBox->addItem("startTransition");
    stateComboBox->addItem("endTransition");
    stateComboBox->addItem("stopTransition");
    stateComboBox->addItem("skipTransition");
    stateComboBox->addItem("runningState");
    stateComboBox->addItem("standbyState");

    registerField(fieldprefix + "storyboardElementType", storyboardElementTypeComboBox, "currentText");
    registerField(fieldprefix + "storyboardElementRef", storyboardElementRefComboBox, "currentText");
    registerField(fieldprefix + "state", stateComboBox, "currentText");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(storyboardElementTypeLabel, 0, 0);
    layout->addWidget(storyboardElementRefLabel, 1, 0);
    layout->addWidget(stateLabel, 2, 0);

    layout->addWidget(storyboardElementTypeComboBox, 0, 1);
    layout->addWidget(storyboardElementRefComboBox, 1, 1);
    layout->addWidget(stateComboBox, 2, 1);
    setLayout(layout);
}
StandStillConditionGroupBox::StandStillConditionGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    setTitle("StandStillCondition");
    durationLabel = new QLabel("duration:");
    durationLineEdit = new QLineEdit("0.1");

    registerField(fieldprefix+"duration", durationLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(durationLabel, 0, 0);
    layout->addWidget(durationLineEdit, 0, 1);
    setLayout(layout);
}
TraveledDistanceConditionGroupBox::TraveledDistanceConditionGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    setTitle("TraveledDistanceCondition");
    valueLabel = new QLabel("value:");
    valueLineEdit = new QLineEdit;

    registerField(fieldprefix+"value", valueLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(valueLabel, 0, 0);
    layout->addWidget(valueLineEdit, 0, 1);
    setLayout(layout);
}
ReachPositionConditionGroupBox::ReachPositionConditionGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    setTitle("ReachPositionCondition");
    toleranceLabel = new QLabel("tolerance:");
    toleranceLineEdit = new QLineEdit;
    positionGroupBox = new PositionGroupBox(fieldprefix+"Position.", this);

    registerField(fieldprefix+"tolerance", toleranceLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(toleranceLabel, 0, 0);
    layout->addWidget(toleranceLineEdit, 0, 1);
    layout->addWidget(positionGroupBox, 1, 0, 1, 2);
    setLayout(layout);
}
RelativeDistanceConditionGroupBox::RelativeDistanceConditionGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    setTitle("RelativeDistanceCondition");
    entityRefLabel = new QLabel("entityRef:");
    relativeDistanceTypeLabel = new QLabel("relativeDistanceType:");
    valueLabel = new QLabel("value:");
    freespaceLabel = new QLabel("freespace:");
    ruleLabel = new QLabel("rule:");


    entityRefComboBox = new QComboBox;
    relativeDistanceTypeComboBox = new QComboBox;
    valueLineEdit = new QLineEdit;
    freespaceComboBox = BooleanQComboBox(false, this);
    ruleComboBox = RuleComboBox(-1, this);

    for (int i = 0; i < MAXACTORNUM; ++i) {
        entityRefComboBox->addItem("Actor"+QString::number(i));
    }
    relativeDistanceTypeComboBox->addItem("cartesianDistance");
    relativeDistanceTypeComboBox->addItem("longitudinal");
    relativeDistanceTypeComboBox->addItem("lateral");

    registerField(fieldprefix+"entityRef", entityRefComboBox, "currentText");
    registerField(fieldprefix+"relativeDistanceType", relativeDistanceTypeComboBox, "currentText");
    registerField(fieldprefix+"value", valueLineEdit);
    registerField(fieldprefix+"freespace", freespaceComboBox, "currentText");
    registerField(fieldprefix+"rule", ruleComboBox, "currentText");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(entityRefLabel, 0, 0);
    layout->addWidget(relativeDistanceTypeLabel, 1, 0);
    layout->addWidget(valueLabel, 2, 0);
    layout->addWidget(freespaceLabel, 3, 0);
    layout->addWidget(ruleLabel, 4, 0);

    layout->addWidget(entityRefComboBox, 0, 1);
    layout->addWidget(relativeDistanceTypeComboBox, 1, 1);
    layout->addWidget(valueLineEdit, 2, 1);
    layout->addWidget(freespaceComboBox, 3, 1);
    layout->addWidget(ruleComboBox, 4, 1);
    setLayout(layout);
}

ConditionGroupBox::ConditionGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    nameLabel = new QLabel("name:");
    delayLabel = new QLabel("delay[0,inf):");
    conditionEdgeLabel = new QLabel("conditionEdge:");
    triggeringEntityRefLabel = new QLabel("triggeringEntityRef:");
    typeLabel = new QLabel("type:");
    nameLineEdit = new QLineEdit;
    delayLineEdit = new QLineEdit("0");
    conditionEdgeComboBox = new QComboBox;
    conditionEdgeComboBox->addItem("rising");
    conditionEdgeComboBox->addItem("falling");
    conditionEdgeComboBox->addItem("risingOrFalling");
    conditionEdgeComboBox->addItem("none");
    triggeringEntityRefComboBox = new QComboBox;
    for (int i = 0; i < MAXACTORNUM; ++i) {
        triggeringEntityRefComboBox->addItem("Actor"+QString::number(i));
    }
    typeComboBox = new QComboBox;
    typeComboBox->addItem("ParameterCondition");
    typeComboBox->addItem("SimulationTimeCondition");
    typeComboBox->addItem("StoryboardElementStateCondition");
    typeComboBox->addItem("StandStillCondition");
    typeComboBox->addItem("TraveledDistanceCondition");
    typeComboBox->addItem("ReachPositionCondition");
    typeComboBox->addItem("RelativeDistanceCondition");

    parameterConditionGroupBox = new ParameterConditionGroupBox(fieldprefix+"ParameterCondition.", this);
    simulationTimeConditionGroupBox = new SimulationTimeConditionGroupBox(fieldprefix+"SimulationTimeCondition.", this);
    storyboardElementStateConditionGroupBox = new StoryboardElementStateConditionGroupBox(fieldprefix+"StoryboardElementStateCondition.", this);
    standStillConditionGroupBox = new StandStillConditionGroupBox(fieldprefix+"StandStillCondition.", this);
    traveledDistanceConditionGroupBox = new TraveledDistanceConditionGroupBox(fieldprefix+"TraveledDistanceCondition.", this);
    reachPositionConditionGroupBox = new ReachPositionConditionGroupBox(fieldprefix+"ReachPositionCondition.", this);
    relativeDistanceConditionGroupBox = new RelativeDistanceConditionGroupBox(fieldprefix+"RelativeDistanceCondition.", this);

    QString type = typeComboBox->currentText();
    if (type == "ParameterCondition") {
        parameterConditionGroupBox->setVisible(true);
        simulationTimeConditionGroupBox->setVisible(false);
        storyboardElementStateConditionGroupBox->setVisible(false);
        standStillConditionGroupBox->setVisible(false);
        traveledDistanceConditionGroupBox->setVisible(false);
        reachPositionConditionGroupBox->setVisible(false);
        relativeDistanceConditionGroupBox->setVisible(false);
    }
    else if (type == "SimulationTimeCondition") {
        parameterConditionGroupBox->setVisible(false);
        simulationTimeConditionGroupBox->setVisible(true);
        storyboardElementStateConditionGroupBox->setVisible(false);
        standStillConditionGroupBox->setVisible(false);
        traveledDistanceConditionGroupBox->setVisible(false);
        reachPositionConditionGroupBox->setVisible(false);
        relativeDistanceConditionGroupBox->setVisible(false);
    }
    else if (type == "StoryboardElementStateCondition") {
        parameterConditionGroupBox->setVisible(false);
        simulationTimeConditionGroupBox->setVisible(false);
        storyboardElementStateConditionGroupBox->setVisible(true);
        standStillConditionGroupBox->setVisible(false);
        traveledDistanceConditionGroupBox->setVisible(false);
        reachPositionConditionGroupBox->setVisible(false);
        relativeDistanceConditionGroupBox->setVisible(false);
    }
    else if (type == "StandStillCondition") {
        parameterConditionGroupBox->setVisible(false);
        simulationTimeConditionGroupBox->setVisible(false);
        storyboardElementStateConditionGroupBox->setVisible(false);
        standStillConditionGroupBox->setVisible(true);
        traveledDistanceConditionGroupBox->setVisible(false);
        reachPositionConditionGroupBox->setVisible(false);
        relativeDistanceConditionGroupBox->setVisible(false);
    }
    else if (type == "TraveledDistanceCondition") {
        parameterConditionGroupBox->setVisible(false);
        simulationTimeConditionGroupBox->setVisible(false);
        storyboardElementStateConditionGroupBox->setVisible(false);
        standStillConditionGroupBox->setVisible(false);
        traveledDistanceConditionGroupBox->setVisible(true);
        reachPositionConditionGroupBox->setVisible(false);
        relativeDistanceConditionGroupBox->setVisible(false);
    }
    else if (type == "ReachPositionCondition") {
        parameterConditionGroupBox->setVisible(false);
        simulationTimeConditionGroupBox->setVisible(false);
        storyboardElementStateConditionGroupBox->setVisible(false);
        standStillConditionGroupBox->setVisible(false);
        traveledDistanceConditionGroupBox->setVisible(false);
        reachPositionConditionGroupBox->setVisible(true);
        relativeDistanceConditionGroupBox->setVisible(false);
    }
    else if (type == "RelativeDistanceCondition") {
        parameterConditionGroupBox->setVisible(false);
        simulationTimeConditionGroupBox->setVisible(false);
        storyboardElementStateConditionGroupBox->setVisible(false);
        standStillConditionGroupBox->setVisible(false);
        traveledDistanceConditionGroupBox->setVisible(false);
        reachPositionConditionGroupBox->setVisible(false);
        relativeDistanceConditionGroupBox->setVisible(true);
    }

    connect(typeComboBox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(updateConditionType()));

    registerField(fieldprefix+"name", nameLineEdit);
    registerField(fieldprefix+"delay", delayLineEdit);
    registerField(fieldprefix+"conditionEdge", conditionEdgeComboBox, "currentText");
    registerField(fieldprefix+"triggeringEntityRef", triggeringEntityRefComboBox, "currentText");
    registerField(fieldprefix+"type", typeComboBox, "currentText");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(delayLabel, 1, 0);
    layout->addWidget(conditionEdgeLabel, 2, 0);
    layout->addWidget(typeLabel, 3, 0);
    layout->addWidget(triggeringEntityRefLabel, 4, 0);

    layout->addWidget(nameLineEdit, 0, 1);
    layout->addWidget(delayLineEdit, 1, 1);
    layout->addWidget(conditionEdgeComboBox, 2, 1);
    layout->addWidget(typeComboBox, 3, 1);
    layout->addWidget(triggeringEntityRefComboBox, 4, 1);

    layout->addWidget(parameterConditionGroupBox, 5, 0, 1, 2);
    layout->addWidget(simulationTimeConditionGroupBox, 6, 0, 1, 2);
    layout->addWidget(storyboardElementStateConditionGroupBox, 7, 0, 1, 2);
    layout->addWidget(standStillConditionGroupBox, 8, 0, 1, 2);
    layout->addWidget(traveledDistanceConditionGroupBox, 9, 0, 1, 2);
    layout->addWidget(reachPositionConditionGroupBox, 10, 0, 1, 2);
    layout->addWidget(relativeDistanceConditionGroupBox, 11, 0, 1, 2);

    setLayout(layout);
}

void ConditionGroupBox::updateConditionType()
{
    QString type = typeComboBox->currentText();
    if (type == "ParameterCondition") {
        triggeringEntityRefLabel->setVisible(false);
        triggeringEntityRefComboBox->setVisible(false);
        parameterConditionGroupBox->setVisible(true);
        simulationTimeConditionGroupBox->setVisible(false);
        storyboardElementStateConditionGroupBox->setVisible(false);
        standStillConditionGroupBox->setVisible(false);
        traveledDistanceConditionGroupBox->setVisible(false);
        reachPositionConditionGroupBox->setVisible(false);
        relativeDistanceConditionGroupBox->setVisible(false);
    }
    else if (type == "SimulationTimeCondition") {
        triggeringEntityRefLabel->setVisible(false);
        triggeringEntityRefComboBox->setVisible(false);
        parameterConditionGroupBox->setVisible(false);
        simulationTimeConditionGroupBox->setVisible(true);
        storyboardElementStateConditionGroupBox->setVisible(false);
        standStillConditionGroupBox->setVisible(false);
        traveledDistanceConditionGroupBox->setVisible(false);
        reachPositionConditionGroupBox->setVisible(false);
        relativeDistanceConditionGroupBox->setVisible(false);
    }
    else if (type == "StoryboardElementStateCondition") {
        triggeringEntityRefLabel->setVisible(false);
        triggeringEntityRefComboBox->setVisible(false);
        parameterConditionGroupBox->setVisible(false);
        simulationTimeConditionGroupBox->setVisible(false);
        storyboardElementStateConditionGroupBox->setVisible(true);
        standStillConditionGroupBox->setVisible(false);
        traveledDistanceConditionGroupBox->setVisible(false);
        reachPositionConditionGroupBox->setVisible(false);
        relativeDistanceConditionGroupBox->setVisible(false);
    }
    else if (type == "StandStillCondition") {
        triggeringEntityRefLabel->setVisible(true);
        triggeringEntityRefComboBox->setVisible(true);
        parameterConditionGroupBox->setVisible(false);
        simulationTimeConditionGroupBox->setVisible(false);
        storyboardElementStateConditionGroupBox->setVisible(false);
        standStillConditionGroupBox->setVisible(true);
        traveledDistanceConditionGroupBox->setVisible(false);
        reachPositionConditionGroupBox->setVisible(false);
        relativeDistanceConditionGroupBox->setVisible(false);
    }
    else if (type == "TraveledDistanceCondition") {
        triggeringEntityRefLabel->setVisible(true);
        triggeringEntityRefComboBox->setVisible(true);
        parameterConditionGroupBox->setVisible(false);
        simulationTimeConditionGroupBox->setVisible(false);
        storyboardElementStateConditionGroupBox->setVisible(false);
        standStillConditionGroupBox->setVisible(false);
        traveledDistanceConditionGroupBox->setVisible(true);
        reachPositionConditionGroupBox->setVisible(false);
        relativeDistanceConditionGroupBox->setVisible(false);
    }
    else if (type == "ReachPositionCondition") {
        triggeringEntityRefLabel->setVisible(true);
        triggeringEntityRefComboBox->setVisible(true);
        parameterConditionGroupBox->setVisible(false);
        simulationTimeConditionGroupBox->setVisible(false);
        storyboardElementStateConditionGroupBox->setVisible(false);
        standStillConditionGroupBox->setVisible(false);
        traveledDistanceConditionGroupBox->setVisible(false);
        reachPositionConditionGroupBox->setVisible(true);
        relativeDistanceConditionGroupBox->setVisible(false);
    }
    else if (type == "RelativeDistanceCondition") {
        triggeringEntityRefLabel->setVisible(true);
        triggeringEntityRefComboBox->setVisible(true);
        parameterConditionGroupBox->setVisible(false);
        simulationTimeConditionGroupBox->setVisible(false);
        storyboardElementStateConditionGroupBox->setVisible(false);
        standStillConditionGroupBox->setVisible(false);
        traveledDistanceConditionGroupBox->setVisible(false);
        reachPositionConditionGroupBox->setVisible(false);
        relativeDistanceConditionGroupBox->setVisible(true);
    }
}

StoryPage::StoryPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle("Story Parameters");
    setSubTitle("Set the basic information of <i>OpenScenario</i>&trade; Story.");
    fieldprefix = "Story.";
    storyNameLabel = new QLabel("storyName:");
    actNameLabel = new QLabel("actName:");
    maneuverGroupNameLabel = new QLabel("maneuverGroupName:");
    maximumExecutionCountLabel = new QLabel("maximumExecutionCount[1,inf):");
    selectTriggeringEntitiesLabel = new QLabel("selectTriggeringEntities:");
    entityRefLabel = new QLabel("entityRef:");
    maneuverNameLabel = new QLabel("maneuverName:");

    storyNameLineEdit = new QLineEdit("MyStory");
    actNameLineEdit = new QLineEdit("Behavior");
    maneuverGroupNameLineEdit = new QLineEdit("ManeuverSequence");
    maximumExecutionCountLineEdit = new QLineEdit("1");
    selectTriggeringEntitiesComboBox = BooleanQComboBox(false);
    entityRefComboBox = new QComboBox;
    for (int i = 0; i < MAXACTORNUM; ++i) {
        entityRefComboBox->addItem("Actor"+QString::number(i));
    }
    maneuverNameLineEdit = new QLineEdit;

    maneuverNameLineEdit->setPlaceholderText("A name describes the maneuver.");

    registerField(fieldprefix+"storyName", storyNameLineEdit);
    registerField(fieldprefix+"actName", actNameLineEdit);
    registerField(fieldprefix+"maneuverGroupName", maneuverGroupNameLineEdit);
    registerField(fieldprefix+"maximumExecutionCount", maximumExecutionCountLineEdit);
    registerField(fieldprefix+"selectTriggeringEntities", selectTriggeringEntitiesComboBox, "currentText");
    registerField(fieldprefix+"entityRef", entityRefComboBox, "currentText");
    registerField(fieldprefix+"maneuverName", maneuverNameLineEdit);
    QVector<QString>::iterator itername;
    QVector<QWidget*>::iterator iterwidget;
    QVector<const char*>::iterator iterproperty;
    for (itername = childfieldname.begin(), iterwidget = childfieldwidget.begin(), iterproperty = childfieldproperty.begin();
      itername != childfieldname.end() && iterwidget!= childfieldwidget.end() && iterproperty != childfieldproperty.end();
      ++itername, ++iterwidget, ++iterproperty
    ) {
        registerField(*itername, *iterwidget, *iterproperty);
    }
    childfieldname.clear();
    childfieldwidget.clear();
    childfieldproperty.clear();
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(storyNameLabel, 0, 0);
    layout->addWidget(actNameLabel, 1, 0);
    layout->addWidget(maneuverGroupNameLabel, 2, 0);
    layout->addWidget(maximumExecutionCountLabel, 3, 0);
    layout->addWidget(selectTriggeringEntitiesLabel, 4, 0);
    layout->addWidget(entityRefLabel, 5, 0);
    layout->addWidget(maneuverNameLabel, 6, 0);

    layout->addWidget(storyNameLineEdit, 0, 1);
    layout->addWidget(actNameLineEdit, 1, 1);
    layout->addWidget(maneuverGroupNameLineEdit, 2, 1);
    layout->addWidget(maximumExecutionCountLineEdit, 3, 1);
    layout->addWidget(selectTriggeringEntitiesComboBox, 4, 1);
    layout->addWidget(entityRefComboBox, 5, 1);
    layout->addWidget(maneuverNameLineEdit, 6, 1);

    setLayout(layout);
    
}
int StoryPage::nextId() const
{
    return LicenseWizard::Page_Event;
}

EnvironmentActionGroupBox::EnvironmentActionGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    setTitle("EnvironmentAction");
    environmentGroupBox = new EnvironmentGroupBox(fieldprefix+"Environment.", this);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(environmentGroupBox, 0, 0);
    setLayout(layout);
}
LongitudinalActionGroupBox::LongitudinalActionGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    setTitle("LongitudinalAction");
    dynamicsShapeLabel = new QLabel("dynamicsShape:");
    dynamicsvalueLabel = new QLabel("dynamicsvalue[0.0,inf):");
    dynamicsDimensionLabel = new QLabel("dynamicsDimension:");
    targetvalueLabel = new QLabel("absoluteTargetSpeed(m/s):");

    dynamicsShapeComboBox = new QComboBox;
    dynamicsShapeComboBox->addItem("step");
    dynamicsShapeComboBox->addItem("cubic");
    dynamicsShapeComboBox->addItem("sinusoidal");
    dynamicsShapeComboBox->addItem("linear");
    dynamicsvalueLineEdit = new QLineEdit;
    dynamicsDimensionComboBox = new QComboBox;
    dynamicsDimensionComboBox->addItem("distance");
    dynamicsDimensionComboBox->addItem("time");
    dynamicsDimensionComboBox->addItem("rate");
    targetvalueLineEdit = new QLineEdit("0.0");

    registerField(fieldprefix+"dynamicsShape", dynamicsShapeComboBox, "currentText");
    registerField(fieldprefix+"dynamicsvalue", dynamicsvalueLineEdit);
    registerField(fieldprefix+"dynamicsDimension", dynamicsDimensionComboBox, "currentText");
    registerField(fieldprefix+"targetvalue", targetvalueLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(dynamicsShapeLabel, 0, 0);
    layout->addWidget(dynamicsvalueLabel, 1, 0);
    layout->addWidget(dynamicsDimensionLabel, 2, 0);
    layout->addWidget(targetvalueLabel, 3, 0);
    layout->addWidget(dynamicsShapeComboBox, 0, 1);
    layout->addWidget(dynamicsvalueLineEdit, 1, 1);
    layout->addWidget(dynamicsDimensionComboBox, 2, 1);
    layout->addWidget(targetvalueLineEdit, 3, 1);
    setLayout(layout);
}
LateralActionGroupBox::LateralActionGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    setTitle("LateralAction");
    dynamicsShapeLabel = new QLabel("dynamicsShape:");
    dynamicsvalueLabel = new QLabel("dynamicsvalue[0.0,inf):");
    dynamicsDimensionLabel = new QLabel("dynamicsDimension:");
    targetentityRefLabel = new QLabel("entityRef:");
    targetvalueLabel = new QLabel("absoluteTargetSpeed(m/s):");

    dynamicsShapeComboBox = new QComboBox;
    dynamicsShapeComboBox->addItem("step");
    dynamicsShapeComboBox->addItem("cubic");
    dynamicsShapeComboBox->addItem("sinusoidal");
    dynamicsShapeComboBox->addItem("linear");
    dynamicsvalueLineEdit = new QLineEdit;
    dynamicsDimensionComboBox = new QComboBox;
    dynamicsDimensionComboBox->addItem("distance");
    dynamicsDimensionComboBox->addItem("time");
    dynamicsDimensionComboBox->addItem("rate");
    targetentityRefComboBox = new QComboBox;
    for (int i = 0; i < MAXACTORNUM; ++i) {
        targetentityRefComboBox->addItem("Actor"+QString::number(i));
    }
    targetvalueLineEdit = new QLineEdit("0.0");

    registerField(fieldprefix+"dynamicsShape", dynamicsShapeComboBox, "currentText");
    registerField(fieldprefix+"dynamicsvalue", dynamicsvalueLineEdit);
    registerField(fieldprefix+"dynamicsDimension", dynamicsDimensionComboBox, "currentText");
    registerField(fieldprefix+"targetentityRef", targetentityRefComboBox, "currentText");
    registerField(fieldprefix+"targetvalue", targetvalueLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(dynamicsShapeLabel, 0, 0);
    layout->addWidget(dynamicsvalueLabel, 1, 0);
    layout->addWidget(dynamicsDimensionLabel, 2, 0);
    layout->addWidget(targetentityRefLabel, 3, 0);
    layout->addWidget(targetvalueLabel, 4, 0);
    layout->addWidget(dynamicsShapeComboBox, 0, 1);
    layout->addWidget(dynamicsvalueLineEdit, 1, 1);
    layout->addWidget(dynamicsDimensionComboBox, 2, 1);
    layout->addWidget(targetentityRefComboBox, 3, 1);
    layout->addWidget(targetvalueLineEdit, 4, 1);
    setLayout(layout);
}
SynchronizeActionGroupBox::SynchronizeActionGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    setTitle("SynchronizeAction");
    masterEntityRefLabel = new QLabel("masterEntityRef:");
    relativeSpeedToMasterValueLabel = new QLabel("relativeSpeedToMasterValue:");
    speedTargetValueTypeLabel = new QLabel("speedTargetValueType:");

    masterEntityRefComboBox = new QComboBox;
    relativeSpeedToMasterValueLineEdit = new QLineEdit;
    speedTargetValueTypeComboBox = new QComboBox;

    targetPositionMasterGroupBox = new PositionGroupBox(fieldprefix+"targetPositionMaster.", this);
    targetPositionGroupBox = new PositionGroupBox(fieldprefix+"targetPosition.", this);

    for (int i = 0; i < MAXACTORNUM; ++i) {
        masterEntityRefComboBox->addItem("Actor"+QString::number(i));
    }
    speedTargetValueTypeComboBox->addItem("delta");
    speedTargetValueTypeComboBox->addItem("factor");

    registerField(fieldprefix+"masterEntityRef", masterEntityRefComboBox, "currentText");
    registerField(fieldprefix+"relativeSpeedToMasterValue", relativeSpeedToMasterValueLineEdit);
    registerField(fieldprefix+"speedTargetValueType", speedTargetValueTypeComboBox, "currentText");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(masterEntityRefLabel, 0, 0);
    layout->addWidget(relativeSpeedToMasterValueLabel, 1, 0);
    layout->addWidget(speedTargetValueTypeLabel, 2, 0);
    layout->addWidget(masterEntityRefComboBox, 0, 1);
    layout->addWidget(relativeSpeedToMasterValueLineEdit, 1, 1);
    layout->addWidget(speedTargetValueTypeComboBox, 2, 1);
    layout->addWidget(targetPositionMasterGroupBox, 3, 0, 1, 2);
    layout->addWidget(targetPositionGroupBox, 4, 0, 1, 2);
    setLayout(layout);
}
RoutingActionGroupBox::RoutingActionGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    setTitle("RoutingAction");
    positionGroupBox = new PositionGroupBox(fieldprefix+"Position.", this);
    positionGroupBox->setTitle("AcquirePositionAction");
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(positionGroupBox, 0, 0);
    setLayout(layout);
}

ActionGroupBox::ActionGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    setTitle("Action");
    nameLabel = new QLabel("name:");
    typeLabel = new QLabel("type:");

    nameLineEdit = new QLineEdit;
    typeComboBox = new QComboBox;
    typeComboBox->addItem("EnvironmentAction");
    typeComboBox->addItem("LongitudinalAction");
    typeComboBox->addItem("LateralAction");
    typeComboBox->addItem("SynchronizeAction");
    typeComboBox->addItem("RoutingAction");

    environmentActionGroupBox = new EnvironmentActionGroupBox(fieldprefix + "EnvironmentAction.", this);
    longitudinalActionGroupBox = new LongitudinalActionGroupBox(fieldprefix + "LongitudinalAction.", this);
    lateralActionGroupBox = new LateralActionGroupBox(fieldprefix + "LateralAction.", this);
    synchronizeActionGroupBox = new SynchronizeActionGroupBox(fieldprefix + "SynchronizeAction.", this);
    routingActionGroupBox = new RoutingActionGroupBox(fieldprefix + "RoutingAction.", this);

    connect(typeComboBox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(updateActionType()));
    registerField(fieldprefix+"name", nameLineEdit);
    registerField(fieldprefix+"type", typeComboBox, "currentText");

    QString type = typeComboBox->currentText();
    if (type == "EnvironmentAction") {
        environmentActionGroupBox->setVisible(true);
        longitudinalActionGroupBox->setVisible(false);
        lateralActionGroupBox->setVisible(false);
        synchronizeActionGroupBox->setVisible(false);
        routingActionGroupBox->setVisible(false);
    }
    else if (type == "LongitudinalAction") {
        environmentActionGroupBox->setVisible(false);
        longitudinalActionGroupBox->setVisible(true);
        lateralActionGroupBox->setVisible(false);
        synchronizeActionGroupBox->setVisible(false);
        routingActionGroupBox->setVisible(false);
    }
    else if (type == "LateralAction") {
        environmentActionGroupBox->setVisible(false);
        longitudinalActionGroupBox->setVisible(false);
        lateralActionGroupBox->setVisible(true);
        synchronizeActionGroupBox->setVisible(false);
        routingActionGroupBox->setVisible(false);
    }
    else if (type == "SynchronizeAction") {
        environmentActionGroupBox->setVisible(false);
        longitudinalActionGroupBox->setVisible(false);
        lateralActionGroupBox->setVisible(false);
        synchronizeActionGroupBox->setVisible(true);
        routingActionGroupBox->setVisible(false);
    }
    else if (type == "RoutingAction") {
        environmentActionGroupBox->setVisible(false);
        longitudinalActionGroupBox->setVisible(false);
        lateralActionGroupBox->setVisible(false);
        synchronizeActionGroupBox->setVisible(false);
        routingActionGroupBox->setVisible(true);
    }

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(typeLabel, 1, 0);

    layout->addWidget(nameLineEdit, 0, 1);
    layout->addWidget(typeComboBox, 1, 1);
    layout->addWidget(environmentActionGroupBox, 2, 0, 1, 2);
    layout->addWidget(longitudinalActionGroupBox, 3, 0, 1, 2);
    layout->addWidget(lateralActionGroupBox, 4, 0, 1, 2);
    layout->addWidget(synchronizeActionGroupBox, 5, 0, 1, 2);
    layout->addWidget(routingActionGroupBox, 6, 0, 1, 2);
    setLayout(layout);
}

void ActionGroupBox::updateActionType()
{
    QString type = typeComboBox->currentText();
    if (type == "EnvironmentAction") {
        environmentActionGroupBox->setVisible(true);
        longitudinalActionGroupBox->setVisible(false);
        lateralActionGroupBox->setVisible(false);
        synchronizeActionGroupBox->setVisible(false);
        routingActionGroupBox->setVisible(false);
    }
    else if (type == "LongitudinalAction") {
        environmentActionGroupBox->setVisible(false);
        longitudinalActionGroupBox->setVisible(true);
        lateralActionGroupBox->setVisible(false);
        synchronizeActionGroupBox->setVisible(false);
        routingActionGroupBox->setVisible(false);
    }
    else if (type == "LateralAction") {
        environmentActionGroupBox->setVisible(false);
        longitudinalActionGroupBox->setVisible(false);
        lateralActionGroupBox->setVisible(true);
        synchronizeActionGroupBox->setVisible(false);
        routingActionGroupBox->setVisible(false);
    }
    else if (type == "SynchronizeAction") {
        environmentActionGroupBox->setVisible(false);
        longitudinalActionGroupBox->setVisible(false);
        lateralActionGroupBox->setVisible(false);
        synchronizeActionGroupBox->setVisible(true);
        routingActionGroupBox->setVisible(false);
    }
    else if (type == "RoutingAction") {
        environmentActionGroupBox->setVisible(false);
        longitudinalActionGroupBox->setVisible(false);
        lateralActionGroupBox->setVisible(false);
        synchronizeActionGroupBox->setVisible(false);
        routingActionGroupBox->setVisible(true);
    }
}

EventGroupBox::EventGroupBox(QString str, QWidget *parent) : XOSCGroupBox(str,parent)
{
    setTitle("Event");
    nameLabel = new QLabel("name:");
    priorityLabel = new QLabel("priority:");
    conditionNumLabel = new QLabel("Condition Number:");

    nameLineEdit = new QLineEdit;
    priorityComboBox = new QComboBox;
    conditionNumComboBox = NumberQComboBox(MINCONDITIONNUM, MAXCONDITIONNUM);
    priorityComboBox->addItem("overwrite");
    priorityComboBox->addItem("skip");
    priorityComboBox->addItem("parallel");

    actionGroupBox = new ActionGroupBox(fieldprefix+"Action.", this);

    connect(conditionNumComboBox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(updateConditions()));
    registerField(fieldprefix+"name", nameLineEdit);
    registerField(fieldprefix+"priority", priorityComboBox, "currentText");
    registerField(fieldprefix+"conditionNum", conditionNumComboBox, "currentText");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(priorityLabel, 1, 0);
    layout->addWidget(conditionNumLabel, 3, 0);

    layout->addWidget(nameLineEdit, 0, 1);
    layout->addWidget(priorityComboBox, 1, 1);
    layout->addWidget(conditionNumComboBox, 3, 1);
    
    layout->addWidget(actionGroupBox, 2, 0, 1, 2);

    int conditionnum = conditionNumComboBox->currentText().toInt();
    for (int i = 0; i < MAXCONDITIONNUM; ++i) {
        ConditionGroupBox *box = new ConditionGroupBox(fieldprefix+"StartCondition"+QString::number(i)+".", this);
        startConditionGroupBox.append(box);
        box->setTitle("StartCondition"+QString::number(i));
        if (i < conditionnum) {
            box->setVisible(true);
        }
        else {
            box->setVisible(false);
        }
        layout->addWidget(box, i+4, 0, 1, 2);
    }
    setLayout(layout);
}
void EventGroupBox::updateConditions()
{
    int conditionnum = conditionNumComboBox->currentText().toInt();
    for (int i = 0; i < MAXCONDITIONNUM; ++i) {
        if (i < conditionnum) {
            startConditionGroupBox[i]->setVisible(true);
        }
        else {
            startConditionGroupBox[i]->setVisible(false);
        }
    }
}

EventPage::EventPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle("Set Event");
    setSubTitle("Design the events of your scenario.");
    fieldprefix = "Event.";
    QScrollArea* scrollArea = new QScrollArea;
    QWidget *widget = new QWidget;
    QGridLayout *layout = new QGridLayout;
    eventNumLabel = new QLabel("event number:");
    eventNumComboBox = NumberQComboBox(MINEVENTNUM, MAXEVENTNUM);

    layout->addWidget(eventNumLabel, 0, 0);
    layout->addWidget(eventNumComboBox, 0, 1);

    connect(eventNumComboBox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(updateEvent()));
    registerField(fieldprefix+"eventNum", eventNumComboBox, "currentText");

    int eventnum = eventNumComboBox->currentText().toInt();
    for (int i = 0; i < MAXEVENTNUM; ++i) {
        EventGroupBox *box = new EventGroupBox(fieldprefix+"Event"+QString::number(i)+".", this);
        eventGroupBox.append(box);
        box->setTitle("Event"+QString::number(i));
        if (i < eventnum) {
            box->setVisible(true);
        }
        else {
            box->setVisible(false);
        }
        layout->addWidget(box, i+1, 0, 1, 2);
    }

    QVector<QString>::iterator itername;
    QVector<QWidget*>::iterator iterwidget;
    QVector<const char*>::iterator iterproperty;
    for (itername = childfieldname.begin(), iterwidget = childfieldwidget.begin(), iterproperty = childfieldproperty.begin();
      itername != childfieldname.end() && iterwidget!= childfieldwidget.end() && iterproperty != childfieldproperty.end();
      ++itername, ++iterwidget, ++iterproperty
    ) {
        registerField(*itername, *iterwidget, *iterproperty);
    }
    childfieldname.clear();
    childfieldwidget.clear();
    childfieldproperty.clear();
    layout->setAlignment(Qt::AlignTop);
    widget->setLayout(layout);
    scrollArea->setWidget(widget);
    scrollArea->setWidgetResizable(true);

    QGridLayout *wholelayout = new QGridLayout;
    wholelayout->addWidget(scrollArea, 0, 0);
    wholelayout->setAlignment(Qt::AlignTop);
    setLayout(wholelayout);
}
int EventPage::nextId() const
{
    return LicenseWizard::Page_StoryCondition;
}
void EventPage::updateEvent()
{
    int eventnum = eventNumComboBox->currentText().toInt();
    for (int i = 0; i < MAXEVENTNUM; ++i) {
        if (i < eventnum) {
            eventGroupBox[i]->setVisible(true);
        }
        else {
            eventGroupBox[i]->setVisible(false);
        }
    }
}

StoryConditionPage::StoryConditionPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle("Set Story Condition");
    setSubTitle("Set the start conditions and stop conditions of the stories.");
    fieldprefix = "Story.";

    QScrollArea* scrollArea = new QScrollArea;
    QWidget *widget = new QWidget;
    QGridLayout *layout = new QGridLayout;
    startConditionNumLabel = new QLabel("startConditionNum");
    stopConditionNumLabel = new QLabel("stopConditionNum");

    startConditionNumComboBox = NumberQComboBox(MINCONDITIONNUM, MAXCONDITIONNUM);
    stopConditionNumComboBox = NumberQComboBox(MINCONDITIONNUM, MAXCONDITIONNUM);

    layout->addWidget(startConditionNumLabel, 0, 0);
    layout->addWidget(startConditionNumComboBox, 0, 1);
    layout->addWidget(stopConditionNumLabel, 1, 0);
    layout->addWidget(stopConditionNumComboBox, 1, 1);
    connect(startConditionNumComboBox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(updateConditions()));
    connect(stopConditionNumComboBox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(updateConditions()));
    int startConditionNum = startConditionNumComboBox->currentText().toInt();
    int stopConditionNum = stopConditionNumComboBox->currentText().toInt();
    for (int i = 0; i < MAXCONDITIONNUM; ++i) {
        ConditionGroupBox *box = new ConditionGroupBox(fieldprefix+"StartCondition"+QString::number(i)+".", this);
        startConditionGroupBox.append(box);
        box->setTitle("StartCondition"+QString::number(i));
        if (i < startConditionNum) {
            box->setVisible(true);
        }
        else {
            box->setVisible(false);
        }
        layout->addWidget(box, i+2, 0, 1, 2);
    }
    for (int i = 0; i < MAXCONDITIONNUM; ++i) {
        ConditionGroupBox *box = new ConditionGroupBox(fieldprefix+"StopCondition"+QString::number(i)+".", this);
        stopConditionGroupBox.append(box);
        box->setTitle("StopCondition"+QString::number(i));
        if (i < stopConditionNum) {
            box->setVisible(true);
        }
        else {
            box->setVisible(false);
        }
        layout->addWidget(box, i+MAXCONDITIONNUM+2, 0, 1, 2);
    }
    registerField(fieldprefix+"startConditionNum", startConditionNumComboBox, "currentText");
    registerField(fieldprefix+"stopConditionNum", stopConditionNumComboBox, "currentText");
    QVector<QString>::iterator itername;
    QVector<QWidget*>::iterator iterwidget;
    QVector<const char*>::iterator iterproperty;
    for (itername = childfieldname.begin(), iterwidget = childfieldwidget.begin(), iterproperty = childfieldproperty.begin();
      itername != childfieldname.end() && iterwidget!= childfieldwidget.end() && iterproperty != childfieldproperty.end();
      ++itername, ++iterwidget, ++iterproperty
    ) {
        registerField(*itername, *iterwidget, *iterproperty);
    }
    childfieldname.clear();
    childfieldwidget.clear();
    childfieldproperty.clear();
    layout->setAlignment(Qt::AlignTop);
    widget->setLayout(layout);
    scrollArea->setWidget(widget);
    scrollArea->setWidgetResizable(true);
    QGridLayout *wholelayout = new QGridLayout;
    wholelayout->addWidget(scrollArea, 0, 0);
    wholelayout->setAlignment(Qt::AlignTop);
    setLayout(wholelayout);
}
int StoryConditionPage::nextId() const
{
    return LicenseWizard::Page_StopTrigger;
}
void StoryConditionPage::updateConditions()
{
    int startConditionNum = startConditionNumComboBox->currentText().toInt();
    int stopConditionNum = stopConditionNumComboBox->currentText().toInt();
    for (int i = 0; i < MAXCONDITIONNUM; ++i) {
        if (i < startConditionNum) {
            startConditionGroupBox[i]->setVisible(true);
        }
        else {
            startConditionGroupBox[i]->setVisible(false);
        }
    }
    for (int i = 0; i < MAXCONDITIONNUM; ++i) {
        if (i < stopConditionNum) {
            stopConditionGroupBox[i]->setVisible(true);
        }
        else {
            stopConditionGroupBox[i]->setVisible(false);
        }
    }
}

StopTriggerPage::StopTriggerPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle("<i>OpenScenario</i>&trade; StopTrigger");
    setSubTitle("Set your StopTriggers of the whole scenario file.");
    criteria_RunningStopTest = new QLabel("criteria_RunningStopTest(recommended)");
    criteria_RunningRedLightTest = new QLabel("criteria_RunningRedLightTest(recommended)");
    criteria_WrongLaneTest = new QLabel("criteria_WrongLaneTest(recommended)");
    criteria_OnSidewalkTest = new QLabel("criteria_OnSidewalkTest(recommended)");
    criteria_KeepLaneTest = new QLabel("criteria_KeepLaneTest(recommended)");
    criteria_CollisionTest = new QLabel("criteria_CollisionTest(recommended)");
    criteria_DrivenDistanceTestLabel = new QLabel("criteria_DrivenDistanceTest(recommended)");
    DrivenDistanceLabel = new QLabel("DrivenDistance");

    criteria_RunningStopTestCheckBox = new QCheckBox;
    criteria_RunningStopTestCheckBox->setCheckState(Qt::Checked);
    criteria_RunningRedLightTestCheckBox = new QCheckBox;
    criteria_RunningRedLightTestCheckBox->setCheckState(Qt::Checked);
    criteria_WrongLaneTestCheckBox = new QCheckBox;
    criteria_WrongLaneTestCheckBox->setCheckState(Qt::Checked);
    criteria_OnSidewalkTestCheckBox = new QCheckBox;
    criteria_OnSidewalkTestCheckBox->setCheckState(Qt::Checked);
    criteria_KeepLaneTestCheckBox = new QCheckBox;
    criteria_KeepLaneTestCheckBox->setCheckState(Qt::Checked);
    criteria_CollisionTestCheckBox = new QCheckBox;
    criteria_CollisionTestCheckBox->setCheckState(Qt::Checked);
    criteria_DrivenDistanceTestCheckBox = new QCheckBox;
    criteria_DrivenDistanceTestCheckBox->setCheckState(Qt::Checked);
    DrivenDistanceLineEdit = new QLineEdit("100");

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(criteria_RunningStopTest, 0, 0);
    layout->addWidget(criteria_RunningRedLightTest, 1, 0);
    layout->addWidget(criteria_WrongLaneTest, 2, 0);
    layout->addWidget(criteria_OnSidewalkTest, 3, 0);
    layout->addWidget(criteria_KeepLaneTest, 4, 0);
    layout->addWidget(criteria_CollisionTest, 5, 0);
    layout->addWidget(criteria_DrivenDistanceTestLabel, 6, 0);
    layout->addWidget(DrivenDistanceLabel, 7, 0);

    layout->addWidget(criteria_RunningStopTestCheckBox, 0, 1);
    layout->addWidget(criteria_RunningRedLightTestCheckBox, 1, 1);
    layout->addWidget(criteria_WrongLaneTestCheckBox, 2, 1);
    layout->addWidget(criteria_OnSidewalkTestCheckBox, 3, 1);
    layout->addWidget(criteria_KeepLaneTestCheckBox, 4, 1);
    layout->addWidget(criteria_CollisionTestCheckBox, 5, 1);
    layout->addWidget(criteria_DrivenDistanceTestCheckBox, 6, 1);
    layout->addWidget(DrivenDistanceLineEdit, 7, 1);
    fieldprefix = "StopTrigger.";
    registerField(fieldprefix + "criteria_RunningStopTestCheckBox", criteria_RunningStopTestCheckBox);
    registerField(fieldprefix + "criteria_RunningRedLightTestCheckBox", criteria_RunningRedLightTestCheckBox);
    registerField(fieldprefix + "criteria_WrongLaneTestCheckBox", criteria_WrongLaneTestCheckBox);
    registerField(fieldprefix + "criteria_OnSidewalkTestCheckBox", criteria_OnSidewalkTestCheckBox);
    registerField(fieldprefix + "criteria_KeepLaneTestCheckBox", criteria_KeepLaneTestCheckBox);
    registerField(fieldprefix + "criteria_CollisionTestCheckBox", criteria_CollisionTestCheckBox);
    registerField(fieldprefix + "criteria_DrivenDistanceTestCheckBox", criteria_DrivenDistanceTestCheckBox);
    registerField(fieldprefix + "DrivenDistanceLineEdit", DrivenDistanceLineEdit);
    QVector<QString>::iterator itername;
    QVector<QWidget*>::iterator iterwidget;
    QVector<const char*>::iterator iterproperty;
    for (itername = childfieldname.begin(), iterwidget = childfieldwidget.begin(), iterproperty = childfieldproperty.begin();
      itername != childfieldname.end() && iterwidget!= childfieldwidget.end() && iterproperty != childfieldproperty.end();
      ++itername, ++iterwidget, ++iterproperty
    ) {
        registerField(*itername, *iterwidget, *iterproperty);
    }
    childfieldname.clear();
    childfieldwidget.clear();
    childfieldproperty.clear();
    setLayout(layout);
}

int StopTriggerPage::nextId() const
{
    return -1;
}