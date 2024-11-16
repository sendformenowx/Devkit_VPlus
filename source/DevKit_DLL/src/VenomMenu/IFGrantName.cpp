#include "IFGrantName.h"
#include <Game.h>
#include <StdAfx.h>
#include <NetProcessIn.h>
#include <CharacterDependentData.h>
#include "GInterface.h"
#include "ICPlayer.h"
#include "../Network/CPSMission.h"


#define GDR_GRANTNAME_BTN_APPLY 11
#define GDR_GRANTNAME_WRITE 10
#define GDR_GRANTNAME_BG3 52
#define GDR_GRANTNAME_BG2 51
#define GDR_GRANTNAME_BG1 50
#define GDR_GRANTNAME_LABEL 53


GFX_IMPLEMENT_DYNCREATE(CIFGrantName, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFGrantName, CIFMainFrame)
                    ONG_COMMAND(GDR_GRANTNAME_BTN_APPLY, &On_BtnClick)
GFX_END_MESSAGE_MAP()


bool CIFGrantName::OnCreate(long ln)
{

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);
    m_title->SetText(L"Change Grant Name");

    TB_Func_13("interface\\messagebox\\msgbox2_window_", 0, 0);
    wnd_rect sz;


    sz.pos.x= 16;
    sz.pos.y = 40;
    sz.size.width = 325;
    sz.size.height = 28;
    m_mytile1 = (CIFNormalTile* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFNormalTile), sz, GDR_GRANTNAME_BG1, 1);
    m_mytile1->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_b.ddj", 0, 0);


    sz.pos.x= 16;
    sz.pos.y = 93;
    sz.size.width = 325;
    sz.size.height = 46;
    m_mytile2 = (CIFNormalTile* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFNormalTile), sz, GDR_GRANTNAME_BG2, 1);
    m_mytile2->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_b.ddj", 0, 0);


    sz.pos.x= 20;
    sz.pos.y = 68;
    sz.size.width = 317;
    sz.size.height = 27;
    m_mytile3 = (CIFNormalTile* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFNormalTile), sz, GDR_GRANTNAME_BG3, 1);
    m_mytile3->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_e.ddj", 0, 0);

    sz.pos.x= 16;
    sz.pos.y = 66;
    sz.size.width = 325;
    sz.size.height = 30;
    m_myname = (CIFEdit*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEdit), sz,GDR_GRANTNAME_WRITE, 0);
    m_myname->TB_Func_13("interface\\messagebox\\msgbox_blackbox_02.ddj", 0, 0);
    m_myname->TB_Func_5(1);
    m_myname->TB_Func_6(1);
    std::n_wstring msg2(L"Enter the grant name!");
    m_myname->SetTooltipText(&msg2);
    m_myname->SetToolTipSetting(0x80);


    m_myname->AddValue_404(5);
    m_myname->SetValue_404(2);
    m_myname->FUN_00634f80(12);
    wnd_rect bounds = m_myname->GetBounds();

    m_myname->SetTextmode(bounds.size.width);


    sz.pos.x= 26;
    sz.pos.y = 43;
    sz.size.width = 302;
    sz.size.height = 25;
    m_custom_label = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_GRANTNAME_LABEL, 0);


    sz.pos.x= 142;
    sz.pos.y = 105;
    sz.size.width = 75;
    sz.size.height = 25;
    m_mybutton = (CIFButton*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, GDR_GRANTNAME_BTN_APPLY, 0);
    m_mybutton -> SetText(L"Confirm");
    m_mybutton->TB_Func_13("interface\\system\\sys_button.ddj", 0, 0);


    this->ShowGWnd(false);
    UpdateMenuSize();
    return true;
}


void CIFGrantName::UpdateMenuSize()
{
    const ClientResolutonData &res = CGame::GetClientDimensionStuff();
    MoveGWnd(((res.width - GetSize().width) - 400), GetPos().y);
    BringToFront();

}


void CIFGrantName::OnUpdate()
{
    std::n_wstring input_textnew = g_pCICPlayer ->m_charname.c_str();
    std::n_wstring ItemName = L"Enter the grant name to address [" + input_textnew + L"]";

    m_custom_label->SetText(ItemName.c_str());

}

void CIFGrantName::On_BtnClick()
{
    std::n_wstring guildname2 = g_pCICPlayer->GetGuildName().c_str();
    if (guildname2.empty())
    {
        g_pCGInterface->ShowMessage_Warning(L"You need join a guild first.");
        return;
    }
    if (m_myname->GetCurrentText().length() != 2)
    {
        INT8 Status = 1;
        CMsgStreamBuffer buf(0x3501);
        buf << Status;
        buf << GET_OWN_GAME_ID();
        buf << TO_NSTRING(this->m_myname->GetCurrentText());
        SendMsg(buf);
        m_myname->SetText(L"");
    }
    else
    {
        g_pCGInterface->ShowMessage_Warning(L"Grant name must contain more than 2 letters.");
        return;
    }
}
