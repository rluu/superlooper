
#include "FrameSizeEditWidget.h"


FrameSizeEditWidget::FrameSizeEditWidget( const quint32& minFrameSize, 
                                          const quint32& maxFrameSize, 
                                          const quint32& defaultFrameSize,
                                          QWidget* parent,
                                          Qt::WFlags f )
    :
    QWidget( parent, f ),
    defaultFrameSize_( defaultFrameSize )
{
    // Blah, I guess I can't get around globals.
    const int SINGLE_STEP_SIZE( 1 );
    const int PAGE_STEP_SIZE( 5 );

    // Do some initial checks.
    if( minFrameSize > defaultFrameSize || minFrameSize > maxFrameSize ||
        defaultFrameSize > maxFrameSize )
    {
        qWarning( "Invalid argument: arguments should be incremental: "
                  "%d, %d, %d", minFrameSize, defaultFrameSize, maxFrameSize );
        return;
    }

    // Allocate internal widgets.
    label_  = new QLabel( tr("Frame Size"), this );
    slider_ = new QSlider( Qt::Horizontal, this );
    spinBox_ = new QSpinBox( this );
    resetButton_ = new QPushButton( tr("Reset to Default"), this );
    
    // Set slider settings.
    slider_->setTickInterval( SINGLE_STEP_SIZE );
    slider_->setRange( minFrameSize, maxFrameSize );
    slider_->setSingleStep( SINGLE_STEP_SIZE );
    slider_->setPageStep( PAGE_STEP_SIZE );
    slider_->setValue( defaultFrameSize_ );
    
    // Set spin box settings.
    spinBox_->setRange( minFrameSize, maxFrameSize );
    spinBox_->setSingleStep( SINGLE_STEP_SIZE );
    spinBox_->setSuffix( " sec" );


    // Set up the widget interface look.
    QHBoxLayout *b = new QHBoxLayout;
    b->addStretch();
    b->addWidget( spinBox_ );
    b->addWidget( resetButton_ );
    
    QVBoxLayout *a = new QVBoxLayout( this );
    a->addWidget( label_ );
    a->addWidget( slider_ );
    a->addLayout( b );
    
    
    // Make signal/slot connections.
    connect( slider_, SIGNAL(valueChanged(int)),
             spinBox_, SLOT(setValue(int)) );
    connect( spinBox_, SIGNAL(valueChanged(int)),
             slider_, SLOT(setValue(int)) );
    connect( spinBox_, SIGNAL(valueChanged(int)),
             this, SIGNAL(frameSizeUpdated(int)) );
    connect( resetButton_, SIGNAL(clicked()),
             this, SLOT(resetButtonClicked()) );
}

FrameSizeEditWidget::~FrameSizeEditWidget()
{
    // The child widgets destruct themselves when it's parent destructs.
}

quint32 FrameSizeEditWidget::frameSize() const
{
    return spinBox_->value();
}

void FrameSizeEditWidget::setMediaDuration( const quint32& duration )
{
    // Get the slider minimum value.
    int minimum = slider_->minimum();

    // Duration would be the new maximum.
    int newMaximum = duration;

    // Make sure the value is valid(above the minimum value).
    if( newMaximum >= minimum )
    {
        // // Set frame size to minimum just in case.  I don't know if
        // // weird things happen if the old frame size was greater than
        // // the new maximum frame size.
        // this->setFrameSize( minimum );

        // Reset the ranges.
        slider_->setRange( minimum, newMaximum );
        spinBox_->setRange( minimum, newMaximum );
    }
    else
    {
        qDebug( "Attempt to set maximum frame size(%d) to less than "
                "minimum frame size(%d).",
                newMaximum,
                minimum );

        // Reassign minimum value to equal the duration value.  It
        // would mean that this property wouldn't be adjustable.  I'm
        // not sure if that makes sense to do...  Hopefully the
        // original minimum value was set to be something sane.
        minimum = newMaximum;
        slider_->setRange( minimum, newMaximum );
        spinBox_->setRange( minimum, newMaximum );
    }

    // Should we reset the frame size to the default again?  Some may
    // like the settings they have... so I guess not.
    //     defaultValue_ = ( minimum + newMaximum ) / 2;
    //     this->resetButtonClicked();
}

void FrameSizeEditWidget::setDisabled( bool disable )
{
    this->setEnabled( !disable );
}

void FrameSizeEditWidget::setEnabled( bool enable )
{
    label_->setEnabled( enable );
    slider_->setEnabled( enable );
    spinBox_->setEnabled( enable );
    resetButton_->setEnabled( enable );
    
    QWidget::setEnabled( enable );
}

void FrameSizeEditWidget::setFrameSize( quint32 frameSize )
{
    slider_->setValue( frameSize );
    spinBox_->setValue( frameSize );
}

void FrameSizeEditWidget::adjustFrameSize( qint32 change )
{
    (*this) += change;
}

void FrameSizeEditWidget::operator+=( const qint32& value )
{
    // Setting the slider should also auto-set the spinbox too.

    qint32 newFrameSize = value + this->frameSize();
    
    // Make sure it's within the given parameters.
    if( newFrameSize > slider_->minimum() && 
        newFrameSize < slider_->maximum() )
    {
        slider_->setValue( newFrameSize );
        spinBox_->setValue( newFrameSize );
    }
}

void FrameSizeEditWidget::resetButtonClicked()
{
    // Setting the slider should also auto-set the spinbox too.
    slider_->setValue( defaultFrameSize_ );
    spinBox_->setValue( defaultFrameSize_ );
}

