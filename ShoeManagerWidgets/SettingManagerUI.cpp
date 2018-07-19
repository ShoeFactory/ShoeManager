#include "SettingManagerUI.hpp"
#include <QHBoxLayout>
#include <QDebug>
#include "SettingProfileEditorUI.hpp"
#include "SettingDeviceEditor.hpp"

#include <QTimer>

SettingManagerUI::SettingManagerUI(int defaultItem, QWidget *parent)
    : QUtilsFramelessDialog(parent)
{
    initLayout();
    initConnection();

    pListWidget->setCurrentRow(defaultItem);
}

void SettingManagerUI::initLayout()
{
    pListWidget = new ZListWidget;
    {
        pProfile = new QListWidgetItem("账户设置");
        pDevice = new QListWidgetItem("设备管理");

        pListWidget->addItem(pProfile);
        pListWidget->addItem(pDevice);
    }

    pStackWidget = new QStackedWidget;
    {
        pProfileEditer = new SettingProfileEditorUI;
        pDeviceEditor = new SettingDeviceEditor;

        pStackWidget->addWidget(pProfileEditer);
        pStackWidget->addWidget(pDeviceEditor);
        pStackWidget->layout()->setMargin(0);
    }

    QHBoxLayout *hboxMain = new QHBoxLayout;
    {
        hboxMain->addWidget(pListWidget, 1);
        hboxMain->addWidget(pStackWidget,3);
        hboxMain->setMargin(0);
        hboxMain->setSpacing(0);
        this->setBodyLayout(hboxMain);

        resize(600, 450);
    }

    setTitleText("设置");
}

void SettingManagerUI::initConnection()
{
    connect(pListWidget, &ZListWidget::currentRowChanged, pStackWidget, &QStackedWidget::setCurrentIndex);
}
