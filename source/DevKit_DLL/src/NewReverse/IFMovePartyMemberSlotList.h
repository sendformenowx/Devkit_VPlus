#pragma once


#include "IFMovePartyMemberSlot.h"

class CIFMovePartyMemberSlotList : public CIFWnd
{
    GFX_DECLARE_DYNCREATE(CIFMovePartyMemberSlotList)
    GFX_DECLARE_MESSAGE_MAP(CIFMovePartyMemberSlotList)

public:
    bool OnCreate(long ln) override;
    void OnUpdate() override;

    CIFMovePartyMemberSlot* line1;
    CIFMovePartyMemberSlot* line2;
    CIFMovePartyMemberSlot* line3;
    CIFMovePartyMemberSlot* line4;
    CIFMovePartyMemberSlot* line5;
    CIFMovePartyMemberSlot* line6;
    CIFMovePartyMemberSlot* line7;
    CIFMovePartyMemberSlot* line8;

    void ClearDDJ();
};
