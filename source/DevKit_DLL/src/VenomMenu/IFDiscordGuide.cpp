
#include "IFDiscordGuide.h"
#include "GEffSoundBody.h"
#include "GInterface.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include "../../../DevKit_DLL/src/VenomMenu/IFFacebook.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFDiscord.h"
#include <BSLib/Debug.h>

GFX_IMPLEMENT_DYNCREATE(CIFDiscordGuide, CIFDecoratedStatic)

bool CIFDiscordGuide::OnCreate(long ln)
{
    BS_DEBUG_LOW("> " __FUNCTION__ "(%d)", ln);
    CIFDecoratedStatic::OnCreate(ln);

    TB_Func_13("icon\\etc\\discord_1.ddj", 0, 0);
    sub_634470("icon\\etc\\discord_2.ddj");

    set_N00009BD4(2);
    set_N00009BD3(500);
    RECT rect = { 0,0,40,40 };
    m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect, GUIDE_DC, 0);
    std::n_wstring msg(L"Discord Page Shortcut");
    m_custom_label1->SetTooltipText(&msg);
    m_custom_label1->SetToolTipSetting(0x80);

    return true;
}

int CIFDiscordGuide::OnMouseLeftUp(int a1, int x, int y)
{

    if(CIFFacebook::FBW->IsVisible())
    {
        CIFFacebook::FBW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }

    if(CIFDiscord::DCW->IsVisible())
    {
        CIFDiscord::DCW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else
    {
        CIFDiscord::DCW->ShowGWnd(true);
        CGEffSoundBody::get()->PlaySound(L"snd_window_open");
        CIFDiscord::DCW->UpdateMenuSize();
        CIFDiscord::DCW->BringToFront();
    }

    return 0;


}

void CIFDiscordGuide::OnCIFReady()
{
    BS_DEBUG_LOW("> " __FUNCTION__);

    CIFDecoratedStatic::OnCIFReady();
    sub_633990();

}

