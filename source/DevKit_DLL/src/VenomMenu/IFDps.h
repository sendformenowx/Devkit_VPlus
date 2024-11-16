#pragma once
#include "IFMainFrame.h"
#include "IFBarWnd.h"
#include "IFStretchWnd.h"
#include "IFNormalTile.h"

class CIFDps : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFDps)

public:
    static struct DpsMeter
    {
        std::wstring Charname;
        int damage;
    };
    static std::vector<DpsMeter> DpsDamage;

    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void WriteLine(BYTE Num, const wchar_t* Charname, const wchar_t* DMG) const;
    void Clear() const;
    void UpdateMenuSize();
    void OnTimer(int) override;
    void OpenDPS(int timeoutSeconds);
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
    CIFStatic* unique_slot;
    CIFStretchWnd* blacksquare;
    CIFNormalTile* tile;
};
