#include "QUtilsFramelessDialog.hpp"
#include "QUtilsFramelessHelper.hpp"
#include "IconFont.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>

QUtilsFramelessDialog::QUtilsFramelessDialog(QWidget *parent)
    : QDialog(parent)
{
    // 标题栏
    mHeader = new QWidget;
    {
        QHBoxLayout *hboxHeader = new QHBoxLayout(mHeader);
        hboxHeader->setMargin(0);
        hboxHeader->setSpacing(0);

        mTitleIcon = new QLabel;
        mTitleText = new QLabel;
        mTitleToolBar = new QWidget;

        mTitleButtonBar = new QWidget;
        {
            QHBoxLayout *hboxTittleButtonBar = new QHBoxLayout(mTitleButtonBar);
            hboxTittleButtonBar->setMargin(2);
            hboxTittleButtonBar->setSpacing(0);

            mTitleMin = new QPushButton(QString(QChar(IconFont::HideIcon)));
            mTitleMax = new QPushButton(QString(QChar(IconFont::MaximizeIcon)));
            mTitleClose = new QPushButton(QString(QChar(IconFont::CloseIcon)));
            mTitleMin->setVisible(false);
            mTitleMax->setVisible(false);
            connect(mTitleMin, &QPushButton::clicked, this, &QUtilsFramelessDialog::showMinimized);
            connect(mTitleMax, &QPushButton::clicked, [=]{
                if(isMaximized())
                    showNormal();
                else
                    showMaximized();
            });
            connect(mTitleClose, &QPushButton::clicked, this, &QUtilsFramelessDialog::reject);

            auto oFont = IconFont::getInstance()->font();

            auto buttonList  = {mTitleMin, mTitleMax, mTitleClose};
            for(QPushButton *button : buttonList)
            {
                button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
                button->setFont(oFont);
                button->setFocusPolicy(Qt::NoFocus);
                button->setFixedWidth(23);
                button->setStyleSheet("QPushButton{"
                                      "color : white;"
                                      "border: 0px;"
                                      "}"
                                      "QPushButton:hover{"
                                      "background-color: rgb(255, 0, 0)"
                                      "}");
                hboxTittleButtonBar->addWidget(button);
            }
        }

        hboxHeader->addWidget(mTitleIcon);
        hboxHeader->addWidget(mTitleText);
        hboxHeader->addWidget(mTitleToolBar);
        hboxHeader->addStretch(1);
        hboxHeader->addWidget(mTitleButtonBar);
    }

    // 主体
    mBody = new QWidget;
    {

    }

    // 底部
    mFooter = new QWidget;
    {
        pButtonOK = new QPushButton("确认");
        pButtonCancle = new QPushButton("取消");

        QHBoxLayout *hboxFooter = new QHBoxLayout(mFooter);
        hboxFooter->addStretch(1);
        hboxFooter->addWidget(pButtonCancle);
        hboxFooter->addWidget(pButtonOK);
        hboxFooter->addStretch(1);
        mFooter->setVisible(false);
    }

    // 边界
    mMainFrame = new QFrame;
    {
        QVBoxLayout *vboxMainFrame = new QVBoxLayout(mMainFrame);
        vboxMainFrame->setMargin(0);
        vboxMainFrame->setSpacing(0);
        vboxMainFrame->addWidget(mHeader);
        vboxMainFrame->addWidget(mBody);
        vboxMainFrame->addWidget(mFooter);
    }

    // 主窗体
    QHBoxLayout *hboxMain = new QHBoxLayout;
    {
        hboxMain->addWidget(mMainFrame);
        hboxMain->setMargin(0);
        hboxMain->setSpacing(0);
        this->setLayout(hboxMain);
    }

    // 样式
    mHeader->setObjectName("FramelessDialog_Title");
    mHeader->setStyleSheet("QWidget#FramelessDialog_Title{"
                          "background-color: #343434;"
                          "}");

    mBody->setObjectName("FramelessDialog_Body");
    mBody->setStyleSheet("QWidget#FramelessDialog_Body{"
                          "background-color: white;"
                          "}");

    mMainFrame->setObjectName("FramelessDialog_MainFrame");
    mMainFrame->setStyleSheet("QFrame#FramelessDialog_MainFrame{"
                              "border: 1px solid #343434;"
                              "}");

    // 无边框处理
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    pHelper = new FramelessHelper(this);
    pHelper->activateOn(this);              //激活当前窗体
    pHelper->setWidgetMovable(true);        //设置窗体可移动
    pHelper->setWidgetResizable(true);      //设置窗体可缩放
    pHelper->setRubberBandOnMove(true);     //设置橡皮筋效果-可移动
    pHelper->setRubberBandOnResize(true);   //设置橡皮筋效果-可缩放
    setTitleHight(28);                      //设置窗体的标题栏高度

    // 鼠标边界处理
    pHelper->setBorderWidth(3);
}

int QUtilsFramelessDialog::getTitleHeight()
{
    return mTitleHeight;
}

void QUtilsFramelessDialog::setTitleHight(int height)
{
    mTitleHeight = height;
    mHeader->setFixedHeight(mTitleHeight);
    pHelper->setTitleHeight(mTitleHeight);
}

void QUtilsFramelessDialog::setTitleText(QString text)
{
    mTitleText->setText(text);
}

void QUtilsFramelessDialog::setTitleToolBarLayout(QLayout *layout)
{
    Q_ASSERT(layout);
    mTitleToolBar->setLayout(layout);
}

void QUtilsFramelessDialog::setBodyLayout(QLayout *layout)
{
    Q_ASSERT(layout);
    mBody->setLayout(layout);
}

void QUtilsFramelessDialog::setFooterVisible(bool visible)
{
    mFooter->setVisible(visible);
}
