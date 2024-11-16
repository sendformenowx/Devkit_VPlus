#pragma once
#include "IFDecoratedStatic.h"

#define GUIDE_MAINMENU 13380

class CIFMainMenuGuide : public CIFDecoratedStatic
{
GFX_DECLARE_DYNCREATE(CIFMainMenuGuide)

public:
    bool OnCreate(long ln) override;
    int OnMouseLeftUp(int a1, int x, int y) override;
    void OnCIFReady() override;
    CIFStatic * m_custom_label1;
    CIFStatic * iconframe;
};
