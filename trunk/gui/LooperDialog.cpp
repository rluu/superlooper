
#include "LooperDialog.h"



LooperDialog::LooperDialog( QWidget* parent, Qt::WFlags f )
    : QDialog( parent, f )
{
    // This gives the window minimize and maximize buttons.
    this->setWindowFlags( Qt::Window );

    // This is required to accept custom keyboard input events.
    this->setFocusPolicy( Qt::StrongFocus );

    mediaFilenameLabel_ = new QLabel( tr("Media Filename"), this );
    mediaFilenameLabel_->setAlignment( Qt::AlignLeft );
    mediaFilenameLineEdit_ = new QLineEdit( this );
    lockUnlockMediaButton_ = new QPushButton( tr("&Lock"), this );
    browseForMediaFileButton_ = new QPushButton( tr("&Browse"), this );

    mediaPlayerFileLocationLabel_ = 
        new QLabel( tr("Media Player Filename"), this );
    mediaPlayerFileLocationLabel_->setAlignment( Qt::AlignLeft );    
    mediaPlayerFileLocationLineEdit_ = new QLineEdit( this );
    mediaPlayerFileLocationLineEdit_->setEnabled( false );
    browseForMediaPlayerButton_ = new QPushButton( tr("B&rowse"), this );

    mediaPlayerAdditionalOptionsLabel_ = 
        new QLabel( tr("Additional Media Player Command-line Options"), this );
    mediaPlayerAdditionalOptionsLineEdit_ = new QLineEdit( this );

    cmdToExecuteLabel_ = new QLabel( tr("Command To Execute"), this );
    cmdToExecuteLineEdit_ = new QLineEdit( this );
    cmdToExecuteLineEdit_->setEnabled( false );
    

    // Parameters for the SpeedEditWidget constructor.
    const quint32 tickSize( 10 );
    const quint32 minSpeed( 1 );
    const quint32 maxSpeed( 400 );
    const quint32 defaultSpeed( 100 );

    frameEditWidget_ = new FrameEditWidget( this );

    speedEditWidget_ = new SpeedEditWidget( tickSize, minSpeed, maxSpeed, 
                                            defaultSpeed, this );
    
    // Start button is initially disabled untill a file is locked.
    // Stop button is initially disabled untill the user clicks start.
    startButton_ = new QPushButton( tr("&Start"), this );
    startButton_->setEnabled( false );
    stopButton_ = new QPushButton( tr("S&top"), this );
    stopButton_->setEnabled( false );
    aboutButton_ = new QPushButton( tr("&About"), this );
    exitButton_ = new QPushButton( tr("E&xit"), this );

    // Set up the interface layout.

    QHBoxLayout *mediaFilenameLayout2 = new QHBoxLayout;
    mediaFilenameLayout2->addStretch();
    mediaFilenameLayout2->addWidget( lockUnlockMediaButton_ );
    mediaFilenameLayout2->addWidget( browseForMediaFileButton_ );
    QVBoxLayout *mediaFilenameLayout1 = new QVBoxLayout;
    mediaFilenameLayout1->addWidget( mediaFilenameLabel_ );
    mediaFilenameLayout1->addWidget( mediaFilenameLineEdit_ );
    mediaFilenameLayout1->addLayout( mediaFilenameLayout2 );

    QHBoxLayout *mediaPlayerFileLocationLayout2 = new QHBoxLayout;
    mediaPlayerFileLocationLayout2->addStretch();
    mediaPlayerFileLocationLayout2->addWidget( browseForMediaPlayerButton_ );
    QVBoxLayout *mediaPlayerFileLocationLayout1 = new QVBoxLayout;
    mediaPlayerFileLocationLayout1->addWidget( mediaPlayerFileLocationLabel_ );
    mediaPlayerFileLocationLayout1->addWidget
        ( mediaPlayerFileLocationLineEdit_ );
    mediaPlayerFileLocationLayout1->addLayout
        ( mediaPlayerFileLocationLayout2 );

    QVBoxLayout *mediaPlayerAdditionalOptionsLayout1 = new QVBoxLayout;
    mediaPlayerAdditionalOptionsLayout1->addWidget
        ( mediaPlayerAdditionalOptionsLabel_ );
    mediaPlayerAdditionalOptionsLayout1->addWidget
        ( mediaPlayerAdditionalOptionsLineEdit_ );

    QVBoxLayout *cmdToExecuteLayout1 = new QVBoxLayout;
    cmdToExecuteLayout1->addWidget
        ( cmdToExecuteLabel_ );
    cmdToExecuteLayout1->addWidget
        ( cmdToExecuteLineEdit_ );
    
    QHBoxLayout *compositeWidgetsLayout1 = new QHBoxLayout;
    compositeWidgetsLayout1->addWidget( frameEditWidget_ );
    compositeWidgetsLayout1->addWidget( speedEditWidget_ );
    
    QHBoxLayout *buttonsAtBottomLayout1 = new QHBoxLayout;
    buttonsAtBottomLayout1->addWidget( startButton_ );
    buttonsAtBottomLayout1->addWidget( stopButton_ );
    buttonsAtBottomLayout1->addWidget( aboutButton_ );
    buttonsAtBottomLayout1->addWidget( exitButton_ );
    
    QVBoxLayout *mainLayout = new QVBoxLayout( this );
    mainLayout->addLayout( mediaFilenameLayout1 );
    mainLayout->addLayout( mediaPlayerFileLocationLayout1 );
    mainLayout->addLayout( mediaPlayerAdditionalOptionsLayout1 );
    mainLayout->addLayout( cmdToExecuteLayout1 );
    mainLayout->addLayout( compositeWidgetsLayout1 );
    mainLayout->addLayout( buttonsAtBottomLayout1 );

    // Load the settings.
    settings_.loadSettings();
    mediaFilenameLineEdit_->setText( settings_.mediaFilename() );
    mediaPlayerFileLocationLineEdit_->setText
        ( settings_.mediaPlayerFileLocation() );
    mediaPlayerAdditionalOptionsLineEdit_->setText
        ( settings_.mediaPlayerAdditionalOptions() );
    frameEditWidget_->setFrameSizeSec( settings_.frameSizeSec() );
    frameEditWidget_->setFrameStartTimeSec( settings_.frameStartTimeSec() );
    speedEditWidget_->setSpeed( settings_.playbackSpeed() );
    if( settings_.isMediaFilenameLocked() == true )
    {
        // First set it to false, and toggle it to true.
        settings_.setMediaFilenameLocked( false );
        this->mediaFileLockedUnlockedClicked();
    }
    
    // Make some connections.
    
    // Simple stuff first... connect the buttons.
    connect( browseForMediaFileButton_, SIGNAL(clicked()),
             this, SLOT(browseForMediaFileClicked()) );
    connect( browseForMediaPlayerButton_, SIGNAL(clicked()),
             this, SLOT(browseForMediaPlayerClicked()) );
    connect( lockUnlockMediaButton_, SIGNAL(clicked()),
             this, SLOT(mediaFileLockedUnlockedClicked()) );
    connect( startButton_, SIGNAL(clicked()),
             this, SLOT(startButtonClicked()) );
    connect( stopButton_, SIGNAL(clicked()),
             this, SLOT(stopButtonClicked()) );
    connect( aboutButton_, SIGNAL(clicked()),
             this, SLOT(aboutButtonClicked()) );
    connect( exitButton_, SIGNAL(clicked()),
             this, SLOT(exitButtonClicked()) );
    
    // If something changes, run the slot parametersChanged().  This
    // has to manually be done for lock/unlock media filename.
    // Everything else, do it.
    connect( mediaPlayerFileLocationLineEdit_, 
             SIGNAL( textChanged(const QString&) ),
             this, SLOT(parametersChanged()) );
    connect( mediaPlayerAdditionalOptionsLineEdit_,
             SIGNAL( textChanged(const QString&) ),
             this, SLOT(parametersChanged()) );
    connect( frameEditWidget_, SIGNAL(frameStartTimeSecUpdated(int)),
             this, SLOT(parametersChanged()) );
    connect( frameEditWidget_, SIGNAL(frameSizeSecUpdated(int)),
             this, SLOT(parametersChanged()) );
    connect( speedEditWidget_, SIGNAL(speedUpdated(int)),
             this, SLOT(parametersChanged()) );
    
    // This is so we can maintain control over the looping process.
    connect( &looper_, SIGNAL(processStarted()),
             this, SLOT(handleProcessStarted()) );
    
    // Update the cmdToExecuteLineEdit_ with valid values for what's
    // in the widgets now.
    this->parametersChanged();
}

