
#include "LooperSettings.h"

LooperSettings::LooperSettings()
{
    // Do this even if there are no values set.  This is so we can
    // establish a set of valid values that the user can retrieve.
    loadSettings();
}

LooperSettings::~LooperSettings()
{
    // Empty.
}

void LooperSettings::setMediaFilename( const QString& mediaFilename )
{
    mediaFilename_ = mediaFilename;
}

QString LooperSettings::mediaFilename() const
{
    return mediaFilename_;
}

void LooperSettings::setMediaPlayerFileLocation
( const QString& mediaPlayerFileLocation )
{
    mediaPlayerFileLocation_ = mediaPlayerFileLocation;
}

void LooperSettings::setMediaFilenameLocked( const bool& locked )
{
    if( locked == true )
    {
        mediaFilenameLocked_ = 1;
    }
    else
    {
        mediaFilenameLocked_ = 0;
    }
}

bool LooperSettings::isMediaFilenameLocked() const
{
    if( mediaFilenameLocked_ == 1 )
    {
        return true;
    }
    else if( mediaFilenameLocked_ == 0 )
    {
        return false;
    }
    else
    {
        return false;
    }
}


QString LooperSettings::mediaPlayerFileLocation() const
{
    return mediaPlayerFileLocation_;
}

void LooperSettings::setMediaPlayerAdditionalOptions
( const QString& mediaPlayerAdditionalOptions )
{
    mediaPlayerAdditionalOptions_ = mediaPlayerAdditionalOptions;
}

QString LooperSettings::mediaPlayerAdditionalOptions() const
{
    return mediaPlayerAdditionalOptions_;
}

void LooperSettings::setPlaybackSpeed( const quint32& playbackSpeed )
{
    playbackSpeed_ = playbackSpeed;
}

quint32 LooperSettings::playbackSpeed() const
{
    return playbackSpeed_;
}

void LooperSettings::setFrameStartTimeSec( const quint32& frameStartTimeSec )
{
    frameStartTimeSec_ = frameStartTimeSec;
}

quint32 LooperSettings::frameStartTimeSec() const
{
    return frameStartTimeSec_;
}


void LooperSettings::setFrameSizeSec( const quint32& frameSizeSec )
{
    frameSizeSec_ = frameSizeSec;
}

quint32 LooperSettings::frameSizeSec() const
{
    return frameSizeSec_;
}



void LooperSettings::loadSettings()
{
    QSettings settings;
    // The first param to QSettings::value() is the key.  The second
    // param is the value returned if the key/value pair does not
    // exist.

    mediaFilename_ =
        settings.value( "mediaFilename", "" ).toString();
    mediaFilenameLocked_ = 
        settings.value( "mediaFilenameLocked", 0 ).toUInt();
    mediaPlayerFileLocation_ = 
        settings.value( "mediaPlayerFileLocation", "" ).toString();
    mediaPlayerAdditionalOptions_ =
        settings.value( "mediaPlayerAdditionalOptions", "" ).toString();
    playbackSpeed_ = 
        settings.value( "playbackSpeed", 1 ).toUInt();
    frameStartTimeSec_ = 
        settings.value( "frameStartTimeSec", 0 ).toUInt();
    frameSizeSec_ =
        settings.value( "frameSizeSec", 5 ).toUInt();

}

void LooperSettings::saveSettings()
{
    QSettings settings;

    settings.setValue( "mediaFilename", mediaFilename_ );
    settings.setValue( "mediaFilenameLocked", mediaFilenameLocked_ );
    settings.setValue( "mediaPlayerFileLocation", mediaPlayerFileLocation_ );
    settings.setValue( "mediaPlayerAdditionalOptions", 
                       mediaPlayerAdditionalOptions_ );
    settings.setValue( "playbackSpeed", playbackSpeed_ );
    settings.setValue( "frameStartTimeSec", frameStartTimeSec_ );
    settings.setValue( "frameSizeSec", frameSizeSec_ );

    settings.sync();

}

