#ifndef XBEEREADER_H
#define XBEEREADER_H

#include <QByteArray>
#include <QSharedPointer>
#include <QtCore>

class XbeeFrame;

class XbeeReader : public QObject {
    Q_OBJECT

    QByteArray mData;
    int mExpectedLength = 255;

signals:
    void receivedRxPacket( QSharedPointer<XbeeFrame> packet );

public:
    XbeeReader() = default;
    virtual ~XbeeReader() = default;

    virtual void read( const QByteArray& data );

    virtual XbeeFrame* getFrame();

private:
    void processPacket();
};

#endif // XBEEREADER_H
