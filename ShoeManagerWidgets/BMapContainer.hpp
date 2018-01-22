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

public slots:
    void slotAlert();
    void showMsgBox();

private:
    QWebEngineView *webView;
    QWebEnginePage *webPage;
};

#endif // BMAPCONTAINER_HPP
