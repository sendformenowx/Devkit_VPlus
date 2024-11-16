#pragma once
#include "IFMainFrame.h"
#include "IFBarWnd.h"
#include "IFStretchWnd.h"
#include "IFNormalTile.h"
#include "IFSelectableArea.h"
class CIFFortressWar : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFFortressWar)
GFX_DECLARE_MESSAGE_MAP(CIFFortressWar)
public:
    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void WriteLine(BYTE Num, const wchar_t* Charname, const wchar_t* DMG) const;
    void ClearGuild() const;
    void ClearUni() const;
    void ClearPlayer() const;
    void UpdateMenuSize();
private:
    void On_BtnClick();
    void On_BtnClickUni();
    void On_BtnClickPlayer();
public:
    CIFStatic* dps_title;
    CIFBarWnd* bars[10];
    CIFBarWnd* name_label;
    CIFBarWnd* rank_label;
    CIFBarWnd* dmg_label;
    CIFStatic* rank_slot[10];
    CIFStatic* name_slot[10];
    CIFStatic* unionname_slot[10];
    CIFStatic* playername_slot[10];

    CIFStatic* dmg_slot[10];
    CIFStatic* uniondmg_slot[10];
    CIFStatic* playerdmg_slot[10];

    CIFButton* ShowGuild;
    CIFButton* ShowUnion;
    CIFButton* ShowPlayer;
    CIFStretchWnd* blacksquare;
    CIFNormalTile* tile;
    void WriteLine2(BYTE Num, const wchar_t *Charname, const wchar_t *DMG) const;

    void WriteLine3(BYTE Num, const wchar_t *Charname, const wchar_t *DMG) const;
};
