#include <ICPlayer.h>
#include "IFCharAnalyzer.h"
#include "GInterface.h"
#include "Game.h"

#define GDR_ICONS 11
#define GDR_RANKBOX 12
#define GDR_FRAME_1 14
#define GDR_TILE_1 15
#define GDR_TAKSIM 54
#define GDR_RANK_SLOT 55
GFX_IMPLEMENT_DYNCREATE(CIFCharAnalyzer, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFCharAnalyzer, CIFMainFrame)


GFX_END_MESSAGE_MAP()


bool CIFCharAnalyzer::OnCreate(long ln) {

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);
    m_title->SetText(L"Character Analyzer");
    TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);
    wnd_rect sz;

    sz.pos.x= 14;
    sz.pos.y = 48;
    sz.size.width = 189;
    sz.size.height = 214;
    tile = (CIFNormalTile*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFNormalTile), sz, GDR_TILE_1, 1);
    tile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_b.ddj", 1, 1);


    sz.pos.x= 11;
    sz.pos.y = 36;
    sz.size.width = 200;
    sz.size.height = 228;
    frame = (CIFFrame*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), sz, GDR_FRAME_1, 1);
    frame->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 1);



    sz.pos.x= 20;
    sz.pos.y = 52;
    sz.size.width = 182;
    sz.size.height = 18;
    istatikler = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_ICONS, 1);
    istatikler->TB_Func_13("interface\\exchange\\exc_box.ddj", 0, 0);
    istatikler->TB_Func_6(1);
    istatikler->TB_Func_5(1);




///1.slot
    sz.pos.x= 16;
    sz.pos.y = 70;
    sz.size.width = 28;
    sz.size.height = 28;
    Icon1 = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_ICONS, 1);
    Icon1->TB_Func_13("interface\\ifcommon\\com_ranking_icon_01.ddj", 0, 0);

    sz.pos.x= 44;
    sz.pos.y = 75;
    sz.size.width = 80;
    sz.size.height = 18;
    rankbox = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANKBOX, 1);
    rankbox->TB_Func_13("interface\\exchange\\exc_box.ddj", 0, 0);

    sz.pos.x= 124;
    sz.pos.y = 81;
    sz.size.width = 5;
    sz.size.height = 5;
    taksim = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_TAKSIM, 1);
    taksim->SetText(L"/");

    sz.pos.x= 130;
    sz.pos.y = 75;
    sz.size.width = 70;
    sz.size.height = 18;
    rankbox = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANKBOX, 1);
    rankbox->TB_Func_13("interface\\exchange\\exc_box.ddj", 0, 0);

    sz.pos.x= 46;
    sz.pos.y = 77;
    sz.size.width = 78;
    sz.size.height = 18;
    survkill = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANK_SLOT, 1);
    survkill->SetText(L"Survival Kills");
    survkill->TB_Func_5(0);
    survkill->TB_Func_6(0);

    sz.pos.x= 132;
    sz.pos.y = 77;
    sz.size.width = 72;
    sz.size.height = 18;
    survkillslot = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANK_SLOT, 1);
    survkillslot->TB_Func_5(0);
    survkillslot->TB_Func_6(0);
    //survkillslot->m_FontTexture.SetColor(D3DCOLOR_ARGB(0,245,14,14));
