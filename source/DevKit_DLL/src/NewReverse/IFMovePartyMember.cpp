#include "IFMovePartyMember.h"
#include <GInterface.h>
#include <sstream>
#include <StdAfx.h>
#include <GlobalDataManager.h>
#include <CharacterDependentData.h>
#include "NetProcessIn.h"
#include "Game.h"
#include "../Network/CPSMission.h"

#define GDR_7_BTN 3
#define TIMER_CHATBLOCK 230
#define GDR_PT 31


GFX_IMPLEMENT_DYNCREATE(CIFMovePartyMember, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFMovePartyMember, CIFMainFrame)
ONG_COMMAND(GDR_7_BTN, &CIFMovePartyMember::FirstBtn)
GFX_END_MESSAGE_MAP()


std::vector<CIFMovePartyMember::PartyMember> CIFMovePartyMember::PartyList;


bool CIFMovePartyMember::OnCreate(long ln)
{

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);
    // TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);
    m_title->SetText(L"Party members window");
    TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);
    wnd_rect sz;



    RECT Lablerect = { 16,308,480,62 };
    RECT Lable2rect = { 15,49,481,259 };

    RECT Butt1rect = { 68,51,225,24 };
    RECT Butt2rect = { 243,51,75,24 };
    RECT Butt3rect = { 319,51,170,24 };
    RECT Butt4rect = { 373,51,95,24 };

    RECT Spinect = { 325,316,50,16 };
    RECT Takerect = { 273,242,70,24 };

    RECT SlotCountrect = { 140,315,30,20 };
    RECT SlotCountTextrect = { 35,318,90,13 };

    sz.pos.x = 13;
    sz.pos.y = 42;
    sz.size.width = 351;
    sz.size.height = 231;
    mytile[0] = (CIFNormalTile*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFNormalTile), sz, GDR_PT, 0);
    mytile[0]->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_b.ddj", 0, 0);


    sz.pos.x = 8;
    sz.pos.y = 36;
    sz.size.width = 361;
    sz.size.height = 242;
    chestframe = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), sz, 32, 0);
    chestframe->TB_Func_13("interface\\frame\\frameg_wnd_", 0, 0);

    sz.pos.x = 21;
    sz.pos.y = 50;
    sz.size.width = 333;
    sz.size.height = 188;
    blacksquare = (CIFStretchWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStretchWnd), sz, GDR_PT, 0);

    blacksquare->SetEdgeTextures("interface\\ifcommon\\com_blacksquare_right_side.ddj", "interface\\ifcommon\\com_blacksquare_left_up.ddj",
        "interface\\ifcommon\\com_blacksquare_left_side.ddj", "interface\\ifcommon\\com_blacksquare_left_up.ddj");





    sz.pos.x = 23;
    sz.pos.y = 52;
    sz.size.width = 41;
    sz.size.height = 24;
    mybarnumber = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_PT, 0);
    mybarnumber->SetText(L"No.");
    mybarnumber->TB_Func_13("interface\\ifcommon\\com_bar02_", 0, 0);



    sz.pos.x = 64;
    sz.pos.y = 52;
    sz.size.width = 290;
    sz.size.height = 24;
    mybarname = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_PT, 0);
    mybarname->SetText(L"Member Name");
    mybarname->TB_Func_13("interface\\ifcommon\\com_bar02_", 0, 0);





    Move = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Takerect, GDR_7_BTN, 0);
    Move->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);



    RECT rect = { 0,0,0,0 };
    m_slot1 = (CIFMovePartyMemberSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFMovePartyMemberSlotList), rect, 40, 0);


    m_slot1->MoveGWnd(m_slot1->GetPos().x + 7, m_slot1->GetPos().y + 5);


    HideLists();
    m_slot1->ShowGWnd(true);

    this->Move->SetText(L"Move");



    this->ShowGWnd(false);

    UpdateMenuSize();


    return true;
}
struct ListColumnHeader {
    const char* label;
    float size;
};
int replace = -1;

void CIFMovePartyMember::FirstBtn() {
    if (wcscmp(g_pCICPlayer->GetCharName().c_str(), SelectedItemName.c_str()) == 0)
    {
        return;
    }

    if (!SelectedItemName.empty()) {
        const SPartyData& partyData = g_CCharacterDependentData.GetPartyData();
        for (int i = 0; i < partyData.NumberOfMembers; ++i) {

            const SPartyMemberData& memberData = g_CCharacterDependentData.GetPartyMemberData(i);
            uregion region = memberData.region;
            D3DVECTOR location = memberData.position;


            if (wcscmp(memberData.m_charactername.c_str(), SelectedItemName.c_str()) == 0)
            {
                SendPacket(int(location.x), int(location.y), int(location.z), region.r, SelectedItemName);
                SelectedItemName = L"";
                ClearDDJ();
                this->ShowGWnd(false);
            }
        }

    }
}

