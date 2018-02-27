#include "BMapControlPanel.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include "ShoeManagerNetwork.hpp"
#include "ShoeManagerNetworkResult.hpp"
#include <QTimer>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

DeviceControlItem::DeviceControlItem(QWidget *parent)
    : QWidget(parent)
{
    initLayout();
    initConnection();
}

void DeviceControlItem::initLayout()
{
    QVBoxLayout *vbox = new QVBoxLayout;
    {
        pLabelName = new QLabel;
        pLineName = new QUtilsLayoutLine;

        vbox->addWidget(pLabelName, 0, Qt::AlignLeft);
        vbox->addWidget(pLineName);
    }

    QGridLayout *grid = new QGridLayout;
    {
        pLabelStatus = new QLabel("[状态]： ");
        pLabelSwitch = new QLabel("[监视]： ");
        pLabelIMEI = new QLabel("[IMEI]： ");
        pLabelPower = new QLabel("[电量]： ");

        pLabelStatusValue = new QLabel;
        pSwitchButton = new SwitchButton;
        pLabelIMEIValue = new QLabel;
        pLabelPowerValue = new QLabel;

        grid->addWidget(pLabelStatus,      0, 0, 1, 1);
        grid->addWidget(pLabelStatusValue, 0, 1, 1, 3);
        grid->addWidget(pLabelSwitch,      0, 4, 1, 1);
        grid->addWidget(pSwitchButton,     0, 5, 1, 1);

        grid->addWidget(pLabelIMEI,        1, 0, 1, 1);
        grid->addWidget(pLabelIMEIValue,   1, 1, 1, 3);
        grid->addWidget(pLabelPower,       1, 4, 1, 1);
        grid->addWidget(pLabelPowerValue,  1, 5, 1, 1);
    }

    QVBoxLayout *vboxMain = new QVBoxLayout(this);
    {
        vboxMain->addLayout(vbox);
        vboxMain->addLayout(grid);
    }
}

void DeviceControlItem::initConnection()
{
    connect(pSwitchButton, &SwitchButton::checkedChanged, [=](bool checked){
        emit switchButtonChecked(pLabelIMEIValue->text(), checked);
    });
}

void DeviceControlItem::setDeviceModel(const ShoeDeviceModel * const deviceModel)
{
    pLabelName->setText(deviceModel->name);
    pLabelIMEIValue->setText(deviceModel->imei);
    pSwitchButton->setChecked(deviceModel->isSubscribed);
    pLabelStatusValue->setText(deviceModel->isOnline? "在线": "离线");
    pLabelPowerValue->setText(QString("%1").arg(deviceModel->powerPercent, 0, 'f', 2));
}

BMapControlPanel::BMapControlPanel(QWidget *parent) : QWidget(parent)
{
    initLayout();
    initConnection();
}

void BMapControlPanel::initLayout()
{

    {
        timerFetchDeviceData = new QTimer;
        timerFetchDeviceData->setInterval(5000);
    }


    auto *hboxMenu = new QHBoxLayout;
    {
        btnflushDeviceList = new QPushButton("刷新");
        hboxMenu->addWidget(btnflushDeviceList);
    }


    vboxDevice = new QVBoxLayout;
    {

    }

     QWidget *scrollWidget = new QWidget;
     {
         QVBoxLayout *vbox = new QVBoxLayout(scrollWidget);
         vbox->addLayout(hboxMenu);
         vbox->addLayout(vboxDevice);
         vbox->addStretch(1);
     }

    QVBoxLayout *vboxMain = new QVBoxLayout(this);
    {
        QScrollArea *scrollArea = new QScrollArea;
        scrollArea->setWidget(scrollWidget);
        scrollArea->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
        scrollArea->setWidgetResizable(true);

        vboxMain->addWidget(scrollArea);
        setMinimumWidth(300);
    }
}

void BMapControlPanel::initConnection()
{
    connect(btnflushDeviceList, &QPushButton::clicked, this, &BMapControlPanel::flushDeviceList);
    connect(timerFetchDeviceData, &QTimer::timeout, [=](){
       flushDeviceStatus(m_CurrentDeviceModelMap.keys());
       flushDevicePosition(m_CurrentDeviceModelMap.keys() ,currentType);
    });
}

void BMapControlPanel::flushDeviceList()
{
    auto *result = ShoeManagerNetwork::getInstance()->bindDevices();
    connect(result, &ShoeManagerNetworkResult::requestFinished, this, &BMapControlPanel::flushDeviceListResult);
}

