#pragma once
#include "IFMainFrame.h"
#include "IFChestSlotList.h"
#include "IFSpinButton.h"
#include <list>
#include "IFStretchWnd.h"
#include "IFNormalTile.h"
#include "IFBarWnd.h"
#include <string>
#include <sstream>

class CIFPlayerChest : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFPlayerChest)
GFX_DECLARE_MESSAGE_MAP(CIFPlayerChest)

public:

    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void UpdateMenuSize();

    void HideLists();
    void ShowList(BYTE listid);
    bool IsPageFull(BYTE PageID, BYTE LineID);
    void Clear();
    void UpdateChest();
    bool ChestContains(const wchar_t* ItemName);
    static  DWORD WINAPI UpdateSlotCount(LPVOID lpParam);
    static CIFWnd* ChestIcon;
    static CIFPlayerChest* ChestW;
private:
    void On_BtnClick_1();

    void On_BtnClick_2();

    void OnClick_Exit();

public:
    static struct Chest
    {
        std::wstring ItemID;
        int LineNum;
        std::wstring CodeName128;
        bool RandomStat;
        std::n_string OptLevel;
        std::wstring NameStrID128;
        std::wstring Count;
        std::wstring From;
        std::wstring Date;
    };

    static std::vector<Chest> ChestList;

    CIFPlayerChestSlotList* m_slot1;
    CIFPlayerChestSlotList* m_slot2;
    CIFPlayerChestSlotList* m_slot3;
    CIFPlayerChestSlotList* m_slot4;
    CIFPlayerChestSlotList* m_slot5;
    CIFPlayerChestSlotList* m_slot6;
    CIFPlayerChestSlotList* m_slot7;
    CIFPlayerChestSlotList* m_slot8;
    CIFPlayerChestSlotList* m_slot9;
    CIFPlayerChestSlotList* m_slot10;

    CIFSpinControl* m_spin;
    CIFStatic* m_custom_label2;
    CIFStatic* Count;
    CIFButton* Take;
    CIFFrame* chestframe;
    CIFBarWnd* mybarname;
    CIFBarWnd* mybaradet;
    CIFBarWnd* mybarnumber;
    CIFBarWnd* mybarfrom;
    CIFBarWnd* mybardate;
    CIFStretchWnd* blacksquare;
    CIFNormalTile* mytile[50];
    std::n_wstring SelectedItemName;
    CIFStatic* remainingbox;
    CIFStatic* remaining;
    void ClearDDJ();


};
