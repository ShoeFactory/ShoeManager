#ifndef QUTILSBETTERTABLEVIEW_HPP
#define QUTILSBETTERTABLEVIEW_HPP

#include <QTableView>
#include <QStyledItemDelegate>
#include "shoemanagercore_global.h"


class SHOEMANAGERCORESHARED_EXPORT QUtilsBetterTableDelegate : public QStyledItemDelegate
{
public:
    QUtilsBetterTableDelegate(QObject *parent = 0);

protected:
    void paint( QPainter *painter,
                const QStyleOptionViewItem &option,
                const QModelIndex &index ) const;
};

class SHOEMANAGERCORESHARED_EXPORT QUtilsBetterTableView : public QTableView
{
public:
    QUtilsBetterTableView(QWidget *parent=nullptr);

    void setColumnInteractive(bool interactive = false);
};

#endif // QUTILSBETTERTABLEVIEW_HPP
