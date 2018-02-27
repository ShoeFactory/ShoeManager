#ifndef ACCOUNTPASSWDWIDGET_HPP
#define ACCOUNTPASSWDWIDGET_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QStackedLayout>
class AccountPasswdWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AccountPasswdWidget(QWidget *parent = nullptr);

signals:

public slots:
    void buttonValidateClicked();
    void buttonUpdatePasswordClicked();

private:
    void initLayout();
    void initConnection();

private:
    QLabel *mLabelTelephone;
    QLabel *mLabelValidate;
    QLabel *mLabelPasswd;
    QLabel *mLabelPasswdConfirm;
    QLineEdit *mLineTelephone;
    QLineEdit *mlineValidate;
    QLineEdit *mLinePasswd;
    QLineEdit *mLinePasswdConfirm;

    QLabel *mLabelPrompt;
    QPushButton *mButtonValidate;
    QPushButton *mButtonPasswd;
};

#endif // ACCOUNTPASSWDWIDGET_HPP