LooperDialog::~LooperDialog()
{
    settings_.saveSettings();
}

void LooperDialog::keyPressEvent( QKeyEvent *e ) 
{
    switch( e->key() ) 
    {
    case Qt::Key_Left:
        if( e->modifiers() == Qt::NoModifier )
        {
            e->accept();
            frameEditWidget_->adjustFrameSize( -1 );
            return;
        }
        else if( e->modifiers() & Qt::ShiftModifier ||
                 e->modifiers() & Qt::ControlModifier ||
                 e->modifiers() & Qt::AltModifier ||
                 e->modifiers() & Qt::MetaModifier )
        {
            e->accept();
            frameEditWidget_->adjustFrameStartTime( -1 );
            return;
        }
        break;
    case Qt::Key_Right:
        if( e->modifiers() == Qt::NoModifier )
        {
            e->accept();
            frameEditWidget_->adjustFrameSize( 1 );
            return;
        }
        else if( e->modifiers() & Qt::ShiftModifier ||
                 e->modifiers() & Qt::ControlModifier ||
                 e->modifiers() & Qt::AltModifier ||
                 e->modifiers() & Qt::MetaModifier )
        {
            e->accept();
            frameEditWidget_->adjustFrameStartTime( 1 );
            return;
        }
        break;
    case Qt::Key_Up:
        e->accept();
        speedEditWidget_->adjustSpeed( 10 );
        return;
        break;
    case Qt::Key_Down:
        e->accept();
        speedEditWidget_->adjustSpeed( -10 );
        return;
        break;
    }
    
    e->ignore();        
}

