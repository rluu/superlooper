// This class provides persistent platform-independent settings storage.
#ifndef LOOPERSETTINGS_H
#define LOOPERSETTINGS_H

#include <QSettings>

class LooperSettings : public QObject
{
Q_OBJECT

public:
    LooperSettings();
    virtual ~LooperSettings();
    
    // Audio or video filename.
    void setMediaFilename( const QString& mediaFilename );
    QString mediaFilename() const;

    // Audio or video filename is locked.  A boolean value,
    // represented as 0 or 1.
    void setMediaFilenameLocked( const bool& locked );
    bool isMediaFilenameLocked() const;

    // Media Player File Location.
    void setMediaPlayerFileLocation( const QString& mediaPlayerFileLocation );
    QString mediaPlayerFileLocation() const;

    // Media Player Additional Options.
    void setMediaPlayerAdditionalOptions
    ( const QString& mediaPlayerAdditionalOptions );
    QString mediaPlayerAdditionalOptions() const;
    
    // Playback speed.
    void setPlaybackSpeed( const quint32& playbackSpeed );
    quint32 playbackSpeed() const;

    // Frame start time(sec).
    void setFrameStartTimeSec( const quint32& frameStartTimeSec );
    quint32 frameStartTimeSec() const;

    // Frame size(sec).
    void setFrameSizeSec( const quint32& frameSizeSec );
    quint32 frameSizeSec() const;

public slots:
    // Persistence for the settings.
    void loadSettings();
    void saveSettings();

private:
    // Unimplemented functions.
    LooperSettings( const LooperSettings& toCopy );
    LooperSettings& operator=( const LooperSettings& rhs );

    // Internal settings variables.
    QString mediaFilename_;
    quint32 mediaFilenameLocked_;
    QString mediaPlayerFileLocation_;
    QString mediaPlayerAdditionalOptions_;
    quint32 playbackSpeed_;       // A number between 0.01 and 100.
    quint32 frameStartTimeSec_;
    quint32 frameSizeSec_;
};

#endif   // #ifndef LOOPERSETTINGS_H
