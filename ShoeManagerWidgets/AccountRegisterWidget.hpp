#ifndef ACCOUNTREGISTERWIDGET_HPP
#define ACCOUNTREGISTERWIDGET_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QStackedLayout>
class AccountRegisterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AccountRegisterWidget(QWidget *parent = nullptr);

signals:

public slots:
    void registerValidateClicked();
    void registerClicked();

private:
    void initLayout();
    void initConnection();

private:
    QLabel *mLabelTelephone;
    QLabel *mLabelValidate;
    QLabel *mLabelPasswd;
    QLabel *mLabelPasswdConfirm;
    QLabel *mLabelName;
    QLineEdit *mLineTelephone;
    QLineEdit *mlineValidate;
    QLineEdit *mLinePasswd;
    QLineEdit *mLinePasswdConfirm;
    QLineEdit *mLineName;

    QLabel *mLabelPrompt;
    QPushButton *mButtonValidate;
    QPushButton *mButtonRegister;
};

#endif // ACCOUNTREGISTERWIDGET_HPP
