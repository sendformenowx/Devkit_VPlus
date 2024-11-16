#include "IFRankList.h"


#define GDR_RANKS_SLOT1 25
#define GDR_RANKS_SLOT2 26
#define GDR_RANKS_SLOT3 27
#define GDR_RANKS_SLOT4 28
#define GDR_RANKS_SLOT5 29
#define GDR_RANKS_SLOT6 30
#define GDR_RANKS_SLOT7 31
#define GDR_RANKS_SLOT8 32
#define GDR_RANKS_SLOT9 33
#define GDR_RANKS_SLOT10 34
#define GDR_RANKS_SLOT11 35


GFX_IMPLEMENT_DYNCREATE(CIFRankList, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFRankList, CIFWnd)
GFX_END_MESSAGE_MAP()

bool CIFRankList::OnCreate(long ln)
{
    // Populate inherited members
    CIFWnd::OnCreate(ln);
    wnd_rect sz;

    sz.pos.x= 14;
    sz.pos.y = 76;
    sz.size.width = 339;
    sz.size.height = 20;
    bars[0] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_RANKS_SLOT1, 0);
    bars[0]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);


    sz.pos.x= 14;
    sz.pos.y = 95;
    sz.size.width = 339;
    sz.size.height = 20;
    bars[1] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_RANKS_SLOT2, 0);
    bars[1]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x= 14;
    sz.pos.y = 114;
    sz.size.width = 339;
    sz.size.height = 20;
    bars[2] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_RANKS_SLOT3, 0);
    bars[2]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x= 14;
    sz.pos.y = 133;
    sz.size.width = 339;
    sz.size.height = 20;
    bars[3] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_RANKS_SLOT4, 0);
    bars[3]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);


    sz.pos.x= 14;
    sz.pos.y = 152;
    sz.size.width = 339;
    sz.size.height = 20;
    bars[4] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_RANKS_SLOT5, 0);
    bars[4]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);


    sz.pos.x= 14;
    sz.pos.y = 171;
    sz.size.width = 339;
    sz.size.height = 20;
    bars[5] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_RANKS_SLOT6, 0);
    bars[5]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);


    sz.pos.x= 14;
    sz.pos.y = 190;
    sz.size.width = 339;
    sz.size.height = 20;
    bars[6] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_RANKS_SLOT7, 0);
    bars[6]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);


    sz.pos.x= 14;
    sz.pos.y = 209;
    sz.size.width = 339;
    sz.size.height = 20;
    bars[7] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_RANKS_SLOT8, 0);
    bars[7]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);


    sz.pos.x= 14;
    sz.pos.y = 228;
    sz.size.width = 339;
    sz.size.height = 20;
    bars[8] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_RANKS_SLOT9, 0);
    bars[8]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);


    sz.pos.x= 14;
    sz.pos.y = 247;
    sz.size.width = 339;
    sz.size.height = 20;
    bars[9] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_RANKS_SLOT10, 0);
    bars[9]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);


    sz.pos.x= 14;
    sz.pos.y = 266;
    sz.size.width = 339;
    sz.size.height = 20;
    bars[10] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_RANKS_SLOT11, 0);
    bars[10]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);







    RECT stratcherect = { 15,51,359,280 };
    RECT line1rect = { 14,75,339,20 };
    RECT line2rect = { 14,94,339,20 };
    RECT line3rect = { 14,113,339,20 };
    RECT line4rect = { 14,132,339,20 };
    RECT line5rect = { 14,151,339,20 };
    RECT line6rect = { 14,170,339,20 };
    RECT line7rect = { 14,189,339,20 };
    RECT line8rect = { 14,208,339,20 };
    RECT line9rect = { 14,227,339,20 };
    RECT line10rect = { 14,246,339,20 };
    RECT line11rect = { 14,265,339,20 };


    line1 = (CIFRankSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFRankSlot), line1rect, 30, 0);
    line2 = (CIFRankSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFRankSlot), line2rect, 31, 0);
    line3 = (CIFRankSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFRankSlot), line3rect, 32, 0);
    line4 = (CIFRankSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFRankSlot), line4rect, 33, 0);
    line5 = (CIFRankSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFRankSlot), line5rect, 34, 0);
    line6 = (CIFRankSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFRankSlot), line6rect, 35, 0);
    line7 = (CIFRankSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFRankSlot), line7rect, 36, 0);
    line8 = (CIFRankSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFRankSlot), line8rect, 37, 0);
    line9 = (CIFRankSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFRankSlot), line9rect, 38, 0);
    line10 = (CIFRankSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFRankSlot), line10rect, 39, 0);
    line11 = (CIFRankSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFRankSlot), line11rect, 40, 0);


    line1->ShowGWnd(true);
    line2->ShowGWnd(true);
    line3->ShowGWnd(true);
    line4->ShowGWnd(true);
    line5->ShowGWnd(true);
    line6->ShowGWnd(true);
    line7->ShowGWnd(true);
    line8->ShowGWnd(true);
    line9->ShowGWnd(true);
    line10->ShowGWnd(true);
    line11->ShowGWnd(true);

    this->ShowGWnd(false);
    return true;
}

void CIFRankList::OnUpdate()
{
}
