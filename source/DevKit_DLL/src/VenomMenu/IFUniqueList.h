#pragma once
#include "IFMainFrame.h"
#include "IFUniqueLogSlot.h"
#include "IFBarWnd.h"

class CIFUniqueList : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFUniqueList)
GFX_DECLARE_MESSAGE_MAP(CIFUniqueList)

public:
    bool OnCreate(long ln) override;
    void OnUpdate() override;


    CIFUniqueLogSlot* line1;
    CIFUniqueLogSlot* line2;
    CIFUniqueLogSlot* line3;
    CIFUniqueLogSlot* line4;
    CIFUniqueLogSlot* line5;
    CIFUniqueLogSlot* line6;
    CIFUniqueLogSlot* line7;
    CIFUniqueLogSlot* line8;
    CIFUniqueLogSlot* line9;
    CIFUniqueLogSlot* line10;

    CIFBarWnd* bar[10];
    CIFBarWnd* bar1[10];
};
