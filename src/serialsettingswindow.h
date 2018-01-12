#ifndef SERIALSETTINGSWINDOW_H
#define SERIALSETTINGSWINDOW_H

#include "serialsettings.h"
#include <QComboBox>
#include <QDialog>
#include <QMap>
#include <QSerialPort>

namespace Ui {
class SerialSettingsWindow;
}

class SerialSettingsWindow : public QDialog {
    Q_OBJECT
public:
    explicit SerialSettingsWindow( QWidget* parent = nullptr );
    ~SerialSettingsWindow();

signals:
    void settingsChanged( const SerialSettings& settings );

private:
    Ui::SerialSettingsWindow* ui;

    SerialSettings mSettings;

    QPushButton* mApplyBtn;
    QPushButton* mCancelBtn;

    QComboBox* mBaudBox;
    QComboBox* mFlowBox;
    QComboBox* mParityBox;
    QComboBox* mDatabitBox;
    QComboBox* mStopbitBox;

    void setDefaultSettings();

public:
    const SerialSettings& getCurrentSettings() const { return mSettings; }
};

#endif // SERIALSETTINGSWINDOW_H
