#include <QApplication>
#include <QTranslator>
#include <helpers.hpp>

#include "example/mainwindow.hpp"
#include "example/texteditorsettings.hpp"

#include <QDateTime>
#include <QFile>
#include <QTextStream>

#include <debug_new>  // Must be last one.

#ifdef NVWA_INCLUDE
/**
 * C style callback for NVWA memory leak detection.
 * Let you whitelist memory leaks if it false positive.
 *
 * By default, I assume that all project entities has debug_new included
 * and whitelisted all leak that do not have file name as Qt architecture caused
 * false positive.
 *
 * @return true entity is whitelisted and hide from trace.
 * @return false entity is shown in trace as normal.
 */
extern "C" bool leak_whitelist_callback(char const* file, int line, void* addr, void** stacktrace) {
    // If file name empty, it is leak not in project...or you forget to include
    // debug_new header somewhere.
    if (file == nullptr) return true;
    auto filename = std::string(file);
    // Let's whitelist something.
    // I used QEvent, it's object deleted outside of origin file and will be
    // detected.
    auto whitelist
        = std::map<std::string, std::list<int>>{{"settingsdialog.cpp", std::list<int>{46}}};
    // Iterate through whitelist and return true if coincidence found.
    for (auto const& it : whitelist) {
        if (filename.find(it.first) == std::string::npos) continue;
        for (auto const& row : it.second) {
            if (line == row) return true;
        }
    }
    // Has file name and not whitelisted? We found a leak!
    return false;
}
#endif

/**
 * Initialized and load application settings.
 */
void readSettings() {
    Settings* settings = new TextEditorSettings();
    // Init defaults if not set.
    settings->initDefaults();
    // Set style from settings.
    QApplication::setStyle(settings->style());
    delete settings;
}

int main(int argc, char* argv[]) {
#ifdef NVWA_INCLUDE
    // Prepare NVWA leak detection.
    nvwa::new_progname = argv[0];
    nvwa::leak_whitelist_callback = leak_whitelist_callback;
    // Let's create debug memory leak. You can see it in a trace.
    int* leak = new int(0);
#endif
    // Load app resources.
    Q_INIT_RESOURCE(app);
    // Set you own app name and version here.
    QCoreApplication::setApplicationName("Utility Boilerplate Qt");
    QCoreApplication::setApplicationVersion("1.0");
    // Get rid of question mark.
    QApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);
    // Create normal Qt application class.
    QApplication app(argc, argv);
    // Set logging handler here, if you need to redirect logs in to a file.
    // qInstallMessageHandler(messageHandler);
    // Load settings.
    readSettings();
    // Create main window.
    MainWindow mainWin;
    // Check command line arguments for file to open.
    QStringList arguments = ub_helpers::parseFirstArgumentAsFile(app);
    if (!arguments.isEmpty()) {
        mainWin.loadFile(arguments.first());
    }
    // Display window and run application.
    mainWin.show();
    int result;
    try {
        // Run application.
        result = QApplication::exec();
    } catch (std::exception& e) {
        // Catch exception if it make its way down here.
        qFatal("Error %s", e.what());
    }
    return result;
}
