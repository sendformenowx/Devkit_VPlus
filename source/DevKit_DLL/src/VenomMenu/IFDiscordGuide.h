#pragma once
#include "IFDecoratedStatic.h"

#define GUIDE_DC 13383

class CIFDiscordGuide : public CIFDecoratedStatic
{
GFX_DECLARE_DYNCREATE(CIFDiscordGuide)

public:
    bool OnCreate(long ln) override;
    int OnMouseLeftUp(int a1, int x, int y) override;
    void OnCIFReady() override;
    CIFStatic *m_custom_label1;
};