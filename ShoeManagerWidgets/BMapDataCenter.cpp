#include "BMapDataCenter.hpp"

BMapDataCenter *BMapDataCenter::getInstance()
{
    static BMapDataCenter oInstance;
    return &oInstance;
}

void BMapDataCenter::slotAlert()
{
    emit sigAlert();
}

BMapDataCenter::BMapDataCenter(QObject *parent) : QObject(parent)
{

}

QString BMapDataCenter::getMarkers() const
{
    return m_markers;
}

void BMapDataCenter::setMarkers(const QString &markers)
{
    if(markers == m_markers)
        return;

    m_markers = markers;
    emit markerChanged(m_markers);
}
