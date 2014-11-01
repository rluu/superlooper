
#include "SpeedEditWidget.h"


SpeedEditWidget::SpeedEditWidget( const quint32& tickSize,
                                  const quint32& minSpeed, 
                                  const quint32& maxSpeed, 
                                  const quint32& defaultSpeed,
                                  QWidget* parent,
                                  Qt::WFlags f )
    :
    QWidget( parent, f ),
    defaultSpeed_( defaultSpeed )
{
    // Blah, I guess I can't get around globals.
    const int SINGLE_STEP_SIZE( 10 );
    const int PAGE_STEP_SIZE( 1000 );

    // Do some initial checks.
    if( minSpeed > defaultSpeed || minSpeed > maxSpeed ||
        defaultSpeed > maxSpeed )
    {
        qWarning( "Invalid argument: arguments should be incremental: "
                  "%d, %d, %d", minSpeed, defaultSpeed, maxSpeed );
        return;
    }

    if( tickSize > ( maxSpeed - minSpeed ) )
    {
        qWarning( "Invalid argument: tickSize resolution too large: %d",
                  tickSize );
        return;
    }

    // Allocate internal widgets.
    label_  = new QLabel( tr("Playback Speed"), this );
    slider_ = new QSlider( Qt::Vertical, this );
    spinBox_ = new QSpinBox( this );
    resetButton_ = new QPushButton( tr("Reset to Default"), this );
    
    // Set slider settings.
    slider_->setTickInterval( tickSize );
    slider_->setRange( minSpeed, maxSpeed );
    slider_->setSingleStep( SINGLE_STEP_SIZE );
    slider_->setPageStep( PAGE_STEP_SIZE );
    slider_->setValue( defaultSpeed_ );
    
    // Set spin box settings.
    spinBox_->setRange( minSpeed, maxSpeed );
    spinBox_->setSingleStep( SINGLE_STEP_SIZE );
    spinBox_->setSuffix( " %" );
    spinBox_->setValue( defaultSpeed_ );

    // Set up the widget interface look.
    QHBoxLayout *d = new QHBoxLayout;
    d->addWidget( spinBox_ );
    d->addWidget( resetButton_ );
    
    QVBoxLayout *c = new QVBoxLayout;
    c->addStretch();
    c->addLayout( d );

    QHBoxLayout *b = new QHBoxLayout;
    b->addWidget( slider_ );
    b->addLayout( c );
    
    QVBoxLayout *a = new QVBoxLayout( this );
    a->addWidget( label_ );
    a->addLayout( b );
    
    
    // Make signal/slot connections.
    connect( slider_, SIGNAL(valueChanged(int)),
             spinBox_, SLOT(setValue(int)) );
    connect( spinBox_, SIGNAL(valueChanged(int)),
             slider_, SLOT(setValue(int)) );
    connect( spinBox_, SIGNAL(valueChanged(int)),
             this, SIGNAL(speedUpdated(int)) );
    connect( resetButton_, SIGNAL(clicked()),
             this, SLOT(resetButtonClicked()) );

}

SpeedEditWidget::~SpeedEditWidget()
{
    // The child widgets destruct themselves when it's parent destructs.
}

quint32 SpeedEditWidget::speed() const
{
    return spinBox_->value();
}

void SpeedEditWidget::setDisabled( bool disable )
{
    this->setEnabled( !disable );
}

void SpeedEditWidget::setEnabled( bool enable )
{
    label_->setEnabled( enable );
    slider_->setEnabled( enable );
    spinBox_->setEnabled( enable );
    resetButton_->setEnabled( enable );
    
    QWidget::setEnabled( enable );
}

void SpeedEditWidget::setSpeed( quint32 speed )
{
    // We just need to set either the slider or the spinbox, and the
    // other will automatically sync due to the signal/slot
    // connection.
    slider_->setValue( speed );
}


void SpeedEditWidget::resetButtonClicked()
{
    // Setting the slider should also auto-set the spinbox too.
    slider_->setValue( defaultSpeed_ );
}

void SpeedEditWidget::adjustSpeed( qint32 change )
{
    (*this) += change;
}

void SpeedEditWidget::operator+=( const qint32& value )
{
    // Setting the slider should also auto-set the spinbox too.

    qint32 newSpeed = value + this->speed();
    
    // Make sure it's within the given parameters.
    if( newSpeed > slider_->minimum() && 
        newSpeed < slider_->maximum() )
    {
        slider_->setValue( newSpeed );
    }
}
