#include "BMapControlPanel.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>
#include "ShoeManagerNetwork.hpp"
#include "ShoeManagerNetworkResult.hpp"

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
        mDeviceModel.isSubscribed = checked;
    });
}

void DeviceControlItem::setDeviceModel(const ShoeDeviceModel &deviceModel)
{
    mDeviceModel = deviceModel;

    pLabelName->setText(mDeviceModel.name);
    pLabelStatusValue->setText(mDeviceModel.isOnline? "在线": "离线");
    pLabelIMEIValue->setText(mDeviceModel.imei);

    QString power = QString("%1").arg(mDeviceModel.powerPercent, 0, 'f', 2);
    pLabelPowerValue->setText(power);
    pSwitchButton->setChecked(mDeviceModel.isSubscribed);
}

ShoeDeviceModel DeviceControlItem::deviceModel() const
{
    return mDeviceModel;
}

BMapControlPanel::BMapControlPanel(QWidget *parent) : QWidget(parent)
{
    initLayout();
    initConnection();
}

void BMapControlPanel::initLayout()
{
    auto *hboxMenu = new QHBoxLayout;
    {
        buttonJS = new QPushButton("Alert");
        hboxMenu->addWidget(buttonJS);

        buttonFlush = new QPushButton("刷新");
        hboxMenu->addWidget(buttonFlush);
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
    connect(buttonJS, &QPushButton::clicked, BMapDataCenter::getInstance(), &BMapDataCenter::slotAlert);
    connect(buttonFlush, &QPushButton::clicked, this, &BMapControlPanel::flushDeviceList);
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
        QList<ShoeDeviceModel> deviceList;
        parseJson(deviceList, result->oReturnData);
        updateData(deviceList);
    }
    else
    {
        qDebug() << result->oReturnMessage;
    }
}

void BMapControlPanel::updateData(const QList<ShoeDeviceModel> modelList)
{
    for(auto newModel: modelList)
    {
        bool existedInUI = false;
        DeviceControlItem *existedUI;

        for(auto *controlItem: lControlItemList)
        {
            if(newModel == controlItem->deviceModel())
            {
                existedUI = controlItem;
                existedInUI = true;
                break;
            }
        }

        // 在界面上更新后台状态改变的
        if(existedInUI)
        {
            auto oldModel = existedUI->deviceModel();
            oldModel.powerPercent = newModel.powerPercent;
            oldModel.isOnline = newModel.isOnline;
            existedUI->setDeviceModel(oldModel);
        }
        // 在界面上插入后台新添加的
        else
        {
            DeviceControlItem *newUI = new DeviceControlItem;
            newUI->setDeviceModel(newModel);
            vboxDevice->insertWidget(0, newUI);
            lControlItemList.append(newUI);
        }
    }

    // 从界面上删除已经被后台删除的
    for(int i=lControlItemList.count()-1; i>=0 ; i--)
    {
        auto *controlItem = lControlItemList.at(i);
        if(!modelList.contains(controlItem->deviceModel()))
        {
            vboxDevice->removeWidget(controlItem);
            lControlItemList.removeOne(controlItem);
            controlItem->deleteLater();
        }
    }

}

void BMapControlPanel::showEvent(QShowEvent *event)
{
    flushDeviceList();
    QWidget::showEvent(event);
}
