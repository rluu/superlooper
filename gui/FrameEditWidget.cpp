

#include "FrameEditWidget.h"



FrameEditWidget::FrameEditWidget( QWidget* parent,
                                  Qt::WFlags f )
    : QWidget( parent, f ),
      MIN_FRAME_SIZE( 2 ),
      DEFAULT_FRAME_SIZE( 5 )
{
    // Just placing a sensible default before we load the actual file
    // that will change this.
    const quint32& MAX_FRAME_SIZE( 20 );

    frameSizeEditWidget_ = new FrameSizeEditWidget( MIN_FRAME_SIZE,
                                                    MAX_FRAME_SIZE,
                                                    DEFAULT_FRAME_SIZE,
                                                    this );
                                                             
    frameStartTimeEditWidget_ = new FrameStartTimeEditWidget( this );
    
    // Set up the layout.
    QHBoxLayout *mainLayout = new QHBoxLayout( this );
    mainLayout->addWidget( frameSizeEditWidget_ );
    mainLayout->addWidget( frameStartTimeEditWidget_ );

    // Make signal/slot connections.

    // This passes the signals generated from the child widgets onwards.
    connect( frameSizeEditWidget_, SIGNAL(frameSizeUpdated(int)),
             this, SIGNAL(frameSizeSecUpdated(int)) );
    connect( frameStartTimeEditWidget_, SIGNAL(frameStartTimeUpdated(int)),
             this, SIGNAL(frameStartTimeSecUpdated(int)) );
    
    // This interconnects the two child widgets.
    connect( frameSizeEditWidget_, SIGNAL(frameSizeUpdated(int)),
             frameStartTimeEditWidget_, SLOT(setPageSize(int)) );
}

FrameEditWidget::~FrameEditWidget()
{
    // The child widgets destruct themselves when it's parent destructs.
}


quint32 FrameEditWidget::frameStartTimeSec() const
{
    return frameStartTimeEditWidget_->frameStartTime();
}


quint32 FrameEditWidget::frameSizeSec() const
{
    return frameSizeEditWidget_->frameSize();
}


void FrameEditWidget::setDisabled( bool disable )
{
    frameSizeEditWidget_->setDisabled( disable );
    frameStartTimeEditWidget_->setDisabled( disable );
}


void FrameEditWidget::setEnabled( bool enable )
{
    frameSizeEditWidget_->setEnabled( enable );
    frameStartTimeEditWidget_->setEnabled( enable );
}


void FrameEditWidget::setFrameStartTimeSec( quint32 frameStartTimeSec )
{
    frameStartTimeEditWidget_->setFrameStartTime( frameStartTimeSec );
}


void FrameEditWidget::setFrameSizeSec( quint32 frameSizeSec )
{
    frameSizeEditWidget_->setFrameSize( frameSizeSec );
}


void FrameEditWidget::setDuration( quint32 duration )
{
    frameSizeEditWidget_->setMediaDuration( duration );
    frameStartTimeEditWidget_->setMediaDuration( duration );
    frameStartTimeEditWidget_->
        setPageSize( frameSizeEditWidget_->frameSize() );
}

void FrameEditWidget::adjustFrameStartTime( qint32 change )
{
    frameStartTimeEditWidget_->adjustFrameStartTime( change );
}


void FrameEditWidget::adjustFrameSize( qint32 change )
{
    frameSizeEditWidget_->adjustFrameSize( change );
}

