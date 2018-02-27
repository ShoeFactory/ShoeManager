#include "QUtilsFramLessMessageBox.hpp"
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "QUtilsFramelessDialog.hpp"

QUtilsFramLessMessageBox::QUtilsFramLessMessageBox(QObject *parent)
    : QObject(parent)
{

}

void QUtilsFramLessMessageBox::info(QString content, QString title)
{
    QUtilsFramelessDialog messageBox;
    messageBox.setTitleText(title);


    QHBoxLayout *hboxLabel = new QHBoxLayout;
    {
        QLabel *label = new QLabel(content);
        hboxLabel->addWidget(label);
    }

    QHBoxLayout *hboxButton = new QHBoxLayout;
    {
        QPushButton *button = new QPushButton("确认");
        hboxButton->addWidget(button);
        connect(button, &QPushButton::clicked, &messageBox, &QUtilsFramelessDialog::accept);
    }

    QVBoxLayout *vboxMain = new QVBoxLayout;
    {
        vboxMain->addLayout(hboxLabel, 100);
        vboxMain->addLayout(hboxButton, 1);
        messageBox.setBodyLayout(vboxMain);
    }

    messageBox.exec();
}

bool QUtilsFramLessMessageBox::confirm(QString content, QString title)
{
    return true;
}
