#include "IFRankSlot.h"

#define GDR_SLOT_RANK_NUMBER 1
#define GXVSRO_SLOT_UNIQUELOG_NUM_PIC 2
#define GDR_SLOT_RANK_NAME 3
#define GDR_SLOT_RANK_GUILD 5
#define GDRO_SLOT_RANK_POINTKILL 6

GFX_IMPLEMENT_DYNCREATE(CIFRankSlot, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFRankSlot, CIFWnd)
GFX_END_MESSAGE_MAP()


bool CIFRankSlot::OnCreate(long ln)
{
    // Populate inherited members
    CIFWnd::OnCreate(ln);

    RECT rect0 = { 5,5,46,15 };
    RECT rect1 = { 5,5,46,15 };
    RECT rect2 = { 57,5,102,15 };
    RECT rect3 = { 165,5,108,15 };
    RECT rect4 = { 276,5,60,15 };

    m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect0, GDR_SLOT_RANK_NUMBER, 0);
    m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect1, GXVSRO_SLOT_UNIQUELOG_NUM_PIC, 0);
    m_custom_label3 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect2, GDR_SLOT_RANK_NAME, 0);
    m_custom_label4 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect3, GDR_SLOT_RANK_GUILD, 0);
    m_custom_label5 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect4, GDRO_SLOT_RANK_POINTKILL, 0);



    m_custom_label1->m_FontTexture.SetColor(0xffffff);
    m_custom_label2->m_FontTexture.SetColor(0xffffff);
    m_custom_label3->m_FontTexture.SetColor(0xffffff);
    m_custom_label4->m_FontTexture.SetColor(0xffffff);
    m_custom_label5->m_FontTexture.SetColor(0xffffff);
    m_custom_label2->ShowGWnd(false);
    ShowGWnd(true);
    return true;
}

void CIFRankSlot::OnUpdate()
{
}

void CIFRankSlot::WriteLine(const wchar_t* num, const wchar_t* Charname, const wchar_t* Guild, const wchar_t* Points)
{
    m_custom_label1->SetText(num);
    m_custom_label3->SetText(Charname);
    m_custom_label4->SetText(Guild);
    m_custom_label5->SetText(Points);
}

void CIFRankSlot::ShowIcon()
{
    m_custom_label2->ShowGWnd(true);
}