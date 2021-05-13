#ifndef UTILITY_BOILERPLATE_QT_SETTINGITEM_HPP
#define UTILITY_BOILERPLATE_QT_SETTINGITEM_HPP

#include <QString>
#include <QLayout>

/**
 * Abstract class for setting item.
 */
class SettingItem {

public:
    explicit SettingItem(
            QString key
    ) : _key{std::move(key)} {};

    virtual ~SettingItem() {};

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

protected:
    /**
     * Key that used for storage.
     */
    QString _key = nullptr;
};


#endif //UTILITY_BOILERPLATE_QT_SETTINGITEM_HPP
