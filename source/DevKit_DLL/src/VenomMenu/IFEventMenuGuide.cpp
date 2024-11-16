
#include "IFEventMenuGuide.h"
#include "GEffSoundBody.h"
#include "GInterface.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include "../../../DevKit_DLL/src/VenomMenu/IFEventMenu.h"
#include <BSLib/Debug.h>

GFX_IMPLEMENT_DYNCREATE(CIFEventMenuGuide, CIFDecoratedStatic)

bool CIFEventMenuGuide::OnCreate(long ln)
{
    CIFDecoratedStatic::OnCreate(ln);


    TB_Func_13("icon\\etc\\bugle_icon_1.ddj", 0, 0);
    sub_634470("icon\\etc\\bugle_icon_2.ddj");

    set_N00009BD4(2);
    set_N00009BD3(500);

    RECT rect = { 0,0,40,40 };
    m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect, GUIDE_EVENTS, 0);
    std::n_wstring msg(L"Event Register Menu");
    m_custom_label1->SetTooltipText(&msg);
    m_custom_label1->SetToolTipSetting(0x80);



    return true;
}

int CIFEventMenuGuide::OnMouseLeftUp(int a1, int x, int y)
{
    if( CIFEventMenu::EventW->IsVisible())
    {
        CIFEventMenu::EventW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else
    {
        CIFEventMenu::EventW->ShowGWnd(true);
        CGEffSoundBody::get()->PlaySound(L"snd_window_open");
        CIFEventMenu::EventW->UpdateMenuSize();
        CIFEventMenu::EventW->BringToFront();
        CMsgStreamBuffer buf(0x180A);
        byte type = 11;
        buf << type;
        SendMsg(buf);
    }

    return 0;

}

void CIFEventMenuGuide::OnCIFReady()
{
    CIFDecoratedStatic::OnCIFReady();
    sub_633990();

}