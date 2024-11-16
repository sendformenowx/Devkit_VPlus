#pragma once
#include "IFDecoratedStatic.h"

#define GUIDE_FACEBOOK 13382

class CIFFacebookGuide : public CIFDecoratedStatic
{
GFX_DECLARE_DYNCREATE(CIFFacebookGuide)

public:
    bool OnCreate(long ln) override;
    int OnMouseLeftUp(int a1, int x, int y) override;
    void OnCIFReady() override;
    CIFStatic * m_custom_label1;
};