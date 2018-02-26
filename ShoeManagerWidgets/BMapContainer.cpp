#include "BMapContainer.hpp"
#include <QHBoxLayout>
#include <QMessageBox>

BMapContainer::BMapContainer(QWidget *parent) : QWidget(parent)
{
    initLayout();
    initConnection();
}

void BMapContainer::initLayout()
{
    webPage = new QWebEnginePage;
    webView = new QWebEngineView;

    QWebChannel *channel = new QWebChannel(this);
    channel->registerObject(QStringLiteral("containerUI"), this);

    dataCenter  = BMapDataCenter::getInstance();
    channel->registerObject(QStringLiteral("dataCenter"), dataCenter);

    webPage->setWebChannel(channel);
    webView->setPage(webPage);

    QHBoxLayout *hboxMain = new QHBoxLayout;
    hboxMain->addWidget(webView);
    this->setLayout(hboxMain);

    webView->setContextMenuPolicy(Qt::NoContextMenu);
    webView->setUrl(QUrl("qrc:/websource/index.html"));
}

void BMapContainer::initConnection()
{
    connect(BMapDataCenter::getInstance(), &BMapDataCenter::sigAlert,
            this, &BMapContainer::slotAlert);
}

void BMapContainer::slotAlert()
{
    webPage->runJavaScript("showAlert()");
}

void BMapContainer::showMsgBox()
{
    QMessageBox::information(this, "GOOD", "callbackfromweb");
}
