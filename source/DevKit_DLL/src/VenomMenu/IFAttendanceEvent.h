#pragma once
#include "IFDecoratedStatic.h"

#define GUIDE_ATTENDANCE 13385

class CIFAttendanceEventGuide : public CIFDecoratedStatic
{
GFX_DECLARE_DYNCREATE(CIFAttendanceEventGuide)

public:
    bool OnCreate(long ln) override;
    int OnMouseLeftUp(int a1, int x, int y) override;
    void OnCIFReady() override;
    CIFStatic* m_custom_label1;
};