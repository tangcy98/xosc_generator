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
class QRadioButton;
QT_END_NAMESPACE

// static QComboBox* BooleanQComboBox(bool defaultopt = true);

class LicenseWizard : public QWizard
{
    Q_OBJECT
public:
    enum { Page_Intro, Page_Filename, Page_Map, Page_Environment,
           Page_Actor, Page_Story, Page_StopTrigger };

    LicenseWizard(QWidget *parent = nullptr);
    void accept() override;
    Environment getEnvironment();
    Actor getActor(int n);
    Story getStory();
    StopTrigger getStopTrigger();

private slots:
    void showHelp();
    
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
    QLabel *nameLabel;
    QComboBox *nameComboBox;
};

class EnvironmentPage : public QWizardPage
{
    Q_OBJECT
public:
    EnvironmentPage(QWidget *parent = nullptr);

    int nextId() const override;

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

#define MINACTORNUM 1
#define MAXACTORNUM 10
#define MINPARANUM 0
#define MAXPARANUM 10
#define MINPROPNUM 0
#define MAXPROPNUM 10

class WorldPositionGroupBox : public QGroupBox
{
    Q_OBJECT
public:
    WorldPositionGroupBox(QWidget *parent = nullptr);
private:
    QLabel *xLabel;
    QLineEdit *xLineEdit;
    QLabel *yLabel;
    QLineEdit *yLineEdit;
    QLabel *zLabel;
    QLineEdit *zLineEdit;
    QLabel *hLabel;
    QLineEdit *hLineEdit;
};
class LanePositionGroupBox : public QGroupBox
{
    Q_OBJECT
public:
    LanePositionGroupBox(QWidget *parent = nullptr);
private:
    QLabel *roadIdLabel;
    QLineEdit *roadIdLineEdit;
    QLabel *laneIdLabel;
    QLineEdit *laneIdLineEdit;
    QLabel *offsetLabel;
    QLineEdit *offsetLineEdit;
    QLabel *sLabel;
    QLineEdit *sLineEdit;
};
class PositionGroupBox : public QGroupBox
{
    Q_OBJECT
public:
    PositionGroupBox(QWidget *parent = nullptr);
private slots:
    void updatePositionType();
private:
    QLabel *typeLabel;
    QComboBox *typeComboBox;

    WorldPositionGroupBox *worldPositionGroupBox;
    LanePositionGroupBox  *lanePositionGroupBox;
};

class PropertiesGroupBox : public QGroupBox
{
    Q_OBJECT
public:
    PropertiesGroupBox(QWidget *parent = nullptr);
private slots:
    void updateProperties();
private:
    QLabel *propertynumberLabel;
    QComboBox *propertynumberComboBox;

    QVector<QLabel *> propertynameLabel;
    QVector<QLineEdit *> propertynameLineEdit;
    QVector<QLabel *> propertyvalueLabel;
    QVector<QLineEdit *> propertyvalueLineEdit;
};
class VehicleGroupBox : public QGroupBox
{
    Q_OBJECT
public:
    VehicleGroupBox(QWidget *parent = nullptr);
private:
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
class PedestrianGroupBox : public QGroupBox
{
    Q_OBJECT
public:
    PedestrianGroupBox(QWidget *parent = nullptr);
private:
    QLabel *massLabel;
    QLineEdit *massLineEdit;
};
class MiscObjectGroupBox : public QGroupBox
{
    Q_OBJECT
public:
    MiscObjectGroupBox(QWidget *parent = nullptr);
private:
    QLabel *massLabel;
    QLineEdit *massLineEdit;
};


class ActorGroupBox : public QGroupBox
{
    Q_OBJECT
public:
    ActorGroupBox(QWidget *parent = nullptr);
private slots:
    void updateName();
private:

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
    QLabel *actornumLabel;
    QComboBox *actornumComboBox;

    QVector<ActorGroupBox*> actorGroupBox;

};


class StopTriggerPage : public QWizardPage
{
    Q_OBJECT
public:
    StopTriggerPage(QWidget *parent = nullptr);

    int nextId() const override;
private slots:

private:
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
