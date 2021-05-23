#include "settingschangedevent.hpp"

QEvent::Type SettingsChangedEvent::_eventType = QEvent::None;

SettingsChangedEvent::SettingsChangedEvent() : QEvent(type()) {}

QEvent::Type SettingsChangedEvent::type() {
    if (_eventType == QEvent::None) {
        int generatedType = QEvent::registerEventType();
        _eventType = static_cast<QEvent::Type>(generatedType);
    }
    return _eventType;
}