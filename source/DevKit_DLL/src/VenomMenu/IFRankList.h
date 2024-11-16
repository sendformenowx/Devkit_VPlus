#pragma once
#include "IFMainFrame.h"
#include "IFRankSlot.h"
#include "IFBarWnd.h"

class CIFRankList : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFRankList)
GFX_DECLARE_MESSAGE_MAP(CIFRankList)

public:

    bool OnCreate(long ln) override;
    void OnUpdate() override;
public:
    CIFStatic* m_custom_label2;
    CIFRankSlot* line1;
    CIFRankSlot* line2;
    CIFRankSlot* line3;
    CIFRankSlot* line4;
    CIFRankSlot* line5;
    CIFRankSlot* line6;
    CIFRankSlot* line7;
    CIFRankSlot* line8;
    CIFRankSlot* line9;
    CIFRankSlot* line10;
    CIFRankSlot* line11;
    CIFBarWnd* bars[15];

};



