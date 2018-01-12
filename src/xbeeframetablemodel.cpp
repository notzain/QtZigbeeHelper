#include "xbeeframetablemodel.h"

#include <QDebug>

XbeeFrameTableModel::XbeeFrameTableModel( QObject* parent )
    : QAbstractTableModel( parent )
{
}

int XbeeFrameTableModel::rowCount( const QModelIndex& parent ) const
{
    return mMap.count();
}

int XbeeFrameTableModel::columnCount( const QModelIndex& parent ) const
{
    // ID, Time and Packet type
    return 3;
}

QVariant XbeeFrameTableModel::headerData(
    int section, Qt::Orientation orientation, int role ) const
{
    if ( role == Qt::DisplayRole ) {
        if ( orientation == Qt::Horizontal ) {
            switch ( section ) {
            case 0:
                return QString( "ID" );
            case 1:
                return QString( "Time" );
            case 2:
                return QString( "Packet type" );
            }
        }
    }
    return QVariant();
}

QVariant XbeeFrameTableModel::data( const QModelIndex& index, int role ) const
{
    if ( role == Qt::DisplayRole ) {
        const int row = index.row();
        const int column = index.column();

        /*
        qDebug() << QString( "Row: %1, Column: %2, Size: %3" )
                        .arg( row )
                        .arg( column )
                        .arg( mMap.count() );
        */

        switch ( column ) {
        // index
        case 0: {
            // return QVariant( "my id" );
            return QVariant( row );
        }
        // time
        case 1: {
            const QTime& time = mMap[row]->time;
            // return QVariant( "my time" );
            return QVariant( time.toString() );
        }
        // frametype name
        case 2: {
            const QString& framename = mMap[row]->packetType;
            // return QVariant( "my frame" );
            return QVariant( framename );
        }
        }
    }

    return QVariant();
}

XbeeFrame* XbeeFrameTableModel::getFrame( const QModelIndex& index )
{
    return mMap[index.row()]->frame.data();
}

void XbeeFrameTableModel::addElement( const QTime& time, QSharedPointer<XbeeFrame> frame )
{
    beginInsertRows(
        QModelIndex(), rowCount( QModelIndex() ), rowCount( QModelIndex() ) );

    Element* element = new Element( this );
    element->time = time;
    element->frame = frame;
    element->packetType = [&] {
        switch ( const auto type = QChar( frame->getFrameType() ).unicode() ) {
        case 0x90:
            return QString( "Rx Packet" );
        default:
            return QString( "Unknown: %1" ).arg( type, 8, 16, QLatin1Char( '0' ) );
        }
    }();

    const int newSize = mMap.count();
    mMap.insert( newSize, element );

    endInsertRows();
}
