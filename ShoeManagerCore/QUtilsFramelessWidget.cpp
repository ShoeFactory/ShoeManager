#include "QUtilsFramelessWidget.hpp"
#include "QUtilsFramelessHelper.hpp"
#include "IconFont.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>

QUtilsFramelessWidget::QUtilsFramelessWidget(QWidget *parent)
    : QWidget(parent)
{
    // 标题栏
    mTitle = new QWidget;
    {
        QHBoxLayout *hboxHeader = new QHBoxLayout(mTitle);
        hboxHeader->setMargin(0);
        hboxHeader->setSpacing(0);

        mTitleIcon = new QLabel;
        mTitleText = new QLabel;
        mTitleText->setStyleSheet("QLabel { background-color : transparent; color : white; }");
        mTitleToolBar = new QWidget;

        mTitleButtonBar = new QWidget;
        {
            QHBoxLayout *hboxTittleButtonBar = new QHBoxLayout(mTitleButtonBar);
            hboxTittleButtonBar->setMargin(2);
            hboxTittleButtonBar->setSpacing(0);

            mTitleMin = new QPushButton(QString(QChar(IconFont::HideIcon)));
            mTitleMax = new QPushButton(QString(QChar(IconFont::MaximizeIcon)));
            mTitleClose = new QPushButton(QString(QChar(IconFont::CloseIcon)));
            connect(mTitleMin, &QPushButton::clicked, this, &QUtilsFramelessWidget::showMinimized);
            connect(mTitleMax, &QPushButton::clicked, [=]{
                if(isMaximized())
                    showNormal();
                else
                    showMaximized();
            });
            connect(mTitleClose, &QPushButton::clicked, this, &QUtilsFramelessWidget::close);

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
        hboxHeader->addWidget(mTitleToolBar, 1);
        hboxHeader->addWidget(mTitleButtonBar);
    }

    // 主体
    mBody = new QWidget;
    {

    }

    // 边界
    mMainFrame = new QFrame;
    {
        QVBoxLayout *vboxMainFrame = new QVBoxLayout(mMainFrame);
        vboxMainFrame->setMargin(0);
        vboxMainFrame->setSpacing(0);
        vboxMainFrame->addWidget(mTitle);
        vboxMainFrame->addWidget(mBody);
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
    mTitle->setObjectName("FramelessDialog_Title");
    mTitle->setStyleSheet("QWidget#FramelessDialog_Title{"
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

int QUtilsFramelessWidget::getTitleHeight()
{
    return mTitleHeight;
}

void QUtilsFramelessWidget::setTitleHight(int height)
{
    mTitleHeight = height;
    mTitle->setFixedHeight(mTitleHeight);
    pHelper->setTitleHeight(mTitleHeight);
}

void QUtilsFramelessWidget::setTitleText(QString text)
{
    mTitleText->setText(text);
}

void QUtilsFramelessWidget::setTitleToolBarLayout(QLayout *layout)
{
    Q_ASSERT(layout);
    mTitleToolBar->setLayout(layout);
}

void QUtilsFramelessWidget::setBodyLayout(QLayout *layout)
{
    Q_ASSERT(layout);
    mBody->setLayout(layout);
}