void BMapControlPanel::flushDeviceListResult()
{
    auto *result = static_cast<ShoeManagerNetworkResult*>(sender());
    if(result->oReturnCode == 0)
    {
        QList<ShoeDeviceModel> modelList;
        parseJson(modelList, result->oReturnData);
        QStringList targetIMEIs;
        for(ShoeDeviceModel &model: modelList)
            targetIMEIs.append(model.imei);

        QStringList currentIMEIs = m_CurrentDeviceModelMap.keys();      // 当前设备列表
        QStringList tobeRemovedIMEIs = m_CurrentDeviceModelMap.keys();  // 要从当前中删除的
        QStringList tobeAddedIMEIs;                                     // 要添加到当前中的

        // 计算出要添加和删除的
        for(QString imei: targetIMEIs)
        {
            if(!currentIMEIs.contains(imei))
                tobeAddedIMEIs.append(imei);
            tobeRemovedIMEIs.removeAll(imei);
        }

        // 新添
        for(QString imei: tobeAddedIMEIs)
        {
            ShoeDeviceModel *deviceModel = new ShoeDeviceModel;
            deviceModel->imei = imei;
            m_CurrentDeviceModelMap.insert(imei, deviceModel);
        }

        // 删除过时
        for(QString imei: tobeRemovedIMEIs)
        {
            ShoeDeviceModel *deviceModel = m_CurrentDeviceModelMap.value(imei);
            m_CurrentDeviceModelMap.remove(imei);
            delete deviceModel;
        }

        // beginReset;

        // 推毁
        QList<DeviceControlItem*> deviceControlList = m_CurrentDeviceViewMap.values();
        for(DeviceControlItem *item : deviceControlList)
            vboxDevice->removeWidget(item);
        qDeleteAll(deviceControlList);
        m_CurrentDeviceViewMap.clear();

        // 重建
        QList<ShoeDeviceModel*> deviceModelList = m_CurrentDeviceModelMap.values();
        for(ShoeDeviceModel *model : deviceModelList)
        {
            DeviceControlItem *newUI = new DeviceControlItem;
            newUI->setDeviceModel(model);
            connect(newUI, &DeviceControlItem::switchButtonChecked, this, &BMapControlPanel::subscribeDevice);
            vboxDevice->insertWidget(0, newUI);

            m_CurrentDeviceViewMap.insert(model->imei, newUI);
        }

        // endReset

        // 拉到列表后 更新一下状态
        flushDeviceStatus(m_CurrentDeviceModelMap.keys());
    }
    else
    {
        qDebug() << result->oReturnMessage;
    }
}

void BMapControlPanel::subscribeDevice(QString imei, bool checked)
{
    auto *result = ShoeManagerNetwork::getInstance()->setDeviceIsSubscibed(imei, checked);
    connect(result, &ShoeManagerNetworkResult::requestFinished, this, &BMapControlPanel::subscribeDeviceResult);
}

void BMapControlPanel::subscribeDeviceResult()
{
    auto *result = static_cast<ShoeManagerNetworkResult*>(sender());
    if(result->oReturnCode == 0)
    {
        flushDeviceStatus(m_CurrentDeviceModelMap.keys());
        flushDevicePosition(m_CurrentDeviceModelMap.keys(), currentType);
    }
    else
    {
        qDebug() << result->oReturnMessage;
    }
}

void BMapControlPanel::flushDeviceStatus(QStringList IMEIs)
{
    auto *result = ShoeManagerNetwork::getInstance()->getDeviceStatus(IMEIs);
    connect(result, &ShoeManagerNetworkResult::requestFinished, this, &BMapControlPanel::flushDeviceStatusResult);
}

void BMapControlPanel::flushDeviceStatusResult()
{
    auto *result = static_cast<ShoeManagerNetworkResult*>(sender());
    if(result->oReturnCode == 0)
    {
        // 解析设备状态
        QJsonArray deviceStatusArray = result->oReturnData.toArray();
        for(QJsonValue deviceStatusValue: deviceStatusArray)
        {
            QJsonObject deviceStatusObject = deviceStatusValue.toObject();
            QString imei = deviceStatusObject["imei"].toString();

            if(m_CurrentDeviceModelMap.contains(imei))
            {
                auto *deviceModel = m_CurrentDeviceModelMap.value(imei);

                deviceModel->name = deviceStatusObject["name"].toString();
                deviceModel->isOnline = deviceStatusObject["isOnline"].toBool();
                deviceModel->powerPercent = deviceStatusObject["power"].toDouble();
                deviceModel->isSubscribed = deviceStatusObject["isSubscribed"].toBool();
            }
        }

        // 更新设备界面
        QStringList imeis = m_CurrentDeviceModelMap.keys();
        for(QString imei : imeis)
        {
            DeviceControlItem *view = m_CurrentDeviceViewMap.value(imei);
            ShoeDeviceModel  *model = m_CurrentDeviceModelMap.value(imei);

            if(view && model)
            {
                view->setDeviceModel(model);
            }
        }
    }
    else
    {
        qDebug() << result->oReturnMessage;
    }
}

void BMapControlPanel::flushDevicePosition(QStringList IMEIs, BMapControlPanel::PositionType type)
{
    auto *result = ShoeManagerNetwork::getInstance()->getDevicePosition(IMEIs, type);
    connect(result, &ShoeManagerNetworkResult::requestFinished, this, &BMapControlPanel::flushDevicePositionResult);
}

void BMapControlPanel::flushDevicePositionResult()
{
    auto *result = static_cast<ShoeManagerNetworkResult*>(sender());
    if(result->oReturnCode == 0)
    {
        QStringList subscribeDevices;
        QList<ShoeDeviceModel*> modelList = m_CurrentDeviceModelMap.values();
        for(ShoeDeviceModel *model : modelList)
        {
            if(model->isSubscribed)
                subscribeDevices.append(model->imei);
        }

        QJsonArray markerArray;
        QJsonArray positionArray = result->oReturnData.toArray();
        foreach (QJsonValue positionValue, positionArray) {
            QJsonObject position = positionValue.toObject();
            QString imei = position["imei"].toString();
            if(subscribeDevices.contains(imei))
                markerArray.append(position);
        }

        QJsonDocument doc(markerArray);
        BMapDataCenter::getInstance()->setMarkers(doc.toJson(QJsonDocument::Compact));
    }
    else
    {
        qDebug() << result->oReturnMessage;
    }
}

void BMapControlPanel::showEvent(QShowEvent *event)
{
    flushDeviceList();
    timerFetchDeviceData->start();

    QWidget::showEvent(event);
}

void BMapControlPanel::hideEvent(QHideEvent *event)
{
    timerFetchDeviceData->stop();

    QWidget::hideEvent(event);
}
