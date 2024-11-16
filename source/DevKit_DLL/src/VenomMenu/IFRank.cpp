#include "IFRank.h"
#include <ICPlayer.h>
#include "Game.h"
#include <StdAfx.h>
#include <sstream>

#define GDR_Thief_BTN 3
#define GDR_Thief_BTNNew 37
#define GDR_Hunter_BTN 5
#define GDR_Trader_BTN 6

#define GDR_RANKS_POINT_LABEL 21
#define GDR_RANKS_RANK_LABEL 22
#define GDR_RANKS_NAME_LABEL 23
#define GDR_RANKS_GUILD_LABEL 24
#define GDR_RANKS_BG 5
#define GDR_RANKS_FRAME 3
#define GDR_RANKS_BLACKSQUARE 1
GFX_IMPLEMENT_DYNCREATE(CIFRank, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFRank, CIFMainFrame)
                    ONG_COMMAND(100, &CIFRank::OnUnknownStuff)
                    ONG_COMMAND(101, &CIFRank::OnUnknownStuff)
                    ONG_COMMAND(102, &CIFRank::OnUnknownStuff)
// ONG_COMMAND(103, &CIFRank::OnUnknownStuff)
// ONG_COMMAND(104, &CIFRank::OnUnknownStuff)
//  ONG_COMMAND(105, &CIFRank::OnUnknownStuff)
                    ONG_COMMAND(GDR_Thief_BTNNew, &CIFRank::OnThiefRank)
                    ONG_COMMAND(GDR_Hunter_BTN, &CIFRank::OnHunterRank)
                    ONG_COMMAND(GDR_Trader_BTN, &CIFRank::OnTraderRank)
GFX_END_MESSAGE_MAP()


std::vector<CIFRank::RankStruct> CIFRank::UniquesRankList;
std::vector<CIFRank::RankStruct> CIFRank::HonorRankList;
std::vector<CIFRank::RankStruct> CIFRank::JobTraderRank;
std::vector<CIFRank::RankStruct> CIFRank::JobHunterRank;
std::vector<CIFRank::RankStruct> CIFRank::JobRankTFList;

