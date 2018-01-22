#include "QUtilsButtonsDelegate.hpp"
#include <QStyleOptionToolButton>
#include <QEvent>
#include <QMouseEvent>
#include <QTableView>

#include <QStyle>
#include <QDebug>
#include <QApplication>


QUtilsButtonsDelegate::QUtilsButtonsDelegate(QTableView *pTableView)
    :pTableView(pTableView), QStyledItemDelegate(pTableView)
{
    nMargin = 5;
    nSpacing = 5;
    connect(pTableView,SIGNAL(pressed(const QModelIndex &)),this,SLOT(slotPressed(const QModelIndex &)));
}

QUtilsButtonsDelegate::~QUtilsButtonsDelegate()
{

}

QAction* QUtilsButtonsDelegate::addButton(QString const& strObjectName,QIcon const& oIcon )
{
    QAction* action = new QAction(this);
    action->setText(strObjectName);
    QPushButton* button = new QPushButton();

    button->setStyleSheet("QPushButton {border: none; background-color: transparent; color:#4D84FF;} \
                                 QPushButton:hover {color:#FF1B1B;}");


    button->setIcon(oIcon);
    button->setObjectName(strObjectName);
    QPair<QPushButton*,QAction*> pair;
    pair.first = button;
    pair.second = action;
    plButtonAction.append(pair);
    return action;
}

 void QUtilsButtonsDelegate::setGroupColumn(int nColumn)
 {
     nGroupColumn = nColumn;
 }

void QUtilsButtonsDelegate::paint(QPainter *painter,const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    if(!index.isValid())
    {
        return ;
    }
    QStyleOptionViewItem viewOption(option);
    initStyleOption(&viewOption, index);
    if (option.state.testFlag(QStyle::State_HasFocus))
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;
    QStyledItemDelegate::paint(painter, viewOption, index);

    if(index.column() == nGroupColumn)
    {
        int nXOffset = option.rect.left() + nMargin;
        int nYOffset = option.rect.top() + nMargin ;//+ nSpacing;

        QVariant oData = index.model()->data(index,Qt::UserRole);
        QString strData = oData.toString();
        auto strButtonTexts = strData.split("|");
        if(strButtonTexts.size() != plButtonAction.size())
        {
            return;
        }
        for(int i=0; i< plButtonAction.size(); i++)
        {
            plButtonAction.at(i).first->setText(strButtonTexts.at(i));
        }

        QFont font = option.widget->font();
        QFontMetrics fontmetrics(font);

        for(int i=0; i<plButtonAction.size(); i++)
        {
            QStyleOptionButton pButton;
            QPushButton *pPushButton = plButtonAction.value(i).first;

            pPushButton->setFont(font);
            QString strText = pPushButton->text();
            if(strText.isEmpty())
            {
                continue;
            }
            int w = fontmetrics.boundingRect(strText).width();
            int h = fontmetrics.boundingRect(strText).height();
            pPushButton->setGeometry(nXOffset,nYOffset,w , h );
            pButton.rect = QRect(nXOffset,nYOffset,w,h);
            pButton.state |= QStyle::State_Enabled;
            pButton.text = pPushButton->text();

            if(pButton.rect.contains(oMousePoint))
            {
                pButton.state |= QStyle::State_MouseOver;
            }

            QApplication::style()->drawControl(QStyle::CE_PushButton, &pButton, painter, pPushButton);
            nXOffset += pPushButton->width() + nSpacing;
        }
    }
}

QSize QUtilsButtonsDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int nWidth = (plButtonAction.size() - 1) * nSpacing + 2 * nMargin;
    int nHeight = 2 * nMargin;
    int nMaxHeight = 0;

    for(int i=0; i<plButtonAction.size(); i++)
    {
        QPushButton *pPushButton = plButtonAction.value(i).first;

        nWidth += pPushButton->width();
        if(nMaxHeight < pPushButton->height())
        {
            nMaxHeight = pPushButton->height();
        }

    }

    nHeight += nMaxHeight;
    return QSize(nWidth,nHeight);
}

void QUtilsButtonsDelegate::slotPressed(const QModelIndex &rIndex)
{
    if(rIndex.column() == nGroupColumn)
    {
        auto oItemRect = pTableView->visualRect(rIndex);
        int nXOffset = oItemRect.left() + nMargin;
        int nYOffset = oItemRect.top() + nMargin;// + nSpacing;

        QFont font = pTableView->font();
        QFontMetrics fontmetrics(font);

        for(int i=0; i<plButtonAction.size(); i++)
        {
            QPushButton *pPushButton = plButtonAction.value(i).first;

            QString strText = pPushButton->text();
            if(strText.isEmpty())
            {
                continue;
            }
            int w = fontmetrics.boundingRect(strText).width();
            int h = fontmetrics.boundingRect(strText).height();
            auto oRect = QRect(nXOffset,nYOffset,w ,h );
            if (oRect.contains(oMousePoint))
            {
                plButtonAction.value(i).second->trigger();
                break;
            }
            nXOffset += pPushButton->width() + nSpacing;
        }
    }
}

bool QUtilsButtonsDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    QApplication::restoreOverrideCursor();
    bool bRet = QStyledItemDelegate::editorEvent(event,model,option,index);
    if(index.column() == nGroupColumn)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        switch (event->type())
        {
        case QEvent::MouseButtonDblClick:
            break;
        case QEvent::MouseButtonPress:
        {

        }
            break;
        case QEvent::MouseButtonRelease:
            break;
        case QEvent::MouseMove:
        {
            int nXOffset = option.rect.left() + nMargin;
            int nYOffset = option.rect.top() + nMargin; //  + nSpacing;

            QFont font = option.widget->font();
            QFontMetrics fontmetrics(font);

            for(int i=0; i<plButtonAction.size(); i++)
            {
                QPushButton *pPushButton = plButtonAction.value(i).first;
                int w = fontmetrics.boundingRect(pPushButton->text()).width();
                int h = fontmetrics.boundingRect(pPushButton->text()).height();
                auto oRect = QRect(nXOffset,nYOffset,w ,h );
                auto oPos = mouseEvent->pos();
                if (oRect.contains(oPos))
                {
                    bRet = true;
                    QApplication::setOverrideCursor(Qt::PointingHandCursor);
                }
                oMousePoint = oPos;
                nXOffset += pPushButton->width() + nSpacing;
            }
        }
            break;
        default:
            break;
        }
    }
    return bRet;
}
