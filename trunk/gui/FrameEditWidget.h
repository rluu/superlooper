
#ifndef FRAMEEDITWIDGET_H
#define FRAMEEDITWIDGET_H

#include <QWidget>
#include <QBoxLayout>

#include "FrameSizeEditWidget.h"
#include "FrameStartTimeEditWidget.h"


class FrameEditWidget : public QWidget
{
    Q_OBJECT
public:
    FrameEditWidget( QWidget* parent = 0,
                     Qt::WFlags f = 0 );
    virtual ~FrameEditWidget();

    quint32 frameStartTimeSec() const;
    quint32 frameSizeSec() const;

signals:
    void frameStartTimeSecUpdated( int );
    void frameSizeSecUpdated( int );

public slots:
    void setDisabled( bool disable );
    void setEnabled( bool enable );

    void setFrameStartTimeSec( quint32 frameStartTimeSec );
    void setFrameSizeSec( quint32 frameSizeSec );

    void setDuration( quint32 duration );

    void adjustFrameStartTime( qint32 change );
    void adjustFrameSize( qint32 change );

private:
    const quint32 MIN_FRAME_SIZE;
    const quint32 DEFAULT_FRAME_SIZE;

    FrameSizeEditWidget      *frameSizeEditWidget_;
    FrameStartTimeEditWidget *frameStartTimeEditWidget_;
};


#endif     // #ifndef FRAMEEDITWIDGET_H
