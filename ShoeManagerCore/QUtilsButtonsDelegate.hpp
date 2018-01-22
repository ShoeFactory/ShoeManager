#ifndef QUANTBUTTONGROUPITEMDELEGATE_HPP
#define QUANTBUTTONGROUPITEMDELEGATE_HPP

#include <QObject>
#include <QAction>
#include <QStyledItemDelegate>
#include <QMap>
#include <QPushButton>
#include <QPoint>
#include <QPair>
#include <QList>
#include <QTableView>

#include "shoemanagercore_global.h"

class SHOEMANAGERCORESHARED_EXPORT QUtilsButtonsDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:

    explicit QUtilsButtonsDelegate(QTableView *pTableView);

    ~QUtilsButtonsDelegate();

public:

    QAction* addButton(QString const& strObjectName,QIcon const& oIcon = QIcon());

public:

    void setMargin(int nMargin);

    void setSpacing(int nSpacing);

public:

    void setGroupColumn(int nColumn);

public:

    void paint(QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index) const ;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const ;

    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

public slots:

    void slotPressed(const QModelIndex &rIndex);

private:

    QTableView *pTableView;
    QPoint m_mousePoint;

    int nMargin = 2;
    int nSpacing = 2;
    QPoint oMousePoint;

    QList<QPair<QPushButton*,QAction*>> plButtonAction;
    int nGroupColumn;

};

#endif // QUANTBUTTONGROUPITEMDELEGATE_HPP
