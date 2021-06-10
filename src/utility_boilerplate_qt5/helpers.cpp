#include "helpers.hpp"

#include <QCommandLineParser>
#include <debug_new>

QStringList ub_helpers::parseFirstArgumentAsFile(const QApplication& app) {
    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", "File to open.");
    parser.process(app);
    return parser.positionalArguments();
}
