#include "SOItem.h"
#include "GlobalDataManager.h"


const CItemData::SData *CSOItem::GetItemData() const {
    const CItemData::SData *data = NULL;

    if (m_refObjItemId != 0) {
        data = &g_CGlobalDataManager->GetItemData(m_refObjItemId);
    }

    return data;
}

int CSOItem::GetQuantity() const {
    return m_quantity;
}


ObjectData* CSOItem::GetObjectData(void)
{
    return reinterpret_cast<ObjectData*(__thiscall*)(CSOItem*)>(0x008BA440)(this);
}
