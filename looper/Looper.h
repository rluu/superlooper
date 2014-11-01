


#ifndef LOOPER_H
#define LOOPER_H

#include <QObject>
#include <QProcess>
// #include <QTimer>

// This class controls the looping of a child program's execution.

class Looper : public QObject
{
Q_OBJECT
public:
    Looper();
    virtual ~Looper();

    // Set- functions.
    void setCmdToExecute( const QString& cmdToExecute );
    void setLoopingInterval( const quint32& loopingInterval );
    void setMaxIterations( const qint32& maxIterations );

    // Get- functions.
    quint32 loopingInterval() const;
    QString cmdToExecute() const;
    qint32 maxIterations() const;
    qint32 iterationCount() const;
public slots:
    void startLooping();
    void stopLooping();

signals:
    void processStarted();

protected:
    void timerEvent( QTimerEvent* event );


private slots:
    void iterationComplete();

private:
    void startProcess();
    void stopProcess();
    void startLoopingHelper();

    int timerId_;

    QProcess *process_;        // Process spawned.

    bool staleLoopingIntervalFlag_;  // Flag that tells us we need to
                                     // reset the timer.

    quint32 loopingInterval_;  // Interval at which to loop at.
    QString cmdToExecute_;     // Cmd to execute per iteration.
    qint32 maxIterations_;     // Maximum number of iterations to do.
    qint32 iterationCount_;    // Current iteration count.
};


#endif   // #ifndef LOOPER_H
