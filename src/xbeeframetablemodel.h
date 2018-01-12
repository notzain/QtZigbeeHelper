#ifndef XBEEFRAMETABLEMODEL_H
#define XBEEFRAMETABLEMODEL_H

#include "xbeeframe.h"

#include <QAbstractTableModel>
#include <QMap>
#include <QSharedPointer>
#include <QTime>

struct Element : public QObject {
    QTime time;
    QString packetType;
    QSharedPointer<XbeeFrame> frame;

    Element( QObject* parent = 0 )
        : QObject( parent )
    {
    }
};

class XbeeFrameTableModel : public QAbstractTableModel {
public:
    XbeeFrameTableModel( QObject* parent = 0 );

    int rowCount( const QModelIndex& parent ) const;
    int columnCount( const QModelIndex& parent ) const;

    QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
    QVariant data( const QModelIndex& index, int role ) const;

    XbeeFrame* getFrame( const QModelIndex& index );

    void addElement( const QTime& time, QSharedPointer<XbeeFrame> frame );

private:
    QMap<int, Element*> mMap;
};

#endif // XBEEFRAMETABLEMODEL_H
