#ifndef ACCOUNTLOGINWIDGET_HPP
#define ACCOUNTLOGINWIDGET_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QStackedLayout>

class AccountLoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AccountLoginWidget(QWidget *parent = nullptr);

signals:
    void gotoPasswd();
    void gotoRegister();

    void loginSucceed();

public slots:
    void loginButtonClicked();

private:
    void initLayout();
    void initConnection();

private:
    QLabel *mLabelTelephone;
    QLabel *mLabelPasswd;
    QLineEdit *mLineTelephone;
    QLineEdit *mLinePasswd;

    QLabel *mLabelPrompt;
    QPushButton *mButtonLogin;
    QPushButton *mButtonRegister;
    QPushButton *mButtonPasswd;
};

#endif // ACCOUNTLOGINWIDGET_HPP
