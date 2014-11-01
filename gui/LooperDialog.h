
#ifndef LOOPERDIALOG_H
#define LOOPERDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QKeyEvent>
#include <QTimer>
#include <QFileDialog>
#include <QMessageBox>


#include "FrameEditWidget.h"
#include "SpeedEditWidget.h"
#include "LooperSettings.h"
#include "Looper.h"
#include "MediaInfo.h"
#include "MPlayerOptionsManager.h"
#include "AboutDialog.h"


class LooperDialog : public QDialog
{
    Q_OBJECT
public:
    LooperDialog( QWidget* parent = 0, Qt::WFlags f = 0 );
    virtual ~LooperDialog();

protected:
  void keyPressEvent( QKeyEvent * );

private slots:
    // This will update the settings and the cmdToExecuteLineEdit_.
    void parametersChanged();

    void browseForMediaFileClicked();
    void browseForMediaPlayerClicked();
    void mediaFileLockedUnlockedClicked();

    void startButtonClicked();
    void stopButtonClicked();
    void aboutButtonClicked();
    void exitButtonClicked();

    
    void handleProcessStarted();    
    void raiseAndFocusWindow();
private:
    LooperSettings settings_;
    Looper looper_;

    // Widgets.
    QLabel *mediaFilenameLabel_;
    QLabel *mediaPlayerFileLocationLabel_;
    QLabel *mediaPlayerAdditionalOptionsLabel_;
    QLabel *cmdToExecuteLabel_;

    QLineEdit *mediaFilenameLineEdit_;
    QLineEdit *mediaPlayerFileLocationLineEdit_;
    QLineEdit *mediaPlayerAdditionalOptionsLineEdit_;
    QLineEdit *cmdToExecuteLineEdit_;  // Read only.
    
    QPushButton *browseForMediaFileButton_;
    QPushButton *browseForMediaPlayerButton_;
    QPushButton *lockUnlockMediaButton_;

    QPushButton *startButton_;
    QPushButton *stopButton_;
    QPushButton *aboutButton_;
    QPushButton *exitButton_;

    FrameEditWidget *frameEditWidget_;
    SpeedEditWidget *speedEditWidget_;
};


#endif     // #ifndef LOOPERDIALOG_H
