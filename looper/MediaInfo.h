

#ifndef MEDIAINFO_H
#define MEDIAINFO_H

#include <QObject>
#include <QProcess>
#include <QTime>
#include <QByteArray>

class MediaInfo : public QObject
{
Q_OBJECT
 public:
    MediaInfo( const QString& mediaFilename,
               const QString& ffmpegLocation = "ffmpeg" );
    virtual ~MediaInfo();
    void setMediaFilename( const QString& mediaFilename );
    void setFFMPEGLocation( const QString& ffmpegLocation );

    QTime getDuration();
 private:
    QString mediaFilename_;
    QString ffmpegLocation_;

    QProcess* process_;        // Process spawned to determine duration.
};


#endif    // #ifndef MEDIAINFO_H
