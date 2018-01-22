#ifndef QUTILSFRAMLESSDIALOG_HPP
#define QUTILSFRAMLESSDIALOG_HPP

#include "shoemanagercore_global.h"

#include <QDialog>
#include <QFrame>
#include <QWidget>
#include <QLabel>
#include <QPushButton>

class FramelessHelper;

class SHOEMANAGERCORESHARED_EXPORT QUtilsFramelessDialog : public QDialog
{
    Q_OBJECT
public:
    QUtilsFramelessDialog(QWidget *parent=nullptr);

    int getTitleHeight();
    void setTitleHight(int height);
    void setTitleText(QString text);
    void setTitleIcon(QIcon icon);

    void setTitleToolBarLayout(QLayout *layout);
    void setBodyLayout(QLayout *layout);

    void setFooterVisible(bool visible);
    QPushButton *pButtonOK;
    QPushButton *pButtonCancle;

private:
    QFrame *mMainFrame;
    QWidget *mHeader;
    QWidget *mBody;
    QWidget *mFooter;

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

#endif // QUTILSFRAMLESSDIALOG_HPP
