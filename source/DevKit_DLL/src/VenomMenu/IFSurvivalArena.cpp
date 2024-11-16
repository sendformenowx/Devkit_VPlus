#include "IFSurvivalArena.h"
#include "Game.h"

#define GDR_FTW_BAR1 20
#define GDR_FTW_BAR2 21
#define GDR_FTW_BAR3 22
#define GDR_FTW_BAR4 23
#define GDR_FTW_BAR5 24
#define GDR_FTW_RANK_LABEL 50
#define GDR_FTW_NAME_LABEL 60
#define GDR_FTW_TITLE_LABEL 10
#define GDR_FTW_DMG_LABEL 51
#define GDR_FTW_RANK1 30
#define GDR_FTW_RANK2 31
#define GDR_FTW_RANK3 32
#define GDR_FTW_RANK4 33
#define GDR_FTW_RANK5 34
#define GDR_FTW_NAME1 38
#define GDR_FTW_NAME2 39
#define GDR_FTW_NAME3 40
#define GDR_FTW_NAME4 41
#define GDR_FTW_NAME5 42


#define GDR_FTW_DMG1 70
#define GDR_FTW_DMG2 71
#define GDR_FTW_DMG3 72
#define GDR_FTW_DMG4 73
#define GDR_FTW_DMG5 74
#define GDR_BLACKSQUARE 50


GFX_IMPLEMENT_DYNCREATE(CIFSurvivalArena, CIFFrame)



bool CIFSurvivalArena::OnCreate(long ln) {

    // Populate inherited members
    CIFFrame::OnCreate(ln);
    wnd_rect sz;
    TB_Func_13("interface\\frame\\sframe_wnd_", 1, 1);

    sz.pos.x= 7;
    sz.pos.y = 31;
    sz.size.width = 198;
    sz.size.height = 121;
    blacksquare = (CIFStretchWnd* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStretchWnd), sz, GDR_BLACKSQUARE, 0);
    blacksquare->SetEdgeTextures("interface\\ifcommon\\com_blacksquare_right_side.ddj", "interface\\ifcommon\\com_blacksquare_left_up.ddj",
                                 "interface\\ifcommon\\com_blacksquare_left_side.ddj", "interface\\ifcommon\\com_blacksquare_left_up.ddj");



    sz.pos.x = 8;
    sz.pos.y = 55;
    sz.size.width = 194;
    sz.size.height = 20;
    bars[1] = (CIFBarWnd* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_FTW_BAR1, 0);
    bars[1]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x = 8;
    sz.pos.y = 74;
    sz.size.width = 194;
    sz.size.height = 20;
    bars[2] = (CIFBarWnd* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_FTW_BAR2, 0);
    bars[2]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);


    sz.pos.x = 8;
    sz.pos.y = 93;
    sz.size.width = 194;
    sz.size.height = 20;
    bars[3] = (CIFBarWnd* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_FTW_BAR3, 0);
    bars[3]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);


    sz.pos.x = 8;
    sz.pos.y = 112;
    sz.size.width = 194;
    sz.size.height = 20;
    bars[4] = (CIFBarWnd* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_FTW_BAR4, 0);
    bars[4]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);


    sz.pos.x = 8;
    sz.pos.y = 131;
    sz.size.width = 194;
    sz.size.height = 20;
    bars[5] = (CIFBarWnd* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_FTW_BAR5, 0);
    bars[5]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);





    sz.pos.x= 8;
    sz.pos.y = 33;
    sz.size.width = 39;
    sz.size.height = 25;
    rank_label = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, 192, 0);
    rank_label->SetText(L"Rank");
    rank_label->TB_Func_13("interface\\ifcommon\\com_bar02_", 1, 1);


    sz.pos.x= 47;
    sz.pos.y = 33;
    sz.size.width = 115;
    sz.size.height = 25;
    name_label = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, 101, 0);
    name_label -> SetText(L"Name");
    name_label->TB_Func_13("interface\\ifcommon\\com_bar02_", 1, 1);



    sz.pos.x= 162;
    sz.pos.y = 33;
    sz.size.width = 41;
    sz.size.height = 25;
    dmg_label = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, 100, 0);
    dmg_label -> SetText(L"Kill");
    dmg_label->TB_Func_13("interface\\ifcommon\\com_bar02_", 1, 1);


    sz.pos.x= 15;
    sz.pos.y = 8;
    sz.size.width = 181;
    sz.size.height = 15;
    dps_title = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_TITLE_LABEL, 0);
    dps_title->SetText(L"Kill Counter");



    sz.pos.x = 12;
    sz.pos.y = 57;
    sz.size.width = 32;
    sz.size.height = 15;
    rank_slot[1] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_RANK1, 1);
    rank_slot[1]->SetText(L"1.");
    //  rank_slot[1]->SetTextColor(0xeb345b);

    sz.pos.x = 12;
    sz.pos.y = 77;
    sz.size.width = 32;
    sz.size.height = 15;
    rank_slot[2] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_RANK2, 1);
    rank_slot[2]->SetText(L"2.");
    //rank_slot[2]->SetTextColor(0xfef29d);

    sz.pos.x = 12;
    sz.pos.y = 96;
    sz.size.width = 32;
    sz.size.height = 15;
    rank_slot[3] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_RANK3, 1);
    rank_slot[3]->SetText(L"3.");
    // rank_slot[3]->SetTextColor(0x5ad3a9);

    sz.pos.x = 12;
    sz.pos.y = 115;
    sz.size.width = 32;
    sz.size.height = 15;
    rank_slot[4] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_RANK4, 1);
    rank_slot[4]->SetText(L"4.");

    sz.pos.x = 12;
    sz.pos.y = 134;
    sz.size.width = 32;
    sz.size.height = 15;
    rank_slot[5] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_RANK5, 1);
    rank_slot[5]->SetText(L"5.");

    //

    sz.pos.x = 51;
    sz.pos.y = 57;
    sz.size.width = 109;
    sz.size.height = 15;
    name_slot[1] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_NAME1, 1);
    // name_slot[1]->SetTextColor(0xeb345b);


    sz.pos.x = 51;
    sz.pos.y = 77;
    sz.size.width = 109;
    sz.size.height = 15;
    name_slot[2] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_NAME2, 1);
    //  name_slot[2]->SetTextColor(0xfef29d);


    sz.pos.x = 51;
    sz.pos.y = 96;
    sz.size.width = 109;
    sz.size.height = 15;
    name_slot[3] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_NAME3, 1);
    //   name_slot[3]->SetTextColor(0x5ad3a9);


    sz.pos.x = 51;
    sz.pos.y = 115;
    sz.size.width = 109;
    sz.size.height = 15;
    name_slot[4] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_NAME4, 1);


    sz.pos.x = 51;
    sz.pos.y = 134;
    sz.size.width = 109;
    sz.size.height = 15;
    name_slot[5] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_NAME5, 1);



