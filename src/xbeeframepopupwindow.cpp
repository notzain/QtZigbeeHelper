#include "xbeeframepopupwindow.h"
#include "ui_xbeeframepopupwindow.h"

#include "xbeeframe.h"
#include "xbeereceiveframe.h"

#include <QDebug>
#include <QLabel>
#include <QLineEdit>

XbeeFramePopupWindow::XbeeFramePopupWindow( XbeeFrame* frame, QWidget* parent )
    : QDialog( parent )
    , ui( new Ui::XbeeFramePopupWindow )
{
    ui->setupUi( this );

    this->setWindowTitle( "Xbee Frame Details" );

    mAsciiField = ui->asciiTextField;
    mHexField = ui->hexTextField;
    mFrameForm = ui->frameFormLayout;

    mAsciiField->setReadOnly( true );
    mHexField->setReadOnly( true );

    initForm( frame );
}

void XbeeFramePopupWindow::initForm( XbeeFrame* frame )
{
    switch ( const auto type = QChar( frame->getFrameType() ).unicode() ) {
    case 0x90:
        initFormAsRx( frame );
        break;
    default:
        break;
    }
}

void XbeeFramePopupWindow::initFormAsRx( XbeeFrame* frame )
{
    auto* rx_frame = dynamic_cast<XbeeReceiveFrame*>( frame );
    {
        auto val = QString( "0x%1 (%2)" )
                       .arg( QChar( rx_frame->getLength() ).unicode(), 4, 16,
                           QLatin1Char( '0' ) )
                       .arg( rx_frame->getLength() );
        auto* edit = new QLineEdit( val, this );
        edit->setReadOnly( true );
        mFrameForm->addRow( "Length", edit );
    }
    {
        auto val
            = QString( "0x%1" ).arg( QChar( rx_frame->getFrameType() ).unicode(), 0, 16 );
        auto* edit = new QLineEdit( val, this );
        edit->setReadOnly( true );
        mFrameForm->addRow( "Packet type", edit );
    }
    {
        auto val = rx_frame->getAddress64();
        auto* edit = new QLineEdit( "0x" + val.toHex( ' ' ).toUpper(), this );
        edit->setReadOnly( true );
        mFrameForm->addRow( "Source Address (64)", edit );
    }
    {
        auto val = rx_frame->getAddress16();
        auto* edit = new QLineEdit( "0x" + val.toHex( ' ' ).toUpper(), this );
        edit->setReadOnly( true );
        mFrameForm->addRow( "Source Address (16)", edit );
    }

    auto msg = rx_frame->getMessage();

    mHexField->setText( msg.toHex( ' ' ).toUpper() );
    mAsciiField->setText( msg );
}
