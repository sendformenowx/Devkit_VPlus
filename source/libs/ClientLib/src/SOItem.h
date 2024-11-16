#pragma once

#include "Data/ItemData.h"
#include "../../../DevKit_DLL/src/ItemLinking/ObjectData.h"
#include <BSLib/BSLib.h>
#include <ghidra/undefined.h>

enum Blue : short {
    BLUE_INT = 0x0005,
    BLUE_STR = 0x000b,
    BLUE_DURABILITY = 0x0050,
    BLUE_LUCKY = 0x003d,
    BLUE_LUCKY2 = 0x003b,
    BLUE_MP = 0x0098,
    BLUE_HP = 0x008C,
    BLUE_PARRY = 0x0080,
    BLUE_REPAIR_INVALID = 0x0041,
    BLUE_STEADY = 0x0035
};

class CSOItem {
public:
    /// \address 008ba440
    const CItemData::SData *GetItemData() const;
    ObjectData* GetObjectData();
    /// \address 008ba460
    int GetQuantity() const;

public:
    char pad_0000[24]; //0x0000
    DWORD unkClass; //0x0018
    DWORD unk_1; //0x001C
    DWORD Active; //0x0020
    char pad_0024[4]; //0x0024
    undefined1 field_28; //0x0028
    char pad_0029[11]; //0x0029
    int m_refObjItemId; //0x0034
    char pad_0038[84]; //0x0038
    BYTE OptLevel; //0x008C
    char pad_008D[11]; //0x008D
    int CurrDurability; //0x0098
    int m_quantity; //0x009C
    char pad_00A0[36]; //0x00A0
    std::n_map<Blue, int> bluemap;//0x00c4
    char pad_00D0[16]; //0x00D0
    int PhyAtkPwrMax; //0x00E0
    int PhyAtkPwrMin; //0x00E4
    int MagAtkPwrMax; //0x00E8
    int MagAtkPwrMin; //0x00EC
    int BlockingRateValue; //0x00F0
    int MaxDurability; //0x00F4
    float PhyDefPwrValue; //0x00F8
    int ParryRateValue; //0x00FC
    float PhyAbsorption; //0x0100
    char pad_0104[4]; //0x0104
    int CriticalValue; //0x0108
    float MagDefPwrValue; //0x010C
    float MagAbsorption; //0x0110
    float PhyReinforcementMin; //0x0114
    float PhyReinforcementMax; //0x0118
    float MagReinforcementMin; //0x011C
    float MagReinforcementMax; //0x0120
    float PhyReinforcementValue; //0x0124
    float MagReinforcementValue; //0x0128
    char pad_012C[4]; //0x012C
    int AttackRateValue; //0x0130
    char pad_0134[156]; //0x0134


BEGIN_FIXTURE()
        ENSURE_SIZE(464)// approved by CIFExchange::ctor
        ENSURE_OFFSET(field_28, 0x28)
        ENSURE_OFFSET(m_refObjItemId, 0x34)
        ENSURE_OFFSET(m_quantity, 0x9c)
        ENSURE_OFFSET(bluemap, 0xc4)
    END_FIXTURE()

    RUN_FIXTURE(CSOItem)
}; //Size: 0x01D0