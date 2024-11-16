#include "IFEventTimeSlotList.h"



#define WRITE_SLOT_0 30
#define WRITE_SLOT_1 31
#define WRITE_SLOT_2 32
#define WRITE_SLOT_3 33
#define WRITE_SLOT_4 34
#define WRITE_SLOT_5 35
#define WRITE_SLOT_6 36
#define WRITE_SLOT_7 37
#define WRITE_SLOT_8 38
#define WRITE_SLOT_9 39


#define GDR_BAR_WND0 50
#define GDR_BAR_WND1 51
#define GDR_BAR_WND2 52
#define GDR_BAR_WND3 53
#define GDR_BAR_WND4 54
#define GDR_BAR_WND5 55
#define GDR_BAR_WND6 56
#define GDR_BAR_WND7 57
#define GDR_BAR_WND8 58
#define GDR_BAR_WND9 59



GFX_IMPLEMENT_DYNCREATE(CIFEventTimeList, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFEventTimeList, CIFWnd)
GFX_END_MESSAGE_MAP()


bool CIFEventTimeList::OnCreate(long ln)
{
    // printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFWnd::OnCreate(ln);


    RECT Line1rect = { 22,72,310,20 };
    RECT Line2rect = { 22,91,310,20 };
    RECT Line3rect = { 22,110,310,20 };
    RECT Line4rect = { 22,129,310,20 };
    RECT Line5rect = { 22,148,310,20 };
    RECT Line6rect = { 22,167,310,20 };
    RECT Line7rect = { 22,186,310,20 };
    RECT Line8rect = { 22,205,310,20 };
    RECT Line9rect = { 22,224,310,20 };
    RECT Line10rect = { 22,243,310, 20 };
    bars[0] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), Line1rect, GDR_BAR_WND0, 0);
    bars[1] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), Line2rect, GDR_BAR_WND1, 0);
    bars[2] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), Line3rect, GDR_BAR_WND2, 0);
    bars[3] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), Line4rect, GDR_BAR_WND3, 0);
    bars[4] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), Line5rect, GDR_BAR_WND4, 0);
    bars[5] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), Line6rect, GDR_BAR_WND5, 0);
    bars[6] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), Line7rect, GDR_BAR_WND6, 0);
    bars[7] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), Line8rect, GDR_BAR_WND7, 0);
    bars[8] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), Line9rect, GDR_BAR_WND8, 0);
    bars[9] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), Line10rect, GDR_BAR_WND9, 0);

    Line1 = (CIFEventTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeSlot), Line1rect, WRITE_SLOT_0, 0);
    Line2 = (CIFEventTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeSlot), Line2rect, WRITE_SLOT_1, 0);
    Line3 = (CIFEventTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeSlot), Line3rect, WRITE_SLOT_2, 0);
    Line4 = (CIFEventTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeSlot), Line4rect, WRITE_SLOT_3, 0);
    Line5 = (CIFEventTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeSlot), Line5rect, WRITE_SLOT_4, 0);
    Line6 = (CIFEventTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeSlot), Line6rect, WRITE_SLOT_5, 0);
    Line7 = (CIFEventTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeSlot), Line7rect, WRITE_SLOT_6, 0);
    Line8 = (CIFEventTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeSlot), Line8rect, WRITE_SLOT_7, 0);
    Line9 = (CIFEventTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeSlot), Line9rect, WRITE_SLOT_8, 0);
    Line10 = (CIFEventTimeSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeSlot), Line10rect, WRITE_SLOT_9, 0);

    bars[0]->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);
    bars[1]->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);
    bars[2]->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);
    bars[3]->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);
    bars[4]->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);
    bars[5]->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);
    bars[6]->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);
    bars[7]->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);
    bars[8]->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);
    bars[9]->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);



    Line1->ShowGWnd(true);
    Line2->ShowGWnd(true);
    Line3->ShowGWnd(true);
    Line4->ShowGWnd(true);
    Line5->ShowGWnd(true);
    Line6->ShowGWnd(true);
    Line7->ShowGWnd(true);
    Line8->ShowGWnd(true);
    Line9->ShowGWnd(true);
    Line10->ShowGWnd(true);


    this->ShowGWnd(false);
    return true;
}

void CIFEventTimeList::OnUpdate()
{
}
