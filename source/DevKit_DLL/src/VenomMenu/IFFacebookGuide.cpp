
#include "IFFacebookGuide.h"
#include "GEffSoundBody.h"
#include "GInterface.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include "../../../DevKit_DLL/src/VenomMenu/IFFacebook.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFDiscord.h"
#include <BSLib/Debug.h>

GFX_IMPLEMENT_DYNCREATE(CIFFacebookGuide, CIFDecoratedStatic)

bool CIFFacebookGuide::OnCreate(long ln)
{
    CIFDecoratedStatic::OnCreate(ln);

    TB_Func_13("icon\\etc\\facebook_1.ddj", 0, 0);
    sub_634470("icon\\etc\\facebook_2.ddj");

    set_N00009BD4(2);
    set_N00009BD3(500);

    RECT rect = { 0,0,40,40 };

    m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect, GUIDE_FACEBOOK, 0);
    std::n_wstring msg(L"Facebook Page Shortcut");
    m_custom_label1->SetTooltipText(&msg);
    m_custom_label1->SetToolTipSetting(0x80);
    return true;
}

int CIFFacebookGuide::OnMouseLeftUp(int a1, int x, int y)
{

    if(CIFDiscord::DCW->IsVisible())
    {
        CIFDiscord::DCW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }

    if(CIFFacebook::FBW->IsVisible())
    {
        CIFFacebook::FBW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else
    {
        CIFFacebook::FBW->ShowGWnd(true);
        CGEffSoundBody::get()->PlaySound(L"snd_window_open");
        CIFFacebook::FBW->UpdateMenuSize();
        CIFFacebook::FBW->BringToFront();
    }

    return 0;

}

void CIFFacebookGuide::OnCIFReady()
{
    CIFDecoratedStatic::OnCIFReady();
    sub_633990();
}