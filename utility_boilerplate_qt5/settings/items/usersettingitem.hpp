#ifndef UTILITY_BOILERPLATE_QT_USERSETTINGITEM_HPP
#define UTILITY_BOILERPLATE_QT_USERSETTINGITEM_HPP

#include <QString>
#include <QLayout>

/**
 * Abstract class for setting item.
 */
class UserSettingItem {

public:
    explicit UserSettingItem(
            QString key
    ) : _key{std::move(key)} {};

    virtual ~UserSettingItem() = default;

    /**
     * View for settings dialog.
     *
     * @return pointer on QWidget representation.
     */
    virtual QWidget* view(QWidget* parent) = 0;

    /**
     * Actual selected value.
     */
    virtual QString value() = 0;

    virtual void setValue(QString value) = 0;

    virtual QString defaultValue() = 0;

    /**
     * Storage key.
     */
    QString key() { return _key; }

    /**
     * If key not set or empty, object do not hold any value and must not be saved.
     * @return
     */
    bool isDecoration() {
        if (_key == nullptr) return true;
        if (_key.isEmpty()) return true;
        return false;
    }

protected:

    /**
     * Key that used for storage.
     */
    QString _key = nullptr;
};

#endif //UTILITY_BOILERPLATE_QT_USERSETTINGITEM_HPP
