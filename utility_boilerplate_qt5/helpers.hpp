#ifndef UTILITY_BOILERPLATE_QT_HELPERS_HPP
#define UTILITY_BOILERPLATE_QT_HELPERS_HPP

#include <QApplication>
#include <QStringList>
#include <QKeySequence>
#include <QMenu>
#include <QToolBar>

namespace UBHelpers {
    QStringList parseFirstArgumentAsFile(const QApplication& app);
}

#endif //UTILITY_BOILERPLATE_QT_HELPERS_HPP
