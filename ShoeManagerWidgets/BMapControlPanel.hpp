#ifndef BMAPCONTROLPANEL_HPP
#define BMAPCONTROLPANEL_HPP

#include <QWidget>
#include <QPushButton>
#include "BMapDataCenter.hpp"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMap>

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

    void setDeviceModel(const ShoeDeviceModel * const deviceModel);

signals:
    void switchButtonChecked(QString imei, bool checked);

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
};


class BMapControlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit BMapControlPanel(QWidget *parent = nullptr);

    void initLayout();
    void initConnection();

signals:

public:
    enum PositionType{
        PositionType_All = 0,
        PositionType_GPS,
        PositionType_LBS,
    };
private:
    PositionType currentType = PositionType_GPS;

public slots:
    // 刷新设备列表
    void flushDeviceList();
    void flushDeviceListResult();

    // 订阅设备
    void subscribeDevice(QString imei, bool checked);
    void subscribeDeviceResult();

    // 刷新设备状态（电量 是否在线 是否订阅）
    void flushDeviceStatus(QStringList IMEIs);
    void flushDeviceStatusResult();

    // 位置（只刷新订阅了 分级别）
    void flushDevicePosition(QStringList IMEIs, PositionType type = PositionType_GPS);
    void flushDevicePositionResult();

protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);

private:
    QPushButton *btnflushDeviceList;// 刷新设备列表
    QTimer *timerFetchDeviceData;   // 刷新设备数据

private:
    QMap<QString, ShoeDeviceModel*> m_CurrentDeviceModelMap;
    QMap<QString, DeviceControlItem*> m_CurrentDeviceViewMap;
    QVBoxLayout *vboxDevice;

};

#endif // BMAPCONTROLPANEL_HPP
