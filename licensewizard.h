#ifndef LICENSEWIZARD_H
#define LICENSEWIZARD_H

#include <QWizard>
#include <QComboBox>
#include <QGroupBox>
#include "xosc_generator.h"

QT_BEGIN_NAMESPACE
class QCheckBox;
class QLabel;
class QLineEdit;
QT_END_NAMESPACE

// static QComboBox* BooleanQComboBox(bool defaultopt = true);

#define MINACTORNUM 0
#define MAXACTORNUM 8
#define MINPARANUM 0
#define MAXPARANUM 6
#define MINPROPNUM 0
#define MAXPROPNUM 6

class XOSCGroupBox : public QGroupBox
{
    Q_OBJECT
public:
    XOSCGroupBox(QString str, QWidget *parent = nullptr);
protected:
    void registerField(QString str, QWidget *widget,const char *property = nullptr);
    
protected:
    QString fieldprefix;
};

class LicenseWizard : public QWizard
{
    Q_OBJECT
public:
    enum { Page_Intro, Page_Filename, Page_Map, Page_Environment,
           Page_Actor, Page_Story, Page_Event, Page_StoryCondition,
           Page_StopTrigger };

    LicenseWizard(QWidget *parent = nullptr);
    void accept() override;
};

class IntroPage : public QWizardPage
{
    Q_OBJECT
public:
    IntroPage(QWidget *parent = nullptr);
    int nextId() const override;
private:
    QLabel *topLabel;
};

class FilenamePage : public QWizardPage
{
    Q_OBJECT
public:
    FilenamePage(QWidget *parent = nullptr);
    // ~FilenamePage();
    int nextId() const override;

private:
    QString fieldprefix;
    QLabel *filenameLabel;
    QLineEdit *filenameLineEdit;
    QLabel *filenameExampleLabel;
};

class MapPage : public QWizardPage
{
    Q_OBJECT
public:
    MapPage(QWidget *parent = nullptr);

    int nextId() const override;

private:
    QString fieldprefix;
    QLabel *nameLabel;
    QComboBox *nameComboBox;
};

class EnvironmentGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    EnvironmentGroupBox(QString str, QWidget *parent = nullptr);
private:
    QLabel *nameLabel;
    QLabel *animationLabel;
    QLabel *dateTimeLabel;
    QLabel *cloudStateLabel;
    QLabel *sunintensityLabel;
    QLabel *azimuthLabel;
    QLabel *elevationLabel;
    QLabel *visualRangeLabel;
    QLabel *precipitationTypeLabel;
    QLabel *precipitationintensityLabel;
    QLabel *frictionScaleFactorLabel;

    QLineEdit *nameLineEdit;
    QComboBox *animationComboBox;
    QLineEdit *dateTimeLineEdit;
    QComboBox *cloudStateComboBox;
    QLineEdit *sunintensityLineEdit;
    QLineEdit *azimuthLineEdit;
    QLineEdit *elevationLineEdit;
    QLineEdit *visualRangeLineEdit;
    QComboBox *precipitationTypeComboBox;
    QLineEdit *precipitationintensityLineEdit;
    QLineEdit *frictionScaleFactorLineEdit;
};

class EnvironmentPage : public QWizardPage
{
    Q_OBJECT
public:
    EnvironmentPage(QWidget *parent = nullptr);

    int nextId() const override;

private:
    QString fieldprefix;
    EnvironmentGroupBox *environmentGroupBox;
};

class WorldPositionGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    WorldPositionGroupBox(QString str, QWidget *parent = nullptr);
    
private:
    // QString fieldprefix;
    QLabel *xLabel;
    QLineEdit *xLineEdit;
    QLabel *yLabel;
    QLineEdit *yLineEdit;
    QLabel *zLabel;
    QLineEdit *zLineEdit;
    QLabel *hLabel;
    QLineEdit *hLineEdit;
};
class LanePositionGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    LanePositionGroupBox(QString str, QWidget *parent = nullptr);
private:
    // QString fieldprefix;
    QLabel *roadIdLabel;
    QLineEdit *roadIdLineEdit;
    QLabel *laneIdLabel;
    QLineEdit *laneIdLineEdit;
    QLabel *offsetLabel;
    QLineEdit *offsetLineEdit;
    QLabel *sLabel;
    QLineEdit *sLineEdit;
};
class PositionGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    PositionGroupBox(QString str, QWidget *parent = nullptr);
private slots:
    void updatePositionType();
