// Simple class to display the license in a textedit widget.

#ifndef LICENSEDIALOG_H
#define LICENSEDIALOG_H

#include <QLayout>
#include <QDialog>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>

class LicenseDialog : public QDialog 
{
    Q_OBJECT
public:
    // Default constructor.
    LicenseDialog( QWidget* parent = 0, Qt::WFlags f = 0 );
    virtual ~LicenseDialog();

private slots:
    void closeClicked();     // Close this dialog.

private:
    void setLicenseString();  // Set the license string below.

    QString license_;             // The license string.

    QTextEdit *licenseTextEdit_;  // Text Edit holding the license string.

    QPushButton *closeButton_;    // Close dialog button.

};

#endif     // #ifndef LICENSEDIALOG_H
