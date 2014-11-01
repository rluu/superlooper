
#ifndef SPEEDEDITWIDGET_H
#define SPEEDEDITWIDGET_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QBoxLayout>


class SpeedEditWidget : public QWidget
{
    Q_OBJECT
public:
    SpeedEditWidget( const quint32& tickSize,
                     const quint32& minSpeed, 
                     const quint32& maxSpeed, 
                     const quint32& defaultSpeed, 
                     QWidget* parent = 0,
                     Qt::WFlags f = 0 );
    virtual ~SpeedEditWidget();

    quint32 speed() const;
    void operator+=( const qint32& value );

signals:
    void speedUpdated( int speed );

public slots:
    void setDisabled( bool disable );
    void setEnabled( bool enable );
    void setSpeed( quint32 speed );
    void adjustSpeed( qint32 change );

private slots:
    void resetButtonClicked();

private:
    QLabel *label_;
    QSlider *slider_;
    QSpinBox *spinBox_;
    QPushButton *resetButton_;
    
    quint32 defaultSpeed_;
};

#endif      // #ifndef SPEEDEDITWIDGET_H
