#include "events.hpp"

template <> QEvent::Type UBEvent<SettingsChangedEvent>::_eventType = QEvent::None;
template <> QEvent::Type UBEvent<DocumentModifiedEvent>::_eventType = QEvent::None;

DocumentModifiedEvent::DocumentModifiedEvent(bool isModified) : _value(isModified) {}
