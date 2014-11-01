

#include "AboutDialog.h"


AboutDialog::AboutDialog( QWidget* parent, Qt::WFlags f )
    :
    QDialog( parent, f )
{
    // Set the About strings.
    setAboutStrings();
    
    // Create the push button.
    showLicenseButton_ = new QPushButton( tr("&Show License"), this );
    closeDialogButton_ = new QPushButton( tr("&Close"), this );
    
    // Create labels.
    aboutPicLabel_         = new QLabel( this );
    aboutInfoLabel_        = new QLabel( this );
    aboutLicenseLabel_     = new QLabel( this );
    aboutDescriptionLabel_ = new QLabel( this );
    
    //     // Set the picture label.
    //     aboutPicLabel_->setPixmap( QPixmap::fromMimeSource("frog.png") );
    
    // Set the text for the other labels.
    aboutInfoLabel_       ->setText(aboutInfoStr_);
    aboutLicenseLabel_    ->setText(aboutLicenseStr_);
    aboutDescriptionLabel_->setText(aboutDescriptionStr_);

    // Set the font text for the labels.
    //   aboutInfoLabel_       ->setFont(courier);
    //   aboutLicenseLabel_    ->setFont(courier);
    //   aboutDescriptionLabel_->setFont(courier);

    // Set up the layout of the dialog.  

    // This is how the layouts are set up.  There are two layouts
    // within the main layout.  They are the top layout and the bottom
    // layout.  The top layout contains most of About stuff.  The top
    // layout contains a left layout and a right layout.  The left
    // layout contains just icon label.  The right layout actually
    // contains the text and raw meat of the About info.  There a
    // layout embedded in the right layout, it is the licenseLayout,
    // which is used so we can add a button to view the license inside
    // the right layout.

    // This layout is a horizontal layout that contains the license
    // label and a button to display the license.
    QHBoxLayout *licenseLayout = new QHBoxLayout;
    licenseLayout->addWidget(aboutLicenseLabel_);
    licenseLayout->addWidget(showLicenseButton_);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addSpacing(20);
    leftLayout->addWidget(aboutPicLabel_);
    leftLayout->addStretch(1);
  
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addSpacing(20);  
    rightLayout->addWidget(aboutDescriptionLabel_);
    rightLayout->addSpacing(30);
    rightLayout->addWidget(aboutInfoLabel_);
    rightLayout->addSpacing(30);
    rightLayout->addLayout(licenseLayout);
    rightLayout->addSpacing(30);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addLayout(leftLayout);
    topLayout->addSpacing(20);
    topLayout->addLayout(rightLayout);
  
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(closeDialogButton_);

    // Connect the signals to slots for the buttons.
    connect(showLicenseButton_, SIGNAL(clicked()),
	    this, SLOT(showLicenseButtonClicked()));
    connect(closeDialogButton_, SIGNAL(clicked()),
            this, SLOT(accept()));
}

AboutDialog::~AboutDialog()
{
    // Empty.
}

void AboutDialog::showLicenseButtonClicked() {
  LicenseDialog licenseDialog(this);
  licenseDialog.exec();
}



// Helper function for the constructor to make it clearer to read what
// the constructor is doing.
void AboutDialog::setAboutStrings() {

  // About:  License.  (As Normal Text).
  aboutLicenseStr_ = tr("License: GNU General Public License (GPL).");

  // About:  General info about usage.  (As Normal Text).
  aboutInfoStr_ = QString("SuperLooper") + tr(" version ") 
    + QString(VERSION) + tr(", Copyright (C) ") + QString(YEAR)
    + QString(" Ryan Luu.\n") 
    + QString("SuperLooper") + tr(" comes with ABSOLUTELY NO WARRANTY.\n")
    + tr("This is free software made by myself, Ryan Luu, and \n")
    + tr("you are welcome ")
    + tr("to redistribute it under certain conditions.  \n\n")
    + tr("My email contact is: ryanluu@gmail.com\n");


  // About:  Application description.  (as Rich Text)
  aboutDescriptionStr_ = 
      tr("SuperLooper is a program that loops playback <br />") +
      tr("of an audio or video file.  The playback of the <br />") +
      tr("audio or video file can be customized to play at <br />") +
      tr("different playback speeds, frame lengths, and starting <br />") +
      tr("points.  These customizations allow users to utilze <br />") +
      tr("this application as a tool in transcribing audio <br />") +
      tr("and video.<br />");
}

