#pragma once
#include "SOItem.h"
#include "IFWnd.h"

class CIFSlotWithHelp : public CIFWnd
{
    GFX_DECLARE_DYNAMIC_EXISTING(CIFSlotWithHelp, 0x00ee9B18)

public:
    void AppendAdvancedInfo(class CIFHelperBubbleWindow* window);
    void sub_686C50(DWORD32 a2) const;
    void sub_685F20(DWORD32 a2) const;
    void sub_6860A0(DWORD32 a2) const;
    void sub_66EC40(DWORD32 a2) const;
    void sub_672990(DWORD32 a2) const;
    void sub_686DB0() const;
    void UpdateLocation(DWORD x, DWORD y);;
    void MakeBubble();

public:
    int Type;//36C
    char pad_0x0370[0x20];//370
    CSOItem* ItemInfo;
    char pad_0x036C[0x35C - 4 - 0x28];
}; //Size=0x06C8