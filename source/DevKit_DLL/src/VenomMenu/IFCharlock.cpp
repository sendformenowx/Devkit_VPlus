#include "IFCharlock.h"
#include "GInterface.h"
#include <IFSystemMessage.h>
#include "ICPlayer.h"
#include <Game.h>
#include <StdAfx.h>


#define GDR_CHARLOCK_LOCK 11
#define GDR_CHARLOCK_UNLOCK 12


GFX_IMPLEMENT_DYNCREATE(CIFCharlock, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFCharlock, CIFMainFrame)
                    ONG_COMMAND(GDR_CHARLOCK_LOCK, &On_BtnClick)
                    ONG_COMMAND(GDR_CHARLOCK_UNLOCK, &On_BtnClickUnlock)
GFX_END_MESSAGE_MAP()


bool CIFCharlock::OnCreate(long ln)
{
    // Populate inherited members
    CIFMainFrame::OnCreate(ln);
    SetText(L"Character Lock");
    TB_Func_13("interface\\messagebox\\msgbox2_window_", 0, 0);

    wnd_rect sz;
    sz.pos.x= 16;
    sz.pos.y = 40;
    sz.size.width = 325;
    sz.size.height = 28;
    m_mytile1 = (CIFNormalTile* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFNormalTile), sz, 1, 1);
    m_mytile1->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_b.ddj", 0, 0);


    sz.pos.x= 16;
    sz.pos.y = 93;
    sz.size.width = 325;
    sz.size.height = 46;
    m_mytile2 = (CIFNormalTile* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFNormalTile), sz, 2, 1);
    m_mytile2->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_b.ddj", 0, 0);


    sz.pos.x= 20;
    sz.pos.y = 68;
    sz.size.width = 317;
    sz.size.height = 27;
    m_mytile3 = (CIFNormalTile* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFNormalTile), sz, 3, 1);
    m_mytile3->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_e.ddj", 0, 0);


    sz.pos.x= 16;
    sz.pos.y = 66;
    sz.size.width = 325;
    sz.size.height = 30;
    m_myname = (CIFEdit*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEdit), sz,4, 0);
    m_myname->TB_Func_13("interface\\messagebox\\msgbox_blackbox_02.ddj", 0, 0);
    m_myname->TB_Func_5(1);
    m_myname->TB_Func_6(1);
    std::n_wstring msg2(L"Enter the password!");
    m_myname->SetTooltipText(&msg2);
    m_myname->SetToolTipSetting(0x80);

    m_myname->AddValue_404(1);
    m_myname->FUN_00634f80(4);
    wnd_rect bounds = m_myname->GetBounds();

    m_myname->SetTextmode(bounds.size.width);




    sz.pos.x= 26;
    sz.pos.y = 43;
    sz.size.width = 302;
    sz.size.height = 25;
    m_custom_label = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 5, 0);



    sz.pos.x= 89;
    sz.pos.y = 105;
    sz.size.width = 75;
    sz.size.height = 25;
    m_mybutton = (CIFButton*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, GDR_CHARLOCK_UNLOCK, 0);
    m_mybutton -> SetText(L"Unlock");
    m_mybutton->TB_Func_13("interface\\system\\sys_button.ddj", 0, 0);


    sz.pos.x= 178;
    sz.pos.y = 105;
    sz.size.width = 75;
    sz.size.height = 25;
    m_mybutton2 = (CIFButton*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, GDR_CHARLOCK_LOCK, 0);
    m_mybutton2 -> SetText(L"Lock");
    m_mybutton2->TB_Func_13("interface\\system\\sys_button.ddj", 0, 0);


    this->ShowGWnd(false);

    UpdateMenuSize();

    return true;
}

void CIFCharlock::OnUpdate()
{
    std::n_wstring input_textnew = g_pCICPlayer ->m_charname.c_str();
    std::n_wstring ItemName = L"Enter the password to address [" + input_textnew + L"]";

    m_custom_label->SetText(ItemName.c_str());
        
}


void CIFCharlock::On_BtnClick() {
    std::n_wstring input_text = m_myname->GetCurrentText();
    if (input_text.length() != 4) {
        wchar_t message[] = L"Your password must consist of 4 digits.";
        g_pCGInterface->ShowMessage_Warning(L"Your password must consist of 4 digits.");
        CIFSystemMessage *systemmessage = reinterpret_cast<CIFSystemMessage *>(g_pCGInterface->m_IRM.GetResObj(68, 1));
        int color = D3DCOLOR_ARGB(255, 239, 218, 164);
        systemmessage->WriteMessage(0xFF, color, message, 0, 1);
    } else {

        std::n_wstring input_text = m_myname->GetCurrentText();
        CMsgStreamBuffer buf(0x1318);

        buf << std::n_string(TO_NSTRING(this->m_myname->GetCurrentText()));
        buf << std::n_string("!lock");
        SendMsg(buf);
        m_myname->SetText(L"");

    }
}
void CIFCharlock::On_BtnClickUnlock() {
    std::n_wstring input_text = m_myname->GetCurrentText();
    if (input_text.length() != 4) 
    {
        g_pCGInterface->ShowMessage_Warning(L"Enter your 4 digit password.");
        return;
    }
    else {
        std::n_wstring input_text = m_myname->GetCurrentText();
        CMsgStreamBuffer buf(0x1318);

        buf << std::n_string(TO_NSTRING(this->m_myname->GetCurrentText()));
        buf << std::n_string("!unlock");
        SendMsg(buf);
        m_myname->SetText(L"");
    }
}


void CIFCharlock::UpdateMenuSize()
{
    const ClientResolutonData &res = CGame::GetClientDimensionStuff();
    MoveGWnd(((res.width - GetSize().width) - 400), GetPos().y);
    BringToFront();

}
