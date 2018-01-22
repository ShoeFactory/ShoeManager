#include "QUtilsBetterTableView.hpp"
#include <QHeaderView>

QUtilsBetterTableView::QUtilsBetterTableView(QWidget *parent)
    : QTableView(parent)
{
    setShowGrid(false);
    verticalHeader()->setVisible(false);
    horizontalHeader()->setHighlightSections(false);

    setSelectionMode(QTableView::SingleSelection);
    setSelectionBehavior(QTableView::SelectRows);

    setItemDelegate(new QUtilsBetterTableDelegate);
}

void QUtilsBetterTableView::setColumnInteractive(bool interactive)
{
    if(interactive)
        horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    else
        horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

QUtilsBetterTableDelegate::QUtilsBetterTableDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

void QUtilsBetterTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //去掉选中时item的虚线样式
    QStyleOptionViewItem itemOption(option);
    if (itemOption.state & QStyle::State_HasFocus)
    {
        itemOption.state = itemOption.state ^ QStyle::State_HasFocus;
    }

    if (itemOption.state & QStyle::State_Selected)
    {
        QVariant textColor = index.data(Qt::TextColorRole);
        if (textColor.canConvert<QColor>())
        {
            itemOption.palette.setColor(QPalette::HighlightedText, textColor.value<QColor>());
        }
    }

    QStyledItemDelegate::paint( painter, itemOption, index );
}
