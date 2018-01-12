#include "xbeeframe.h"

QByteArray XbeeFrame::getDataAsHex( const char seperator ) const
{
    return mData.toHex( seperator );
}

QByteArray& XbeeFrame::getData()
{
    return mData;
}

void XbeeFrame::append( const char byte )
{
    mData.append( byte );
}

void XbeeFrame::append( const QByteArray& array )
{
    mData.append( array );
}

char XbeeFrame::at( const int index ) const
{
    return mData.at( index );
}

int XbeeFrame::getLength() const
{
    return mData.at( Position::LENGTH_LSB );
}

char XbeeFrame::getFrameType() const
{
    return mData.at( Position::FRAMETYPE );
}
