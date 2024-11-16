#pragma once
#include "IFMainFrame.h"
#include "IFBarWnd.h"
#include "IFStretchWnd.h"

class CIFSurvivalArena : public CIFFrame
{
GFX_DECLARE_DYNCREATE(CIFSurvivalArena)

public:
    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void WriteLine(BYTE Num, const wchar_t* Charname, const wchar_t* DMG) const;
    void Clear() const;
    void UpdateMenuSize();
private:
    void On_BtnClick();

public:
    CIFStatic* dps_title;
    CIFBarWnd* bars[10];
    CIFBarWnd* name_label;
    CIFBarWnd* rank_label;
    CIFBarWnd* dmg_label;
    CIFStatic* rank_slot[10];
    CIFStatic* name_slot[10];
    CIFStatic* dmg_slot[10];
    CIFStretchWnd* blacksquare;

};
