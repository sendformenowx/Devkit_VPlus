#include "IFTitleManagerSlot.h"
#include "IFMainMenu.h"
#include <ICPlayer.h>

GFX_IMPLEMENT_DYNCREATE(CIFTitleManagerSlot, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFTitleManagerSlot, CIFWnd)
GFX_END_MESSAGE_MAP()

CIFTitleManagerSlot::CIFTitleManagerSlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}

CIFTitleManagerSlot::~CIFTitleManagerSlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}

bool CIFTitleManagerSlot::OnCreate(long ln)
{
    //printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFWnd::OnCreate(ln);

    RECT rect1 = { 18,5,210,13 };
    m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect1, 0, 0);
    RECT rect2 = { 0,0,229,24 };
    bars = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), rect2, 5, 0);
    bars->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    m_custom_label1->MoveGWnd(GetPos().x + 5, m_custom_label1->GetPos().y);
    m_custom_label1->m_FontTexture.SetColor(0xffffff);

    m_custom_label1->BringToFront();

    this->ShowGWnd(false);
    return true;
}

int CIFTitleManagerSlot::OnMouseLeftUp(int a1, int x, int y) {

    printf("name: %ls\n", m_custom_label1->GetNText().c_str());
    CIFMainMenu::TitleW->ClearDDJ();
    if (m_custom_label1->GetNText().length() != 0)
    {
        CIFMainMenu::TitleW->m_custom_label6->SetText(m_custom_label1->GetNText().c_str());
        bars->TB_Func_13("interface\\ifcommon\\com_bar01select_", 1, 1);
        CIFTitleManager::selecttitlecolor = m_custom_label1->m_FontTexture.m_color_fg;
        CIFMainMenu::TitleW->owntitle->m_FontTexture.SetColor(m_custom_label1->m_FontTexture.m_color_fg);
        CIFMainMenu::TitleW->owntitle->SetText(m_custom_label1->GetNText().c_str());

    }
    else
    {
        CIFMainMenu::TitleW->m_custom_label6->SetText(m_custom_label1->GetNText().c_str());
    }
    return true;
}

void CIFTitleManagerSlot::SetName(const wchar_t* name,int color) {

        m_custom_label1->SetText(name);
        m_custom_label1->m_FontTexture.SetColor(color);

}

void CIFTitleManagerSlot::ClearDDJ()
{
    bars->TB_Func_13("interface\\ifcommon\\com_bar01_", 0, 0);
}