
#include <QApplication>

#include "LooperDialog.h"

#define ORGANIZATION_NAME "Ryan Luu"
#define ORGANIZATION_DOMAIN ""
#define APPLICATION_NAME "SuperLooper"


int main( int argc, char *argv[] )
{
    QApplication app( argc, argv );
    app.setQuitOnLastWindowClosed( true );
    
    // These are required for persistent SuperLooper settings.
    app.setOrganizationName( ORGANIZATION_NAME );
    app.setOrganizationDomain( ORGANIZATION_DOMAIN );
    app.setApplicationName( APPLICATION_NAME );


    LooperDialog looperDialog;
    looperDialog.show();

    return app.exec();
}
