#pragma once
#include "IFDecoratedStatic.h"

#define GUIDE_CHEST 13381

class CIFChestGuide : public CIFDecoratedStatic
{
GFX_DECLARE_DYNCREATE(CIFChestGuide)
GFX_DECLARE_MESSAGE_MAP(CIFChestGuide)

public:
    bool OnCreate(long ln) override;
    int OnMouseLeftUp(int a1, int x, int y) override;
    void OnCIFReady() override;
    void OnUpdate() override;
    int OnVisibleStateChange(int a1, int a2);
    CIFStatic * m_custom_label1;
};