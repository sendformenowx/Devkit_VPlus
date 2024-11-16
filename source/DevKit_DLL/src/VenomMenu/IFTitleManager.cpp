#include "IFTitleManager.h"
#include <NetProcessIn.h>
#include <ICPlayer.h>
#include "GInterface.h"
#include "TextStringManager.h"
#include "IFSystemMessage.h"
#include "Game.h"


#define GDR_TITLEMANAGER_BTN_APPLY 11
#define GDR_TITLEMANAGER_BTN_REMOVE 12
#define GDR_TITLEMANAGER_BOX 7
#define GDR_TITLEMANAGER_BOXNEW 8
#define CURRENT_NEW_TITLE 231

std::vector<CIFTitleManager::RankStruct> CIFTitleManager::TitleNameRankList;
std::vector<CIFTitleManager::RankStruct> CIFTitleManager::TapNameRankList;

std::vector<CIFTitleManager::ColorStruct> CIFTitleManager::TitleColor;

GFX_IMPLEMENT_DYNCREATE(CIFTitleManager, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFTitleManager, CIFMainFrame)
                    ONG_COMMAND(GDR_TITLEMANAGER_BTN_APPLY, &On_BtnClick)
                    ONG_COMMAND(GDR_TITLEMANAGER_BTN_REMOVE, &On_BtnClickRemove)
                    ONG_COMMAND(100, &CIFTitleManager::OnUnknownStuff)
GFX_END_MESSAGE_MAP()
int CIFTitleManager::Func_4(int a2) {
    int v1 = 0;
    while (a2 != v1 + 100) {
        if (++v1 >= 5)
            return -1;
    }

    return 100;
}

