#include "IFMainMenuGuide.h"
#include <BSLib/Debug.h>
#include "GEffSoundBody.h"
#include "GInterface.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFMainMenu.h"
#include "Game.h"
GFX_IMPLEMENT_DYNCREATE(CIFMainMenuGuide, CIFDecoratedStatic)


bool CIFMainMenuGuide::OnCreate(long ln)
{
    CIFDecoratedStatic::OnCreate(ln);

    TB_Func_13("icon\\etc\\webgacha2_1.ddj", 0, 0);
    sub_634470("icon\\etc\\webgacha2_2.ddj");
    set_N00009BD4(2);
    set_N00009BD3(500);

    RECT rect = { 0,0,40,40 };
    m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect, GUIDE_MAINMENU, 0);
    std::n_wstring msg(L"Main Menu");
    m_custom_label1->SetTooltipText(&msg);
    m_custom_label1->SetToolTipSetting(0x80);


    //CGWndBase::wnd_rect magicstateboard = g_pCGInterface->m_IRM.GetResObj(22, 1)->GetBounds();
    //CIFWnd* wind = g_pCGInterface->m_IRM.GetResObj(22, 1);


    //const ClientResolutonData& res = CGame::GetClientDimensionStuff();
    //wind->MoveGWnd(((res.width - (magicstateboard.pos.x) + 20)), magicstateboard.pos.y);

    return true;
}

int CIFMainMenuGuide::OnMouseLeftUp(int a1, int x, int y)
{

    if(CIFMainMenu::MenuW->IsVisible())
    {
        CIFMainMenu::MenuW->ShowGWnd(false);
    }
    else
    {
        CGEffSoundBody::get()->PlaySound(L"snd_window_open");
        CIFMainMenu::MenuW->ShowGWnd(true);
        CIFMainMenu::MenuW->UpdateMenuSize();
        CIFMainMenu::MenuW->BringToFront();
    }
    return 0;
}

void CIFMainMenuGuide::OnCIFReady()
{
    CIFDecoratedStatic::OnCIFReady();
    sub_633990();
}
