#include "SettingProfileEditorUI.hpp"
#include "QUtilsFramLessMessageBox.hpp"
#include <QBoxLayout>
#include <QFormLayout>
#include <ShoeManagerNetwork.hpp>
#include <ShoeManagerNetworkResult.hpp>

SettingProfileEditorUI::SettingProfileEditorUI(QWidget *parent) : QWidget(parent)
{
    initLayout();
    initConnection();
}

void SettingProfileEditorUI::initLayout()
{
    QGroupBox *pGroupPasswd = new QGroupBox;
    {
        pLabelNewPasswd = new QLabel("新密码");
        pLabelNewPasswdConfirm = new QLabel("确认密码");
        pLineNewPasswd = new QLineEdit;
        pLineNewPasswdConfirm = new QLineEdit;
        pButtonUpdatePasswd = new QPushButton("提交");

        QVBoxLayout *vbox = new QVBoxLayout(pGroupPasswd);
        vbox->addWidget(pLabelNewPasswd);
        vbox->addWidget(pLineNewPasswd);
        vbox->addWidget(pLabelNewPasswdConfirm);
        vbox->addWidget(pLineNewPasswdConfirm);
        vbox->addWidget(pButtonUpdatePasswd);

        vbox->setMargin(0);
        pButtonUpdatePasswd->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    }

    QGroupBox *pGroupName = new QGroupBox;
    {
        pLabelNewName = new QLabel("新名称");
        pLineNewName = new QLineEdit;
        pButtonUpdateName = new QPushButton("提交");

        QVBoxLayout *vbox = new QVBoxLayout(pGroupName);
        vbox->addWidget(pLabelNewName);
        vbox->addWidget(pLineNewName);
        vbox->addWidget(pButtonUpdateName);

        vbox->setMargin(0);
        pButtonUpdateName->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    }

    QHBoxLayout *hboxMain = new QHBoxLayout;
    {
        QVBoxLayout *vbox = new QVBoxLayout;
        vbox->addWidget(pGroupPasswd);
        vbox->addWidget(pGroupName);
        vbox->addStretch(1);

        hboxMain->addLayout(vbox);
        hboxMain->addStretch(1);
        this->setLayout(hboxMain);

        vbox->setMargin(0);
        hboxMain->setMargin(0);
        hboxMain->setSpacing(0);
    }
}

void SettingProfileEditorUI::initConnection()
{
    connect(pButtonUpdatePasswd, &QPushButton::clicked, this, &SettingProfileEditorUI::updatePasswdClicked);
    connect(pButtonUpdateName, &QPushButton::clicked, this, &SettingProfileEditorUI::updateNameClicked);
}

void SettingProfileEditorUI::updatePasswdClicked()
{
    bool checkOK = true;
    do{
        if(pLineNewPasswd->text().trimmed().isEmpty())
        {
            QUtilsFramLessMessageBox::info("密码不能为空");
            checkOK = false;
            break;
        }
        if(pLineNewPasswd->text() != pLineNewPasswdConfirm->text())
        {
            QUtilsFramLessMessageBox::info("两次输入密码不一致");
            checkOK = false;
            break;
        }
    }while(false);

    if(checkOK == false)
        return;

    auto *result = ShoeManagerNetwork::getInstance()->passwdUpdate(pLineNewPasswd->text());
    if(result->oReturnCode == 0)
    {
        QUtilsFramLessMessageBox::info("密码修改成功");
    }
    else
    {
        QUtilsFramLessMessageBox::info(result->oReturnMessage);
    }
}

void SettingProfileEditorUI::updateNameClicked()
{
    bool checkOK = true;
    do{
        if(pLineNewName->text().trimmed().isEmpty())
        {
            QUtilsFramLessMessageBox::info("名称不能为空");
            checkOK = false;
            break;
        }
    }while(false);

    if(checkOK == false)
        return;

    auto *result = ShoeManagerNetwork::getInstance()->userProfileUpdate(pLineNewName->text());
    if(result->oReturnCode == 0)
    {
        QUtilsFramLessMessageBox::info("用户名修改成功");
    }
    else
    {
        QUtilsFramLessMessageBox::info(result->oReturnMessage);
    }
}
