

#include "MPlayerOptionsManager.h"

MPlayerOptionsManager::MPlayerOptionsManager
( const QString& mplayerFileLocation,
  const QString& additionalCmdlineOptions,
  const qreal& playbackSpeed,
  const quint32& frameStartTimeSec )
    : 
    mplayerFileLocation_( mplayerFileLocation ),
    additionalCmdlineOptions_( additionalCmdlineOptions ),
    playbackSpeed_( playbackSpeed ),
    frameStartTimeSec_( frameStartTimeSec )
{
    // Empty.
}

MPlayerOptionsManager::~MPlayerOptionsManager()
{
    // Empty.
}


void MPlayerOptionsManager::setMPlayerFileLocation
( const QString& mplayerFileLocation )
{
    mplayerFileLocation_ = mplayerFileLocation;
}

void MPlayerOptionsManager::setAdditionalCmdlineOptions
( const QString& additionalCmdlineOptions )
{
    additionalCmdlineOptions_ = additionalCmdlineOptions;
}

void MPlayerOptionsManager::setPlaybackSpeed( const qreal& playbackSpeed )
{
    playbackSpeed_ = playbackSpeed;
    playbackSpeed_ /= 100;
}

void MPlayerOptionsManager::setFrameStartTimeSec
( const quint32& frameStartTimeSec )
{
    frameStartTimeSec_ = frameStartTimeSec;
}


QString MPlayerOptionsManager::execStr() const
{
    QString generatedOptions;
    QString rv;
    
    generatedOptions += "-speed ";
    generatedOptions += QString::number( playbackSpeed_ );
    generatedOptions += " ";
    generatedOptions += "-ss ";
    generatedOptions += QString::number( frameStartTimeSec_ );    

    rv += "";
    rv += mplayerFileLocation_;
    rv += "";
    rv += " ";
    rv += generatedOptions;
    rv += " ";
    rv += additionalCmdlineOptions_;
    return rv;
}