//damage slots

    sz.pos.x = 166;
    sz.pos.y = 57;
    sz.size.width = 32;
    sz.size.height = 15;
    dmg_slot[1] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_DMG1, 1);
    // dmg_slot[1]->SetTextColor(0xeb345b);


    sz.pos.x = 166;
    sz.pos.y = 77;
    sz.size.width = 32;
    sz.size.height = 15;
    dmg_slot[2] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_DMG2, 1);
    // dmg_slot[2]->SetTextColor(0xfef29d);



    sz.pos.x = 166;
    sz.pos.y = 96;
    sz.size.width = 32;
    sz.size.height = 15;
    dmg_slot[3] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_DMG3, 1);
    // dmg_slot[3]->SetTextColor(0x5ad3a9);


    sz.pos.x = 166;
    sz.pos.y = 115;
    sz.size.width = 32;
    sz.size.height = 15;
    dmg_slot[4] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_DMG4, 1);


    sz.pos.x = 166;
    sz.pos.y = 134;
    sz.size.width = 32;
    sz.size.height = 15;
    dmg_slot[5] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_DMG5, 1);

    this->ShowGWnd(false);

    UpdateMenuSize();

    return true;
}

void CIFSurvivalArena::OnUpdate()
{

}

void CIFSurvivalArena::WriteLine(BYTE Num, const wchar_t* Charname, const wchar_t* DMG) const
{
    switch (Num)
    {
        case 1:
            name_slot[1]->SetText(Charname);
            dmg_slot[1]->SetText(DMG);
            break;
        case 2:
            name_slot[2]->SetText(Charname);
            dmg_slot[2]->SetText(DMG);
            break;
        case 3:
            name_slot[3]->SetText(Charname);
            dmg_slot[3]->SetText(DMG);
            break;
        case 4:
            name_slot[4]->SetText(Charname);
            dmg_slot[4]->SetText(DMG);
            break;
        case 5:
            name_slot[5]->SetText(Charname);
            dmg_slot[5]->SetText(DMG);
            break;
        default:
            break;
    }
}

void CIFSurvivalArena::Clear() const
{
    name_slot[1]->SetText(L"<None>");
    dmg_slot[1]->SetText(L"-");

    name_slot[2]->SetText(L"<None>");
    dmg_slot[2]->SetText(L"-");

    name_slot[3]->SetText(L"<None>");
    dmg_slot[3]->SetText(L"-");

    name_slot[4]->SetText(L"<None>");
    dmg_slot[4]->SetText(L"-");

    name_slot[5]->SetText(L"<None>");
    dmg_slot[5]->SetText(L"-");

}

void CIFSurvivalArena::UpdateMenuSize()
{
    const ClientResolutonData &res = CGame::GetClientDimensionStuff();
    MoveGWnd(((res.width - GetSize().width) - 20), GetPos().y);
    BringToFront();

}
