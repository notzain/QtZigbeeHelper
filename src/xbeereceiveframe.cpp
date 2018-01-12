#include "xbeereceiveframe.h"

XbeeReceiveFrame::XbeeReceiveFrame( //
    const char length_msb,
    const char length_lsb,
    const QByteArray& address64,
    const QByteArray& address16,
    const char options,
    const QByteArray& message,
    const char checksum )
{
    append( SpecialBytes::START );
    append( length_msb );
    append( length_lsb );
    append( 0x90 );
    append( address64 );
    append( address16 );
    append( options );
    append( message );
    append( checksum );
}

QByteArray XbeeReceiveFrame::getAddress64()
{
    return getData().mid( Position::ADDRESS64, 8 );
}

QByteArray XbeeReceiveFrame::getAddress16()
{
    return getData().mid( Position::ADDRESS16, 2 );
}

char XbeeReceiveFrame::getOptions()
{
    return getData().at( Position::OPTIONS );
}

QByteArray XbeeReceiveFrame::getMessage()
{
    // Last byte of the message is the size() minus checksum byte (1)
    // The position of the last byte of the message is size() - 1
    // but QByteArray ensures the array ends with a null terminator
    // so there's an extra byte -> size() - 2
    return getData().mid( Position::MESSAGE, getData().size() - 2 );
}
