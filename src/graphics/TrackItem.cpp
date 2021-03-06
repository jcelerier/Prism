#include <QPainter>
#include <QDebug>

#include "TrackItem.h"

const int       TRACK_HEIGHT        = 15;
const int       TRACK_TITLE_WIDTH   = 100;
const int       TRACK_TITLE_MARGIN  = 10;


TrackItem::TrackItem( TrackModel *trackModel )
{
    pTrackModel = trackModel;
    connect( pTrackModel, SIGNAL(clipInserted()), SLOT(updateClips()) );
    prepareGeometryChange();

    setFlag( QGraphicsItem::ItemSendsGeometryChanges );
}


void TrackItem::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget )
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // Draw title
    painter->setFont( QFont( "Monaco", 10 ) );
    painter->setPen( QColor(160, 160, 160) );
    painter->drawText( -TRACK_TITLE_MARGIN, 2, TRACK_TITLE_WIDTH, TRACK_HEIGHT, Qt::AlignRight, pTrackModel->sName );

    // Draw right rule
    painter->setPen( QColor(20, 20, 20) );
    painter->drawLine( TRACK_TITLE_WIDTH, 0, TRACK_TITLE_WIDTH, TRACK_HEIGHT );
}


QRectF TrackItem::boundingRect() const
{
    return QRectF( 0, 0, TRACK_TITLE_WIDTH + 1, TRACK_HEIGHT );
}


void TrackItem::updateClips()
{
    for ( int i = 0; i < this->childItems().length(); i++ )
    {
        ClipItem* item = (ClipItem*)this->childItems()[i];
        item->color = this->pTrackModel->qColor;
        item->setX( item->calculateXPos() );
    }
}

void TrackItem::mouseDoubleClickEvent( QGraphicsSceneMouseEvent *event )
{
    QGraphicsItem::mouseDoubleClickEvent( event );
    emit mouseDouble(this);
}
