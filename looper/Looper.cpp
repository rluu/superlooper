
#include "Looper.h"


Looper::Looper()
{
    process_ = new QProcess( this );

    staleLoopingIntervalFlag_ = true;
    loopingInterval_ = 0;   // Initialize to looping disabled.
    maxIterations_   = -1;  // Infinite iterations.
    iterationCount_  = 0;
}

Looper::~Looper()
{
    killTimer( timerId_ );
    this->stopProcess();

    delete process_;
}

void Looper::setCmdToExecute( const QString& cmdToExecute )
{
    cmdToExecute_ = cmdToExecute;
}

void Looper::setLoopingInterval( const quint32& loopingInterval )
{
    staleLoopingIntervalFlag_ = true;
    loopingInterval_ = loopingInterval;
}

void Looper::setMaxIterations( const qint32& maxIterations )
{
    maxIterations_ = maxIterations;
}

quint32 Looper::loopingInterval() const
{
    return loopingInterval_;
}

QString Looper::cmdToExecute() const
{
    return cmdToExecute_;
}

qint32 Looper::maxIterations() const
{
    return maxIterations_;
}

qint32 Looper::iterationCount() const
{
    return iterationCount_;
}

void Looper::timerEvent( QTimerEvent* event )
{
    // Do something with event so that it doesn't complain about the
    // unused variable.  Set it equal to 0.  Pointers are passed by
    // value, so it'll be alright.
    event = 0;

    this->iterationComplete();
}

void Looper::startLooping()
{
    // Make sure we're not looping already.
    this->stopLooping();
    
    // Reset the iteration count.
    iterationCount_ = 0;
    
    // Start looping (If parameters are good).
    this->startLoopingHelper();
}


void Looper::stopLooping()
{
    killTimer( timerId_ );
    this->stopProcess();
    //    iterationCount_ = 0;
}


void Looper::iterationComplete()
{
    iterationCount_++;


    if( staleLoopingIntervalFlag_ == true )
    {
        // This block will set the timer again with the correct
        // looping interval and continue looping if the iteration
        // count is within bounds of maxIterations.
        this->stopLooping();
        this->startLoopingHelper();
    }
    else
    {
        // This block will stop the process and restart it if the
        // iteration count is withing bounds of maxIterations.
        this->stopProcess();
    
        // It's either:  
        //   1a) Unlimited iterations (-1); start the process.
        //   1b) We haven't hit the max iterations yet; start the process.
        // OR it's:
        //   2) We hit our max iterations.  Don't start anymore processes.
        if( ( maxIterations_ == -1 ) ||
            ( iterationCount_ < maxIterations_ ) )
        {
            // We haven't hit the max iterations yet; start the process.
            this->startProcess();
        }
        else
        {
            killTimer( timerId_ );
        }
    }
}

void Looper::startProcess()
{
    process_->start( cmdToExecute_ );
    emit processStarted();
}

void Looper::stopProcess()
{

    if( process_->state() != QProcess::NotRunning )
    {
        process_->kill();
        process_->terminate();
        delete process_;
        process_ = new QProcess( this );
    }
}

void Looper::startLoopingHelper()
{
    // It's either:  
    //   1a) Unlimited iterations (-1); start the process.
    //   1b) We haven't hit the max iterations yet; start the process.
    // OR it's:
    //   2) We hit our max iterations.  Don't start anymore processes.
    if( ( maxIterations_ == -1 ) ||
        ( iterationCount_ < maxIterations_ ) )
    {
        // Case 1a or 1b, as denoted above.
        this->startProcess();

        // Start the timer for the process.
        if( loopingInterval_ != 0 )
        {
            staleLoopingIntervalFlag_ = false;
            timerId_ = startTimer( loopingInterval_ * 1000 );
        }
    }
    else
    {
        // Case 2, as denoted above.  Don't start a process.
    }
}
