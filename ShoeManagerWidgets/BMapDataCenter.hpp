#ifndef BMAPDATACENTER_HPP
#define BMAPDATACENTER_HPP

#include <QObject>
#include <QMap>
#include <QPoint>

class BMapDataCenter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString m_markers READ getMarkers WRITE setMarkers NOTIFY markersChanged)

public:

    static BMapDataCenter* getInstance();

    QString getMarkers() const;
    void setMarkers(const QString &markers);

signals:
    void markersChanged(QString markers);

private:
    explicit BMapDataCenter(QObject *parent = nullptr);

    /// 要绘制的实时点（json）
    QString m_markers;
};

#endif // BMAPDATACENTER_HPP
