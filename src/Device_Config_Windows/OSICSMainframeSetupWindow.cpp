#include "OSICSMainframeSetupWindow.h"
#include "ui_OSICSMainframeSetupWindow.h"

OSICSMainframeSetupWindow::OSICSMainframeSetupWindow(QVariant &device, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OSICSMainframeSetupWindow)
{
    ui->setupUi(this);
    this->device = device;

    // initialize settings
    settings = new QSettings(QSettings::IniFormat, QSettings::SystemScope, "Test Platform");
    settings->clear();

    // connect button group
    QObject::connect(ui->configureButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(on_configButton_clicked(int)));
}

OSICSMainframeSetupWindow::~OSICSMainframeSetupWindow()
{
    delete ui;
}

void OSICSMainframeSetupWindow::showEvent( QShowEvent* event )
{

    // disable cursor (re-enabled in slotUpdateWindow)
    QApplication::setOverrideCursor(Qt::WaitCursor);

    QWidget::showEvent( event );
    if(!windowConfigured){
        emit signalUpdateConfigSettings(device, settings);
    }

    windowConfigured = true;

}


void OSICSMainframeSetupWindow::slotUpdateWindow(){

    // if modules/config windows haven't been added for this window, connect w/ orchestrator and get them
    if(moduleConfigPairs.size() == 0){
        // connect signal to orchestrator to get modules and module windows
        QObject::connect(this, SIGNAL(signalGetEXFOModuleConfigPairs(QVariant , QMap<int, ModuleConfigPair> *)),
                         QObject::sender(), SLOT(slotGetEXFOModuleConfigPairs(QVariant , QMap<int, ModuleConfigPair> *)));
        emit signalGetEXFOModuleConfigPairs(device, &moduleConfigPairs);
    }

    // store values from settings
    getValuesFromConfig();

    // display values
    populateAllValues();

    // disconnect signal
    QObject::disconnect(QObject::sender(), SIGNAL(signalSettingsUpdated()), this, SLOT(slotUpdateWindow()));

    // enable cursor
    QApplication::restoreOverrideCursor();

}


void OSICSMainframeSetupWindow::getValuesFromConfig(){

    deviceIdentity = settings->value(DEVICE_IDENTITY).value<QByteArray>();
    deviceLocation = settings->value(DEVICE_ADDRESS).value<QByteArray>();
    deviceNickname = settings->value(DEVICE_NICKNAME).value<QByteArray>();
    moduleNames = settings->value(EXFO_OSICS_MODULE_NAMES).value<QList<QByteArray>>();
}

void OSICSMainframeSetupWindow::populateAllValues(){
    populateIdentityAndLoc();
    if(!moduleTypesDisplayed){
        populateModuleNames();
    }

}

void OSICSMainframeSetupWindow::populateIdentityAndLoc(){
    ui->instrumentAddressLabel->setText(deviceLocation);
    ui->instrumentInfoLabel->setText(deviceNickname);
}

void OSICSMainframeSetupWindow::populateModuleNames(){

    numInstalledModules = 0;
    for(int i = 0; i < EXFO_OSICS_NUM_SLOTS; i++){
        QLabel *label = new QLabel();
        // set font
        QFont font = label->font();
        font.setPointSize(12);
        label->setFont(font);
        label->setText(moduleNames[i]);
        label->setAlignment(Qt::AlignCenter);
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
    moduleTypesDisplayed = true;
}


void OSICSMainframeSetupWindow::on_configButton_clicked(int index){
    // QButton groups start at index -2 and decrease by 1
    index = index * -1 - 2;

    QVariant module = moduleConfigPairs.value(index + 1).first;
    QMainWindow *configWindow = moduleConfigPairs.value(index + 1).second;


    // update settings (for mainframe, if any)
//    emit signalUpdateConfigSettings(module, *settings);

    // connect the window to be shown with a slot that forwards apply/update
    // config settings to orchestrator

    //  we only want to carry out this connect() if the window hasn't been configured yet
    if(!moduleConfiguredStatusList[index]){
        QObject::connect(configWindow, SIGNAL(signalApplyConfigSettings(QVariant, QSettings *)),
                         this, SLOT(slotForwardApplyConfigSettings(QVariant, QSettings *)));

        QObject::connect(configWindow, SIGNAL(signalUpdateConfigSettings(QVariant, QSettings *)),
                         this, SLOT(slotForwardUpdateConfigSettings(QVariant, QSettings *)));
    }

    configWindow->show();
    moduleConfiguredStatusList[index] = true;
}


void OSICSMainframeSetupWindow::slotForwardApplyConfigSettings(QVariant deviceVariant, QSettings *configSettings){
    emit signalApplyConfigSettings(deviceVariant, settings);
}

void OSICSMainframeSetupWindow::slotForwardUpdateConfigSettings(QVariant deviceVariant, QSettings *configSettings){
    emit signalUpdateConfigSettings(deviceVariant, settings);
}


void OSICSMainframeSetupWindow::on_setNicknameBtn_clicked()
{
    // open dialog box with text entry field
    bool ok;
    QString nicknameText = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                                 tr("Enter desired nickname for device."),
                                                 QLineEdit::Normal, "", &ok);
    if(ok && !nicknameText.trimmed().isEmpty()){
        deviceNickname = nicknameText.toLatin1();
                        settings->setValue(DEVICE_NICKNAME, QVariant::fromValue(deviceNickname));
    }

    emit signalApplyConfigSettings(device, settings);

}
