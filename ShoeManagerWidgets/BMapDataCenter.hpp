#ifndef BMAPDATACENTER_HPP
#define BMAPDATACENTER_HPP

#include <QObject>
#include <QMap>
#include <QPoint>

class BMapDataCenter : public QObject
{
    Q_OBJECT
public:

    static BMapDataCenter* getInstance();

signals:
    void sigAlert();

public slots:
    void slotAlert();

private:
    explicit BMapDataCenter(QObject *parent = nullptr);
    QMap<QString, QPoint> currentPositionMap;
    QMap<QString, QList<QPoint>> historyPositionMap;
};

#endif // BMAPDATACENTER_HPP
