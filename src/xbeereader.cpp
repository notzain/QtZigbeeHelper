#include "xbeereader.h"
#include "xbeeframe.h"
#include "xbeereceiveframe.h"

#include <QChar>
#include <QDebug>

void XbeeReader::read( const QByteArray& data )
{
    static bool escaped = false;

    const auto hexData = data.toHex();

    qDebug() << hexData;

    for ( const QChar byteAsUnicode : data ) {

        // QString hex = hexData.mid( i, 2 );
        // int byte = hex.toUInt( nullptr, 16 );

        // qDebug() << QString( "Hex: %1, Int: %2" ).arg( hex ).arg( byte );

        int byte = byteAsUnicode.unicode();

        if ( byte == XbeeFrame::SpecialBytes::ESCAPE ) {
            escaped = true;
            continue;
        }

        if ( escaped ) {
            byte = byte ^ 0x20;
            escaped = false;
        }

        switch ( auto curSize = mData.length() ) {
        case 0: {
            if ( byte != XbeeFrame::SpecialBytes::START ) {
                continue;
            }
            mData.append( byte );

            break;
        }
        case 2: {
            mExpectedLength = byte + 4;

            mData.append( byte );
            break;
        }
        default: {
            mData.append( byte );
            if ( curSize >= mExpectedLength - 1 ) {
                processPacket();
            }
            break;
        }
        }
    }
}

void XbeeReader::processPacket()
{
    const int type = QChar( mData.at( XbeeFrame::Position::FRAMETYPE ) ).unicode();

    switch ( type ) {
    case 0x90: {

        auto* frame = new XbeeReceiveFrame{
            mData.at( XbeeFrame::Position::LENGTH_MSB ), //
            mData.at( XbeeFrame::Position::LENGTH_LSB ), //
            mData.mid( XbeeReceiveFrame::Position::ADDRESS64, 8 ), //
            mData.mid( XbeeReceiveFrame::Position::ADDRESS16, 2 ), //
            mData.at( XbeeReceiveFrame::Position::OPTIONS ), //
            mData.mid( XbeeReceiveFrame::Position::MESSAGE, mData.size() - 2 ), //
            mData.at( mData.size() - 1 ) //
        };
        auto ptr = QSharedPointer<XbeeFrame>( frame );

        mData.clear();

        emit receivedRxPacket( ptr );
        break;
    }
    }
}

XbeeFrame* XbeeReader::getFrame()
{
    return nullptr;
}
