#include "ShoeDeviceListModel.hpp"

ShoeDeviceListModel::ShoeDeviceListModel(QObject *parent)
    :QAbstractTableModel(parent)
{

}

int ShoeDeviceListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return mItemList.count();
}

int ShoeDeviceListModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return Columns;
}

QVariant ShoeDeviceListModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        auto &item = mItemList[index.row()];
        QString result;
        switch (index.column()) {
        case Column_name:
            result = item.name;
            break;
        case Column_imei:
            result = item.imei;
            break;
        default:
            break;
        }
        return result;
    }

    else if(role == Qt::UserRole)
    {
        if(index.column()==Column_operate)
        {
            return QString("删除|编辑");
        }
    }

    return QVariant();
}

QVariant ShoeDeviceListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role==Qt::DisplayRole)
    {
        QString result;
        switch (section) {
        case Column_name:
            result = QString("名称");
            break;
        case Column_imei:
            result = QString("定位器IMEI");
            break;
        case Column_operate:
            result = QString("操作");
            break;
        default:
            break;
        }
        return result;
    }

    return QVariant();
}

ShoeDeviceModel ShoeDeviceListModel::itemAtRow(int row)
{
    return mItemList.value(row);
}

void ShoeDeviceListModel::setItemList(QList<ShoeDeviceModel> itemList)
{
    beginResetModel();
    mItemList = itemList;
    endResetModel();
}