bool CIFRank::OnCreate(long ln)
{

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);
    SetText(L"Ranking");
    TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);


    wnd_rect sz;
    sz.pos.x= 13;
    sz.pos.y = 72;
    sz.size.width = 356;
    sz.size.height = 268;
    tile = (CIFNormalTile*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFNormalTile), sz, GDR_RANKS_BG, 0);
    tile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_b.ddj", 0, 0);

    sz.pos.x= 8;
    sz.pos.y = 67;
    sz.size.width = 366;
    sz.size.height = 278;
    frame = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), sz, GDR_RANKS_FRAME, 0);
    frame->TB_Func_13("interface\\inventory\\int_window_", 0, 0);


    sz.pos.x = 20;
    sz.pos.y = 78;
    sz.size.width = 341;
    sz.size.height = 234;
    blacksquare = (CIFStretchWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStretchWnd), sz, GDR_RANKS_BLACKSQUARE, 0);
    blacksquare->SetEdgeTextures("interface\\ifcommon\\com_blacksquare_right_side.ddj", "interface\\ifcommon\\com_blacksquare_left_up.ddj",
                                 "interface\\ifcommon\\com_blacksquare_left_side.ddj", "interface\\ifcommon\\com_blacksquare_left_up.ddj");



    sz.pos.x = 21;
    sz.pos.y = 78;
    sz.size.width = 55;
    sz.size.height = 24;
    rank_label = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANKS_RANK_LABEL, 0);
    rank_label->SetText(L"Rank");
    rank_label->TB_Func_13("interface\\guild\\gil_subj_button10.ddj", 1, 1);


    sz.pos.x = 76;
    sz.pos.y = 78;
    sz.size.width = 107;
    sz.size.height = 24;
    name_label = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANKS_NAME_LABEL, 0);
    name_label->SetText(L"Name");
    name_label->TB_Func_13("interface\\guild\\gil_subj_button10.ddj", 1, 1);



    sz.pos.x = 183;
    sz.pos.y = 78;
    sz.size.width = 112;
    sz.size.height = 24;
    guild_label = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANKS_GUILD_LABEL, 0);
    guild_label->SetText(L"Guild");
    guild_label->TB_Func_13("interface\\guild\\gil_subj_button10.ddj", 1, 1);


    sz.pos.x = 295;
    sz.pos.y = 78;
    sz.size.width = 65;
    sz.size.height = 24;
    point_label = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANKS_POINT_LABEL, 0);
    point_label->SetText(L"Kill");
    point_label->TB_Func_13("interface\\guild\\gil_subj_button10.ddj", 1, 1);


    RECT Framerect = { 17,45,180,185 };
    RECT Lablerect = { 16,308,480,62 };
    RECT Buttrect = { 70,318,16,16 };
    RECT Butt2rect = { 50,318,16,16 };
    RECT Butt3rect = { 30,318,16,16 };
    RECT Butt1rect = { 26,76,50,23 };
    RECT Butt12rect = { 72,76,140,23 };
    RECT Butt4rect = { 208,76,120,23 };
    RECT Butt13rect = { 317,76,64,23 };
    RECT Spinrect = { 164,316,50,16 };

    RECT label5rect = { 28,316,20,20 };
    RECT label6rect = { 48,316,20,20 };
    RECT label7rect = { 68,316,20,20 };
    m_custom_label5 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), label5rect, GDR_Trader_BTN, 0);
    m_custom_label5->TB_Func_13("interface\\durabilityerror\\broken.ddj", 0, 0);


    m_custom_label6 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), label6rect, GDR_Hunter_BTN, 0);
    m_custom_label6->TB_Func_13("interface\\durabilityerror\\broken.ddj", 0, 0);


    m_custom_label7 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), label7rect, GDR_Thief_BTN, 0);
    m_custom_label7->TB_Func_13("interface\\durabilityerror\\broken.ddj", 0, 0);




    m_mybutton2 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Butt2rect, GDR_Hunter_BTN, 0);
    m_mybutton3 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Butt3rect, GDR_Trader_BTN, 0);
    m_mybutton5 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Buttrect, GDR_Thief_BTNNew, 0);

    m_spin = (CIFSpinControl*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSpinControl), Spinrect, 4, 0);


    m_mybutton5->TB_Func_13("icon\\etc\\thiefgui.ddj", 0, 0);
    m_mybutton2->TB_Func_13("icon\\etc\\huntergui.ddj", 0, 0);
    m_mybutton3->TB_Func_13("icon\\etc\\tradergui.ddj", 0, 0);




    m_pTabs = new CIFSelectableArea * [numberOfTabs];

    for (int i = 0; i < numberOfTabs; i++) {

        RECT selectable_area_size;
        selectable_area_size.top = 44;
        selectable_area_size.left = 20;
        // selectable_area_size.left = tabMarginLeft + tabWidth * i;
        selectable_area_size.right = tabWidth + 1;
        selectable_area_size.bottom = tabHeight;

        m_pTabs[i] = (CIFSelectableArea*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSelectableArea),
                                                               selectable_area_size, tabFirstId + i, 0);
        m_pTabs[i]->SetFont(this->N00009C2F);


        m_pTabs[i]->sub_64CE30("interface\\ifcommon\\com_long_tab_on.ddj",
                               "interface\\ifcommon\\com_long_tab_off.ddj", "interface\\ifcommon\\com_long_tab_disable.ddj");

        switch (i) {
            case 0:
                m_pTabs[0]->sub_64CC30(1);
                break;
            case 1:
                m_pTabs[1]->MoveGWnd(m_pTabs[0]->GetPos().x + m_pTabs[0]->GetSize().width, m_pTabs[0]->GetPos().y);
                m_pTabs[1]->sub_64CC30(3);
                break;
            case 2:
                m_pTabs[2]->MoveGWnd(m_pTabs[1]->GetPos().x + m_pTabs[1]->GetSize().width, m_pTabs[0]->GetPos().y);
                m_pTabs[2]->sub_64CC30(0);
                break;
            case 3:
                m_pTabs[3]->MoveGWnd(m_pTabs[2]->GetPos().x + m_pTabs[2]->GetSize().width, m_pTabs[0]->GetPos().y);
                m_pTabs[3]->sub_64CE30("interface\\ifcommon\\com_long_tab_disable.ddj",
                                       "interface\\ifcommon\\com_long_tab_disable.ddj", "interface\\ifcommon\\com_long_tab_disable.ddj");
                break;
            case 4:
                m_pTabs[4]->MoveGWnd(m_pTabs[3]->GetPos().x + m_pTabs[3]->GetSize().width, m_pTabs[0]->GetPos().y);
                m_pTabs[4]->sub_64CE30("interface\\ifcommon\\com_long_tab_disable.ddj",
                                       "interface\\ifcommon\\com_long_tab_disable.ddj", "interface\\ifcommon\\com_long_tab_disable.ddj");
                break;
            case 5:
                m_pTabs[5]->MoveGWnd(m_pTabs[4]->GetPos().x + m_pTabs[4]->GetSize().width, m_pTabs[0]->GetPos().y);
                m_pTabs[5]->sub_64CE30("interface\\ifcommon\\com_long_tab_disable.ddj",
                                       "interface\\ifcommon\\com_long_tab_disable.ddj", "interface\\ifcommon\\com_long_tab_disable.ddj");
                break;
        }
    }

    m_title->SetText(L"Dynamic Ranking");
    m_pTabs[0]->SetText(L"Unique");//--
    m_pTabs[1]->SetText(L"Honor");
    m_pTabs[2]->SetText(L"Job");//--
    m_pTabs[3]->SetText(L"Custom");//--
    m_pTabs[4]->SetText(L"Custom");//--
    m_pTabs[5]->SetText(L"Custom");

    RECT rect = { 0,0,0,0 };
    m_slot1 = (CIFRankList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFRankList), rect, 40, 0);
    m_slot2 = (CIFRankList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFRankList), rect, 41, 0);
    m_slot3 = (CIFRankList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFRankList), rect, 42, 0);
    m_slot4 = (CIFRankList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFRankList), rect, 43, 0);
    m_slot5 = (CIFRankList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFRankList), rect, 44, 0);

    HideLists();
    m_slot1->ShowGWnd(true);
    m_slot1->MoveGWnd(m_slot1->GetPos().x + 7, m_slot1->GetPos().y + 24);
    m_slot2->MoveGWnd(m_slot2->GetPos().x + 7, m_slot2->GetPos().y + 24);
    m_slot3->MoveGWnd(m_slot3->GetPos().x + 7, m_slot3->GetPos().y + 24);
    m_slot4->MoveGWnd(m_slot4->GetPos().x + 7, m_slot4->GetPos().y + 24);
    m_slot5->MoveGWnd(m_slot5->GetPos().x + 7, m_slot5->GetPos().y + 24);

    m_spin->SetMinValue(1);
    m_spin->SetCurrentValue(1);
    m_spin->SetMaxValue(10);
    m_spin->ShowGWnd(true);

    m_mybutton5->ShowGWnd(false);
    m_mybutton2->ShowGWnd(false);
    m_mybutton3->ShowGWnd(false);
    m_custom_label5->ShowGWnd(false);
    m_custom_label6->ShowGWnd(false);
    m_custom_label7->ShowGWnd(false);

    this->ShowGWnd(false);
    UpdateMenuSize();
    return true;
}

