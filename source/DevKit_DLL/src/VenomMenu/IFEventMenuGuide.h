#pragma once
#include "IFDecoratedStatic.h"

#define GUIDE_EVENTS 13384

class CIFEventMenuGuide : public CIFDecoratedStatic
{
GFX_DECLARE_DYNCREATE(CIFEventMenuGuide)

public:
    bool OnCreate(long ln) override;
    int OnMouseLeftUp(int a1, int x, int y) override;
    void OnCIFReady() override;
    CIFStatic * m_custom_label1;
};