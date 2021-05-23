#ifndef UTILITY_BOILERPLATE_QT_SETTINGSCHANGEDEVENT_HPP
#define UTILITY_BOILERPLATE_QT_SETTINGSCHANGEDEVENT_HPP

#include <QEvent>

class SettingsChangedEvent : public QEvent {
public:
    SettingsChangedEvent();

    static QEvent::Type type();

private:
    static QEvent::Type _eventType;
};

#endif //UTILITY_BOILERPLATE_QT_SETTINGSCHANGEDEVENT_HPP