void CIFRank::UpdateMenuSize()
{
    const ClientResolutonData& res = CGame::GetClientDimensionStuff();
    MoveGWnd(((res.width - GetSize().width) - 400), GetPos().y);
    BringToFront();

}

void CIFRank::OnUnknownStuff() {
    int id = GetIDOfInterfaceUnderCursor();
    int i = 0;

    for (int i = 0; i < numberOfTabs; ++i) {
        if (id == m_pTabs[i]->UniqueID()) {
            ActivateTabPage(i);
            return;
        }
    }
}

void CIFRank::ActivateTabPage(BYTE page) {

    for (int i = 0; i < numberOfTabs; i++) {
        if (i == page)
            continue;

        m_pTabs[i]->sub_64CC30(0);
    }

    m_pTabs[page]->sub_64CC30(1);

    //job hiden buttons
    if (page == 2)
    {
        m_mybutton5->ShowGWnd(true);
        m_mybutton2->ShowGWnd(true);
        m_mybutton3->ShowGWnd(true);
        m_custom_label5->ShowGWnd(true);
        m_custom_label6->ShowGWnd(false);
        m_custom_label7->ShowGWnd(false);

    }
    else
    {
        m_mybutton5->ShowGWnd(false);
        m_mybutton2->ShowGWnd(false);
        m_mybutton3->ShowGWnd(false);
        m_custom_label5->ShowGWnd(false);
        m_custom_label6->ShowGWnd(false);
        m_custom_label7->ShowGWnd(false);
    }


    switch (page)
    {
        case 0:
        {

            point_label->SetText(L"Point");
            Clear();
            CIFRank::UniquesRankList.clear();
            byte uniquerank = 6;
            SendPacket(uniquerank);

            UpdateUniqueRank();
            m_spin->m_Ranklogpage = 1;
            m_spin->m_valueCurrent = 1;
            ShowList(m_spin->m_Ranklogpage);
            m_spin->SetCurrentValue(1);
            m_spin->UpdateText();
        }
        break;
        
        case 1:
        {

            point_label->SetText(L"Point");
            Clear();
            CIFRank::HonorRankList.clear();
            byte honorrank = 7;
            SendPacket(honorrank);
            UpdateHonorRank();
            m_spin->m_Ranklogpage = 1;
            m_spin->m_valueCurrent = 1;
            ShowList(m_spin->m_Ranklogpage);
            m_spin->SetCurrentValue(1);
            m_spin->UpdateText();
        }
            break;
        case 2:
        {

            point_label->SetText(L"Exp");
            Clear();
            CIFRank::JobTraderRank.clear();
            byte jobrank = 8;
            SendPacket(jobrank);
            UpdateTraderRank();
            m_spin->m_Ranklogpage = 1;
            m_spin->m_valueCurrent = 1;
            ShowList(m_spin->m_Ranklogpage);
            m_spin->SetCurrentValue(1);
            m_spin->UpdateText();
        }
            break;
        case 3:
            point_label->SetText(L"P");
            Clear();
            break;
        case 4:
            point_label->SetText(L"P");
            Clear();
            break;
        case 5:
            point_label->SetText(L"P");
            Clear();
            break;
    }
}

