#ifndef UB_HELPERS_H
#define UB_HELPERS_H

#include <QApplication>
#include <QStringList>
#include <QKeySequence>
#include <QMenu>
#include <QToolBar>

namespace UBHelpers {
    QStringList parseFirstArgumentAsFile(const QApplication& app);
}

#endif //UB_HELPERS_H
