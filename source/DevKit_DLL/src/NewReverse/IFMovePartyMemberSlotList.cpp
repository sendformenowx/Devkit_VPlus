#include "IFMovePartyMemberSlotList.h"


GFX_IMPLEMENT_DYNCREATE(CIFMovePartyMemberSlotList, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFMovePartyMemberSlotList, CIFWnd)
GFX_END_MESSAGE_MAP()


bool CIFMovePartyMemberSlotList::OnCreate(long ln)
{
    //printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFWnd::OnCreate(ln);
    wnd_rect sz;

    sz.pos.x= 16;
    sz.pos.y = 68;
    sz.size.width = 330;
    sz.size.height = 24;
    // m_mybar1 = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_CHEST_SLOT1, 0);
    //m_mybar1->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);
    line1 = (CIFMovePartyMemberSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFMovePartyMemberSlot), sz, 31, 0);
    line1->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0 ,0);


    sz.pos.x= 16;
    sz.pos.y = 91;
    sz.size.width = 330;
    sz.size.height = 24;
    // m_mybar2 = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_CHEST_SLOT2, 0);
    // m_mybar2->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);
    line2 = (CIFMovePartyMemberSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFMovePartyMemberSlot), sz, 31, 0);
    line2->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0 ,0);

    sz.pos.x= 16;
    sz.pos.y = 114;
    sz.size.width = 330;
    sz.size.height = 24;
    //m_mybar3 = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_CHEST_SLOT3, 0);
    //m_mybar3->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);


    line3 = (CIFMovePartyMemberSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFMovePartyMemberSlot), sz, 31, 0);
    line3->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0 ,0);


    sz.pos.x= 16;
    sz.pos.y = 137;
    sz.size.width = 330;
    sz.size.height = 24;
    // m_mybar4 = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_CHEST_SLOT4, 0);
    //m_mybar4->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);
    line4 = (CIFMovePartyMemberSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFMovePartyMemberSlot), sz, 31, 0);
    line4->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0 ,0);


    sz.pos.x= 16;
    sz.pos.y = 160;
    sz.size.width = 330;
    sz.size.height = 24;
    //m_mybar5 = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_CHEST_SLOT5, 0);
    //m_mybar5->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);

    line5 = (CIFMovePartyMemberSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFMovePartyMemberSlot), sz, 31, 0);
    line5->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0 ,0);

    sz.pos.x= 16;
    sz.pos.y = 183;
    sz.size.width = 330;
    sz.size.height = 24;
    //m_mybar6 = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_CHEST_SLOT6, 0);
    //m_mybar6->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);
    line6 = (CIFMovePartyMemberSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFMovePartyMemberSlot), sz, 31, 0);
    line6->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0 ,0);

    sz.pos.x= 16;
    sz.pos.y = 206;
    sz.size.width = 330;
    sz.size.height = 24;
    //m_mybar7 = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_CHEST_SLOT7, 0);
    //m_mybar7->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);
    line7 = (CIFMovePartyMemberSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFMovePartyMemberSlot), sz, 31, 0);
    line7->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0 ,0);

    sz.pos.x= 16;
    sz.pos.y = 229;
    sz.size.width = 330;
    sz.size.height = 24;
    //  m_mybar8 = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_CHEST_SLOT8, 0);
    // m_mybar8->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);
    line8 = (CIFMovePartyMemberSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFMovePartyMemberSlot), sz, 31, 0);
    line8->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0 ,0);




    line1->ShowGWnd(true);
    line2->ShowGWnd(true);
    line3->ShowGWnd(true);
    line4->ShowGWnd(true);
    line5->ShowGWnd(true);
    line6->ShowGWnd(true);
    line7->ShowGWnd(true);
    line8->ShowGWnd(false);


    line1->BringToFront();
    line2->BringToFront();
    line3->BringToFront();
    line4->BringToFront();
    line5->BringToFront();
    line6->BringToFront();
    line7->BringToFront();




    this->ShowGWnd(false);
    return true;

}

void CIFMovePartyMemberSlotList::OnUpdate()
{
}

void CIFMovePartyMemberSlotList::ClearDDJ()
{
    line1->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0 ,0);
    line2->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0 ,0);
    line3->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0 ,0);
    line4->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0 ,0);;
    line5->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0 ,0);
    line6->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0 ,0);
    line7->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0 ,0);
    line8->TB_Func_13("interface\\guild\\gil_bar02_deselect.ddj", 0 ,0);
}
