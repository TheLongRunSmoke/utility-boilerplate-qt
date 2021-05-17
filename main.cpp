#include <QtWidgets/QApplication>
#include "utility_boilerplate_qt5/helpers.hpp"
#include "mainwindow.hpp"

#ifdef DEBUG
#include "utility_boilerplate_qt5/nvwa/debug_new.h"
#endif


int main(int argc, char *argv[]) {
#ifdef DEBUG
    // Prepare NVWA leak detection.
    nvwa::new_progname = argv[0];
#endif
    int* test = new int(0);
    // Load app resources.
    Q_INIT_RESOURCE(utility_boilerplate_qt);
    // Set you own app name and version here.
    QCoreApplication::setApplicationName("Utility Boilerplate Qt");
    QCoreApplication::setApplicationVersion("1.0");
    QApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);
    // Create normal Qt application class.
    QApplication app(argc, argv);
    // Parse command line arguments.
    QStringList arguments = UBHelpers::parseFirstArgumentAsFile(app);
    // Create main window.
    MainWindow mainWin;
    // Open file if requested.
    if (!arguments.isEmpty())
        mainWin.loadFile(arguments.first());
    mainWin.show();
    int result;
    try {
        result = QApplication::exec();
    } catch (std::exception &e) {
        qFatal("Error %s", e.what());
    }
    return result;
}