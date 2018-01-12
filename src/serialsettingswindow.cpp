#include "serialsettingswindow.h"
#include "ui_serialsettingswindow.h"

#include <QDebug>
#include <QMap>

// clang-format off
static const QMap<QSerialPort::BaudRate, QString> bauds_as_string {
    { QSerialPort::Baud1200, "1200" },
    { QSerialPort::Baud2400, "2400" },
    { QSerialPort::Baud4800, "4800" },
    { QSerialPort::Baud9600, "9600" },
    { QSerialPort::Baud19200, "19200" },
    { QSerialPort::Baud38400, "38400" },
    { QSerialPort::Baud57600, "57600" },
    { QSerialPort::Baud115200, "115200" }
};

static const QMap<QSerialPort::DataBits, QString> databits_as_string {
    { QSerialPort::Data5, "5" },
    { QSerialPort::Data6, "6" },
    { QSerialPort::Data7, "7" },
    { QSerialPort::Data8, "8" }
};

static const QMap<QSerialPort::FlowControl, QString> flowcontrol_as_string {
    { QSerialPort::NoFlowControl, "None" },
    { QSerialPort::HardwareControl, "Hardware (RTS/CTS)" },
    { QSerialPort::SoftwareControl, "Software (XON/XOFF)" }
};
// clang-format on

SerialSettingsWindow::SerialSettingsWindow( QWidget* parent )
    : QDialog( parent )
    , ui( new Ui::SerialSettingsWindow )
{
    ui->setupUi( this );

    mApplyBtn = ui->applyBtn;
    mCancelBtn = ui->cancelBtn;

    mBaudBox = ui->baudrateCbox;
    mParityBox = ui->parityCbox;
    mFlowBox = ui->flowctrlCbox;
    mDatabitBox = ui->databitsCbox;
    mStopbitBox = ui->stopbitsCbox;

    for ( auto&& baud : bauds_as_string ) {
        mBaudBox->addItem( baud );
    }

    for ( auto&& data : databits_as_string ) {
        mDatabitBox->addItem( data );
    }

    for ( auto&& flow : flowcontrol_as_string ) {
        mFlowBox->addItem( flow );
    }

    setDefaultSettings();

    connect( mCancelBtn, &QPushButton::clicked, this, [this] {
        mBaudBox->setCurrentText( bauds_as_string[mSettings.BaudRate] );
        mFlowBox->setCurrentText( flowcontrol_as_string[mSettings.FlowControl] );
        mDatabitBox->setCurrentText( databits_as_string[mSettings.DataBits] );
        this->reject();
    } );

    connect( mApplyBtn, &QPushButton::clicked, this, [this] {
        mSettings.BaudRate //
            = static_cast<QSerialPort::BaudRate>( mBaudBox->currentText().toInt() );

        mSettings.DataBits //
            = static_cast<QSerialPort::DataBits>( mDatabitBox->currentText().toInt() );

        mSettings.FlowControl // Combobox index and enum value match, so just cast it
            = static_cast<QSerialPort::FlowControl>( mFlowBox->currentIndex() );

        mSettings.StopBits = QSerialPort::OneStop;

        emit settingsChanged( mSettings );
        this->accept();
    } );
}

SerialSettingsWindow::~SerialSettingsWindow()
{
    delete ui;
}

void SerialSettingsWindow::setDefaultSettings()
{
    // default baud
    mBaudBox->setCurrentText( bauds_as_string[QSerialPort::Baud9600] );
    mSettings.BaudRate = QSerialPort::Baud9600;

    // default data bit
    mDatabitBox->setCurrentText( databits_as_string[QSerialPort::Data8] );
    mSettings.DataBits = QSerialPort::Data8;

    // default flow
    mFlowBox->setCurrentText( flowcontrol_as_string[QSerialPort::NoFlowControl] );
    mSettings.FlowControl = QSerialPort::NoFlowControl;
}
