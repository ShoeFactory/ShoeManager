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
    void flushDeviceList();
    void flushDeviceListResult();

    void updateData(const QList<ShoeDeviceModel> modelList);

protected:
    void showEvent(QShowEvent *event);

private:
    QPushButton *buttonJS;
    QPushButton *buttonFlush;

    QVBoxLayout *vboxDevice;
    QList<DeviceControlItem*> lControlItemList;
};

#endif // BMAPCONTROLPANEL_HPP
