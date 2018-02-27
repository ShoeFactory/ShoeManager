#ifndef BMAPCONTAINER_HPP
#define BMAPCONTAINER_HPP

#include <QWidget>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebChannel>
#include "BMapDataCenter.hpp"

class BMapContainer : public QWidget
{
    Q_OBJECT
public:
    explicit BMapContainer(QWidget *parent = nullptr);

    void initLayout();
    void initConnection();

signals:

private:
    QWebEngineView *webView;
    QWebEnginePage *webPage;

    BMapDataCenter *dataCenter;
};

#endif // BMAPCONTAINER_HPP
