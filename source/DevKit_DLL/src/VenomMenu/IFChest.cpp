#include "IFChest.h"
#include <GInterface.h>
#include <sstream>
#include <StdAfx.h>
#include <GlobalDataManager.h>
#include "NetProcessIn.h"
#include "Game.h"
#include "../Network/CPSMission.h"

#define GDR_7_BTN 3
#define TIMER_CHATBLOCK 230
#define GDR_CHEST_BG 31
CIFPlayerChest* CIFPlayerChest::ChestW;
CIFWnd* CIFPlayerChest::ChestIcon;


GFX_IMPLEMENT_DYNCREATE(CIFPlayerChest, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFPlayerChest, CIFMainFrame)
                    ONG_COMMAND(GDR_7_BTN, &CIFPlayerChest::On_BtnClick_1)
                    ONG_COMMAND(6, &CIFPlayerChest::On_BtnClick_2)
GFX_END_MESSAGE_MAP()


std::vector<CIFPlayerChest::Chest> CIFPlayerChest::ChestList;


bool CIFPlayerChest::OnCreate(long ln)
{

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);
    // TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);
    m_title->SetText(L"Item Chest");
    TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);
    wnd_rect sz;



    RECT Lablerect = { 16,308,480,62 };
    RECT Lable2rect = { 15,49,481,259 };

    RECT Butt1rect = { 68,51,225,24 };
    RECT Butt2rect = { 243,51,75,24 };
    RECT Butt3rect = { 319,51,170,24 };
    RECT Butt4rect = { 373,51,95,24 };

    RECT Spinect = { 325,316,50,16 };
    RECT Takerect = { 600,311,70,24 };
    RECT TakeAllrect = { 420,319,70,24 };

    RECT SlotCountrect = { 140,315,30,20 };
    RECT SlotCountTextrect = { 35,318,90,13 };

    sz.pos.x= 13;
    sz.pos.y = 42;
    sz.size.width = 678;
    sz.size.height = 300;
    mytile[0] = (CIFNormalTile*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFNormalTile), sz, GDR_CHEST_BG, 0);
    mytile[0]->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_b.ddj", 0, 0);


    sz.pos.x= 8;
    sz.pos.y = 36;
    sz.size.width = 688;
    sz.size.height = 311;
    chestframe = (CIFFrame*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), sz, 32, 0);
    chestframe->TB_Func_13("interface\\frame\\frameg_wnd_", 0, 0);

    sz.pos.x= 21;
    sz.pos.y = 50;
    sz.size.width = 660;
    sz.size.height = 257;
    blacksquare = (CIFStretchWnd* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStretchWnd), sz, GDR_CHEST_BG, 0);

    blacksquare->SetEdgeTextures("interface\\ifcommon\\com_blacksquare_right_side.ddj", "interface\\ifcommon\\com_blacksquare_left_up.ddj",
                                 "interface\\ifcommon\\com_blacksquare_left_side.ddj", "interface\\ifcommon\\com_blacksquare_left_up.ddj");





    sz.pos.x= 23;
    sz.pos.y = 52;
    sz.size.width = 41;
    sz.size.height = 24;
    mybarnumber = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_CHEST_BG, 0);
    mybarnumber -> SetText(L"No.");
    mybarnumber->TB_Func_13("interface\\ifcommon\\com_bar02_", 0 ,0);



    sz.pos.x= 64;
    sz.pos.y = 52;
    sz.size.width = 290;
    sz.size.height = 24;
    mybarname = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_CHEST_BG, 0);
    mybarname -> SetText(L"Item Name");
    mybarname->TB_Func_13("interface\\ifcommon\\com_bar02_", 0 ,0);



    sz.pos.x= 354;
    sz.pos.y = 52;
    sz.size.width = 83;
    sz.size.height = 24;
    mybaradet = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_CHEST_BG, 0);
    mybaradet -> SetText(L"Quantity");
    mybaradet->TB_Func_13("interface\\ifcommon\\com_bar02_", 0 ,0);



    sz.pos.x= 437;
    sz.pos.y = 52;
    sz.size.width = 151;
    sz.size.height = 24;
    mybarfrom = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_CHEST_BG, 0);
    mybarfrom -> SetText(L"From");
    mybarfrom->TB_Func_13("interface\\ifcommon\\com_bar02_", 0 ,0);



    sz.pos.x= 588;
    sz.pos.y = 52;
    sz.size.width = 93;
    sz.size.height = 24;
    mybardate = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_CHEST_BG, 0);
    mybardate -> SetText(L"Date");
    mybardate->TB_Func_13("interface\\ifcommon\\com_bar02_", 0 ,0);



    m_spin = (CIFSpinControl*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSpinControl), Spinect, 4, 0);
    Take = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Takerect, GDR_7_BTN, 0);
    Take->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);


    sz.pos.x= 60;
    sz.pos.y = 311;
    sz.size.width = 40;
    sz.size.height = 20;
    remaining = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 179, 1);
    remaining->TB_Func_6(1);
    remaining->TB_Func_5(1);
    remaining->SetText(L"Inventory Remaining");

    sz.pos.x= 140;
    sz.pos.y = 311;
    sz.size.width = 40;
    sz.size.height = 20;
    remainingbox = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 180, 1);
    remainingbox->TB_Func_13("interface\\exchange\\exc_box.ddj", 0, 0);
    remainingbox->TB_Func_6(1);
    remainingbox->TB_Func_5(1);

    RECT rect = { 0,0,0,0 };
    m_slot1 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 40, 0);
    m_slot2 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 41, 0);
    m_slot3 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 42, 0);
    m_slot4 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 43, 0);
    m_slot5 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 44, 0);
    m_slot6 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 45, 0);
    m_slot7 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 46, 0);
    m_slot8 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 47, 0);
    m_slot9 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 48, 0);
    m_slot10 = (CIFPlayerChestSlotList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChestSlotList), rect, 49, 0);

    m_slot1->MoveGWnd(m_slot1->GetPos().x + 7, m_slot1->GetPos().y + 5);
    m_slot2->MoveGWnd(m_slot2->GetPos().x + 7, m_slot2->GetPos().y + 5);
    m_slot3->MoveGWnd(m_slot3->GetPos().x + 7, m_slot3->GetPos().y + 5);
    m_slot4->MoveGWnd(m_slot4->GetPos().x + 7, m_slot4->GetPos().y + 5);
    m_slot5->MoveGWnd(m_slot5->GetPos().x + 7, m_slot5->GetPos().y + 5);
    m_slot6->MoveGWnd(m_slot6->GetPos().x + 7, m_slot6->GetPos().y + 5);
    m_slot7->MoveGWnd(m_slot7->GetPos().x + 7, m_slot7->GetPos().y + 5);
    m_slot8->MoveGWnd(m_slot8->GetPos().x + 7, m_slot8->GetPos().y + 5);
    m_slot9->MoveGWnd(m_slot9->GetPos().x + 7, m_slot9->GetPos().y + 5);
    m_slot10->MoveGWnd(m_slot10->GetPos().x + 7, m_slot10->GetPos().y + 5);


    HideLists();
    m_slot1->ShowGWnd(true);
    m_spin->SetMinValue(1);
    m_spin->SetCurrentValue(1);
    m_spin->SetMaxValue(10);
    m_spin->ShowGWnd(true);


    this->Take->SetText(L"Take");



    this->ShowGWnd(false);

    UpdateMenuSize();


    return true;
}
unsigned __int8 InventorySlot;
void CIFPlayerChest::OnUpdate()
{
    unsigned __int8 test = g_CGlobalDataManager->GetEmptyInventorySlots();
    InventorySlot = test;
    wchar_t Point[33];
    swprintf_s(Point, L"%d", test);
    remainingbox->SetText(Point);
}

