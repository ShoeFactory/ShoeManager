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