///2.slot
    sz.pos.x= 16;
    sz.pos.y = 100;
    sz.size.width = 28;
    sz.size.height = 28;
    Icon1 = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_ICONS, 1);
    Icon1->TB_Func_13("interface\\ifcommon\\com_ranking_icon_01.ddj", 0, 0);


    sz.pos.x= 44;
    sz.pos.y = 105;
    sz.size.width = 80;
    sz.size.height = 18;
    rankbox = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANKBOX, 1);
    rankbox->TB_Func_13("interface\\exchange\\exc_box.ddj", 0, 0);

    sz.pos.x= 124;
    sz.pos.y = 111;
    sz.size.width = 5;
    sz.size.height = 5;
    taksim = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_TAKSIM, 1);
    taksim->SetText(L"/");


    sz.pos.x= 130;
    sz.pos.y = 105;
    sz.size.width = 70;
    sz.size.height = 18;
    rankbox = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANKBOX, 1);
    rankbox->TB_Func_13("interface\\exchange\\exc_box.ddj", 0, 0);

    sz.pos.x= 46;
    sz.pos.y = 107;
    sz.size.width = 78;
    sz.size.height = 18;
    ctfkill = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANK_SLOT, 1);
    ctfkill->SetText(L"Fortress Kills");
    ctfkill->TB_Func_5(0);
    ctfkill->TB_Func_6(0);

    sz.pos.x= 132;
    sz.pos.y = 107;
    sz.size.width = 72;
    sz.size.height = 18;
    ctfkillslot = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANK_SLOT, 1);
    ctfkillslot->TB_Func_5(0);
    ctfkillslot->TB_Func_6(0);
    //ctfkillslot->m_FontTexture.SetColor(D3DCOLOR_ARGB(0,245,14,14));

    ///3.slot
    sz.pos.x= 16;
    sz.pos.y = 130;
    sz.size.width = 28;
    sz.size.height = 28;
    Icon1 = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_ICONS, 1);
    Icon1->TB_Func_13("interface\\ifcommon\\com_ranking_icon_01.ddj", 0, 0);



    sz.pos.x= 44;
    sz.pos.y = 135;
    sz.size.width = 80;
    sz.size.height = 18;
    rankbox = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANKBOX, 1);
    rankbox->TB_Func_13("interface\\exchange\\exc_box.ddj", 0, 0);


    sz.pos.x= 124;
    sz.pos.y = 141;
    sz.size.width = 5;
    sz.size.height = 5;
    taksim = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_TAKSIM, 1);
    taksim->SetText(L"/");


    sz.pos.x= 130;
    sz.pos.y = 135;
    sz.size.width = 70;
    sz.size.height = 18;
    rankbox = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANKBOX, 1);
    rankbox->TB_Func_13("interface\\exchange\\exc_box.ddj", 0, 0);

    sz.pos.x= 46;
    sz.pos.y = 137;
    sz.size.width = 74;
    sz.size.height = 18;
    battlekill = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANK_SLOT, 1);
    battlekill->SetText(L"B.A. Kills");
    battlekill->TB_Func_5(0);
    battlekill->TB_Func_6(0);


    sz.pos.x= 132;
    sz.pos.y = 137;
    sz.size.width = 72;
    sz.size.height = 18;
    battlekillslot = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANK_SLOT, 1);
    battlekillslot->TB_Func_5(0);
    battlekillslot->TB_Func_6(0);
    //battlekillslot->m_FontTexture.SetColor(D3DCOLOR_ARGB(0,245,14,14));
///4.slot
    sz.pos.x= 16;
    sz.pos.y = 160;
    sz.size.width = 28;
    sz.size.height = 28;
    Icon1 = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_ICONS, 1);
    Icon1->TB_Func_13("interface\\ifcommon\\com_ranking_icon_01.ddj", 0, 0);

    sz.pos.x= 44;
    sz.pos.y = 165;
    sz.size.width = 80;
    sz.size.height = 18;
    rankbox = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANKBOX, 1);
    rankbox->TB_Func_13("interface\\exchange\\exc_box.ddj", 0, 0);


    sz.pos.x= 124;
    sz.pos.y = 171;
    sz.size.width = 5;
    sz.size.height = 5;
    taksim = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_TAKSIM, 1);
    taksim->SetText(L"/");


    sz.pos.x = 130;
    sz.pos.y = 165;
    sz.size.width = 70;
    sz.size.height = 18;
    rankbox = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANKBOX, 1);
    rankbox->TB_Func_13("interface\\exchange\\exc_box.ddj", 0, 0);

    sz.pos.x= 46;
    sz.pos.y = 167;
    sz.size.width = 74;
    sz.size.height = 18;
    jobkill = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANK_SLOT, 1);
    jobkill->SetText(L"Job Kills");
    jobkill->TB_Func_5(0);
    jobkill->TB_Func_6(0);

    sz.pos.x= 132;
    sz.pos.y = 167;
    sz.size.width = 72;
    sz.size.height = 18;
    jobkillslot = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANK_SLOT, 1);
    jobkillslot->TB_Func_5(0);
    jobkillslot->TB_Func_6(0);
    //jobkillslot->m_FontTexture.SetColor(D3DCOLOR_ARGB(0,245,14,14));
