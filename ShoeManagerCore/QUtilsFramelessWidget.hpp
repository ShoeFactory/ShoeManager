#ifndef QUTILSFRAMELESSWIDGET_HPP
#define QUTILSFRAMELESSWIDGET_HPP
#include "shoemanagercore_global.h"

#include <QWidget>
#include <QFrame>
#include <QWidget>
#include <QLabel>
#include <QPushButton>

class FramelessHelper;

class SHOEMANAGERCORESHARED_EXPORT QUtilsFramelessWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QUtilsFramelessWidget(QWidget *parent = nullptr);

    int getTitleHeight();
    void setTitleHight(int height);
    void setTitleText(QString text);
    void setTitleIcon(QIcon icon);

    void setTitleToolBarLayout(QLayout *layout);
    void setBodyLayout(QLayout *layout);

public:
    virtual void initLayout()=0;
    virtual void initConnection()=0;

private:
    QFrame *mMainFrame;
    QWidget *mTitle;
    QWidget *mBody;

    int mTitleHeight;
    QLabel *mTitleIcon;
    QLabel *mTitleText;
    QWidget *mTitleToolBar;
    QWidget *mTitleButtonBar;
    QPushButton *mTitleMin;
    QPushButton *mTitleMax;
    QPushButton *mTitleClose;

    FramelessHelper *pHelper;

};

#endif // QUTILSFRAMELESSWIDGET_HPP
