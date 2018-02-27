#ifndef SHOEDEVICELISTMODEL_HPP
#define SHOEDEVICELISTMODEL_HPP

#include <QAbstractTableModel>
#include "ShoeDeviceModel.hpp"

class ShoeDeviceListModel : public QAbstractTableModel
{
public:
    enum Column{
        Column_name,
        Column_imei,
        Column_operate,
        Columns,
    };

public:
    ShoeDeviceListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    ShoeDeviceModel itemAtRow(int row);
    void setItemList(QList<ShoeDeviceModel> itemList);

private:
    QList<ShoeDeviceModel> mItemList;
};

#endif // SHOEDEVICELISTMODEL_HPP
