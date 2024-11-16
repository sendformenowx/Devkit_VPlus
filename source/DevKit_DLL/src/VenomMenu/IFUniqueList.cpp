#include "IFUniqueList.h"


#define GDR_UNIQUE_SLOT1 20
#define GDR_UNIQUE_SLOT2 21
#define GDR_UNIQUE_SLOT3 22
#define GDR_UNIQUE_SLOT4 23
#define GDR_UNIQUE_SLOT5 24
#define GDR_UNIQUE_SLOT6 25
#define GDR_UNIQUE_SLOT7 26
#define GDR_UNIQUE_SLOT8 27
#define GDR_UNIQUE_SLOT9 28
#define GDR_UNIQUE_SLOT10 29




GFX_IMPLEMENT_DYNCREATE(CIFUniqueList, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFUniqueList, CIFWnd)
GFX_END_MESSAGE_MAP()


bool CIFUniqueList::OnCreate(long ln)
{
    //printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFWnd::OnCreate(ln);
    wnd_rect sz;


    sz.pos.x= 18;
    sz.pos.y = 69;
    sz.size.width = 338;
    sz.size.height = 20;
    bar[0] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_UNIQUE_SLOT1, 0);
    bar[0]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);


    sz.pos.x= 18;
    sz.pos.y = 88;
    sz.size.width = 338;
    sz.size.height = 20;
    bar[1] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_UNIQUE_SLOT2, 0);
    bar[1]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x= 18;
    sz.pos.y = 107;
    sz.size.width = 338;
    sz.size.height = 20;
    bar[2] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_UNIQUE_SLOT3, 0);
    bar[2]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x= 18;
    sz.pos.y = 126;
    sz.size.width = 338;
    sz.size.height = 20;
    bar[3] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_UNIQUE_SLOT4, 0);
    bar[3]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x= 18;
    sz.pos.y = 145;
    sz.size.width = 338;
    sz.size.height = 20;
    bar[4] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_UNIQUE_SLOT5, 0);
    bar[4]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x= 18;
    sz.pos.y = 164;
    sz.size.width = 338;
    sz.size.height = 20;
    bar[5] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_UNIQUE_SLOT6, 0);
    bar[5]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x= 18;
    sz.pos.y = 183;
    sz.size.width = 338;
    sz.size.height = 20;
    bar[6] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_UNIQUE_SLOT7, 0);
    bar[6]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x= 18;
    sz.pos.y = 202;
    sz.size.width = 338;
    sz.size.height = 20;
    bar[7] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_UNIQUE_SLOT8, 0);
    bar[7]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x= 18;
    sz.pos.y = 221;
    sz.size.width = 338;
    sz.size.height = 20;
    bar[8] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_UNIQUE_SLOT9, 0);
    bar[8]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x= 18;
    sz.pos.y = 240;
    sz.size.width = 338;
    sz.size.height = 20;
    bar[9] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_UNIQUE_SLOT10, 0);
    bar[9]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);




    RECT line1rect = { 18,69,340,20 };
    RECT line2rect = { 18,88,340,20 };
    RECT line3rect = { 18,107,340,20 };
    RECT line4rect = { 18,126,340,20 };
    RECT line5rect = { 18,145,340,20 };
    RECT line6rect = { 18,164,340,20 };
    RECT line7rect = { 18,183,340,20 };
    RECT line8rect = { 18,202,340,20 };
    RECT line9rect = { 18,221,340,20 };
    RECT line10rect = { 18,240,340,20 };



    line1 = (CIFUniqueLogSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueLogSlot), line1rect, 30, 0);
    line2 = (CIFUniqueLogSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueLogSlot), line2rect, 31, 0);
    line3 = (CIFUniqueLogSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueLogSlot), line3rect, 32, 0);
    line4 = (CIFUniqueLogSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueLogSlot), line4rect, 33, 0);
    line5 = (CIFUniqueLogSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueLogSlot), line5rect, 34, 0);
    line6 = (CIFUniqueLogSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueLogSlot), line6rect, 35, 0);
    line7 = (CIFUniqueLogSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueLogSlot), line7rect, 36, 0);
    line8 = (CIFUniqueLogSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueLogSlot), line8rect, 37, 0);
    line9 = (CIFUniqueLogSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueLogSlot), line9rect, 38, 0);
    line10 = (CIFUniqueLogSlot*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueLogSlot), line10rect, 39, 0);


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

    this->ShowGWnd(false);
    return true;

}

void CIFUniqueList::OnUpdate()
{
}