bool CIFTitleManager::OnCreate(long ln)
{
    // Populate inherited members
    CIFMainFrame::OnCreate(ln);
    m_title->SetText(L"Title Manager");
    TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);
    wnd_rect sz;

    sz.pos.x = 16;
    sz.pos.y = 66;
    sz.size.width = 457;
    sz.size.height = 209;
    tile = (CIFNormalTile*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFNormalTile), sz, 1, 1);
    tile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_b.ddj", 1, 1);

    sz.pos.x = 11;
    sz.pos.y = 61;
    sz.size.width = 468;
    sz.size.height = 219;
    frame[0] = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), sz, 5, 1);
    frame[0]->TB_Func_13("interface\\inventory\\int_window_", 0, 0);

    sz.pos.x = 11;
    sz.pos.y = 61;
    sz.size.width = 468;
    sz.size.height = 34;
    frame[1] = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), sz, 7, 1);
    frame[1]->TB_Func_13("interface\\inventory\\int_window_", 0, 0);


    sz.pos.x = 11;
    sz.pos.y = 91;
    sz.size.width = 468;
    sz.size.height = 189;
    frame[2] = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), sz, 6, 1);
    frame[2]->TB_Func_13("interface\\inventory\\int_window_", 0, 0);


    sz.pos.x = 20;
    sz.pos.y = 104;
    sz.size.width = 449;
    sz.size.height = 166;
    blacksquare = (CIFStretchWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStretchWnd), sz, 109, 0);
    blacksquare->SetEdgeTextures("interface\\ifcommon\\com_blacksquare_right_side.ddj", "interface\\ifcommon\\com_blacksquare_left_up.ddj",
                                 "interface\\ifcommon\\com_blacksquare_left_side.ddj", "interface\\ifcommon\\com_blacksquare_left_up.ddj");


    sz.pos.x = 268;
    sz.pos.y = 110;
    sz.size.width = 198;
    sz.size.height = 154;
    tile2 = (CIFNormalTile*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFNormalTile), sz, 160, 1);
    tile2->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_s.ddj", 1, 1);

    sz.pos.x = 101;
    sz.pos.y = 68;
    sz.size.width = 272;
    sz.size.height = 20;
    owntitle = (CIFEdit*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEdit), sz, 105, 0);
    owntitle->TB_Func_13("interface\\messagebox\\msgbox_blackbox_02.ddj", 0, 0);
    owntitle->TB_Func_5(1);
    owntitle->TB_Func_6(1);
    std::n_wstring msg2(L"Enter the custom title!");
    owntitle->SetTooltipText(&msg2);
    owntitle->SetToolTipSetting(0x80);


    owntitle->AddValue_404(5);
    owntitle->SetValue_404(2);
    owntitle->FUN_00634f80(12);
    wnd_rect bounds = owntitle->GetBounds();

    owntitle->SetTextmode(bounds.size.width);





    sz.pos.x = 101;
    sz.pos.y = 68;
    sz.size.width = 272;
    sz.size.height = 20;
    owntitlenew = (CIFEdit*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEdit), sz, CURRENT_NEW_TITLE, 1);
    owntitlenew->TB_Func_13("interface\\messagebox\\msgbox_blackbox_02.ddj", 0, 0);
    owntitlenew->TB_Func_5(1);
    owntitlenew->TB_Func_6(1);
    owntitlenew->SetTooltipText(&msg2);
    owntitlenew->SetToolTipSetting(0x80);


    owntitlenew->AddValue_404(5);
    owntitlenew->SetValue_404(2);
    owntitlenew->FUN_00634f80(12);
    wnd_rect bounds2 = owntitlenew->GetBounds();

    owntitlenew->SetTextmode(bounds.size.width);

    sz.pos.x = 20;
    sz.pos.y = 68;
    sz.size.width = 80;
    sz.size.height = 20;
    label[0] = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 106, 0);
    label[0]->SetText(L"Current Title : ");
    label[0]->m_FontTexture.SetColor(D3DCOLOR_ARGB(255, 239, 218, 164));

    sz.pos.x = 380;
    sz.pos.y = 65;
    sz.size.width = 90;
    sz.size.height = 24;
    removebtn = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, GDR_TITLEMANAGER_BTN_REMOVE, 0);
    removebtn->SetText(L"Use title");
    removebtn->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 1, 1);

    sz.pos.x = 22;
    sz.pos.y = 106;
    sz.size.width = 229;
    sz.size.height = 25;
    bars[1] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, 150, 0);
    bars[1]->TB_Func_13("interface\\ifcommon\\com_bar02_", 1, 1);
    bars[1]->SetText(L"Available Titles");

    // V VSCROLL
    sz.pos.x = 251;
    sz.pos.y = 106;
    sz.size.width = 16;
    sz.size.height = 25;
    label[1] = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 170, 0);
    label[1]->TB_Func_13("interface\\guild\\gil_shape.ddj", 1, 1);

    sz.pos.x = 267;
    sz.pos.y = 106;
    sz.size.width = 201;
    sz.size.height = 25;
    bars[2] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, 150, 0);
    bars[2]->TB_Func_13("interface\\ifcommon\\com_bar02_", 1, 1);
    bars[2]->SetText(L"Description");


    sz.pos.x = 22;
    sz.pos.y = 129;
    sz.size.width = 229;
    sz.size.height = 24;
    m_mybar[0] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, 200, 0);
    m_mybar[0]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x = 22;
    sz.pos.y = 152;
    sz.size.width = 229;
    sz.size.height = 24;
    m_mybar[1] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, 111, 0);
    m_mybar[1]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x = 22;
    sz.pos.y = 175;
    sz.size.width = 229;
    sz.size.height = 24;
    m_mybar[2] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, 112, 0);
    m_mybar[2]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);


    sz.pos.x = 22;
    sz.pos.y = 198;
    sz.size.width = 229;
    sz.size.height = 24;
    m_mybar[3] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, 113, 0);
    m_mybar[3]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x = 22;
    sz.pos.y = 221;
    sz.size.width = 229;
    sz.size.height = 24;
    m_mybar[4] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, 114, 0);
    m_mybar[4]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x = 22;
    sz.pos.y = 244;
    sz.size.width = 229;
    sz.size.height = 24;
    m_mybar[5] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, 115, 0);
    m_mybar[5]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x = 271;
    sz.pos.y = 244;
    sz.size.width = 196;
    sz.size.height = 24;
    usebtn = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, GDR_TITLEMANAGER_BTN_APPLY, 0);
    usebtn->SetText(L"Use Color");
    usebtn->TB_Func_13("interface\\messagebox\\msgbox_rebirth_button.ddj", 0, 0);

    sz.pos.x = 273;
    sz.pos.y = 176;
    sz.size.width = 190;
    sz.size.height = 20;
    m_custom_label6 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 1590, 1);
    m_custom_label6->TB_Func_6(0);
    m_custom_label6->TB_Func_5(0);

    sz.pos.x = 273;
    sz.pos.y = 132;
    sz.size.width = 190;
    sz.size.height = 80;
    my_textbox = (CIFTextBox*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFTextBox), sz, 1231, 1);
    my_textbox->SetText(L"When <Use Title> button is clicked, your title will be -");


    my_textbox->m_FontTexture.sub_8B4400(2, 2);
    my_textbox->m_FontTexture.sub_8B4750(2);
    my_textbox->TB_Func_5(0);
    my_textbox->TB_Func_6(0);

    sz.pos.x = 30;
    sz.pos.y = 129;
    sz.size.width = 229;
    sz.size.height = 140;
    m_scroll = (CIFScrollManager*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFScrollManager), sz, 160, 0);
    m_scroll->m_verticalScroll->SetUniqueID(10);
    m_scroll->sub_008124F0(0);
    m_scroll->sub_008124C0(0x17);
    m_scroll->sub_008123F0(6);
    m_scroll->sub_00812500(0);
    m_scroll->sub_00812420(-8, 0);




    sz.pos.x = 0;
    sz.pos.y = 0;
    sz.size.width = 229;
    sz.size.height = 24;
    for (int i = 1; i <= 50; ++i)
        m_slot[i] = (CIFTitleManagerSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFTitleManagerSlot), sz, 301, 0);


    m_pTabs = new CIFSelectableArea * [numberOfTabs];

    for (int i = 0; i < numberOfTabs; i++) {

        RECT selectable_area_size;
        selectable_area_size.top = 38;
        selectable_area_size.left = 16;
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
                m_pTabs[1]->MoveGWnd(m_pTabs[0]->GetPos().x + m_pTabs[0]->GetSize().width + 1, m_pTabs[0]->GetPos().y);
                m_pTabs[1]->sub_64CC30(0);
                break;
        }
    }

    m_pTabs[0]->SetText(L"Titles");
    m_pTabs[1]->SetText(L"iSro Titles");



 /*   CIFTitleManager::ColorStruct uqR = CIFTitleManager::ColorStruct();
    uqR.ID = 1;
    uqR.Color = 65280;
    TitleColor.push_back(uqR);
    uqR.ID = 2;
    uqR.Color = 65441;
    TitleColor.push_back(uqR);
    uqR.ID = 3;
    uqR.Color = 16728064;
    TitleColor.push_back(uqR);
    uqR.ID = 4;
    uqR.Color = 8421504;
    TitleColor.push_back(uqR);
    uqR.ID = 5;
    uqR.Color = 16776960;
    TitleColor.push_back(uqR);

    uqR.ID = 6;
    uqR.Color = 10776960;
    TitleColor.push_back(uqR);

    uqR.ID = 7;
    uqR.Color = 11776960;
    TitleColor.push_back(uqR);

    uqR.ID = 8;
    uqR.Color = 12776960;
    TitleColor.push_back(uqR);

    uqR.ID = 9;
    uqR.Color = 13776960;
    TitleColor.push_back(uqR);

    uqR.ID = 10;
    uqR.Color = 14776960;
    TitleColor.push_back(uqR);*/




    ActivateTabPage(0);

    this->ShowGWnd(false);
    UpdateMenuSize();
    return true;
}

