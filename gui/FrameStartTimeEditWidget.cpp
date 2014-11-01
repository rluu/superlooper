
#include "FrameStartTimeEditWidget.h"


FrameStartTimeEditWidget::FrameStartTimeEditWidget( QWidget* parent,
                                                    Qt::WFlags f )
    :
    QWidget( parent, f ),
    DEFAULT_FRAME_START_TIME( 0 ),
    MINIMUM_START_TIME( 0 ),
    SINGLE_STEP_SIZE( 1 )
{
    // These two values were pulled out of my ass.
    const int INITIAL_PAGE_STEP_SIZE( 10 );
    const int INITIAL_MAXIMUM_START_TIME( 10 );

    // Allocate internal widgets.
    label_  = new QLabel( tr("Frame Start Time"), this );
    scrollBar_ = new QScrollBar( Qt::Horizontal, this );
    timeEdit_ = new QTimeEdit( this );
    resetButton_ = new QPushButton( tr("Reset to Default"), this );
    
    // Set slider settings.
    scrollBar_->setRange( MINIMUM_START_TIME, INITIAL_MAXIMUM_START_TIME );
    scrollBar_->setSingleStep( SINGLE_STEP_SIZE );
    scrollBar_->setPageStep( INITIAL_PAGE_STEP_SIZE );
    scrollBar_->setValue( DEFAULT_FRAME_START_TIME );

    // Set the QTimeEdit settings.
    timeEdit_->setDisplayFormat( "hh:mm:ss" );

    // Set up the widget interface look.
    QHBoxLayout *b = new QHBoxLayout;
    b->addStretch();
    b->addWidget( timeEdit_ );
    b->addWidget( resetButton_ );
    
    QVBoxLayout *a = new QVBoxLayout( this );
    a->addWidget( label_ );
    a->addWidget( scrollBar_ );
    a->addLayout( b );

    // Make signal/slot connections.
    connect( timeEdit_, SIGNAL(timeChanged(const QTime&)),
             this, SLOT(syncScrollBar(const QTime&)) );
    connect( scrollBar_, SIGNAL(valueChanged(int)),
             this, SLOT(syncTimeEdit(int)) );
    connect( scrollBar_, SIGNAL(valueChanged(int)),
             this, SIGNAL(frameStartTimeUpdated(int)) );
    connect( resetButton_, SIGNAL(clicked()),
             this, SLOT(resetButtonClicked()) );
}


FrameStartTimeEditWidget::~FrameStartTimeEditWidget()
{
    // The child widgets destruct themselves when it's parent destructs.    
}

quint32 FrameStartTimeEditWidget::frameStartTime() const
{
    return scrollBar_->value();
}


void FrameStartTimeEditWidget::setDisabled( bool disable )
{
    this->setEnabled( !disable );
}

void FrameStartTimeEditWidget::setEnabled( bool enable )
{
    label_->setEnabled( enable );
    scrollBar_->setEnabled( enable );
    timeEdit_->setEnabled( enable );
    resetButton_->setEnabled( enable );
    
    QWidget::setEnabled( enable );
}

void FrameStartTimeEditWidget::setFrameStartTime( quint32 frameStartTime )
{
    scrollBar_->setValue( frameStartTime );
    timeEdit_->setTime( QTime().addSecs( frameStartTime ) );
}

void FrameStartTimeEditWidget::setPageSize( int pageSize )
{
    scrollBar_->setPageStep( pageSize );
    this->setMediaDuration( duration_ );
}

void FrameStartTimeEditWidget::setMediaDuration( const quint32& duration )
{
    int maximumStartTimeSec;
    QTime minStartTime;
    QTime maxStartTime;

    duration_ = duration;

    maximumStartTimeSec = duration_ - scrollBar_->pageStep();

    minStartTime = QTime().addSecs( MINIMUM_START_TIME );
    maxStartTime = QTime().addSecs( maximumStartTimeSec );

    // Set the ranges.
    scrollBar_->setRange( QTime().secsTo(minStartTime), 
                          QTime().secsTo(maxStartTime) );
    timeEdit_->setTimeRange( minStartTime, maxStartTime );
    timeEdit_->setCurrentSection( QDateTimeEdit::SecondSection );

    // Reset the start time value.
    //    this->resetButtonClicked();
}


void FrameStartTimeEditWidget::adjustFrameStartTime( qint32 change )
{
    (*this) += change;
}

void FrameStartTimeEditWidget::operator+=( const qint32& value )
{
    // Setting the scrollBar should also auto-set the QTimeEdit too.

    qint32 newStartTime = value + this->frameStartTime();
    
    // Make sure it's within the given parameters.
    if( newStartTime > scrollBar_->minimum() && 
        newStartTime < scrollBar_->maximum() )
    {
        scrollBar_->setValue( newStartTime );
        timeEdit_->setTime( QTime().addSecs( newStartTime ) );
    }
}

void FrameStartTimeEditWidget::resetButtonClicked()
{
    this->setFrameStartTime( DEFAULT_FRAME_START_TIME );
}

void FrameStartTimeEditWidget::syncTimeEdit( int seconds )
{
    timeEdit_->setTime( QTime().addSecs( seconds ) );
}

void FrameStartTimeEditWidget::syncScrollBar( const QTime& newTime )
{
    scrollBar_->setValue( QTime().secsTo( newTime ) );
}
