#ifndef XBEEFRAME_H
#define XBEEFRAME_H

#include <QByteArray>

class XbeeFrame {
    QByteArray mData;

public:
    XbeeFrame() = default;
    virtual ~XbeeFrame() = default;

    virtual QByteArray getDataAsHex( const char seperator = ' ' ) const;

    virtual QByteArray& getData();

    virtual void append( const char byte );

    virtual void append( const QByteArray& array );

    virtual char at( const int index ) const;

    virtual int getLength() const;

    virtual char getFrameType() const;

    enum Position {
        LENGTH_MSB = 1, //
        LENGTH_LSB = 2, //
        FRAMETYPE = 3 //
    };

    enum SpecialBytes {
        START = 0x7E, //
        ESCAPE = 0x7D, //
    };
};

#endif // XBEEFRAME_H
