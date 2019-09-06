#include "OSICSMainframeSetupWindow.h"
#include "ui_OSICSMainframeSetupWindow.h"

OSICSMainframeSetupWindow::OSICSMainframeSetupWindow(QVariant &device, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OSICSMainframeSetupWindow)
{
    ui->setupUi(this);
    this->device = device;

    // connect button group
    QObject::connect(ui->configureButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(on_configButton_clicked(int)));
}

OSICSMainframeSetupWindow::~OSICSMainframeSetupWindow()
{
    delete ui;
}

void OSICSMainframeSetupWindow::showEvent( QShowEvent* event )
{
    qDebug() << "mainframe window displayed";
    QWidget::showEvent( event );

    // initialize settings and signal to orchestrator to update them from device
    settings = new QSettings(QSettings::IniFormat, QSettings::SystemScope, "Test Platform");
    settings->clear();
    emit signalUpdateConfigSettings(device, *settings);
}


void OSICSMainframeSetupWindow::slotUpdateWindow(){

    // connect slot to create module classes/windows
    QObject::connect(this, SIGNAL(signalGetEXFOModuleQVariants(QList<ModuleConfigPair>&, QList<QByteArray>, QVariant&)),
                     QObject::sender(), SLOT(slotGetEXFOModuleQVariants(QList<ModuleConfigPair>&, QList<QByteArray>, QVariant&)));

    // store values from settings
    getValuesFromConfig();

    // display values
    populateAllValues();

    // disconnect signal
    QObject::disconnect(QObject::sender(), SIGNAL(signalSettingsUpdated()), this, SLOT(slotUpdateWindow()));

    // if there are no modules in the QVariant modules list, signal to orchestrator to get them

    if(modules.size() == 0 && numInstalledModules > 0){
        emit signalGetEXFOModuleQVariants(modules, moduleNames, device);
    }
}


void OSICSMainframeSetupWindow::getValuesFromConfig(){
    // device name/identity
    deviceIdentity = settings->value(DEVICE_IDENTITY).value<QByteArray>();
    qDebug() << deviceIdentity;

    deviceLocation = settings->value(DEVICE_LOCATION).value<QByteArray>();
    qDebug() << deviceLocation;

    moduleNames = settings->value(EXFO_OSICS_MODULE_NAMES).value<QList<QByteArray>>();
    qDebug() << moduleNames;



    // slot names signal to orchestrator that we need a
    // EXFO MAINFRAME* QVariant, each one needs a config window
    // assigned so that we can call show() on it
    // see if qt will like passing a qlist of qvariants over qsettings


    // we will store on the backend the slot names (from QSettings) for display purposes
    // we need a separate list not tied to QSettings? for the actual Qvariant device pointers
}

void OSICSMainframeSetupWindow::populateAllValues(){
    populateIdentityAndLoc();
    populateModuleNames();
}

void OSICSMainframeSetupWindow::populateIdentityAndLoc(){
    ui->instrumentAddressLabel->setText(deviceLocation);
    ui->instrumentInfoLabel->setText(deviceIdentity);
}

void OSICSMainframeSetupWindow::populateModuleNames(){

    numInstalledModules = 0;
    for(int i = 0; i < EXFO_OSICS_NUM_SLOTS; i++){
        QLabel *label = new QLabel();
        label->setText(moduleNames[i]);
        ui->moduleNameLabelLayout->addWidget(label);

        if(moduleNames[i] != "EMPTY"){
            numInstalledModules++;
        }
        else{
            // disable config button
            int index = i * -1 - 2;
            ui->configureButtonGroup->button(index)->setEnabled(false);
        }
    }
    qDebug() << "num installed" << numInstalledModules;
}


void OSICSMainframeSetupWindow::on_configButton_clicked(int index){
    // QButton groups start at index -2 and decrease by 1
    index = index * -1 - 2;
    qDebug() << index;

    QVariant module = modules[index].first;

    // update settings for the module
    emit signalUpdateConfigSettings(module, *settings);

    modules[index].second->show();
}

