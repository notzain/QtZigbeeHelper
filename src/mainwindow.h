#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "serialsettings.h"
#include "serialsettingswindow.h"
#include "xbeeframetablemodel.h"
#include "xbeereader.h"

#include "xbeeframepopupwindow.h"

#include <QComboBox>
#include <QMainWindow>
#include <QPushButton>
#include <QSerialPort>

#include <QTableView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow( QWidget* parent = 0 );
    ~MainWindow();

private:
    Ui::MainWindow* ui;

    QSerialPort mSerialPort;
    XbeeReader mXbeeReader;

    SerialSettingsWindow* mSerSettingsWindow;

    QComboBox* mComportCbox;
    QPushButton* mComportConnectBtn;
    QPushButton* mComportRefreshBtn;
    QPushButton* mComportSettingsBtn;

    XbeeFrameTableModel mTableModel;
    QTableView* mTableView;

    void fillComportCbox();
    void applyComportSettings( const SerialSettings& settings );
    void disconnectFromComport();
    void connectToComport( const QString& portName );
    void connectToComport( const QSerialPortInfo& portInfo );
    void toggleComportConnection();

    void onSerialDataAvailable();
    void onNewPacketArrival( QSharedPointer<XbeeFrame> packet );
    void onTableViewDoubleClick( const QModelIndex index );
};

#endif // MAINWINDOW_H