void CIFPlayerChest::UpdateMenuSize()
{
    const ClientResolutonData &res = CGame::GetClientDimensionStuff();

    MoveGWnd(((res.width - GetSize().width) - 80), GetPos().y);
    ////  MoveGWnd(((res.width - GetSize().width) - 80), (res.height - GetSize().height) - 300);
    BringToFront();

}

void CIFPlayerChest::On_BtnClick_1()
{

    if(InventorySlot == 0)
    {
        g_pCGInterface->ShowMessage_Warning(L"Inventory is full.");
        return;
    }
    if (!SelectedItemName.empty())
    {
        for (int i = 0; i < ChestList.size(); ++i)
        {
            if (wcscmp(ChestList[i].ItemID.c_str(), SelectedItemName.c_str()) == 0)
            {
                CMsgStreamBuffer buf(0x3505);
                buf << GET_OWN_GAME_ID();
                buf << TO_NSTRING(ChestList[i].ItemID);
                SendMsg(buf);
                ClearDDJ();
                SelectedItemName = std::n_wstring();
                unsigned __int8 test = g_CGlobalDataManager->GetEmptyInventorySlots();
                test = InventorySlot;
                wchar_t Point[33];
                swprintf_s(Point, L"%d", test);
                remainingbox->SetText(Point);
                break;
            }
        }
    }
    else
    {
        g_pCGInterface->ShowMessage_Warning(L"Please select a item first.");
        return;
    }
}

