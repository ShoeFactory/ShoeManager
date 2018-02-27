#ifndef SETTINGMANAGERUI_HPP
#define SETTINGMANAGERUI_HPP

#include <QWidget>
#include <QStackedWidget>

#include "zlistwidget.h"
#include "navlistview.h"
#include "QUtilsFramelessDialog.hpp"

class SettingManagerUI : public QUtilsFramelessDialog
{
    Q_OBJECT

public:
    SettingManagerUI(int defaultItem, QWidget *parent=nullptr);

    void initLayout();
    void initConnection();

private:
    ZListWidget *pListWidget;
    QStackedWidget *pStackWidget;

    QListWidgetItem *pProfile;
    QListWidgetItem *pDevice;

    QWidget *pProfileEditer;
    QWidget *pDeviceEditor;
};

#endif // SETTINGMANAGERUI_HPP