// This will update the settings and the cmdToExecuteLineEdit_.
void LooperDialog::parametersChanged()
{
    // Only save to the settings if it has changed.
    if( mediaPlayerFileLocationLineEdit_->text() != 
        settings_.mediaPlayerFileLocation() )
    {
        settings_.setMediaPlayerFileLocation
            ( mediaPlayerFileLocationLineEdit_->text() );
    }
    
    if( mediaPlayerAdditionalOptionsLineEdit_->text() !=
        settings_.mediaPlayerAdditionalOptions() )
    {
        settings_.setMediaPlayerAdditionalOptions
            ( mediaPlayerAdditionalOptionsLineEdit_->text() );
    }

    if( frameEditWidget_->frameSizeSec() != settings_.frameSizeSec() )
    {
        settings_.setFrameSizeSec( frameEditWidget_->frameSizeSec() );
    }
    
    if( frameEditWidget_->frameStartTimeSec() != 
        settings_.frameStartTimeSec() )
    {
        settings_.setFrameStartTimeSec
            ( frameEditWidget_->frameStartTimeSec() );
    }
    
    if( speedEditWidget_->speed() != settings_.playbackSpeed() )
    {
        settings_.setPlaybackSpeed( speedEditWidget_->speed() );
    }

    // Enter stuff into the mplayer options manager.
    MPlayerOptionsManager mplayerOptionsManager;
    mplayerOptionsManager.setMPlayerFileLocation
        ( settings_.mediaPlayerFileLocation() );
    mplayerOptionsManager.setAdditionalCmdlineOptions
        ( settings_.mediaPlayerAdditionalOptions() );
    mplayerOptionsManager.setPlaybackSpeed
        ( settings_.playbackSpeed() );
    mplayerOptionsManager.setFrameStartTimeSec
        ( settings_.frameStartTimeSec() );
    
    // Set the cmdToExecuteLineEdit_.
    cmdToExecuteLineEdit_->setText( mplayerOptionsManager.execStr() + 
                                    QString( " " ) +
                                    QString( "\"" ) +
                                    settings_.mediaFilename() +
                                    QString( "\"" ) );


    // Update the looper.
    looper_.setCmdToExecute( cmdToExecuteLineEdit_->text() );
    looper_.setLoopingInterval( settings_.frameSizeSec() );
}

void LooperDialog::browseForMediaFileClicked()
{
    QFileDialog fileDialog( this );

    fileDialog.setFileMode( QFileDialog::ExistingFile );
    fileDialog.setWindowTitle( "Select Media File" );
    // fileDialog.setFilter( "Media files (*.mp3 *.mpeg *.mpg *.ogg *.avi *.wav *.avi *.mov *.ogm *.spx *.asf *.wm *.wma *.wmv *.mp2 *.mpa *.mid *.midi)" );

    if( fileDialog.exec() )
    {
        QStringList mediaFiles = fileDialog.selectedFiles();
        QString mediaFile = mediaFiles.first();
        mediaFilenameLineEdit_->setText( mediaFile );
    }
}

void LooperDialog::browseForMediaPlayerClicked()
{
    QFileDialog fileDialog( this );

    fileDialog.setFileMode( QFileDialog::ExistingFile );
    fileDialog.setWindowTitle( "Select Media Player" );

    if( fileDialog.exec() )
    {
        QStringList mediaPlayers = fileDialog.selectedFiles();
        QString mediaPlayer = mediaPlayers.first();
        mediaPlayerFileLocationLineEdit_->setText( mediaPlayer );
    }
}