void CIFTitleManager::OnUnknownStuff() {
    int id = GetIDOfInterfaceUnderCursor();
    int i = 0;

    for (int i = 0; i < numberOfTabs; ++i) {
        if (id == m_pTabs[i]->UniqueID()) {
            ActivateTabPage(i);
            return;
        }
    }
}
int PageStatus=0;

void CIFTitleManager::ActivateTabPage(BYTE page) {

    for (int i = 0; i < numberOfTabs; i++) {
        if (i == page)
            continue;

        m_pTabs[i]->sub_64CC30(0);
    }

    m_pTabs[page]->sub_64CC30(1);


    switch (page)
    {
        case 0:
            ClearDDJ();
            Clear();
            UpdateTitleName();
            owntitle->ShowGWnd(true);
            owntitlenew->ShowGWnd(false);
            m_custom_label6->SetText(L"");
            PageStatus = 0;
            break;
        case 1:
            ClearDDJ();
            Clear();
            UpdateTapName();
            owntitle->ShowGWnd(false);
            owntitlenew->ShowGWnd(true);
            m_custom_label6->SetText(L"");
            PageStatus = 1;
            break;
    }
}
wchar_t buffer2[255];
std::n_wstring mymsg2;

int CIFTitleManager::selecttitlecolor=0xFFFF00;
void CIFTitleManager::OnUpdate()
{
    //owntitle->m_FontTexture.SetColor(selecttitlecolor);
    //if(m_custom_label6->GetNText().empty())
    //{
    //    m_custom_label6->SetText(L"<Not Selected>");
    //}
    //std::n_wstring Test = g_pCICPlayer->GetTitleName();
    //wchar_t buffer1[255];
    //swprintf_s(buffer1, sizeof(buffer1), L"%s", Test.c_str());
    //std::n_wstring strmsgnew;
    //strmsgnew.assign(buffer1);

    //owntitle->SetText(strmsgnew.c_str());

    //if(Test.empty())
    //{
    //    owntitle->SetText(L"<No Title>");
    //}

   /* CLASSLINK_LOOP_BEGIN(CICUser)
        std::map<std::wstring, std::wstring>::iterator titledata = g_pCICPlayer->NewTitles.find(g_pCICPlayer->GetCharName().c_str());
        if (titledata != g_pCICPlayer->NewTitles.end())
        {
            swprintf_s(buffer2, sizeof(buffer2), L"<%s>", titledata->second.c_str(), g_pCICPlayer->GetCharName().c_str());
            mymsg2.assign(buffer2);
            owntitlenew->SetText(mymsg2.c_str());
        } else
        {
            owntitlenew->SetText(L"<No Title>");
        }
    CLASSLINK_LOOP_END(CICUser)*/
}

