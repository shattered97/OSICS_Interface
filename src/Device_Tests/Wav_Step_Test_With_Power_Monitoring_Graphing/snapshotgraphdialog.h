#ifndef SNAPSHOTGRAPHDIALOG_H
#define SNAPSHOTGRAPHDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "ConversionUtilities.h"

namespace Ui {
class SnapshotGraphDialog;
}

class SnapshotGraphDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SnapshotGraphDialog(QWidget *parent = nullptr);
    ~SnapshotGraphDialog();

    QByteArray getTestStartTime();
    QByteArray getTestCurrentTime();
    void setTestStartTime(double testStartTimeInSec);
    void setTestCurrentTime(double testCurrentTimeInSec);
    double getGraphStartTime();
    double getGraphEndTime();

signals:
    void signalInputValidated();

private slots:
    void on_graphPastTimeRadioBtn_clicked();

    void on_graphCustomStartEndRadioBtn_clicked();

    void on_snapshotGoBackTimeEdit_editingFinished();

    void on_goBackUnitComboBox_currentIndexChanged(const QString &arg1);

    void on_snapshotStartTimeEdit_editingFinished();

    void on_startAndEndTimeUnitComboBox_currentTextChanged(const QString &arg1);

    void on_snapshotEndTimeEdit_editingFinished();

    void on_okButton_clicked();


private:
    Ui::SnapshotGraphDialog *ui;

    bool makePastTimeGraph = true;

    double graphStartTimeInSec = 0;
    double graphEndTimeInSec = 0;

    double testStartTimeInSec = 0;
    double testCurrentTimeInSec = 0;
    double timeToGoBackInSec = 0;

    bool isInputValueNumeric(QString inputValue);
    bool isAllInputValid();
};

#endif // SNAPSHOTGRAPHDIALOG_H
