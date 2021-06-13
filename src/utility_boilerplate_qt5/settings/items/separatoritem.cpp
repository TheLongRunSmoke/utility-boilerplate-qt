#include "separatoritem.hpp"

#include <QFrame>
#include <debug_new>

SeparatorItem::~SeparatorItem() { delete _view; }

QWidget* SeparatorItem::view(QWidget* parent) {
    if (_view) return _view;
    auto* widget = new QFrame();
    widget->setFrameShape(QFrame::HLine);
    widget->setFrameShadow(QFrame::Plain);
    _view = widget;
    return _view;
}
