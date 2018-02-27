#include "QUtilsFramelessForm.hpp"
#include <QEvent>

QUtilsFramelessForm::QUtilsFramelessForm(QWidget *parent)
    : QUtilsFramelessDialog(parent)
{
    initLayout();
    initConnection();
}

void QUtilsFramelessForm::initLayout()
{
    formWidget = new QWidget;
    {

    }

    QHBoxLayout *hboxPrompt = new QHBoxLayout;
    {
        pLabelPrompt = new QLabel;
        hboxPrompt->addWidget(pLabelPrompt);
    }

    QVBoxLayout *vbox = new QVBoxLayout;
    {
        vbox->addWidget(formWidget);
        vbox->addLayout(hboxPrompt);

        setBodyLayout(vbox);
        setFooterVisible(true);
    }
}

void QUtilsFramelessForm::initConnection()
{
    connect(pButtonCancle, &QPushButton::clicked, this, &QUtilsFramelessForm::reject);
}

void QUtilsFramelessForm::showPrompt(QString prompt)
{
    pLabelPrompt->setText(prompt);
}

void QUtilsFramelessForm::clearPrompt()
{
    pLabelPrompt->clear();
}

void QUtilsFramelessForm::setFormLayout(QLayout *layout)
{
    formWidget->setLayout(layout);
    installAutoPromptEvent();
}

void QUtilsFramelessForm::installAutoPromptEvent()
{
    QList<QObject*> childs = formWidget->children();
    foreach (auto *child, childs) {
        if(child->isWidgetType())
        {
            child->installEventFilter(this);
        }
    }
}

bool QUtilsFramelessForm::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QEvent::FocusIn)
    {
        clearPrompt();
    }
    return QObject::eventFilter(object, event);
}
