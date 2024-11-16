#pragma once
#include "IFMainFrame.h"
#include "IFRankList.h"
#include <IFSelectableArea.h>
#include "IFSpinButton.h"
#include <list>
#include "IFStretchWnd.h"
#include "IFNormalTile.h"
#include "..\..\DevKit_DLL\src\GameHelpers\GameMain.h"
class CIFRank : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFRank)
GFX_DECLARE_MESSAGE_MAP(CIFRank)

public:
    bool OnCreate(long ln) override;
    void OnUnknownStuff();
    void ActivateTabPage(BYTE page);
    void Clear();
    void ShowList(BYTE listid);
    void WriteLineOwn(const wchar_t* Num, const wchar_t* Charname, const wchar_t* Guild, const wchar_t* Points);
    void UpdateUniqueRank();
    void UpdateHonorRank();
    void UpdateTraderRank();
    void UpdateHunterRank();
    void UpdateJobThiefRank();
    bool IsPageFull(BYTE PageID, BYTE LineID);
    void OnUpdate() override;
    void UpdateMenuSize();
    void HideLists();
    void OnThiefRank();
    void OnHunterRank();
    void OnTraderRank();
    void SendPacket(byte type);
public:

    static struct RankStruct
    {
        int LineNum;
        std::wstring Charname;
        std::wstring Guild;
        std::wstring Points;
    };

    static std::vector<RankStruct> UniquesRankList;
    static std::vector<RankStruct> HonorRankList;
    static std::vector<RankStruct> JobTraderRank;
    static std::vector<RankStruct> JobHunterRank;
    static std::vector<RankStruct> JobRankTFList;

public:
    /// Internal constants
    static const int numberOfTabs = 6;
    static const int tabWidth = 55;
    static const int tabHeight = 24;
    static const int tabMarginLeft = 55;
    static const int tabFirstId = 100;
    CIFStatic* name_label;
    CIFStatic* point_label;
    CIFStatic* guild_label;
    CIFStatic* rank_label;
    CIFButton* m_mybutton2;
    CIFButton* m_mybutton3;
    CIFButton* m_mybutton5;
    CIFStatic* m_custom_label2;
    CIFStatic* m_custom_label5;
    CIFStatic* m_custom_label6;
    CIFStatic* m_custom_label7;

    CIFSelectableArea** m_pTabs;

    CIFRankList* m_slot1;
    CIFRankList* m_slot2;
    CIFRankList* m_slot3;
    CIFRankList* m_slot4;
    CIFRankList* m_slot5;

    CIFSpinControl* m_spin;
    CIFFrame* frame;
    CIFNormalTile* tile;
    CIFStretchWnd* blacksquare;
};



