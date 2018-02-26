#ifndef BMAPCONTROLPANEL_HPP
#define BMAPCONTROLPANEL_HPP

#include <QWidget>
#include <QPushButton>
#include "BMapDataCenter.hpp"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "switchbutton.h"
#include "QUtilsLayoutLine.hpp"
#include "ShoeDeviceModel.hpp"

class DeviceControlItem : public QWidget
{
    Q_OBJECT
public:
    DeviceControlItem(QWidget *parent=nullptr);
    void initLayout();
    void initConnection();

    void setDeviceModel(const ShoeDeviceModel &deviceModel);
    ShoeDeviceModel deviceModel() const;

private:
    QLabel *pLabelName;
    QUtilsLayoutLine *pLineName;

    QLabel *pLabelStatus;
    QLabel *pLabelSwitch;
    QLabel *pLabelIMEI;
    QLabel *pLabelPower;

    QLabel *pLabelStatusValue;
    SwitchButton *pSwitchButton;
    QLabel *pLabelIMEIValue;
    QLabel *pLabelPowerValue;

    ShoeDeviceModel mDeviceModel;
};


class BMapControlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit BMapControlPanel(QWidget *parent = nullptr);

    void initLayout();
    void initConnection();

signals:

public slots:
    // 刷新设备列表(在线 电量)
    void flushDeviceList();
    void flushDeviceListResult();
    void updateDeviceList(const QList<ShoeDeviceModel> modelList);

    // 位置（只刷新订阅了的）
    void flushDevicePosition();
    void flushDevicePositionResult();

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private:
    QPushButton *buttonJS;
    QPushButton *buttonFlush;

    QVBoxLayout *vboxDevice;

    // 每个设备 一个小的控制界面
    QList<DeviceControlItem*> lControlItemList;

    // 定时刷新设备数据 （是否在线 电量 位置）
    QTimer *timerFetchDeviceData;
};

#endif // BMAPCONTROLPANEL_HPP