void CIFTitleManager::On_BtnClick() {
 
    if (PageStatus == 0) {
        int test = 0;
        CMsgStreamBuffer buf(0x3502);
        buf << test;
        buf << selecttitlecolor;
        SendMsg(buf);
    }
    if (PageStatus == 1) {
        int test = 1;
        CMsgStreamBuffer buf(0x3502);
        buf << test;
        buf << selecttitlecolor;
        SendMsg(buf);
    }
}
void CIFTitleManager::On_BtnClickRemove() {
    
    if (PageStatus==0) {
        int test = owntitle->GetCurrentText().length();

        if (test >= 2)
        {
            INT8 Status = 2;
            CMsgStreamBuffer buf(0x3501);
            buf << Status;
            buf << GET_OWN_GAME_ID();
            buf << TO_NSTRING(this->owntitle->GetCurrentText());
            SendMsg(buf);
            owntitle->SetText(L"");
        }
        else
        {
            g_pCGInterface->ShowMessage_Warning(L"Title name must contain more than 2 letters.");
            return;
        }
    }
    else  if (PageStatus == 1) {
        int test = owntitlenew->GetCurrentText().length();

        if (test >= 2)
        {
            INT8 Status = 3;
            CMsgStreamBuffer buf(0x3501);
            buf << Status;
            buf << GET_OWN_GAME_ID();
            buf << TO_NSTRING(this->owntitlenew->GetCurrentText());
            SendMsg(buf);
            owntitlenew->SetText(L"");
        }
        else
        {
            g_pCGInterface->ShowMessage_Warning(L"Title name must contain more than 2 letters.");
            return;
        }
    }


    //std::n_wstring mytitle = g_pCICPlayer->GetTitleName().c_str();
    //if (owntitle->IsVisible()) {
    //    if (mytitle.length() != 0)
    //    {
    //        BYTE REMOVE = 0;
    //        BYTE TYPE = 2;
    //        CMsgStreamBuffer buf(0x1201);
    //        buf << TYPE;
    //        buf << REMOVE;
    //        SendMsg(buf);
    //    }
    //}

    //if (owntitlenew->IsVisible()) {
    //    BYTE TYPE = 2;
    //    CMsgStreamBuffer bufx(0x1202);
    //    bufx << TYPE;
    //    SendMsg(bufx);
    //}

}
void CIFTitleManager::UpdateMenuSize()
{
    const ClientResolutonData &res = CGame::GetClientDimensionStuff();
    MoveGWnd(((res.width - GetSize().width) - 400), GetPos().y);
    BringToFront();

}

