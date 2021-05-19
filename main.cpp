#include <QtWidgets/QApplication>
#include "utility_boilerplate_qt5/helpers.hpp"
#include "mainwindow.hpp"
#include <debug_new>

#ifndef NDEBUG
extern "C" bool whitelist_callback(char const *file, int line, void *addr, void **stacktrace) {
    // Whitelist memory leak if it false positive.
    return false;
}
#endif

int main(int argc, char *argv[]) {
#ifndef NDEBUG
    // Prepare NVWA leak detection.
    nvwa::new_progname = argv[0];
    nvwa::leak_whitelist_callback = whitelist_callback;
    // Let's create debug memory leak. You can see it in trace.
    int *leak = new int(0);
#endif
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
    if (!arguments.isEmpty()) {
        mainWin.loadFile(arguments.first());
    }
    mainWin.show();
    int result;
    try {
        result = QApplication::exec();
    } catch (std::exception &e) {
        qFatal("Error %s", e.what());
    }
    return result;
}

