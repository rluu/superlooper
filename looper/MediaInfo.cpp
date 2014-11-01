

#include "MediaInfo.h"


MediaInfo::MediaInfo( const QString& mediaFilename,
                      const QString& ffmpegLocation )
    :
    mediaFilename_( mediaFilename ),
    ffmpegLocation_( ffmpegLocation )
{
    process_ = new QProcess( this );
}

MediaInfo::~MediaInfo()
{
    if( process_->state() != QProcess::NotRunning )
    {
        // process__->tryTerminate();
        process_->kill();
    }

    delete process_;
}


void MediaInfo::setMediaFilename( const QString& mediaFilename )
{
    mediaFilename_ = mediaFilename;
}
 
void MediaInfo::setFFMPEGLocation( const QString& ffmpegLocation )
{
    ffmpegLocation_ = ffmpegLocation;
}


QTime MediaInfo::getDuration()
{
    // Make sure we have the required ffmpeg file location, so we can
    // use it to determine the duration.
    if( ffmpegLocation_ == QString( "" ) || 
        ffmpegLocation_.isNull() == true )
    {
        return QTime();
    }
    
    // Make sure we have a media filename set, so we can know what to
    // check the duration of.
    if( mediaFilename_ == QString( "" ) ||
        mediaFilename_.isNull() == true )
    {
        return QTime();
    }

    process_->setReadChannel( QProcess::StandardError );

    //     qDebug( QString( QString("ffmpegLocation_ is:  ") + QString( ffmpegLocation_ ) ).toAscii() );
    //     qDebug( QString( QString("Media filename is:  ") + QString( mediaFilename_ ) ).toAscii() );

    // Start the process

    QString toExec( QString( "/usr/bin/" ) + ffmpegLocation_ + " -i \"" + mediaFilename_ + "\"" );
    //    qDebug( QString( QString("Str to exec is: ") + toExec ).toAscii() );
    process_->start( toExec );

    //     process_->waitForReadyRead( -1 );
    process_->waitForFinished( 5000 );
    //     process_->terminate();



    QByteArray byteArray;
    byteArray = process_->readAllStandardError();

    while( byteArray.size() != 0 )
    {
        QString line( byteArray );
        // qDebug(QString( QString( "Line recieved is: " ) + line ).toAscii());
        QString durationStr( "  Duration: " );
        QString commaStr( "," );
        QString periodStr( "." );

        int locationOfDuration = line.indexOf( durationStr );
        line.remove( 0, locationOfDuration );
        locationOfDuration = 0;
        // qDebug(QString( QString( "Revised line is: " ) + line ).toAscii() );
        int locationOfComma    = line.indexOf( commaStr );
        int locationOfPeriod   = line.indexOf( periodStr );

        //         qDebug( "locationOfDuration == %d", locationOfDuration );
        //         qDebug( "locationOfComma == %d", locationOfComma );
        //         qDebug( "locationOfPeriod == %d", locationOfPeriod );

        if( locationOfDuration != -1 )
        {
            QString durationTimeStr;

            if( locationOfComma != -1 )
            {
                line.truncate( locationOfComma );
                durationTimeStr = line;
            }

            if( locationOfPeriod != -1 )
            {
                durationTimeStr.truncate( locationOfPeriod );
            }


            durationTimeStr = durationTimeStr.remove( 0, 
                                                      locationOfDuration + 
                                                      durationStr.size() );

            qDebug( QString( QString("Duration:  ") + 
                             durationTimeStr ).toAscii() );

            QString hoursStr = durationTimeStr.section( ':', 0, 0 );
            QString minutesStr = durationTimeStr.section( ':', 1, 1 );
            QString secondsStr = 
                durationTimeStr.section( ':', 2, 2 ).section( '.', 0, 0 );
            QString millisecondsStr =
                durationTimeStr.section( ':', 2, 2 ).section( '.', 1, 1 );

            if( millisecondsStr.size() == 0 )
            {
                millisecondsStr = "0";
            }
            else if( millisecondsStr.size() == 1 )
            {
                millisecondsStr += "000";
            }
            else if( millisecondsStr.size() == 2 )
            {
                millisecondsStr += "00" ;
            }
            else if( millisecondsStr.size() == 3 )
            {
                millisecondsStr += "0";
            }
            
            int hours = hoursStr.toInt();
            int minutes = minutesStr.toInt();
            int seconds = secondsStr.toInt();
            int milliseconds = millisecondsStr.toInt();

            //             qDebug( "Hours == %d", hours );
            //             qDebug( "Minutes == %d", minutes );
            //             qDebug( "Seconds == %d", seconds );
            //             qDebug( "Milliseconds == %d", milliseconds );
            QTime duration( hours, minutes, seconds, milliseconds );
            return duration;
        }

        process_->waitForReadyRead( 2000 );
        byteArray = process_->readAllStandardError();
    }

    qDebug( "DEBUG:  Ran out of lines to parse while "
            "looking for the duration." );

    return QTime();
}
