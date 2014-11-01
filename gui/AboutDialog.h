#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#define VERSION "1.0.0"
#define YEAR "2006"

#include <QDialog>
#include <QLabel>
#include <QPushButton>

#include "LicenseDialog.h"

class AboutDialog : public QDialog
{
Q_OBJECT

public:
    AboutDialog( QWidget* parent = 0, Qt::WFlags f = 0 );
    virtual ~AboutDialog(); 
 
private slots:
    void showLicenseButtonClicked();
     
private:
    void setAboutStrings();
 
    // Buttons.
    QPushButton *showLicenseButton_;
    QPushButton *closeDialogButton_;
    
    // Picture label.
    QLabel *aboutPicLabel_;
    
    // About info label.
    QLabel *aboutLicenseLabel_;
    QLabel *aboutInfoLabel_;
    QLabel *aboutDescriptionLabel_;
    
    // Strings to put into the above labels.
    QString aboutLicenseStr_;
    QString aboutInfoStr_;
    QString aboutDescriptionStr_;

};


#endif    // #ifndef ABOUTDIALOG_H