void LooperDialog::mediaFileLockedUnlockedClicked()
{

    if( settings_.isMediaFilenameLocked() == false )
    {
        // The user is locking the QLineEdit.

        if( mediaFilenameLineEdit_->text() == "" )
        {
            QMessageBox::information( this, tr("Oops!"),
                                      QString( "You can't lock an empty " ) +
                                      QString( "media file!  Please browse" ) +
                                      QString( " and a select a file " ) + 
                                      QString( "before locking it." ) );
            return;
        }


        // Save the stuff in the settings.
        settings_.setMediaFilename( mediaFilenameLineEdit_->text() );
        settings_.setMediaFilenameLocked( true );

        // Rename the lock button to "Unlock", and lock the QLineEdit.
        lockUnlockMediaButton_->setText( "&Unlock" );
        mediaFilenameLineEdit_->setEnabled( false );
    
        // Enable the start button, disable the stop button.
        startButton_->setEnabled( true );
        stopButton_->setEnabled( false );

        // Retrieve the duration of the media file.
        MediaInfo mediaInfo( settings_.mediaFilename() );

        // TODO:  Take this out on production.(linux non-testing version).
        //         mediaInfo.setFFMPEGLocation( "/home/rluu/programming/OptionsPrinter/ffmpeg_fake.exe" );
        //        mediaInfo.setFFMPEGLocation( "C:/msys/1.0/home/rluu/programming/OptionsPrinter/ffmpeg_fake.exe" );
        // Actually this next line is not needed.  "ffmpeg" is the default.
        //        mediaInfo.setFFMPEGLocation( "ffmpeg" );

        quint32 durationSecs = QTime().secsTo( mediaInfo.getDuration() );

        frameEditWidget_->setDuration( durationSecs );
        
        // Update the cmdToExecuteLineEdit_.
        parametersChanged();
    }
    else
    {
        // The user is unlocking the QLineEdit.

        // Save the stuff in the settings.
        settings_.setMediaFilenameLocked( false );

        // Rename the unlock button to "Lock", and reenable the QLineEdit.
        lockUnlockMediaButton_->setText( "&Lock" );
        mediaFilenameLineEdit_->setEnabled( true );
        
        // Disable the start button.
        startButton_->setEnabled( false );

        // Selects the text field of the QLineEdit.
        mediaFilenameLineEdit_->selectAll();
    }
}

void LooperDialog::startButtonClicked()
{
    if( settings_.isMediaFilenameLocked() == false )
    {
        QMessageBox::information( this, tr("Oops!"),
                                  QString( "You must lock a media " ) +
                                  QString( "filename before starting." ) );
        return;
    }
    
    if( settings_.mediaPlayerFileLocation() == "" )
    {
        QMessageBox::information( this, tr("Oops!"),
                                  QString( "You must set the media player " ) +
                                  QString( "location before starting." ) );
        return;
    }
    
    // Disable start button.
    startButton_->setEnabled( false );

    // Enable stop button.
    stopButton_->setEnabled( true );

    // Disable lock/unlock button.
    lockUnlockMediaButton_->setEnabled( false );

    // Start the looper.
    looper_.startLooping();
}

void LooperDialog::stopButtonClicked()
{
    // Stop the looper.
    looper_.stopLooping();

    // Enable start button.
    startButton_->setEnabled( true );

    // Disable stop button.
    stopButton_->setEnabled( false );

    // Enable lock/unlock button.
    lockUnlockMediaButton_->setEnabled( true );

}

void LooperDialog::aboutButtonClicked()
{
    AboutDialog aboutDialog( this );
    aboutDialog.exec();
}

void LooperDialog::exitButtonClicked()
{
    // On exit, we'll call accept, which will return success.  On
    // exit, it will automattically destruct this object, calling the
    // destructor and saving the settings as well.  QObjects (and
    // objects that inherit from a QObject) that were dynamically
    // allocated in this class instantiation are automatically
    // deallocated.
    QDialog::accept();
}


void LooperDialog::handleProcessStarted() 
{
    // Change focus so it's on top.
    //     QTimer::singleShot( 1500, this, SLOT(raiseAndFocusWindow()) );
    
}

void LooperDialog::raiseAndFocusWindow()
{
    QWidget::activateWindow();
    QWidget::raise();
}
