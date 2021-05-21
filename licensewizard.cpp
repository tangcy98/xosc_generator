#include "licensewizard.h"
#include <QtWidgets>


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

static QComboBox* BooleanQComboBox(bool defaultopt = true)
{
    QComboBox *box = new QComboBox;
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

static QComboBox* NumberQComboBox(int bottom, int top)
{
    QComboBox *box = new QComboBox;
    if (bottom >= top) return box;
    for (int i = bottom; i < top; ++i) {
        box->addItem(QString::number(i));
    }
    return box;
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
    setOption(HaveHelpButton, true);
    // setPixmap(QWizard::LogoPixmap, QPixmap(":/images/logo.png"));

    connect(this, &QWizard::helpRequested, this, &LicenseWizard::showHelp);

    setWindowTitle(tr("License Wizard"));
}

void LicenseWizard::showHelp()
{
    static QString lastHelpMessage;

    QString message;

    switch (currentId()) {
    case Page_Intro:
        message = tr("The decision you make here will affect which page you "
                     "get to see next.");
        break;
    case Page_Filename:
        message = tr("Make sure to provide a valid email address, such as "
                     "toni.buddenbrook@example.de.");
        break;
    case Page_Map:
        message = tr("If you don't provide an upgrade key, you will be "
                     "asked to fill in your details.");
        break;
    case Page_Environment:
        message = tr("Make sure to provide a valid email address, such as "
                     "thomas.gradgrind@example.co.uk.");
        break;
    case Page_Actor:
        message = tr("You must accept the terms and conditions of the "
                     "license to proceed.");
        break;
    default:
        message = tr("This help is likely not to be of any help.");
    }

    if (lastHelpMessage == message)
        message = tr("Sorry, I already gave what help I could. "
                     "Maybe you should try asking a human?");

    QMessageBox::information(this, tr("License Wizard Help"), message);

    lastHelpMessage = message;
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
    string name = field("Environment.name").toString().toStdString();
    string animation = field("Environment.animation").toString().toStdString();
    string dateTime = field("Environment.dateTime").toString().toStdString();
    string cloudState = field("Environment.cloudState").toString().toStdString();
    string sunintensity = field("Environment.sunintensity").toString().toStdString();
    string azimuth = field("Environment.azimuth").toString().toStdString();
    string elevation = field("Environment.elevation").toString().toStdString();
    string visualRange = field("Environment.visualRange").toString().toStdString();
    string precipitationType = field("Environment.precipitationType").toString().toStdString();
    string precipitationintensity = field("Environment.precipitationintensity").toString().toStdString();
    string frictionScaleFactor = field("Environment.frictionScaleFactor").toString().toStdString();
    Environment environment(
      name.c_str(),
      animation.c_str(),
      dateTime.c_str(),
      cloudState.c_str(),
      sunintensity.c_str(),
      azimuth.c_str(),
      elevation.c_str(),
      visualRange.c_str(),
      precipitationType.c_str(),
      precipitationintensity.c_str(),
      frictionScaleFactor.c_str()
    );
    xosc.setEnvironment(&environment);
    // end - Environment

    // begin - Actor
    int actornum = field("Actor.num").toString().toInt();
    xosc.setActorNum(actornum);
    
    for (int i = 0; i < actornum; ++i) {

    }
    // end - Actor

    // begin - Story

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

Environment getEnvironment()
{

}
Actor getActor(int n)
{

}
Story getStory()
{

}
StopTrigger getStopTrigger()
{

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

    registerField("Filename.filename*", filenameLineEdit);

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

    registerField("Map.name", nameComboBox);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameComboBox, 0, 1);
    setLayout(layout);
}

int MapPage::nextId() const
{
    return LicenseWizard::Page_Environment;
}

EnvironmentPage::EnvironmentPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Fill In Your Environment"));
    setSubTitle(tr("Please fill all the fields. Make sure to provide a valid "
                   "input and recommended values are already given."));

    nameLabel = new QLabel(tr("name:"));
    nameLineEdit = new QLineEdit;
    nameLineEdit->setText("Environment1");
    nameLabel->setBuddy(nameLineEdit);

    animationLabel = new QLabel(tr("animation:"));
    animationComboBox = BooleanQComboBox(false);
    animationLabel->setBuddy(animationComboBox);

    dateTimeLabel = new QLabel(tr("dateTime:"));
    dateTimeLineEdit = new QLineEdit;
    dateTimeLineEdit->setText("2019-06-25T12:00:00");
    dateTimeLabel->setBuddy(dateTimeLineEdit);

    cloudStateLabel = new QLabel(tr("cloudState:"));
    cloudStateComboBox = new QComboBox;
    cloudStateComboBox->addItem("free");
    cloudStateComboBox->addItem("skyOff");
    cloudStateComboBox->addItem("cloudy");
    cloudStateComboBox->addItem("overcast");
    cloudStateComboBox->addItem("rainy");
    cloudStateLabel->setBuddy(cloudStateComboBox);

    sunintensityLabel = new QLabel(tr("sunintensity[0,inf):"));
    sunintensityLineEdit = new QLineEdit;
    sunintensityLineEdit->setText("0.35");
    sunintensityLineEdit->setValidator(new QDoubleValidator(this));
    sunintensityLabel->setBuddy(sunintensityLineEdit);

    azimuthLabel = new QLabel(tr("azimuth[0,2PI]:"));
    azimuthLineEdit = new QLineEdit;
    azimuthLineEdit->setText("0");
    azimuthLineEdit->setValidator(new QDoubleValidator(this));
    azimuthLabel->setBuddy(azimuthLineEdit);

    elevationLabel = new QLabel(tr("elevation:[-PI,PI]"));
    elevationLineEdit = new QLineEdit;
    elevationLineEdit->setText("1.31");
    elevationLineEdit->setValidator(new QDoubleValidator(this));
    elevationLabel->setBuddy(elevationLineEdit);

    visualRangeLabel = new QLabel(tr("visualRange[0,inf):"));
    visualRangeLineEdit = new QLineEdit;
    visualRangeLineEdit->setText("100000.0");
    visualRangeLineEdit->setValidator(new QDoubleValidator(this));
    visualRangeLabel->setBuddy(visualRangeLineEdit);

    precipitationTypeLabel = new QLabel(tr("precipitationType:"));
    precipitationTypeComboBox = new QComboBox;
    precipitationTypeComboBox->addItem("dry");
    precipitationTypeComboBox->addItem("rain");
    precipitationTypeComboBox->addItem("snow");
    precipitationTypeLabel->setBuddy(precipitationTypeComboBox);

    precipitationintensityLabel = new QLabel(tr("precipitationintensity[0,1]:"));
    precipitationintensityLineEdit = new QLineEdit;
    precipitationintensityLineEdit->setText("0.1");
    precipitationintensityLineEdit->setValidator(new QDoubleValidator(this));
    precipitationintensityLabel->setBuddy(precipitationintensityLineEdit);

    frictionScaleFactorLabel = new QLabel(tr("frictionScaleFactor[0,inf):"));
    frictionScaleFactorLineEdit = new QLineEdit;
    frictionScaleFactorLineEdit->setText("1.0");
    frictionScaleFactorLineEdit->setValidator(new QDoubleValidator(this));
    frictionScaleFactorLabel->setBuddy(frictionScaleFactorLineEdit);

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

    registerField("Environment.name", nameLineEdit);
    registerField("Environment.animation", animationComboBox);
    registerField("Environment.dateTime", dateTimeLineEdit);
    registerField("Environment.cloudState", cloudStateComboBox);
    registerField("Environment.sunintensity", sunintensityLineEdit);
    registerField("Environment.azimuth", azimuthLineEdit);
    registerField("Environment.elevation", elevationLineEdit);
    registerField("Environment.visualRange", visualRangeLineEdit);
    registerField("Environment.precipitationType", precipitationTypeComboBox);
    registerField("Environment.precipitationintensity", precipitationintensityLineEdit);
    registerField("Environment.frictionScaleFactor", frictionScaleFactorLineEdit);

    setLayout(layout);
}

