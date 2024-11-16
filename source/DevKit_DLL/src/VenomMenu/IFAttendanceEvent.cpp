
#include "IFAttendanceEvent.h"
#include "GEffSoundBody.h"
#include "GInterface.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include "../../../DevKit_DLL/src/VenomMenu/IFAttendance.h"
#include <BSLib/Debug.h>

GFX_IMPLEMENT_DYNCREATE(CIFAttendanceEventGuide, CIFDecoratedStatic)

bool CIFAttendanceEventGuide::OnCreate(long ln)
{
    CIFDecoratedStatic::OnCreate(ln);

    TB_Func_13("icon\\etc\\summer_event_calendar.ddj", 0, 0);
    sub_634470("icon\\etc\\summer_event_calendar.ddj");

    set_N00009BD4(2);
    set_N00009BD3(500);
    RECT rect = { 0,0,40,40 };

    m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect, GUIDE_ATTENDANCE, 0);
    std::n_wstring msg(L"Attendance Event");
    m_custom_label1->SetTooltipText(&msg);
    m_custom_label1->SetToolTipSetting(0x80);


    return true;
}

int CIFAttendanceEventGuide::OnMouseLeftUp(int a1, int x, int y)
{

    if( CIFAttendance::ATTW->IsVisible())
    {
        CIFAttendance::ATTW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else
    {
        CIFAttendance::ATTW->ShowGWnd(true);
        CGEffSoundBody::get()->PlaySound(L"snd_window_open");
        CIFAttendance::ATTW->ActivateTabPage(0);
        CIFAttendance::ATTW->BringToFront();

    }

    return 0;


}

void CIFAttendanceEventGuide::OnCIFReady()
{
    CIFDecoratedStatic::OnCIFReady();
    sub_633990();

}