#ifndef SETTINGDEVICEADDDIALOG_HPP
#define SETTINGDEVICEADDDIALOG_HPP

#include "QUtilsFramelessForm.hpp"
#include <QLabel>
#include <QLineEdit>

class SettingDeviceAddDialog : public QUtilsFramelessForm
{
    Q_OBJECT

public:
    SettingDeviceAddDialog(QWidget *widget=nullptr);

    void initLayout();
    void initConnection();

private slots:
    void addDevice();

private:
    QLabel *pLableName;
    QLabel *pLabelIMEI;
    QLineEdit *pLineName;
    QLineEdit *pLineIMEI;
};

#endif // SETTINGDEVICEADDDIALOG_HPP
