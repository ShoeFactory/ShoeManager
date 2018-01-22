#ifndef QUTILSFRAMELESSFORM_HPP
#define QUTILSFRAMELESSFORM_HPP

#include "QUtilsFramelessDialog.hpp"
#include <QFormLayout>
#include <QLabel>


class QUtilsFramelessForm : public QUtilsFramelessDialog
{
public:
    QUtilsFramelessForm(QWidget *parent=nullptr);

    void initLayout();
    void initConnection();

    void showPrompt(QString prompt);
    void clearPrompt();

    void setFormLayout(QLayout *layout);

protected:
    bool eventFilter(QObject *object, QEvent *event);
    void installAutoPromptEvent();

private:
    QWidget *formWidget;
    QLabel *pLabelPrompt;
};

#endif // QUTILSFRAMELESSFORM_HPP
