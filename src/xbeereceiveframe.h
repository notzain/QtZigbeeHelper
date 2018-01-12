#ifndef XBEERECEIVEFRAME_H
#define XBEERECEIVEFRAME_H

#include "xbeeframe.h"

class XbeeReceiveFrame : public XbeeFrame {
public:
    XbeeReceiveFrame( //
        const char length_msb,
        const char length_lsb,
        const QByteArray& address64,
        const QByteArray& address16,
        const char options,
        const QByteArray& message,
        const char checksum );

    QByteArray getAddress64();
    QByteArray getAddress16();

    char getOptions();

    QByteArray getMessage();

    enum Position {
        ADDRESS64 = 4, //
        ADDRESS16 = ADDRESS64 + 8, //
        OPTIONS = ADDRESS16 + 2, //
        MESSAGE = OPTIONS + 1
    };
};

#endif // XBEERECEIVEFRAME_H
