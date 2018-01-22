#include "SettingDeviceAddDialog.hpp"
#include <QFormLayout>
#include "ShoeManagerNetwork.hpp"
#include "ShoeManagerNetworkResult.hpp"
#include "QUtilsFramLessMessageBox.hpp"

SettingDeviceAddDialog::SettingDeviceAddDialog(QWidget *widget)
    : QUtilsFramelessForm(widget)
{
    initLayout();
    initConnection();
}

void SettingDeviceAddDialog::initLayout()
{
    QFormLayout *form = new QFormLayout;
    {
        pLableName = new QLabel("名称");
        pLabelIMEI = new QLabel("IMEI");
        pLineName = new QLineEdit;
        pLineIMEI = new QLineEdit;

        form->addRow(pLableName, pLineName);
        form->addRow(pLabelIMEI, pLineIMEI);

        setFormLayout(form);
        setTitleText("添加设备");
    }
}

void SettingDeviceAddDialog::initConnection()
{
    connect(pButtonOK, &QPushButton::clicked, this, &SettingDeviceAddDialog::addDevice);
}

void SettingDeviceAddDialog::addDevice()
{
    bool checkOK = true;
    do{
        if(pLineName->text().trimmed().isEmpty())
        {
            showPrompt("名称不能为空");
            checkOK = false;
            break;
        }

        if(pLineIMEI->text().length() != 15)
        {
            showPrompt("IMEI不正确");
            checkOK = false;
            break;
        }

    }while(false);

    if(checkOK == false)
        return;

    auto *result = ShoeManagerNetwork::getInstance()->bindDevice(pLineName->text(), pLineIMEI->text());
    if(result->oReturnCode == 0)
    {
        this->accept();
    }
    else
    {
        showPrompt(result->oReturnMessage);
    }
}
