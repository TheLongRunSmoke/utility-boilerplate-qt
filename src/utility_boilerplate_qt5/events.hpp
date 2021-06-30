#ifndef UTILITY_BOILERPLATE_QT_EXAMPLE_EVENTS_HPP
#define UTILITY_BOILERPLATE_QT_EXAMPLE_EVENTS_HPP

#include <QEvent>

template <class Derived> class UBEvent : public QEvent {
  public:
    /**
     * Registered this event in QEvent system, return used to init _eventType.
     * @return id for this type of event.
     */
    static QEvent::Type type() {
        if (_eventType == QEvent::None) {
            int generatedType = QEvent::registerEventType();
            _eventType = static_cast<QEvent::Type>(generatedType);
        }
        return _eventType;
    };

  protected:
    UBEvent() : QEvent(type()){};

  private:
    static QEvent::Type _eventType;
};

/**
 * This event sent when user change settings.
 */
class SettingsChangedEvent : public UBEvent<SettingsChangedEvent> {
  public:
    SettingsChangedEvent() = default;
};

/**
 * This event sent when current document modified.
 */
class DocumentModifiedEvent : public UBEvent<DocumentModifiedEvent> {
  public:
    explicit DocumentModifiedEvent(bool isModified);

    bool isModified() const { return _value; }

  private:
    const bool _value = false;
};

#endif  // UTILITY_BOILERPLATE_QT_EXAMPLE_EVENTS_HPP
