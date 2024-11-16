#pragma once

#include "IFWnd.h"
#include "IFStoreForPackage.h"
#include "IFStorageRoom.h"
#include "SOItem.h"

class CIFInventory : public CIFWnd
{
public:
    CSOItem* GetItemBySlot(int SlotIndex);

    void ShowGWnd(bool bVisible);
public:
    CIFStoreForPackage* m_storeWindow; //0x036C 
    CIFStorageRoom* m_storageWindow; //0x0370 
    char pad_0x0374[0xC]; //0x0374
    __int32 N00000183; //0x0380 
    char pad_0x0384[0x4]; //0x0384
    CIFStatic* m_goldAmtText; //0x0388 
    char pad_0x038C[0xC]; //0x038C
    CIFButton* m_moneyDropButton; //0x0398 
    char pad_039C[20]; //0x039C
    unsigned int pSlots; //0x03B0
    char pad_03B4[60]; //0x03B4
    int GetRemainingSlot();
    int GetFirstEmptySlot();
};