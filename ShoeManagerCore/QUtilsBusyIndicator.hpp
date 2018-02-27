#ifndef BUSYINDICATOR_H
#define BUSYINDICATOR_H

#include <QTimer>
#include <QWidget>
#include <QEvent>
#include "shoemanagercore_global.h"

class SHOEMANAGERCORESHARED_EXPORT QUtilsBusyIndicator : public QWidget
{
    Q_OBJECT

public:
    enum IndicatorStyle{StyleRect, StyleEllipse, StyleArc};

public:
    void busyable(QWidget *slave);
    void startBusy();
    void stopBusy();

    void setIndicatorStyle(IndicatorStyle);
    void setColor(QColor color);
    void setBackgroundColor(QColor color);
    void setOpacity(qreal opacity);

protected:
    bool eventFilter(QObject *watched, QEvent *event);


public:
    explicit QUtilsBusyIndicator();

    void paintEvent(QPaintEvent *);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    IndicatorStyle indicatorStyle() const;

signals:

private slots:
    void rotate();

private:
    QPixmap generatePixmap(int sideLength);
    void drawRectStyle(QPainter *painter);
    void drawEllipseStyle(QPainter *painter);
    void drawArcStyle(QPainter *painter);

    QTimer timer;
    int startAngle;

    IndicatorStyle m_style;

    QColor fillColor;
    QColor backgroundColor;
    qreal  backgroundOpacity;

private:
    QWidget *mSlave;
};

#endif // BUSYINDICATOR_H