void CIFRank::Clear()
{
    m_slot1->line1->m_custom_label2->ShowGWnd(false);
    m_slot1->line2->m_custom_label2->ShowGWnd(false);
    m_slot1->line3->m_custom_label2->ShowGWnd(false);
    m_slot1->line4->m_custom_label2->ShowGWnd(false);
    m_slot1->line5->m_custom_label2->ShowGWnd(false);

    m_slot1->line11->m_custom_label2->ShowGWnd(false);
    m_slot2->line11->m_custom_label2->ShowGWnd(false);
    m_slot3->line11->m_custom_label2->ShowGWnd(false);
    m_slot4->line11->m_custom_label2->ShowGWnd(false);
    m_slot5->line11->m_custom_label2->ShowGWnd(false);

    m_slot1->line1->WriteLine(L"", L"", L"", L"");
    m_slot1->line2->WriteLine(L"", L"", L"", L"");
    m_slot1->line3->WriteLine(L"", L"", L"", L"");
    m_slot1->line4->WriteLine(L"", L"", L"", L"");
    m_slot1->line5->WriteLine(L"", L"", L"", L"");
    m_slot1->line6->WriteLine(L"", L"", L"", L"");
    m_slot1->line7->WriteLine(L"", L"", L"", L"");
    m_slot1->line8->WriteLine(L"", L"", L"", L"");
    m_slot1->line9->WriteLine(L"", L"", L"", L"");
    m_slot1->line10->WriteLine(L"", L"", L"", L"");
    m_slot1->line11->WriteLine(L"", L"", L"", L"");
    m_slot2->line1->WriteLine(L"", L"", L"", L"");
    m_slot2->line2->WriteLine(L"", L"", L"", L"");
    m_slot2->line3->WriteLine(L"", L"", L"", L"");
    m_slot2->line4->WriteLine(L"", L"", L"", L"");
    m_slot2->line5->WriteLine(L"", L"", L"", L"");
    m_slot2->line6->WriteLine(L"", L"", L"", L"");
    m_slot2->line7->WriteLine(L"", L"", L"", L"");
    m_slot2->line8->WriteLine(L"", L"", L"", L"");
    m_slot2->line9->WriteLine(L"", L"", L"", L"");
    m_slot2->line10->WriteLine(L"", L"", L"", L"");
    m_slot2->line11->WriteLine(L"", L"", L"", L"");
    m_slot3->line1->WriteLine(L"", L"", L"", L"");
    m_slot3->line2->WriteLine(L"", L"", L"", L"");
    m_slot3->line3->WriteLine(L"", L"", L"", L"");
    m_slot3->line4->WriteLine(L"", L"", L"", L"");
    m_slot3->line5->WriteLine(L"", L"", L"", L"");
    m_slot3->line6->WriteLine(L"", L"", L"", L"");
    m_slot3->line7->WriteLine(L"", L"", L"", L"");
    m_slot3->line8->WriteLine(L"", L"", L"", L"");
    m_slot3->line9->WriteLine(L"", L"", L"", L"");
    m_slot3->line10->WriteLine(L"", L"", L"", L"");
    m_slot3->line11->WriteLine(L"", L"", L"", L"");
    m_slot4->line1->WriteLine(L"", L"", L"", L"");
    m_slot4->line2->WriteLine(L"", L"", L"", L"");
    m_slot4->line3->WriteLine(L"", L"", L"", L"");
    m_slot4->line4->WriteLine(L"", L"", L"", L"");
    m_slot4->line5->WriteLine(L"", L"", L"", L"");
    m_slot4->line6->WriteLine(L"", L"", L"", L"");
    m_slot4->line7->WriteLine(L"", L"", L"", L"");
    m_slot4->line8->WriteLine(L"", L"", L"", L"");
    m_slot4->line9->WriteLine(L"", L"", L"", L"");
    m_slot4->line10->WriteLine(L"", L"", L"", L"");
    m_slot4->line11->WriteLine(L"", L"", L"", L"");
    m_slot5->line1->WriteLine(L"", L"", L"", L"");
    m_slot5->line2->WriteLine(L"", L"", L"", L"");
    m_slot5->line3->WriteLine(L"", L"", L"", L"");
    m_slot5->line4->WriteLine(L"", L"", L"", L"");
    m_slot5->line5->WriteLine(L"", L"", L"", L"");
    m_slot5->line6->WriteLine(L"", L"", L"", L"");
    m_slot5->line7->WriteLine(L"", L"", L"", L"");
    m_slot5->line8->WriteLine(L"", L"", L"", L"");
    m_slot5->line9->WriteLine(L"", L"", L"", L"");
    m_slot5->line10->WriteLine(L"", L"", L"", L"");
    m_slot5->line11->WriteLine(L"", L"", L"", L"");
}

void CIFRank::ShowList(BYTE listid)
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
    }
}

void CIFRank::WriteLineOwn(const wchar_t* Num, const wchar_t* Charname, const wchar_t* Guild, const wchar_t* Points)
{
    m_slot1->line11->WriteLine(Num, Charname, Guild, Points);
    m_slot1->line11->m_custom_label3->SetText(Charname);
    m_slot1->line11->m_custom_label4->SetText(Guild);
    m_slot1->line11->m_custom_label5->SetText(Points);

    m_slot1->line11->m_custom_label1->m_FontTexture.SetColor(0x00FF00);
    m_slot1->line11->m_custom_label3->m_FontTexture.SetColor(0x00FF00);
    m_slot1->line11->m_custom_label4->m_FontTexture.SetColor(0x00FF00);
    m_slot1->line11->m_custom_label5->m_FontTexture.SetColor(0x00FF00);
    //
    m_slot2->line11->WriteLine(Num, Charname, Guild, Points);

    m_slot2->line11->m_custom_label1->m_FontTexture.SetColor(0x00FF00);
    m_slot2->line11->m_custom_label3->m_FontTexture.SetColor(0x00FF00);
    m_slot2->line11->m_custom_label4->m_FontTexture.SetColor(0x00FF00);
    m_slot2->line11->m_custom_label5->m_FontTexture.SetColor(0x00FF00);
    //
    m_slot3->line11->WriteLine(Num, Charname, Guild, Points);

    m_slot3->line11->m_custom_label1->m_FontTexture.SetColor(0x00FF00);
    m_slot3->line11->m_custom_label3->m_FontTexture.SetColor(0x00FF00);
    m_slot3->line11->m_custom_label4->m_FontTexture.SetColor(0x00FF00);
    m_slot3->line11->m_custom_label5->m_FontTexture.SetColor(0x00FF00);
    //
    m_slot4->line11->WriteLine(Num, Charname, Guild, Points);

    m_slot4->line11->m_custom_label1->m_FontTexture.SetColor(0x00FF00);
    m_slot4->line11->m_custom_label3->m_FontTexture.SetColor(0x00FF00);
    m_slot4->line11->m_custom_label4->m_FontTexture.SetColor(0x00FF00);
    m_slot4->line11->m_custom_label5->m_FontTexture.SetColor(0x00FF00);
    //
    m_slot5->line11->WriteLine(Num, Charname, Guild, Points);
    m_slot5->line11->m_custom_label1->m_FontTexture.SetColor(0x00FF00);
    m_slot5->line11->m_custom_label3->m_FontTexture.SetColor(0x00FF00);
    m_slot5->line11->m_custom_label4->m_FontTexture.SetColor(0x00FF00);
    m_slot5->line11->m_custom_label5->m_FontTexture.SetColor(0x00FF00);
}

