#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMap>
#include <QSerialPortInfo>

// Workaround: getting value from QComboBox->addItem( name, QVariant::fromValue(portInfo)
// using currentData().value<QSerialPortInfo> does not seem to work.
// 0013A200409F77B0

// sky 0013A20040E87A28
// Need to declare Q_DECLARE_METATYPE on a Qt class.
static QMap<QString, QSerialPortInfo> portNameToPortInfo;

MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent )
    , ui( new Ui::MainWindow )
    , mSerSettingsWindow( new SerialSettingsWindow( this ) )
{
    ui->setupUi( this );

    this->setWindowTitle( "XBee Helper Tool" );

    mComportCbox = ui->comportComboBox;
    mComportSettingsBtn = ui->comportSettingsBtn;
    mComportRefreshBtn = ui->comportRefreshBtn;
    mComportConnectBtn = ui->comportConnectBtn;
    mComportConnectBtn->setCheckable( true );
    mComportConnectBtn->setChecked( false );
    mComportConnectBtn->setText( "Connect" );

    fillComportCbox();

    mTableView = ui->serialTableView;

    mTableView->setModel( &mTableModel );
    mTableView->horizontalHeader()->setStretchLastSection( QHeaderView::Stretch );

    connect( mComportConnectBtn, &QPushButton::clicked, //
        this, &MainWindow::toggleComportConnection );

    connect( mComportRefreshBtn, &QPushButton::clicked, //
        this, &MainWindow::fillComportCbox );

    connect( mComportSettingsBtn, &QPushButton::clicked, //
        mSerSettingsWindow, &SerialSettingsWindow::show );

    connect( mSerSettingsWindow, &SerialSettingsWindow::settingsChanged, //
        this, &MainWindow::applyComportSettings );

    connect( &mSerialPort, &QSerialPort::readyRead, //
        this, &MainWindow::onSerialDataAvailable );

    connect( &mXbeeReader, &XbeeReader::receivedRxPacket, //
        this, &MainWindow::onNewPacketArrival );

    connect( mTableView, &QTableView::doubleClicked, //
        this, &MainWindow::onTableViewDoubleClick );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillComportCbox()
{
    mComportCbox->clear();
    portNameToPortInfo.clear();

    for ( const auto& port : QSerialPortInfo::availablePorts() ) {
        const QString portName = QString( "%1 (%2: %3)" )
                                     .arg( port.portName() )
                                     .arg( port.description() )
                                     .arg( port.manufacturer() );

        portNameToPortInfo[portName] = port;
        mComportCbox->addItem( portName );
    }
}

void MainWindow::applyComportSettings( const SerialSettings& settings )
{
    qDebug() << settings.BaudRate << settings.DataBits << settings.FlowControl
             << settings.Parity << settings.StopBits;

    mSerialPort.setBaudRate( settings.BaudRate );
    mSerialPort.setDataBits( settings.DataBits );
    mSerialPort.setFlowControl( settings.FlowControl );
    mSerialPort.setParity( settings.Parity );
    mSerialPort.setStopBits( settings.StopBits );
}

void MainWindow::disconnectFromComport()
{
    if ( mSerialPort.isOpen() ) {
        mSerialPort.close();
    }
}

void MainWindow::connectToComport( const QString& portName )
{
    mSerialPort.setPortName( portName );
    mSerialPort.open( QIODevice::ReadWrite );
}

void MainWindow::connectToComport( const QSerialPortInfo& portInfo )
{
    mSerialPort.setPort( portInfo );
    mSerialPort.open( QIODevice::ReadWrite );
}

void MainWindow::toggleComportConnection()
{
    // button changes state before this function is run
    // so invert state to get the "original" state
    const bool is_connected = !mComportConnectBtn->isChecked();

    // Currently connected, set state to disconnect
    if ( is_connected ) {
        // try
        disconnectFromComport();
        mComportConnectBtn->setChecked( false );
        mComportConnectBtn->setText( "Connect" );

        mComportRefreshBtn->setEnabled( true );
        mComportCbox->setEnabled( true );
        mComportSettingsBtn->setEnabled( true );
    }
    // Currently disconnected, set state to connect
    else {
        // try
        const QSerialPortInfo& port = portNameToPortInfo[mComportCbox->currentText()];

        connectToComport( port );
        mComportConnectBtn->setChecked( true );
        mComportConnectBtn->setText( "Disconnect" );

        mComportRefreshBtn->setEnabled( false );
        mComportCbox->setEnabled( false );
        mComportSettingsBtn->setEnabled( false );
    }
}

void MainWindow::onSerialDataAvailable()
{
    mXbeeReader.read( mSerialPort.readAll() );
}

void MainWindow::onNewPacketArrival( QSharedPointer<XbeeFrame> packet )
{
    mTableModel.addElement( QTime::currentTime(), packet );
}

void MainWindow::onTableViewDoubleClick( const QModelIndex index )
{
    auto* frame = mTableModel.getFrame( index );

    auto* popupWindow = new XbeeFramePopupWindow( frame );
    popupWindow->setAttribute( Qt::WA_DeleteOnClose );
    popupWindow->show();
}