int EnvironmentPage::nextId() const
{
    return LicenseWizard::Page_Actor;
}


WorldPositionGroupBox::WorldPositionGroupBox(QWidget *parent) : QGroupBox(parent)
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
LanePositionGroupBox::LanePositionGroupBox(QWidget *parent) : QGroupBox(parent)
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
PositionGroupBox::PositionGroupBox(QWidget *parent) : QGroupBox(parent)
{
    setTitle("Position");
    typeLabel = new QLabel(tr("type:"));
    typeComboBox = new QComboBox;
    typeComboBox->addItem("WorldPosition");
    typeComboBox->addItem("LanePosition");
    worldPositionGroupBox = new WorldPositionGroupBox;
    lanePositionGroupBox = new LanePositionGroupBox;

    connect(typeComboBox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(updatePositionType()));

    if (typeComboBox->currentText() == "WorldPosition") {
        worldPositionGroupBox->setVisible(true);
        worldPositionGroupBox->setVisible(false);
    }
    else {
        worldPositionGroupBox->setVisible(false);
        worldPositionGroupBox->setVisible(true);
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

PropertiesGroupBox::PropertiesGroupBox(QWidget *parent) : QGroupBox(parent)
{
    propertynumberLabel = new QLabel(tr("number of properties:"));
    propertynumberComboBox = NumberQComboBox(MINPROPNUM, MAXPROPNUM);
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
VehicleGroupBox::VehicleGroupBox(QWidget *parent) : QGroupBox(parent)
{
    setTitle("Vehicle Parameters");
    controllerPropertiesGroupBox = new PropertiesGroupBox;
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
PedestrianGroupBox::PedestrianGroupBox(QWidget *parent) : QGroupBox(parent)
{
    setTitle("Pedestrian Parameters");
    QGridLayout *layout = new QGridLayout;
    massLabel = new QLabel("mass(kg):");
    massLineEdit = new QLineEdit("90.0");
    layout->addWidget(massLabel, 0, 0);
    layout->addWidget(massLineEdit, 0, 1);
    setLayout(layout);
}
MiscObjectGroupBox::MiscObjectGroupBox(QWidget *parent) : QGroupBox(parent)
{
    setTitle("MiscObject Parameters");
    QGridLayout *layout = new QGridLayout;
    massLabel = new QLabel("mass(kg):");
    massLineEdit = new QLineEdit("500.0");
    layout->addWidget(massLabel, 0, 0);
    layout->addWidget(massLineEdit, 0, 1);
    setLayout(layout);
}
ActorGroupBox::ActorGroupBox(QWidget *parent) : QGroupBox(parent)
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
    positionGroupBox = new PositionGroupBox;
    propertiesGroupBox = new PropertiesGroupBox;
    vehiclegroupbox = new VehicleGroupBox;
    pedestriangroupbox = new PedestrianGroupBox;
    miscObjectgroupbox = new MiscObjectGroupBox;
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
    actornumComboBox = NumberQComboBox(2, MAXACTORNUM);
    registerField("Actor.num", actornumComboBox);
    QGridLayout *layout = new QGridLayout;
    connect(actornumComboBox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(updateActorPage()));
    layout->addWidget(actornumLabel, 0, 0);
    layout->addWidget(actornumComboBox, 0, 1);
    for (int i = 0; i < MAXACTORNUM; ++i) {
        ActorGroupBox* box = new ActorGroupBox;
        actorGroupBox.append(box);
        box->setTitle("~Actor" + QString::number(i) + " Settings");

        layout->addWidget(box, i + 1, 0, 1, 2);
    }

    // registerField("conclusion.agree*", agreeCheckBox);
    layout->setAlignment(Qt::AlignTop);
    widget->setLayout(layout);
    scrollArea->setWidget(widget);

    QGridLayout *wholelayout = new QGridLayout;
    wholelayout->addWidget(scrollArea, 0, 0);
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
    return LicenseWizard::Page_StopTrigger;
}

StopTriggerPage::StopTriggerPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle("<i>OpenScenario</i>&trade; StopTrigger");
    setSubTitle("Set your StopTriggers of the whole scenario file");
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

    registerField("StopTrigger.criteria_RunningStopTestCheckBox", criteria_RunningStopTestCheckBox);
    registerField("StopTrigger.criteria_RunningRedLightTestCheckBox", criteria_RunningRedLightTestCheckBox);
    registerField("StopTrigger.criteria_WrongLaneTestCheckBox", criteria_WrongLaneTestCheckBox);
    registerField("StopTrigger.criteria_OnSidewalkTestCheckBox", criteria_OnSidewalkTestCheckBox);
    registerField("StopTrigger.criteria_KeepLaneTestCheckBox", criteria_KeepLaneTestCheckBox);
    registerField("StopTrigger.criteria_CollisionTestCheckBox", criteria_CollisionTestCheckBox);
    registerField("StopTrigger.criteria_DrivenDistanceTestCheckBox", criteria_DrivenDistanceTestCheckBox);
    registerField("StopTrigger.DrivenDistanceLineEdit", DrivenDistanceLineEdit);

    setLayout(layout);
}

int StopTriggerPage::nextId() const
{
    return -1;
}