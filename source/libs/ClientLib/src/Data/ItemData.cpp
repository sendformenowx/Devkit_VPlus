#include "ItemData.h"

const CItemData::SData &CItemData::GetData() const {
    return mData;
}

bool CItemData::SData::IsGlobalMessageScroll() const {
    return m_typeId.Is(TypeIdRegistry::ITEM_ETC_SCROLL_GLOBALCHATTING);
}

bool CItemData::SData::IsReverseScroll() const {
    return m_typeId.Is(TypeIdRegistry::ITEM_ETC_REVERSE_SCROLL);
}
