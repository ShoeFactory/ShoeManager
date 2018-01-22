#include "QUtilsBusyIndicator.hpp"

#include <QDebug>
#include <QPainter>
#include <QPixmapCache>
#include <QGradient>

void QUtilsBusyIndicator::busyable(QWidget *slave)
{
    mSlave = slave;
    slave->installEventFilter(this);
    this->setParent(mSlave);
    this->hide();
}

void QUtilsBusyIndicator::startBusy()
{
    this->setGeometry(0, 0, mSlave->width(), mSlave->height());
    this->raise();
    this->show();
}

void QUtilsBusyIndicator::stopBusy()
{
    this->hide();
}

QUtilsBusyIndicator::QUtilsBusyIndicator() :
    startAngle(0),
    m_style(StyleEllipse),
    backgroundColor(QColor(Qt::gray)),
    backgroundOpacity(0.3)
{
    QSizePolicy policy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    policy.setHeightForWidth(true);
    setSizePolicy(policy);

    fillColor = palette().color(QPalette::WindowText);

    timer.setInterval(50);
    connect(&timer, SIGNAL(timeout()), this, SLOT(rotate()));
    timer.start();

    this->hide();
}

void QUtilsBusyIndicator::rotate()
{
    startAngle += 30;
    startAngle %= 360;
    update();
}

void QUtilsBusyIndicator::setIndicatorStyle(IndicatorStyle style)
{
    m_style = style;
    update();
}

void QUtilsBusyIndicator::setColor(QColor color)
{
    fillColor = color;
}

void QUtilsBusyIndicator::setBackgroundColor(QColor color)
{
    backgroundColor = color;
}

void QUtilsBusyIndicator::setOpacity(qreal opacity)
{
    backgroundOpacity = opacity;
}

bool QUtilsBusyIndicator::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == mSlave && event->type() == QEvent::Resize)
    {
        this->setGeometry(0, 0, mSlave->width(), mSlave->height());
    }

    return QWidget::eventFilter(watched, event);
}

QUtilsBusyIndicator::IndicatorStyle QUtilsBusyIndicator::indicatorStyle() const
{
    return m_style;
}


QPixmap QUtilsBusyIndicator::generatePixmap(int side)
{
    QPixmap pixmap(QSize(side, side));
    pixmap.fill(QColor(255, 255, 255, 0));

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.translate(side / 2, side / 2);
    painter.scale(side / 1600.0, side / 1600.0);

    switch (m_style) {
    case StyleRect:
        drawRectStyle(&painter);
        break;
    case StyleEllipse:
        drawEllipseStyle(&painter);
        break;
    case StyleArc:
        drawArcStyle(&painter);
        break;
    }
    return pixmap;
}

void QUtilsBusyIndicator::drawRectStyle(QPainter *painter)
{
    //    QColor color = palette().color(QPalette::WindowText);
    QColor color = fillColor;
    QBrush brush(color);
    painter->setPen(Qt::NoPen);

    painter->rotate(startAngle);

    float angle = 0;
    while (angle < 360) {
        painter->setBrush(brush);
        painter->drawRect(-8, -100, 16, 35);

        painter->rotate(30);
        angle += 30;

        color.setAlphaF(angle / 360);
        brush.setColor(color);
    }
}

void QUtilsBusyIndicator::drawEllipseStyle(QPainter *painter)
{
    //    QColor color = palette().color(QPalette::WindowText);
    QColor color = fillColor;
    QBrush brush(color);
    painter->setPen(Qt::NoPen);

    painter->rotate(startAngle);

    float angle = 0;
    while (angle < 360) {
        painter->setBrush(brush);
        painter->drawEllipse(-10, -100, 30, 30);

        painter->rotate(30);
        angle += 30;

        color.setAlphaF(angle / 360);
        brush.setColor(color);
    }
}

void QUtilsBusyIndicator::drawArcStyle(QPainter *painter)
{
    //    QColor color = palette().color(QPalette::WindowText);
    QColor color = fillColor;
    QConicalGradient gradient(0, 0, -startAngle);
    gradient.setColorAt(0, color);
    color.setAlpha(0);
    gradient.setColorAt(0.8, color);
    color.setAlpha(255);
    gradient.setColorAt(1, color);

    QPen pen;
    pen.setWidth(30);
    pen.setBrush(QBrush(gradient));
    painter->setPen(pen);

    painter->drawArc(-85, -85, 170, 170, 0 * 16, 360 * 16);
}

void QUtilsBusyIndicator::paintEvent(QPaintEvent *)
{
    QString key = QString("%1:%2:%3:%4:%5")
            .arg(metaObject()->className())
            .arg(width())
            .arg(height())
            .arg(startAngle)
            .arg(m_style);

    QPixmap pixmap;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.save();
    painter.setOpacity(backgroundOpacity);
    painter.setBrush(backgroundColor);
    painter.drawRect(rect());
    painter.restore();


    int side = qMin(width(), height());

    if(!QPixmapCache::find(key, &pixmap)) {
        pixmap = generatePixmap(side);
        QPixmapCache::insert(key, pixmap);
    }

    painter.translate(width() / 2 - side / 2, height() / 2 - side / 2);

    painter.drawPixmap(0, 0, side, side, pixmap);
}

QSize QUtilsBusyIndicator::minimumSizeHint() const
{
    return QSize(20, 20);
}

QSize QUtilsBusyIndicator::sizeHint() const
{
    return QSize(30, 30);
}