void CIFTitleManager::ClearDDJ() {
    for (int i = 1; i <= 50; ++i)
        m_slot[i]->ClearDDJ();
}

void CIFTitleManager::Clear()
{
    for (int i = 1; i <= 50; ++i)
    {
        m_slot[i]->SetText(L"");
        m_scroll->DeleteItem(m_slot[i]);
    }
}
std::n_wstring Costomtitlesaa;
void CIFTitleManager::UpdateTitleName()
{
    if (g_pCICPlayer)
    {
        std::n_wstring nwCharName = g_pCICPlayer->GetCharName();

        for (std::map<std::wstring, std::wstring>::iterator it = g_pCICPlayer->NewCostomTitle.begin(); it != g_pCICPlayer->NewCostomTitle.end(); ++it)
        {
            if (it->first == nwCharName.c_str())
            {
                Costomtitlesaa = it->second.c_str();
            }
        }
        if (Costomtitlesaa.length() <= 1)
            Costomtitlesaa = L"Title Color";
        int count=0;
            for (std::vector<CIFTitleManager::ColorStruct>::iterator it = CIFTitleManager::TitleColor.begin(); it != CIFTitleManager::TitleColor.end(); ++it)
        {
                count++;
            if (g_pCICPlayer)
            {
                if ((*it).Color > 0)
                {
                    m_slot[count]->SetName(Costomtitlesaa.c_str(), (*it).Color);
                    m_scroll->AddItem(m_slot[count], 1, 0);
                }
            }
        }
    }
}

void CIFTitleManager::UpdateTapName()
{

    if (g_pCICPlayer)
    {
        std::n_wstring nwCharName = g_pCICPlayer->GetCharName();

        for (std::map<std::wstring, std::wstring>::iterator it = g_pCICPlayer->NewCostomTitle.begin(); it != g_pCICPlayer->NewCostomTitle.end(); ++it)
        {
            if (it->first == nwCharName.c_str())
            {
                Costomtitlesaa = it->second.c_str();
            }
        }
        int count = 0;
        for (std::vector<CIFTitleManager::ColorStruct>::iterator it = CIFTitleManager::TitleColor.begin(); it != CIFTitleManager::TitleColor.end(); ++it)
        {
            if (g_pCICPlayer)
            {
                count++;
                m_slot[count]->SetName(nwCharName.c_str(), (*it).Color);
                m_scroll->AddItem(m_slot[count], 1, 0);
            }
        }
    }
}