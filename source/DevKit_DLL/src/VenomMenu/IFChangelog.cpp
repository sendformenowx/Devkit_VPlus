#include "IFChangelog.h"
#include "Game.h"
#include "TextStringManager.h"
#define GDR_CHANGELOG_FRAME_1 14
#define GDR_CHANGELOG_TILE_1 15
#define GDR_CHANGELOG_TEXT 21


GFX_IMPLEMENT_DYNCREATE(CIFChangelog, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFChangelog, CIFMainFrame)
GFX_END_MESSAGE_MAP()




bool CIFChangelog::OnCreate(long ln) {


    // Populate inherited members
    CIFMainFrame::OnCreate(ln);
    m_title->SetText(L"Changelog");
    TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);
    wnd_rect sz;

    sz.pos.x = 13;
    sz.pos.y =  42;
    sz.size.width = 320;
    sz.size.height = 248;
    tile = (CIFNormalTile*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFNormalTile), sz, GDR_CHANGELOG_TILE_1, 1);
    tile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_b.ddj", 1, 1);


    sz.pos.x = 10;
    sz.pos.y =  36;
    sz.size.width = 331;
    sz.size.height = 258;
    frame = (CIFFrame*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), sz, GDR_CHANGELOG_FRAME_1, 1);
    frame->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 1);



    /* sz.pos.x = 20;
     sz.pos.y = 46;
     sz.size.width = 312;
     sz.size.height = 237;
     paper = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_CHANGELOG_PAPER, 1);
     paper->TB_Func_13("interface\\guide\\gd_paper.ddj", 1, 1);*/



    sz.pos.x = 24;
    sz.pos.y = 50;
    sz.size.width = 304;
    sz.size.height = 230;
    my_textbox = (CIFTextBox*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFTextBox), sz, GDR_CHANGELOG_TEXT, 1);
    my_textbox->m_FontTexture.sub_8B4400(2, 2);
    my_textbox->m_FontTexture.sub_8B4750(2);
    my_textbox->TB_Func_5(0);
    my_textbox->TB_Func_6(0);


    this->ShowGWnd(false);
    UpdateMenuSize();
    return true;
}





void CIFChangelog::OnUpdate()
{

}

void CIFChangelog::UpdateMenuSize()
{
    const ClientResolutonData &res = CGame::GetClientDimensionStuff();
    MoveGWnd(((res.width - GetSize().width) - 400), GetPos().y);
    BringToFront();

}