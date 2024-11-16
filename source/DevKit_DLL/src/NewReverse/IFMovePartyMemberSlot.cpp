#include "IFMovePartyMemberSlot.h"
#include <ctime>
#include <GInterface.h>
#include "IFChatViewer.h"
#include "IFSystemMessage.h"
#include "../VenomMenu/IFMainMenu.h"
#include <ClientNet\MsgStreamBuffer.h>
#include <ICPlayer.h>


GFX_IMPLEMENT_DYNCREATE(CIFMovePartyMemberSlot, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFMovePartyMemberSlot, CIFWnd)
GFX_END_MESSAGE_MAP()

CIFMovePartyMemberSlot::CIFMovePartyMemberSlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}

CIFMovePartyMemberSlot::~CIFMovePartyMemberSlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}

bool CIFMovePartyMemberSlot::OnCreate(long ln)
{
    //printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFWnd::OnCreate(ln);

    RECT recttest = { 9,5,20,13 };
    RECT rect1 = { 9,5,324,13 };
    RECT rect2 = { 340,5,64,13 };
    RECT rect3 = { 420,5,138,13 };
    RECT rect4 = { 570,5,80,13 };

    m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), recttest, 1, 0);
    m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect1, 2, 0);
    m_custom_label3 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect2, 3, 0);
    m_custom_label4 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect3, 4, 0);
    m_custom_label5 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), rect4, 5, 0);
    m_custom_label6 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), recttest, 6, 0);


    m_custom_label1->m_FontTexture.SetColor(0xffffff);
    m_custom_label2->m_FontTexture.SetColor(0xffffff);
    m_custom_label3->m_FontTexture.SetColor(0xffffff);
    m_custom_label4->m_FontTexture.SetColor(0xffffff);
    m_custom_label5->m_FontTexture.SetColor(0xffffff);
    m_custom_label6->m_FontTexture.SetColor(0xffffff);

    m_custom_label1->BringToFront();
    m_custom_label2->BringToFront();
    m_custom_label3->BringToFront();
    m_custom_label4->BringToFront();
    m_custom_label5->BringToFront();
    m_custom_label6->BringToFront();


    m_custom_label1->ShowGWnd(false);
    m_custom_label2->ShowGWnd(true);
    m_custom_label3->ShowGWnd(true);
    m_custom_label4->ShowGWnd(true);
    m_custom_label5->ShowGWnd(true);
    m_custom_label6->ShowGWnd(true);


    this->ShowGWnd(true);
    BringToFront();
    return true;
}

void CIFMovePartyMemberSlot::WriteLine(const wchar_t* fakenum, int num, const wchar_t* CharName)
{
    wchar_t number[10];
    swprintf_s(number, L"%d", num+1);

    m_custom_label6->SetText(fakenum);
    if (num == 9)
    {
        m_custom_label6->SetText(L"");
    }
    m_custom_label1->SetText(number);
    m_custom_label2->SetText(CharName);

    if(CharName == g_pCICPlayer->GetCharName())
    {

    }

}

int CIFMovePartyMemberSlot::OnMouseLeftUp(int a1, int x, int y)
{
    if (!m_custom_label2->GetNText().empty())
    {
        CIFMainMenu::MoveParty->ClearDDJ();
        CIFMainMenu::MoveParty->SelectedItemName = m_custom_label2->GetNText();
        TB_Func_13("interface\\guild\\gil_bar02_select.ddj", 1  ,2);
    }
    return 0;
}

