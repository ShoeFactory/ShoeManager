#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "shoemanagerwidgets_global.h"
#include "QUtilsFramelessWidget.hpp"

#include <QWidget>
#include "BMapControlPanel.hpp"
#include "BMapContainer.hpp"

class SHOEMANAGERWIDGETSSHARED_EXPORT MainWidget : public QUtilsFramelessWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

    void initLayout();
    void initConnection();

protected:
    void showEvent(QShowEvent *event);

private slots:
    void getUserProfile();
    void parseUserProfile();

    void profileManageButtonClicked();
    void devicesManageButtonClicked();

private:
    BMapControlPanel *mControlPanel;
    BMapContainer *mMapContainter;

    QPushButton *mButtonUserProfile;
    QAction *mActionProfileManage;
    QAction *mActionDevicesManage;
};

#endif // MAINWIDGET_H
