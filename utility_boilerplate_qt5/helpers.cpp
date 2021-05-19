#include "helpers.hpp"

#include <QCommandLineParser>
#include <debug_new>

/**
* Handle command line params, keys and help message.
*
* @param app application object link.
* @return list of given command line args, can be empty.
*/
QStringList UBHelpers::parseFirstArgumentAsFile(const QApplication& app) {
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", "File to open.");
    parser.process(app);
    return parser.positionalArguments();
}
