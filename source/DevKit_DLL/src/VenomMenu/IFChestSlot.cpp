#include "IFChestSlot.h"
#include <ctime>
#include <GInterface.h>
#include "IFChatViewer.h"
#include "IFSystemMessage.h"
#include <ClientNet\MsgStreamBuffer.h>
#include <ICPlayer.h>
#include "IFChest.h"
#include "IFMainMenu.h"


GFX_IMPLEMENT_DYNCREATE(CIFPlayerChestSlot, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFPlayerChestSlot, CIFWnd)
GFX_END_MESSAGE_MAP()

CIFPlayerChestSlot::CIFPlayerChestSlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}

CIFPlayerChestSlot::~CIFPlayerChestSlot(void)
{
    //printf("> " __FUNCTION__ "\n");
}

bool CIFPlayerChestSlot::OnCreate(long ln)
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

void CIFPlayerChestSlot::WriteLine(const wchar_t* fakenum, const wchar_t* num, const wchar_t* ItemName, const wchar_t* Count, const wchar_t* From, const wchar_t* Date)
{

    m_custom_label6->SetText(fakenum);
    m_custom_label1->SetText(num);
    m_custom_label2->SetText(ItemName);
    m_custom_label3->SetText(Count);
    m_custom_label4->SetText(From);
    m_custom_label5->SetText(Date);
}

int CIFPlayerChestSlot::OnMouseLeftUp(int a1, int x, int y)
{
    if (!m_custom_label1->GetNText().empty())
    {
        CIFPlayerChest::ChestW->ClearDDJ();
        CIFPlayerChest::ChestW->SelectedItemName = m_custom_label1->GetNText();
        TB_Func_13("interface\\guild\\gil_bar02_select.ddj", 1  ,2);
        // CIFPlayerChest::ChestW->Take->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    }
    return 0;
}

