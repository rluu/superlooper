
#ifndef MPLAYEROPTIONSMANAGER_H
#define MPLAYEROPTIONSMANAGER_H

#include <QString>

class MPlayerOptionsManager
{
 public:
    MPlayerOptionsManager( const QString& mplayerFileLocation = "echo",
                           const QString& additionalCmdlineOptions = "",
                           const qreal& playbackSpeed = 1,
                           const quint32& frameStartTimeSec = 0 );
    virtual ~MPlayerOptionsManager();
    
    void setMPlayerFileLocation( const QString& mplayerFileLocation );
    void setAdditionalCmdlineOptions( const QString& additionalCmdlineOptions);
    void setPlaybackSpeed( const qreal& playbackSpeed );
    void setFrameStartTimeSec( const quint32& frameStartTimeSec );

    QString execStr() const;
 private:
    QString mplayerFileLocation_;
    QString additionalCmdlineOptions_;
    
    qreal playbackSpeed_;        // A number between 0.01 and 100.
    quint32 frameStartTimeSec_;
};


#endif    // #ifndef MPLAYEROPTIONSMANAGER_H
