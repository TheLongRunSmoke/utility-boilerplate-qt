#ifndef UTILITY_BOILERPLATE_QT_HELPERS_HPP
#define UTILITY_BOILERPLATE_QT_HELPERS_HPP

#include <QApplication>
#include <QKeySequence>
#include <QMenu>
#include <QStringList>
#include <QToolBar>

namespace ub_helpers {

    /**
     * Handle command line params, keys and help message.
     *
     * @param app application object link.
     * @return list of given command line args, can be empty.
     */
    QStringList parseFirstArgumentAsFile(const QApplication& app);

}  // namespace ub_helpers

#endif  // UTILITY_BOILERPLATE_QT_HELPERS_HPP
