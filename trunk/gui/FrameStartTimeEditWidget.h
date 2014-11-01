

#ifndef FRAMESTARTTIMEEDITWIDGET_H
#define FRAMESTARTTIMEEDITWIDGET_H


#include <QWidget>
#include <QScrollBar>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QTimeEdit>
#include <QBoxLayout>


class FrameStartTimeEditWidget : public QWidget
{
    Q_OBJECT
public:
    FrameStartTimeEditWidget( QWidget* parent = 0,
                              Qt::WFlags f = 0 );
    virtual ~FrameStartTimeEditWidget();
    
    quint32 frameStartTime() const;
    void operator+=( const qint32& value );

signals:
    void frameStartTimeUpdated( int frameStartTime );

public slots:
    void setDisabled( bool disable );
    void setEnabled( bool enable );

    void setFrameStartTime( quint32 frameStartTime );
    void setPageSize( int pageSize );
    void setMediaDuration( const quint32& duration );

    // These two functions do the same thing.
    void adjustFrameStartTime( qint32 change );

private slots:
    void resetButtonClicked();
    void syncTimeEdit( int seconds );
    void syncScrollBar( const QTime& newTime );

private:

    const int DEFAULT_FRAME_START_TIME; 
    const int MINIMUM_START_TIME;
    const int SINGLE_STEP_SIZE;
    QLabel *label_;
    QScrollBar *scrollBar_;
    QTimeEdit *timeEdit_;
    QPushButton *resetButton_;
    quint32 duration_;
};


#endif     // #ifndef FRAMESTARTTIMEEDITWIDGET_H