void CIFMovePartyMember::SendPacket(int posx, int posy, int posz, short region, std::n_wstring Charname)
{
    CIFSlotWithHelp* pSlot;
    CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
    for (int i = 0; i < 96; i++)
    {
        pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
        if (pSlot->ItemInfo)
            if (pSlot->ItemInfo->GetObjectData()->TID == 0x19EC || pSlot->ItemInfo->GetObjectData()->TID == 0x19ED)
            {
                byte slot = pSlot->m_UniqueID - 87;
                CMsgStreamBuffer buf(0x200B);
                buf << slot << pSlot->ItemInfo->GetObjectData()->TID;
                buf << posx << posy << posz << region;
                buf << Charname;
                SendMsg(buf);
                break;
            }
    }
}

void CIFMovePartyMember::OnUpdate()
{

    const SPartyData& partyData = g_CCharacterDependentData.GetPartyData();


    if (replace != partyData.NumberOfMembers)
    {
        m_slot1->line1->WriteLine(L"", 9, L"");
        m_slot1->line2->WriteLine(L"", 9, L"");
        m_slot1->line3->WriteLine(L"", 9, L"");
        m_slot1->line4->WriteLine(L"", 9, L"");
        m_slot1->line5->WriteLine(L"", 9, L"");
        m_slot1->line6->WriteLine(L"", 9, L"");
        m_slot1->line7->WriteLine(L"", 9, L"");
        m_slot1->line8->WriteLine(L"", 9, L"");

        replace = partyData.NumberOfMembers;


        if (partyData.NumberOfMembers > 0) {
            ListColumnHeader headers[] = {
                    {"Id", 40},
                    {"Name", 120},
                    {"Guild", 120},
                    {"Level", 70},
                    {"HP", 70},
                    {"MP", 70},
                    {"Position", 120},
            };

            int i2 = -1;
            for (int i = 0; i < partyData.NumberOfMembers; ++i) {

                const SPartyMemberData& memberData = g_CCharacterDependentData.GetPartyMemberData(i);
                std::n_wstring test1 = memberData.m_charactername.c_str();
                std::n_wstring test2 = g_pCICPlayer->GetCharName().c_str();

                if (test1 != test2)
                    ++i2;
                else
                    continue;

                switch (i2)
                {
                case 0:
                {
                    m_slot1->line1->WriteLine(L"1", i, memberData.m_charactername.c_str());
                }break;
                case 1:
                {
                    m_slot1->line2->WriteLine(L"2", i, memberData.m_charactername.c_str());
                }break;
                case 2:
                {
                    m_slot1->line3->WriteLine(L"3", i, memberData.m_charactername.c_str());
                }break;
                case 3:
                {
                    m_slot1->line4->WriteLine(L"4", i, memberData.m_charactername.c_str());
                }break;
                case 4:
                {
                    m_slot1->line5->WriteLine(L"5", i, memberData.m_charactername.c_str());
                }break;
                case 5:
                {
                    m_slot1->line6->WriteLine(L"6", i, memberData.m_charactername.c_str());
                }break;
                case 6:
                {
                    m_slot1->line7->WriteLine(L"7", i, memberData.m_charactername.c_str());
                }break;
                case 7:
                {
                    m_slot1->line8->WriteLine(L"8", i, memberData.m_charactername.c_str());
                }break;

                default:
                    break;
                }

                SelectedItemName = L"";
                ClearDDJ();
            }
        }


    }
}

void CIFMovePartyMember::UpdateMenuSize()
{
    const ClientResolutonData& res = CGame::GetClientDimensionStuff();

    MoveGWnd(((res.width - GetSize().width) - 80), GetPos().y);
    ////  MoveGWnd(((res.width - GetSize().width) - 80), (res.height - GetSize().height) - 300);
    BringToFront();

}


void CIFMovePartyMember::HideLists()
{
    m_slot1->ShowGWnd(false);

}

void CIFMovePartyMember::ClearDDJ() {
    m_slot1->ClearDDJ();

}



void CIFMovePartyMember::Clear()
{

}


void CIFMovePartyMember::Write(int id, const wchar_t* CharName)
{
    int i = 0;
    for (std::vector<CIFMovePartyMember::PartyMember>::iterator it = CIFMovePartyMember::PartyList.begin(); it != CIFMovePartyMember::PartyList.end(); ++it) {
        ++i;
        (*it).LineNum = i;
        switch ((*it).LineNum) {
        case 0: {
            m_slot1->line1->WriteLine(L"1", i, CharName);
        }
              break;
        case 1: {
            m_slot1->line2->WriteLine(L"2", i, CharName);
        }
              break;
        case 2: {
            m_slot1->line3->WriteLine(L"3", i, CharName);
        }
              break;
        case 3: {
            m_slot1->line4->WriteLine(L"4", i, CharName);
        }
              break;
        case 4: {
            m_slot1->line5->WriteLine(L"5", i, CharName);
        }
              break;
        case 5: {
            m_slot1->line6->WriteLine(L"6", i, CharName);
        }
              break;
        case 6: {
            m_slot1->line7->WriteLine(L"7", i, CharName);
        }
              break;
        case 7: {
            m_slot1->line8->WriteLine(L"8", i, CharName);
        }
              break;

        default:
            break;
        }
    }

}