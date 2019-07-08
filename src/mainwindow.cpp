#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DefaultInstrument.h"
#include "N7714A.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //All of this should be in the main.cpp - we need to walk through this code before we go any farther
    theCommBus.createDefaultRM(defaultSession);
    theCommBus.displayResources(defaultSession, instrAddr, currentSession, &numInstruments, findList, foundResources);

    // need method to turn resources into objects
    // hard code this one to test
    QByteArray theIdentity = foundResources.first().second;
    QByteArray theInstrLoc = foundResources.first().first;

//    // ****** TEST DEFAULT INSTRUMENT *******
//    DefaultInstrument testInstrument(theIdentity, theInstrLoc);


//    // ****** TEST N7714A ******
    N7714A testInstrument(theIdentity, theInstrLoc);

    QByteArray rspSTB;
    testInstrument.DefaultInstrument::querySTB(defaultSession, currentSession, rspSTB);
    qDebug() << "STB: " << rspSTB;

    QByteArray rspESE;
    testInstrument.queryESE(defaultSession, currentSession, rspESE);
    qDebug() << "ESE: " << rspESE;

    QByteArray rspESR;
    testInstrument.queryESR(defaultSession, currentSession, rspESR);
    qDebug() << "ESR: " << rspESR;

    QByteArray rspOPC;
    testInstrument.queryOPC(defaultSession, currentSession, rspOPC);
    qDebug() << "OPC : " << rspOPC;

    QByteArray rspTST;
    testInstrument.queryTST(defaultSession, currentSession, rspTST);
    qDebug() << "TST: " << rspTST;

    QByteArray rspOPT;
    testInstrument.queryOPT(defaultSession, currentSession, rspOPT);
    qDebug() << "OPT: " << rspOPT;

    QByteArray rspIDN;
    testInstrument.queryIDN(defaultSession, currentSession, rspIDN);
    qDebug() << "IDN: " << rspIDN;


////// ******* Run default commands with no response *******

    testInstrument.execESE(defaultSession, currentSession, 8);
    QByteArray testSetESE;
    testInstrument.queryESE(defaultSession, currentSession, testSetESE);
    qDebug() << "ESE: " << testSetESE;

    testInstrument.execCLS(defaultSession, currentSession);
    testInstrument.execOPC(defaultSession, currentSession);
    testInstrument.execRST(defaultSession, currentSession);
    testInstrument.execWAI(defaultSession, currentSession);


//// ******** TEST N7714A SPECIFIC COMMANDS




}

MainWindow::~MainWindow()
{
    delete ui;
    theCommBus.closeDefaultSession(defaultSession);

}
