
#include "IFChestGuide.h"
#include "GEffSoundBody.h"
#include "GInterface.h"
#include <Windows.h>
#include <string>
#include <iostream>
#include "../../../DevKit_DLL/src/VenomMenu/IFChest.h"
#include "../GameHelpers/GameMain.h"
#include <BSLib/Debug.h>
#include <GlobalDataManager.h>

GFX_IMPLEMENT_DYNCREATE(CIFChestGuide, CIFDecoratedStatic)
GFX_BEGIN_MESSAGE_MAP(CIFChestGuide, CIFWnd)
                    ONG_VISIBLE_CHANGE()
GFX_END_MESSAGE_MAP()


bool CIFChestGuide::OnCreate(long ln)
{
    CIFDecoratedStatic::OnCreate(ln);

    TB_Func_13("icon\\etc\\itemmall_1.ddj", 0, 0);
    sub_634470("icon\\etc\\itemmall_2.ddj");

    set_N00009BD4(2);
    set_N00009BD3(500);

    RECT rect = { 0,0,40,40 };
    m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect, GUIDE_CHEST, 0);
    std::n_wstring msg(L"Item Chest");
    m_custom_label1->SetTooltipText(&msg);
    m_custom_label1->SetToolTipSetting(0x80);

    return true;
}

int CIFChestGuide::OnMouseLeftUp(int a1, int x, int y)
{
    if(CIFPlayerChest::ChestW->IsVisible())
    {
        CIFPlayerChest::ChestW->ShowGWnd(false);
    }
    else
    {
        CGEffSoundBody::get()->PlaySound(L"snd_window_open");
        CIFPlayerChest::ChestW->ShowGWnd(true);
        CIFPlayerChest::ChestW->UpdateMenuSize();
        CIFPlayerChest::ChestW->BringToFront();
    }
    return 0;
}

void CIFChestGuide::OnCIFReady()
{
    CIFDecoratedStatic::OnCIFReady();
    sub_633990();

}

void CIFChestGuide::OnUpdate()
{
    g_pCGInterface->GetAlarmManager()->UpdatePositions();
}

int CIFChestGuide::OnVisibleStateChange(int newstate, int a2)
{
    return 0;
}