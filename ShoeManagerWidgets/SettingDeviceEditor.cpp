#include "SettingDeviceEditor.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "ShoeManagerNetwork.hpp"
#include "ShoeManagerNetworkResult.hpp"
#include "SettingDeviceAddDialog.hpp"
#include "QUtilsFramLessMessageBox.hpp"

#include <QJsonArray>
#include <QJsonObject>

SettingDeviceEditor::SettingDeviceEditor(QWidget *parent) : QWidget(parent)
{
    initLayout();
    initConnection();
}

void SettingDeviceEditor::initLayout()
{
    QHBoxLayout *hBoxMenu = new QHBoxLayout;
    {
        pButtonAdd = new QPushButton("添加");
        pButtonFlush = new QPushButton("刷新");

        hBoxMenu->addWidget(pButtonAdd);
        hBoxMenu->addWidget(pButtonFlush);
        hBoxMenu->addStretch(1);
    }

    QHBoxLayout *hboxTable = new QHBoxLayout;
    {
        pTableView = new QUtilsBetterTableView;
        pTableModel = new ShoeDeviceListModel;
        pTableDelegate = new QUtilsButtonsDelegate(pTableView);

        pTableView->setModel(pTableModel);

        pTableDelegate->setGroupColumn(pTableModel->Column_operate);
        pButtonDelete = pTableDelegate->addButton("delete");
        pButtonEdit = pTableDelegate->addButton("edit");
        pTableView->setItemDelegateForColumn(pTableModel->Column_operate, pTableDelegate);
        pTableView->setColumnInteractive(false);
        pTableView->setMouseTracking(true);

        ShoeDeviceModel model1;
        ShoeDeviceModel model2;
        pTableModel->setItemList({model1, model2});

        hboxTable->addWidget(pTableView);
    }

    QVBoxLayout *vboxMain = new QVBoxLayout;
    {
        vboxMain->addLayout(hBoxMenu, 1);
        vboxMain->addLayout(hboxTable, 100);
        this->setLayout(vboxMain);
    }

}

void SettingDeviceEditor::initConnection()
{
    connect(pButtonFlush, &QPushButton::clicked, this, &SettingDeviceEditor::flushDeviceList);
    connect(pButtonAdd, &QPushButton::clicked, this, &SettingDeviceEditor::addDeviceClicked);

    connect(pButtonDelete, &QAction::triggered, this, &SettingDeviceEditor::removeDeviceClicked);
    connect(pButtonEdit, &QAction::triggered, this, &SettingDeviceEditor::editDeviceClicked);
}

void SettingDeviceEditor::flushDeviceList()
{
    auto *result = ShoeManagerNetwork::getInstance()->bindDevices();
    connect(result, &ShoeManagerNetworkResult::requestFinished, this, &SettingDeviceEditor::flushDeviceListResult);
}

void SettingDeviceEditor::flushDeviceListResult()
{
    auto *result = static_cast<ShoeManagerNetworkResult*>(sender());
    if(result->oReturnCode == 0)
    {
        QList<ShoeDeviceModel> deviceList;
        parseJson(deviceList, result->oReturnData);
        pTableModel->setItemList(deviceList);
    }
    else
    {
        qDebug() << result->oReturnMessage;
    }
}

void SettingDeviceEditor::addDeviceClicked()
{
    SettingDeviceAddDialog addDevice(this);
    if(addDevice.exec() == QDialog::Accepted)
    {
        flushDeviceList();
    }
}

void SettingDeviceEditor::removeDeviceClicked()
{
    auto device = pTableModel->itemAtRow(pTableView->currentIndex().row());
    auto *result = ShoeManagerNetwork::getInstance()->unbindDevice(device.imei);
    if(result->oReturnCode == 0)
    {
        flushDeviceList();
    }
    else
    {
        QUtilsFramLessMessageBox::info(result->oReturnMessage);
    }
}

void SettingDeviceEditor::editDeviceClicked()
{
    QUtilsFramLessMessageBox::info("暂不支持编辑");
}

void SettingDeviceEditor::showEvent(QShowEvent *event)
{
    flushDeviceList();
    QWidget::showEvent(event);
}