void CIFRank::UpdateUniqueRank()
{
    for (std::vector<CIFRank::RankStruct>::iterator it = CIFRank::UniquesRankList.begin(); it != CIFRank::UniquesRankList.end(); ++it)
    {
        if (wcscmp((*it).Charname.c_str(), g_pCICPlayer->GetCharName().c_str()) == 0)
        {
            std::ostringstream ss;
            ss << (*it).LineNum;
            WriteLineOwn(TO_WSTRING(ss.str()).c_str(), (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
        }
        switch ((*it).LineNum)
        {
            case 1:
            {
                m_slot1->line1->WriteLine(L"1", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine(L"2", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine(L"3", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine(L"4", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine(L"5", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine(L"6", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine(L"7", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 8:
            {
                m_slot1->line8->WriteLine(L"8", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 9:
            {
                m_slot1->line9->WriteLine(L"9", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 10:
            {
                m_slot1->line10->WriteLine(L"10", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line1->WriteLine(L"11", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line2->WriteLine(L"12", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line3->WriteLine(L"13", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line4->WriteLine(L"14", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 15:
            {
                m_slot2->line5->WriteLine(L"15", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 16:
            {
                m_slot2->line6->WriteLine(L"16", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 17:
            {
                m_slot2->line7->WriteLine(L"17", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 18:
            {
                m_slot2->line8->WriteLine(L"18", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 19:
            {
                m_slot2->line9->WriteLine(L"19", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 20:
            {
                m_slot2->line10->WriteLine(L"20", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line1->WriteLine(L"21", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 22:
            {
                m_slot3->line2->WriteLine(L"22", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 23:
            {
                m_slot3->line3->WriteLine(L"23", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 24:
            {
                m_slot3->line4->WriteLine(L"24", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 25:
            {
                m_slot3->line5->WriteLine(L"25", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 26:
            {
                m_slot3->line6->WriteLine(L"26", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 27:
            {
                m_slot3->line7->WriteLine(L"27", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 28:
            {
                m_slot3->line8->WriteLine(L"28", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 29:
            {
                m_slot3->line9->WriteLine(L"29", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 30:
            {
                m_slot3->line10->WriteLine(L"30", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 31:
            {
                m_slot4->line1->WriteLine(L"31", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 32:
            {
                m_slot4->line2->WriteLine(L"32", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 33:
            {
                m_slot4->line3->WriteLine(L"33", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 34:
            {
                m_slot4->line4->WriteLine(L"34", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 35:
            {
                m_slot4->line5->WriteLine(L"35", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 36:
            {
                m_slot4->line6->WriteLine(L"36", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 37:
            {
                m_slot4->line7->WriteLine(L"37", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 38:
            {
                m_slot4->line8->WriteLine(L"38", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 39:
            {
                m_slot4->line9->WriteLine(L"39", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 40:
            {
                m_slot4->line10->WriteLine(L"40", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 41:
            {
                m_slot5->line1->WriteLine(L"41", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 42:
            {
                m_slot5->line2->WriteLine(L"42", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 43:
            {
                m_slot5->line3->WriteLine(L"43", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 44:
            {
                m_slot5->line4->WriteLine(L"44", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 45:
            {
                m_slot5->line5->WriteLine(L"45", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 46:
            {
                m_slot5->line6->WriteLine(L"46", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 47:
            {
                m_slot5->line7->WriteLine(L"47", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 48:
            {
                m_slot5->line8->WriteLine(L"48", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 49:
            {
                m_slot5->line9->WriteLine(L"49", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 50:
            {
                m_slot5->line10->WriteLine(L"50", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
        }
    }
}


void CIFRank::UpdateHonorRank()
{
    for (std::vector<CIFRank::RankStruct>::iterator it = CIFRank::HonorRankList.begin(); it != CIFRank::HonorRankList.end(); ++it)
    {
        if (wcscmp((*it).Charname.c_str(), g_pCICPlayer->GetCharName().c_str()) == 0)
        {
            std::ostringstream ss;
            ss << (*it).LineNum;
            WriteLineOwn(TO_WSTRING(ss.str()).c_str(), (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
        }

        switch ((*it).LineNum)
        {
            case 1:
            {
                m_slot1->line1->WriteLine(L"1", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine(L"2", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine(L"3", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine(L"4", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine(L"5", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine(L"6", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine(L"7", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 8:
            {
                m_slot1->line8->WriteLine(L"8", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 9:
            {
                m_slot1->line9->WriteLine(L"9", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 10:
            {
                m_slot1->line10->WriteLine(L"10", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line1->WriteLine(L"11", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line2->WriteLine(L"12", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line3->WriteLine(L"13", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line4->WriteLine(L"14", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 15:
            {
                m_slot2->line5->WriteLine(L"15", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 16:
            {
                m_slot2->line6->WriteLine(L"16", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 17:
            {
                m_slot2->line7->WriteLine(L"17", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 18:
            {
                m_slot2->line8->WriteLine(L"18", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 19:
            {
                m_slot2->line9->WriteLine(L"19", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 20:
            {
                m_slot2->line10->WriteLine(L"20", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line1->WriteLine(L"21", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 22:
            {
                m_slot3->line2->WriteLine(L"22", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 23:
            {
                m_slot3->line3->WriteLine(L"23", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 24:
            {
                m_slot3->line4->WriteLine(L"24", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 25:
            {
                m_slot3->line5->WriteLine(L"25", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 26:
            {
                m_slot3->line6->WriteLine(L"26", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 27:
            {
                m_slot3->line7->WriteLine(L"27", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 28:
            {
                m_slot3->line8->WriteLine(L"28", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 29:
            {
                m_slot3->line9->WriteLine(L"29", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 30:
            {
                m_slot3->line10->WriteLine(L"30", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 31:
            {
                m_slot4->line1->WriteLine(L"31", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 32:
            {
                m_slot4->line2->WriteLine(L"32", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 33:
            {
                m_slot4->line3->WriteLine(L"33", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 34:
            {
                m_slot4->line4->WriteLine(L"34", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 35:
            {
                m_slot4->line5->WriteLine(L"35", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 36:
            {
                m_slot4->line6->WriteLine(L"36", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 37:
            {
                m_slot4->line7->WriteLine(L"37", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 38:
            {
                m_slot4->line8->WriteLine(L"38", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 39:
            {
                m_slot4->line9->WriteLine(L"39", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 40:
            {
                m_slot4->line10->WriteLine(L"40", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 41:
            {
                m_slot5->line1->WriteLine(L"41", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 42:
            {
                m_slot5->line2->WriteLine(L"42", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 43:
            {
                m_slot5->line3->WriteLine(L"43", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 44:
            {
                m_slot5->line4->WriteLine(L"44", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 45:
            {
                m_slot5->line5->WriteLine(L"45", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 46:
            {
                m_slot5->line6->WriteLine(L"46", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 47:
            {
                m_slot5->line7->WriteLine(L"47", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 48:
            {
                m_slot5->line8->WriteLine(L"48", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 49:
            {
                m_slot5->line9->WriteLine(L"49", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 50:
            {
                m_slot5->line10->WriteLine(L"50", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
        }
    }
}


void CIFRank::UpdateJobThiefRank()
{
    for (std::vector<CIFRank::RankStruct>::iterator it = CIFRank::JobRankTFList.begin(); it != CIFRank::JobRankTFList.end(); ++it)
    {
        if (wcscmp((*it).Charname.c_str(), g_pCICPlayer->GetCharName().c_str()) == 0)
        {
            std::ostringstream ss;
            ss << (*it).LineNum;
            WriteLineOwn(TO_WSTRING(ss.str()).c_str(), (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
        }

        switch ((*it).LineNum)
        {
            case 1:
            {
                m_slot1->line1->WriteLine(L"1", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine(L"2", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine(L"3", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine(L"4", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine(L"5", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine(L"6", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine(L"7", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 8:
            {
                m_slot1->line8->WriteLine(L"8", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 9:
            {
                m_slot1->line9->WriteLine(L"9", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 10:
            {
                m_slot1->line10->WriteLine(L"10", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line1->WriteLine(L"11", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line2->WriteLine(L"12", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line3->WriteLine(L"13", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line4->WriteLine(L"14", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 15:
            {
                m_slot2->line5->WriteLine(L"15", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 16:
            {
                m_slot2->line6->WriteLine(L"16", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 17:
            {
                m_slot2->line7->WriteLine(L"17", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 18:
            {
                m_slot2->line8->WriteLine(L"18", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 19:
            {
                m_slot2->line9->WriteLine(L"19", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 20:
            {
                m_slot2->line10->WriteLine(L"20", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line1->WriteLine(L"21", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 22:
            {
                m_slot3->line2->WriteLine(L"22", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 23:
            {
                m_slot3->line3->WriteLine(L"23", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 24:
            {
                m_slot3->line4->WriteLine(L"24", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 25:
            {
                m_slot3->line5->WriteLine(L"25", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 26:
            {
                m_slot3->line6->WriteLine(L"26", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 27:
            {
                m_slot3->line7->WriteLine(L"27", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 28:
            {
                m_slot3->line8->WriteLine(L"28", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 29:
            {
                m_slot3->line9->WriteLine(L"29", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 30:
            {
                m_slot3->line10->WriteLine(L"30", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 31:
            {
                m_slot4->line1->WriteLine(L"31", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 32:
            {
                m_slot4->line2->WriteLine(L"32", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 33:
            {
                m_slot4->line3->WriteLine(L"33", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 34:
            {
                m_slot4->line4->WriteLine(L"34", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 35:
            {
                m_slot4->line5->WriteLine(L"35", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 36:
            {
                m_slot4->line6->WriteLine(L"36", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 37:
            {
                m_slot4->line7->WriteLine(L"37", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 38:
            {
                m_slot4->line8->WriteLine(L"38", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 39:
            {
                m_slot4->line9->WriteLine(L"39", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 40:
            {
                m_slot4->line10->WriteLine(L"40", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 41:
            {
                m_slot5->line1->WriteLine(L"41", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 42:
            {
                m_slot5->line2->WriteLine(L"42", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 43:
            {
                m_slot5->line3->WriteLine(L"43", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 44:
            {
                m_slot5->line4->WriteLine(L"44", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 45:
            {
                m_slot5->line5->WriteLine(L"45", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 46:
            {
                m_slot5->line6->WriteLine(L"46", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 47:
            {
                m_slot5->line7->WriteLine(L"47", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 48:
            {
                m_slot5->line8->WriteLine(L"48", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 49:
            {
                m_slot5->line9->WriteLine(L"49", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 50:
            {
                m_slot5->line10->WriteLine(L"50", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
        }
    }
}

void CIFRank::UpdateTraderRank()
{
    for (std::vector<CIFRank::RankStruct>::iterator it = CIFRank::JobTraderRank.begin(); it != CIFRank::JobTraderRank.end(); ++it)
    {
        if (wcscmp((*it).Charname.c_str(), g_pCICPlayer->GetJobAlias().c_str()) == 0)
        {
            std::ostringstream ss;
            ss << (*it).LineNum;
            WriteLineOwn(TO_WSTRING(ss.str()).c_str(), (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
        }

        switch ((*it).LineNum)
        {
            case 1:
            {

                m_slot1->line1->WriteLine(L"1", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());


            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine(L"2", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine(L"3", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine(L"4", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine(L"5", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine(L"6", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine(L"7", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 8:
            {
                m_slot1->line8->WriteLine(L"8", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 9:
            {
                m_slot1->line9->WriteLine(L"9", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 10:
            {
                m_slot1->line10->WriteLine(L"10", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line1->WriteLine(L"11", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line2->WriteLine(L"12", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line3->WriteLine(L"13", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line4->WriteLine(L"14", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 15:
            {
                m_slot2->line5->WriteLine(L"15", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 16:
            {
                m_slot2->line6->WriteLine(L"16", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 17:
            {
                m_slot2->line7->WriteLine(L"17", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 18:
            {
                m_slot2->line8->WriteLine(L"18", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 19:
            {
                m_slot2->line9->WriteLine(L"19", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 20:
            {
                m_slot2->line10->WriteLine(L"20", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line1->WriteLine(L"21", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 22:
            {
                m_slot3->line2->WriteLine(L"22", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 23:
            {
                m_slot3->line3->WriteLine(L"23", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 24:
            {
                m_slot3->line4->WriteLine(L"24", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 25:
            {
                m_slot3->line5->WriteLine(L"25", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 26:
            {
                m_slot3->line6->WriteLine(L"26", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 27:
            {
                m_slot3->line7->WriteLine(L"27", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 28:
            {
                m_slot3->line8->WriteLine(L"28", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 29:
            {
                m_slot3->line9->WriteLine(L"29", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 30:
            {
                m_slot3->line10->WriteLine(L"30", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 31:
            {
                m_slot4->line1->WriteLine(L"31", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 32:
            {
                m_slot4->line2->WriteLine(L"32", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 33:
            {
                m_slot4->line3->WriteLine(L"33", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 34:
            {
                m_slot4->line4->WriteLine(L"34", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 35:
            {
                m_slot4->line5->WriteLine(L"35", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 36:
            {
                m_slot4->line6->WriteLine(L"36", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 37:
            {
                m_slot4->line7->WriteLine(L"37", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 38:
            {
                m_slot4->line8->WriteLine(L"38", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 39:
            {
                m_slot4->line9->WriteLine(L"39", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 40:
            {
                m_slot4->line10->WriteLine(L"40", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 41:
            {
                m_slot5->line1->WriteLine(L"41", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 42:
            {
                m_slot5->line2->WriteLine(L"42", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 43:
            {
                m_slot5->line3->WriteLine(L"43", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 44:
            {
                m_slot5->line4->WriteLine(L"44", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 45:
            {
                m_slot5->line5->WriteLine(L"45", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 46:
            {
                m_slot5->line6->WriteLine(L"46", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 47:
            {
                m_slot5->line7->WriteLine(L"47", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 48:
            {
                m_slot5->line8->WriteLine(L"48", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 49:
            {
                m_slot5->line9->WriteLine(L"49", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 50:
            {
                m_slot5->line10->WriteLine(L"50", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
        }
    }
}

void CIFRank::UpdateHunterRank()
{
    for (std::vector<CIFRank::RankStruct>::iterator it = CIFRank::JobHunterRank.begin(); it != CIFRank::JobHunterRank.end(); ++it)
    {
        if (wcscmp((*it).Charname.c_str(), g_pCICPlayer->GetCharName().c_str()) == 0)
        {
            std::ostringstream ss;
            ss << (*it).LineNum;
            WriteLineOwn(TO_WSTRING(ss.str()).c_str(), (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
        }
        switch ((*it).LineNum)
        {
            case 1:
            {
                m_slot1->line1->WriteLine(L"1", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine(L"2", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine(L"3", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine(L"4", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine(L"5", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine(L"6", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine(L"7", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 8:
            {
                m_slot1->line8->WriteLine(L"8", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 9:
            {
                m_slot1->line9->WriteLine(L"9", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 10:
            {
                m_slot1->line10->WriteLine(L"10", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line1->WriteLine(L"11", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line2->WriteLine(L"12", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line3->WriteLine(L"13", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line4->WriteLine(L"14", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 15:
            {
                m_slot2->line5->WriteLine(L"15", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 16:
            {
                m_slot2->line6->WriteLine(L"16", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 17:
            {
                m_slot2->line7->WriteLine(L"17", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 18:
            {
                m_slot2->line8->WriteLine(L"18", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 19:
            {
                m_slot2->line9->WriteLine(L"19", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 20:
            {
                m_slot2->line10->WriteLine(L"20", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line1->WriteLine(L"21", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 22:
            {
                m_slot3->line2->WriteLine(L"22", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 23:
            {
                m_slot3->line3->WriteLine(L"23", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 24:
            {
                m_slot3->line4->WriteLine(L"24", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 25:
            {
                m_slot3->line5->WriteLine(L"25", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 26:
            {
                m_slot3->line6->WriteLine(L"26", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 27:
            {
                m_slot3->line7->WriteLine(L"27", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 28:
            {
                m_slot3->line8->WriteLine(L"28", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 29:
            {
                m_slot3->line9->WriteLine(L"29", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 30:
            {
                m_slot3->line10->WriteLine(L"30", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 31:
            {
                m_slot4->line1->WriteLine(L"31", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 32:
            {
                m_slot4->line2->WriteLine(L"32", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 33:
            {
                m_slot4->line3->WriteLine(L"33", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 34:
            {
                m_slot4->line4->WriteLine(L"34", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 35:
            {
                m_slot4->line5->WriteLine(L"35", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 36:
            {
                m_slot4->line6->WriteLine(L"36", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 37:
            {
                m_slot4->line7->WriteLine(L"37", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 38:
            {
                m_slot4->line8->WriteLine(L"38", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 39:
            {
                m_slot4->line9->WriteLine(L"39", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 40:
            {
                m_slot4->line10->WriteLine(L"40", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 41:
            {
                m_slot5->line1->WriteLine(L"41", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 42:
            {
                m_slot5->line2->WriteLine(L"42", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 43:
            {
                m_slot5->line3->WriteLine(L"43", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 44:
            {
                m_slot5->line4->WriteLine(L"44", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 45:
            {
                m_slot5->line5->WriteLine(L"45", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 46:
            {
                m_slot5->line6->WriteLine(L"46", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 47:
            {
                m_slot5->line7->WriteLine(L"47", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 48:
            {
                m_slot5->line8->WriteLine(L"48", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 49:
            {
                m_slot5->line9->WriteLine(L"49", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
            case 50:
            {
                m_slot5->line10->WriteLine(L"50", (*it).Charname.c_str(), (*it).Guild.c_str(), (*it).Points.c_str());
            }
                break;
        }
    }
}

bool CIFRank::IsPageFull(BYTE PageID, BYTE LineID)
{
    bool full = false;
    if (PageID == 1)
    {
        if (LineID == 30)
        {
            if (m_slot1->line1->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot1->line10->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 2)
    {
        if (LineID == 30)
        {
            if (m_slot2->line1->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot2->line10->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 3)
    {
        if (LineID == 30)
        {
            if (m_slot3->line1->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot3->line10->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 4)
    {
        if (LineID == 30)
        {
            if (m_slot4->line1->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot4->line10->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 5)
    {
        if (LineID == 30)
        {
            if (m_slot5->line1->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot5->line10->m_custom_label3->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    return full;
}

void CIFRank::OnUpdate()
{
    // o baþka aga ya :D o netprocess biliyom aga oraya kod yazmýþýn yüklenince boradan baþla diye her tkladýgýndada yükleniyor
    // bakaym
}

void CIFRank::SendPacket(byte type)
{
    CMsgStreamBuffer buf(0x180A);
    buf << type;
    SendMsg(buf);
}
void CIFRank::OnThiefRank()
{
    point_label->SetText(L"Exp");
    Clear();
    CIFRank::JobRankTFList.clear();
    byte thiefrank = 10;
    SendPacket(thiefrank);
    UpdateJobThiefRank();
    m_custom_label5->ShowGWnd(false);
    m_custom_label6->ShowGWnd(false);
    m_custom_label7->ShowGWnd(true);
}

void CIFRank::OnHunterRank()
{
    point_label->SetText(L"Exp");
    Clear();
    CIFRank::JobHunterRank.clear();
    byte hunterrank = 9;
    SendPacket(hunterrank);

    UpdateHunterRank();
    m_custom_label5->ShowGWnd(false);
    m_custom_label6->ShowGWnd(true);
    m_custom_label7->ShowGWnd(false);
}
void CIFRank::OnTraderRank()
{

    Clear();
    point_label->SetText(L"Exp");
    CIFRank::JobTraderRank.clear();
    byte traderrank = 8;
    SendPacket(traderrank);
    UpdateTraderRank();
    m_custom_label5->ShowGWnd(true);
    m_custom_label6->ShowGWnd(false);
    m_custom_label7->ShowGWnd(false);

}

void CIFRank::HideLists()
{
    m_slot1->ShowGWnd(false);
    m_slot2->ShowGWnd(false);
    m_slot3->ShowGWnd(false);
    m_slot4->ShowGWnd(false);
    m_slot5->ShowGWnd(false);
}