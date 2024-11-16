#include "IFInventory.h"
#include <ICPlayer.h>

CSOItem *CIFInventory::GetItemBySlot(int slotId) {
    return reinterpret_cast<CSOItem *(__thiscall *)(CIFInventory *, int)>(0x6b3e50)(this, slotId);
}

int CIFInventory::GetRemainingSlot()
{
    return reinterpret_cast<int(__thiscall*)(CIFInventory*)>(0x006B6230)(this);
}
int CIFInventory::GetFirstEmptySlot() // + 13 giving first empty slot id
{
    return reinterpret_cast<int(__thiscall*)(CIFInventory*)>(0x006b6280)(this);
}

//006b6130 ???
//


