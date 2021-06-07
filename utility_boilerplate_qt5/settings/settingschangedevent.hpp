#ifndef UTILITY_BOILERPLATE_QT_SETTINGSCHANGEDEVENT_HPP
#define UTILITY_BOILERPLATE_QT_SETTINGSCHANGEDEVENT_HPP

#include <QEvent>

/**
 * This event sent when user change settings.
 */
class SettingsChangedEvent : public QEvent {
public:
    SettingsChangedEvent();

    /**
     * Registered this event in QEvent system, return used to init _eventType.
     * @return id for this type of event.
     */
    static QEvent::Type type();

private:

    /**
     * Type of this event inside QEvent system.
     */
    static QEvent::Type _eventType;
};

#endif //UTILITY_BOILERPLATE_QT_SETTINGSCHANGEDEVENT_HPP
