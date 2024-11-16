#pragma once
#include "IFMainFrame.h"
#include <list>
#include "IFStretchWnd.h"
#include "IFNormalTile.h"
#include "IFBarWnd.h"
#include "IFMovePartyMemberSlotList.h"
#include <string>
#include <sstream>

class CIFMovePartyMember : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFMovePartyMember)
GFX_DECLARE_MESSAGE_MAP(CIFMovePartyMember)

public:

    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void UpdateMenuSize();

    void HideLists();
    void Clear();
    void Write(int id, const wchar_t* CharName);
    void UpdateChest();
private:
    void FirstBtn();
    void SendPacket(int posx, int posy, int posz, short region, std::n_wstring Charname);
public:

    static struct PartyMember
    {
        int LineNum;
        int region;
        int x;
        int y;
        int z;
        byte hpmp;
        byte level;
        std::n_wstring playername;
    };

    static std::vector<PartyMember> PartyList;

    CIFMovePartyMemberSlotList* m_slot1;

    CIFStatic* m_custom_label2;
    CIFStatic* Count;
    CIFButton* Move;
    CIFFrame* chestframe;
    CIFBarWnd* mybarname;
    CIFBarWnd* mybarnumber;
    CIFStretchWnd* blacksquare;
    CIFNormalTile* mytile[50];
    std::n_wstring SelectedItemName;
    void ClearDDJ();


};
