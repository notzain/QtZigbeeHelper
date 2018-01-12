#ifndef SERIALSETTINGS_H
#define SERIALSETTINGS_H

#include <QSerialPort>

struct SerialSettings {
    using qsp = QSerialPort;

    qsp::BaudRate BaudRate;
    qsp::DataBits DataBits;
    qsp::Direction Direction;
    qsp::FlowControl FlowControl;
    qsp::Parity Parity;
    qsp::StopBits StopBits;
};

#endif // SERIALSETTINGS_H
