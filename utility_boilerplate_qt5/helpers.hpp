#ifndef UTILITY_BOILERPLATE_QT_HELPERS_HPP
#define UTILITY_BOILERPLATE_QT_HELPERS_HPP

#include <QApplication>
#include <QStringList>
#include <QKeySequence>
#include <QMenu>
#include <QToolBar>

namespace UBHelpers {

    /**
     * Handle command line params, keys and help message.
     *
     * @param app application object link.
     * @return list of given command line args, can be empty.
     */
    QStringList parseFirstArgumentAsFile(const QApplication& app);
}

#endif //UTILITY_BOILERPLATE_QT_HELPERS_HPP
