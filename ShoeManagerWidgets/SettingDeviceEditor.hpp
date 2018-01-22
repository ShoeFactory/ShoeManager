#ifndef SETTINGDEVICEEDITOR_HPP
#define SETTINGDEVICEEDITOR_HPP

#include <QWidget>
#include <QTableView>
#include "ShoeDeviceListModel.hpp"
#include "QUtilsButtonsDelegate.hpp"
#include "QUtilsBetterTableView.hpp"

class SettingDeviceEditor : public QWidget
{
    Q_OBJECT
public:
    explicit SettingDeviceEditor(QWidget *parent = nullptr);

    void initLayout();
    void initConnection();

signals:

public slots:
    void flushDeviceList();
    void flushDeviceListResult();

    void addDeviceClicked();

    void removeDeviceClicked();
    void editDeviceClicked();

protected:
    void showEvent(QShowEvent *event);

private:
    ShoeDeviceListModel *pTableModel;
    QUtilsBetterTableView *pTableView;
    QUtilsButtonsDelegate *pTableDelegate;

    QPushButton *pButtonAdd;
    QPushButton *pButtonFlush;

    QAction *pButtonEdit;
    QAction *pButtonDelete;
};

#endif // SETTINGDEVICEEDITOR_HPP
