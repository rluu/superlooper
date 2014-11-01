

#ifndef FRAMESIZEEDITWIDGET_H
#define FRAMESIZEEDITWIDGET_H


#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QBoxLayout>


class FrameSizeEditWidget : public QWidget
{
Q_OBJECT
public:
    FrameSizeEditWidget( const quint32& minFrameSize, 
                         const quint32& maxFrameSize, 
                         const quint32& defaultFrameSize, 
                         QWidget* parent = 0,
                         Qt::WFlags f = 0 );
    virtual ~FrameSizeEditWidget();
    
    quint32 frameSize() const;
    void setMediaDuration( const quint32& duration );
    void operator+=( const qint32& value );

signals:
    void frameSizeUpdated( int frameSize );

public slots:
    void setDisabled( bool disable );
    void setEnabled( bool enable );
    void setFrameSize( quint32 frameSize );

    // These two functions do the same thing.
    void adjustFrameSize( qint32 change );

private slots:
    void resetButtonClicked();

private:
    QLabel *label_;
    QSlider *slider_;
    QSpinBox *spinBox_;
    QPushButton *resetButton_;
    
    quint32 defaultFrameSize_;
};

#endif     // #ifndef FRAMESIZEEDITWIDGET_H