void CIFPlayerChest::On_BtnClick_2()
{
    BYTE v1 = 2;
    CMsgStreamBuffer buf(0x3505);
    buf << v1;
    buf << GET_OWN_GAME_ID();
    SendMsg(buf);
    ClearDDJ();
}

DWORD WINAPI CIFPlayerChest::UpdateSlotCount(LPVOID lpParam) {
    while (true) {
        Sleep(1000);
        CMsgStreamBuffer buf(0x3503);
        unsigned int ID = GET_OWN_GAME_ID();
        buf << ID;
        SendMsg(buf);
    }
}
void CIFPlayerChest::OnClick_Exit()
{
    this->OnCloseWnd();
}

void CIFPlayerChest::HideLists()
{
    m_slot1->ShowGWnd(false);
    m_slot2->ShowGWnd(false);
    m_slot3->ShowGWnd(false);
    m_slot4->ShowGWnd(false);
    m_slot5->ShowGWnd(false);
    m_slot6->ShowGWnd(false);
    m_slot7->ShowGWnd(false);
    m_slot8->ShowGWnd(false);
    m_slot9->ShowGWnd(false);
    m_slot10->ShowGWnd(false);
}

void CIFPlayerChest::ClearDDJ() {
    m_slot1->ClearDDJ();
    m_slot2->ClearDDJ();
    m_slot3->ClearDDJ();
    m_slot4->ClearDDJ();
    m_slot5->ClearDDJ();
    m_slot6->ClearDDJ();
    m_slot7->ClearDDJ();
    m_slot8->ClearDDJ();
    m_slot9->ClearDDJ();
    m_slot10->ClearDDJ();
}
void CIFPlayerChest::ShowList(BYTE listid)
{
    switch (listid)
    {
        case 1:
            HideLists();
            m_slot1->ShowGWnd(true);
            break;
        case 2:
            HideLists();
            m_slot2->ShowGWnd(true);
            break;
        case 3:
            HideLists();
            m_slot3->ShowGWnd(true);
            break;
        case 4:
            HideLists();
            m_slot4->ShowGWnd(true);
            break;
        case 5:
            HideLists();
            m_slot5->ShowGWnd(true);
            break;
        case 6:
            HideLists();
            m_slot6->ShowGWnd(true);
            break;
        case 7:
            HideLists();
            m_slot7->ShowGWnd(true);
            break;
        case 8:
            HideLists();
            m_slot8->ShowGWnd(true);
            break;
        case 9:
            HideLists();
            m_slot9->ShowGWnd(true);
            break;
        case 10:
            HideLists();
            m_slot10->ShowGWnd(true);
            break;
    }
}