///5.slot
    sz.pos.x= 16;
    sz.pos.y = 190;
    sz.size.width = 28;
    sz.size.height = 28;
    Icon1 = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_ICONS, 1);
    Icon1->TB_Func_13("interface\\ifcommon\\com_ranking_icon_01.ddj", 0, 0);


    sz.pos.x= 44;
    sz.pos.y = 195;
    sz.size.width = 80;
    sz.size.height = 18;
    rankbox = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANKBOX, 1);
    rankbox->TB_Func_13("interface\\exchange\\exc_box.ddj", 0, 0);



    sz.pos.x= 124;
    sz.pos.y = 2001;
    sz.size.width = 5;
    sz.size.height = 5;
    taksim = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_TAKSIM, 1);
    taksim->SetText(L"/");

    sz.pos.x= 130;
    sz.pos.y = 195;
    sz.size.width = 70;
    sz.size.height = 18;
    rankbox = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANKBOX, 1);
    rankbox->TB_Func_13("interface\\exchange\\exc_box.ddj", 0, 0);


    sz.pos.x= 46;
    sz.pos.y = 197;
    sz.size.width = 74;
    sz.size.height = 18;
    globalrank = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_ICONS, 1);
    globalrank->SetText(L"Global Points");
    globalrank->TB_Func_5(0);
    globalrank->TB_Func_6(0);


    sz.pos.x= 132;
    sz.pos.y = 197;
    sz.size.width = 72;
    sz.size.height = 18;
    globalrankslot = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANK_SLOT, 1);
    globalrankslot->TB_Func_5(0);
    globalrankslot->TB_Func_6(0);
    //   globalrankslot->m_FontTexture.SetColor(D3DCOLOR_ARGB(0,245,14,14));
///6.slot
    sz.pos.x= 16;
    sz.pos.y = 220;
    sz.size.width = 28;
    sz.size.height = 28;
    Icon1 = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_ICONS, 1);
    Icon1->TB_Func_13("interface\\ifcommon\\com_ranking_icon_01.ddj", 0, 0);


    sz.pos.x= 44;
    sz.pos.y = 225;
    sz.size.width = 80;
    sz.size.height = 18;
    rankbox = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANKBOX, 1);
    rankbox->TB_Func_13("interface\\exchange\\exc_box.ddj", 0, 0);



    sz.pos.x= 124;
    sz.pos.y = 231;
    sz.size.width = 5;
    sz.size.height = 5;
    taksim = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_TAKSIM, 1);
    taksim->SetText(L"/");


    sz.pos.x= 130;
    sz.pos.y = 225;
    sz.size.width = 70;
    sz.size.height = 18;
    rankbox = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANKBOX, 1);
    rankbox->TB_Func_13("interface\\exchange\\exc_box.ddj", 0, 0);

    sz.pos.x= 46;
    sz.pos.y = 227;
    sz.size.width = 74;
    sz.size.height = 18;
    honor = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_ICONS, 1);
    honor->SetText(L"Honor Points");
    honor->TB_Func_5(0);
    honor->TB_Func_6(0);


    sz.pos.x= 132;
    sz.pos.y = 227;
    sz.size.width = 72;
    sz.size.height = 18;
    honorslot = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_RANK_SLOT, 1);
    honorslot->TB_Func_5(0);
    honorslot->TB_Func_6(0);

    this->ShowGWnd(false);
    UpdateMenuSize();
    return true;
}

void CIFCharAnalyzer::OnUpdate()
{
    std::n_wstring input_textnew = g_pCICPlayer ->m_charname.c_str();
    std::n_wstring ItemName = L"Statistics of [" + input_textnew + L"]";

    istatikler->SetText(ItemName.c_str());

    if(survkillslot->GetNText().empty())
    {
        survkillslot->SetText(L"0");
    }

    if(ctfkillslot->GetNText().empty())
    {
       ctfkillslot->SetText(L"0");
    }
    if(battlekillslot->GetNText().empty())
    {
       battlekillslot->SetText(L"0");
    }
    if(jobkillslot->GetNText().empty())
    {
       jobkillslot->SetText(L"0");
    }
    if(globalrankslot->GetNText().empty())
    {
       globalrankslot->SetText(L"0");
    }
    if(honorslot->GetNText().empty())
    {
       honorslot->SetText(L"0");
    }

}

void CIFCharAnalyzer::UpdateMenuSize()
{
    const ClientResolutonData &res = CGame::GetClientDimensionStuff();
    MoveGWnd(((res.width - GetSize().width) - 400), GetPos().y);
    BringToFront();

}