private:
    // QString fieldprefix;
    QLabel *typeLabel;
    QComboBox *typeComboBox;

    WorldPositionGroupBox *worldPositionGroupBox;
    LanePositionGroupBox  *lanePositionGroupBox;
};

class PropertiesGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    PropertiesGroupBox(QString str, QWidget *parent = nullptr);
private slots:
    void updateProperties();
private:
    // QString fieldprefix;
    QLabel *propertynumberLabel;
    QComboBox *propertynumberComboBox;

    QVector<QLabel *> propertynameLabel;
    QVector<QLineEdit *> propertynameLineEdit;
    QVector<QLabel *> propertyvalueLabel;
    QVector<QLineEdit *> propertyvalueLineEdit;
};
class VehicleGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    VehicleGroupBox(QString str, QWidget *parent = nullptr);
private:
    // QString fieldprefix;
    QLabel *maxSpeedLabel;
    QLabel *maxAccelerationLabel;
    QLabel *maxDecelerationLabel;
    QLabel *frontAxleMaxSteeringLabel;
    QLabel *frontAxleWheelDiameterLabel;
    QLabel *frontAxleTrackWidthLabel;
    QLabel *frontAxlePositionXLabel;
    QLabel *frontAxlePositionZLabel;
    QLabel *rearAxleMaxSteeringLabel;
    QLabel *rearAxleWheelDiameterLabel;
    QLabel *rearAxleTrackWidthLabel;
    QLabel *rearAxlePositionXLabel;
    QLabel *rearAxlePositionZLabel;
    QLabel *controllerNameLabel;
    QLabel *ThrottleValueLabel;
    QLabel *ThrottleActiveLabel;
    QLabel *BrakeValueLabel;
    QLabel *BrakeActiveLabel;
    QLabel *ClutchValueLabel;
    QLabel *ClutchActiveLabel;
    QLabel *ParkingBrakeValueLabel;
    QLabel *ParkingBrakeActiveLabel;
    QLabel *SteeringWheelValueLabel;
    QLabel *SteeringWheelActiveLabel;
    QLabel *GearNumberLabel;
    QLabel *GearActiveLabel;
    QLineEdit *maxSpeedLineEdit;
    QLineEdit *maxAccelerationLineEdit;
    QLineEdit *maxDecelerationLineEdit;
    QLineEdit *frontAxleMaxSteeringLineEdit;
    QLineEdit *frontAxleWheelDiameterLineEdit;
    QLineEdit *frontAxleTrackWidthLineEdit;
    QLineEdit *frontAxlePositionXLineEdit;
    QLineEdit *frontAxlePositionZLineEdit;
    QLineEdit *rearAxleMaxSteeringLineEdit;
    QLineEdit *rearAxleWheelDiameterLineEdit;
    QLineEdit *rearAxleTrackWidthLineEdit;
    QLineEdit *rearAxlePositionXLineEdit;
    QLineEdit *rearAxlePositionZLineEdit;
    QLineEdit *controllerNameLineEdit;
    QLineEdit *ThrottleValueLineEdit;
    QComboBox *ThrottleActiveComboBox;
    QLineEdit *BrakeValueLineEdit;
    QComboBox *BrakeActiveComboBox;
    QLineEdit *ClutchValueLineEdit;
    QComboBox *ClutchActiveComboBox;
    QLineEdit *ParkingBrakeValueLineEdit;
    QComboBox *ParkingBrakeActiveComboBox;
    QLineEdit *SteeringWheelValueLineEdit;
    QComboBox *SteeringWheelActiveComboBox;
    QLineEdit *GearNumberLineEdit;
    QComboBox *GearActiveComboBox;

    PropertiesGroupBox *controllerPropertiesGroupBox;
};
class PedestrianGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    PedestrianGroupBox(QString str, QWidget *parent = nullptr);
private:
    // QString fieldprefix;
    QLabel *massLabel;
    QLineEdit *massLineEdit;
};
class MiscObjectGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    MiscObjectGroupBox(QString str, QWidget *parent = nullptr);
private:
    // QString fieldprefix;
    QLabel *massLabel;
    QLineEdit *massLineEdit;
};


class ActorGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    ActorGroupBox(QString str, QWidget *parent = nullptr);
private slots:
    void updateName();
private:
    // QString fieldprefix;
    QLabel *typeLabel;
    QComboBox *typeComboBox;

    QLabel *objectnameLabel;
    QLineEdit *objectnameLineEdit;

    QLabel *nameLabel;
    QComboBox *nameComboBox;

    QLabel *categoryLabel;
    QComboBox *categoryComboBox;

    // QLabel *paranumLabel;        // Unsupported
    // QComboBox *paranumComboBox;  // Unsupported

    QLabel *boundingxLabel;
    QLineEdit *boundingxLineEdit;
    QLabel *boundingyLabel;
    QLineEdit *boundingyLineEdit;
    QLabel *boundingzLabel;
    QLineEdit *boundingzLineEdit;

    QLabel *boundingwLabel;
    QLineEdit *boundingwLineEdit;
    QLabel *boundinglLabel;
    QLineEdit *boundinglLineEdit;
    QLabel *boundinghLabel;
    QLineEdit *boundinghLineEdit;

    PositionGroupBox    *positionGroupBox;
    PropertiesGroupBox  *propertiesGroupBox;
    VehicleGroupBox     *vehiclegroupbox;
    PedestrianGroupBox  *pedestriangroupbox;
    MiscObjectGroupBox  *miscObjectgroupbox;
};

class ActorPage : public QWizardPage
{
    Q_OBJECT
public:
    ActorPage(QWidget *parent = nullptr);

    void initializePage() override;
    int nextId() const override;
private slots:
    void updateActorPage();

private:
    QString fieldprefix;
    QLabel *actornumLabel;
    QComboBox *actornumComboBox;

    QVector<ActorGroupBox*> actorGroupBox;

};

#define MINCONDITIONNUM 0
#define MAXCONDITIONNUM 10
class ParameterConditionGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    ParameterConditionGroupBox(QString str, QWidget *parent = nullptr);
private:
    QLabel *parameterRefLabel;
    QLabel *valueLabel;
    QLabel *ruleLabel;

    QLineEdit *parameterRefLineEdit;
    QLineEdit *valueLineEdit;
    QComboBox *ruleComboBox;
};
class SimulationTimeConditionGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    SimulationTimeConditionGroupBox(QString str, QWidget *parent = nullptr);
private:
    QLabel *valueLabel;
    QLabel *ruleLabel;

    QLineEdit *valueLineEdit;
    QComboBox *ruleComboBox;
};
class StoryboardElementStateConditionGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    StoryboardElementStateConditionGroupBox(QString str, QWidget *parent = nullptr);
private:
    QLabel *storyboardElementTypeLabel;
    QLabel *storyboardElementRefLabel;
    QLabel *stateLabel;

    QComboBox *storyboardElementTypeComboBox;
    QComboBox *storyboardElementRefComboBox;
    QComboBox *stateComboBox;
};
class StandStillConditionGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    StandStillConditionGroupBox(QString str, QWidget *parent = nullptr);
private:
    QLabel *durationLabel;
    QLineEdit *durationLineEdit;
};
class TraveledDistanceConditionGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    TraveledDistanceConditionGroupBox(QString str, QWidget *parent = nullptr);
private:
    QLabel *valueLabel;
    QLineEdit *valueLineEdit;
};
class ReachPositionConditionGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    ReachPositionConditionGroupBox(QString str, QWidget *parent = nullptr);
private:
    QLabel *toleranceLabel;
    QLineEdit *toleranceLineEdit;
    PositionGroupBox *positionGroupBox;
};
class RelativeDistanceConditionGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    RelativeDistanceConditionGroupBox(QString str, QWidget *parent = nullptr);
private:
    QLabel *entityRefLabel;
    QLabel *relativeDistanceTypeLabel;
    QLabel *valueLabel;
    QLabel *freespaceLabel;
    QLabel *ruleLabel;

    QComboBox *entityRefComboBox;
    QComboBox *relativeDistanceTypeComboBox;
    QLineEdit *valueLineEdit;
    QComboBox *freespaceComboBox;
    QComboBox *ruleComboBox;
};

class ConditionGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    ConditionGroupBox(QString str, QWidget *parent = nullptr);
private slots:
    void updateConditionType();
private:
    QLabel *nameLabel;
    QLabel *delayLabel;
    QLabel *conditionEdgeLabel;
    QLabel *triggeringEntityRefLabel;
    QLabel *typeLabel;

    QLineEdit *nameLineEdit;
    QLineEdit *delayLineEdit;
    QComboBox *conditionEdgeComboBox;
    QComboBox *triggeringEntityRefComboBox;
    QComboBox *typeComboBox;

    ParameterConditionGroupBox *parameterConditionGroupBox;
    SimulationTimeConditionGroupBox *simulationTimeConditionGroupBox;
    StoryboardElementStateConditionGroupBox *storyboardElementStateConditionGroupBox;
    StandStillConditionGroupBox *standStillConditionGroupBox;
    TraveledDistanceConditionGroupBox *traveledDistanceConditionGroupBox;
    ReachPositionConditionGroupBox *reachPositionConditionGroupBox;
    RelativeDistanceConditionGroupBox *relativeDistanceConditionGroupBox;
};

class StoryPage : public QWizardPage
{
    Q_OBJECT
public:
    StoryPage(QWidget *parent = nullptr);
    int nextId() const override;

private:
    QString fieldprefix;
    QLabel *storyNameLabel;
    QLabel *actNameLabel;
    QLabel *maneuverGroupNameLabel;
    QLabel *maximumExecutionCountLabel;
    QLabel *selectTriggeringEntitiesLabel;
    QLabel *entityRefLabel;
    QLabel *maneuverNameLabel;


    QLineEdit *storyNameLineEdit;
    QLineEdit *actNameLineEdit;
    QLineEdit *maneuverGroupNameLineEdit;
    QLineEdit *maximumExecutionCountLineEdit;
    QComboBox *selectTriggeringEntitiesComboBox;
    QComboBox *entityRefComboBox;
    QLineEdit *maneuverNameLineEdit;
};

class EnvironmentActionGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    EnvironmentActionGroupBox(QString str, QWidget *parent = nullptr);
private:
    EnvironmentGroupBox *environmentGroupBox;
};
class LongitudinalActionGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    LongitudinalActionGroupBox(QString str, QWidget *parent = nullptr);
private:
    QLabel *dynamicsShapeLabel;
    QLabel *dynamicsvalueLabel;
    QLabel *dynamicsDimensionLabel;
    QLabel *targetvalueLabel;

    QComboBox *dynamicsShapeComboBox;
    QLineEdit *dynamicsvalueLineEdit;
    QComboBox *dynamicsDimensionComboBox;
    QLineEdit *targetvalueLineEdit;
};
class LateralActionGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    LateralActionGroupBox(QString str, QWidget *parent = nullptr);
private:
    QLabel *dynamicsShapeLabel;
    QLabel *dynamicsvalueLabel;
    QLabel *dynamicsDimensionLabel;
    QLabel *targetentityRefLabel;
    QLabel *targetvalueLabel;

    QComboBox *dynamicsShapeComboBox;
    QLineEdit *dynamicsvalueLineEdit;
    QComboBox *dynamicsDimensionComboBox;
    QComboBox *targetentityRefComboBox;
    QLineEdit *targetvalueLineEdit;
};

class SynchronizeActionGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    SynchronizeActionGroupBox(QString str, QWidget *parent = nullptr);
private:
    QLabel *masterEntityRefLabel;
    QLabel *relativeSpeedToMasterValueLabel;
    QLabel *speedTargetValueTypeLabel;

    QComboBox *masterEntityRefComboBox;
    QLineEdit *relativeSpeedToMasterValueLineEdit;
    QComboBox *speedTargetValueTypeComboBox;


    PositionGroupBox *targetPositionMasterGroupBox;
    PositionGroupBox *targetPositionGroupBox;
};
class RoutingActionGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    RoutingActionGroupBox(QString str, QWidget *parent = nullptr);
private:
    PositionGroupBox *positionGroupBox;
};

class ActionGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    ActionGroupBox(QString str, QWidget *parent = nullptr);
private slots:
    void updateActionType();
private:
    QLabel *nameLabel;
    QLabel *typeLabel;

    QLineEdit *nameLineEdit;
    QComboBox *typeComboBox;
    EnvironmentActionGroupBox *environmentActionGroupBox;
    LongitudinalActionGroupBox *longitudinalActionGroupBox;
    LateralActionGroupBox *lateralActionGroupBox;
    SynchronizeActionGroupBox *synchronizeActionGroupBox;
    RoutingActionGroupBox *routingActionGroupBox;
};

class EventGroupBox : public XOSCGroupBox
{
    Q_OBJECT
public:
    EventGroupBox(QString str, QWidget *parent = nullptr);
private slots:
    void updateConditions();
private:
    QLabel *nameLabel;
    QLabel *priorityLabel;
    QLabel *conditionNumLabel;

    QLineEdit *nameLineEdit;
    QComboBox *priorityComboBox;
    QComboBox *conditionNumComboBox;
    ActionGroupBox *actionGroupBox;
    QVector<ConditionGroupBox*> startConditionGroupBox;
};

#define MAXEVENTNUM 8
#define MINEVENTNUM 0
class EventPage : public QWizardPage
{
    Q_OBJECT
public:
    EventPage(QWidget *parent = nullptr);
    int nextId() const override;
private slots:
    void updateEvent();
private:
    QString fieldprefix;
    QLabel *eventNumLabel;
    QComboBox *eventNumComboBox;

    QVector< EventGroupBox* > eventGroupBox;
};

class StoryConditionPage : public QWizardPage
{
    Q_OBJECT
public:
    StoryConditionPage(QWidget *parent = nullptr);
    int nextId() const override;
private slots:
    void updateConditions();
private:
    QString fieldprefix;
    QLabel *startConditionNumLabel;
    QLabel *stopConditionNumLabel;

    QComboBox *startConditionNumComboBox;
    QComboBox *stopConditionNumComboBox;

    QVector<ConditionGroupBox*> startConditionGroupBox;
    QVector<ConditionGroupBox*> stopConditionGroupBox;
};

class StopTriggerPage : public QWizardPage
{
    Q_OBJECT
public:
    StopTriggerPage(QWidget *parent = nullptr);
    int nextId() const override;

private:
    QString fieldprefix;
    QLabel *criteria_RunningStopTest;
    QLabel *criteria_RunningRedLightTest;
    QLabel *criteria_WrongLaneTest;
    QLabel *criteria_OnSidewalkTest;
    QLabel *criteria_KeepLaneTest;
    QLabel *criteria_CollisionTest;
    QLabel *criteria_DrivenDistanceTestLabel;
    QLabel *DrivenDistanceLabel;

    QCheckBox *criteria_RunningStopTestCheckBox;
    QCheckBox *criteria_RunningRedLightTestCheckBox;
    QCheckBox *criteria_WrongLaneTestCheckBox;
    QCheckBox *criteria_OnSidewalkTestCheckBox;
    QCheckBox *criteria_KeepLaneTestCheckBox;
    QCheckBox *criteria_CollisionTestCheckBox;
    QCheckBox *criteria_DrivenDistanceTestCheckBox;
    QLineEdit *DrivenDistanceLineEdit;
};

#endif
