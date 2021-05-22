#include <QtWidgets/QApplication>
#include "utility_boilerplate_qt5/helpers.hpp"
#include "mainwindow.hpp"
#include "utility_boilerplate_qt5/settings/settings.hpp"
#include <debug_new>
#include <sstream>

#ifndef NDEBUG
/**
 * C style callback for NVWA memory leak detection.
 * Let you whitelist memory leaks if it false positive.
 *
 * By default, I assume that all project entities has debug_new included
 * and whitelisted all leak that do not have file name as Qt architecture caused false positive.
 *
 * @return true entity is whitelisted and hide from trace.
 * @return false entity is shown in trace as normal.
 */
extern "C" bool leak_whitelist_callback(char const *file, int line, void *addr, void **stacktrace) {
    // Input can be not zero-terminated, reading with stream is safer way.
    std::stringstream strm;
    strm << file;
    // If file name not empty, it must be leak in a project.
    if (!strm.str().empty()) return false;
    return true;
}
#endif

int main(int argc, char *argv[]) {
#ifndef NDEBUG
    // Prepare NVWA leak detection.
    nvwa::new_progname = argv[0];
    nvwa::leak_whitelist_callback = leak_whitelist_callback;
    // Let's create debug memory leak. You can see it in trace.
    int *leak = new int(0);
#endif
    // Load app resources.
    Q_INIT_RESOURCE(utility_boilerplate_qt);
    // Set you own app name and version here.
    QCoreApplication::setApplicationName("Utility Boilerplate Qt");
    QCoreApplication::setApplicationVersion("1.0");
    // Let's get rid of question mark.
    QApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);
    // Create normal Qt application class.
    QApplication app(argc, argv);
    // Init default settings.
    Settings *settings = new Settings();
    settings->initDefaults();
    QApplication::setStyle(settings->style());
    delete settings;
    // Parse command line arguments.
    QStringList arguments = UBHelpers::parseFirstArgumentAsFile(app);
    // Create main window.
    MainWindow mainWin;
    // Open file if requested.
    if (!arguments.isEmpty()) {
        mainWin.loadFile(arguments.first());
    }
    // Prepare window.
    mainWin.show();
    int result;
    try {
        // Run application.
        result = QApplication::exec();
    } catch (std::exception &e) {
        // Catch exception if it make its way down here.
        qFatal("Error %s", e.what());
    }
    return result;
}