bool CIFPlayerChest::IsPageFull(BYTE PageID, BYTE LineID)
{
    bool full = false;
    if (PageID == 1)
    {
        if (LineID == 30)
        {
            if (m_slot1->line1->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot1->line10->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 2)
    {
        if (LineID == 30)
        {
            if (m_slot2->line1->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot2->line10->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 3)
    {
        if (LineID == 30)
        {
            if (m_slot3->line1->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot3->line10->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 4)
    {
        if (LineID == 30)
        {
            if (m_slot4->line1->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot4->line10->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 5)
    {
        if (LineID == 30)
        {
            if (m_slot5->line1->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot5->line10->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 6)
    {
        if (LineID == 30)
        {
            if (m_slot6->line1->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot6->line10->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 7)
    {
        if (LineID == 30)
        {
            if (m_slot7->line1->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot7->line10->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 8)
    {
        if (LineID == 30)
        {
            if (m_slot8->line1->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot8->line10->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 9)
    {
        if (LineID == 30)
        {
            if (m_slot9->line1->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot9->line10->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 10)
    {
        if (LineID == 30)
        {
            if (m_slot10->line1->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot10->line10->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }

    return full;
}

bool CIFPlayerChest::ChestContains(const wchar_t* ItemName)
{
    for (std::vector<CIFPlayerChest::Chest>::iterator it = CIFPlayerChest::ChestList.begin(); it != CIFPlayerChest::ChestList.end(); ++it)
        if (wcscmp((*it).CodeName128.c_str(), ItemName) == 0)
            return true;
    return false;
}

void CIFPlayerChest::UpdateChest()
{
    int i = 0;
    for (std::vector<CIFPlayerChest::Chest>::iterator it = CIFPlayerChest::ChestList.begin(); it != CIFPlayerChest::ChestList.end(); ++it)
    {
        ++i;
        // if(!(*it).NameStrID128.empty())
        //{
        (*it).LineNum = i;
        //}

        switch ((*it).LineNum)
        {
            case 1:
            {
                m_slot1->line1->WriteLine(L"1",(*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine(L"2",(*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine(L"3",(*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine(L"4", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine(L"5",(*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine(L"6",(*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine(L"7", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 8:
            {
                m_slot1->line8->WriteLine(L"8", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 9:
            {
                m_slot1->line9->WriteLine(L"9", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 10:
            {
                m_slot1->line10->WriteLine(L"10", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line1->WriteLine(L"11", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line2->WriteLine(L"12", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line3->WriteLine(L"13", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line4->WriteLine(L"14", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 15:
            {
                m_slot2->line5->WriteLine(L"15", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 16:
            {
                m_slot2->line6->WriteLine(L"16", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 17:
            {
                m_slot2->line7->WriteLine(L"17", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 18:
            {
                m_slot2->line8->WriteLine(L"18", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 19:
            {
                m_slot2->line9->WriteLine(L"19", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 20:
            {
                m_slot2->line10->WriteLine(L"20", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line1->WriteLine(L"21", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 22:
            {
                m_slot3->line2->WriteLine(L"22", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 23:
            {
                m_slot3->line3->WriteLine(L"23", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 24:
            {
                m_slot3->line4->WriteLine(L"24", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 25:
            {
                m_slot3->line5->WriteLine(L"25", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 26:
            {
                m_slot3->line6->WriteLine(L"26", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 27:
            {
                m_slot3->line7->WriteLine(L"27", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 28:
            {
                m_slot3->line8->WriteLine(L"28", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 29:
            {
                m_slot3->line9->WriteLine(L"29", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 30:
            {
                m_slot3->line10->WriteLine(L"30", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 31:
            {
                m_slot4->line1->WriteLine(L"31", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 32:
            {
                m_slot4->line2->WriteLine(L"32", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 33:
            {
                m_slot4->line3->WriteLine(L"33", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 34:
            {
                m_slot4->line4->WriteLine(L"34", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 35:
            {
                m_slot4->line5->WriteLine(L"35", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 36:
            {
                m_slot4->line6->WriteLine(L"36", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 37:
            {
                m_slot4->line7->WriteLine(L"37", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 38:
            {
                m_slot4->line8->WriteLine(L"38", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 39:
            {
                m_slot4->line9->WriteLine(L"39", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 40:
            {
                m_slot4->line10->WriteLine(L"40", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 41:
            {
                m_slot5->line1->WriteLine(L"41", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 42:
            {
                m_slot5->line2->WriteLine(L"42", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 43:
            {
                m_slot5->line3->WriteLine(L"43", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 44:
            {
                m_slot5->line4->WriteLine(L"44", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 45:
            {
                m_slot5->line5->WriteLine(L"45", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 46:
            {
                m_slot5->line6->WriteLine(L"46", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 47:
            {
                m_slot5->line7->WriteLine(L"47", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 48:
            {
                m_slot5->line8->WriteLine(L"48", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 49:
            {
                m_slot5->line9->WriteLine(L"49", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 50:
            {
                m_slot5->line10->WriteLine(L"50", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 51:
            {
                m_slot6->line1->WriteLine(L"51", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 52:
            {
                m_slot6->line2->WriteLine(L"52", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 53:
            {
                m_slot6->line3->WriteLine(L"53", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 54:
            {
                m_slot6->line4->WriteLine(L"54", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 55:
            {
                m_slot6->line5->WriteLine(L"55", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 56:
            {
                m_slot6->line6->WriteLine(L"56", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 57:
            {
                m_slot6->line7->WriteLine(L"57", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 58:
            {
                m_slot6->line8->WriteLine(L"58", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 59:
            {
                m_slot6->line9->WriteLine(L"59", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 60:
            {
                m_slot6->line10->WriteLine(L"60", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 61:
            {
                m_slot7->line1->WriteLine(L"61", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 62:
            {
                m_slot7->line2->WriteLine(L"62", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 63:
            {
                m_slot7->line3->WriteLine(L"63", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 64:
            {
                m_slot7->line4->WriteLine(L"64", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 65:
            {
                m_slot7->line5->WriteLine(L"65", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 66:
            {
                m_slot7->line6->WriteLine(L"66", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 67:
            {
                m_slot7->line7->WriteLine(L"67", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 68:
            {
                m_slot7->line8->WriteLine(L"68", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 69:
            {
                m_slot7->line9->WriteLine(L"69", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 70:
            {
                m_slot7->line10->WriteLine(L"70", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 71:
            {
                m_slot8->line1->WriteLine(L"71", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 72:
            {
                m_slot8->line2->WriteLine(L"72", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 73:
            {
                m_slot8->line3->WriteLine(L"73", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 74:
            {
                m_slot8->line4->WriteLine(L"74", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 75:
            {
                m_slot8->line5->WriteLine(L"75", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 76:
            {
                m_slot8->line6->WriteLine(L"76", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 77:
            {
                m_slot8->line7->WriteLine(L"77", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 78:
            {
                m_slot8->line8->WriteLine(L"78", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 79:
            {
                m_slot8->line9->WriteLine(L"79", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 80:
            {
                m_slot8->line10->WriteLine(L"80", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 81:
            {
                m_slot9->line1->WriteLine(L"81", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 82:
            {
                m_slot9->line2->WriteLine(L"82", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 83:
            {
                m_slot9->line3->WriteLine(L"83", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 84:
            {
                m_slot9->line4->WriteLine(L"84", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 85:
            {
                m_slot9->line5->WriteLine(L"85", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 86:
            {
                m_slot9->line6->WriteLine(L"86", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 87:
            {
                m_slot9->line7->WriteLine(L"87", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 88:
            {
                m_slot9->line8->WriteLine(L"88", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 89:
            {
                m_slot9->line9->WriteLine(L"89", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 90:
            {
                m_slot9->line10->WriteLine(L"90", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 91:
            {
                m_slot10->line1->WriteLine(L"91", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 92:
            {
                m_slot10->line2->WriteLine(L"92", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 93:
            {
                m_slot10->line3->WriteLine(L"93", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 94:
            {
                m_slot10->line4->WriteLine(L"94", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 95:
            {
                m_slot10->line5->WriteLine(L"95", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 96:
            {
                m_slot10->line6->WriteLine(L"96", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 97:
            {
                m_slot10->line7->WriteLine(L"97", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 98:
            {
                m_slot10->line8->WriteLine(L"98", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 99:
            {
                m_slot10->line9->WriteLine(L"99", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
            case 100:
            {
                m_slot10->line10->WriteLine(L"100", (*it).ItemID.c_str(), (*it).NameStrID128.c_str(), (*it).Count.c_str(), (*it).From.c_str(), (*it).Date.c_str());
            }
                break;
        }
    }
}


void CIFPlayerChest::Clear()
{

    m_slot1->line1->WriteLine(L"", L"", L"", L"", L"", L"");
    m_slot1->line2->WriteLine(L"", L"", L"", L"", L"" , L"");
    m_slot1->line3->WriteLine(L"", L"", L"", L"", L"", L"");
    m_slot1->line4->WriteLine(L"", L"", L"", L"", L"", L"");
    m_slot1->line5->WriteLine(L"", L"", L"", L"", L"", L"");
    m_slot1->line6->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot1->line7->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot1->line8->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot1->line9->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot1->line10->WriteLine(L"",L"", L"", L"", L"", L"");

    m_slot2->line1->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot2->line2->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot2->line3->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot2->line4->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot2->line5->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot2->line6->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot2->line7->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot2->line8->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot2->line9->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot2->line10->WriteLine(L"",L"", L"", L"", L"", L"");

    m_slot3->line1->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot3->line2->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot3->line3->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot3->line4->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot3->line5->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot3->line6->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot3->line7->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot3->line8->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot3->line9->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot3->line10->WriteLine(L"",L"", L"", L"", L"", L"");

    m_slot4->line1->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot4->line2->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot4->line3->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot4->line4->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot4->line5->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot4->line6->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot4->line7->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot4->line8->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot4->line9->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot4->line10->WriteLine(L"",L"", L"", L"", L"", L"");

    m_slot5->line1->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot5->line2->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot5->line3->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot5->line4->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot5->line5->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot5->line6->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot5->line7->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot5->line8->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot5->line9->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot5->line10->WriteLine(L"",L"", L"", L"", L"", L"");

    m_slot6->line1->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot6->line2->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot6->line3->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot6->line4->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot6->line5->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot6->line6->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot6->line7->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot6->line8->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot6->line9->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot6->line10->WriteLine(L"",L"", L"", L"", L"", L"");

    m_slot7->line1->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot7->line2->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot7->line3->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot7->line4->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot7->line5->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot7->line6->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot7->line7->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot7->line8->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot7->line9->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot7->line10->WriteLine(L"",L"", L"", L"", L"", L"");

    m_slot8->line1->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot8->line2->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot8->line3->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot8->line4->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot8->line5->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot8->line6->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot8->line7->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot8->line8->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot8->line9->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot8->line10->WriteLine(L"",L"", L"", L"", L"", L"");

    m_slot9->line1->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot9->line2->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot9->line3->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot9->line4->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot9->line5->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot9->line6->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot9->line7->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot9->line8->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot9->line9->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot9->line10->WriteLine(L"",L"", L"", L"", L"", L"");

    m_slot10->line1->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot10->line2->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot10->line3->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot10->line4->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot10->line5->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot10->line6->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot10->line7->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot10->line8->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot10->line9->WriteLine(L"",L"", L"", L"", L"", L"");
    m_slot10->line10->WriteLine(L"",L"", L"", L"", L"", L"");
}
