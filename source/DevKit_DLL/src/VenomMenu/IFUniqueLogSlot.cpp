#include "IFUniqueLogSlot.h"

#define GDR_UNIQUELOG_NAME 2
#define GDR_UNIQUELOG_STATE 3
#define GDR_UNIQUELOG_KILLER 4
#define GDR_UNIQUELOG_TIME 5

GFX_IMPLEMENT_DYNCREATE(CIFUniqueLogSlot, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFUniqueLogSlot, CIFWnd)
GFX_END_MESSAGE_MAP()



bool CIFUniqueLogSlot::OnCreate(long ln)
{

    // Populate inherited members
    CIFWnd::OnCreate(ln);

    RECT rect1 = { 29,5,149,14 };
    RECT rect2 = { 185,5,103,14 };
    RECT rect3 = { 259,5,60,14 };
    RECT rect4 = { 393,5,74,14 };

    m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect1, GDR_UNIQUELOG_NAME, 0);
    m_custom_label3 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect2, GDR_UNIQUELOG_STATE, 0);
    m_custom_label4 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect3, GDR_UNIQUELOG_KILLER, 0);

    m_custom_label2->MoveGWnd(GetPos().x + 5, m_custom_label2->GetPos().y-2);
    m_custom_label3->MoveGWnd(m_custom_label2->GetPos().x + m_custom_label2->GetSize().width + 9, m_custom_label3->GetPos().y-2);
    m_custom_label4->MoveGWnd(m_custom_label3->GetPos().x + m_custom_label3->GetSize().width + 8   , m_custom_label4->GetPos().y-2);


    m_custom_label2->m_FontTexture.SetColor(0xffffff);
    m_custom_label3->m_FontTexture.SetColor(0xffffff);
    m_custom_label4->m_FontTexture.SetColor(0xffffff);


    this->ShowGWnd(false);
    return true;
}


void CIFUniqueLogSlot::WriteLine(const wchar_t* UQName, const wchar_t* State, const wchar_t* Killer)
{
    m_custom_label2->SetText(UQName);
    m_custom_label3->SetText(Killer);
    m_custom_label4->SetText(State);

    if (wcscmp(State, L"<Alive>") == 0)
    {
        m_custom_label4->m_FontTexture.SetColor(0x00ff00);
    }
    else
        m_custom_label4->m_FontTexture.SetColor(0xeb345b);
}