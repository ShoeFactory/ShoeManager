#include "MainWidget.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QMenu>

#include "ShoeManagerNetworkResult.hpp"
#include "ShoeManagerNetwork.hpp"
#include "SettingManagerUI.hpp"

MainWidget::MainWidget(QWidget *parent)
    : QUtilsFramelessWidget(parent)
{
    initLayout();
    initConnection();
}

MainWidget::~MainWidget()
{

}

void MainWidget::initLayout()
{
    // header 标题栏
    QHBoxLayout *hboxHeader = new QHBoxLayout;
    {
        mButtonUserProfile = new QPushButton("User");
        mButtonUserProfile->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        QMenu *menu = new QMenu;
        mButtonUserProfile->setMenu(menu);

        mActionProfileManage = menu->addAction("账户设置");
        mActionDevicesManage = menu->addAction("设备管理");

        hboxHeader->setMargin(0);
        hboxHeader->addStretch(1);
        hboxHeader->addWidget(mButtonUserProfile);
        this->setTitleToolBarLayout(hboxHeader);
    }

    // 主体
    QHBoxLayout *hboxMain = new QHBoxLayout;
    {
        mControlPanel = new BMapControlPanel;
        mMapContainter = new BMapContainer;

        hboxMain->addWidget(mControlPanel  , 1);
        hboxMain->addWidget(mMapContainter , 3);

        hboxMain->setMargin(0);
        hboxMain->setSpacing(0);
        this->setBodyLayout(hboxMain);
    }

    setTitleText("消防员定位监测系统");
}

void MainWidget::initConnection()
{
    connect(mActionProfileManage, &QAction::triggered, this, &MainWidget::profileManageButtonClicked);
    connect(mActionDevicesManage, &QAction::triggered, this, &MainWidget::devicesManageButtonClicked);
}

void MainWidget::showEvent(QShowEvent *event)
{
    getUserProfile();
    QWidget::showEvent(event);
}

void MainWidget::getUserProfile()
{
    ShoeManagerNetworkResult *result = ShoeManagerNetwork::getInstance()->userProfile();
    connect(result, &ShoeManagerNetworkResult::requestFinished, this, &MainWidget::parseUserProfile);
}

void MainWidget::parseUserProfile()
{
    ShoeManagerNetworkResult *result = (ShoeManagerNetworkResult*)sender();
    if(result->oReturnCode == 0)
    {
        auto object = result->oReturnData.toObject();
        QString name = object["name"].toString();
        mButtonUserProfile->setText(name);
    }
    else
    {
        qDebug() << result->oReturnMessage;
    }
}

void MainWidget::profileManageButtonClicked()
{
    SettingManagerUI settingDialog(0);
    settingDialog.exec();
}

void MainWidget::devicesManageButtonClicked()
{
    SettingManagerUI settingDialog(1);
    settingDialog.exec();
}
