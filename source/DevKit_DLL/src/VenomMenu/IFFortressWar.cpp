#include "IFFortressWar.h"
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
#define GDR_GUILD_BTN 75
#define GDR_UNION_BTN 76
#define GDR_PLAYER_BTN 77

GFX_IMPLEMENT_DYNCREATE(CIFFortressWar, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFFortressWar, CIFMainFrame)
                    ONG_COMMAND(GDR_GUILD_BTN, &CIFFortressWar::On_BtnClick)
                    ONG_COMMAND(GDR_UNION_BTN, &CIFFortressWar::On_BtnClickUni)
                    ONG_COMMAND(GDR_PLAYER_BTN, &CIFFortressWar::On_BtnClickPlayer)
GFX_END_MESSAGE_MAP()


bool CIFFortressWar::OnCreate(long ln) {

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);
    wnd_rect sz;
    TB_Func_13("interface\\frame\\sframe_wnd_", 1, 1);

    sz.pos.x= 14;
    sz.pos.y = 32;
    sz.size.width = 60;
    sz.size.height = 24;

    sz.pos.x= 14;
    sz.pos.y = 32;
    sz.size.width = 190;
    sz.size.height = 100;
    tile = (CIFNormalTile*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFNormalTile), sz, 250, 0);
    tile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_b.ddj", 0, 0);

    sz.pos.x= 14;
    sz.pos.y = 32;
    sz.size.width = 60;
    sz.size.height = 24;
    ShowGuild = (CIFButton*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSelectableArea), sz, GDR_GUILD_BTN, 0);
    ShowGuild->TB_Func_13("interface\\ifcommon\\com_long_tab_on.ddj", 0, 0);
    ShowGuild->m_FontTexture.sub_8B4750(7);
    ShowGuild->SetText(L"Guild");


    sz.pos.x = 74;
    sz.pos.y = 32;
    sz.size.width = 60;
    sz.size.height = 24;
    ShowUnion = (CIFButton*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSelectableArea), sz, GDR_UNION_BTN, 0);
    ShowUnion->TB_Func_13("interface\\ifcommon\\com_long_tab_off.ddj", 0, 0);
    ShowUnion->SetText(L"Union");


    sz.pos.x = 134;
    sz.pos.y = 32;
    sz.size.width = 60;
    sz.size.height = 24;
    ShowPlayer = (CIFButton *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSelectableArea), sz, GDR_PLAYER_BTN, 0);
    ShowPlayer->TB_Func_13("interface\\ifcommon\\com_long_tab_off.ddj", 0, 0);
    ShowPlayer->SetText(L"Player");


    sz.pos.x = 8;
    sz.pos.y = 71;
    sz.size.width = 194;
    sz.size.height = 20;
    bars[1] = (CIFBarWnd* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_FTW_BAR1, 0);
    bars[1]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x = 8;
    sz.pos.y = 90;
    sz.size.width = 194;
    sz.size.height = 20;
    bars[2] = (CIFBarWnd* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_FTW_BAR2, 0);
    bars[2]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);


    sz.pos.x = 8;
    sz.pos.y = 109;
    sz.size.width = 194;
    sz.size.height = 20;
    bars[3] = (CIFBarWnd* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_FTW_BAR3, 0);
    bars[3]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);


    sz.pos.x = 8;
    sz.pos.y = 128;
    sz.size.width = 194;
    sz.size.height = 20;
    bars[4] = (CIFBarWnd* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_FTW_BAR4, 0);
    bars[4]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);


    sz.pos.x = 8;
    sz.pos.y = 147;
    sz.size.width = 194;
    sz.size.height = 20;
    bars[5] = (CIFBarWnd* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_FTW_BAR5, 0);
    bars[5]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);





    sz.pos.x= 8;
    sz.pos.y = 55;
    sz.size.width = 39;
    sz.size.height = 20;
    rank_label = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_FTW_RANK_LABEL, 0);
    rank_label->SetText(L"Rank");
    rank_label->TB_Func_13("interface\\ifcommon\\com_bar02_", 1, 1);


    sz.pos.x= 47;
    sz.pos.y = 55;
    sz.size.width = 115;
    sz.size.height = 20;
    name_label = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_FTW_NAME_LABEL, 0);
    name_label -> SetText(L"Name");
    name_label->TB_Func_13("interface\\ifcommon\\com_bar02_", 1, 1);



    sz.pos.x= 162;
    sz.pos.y = 55;
    sz.size.width = 41;
    sz.size.height = 20;
    dmg_label = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_FTW_DMG_LABEL, 0);
    dmg_label -> SetText(L"Kill");
    dmg_label->TB_Func_13("interface\\ifcommon\\com_bar02_", 1, 1);



    sz.pos.x= 15;
    sz.pos.y = 8;
    sz.size.width = 181;
    sz.size.height = 15;
    dps_title = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_TITLE_LABEL, 0);
    dps_title->SetText(L"Fortress War Kills");
    // dps_title->m_FontTexture.SetColor(D3DCOLOR_ARGB(255,239,218,164));



    sz.pos.x = 12;
    sz.pos.y = 73;
    sz.size.width = 32;
    sz.size.height = 15;
    rank_slot[1] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_RANK1, 1);
    rank_slot[1]->SetText(L"1.");
    //  rank_slot[1]->SetTextColor(0xeb345b);

    sz.pos.x = 12;
    sz.pos.y = 93;
    sz.size.width = 32;
    sz.size.height = 15;
    rank_slot[2] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_RANK2, 1);
    rank_slot[2]->SetText(L"2.");
    //rank_slot[2]->SetTextColor(0xfef29d);

    sz.pos.x = 12;
    sz.pos.y = 112;
    sz.size.width = 32;
    sz.size.height = 15;
    rank_slot[3] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_RANK3, 1);
    rank_slot[3]->SetText(L"3.");
    // rank_slot[3]->SetTextColor(0x5ad3a9);

    sz.pos.x = 12;
    sz.pos.y = 131;
    sz.size.width = 32;
    sz.size.height = 15;
    rank_slot[4] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_RANK4, 1);
    rank_slot[4]->SetText(L"4.");

    sz.pos.x = 12;
    sz.pos.y = 150;
    sz.size.width = 32;
    sz.size.height = 15;
    rank_slot[5] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_RANK5, 1);
    rank_slot[5]->SetText(L"5.");

    //

    sz.pos.x = 51;
    sz.pos.y = 73;
    sz.size.width = 109;
    sz.size.height = 15;
    name_slot[1] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_NAME1, 1);
    unionname_slot[1] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_NAME1, 1);
    playername_slot[1] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_NAME1, 1);




    sz.pos.x = 51;
    sz.pos.y = 93;
    sz.size.width = 109;
    sz.size.height = 15;
    name_slot[2] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_NAME2, 1);
    unionname_slot[2] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_NAME1, 1);
    playername_slot[2] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_NAME1, 1);



    sz.pos.x = 51;
    sz.pos.y = 112;
    sz.size.width = 109;
    sz.size.height = 15;
    name_slot[3] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_NAME3, 1);
    unionname_slot[3] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_NAME1, 1);
    playername_slot[3] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_NAME1, 1);



    sz.pos.x = 51;
    sz.pos.y = 131;
    sz.size.width = 109;
    sz.size.height = 15;
    name_slot[4] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_NAME4, 1);
    unionname_slot[4] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_NAME1, 1);
    playername_slot[4] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_NAME1, 1);


    sz.pos.x = 51;
    sz.pos.y = 150;
    sz.size.width = 109;
    sz.size.height = 15;
    name_slot[5] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_NAME5, 1);
    unionname_slot[5] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_NAME1, 1);
    playername_slot[5] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_NAME1, 1);



//damage slots

    sz.pos.x = 166;
    sz.pos.y = 73;
    sz.size.width = 32;
    sz.size.height = 15;
    dmg_slot[1] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_DMG1, 1);
    uniondmg_slot[1] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_DMG1, 1);
    playerdmg_slot[1] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_DMG1, 1);


    sz.pos.x = 166;
    sz.pos.y = 93;
    sz.size.width = 32;
    sz.size.height = 15;
    dmg_slot[2] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_DMG2, 1);
    uniondmg_slot[2] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_DMG1, 1);
    playerdmg_slot[2] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_DMG1, 1);




    sz.pos.x = 166;
    sz.pos.y = 112;
    sz.size.width = 32;
    sz.size.height = 15;
    dmg_slot[3] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_DMG3, 1);
    uniondmg_slot[3] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_DMG1, 1);
    playerdmg_slot[3] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_DMG1, 1);



    sz.pos.x = 166;
    sz.pos.y = 131;
    sz.size.width = 32;
    sz.size.height = 15;
    dmg_slot[4] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_DMG4, 1);
    uniondmg_slot[4] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_DMG1, 1);
    playerdmg_slot[4] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_DMG1, 1);



    sz.pos.x = 166;
    sz.pos.y = 150;
    sz.size.width = 32;
    sz.size.height = 15;
    dmg_slot[5] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_DMG5, 1);
    uniondmg_slot[5] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_DMG1, 1);
    playerdmg_slot[5] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_FTW_DMG1, 1);



    //union name
    unionname_slot[1]->ShowGWnd(false);
    unionname_slot[2]->ShowGWnd(false);
    unionname_slot[3]->ShowGWnd(false);
    unionname_slot[4]->ShowGWnd(false);
    unionname_slot[5]->ShowGWnd(false);
    //player name
    playername_slot[1]->ShowGWnd(false);
    playername_slot[2]->ShowGWnd(false);
    playername_slot[3]->ShowGWnd(false);
    playername_slot[4]->ShowGWnd(false);
    playername_slot[5]->ShowGWnd(false);
    //union dmg
    uniondmg_slot[1]->ShowGWnd(false);
    uniondmg_slot[2]->ShowGWnd(false);
    uniondmg_slot[3]->ShowGWnd(false);
    uniondmg_slot[4]->ShowGWnd(false);
    uniondmg_slot[5]->ShowGWnd(false);
    //player dmg
    playerdmg_slot[1]->ShowGWnd(false);
    playerdmg_slot[2]->ShowGWnd(false);
    playerdmg_slot[3]->ShowGWnd(false);
    playerdmg_slot[4]->ShowGWnd(false);
    playerdmg_slot[5]->ShowGWnd(false);

    m_close->ShowGWnd(false);
    m_handleBar->ShowGWnd(false);
    this->ShowGWnd(false);

    UpdateMenuSize();
    m_close->ShowGWnd(false);
    m_handleBar->ShowGWnd(false);
    return true;
}

void CIFFortressWar::OnUpdate()
{

}

void CIFFortressWar::On_BtnClick() {
    ShowGuild->TB_Func_13("interface\\ifcommon\\com_long_tab_on.ddj", 0, 0);
    ShowUnion->TB_Func_13("interface\\ifcommon\\com_long_tab_off.ddj", 0, 0);
    ShowPlayer->TB_Func_13("interface\\ifcommon\\com_long_tab_off.ddj", 0, 0);
    ShowGuild->m_FontTexture.sub_8B4750(7);
    ShowUnion->m_FontTexture.sub_8B4750(0);
    ShowPlayer->m_FontTexture.sub_8B4750(0);

    // guildname
    name_slot[1]->ShowGWnd(true);
    name_slot[2]->ShowGWnd(true);
    name_slot[3]->ShowGWnd(true);
    name_slot[4]->ShowGWnd(true);
    name_slot[5]->ShowGWnd(true);
//guild dmg
    dmg_slot[1]->ShowGWnd(true);
    dmg_slot[2]->ShowGWnd(true);
    dmg_slot[3]->ShowGWnd(true);
    dmg_slot[4]->ShowGWnd(true);
    dmg_slot[5]->ShowGWnd(true);

    //union name
    unionname_slot[1]->ShowGWnd(false);
    unionname_slot[2]->ShowGWnd(false);
    unionname_slot[3]->ShowGWnd(false);
    unionname_slot[4]->ShowGWnd(false);
    unionname_slot[5]->ShowGWnd(false);
    //player name
    playername_slot[1]->ShowGWnd(false);
    playername_slot[2]->ShowGWnd(false);
    playername_slot[3]->ShowGWnd(false);
    playername_slot[4]->ShowGWnd(false);
    playername_slot[5]->ShowGWnd(false);
    //union dmg
    uniondmg_slot[1]->ShowGWnd(false);
    uniondmg_slot[2]->ShowGWnd(false);
    uniondmg_slot[3]->ShowGWnd(false);
    uniondmg_slot[4]->ShowGWnd(false);
    uniondmg_slot[5]->ShowGWnd(false);
    //player dmg
    playerdmg_slot[1]->ShowGWnd(false);
    playerdmg_slot[2]->ShowGWnd(false);
    playerdmg_slot[3]->ShowGWnd(false);
    playerdmg_slot[4]->ShowGWnd(false);
    playerdmg_slot[5]->ShowGWnd(false);

}

void CIFFortressWar::On_BtnClickUni() {
    ShowGuild->TB_Func_13("interface\\ifcommon\\com_long_tab_off.ddj", 0, 0);
    ShowUnion->TB_Func_13("interface\\ifcommon\\com_long_tab_on.ddj", 0, 0);
    ShowPlayer->TB_Func_13("interface\\ifcommon\\com_long_tab_off.ddj", 0, 0);
    ShowGuild->m_FontTexture.sub_8B4750(0);
    ShowUnion->m_FontTexture.sub_8B4750(7);
    ShowPlayer->m_FontTexture.sub_8B4750(0);


    // guildname
    name_slot[1]->ShowGWnd(false);
    name_slot[2]->ShowGWnd(false);
    name_slot[3]->ShowGWnd(false);
    name_slot[4]->ShowGWnd(false);
    name_slot[5]->ShowGWnd(false);
//guild dmg
    dmg_slot[1]->ShowGWnd(false);
    dmg_slot[2]->ShowGWnd(false);
    dmg_slot[3]->ShowGWnd(false);
    dmg_slot[4]->ShowGWnd(false);
    dmg_slot[5]->ShowGWnd(false);

    //union name
    unionname_slot[1]->ShowGWnd(true);
    unionname_slot[2]->ShowGWnd(true);
    unionname_slot[3]->ShowGWnd(true);
    unionname_slot[4]->ShowGWnd(true);
    unionname_slot[5]->ShowGWnd(true);
    //player name
    playername_slot[1]->ShowGWnd(false);
    playername_slot[2]->ShowGWnd(false);
    playername_slot[3]->ShowGWnd(false);
    playername_slot[4]->ShowGWnd(false);
    playername_slot[5]->ShowGWnd(false);
    //union dmg
    uniondmg_slot[1]->ShowGWnd(true);
    uniondmg_slot[2]->ShowGWnd(true);
    uniondmg_slot[3]->ShowGWnd(true);
    uniondmg_slot[4]->ShowGWnd(true);
    uniondmg_slot[5]->ShowGWnd(true);
    //player dmg
    playerdmg_slot[1]->ShowGWnd(false);
    playerdmg_slot[2]->ShowGWnd(false);
    playerdmg_slot[3]->ShowGWnd(false);
    playerdmg_slot[4]->ShowGWnd(false);
    playerdmg_slot[5]->ShowGWnd(false);


}

void CIFFortressWar::On_BtnClickPlayer() {
    ShowGuild->TB_Func_13("interface\\ifcommon\\com_long_tab_off.ddj", 0, 0);
    ShowUnion->TB_Func_13("interface\\ifcommon\\com_long_tab_off.ddj", 0, 0);
    ShowPlayer->TB_Func_13("interface\\ifcommon\\com_long_tab_on.ddj", 0, 0);
    ShowGuild->m_FontTexture.sub_8B4750(0);
    ShowUnion->m_FontTexture.sub_8B4750(0);
    ShowPlayer->m_FontTexture.sub_8B4750(7);


    // guildname
    name_slot[1]->ShowGWnd(false);
    name_slot[2]->ShowGWnd(false);
    name_slot[3]->ShowGWnd(false);
    name_slot[4]->ShowGWnd(false);
    name_slot[5]->ShowGWnd(false);
//guild dmg
    dmg_slot[1]->ShowGWnd(false);
    dmg_slot[2]->ShowGWnd(false);
    dmg_slot[3]->ShowGWnd(false);
    dmg_slot[4]->ShowGWnd(false);
    dmg_slot[5]->ShowGWnd(false);

    //union name
    unionname_slot[1]->ShowGWnd(false);
    unionname_slot[2]->ShowGWnd(false);
    unionname_slot[3]->ShowGWnd(false);
    unionname_slot[4]->ShowGWnd(false);
    unionname_slot[5]->ShowGWnd(false);
    //player name
    playername_slot[1]->ShowGWnd(true);
    playername_slot[2]->ShowGWnd(true);
    playername_slot[3]->ShowGWnd(true);
    playername_slot[4]->ShowGWnd(true);
    playername_slot[5]->ShowGWnd(true);
    //union dmg
    uniondmg_slot[1]->ShowGWnd(false);
    uniondmg_slot[2]->ShowGWnd(false);
    uniondmg_slot[3]->ShowGWnd(false);
    uniondmg_slot[4]->ShowGWnd(false);
    uniondmg_slot[5]->ShowGWnd(false);
    //player dmg
    playerdmg_slot[1]->ShowGWnd(true);
    playerdmg_slot[2]->ShowGWnd(true);
    playerdmg_slot[3]->ShowGWnd(true);
    playerdmg_slot[4]->ShowGWnd(true);
    playerdmg_slot[5]->ShowGWnd(true);

}



void CIFFortressWar::WriteLine(BYTE Num, const wchar_t* Charname, const wchar_t* DMG) const
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



void CIFFortressWar::WriteLine2(BYTE Num, const wchar_t* Charname, const wchar_t* DMG) const
{
    switch (Num)
    {
        case 1:
            unionname_slot[1]->SetText(Charname);
            uniondmg_slot[1]->SetText(DMG);
            break;
        case 2:
            unionname_slot[2]->SetText(Charname);
            uniondmg_slot[2]->SetText(DMG);
            break;
        case 3:
            unionname_slot[3]->SetText(Charname);
            uniondmg_slot[3]->SetText(DMG);
            break;
        case 4:
            unionname_slot[4]->SetText(Charname);
            uniondmg_slot[4]->SetText(DMG);
            break;
        case 5:
            unionname_slot[5]->SetText(Charname);
            uniondmg_slot[5]->SetText(DMG);
            break;
        default:
            break;
    }
}


void CIFFortressWar::WriteLine3(BYTE Num, const wchar_t* Charname, const wchar_t* DMG) const
{
    switch (Num)
    {
        case 1:
            playername_slot[1]->SetText(Charname);
            playerdmg_slot[1]->SetText(DMG);
            break;
        case 2:
            playername_slot[2]->SetText(Charname);
            playerdmg_slot[2]->SetText(DMG);
            break;
        case 3:
            playername_slot[3]->SetText(Charname);
            playerdmg_slot[3]->SetText(DMG);
            break;
        case 4:
            playername_slot[4]->SetText(Charname);
            playerdmg_slot[4]->SetText(DMG);
            break;
        case 5:
            playername_slot[5]->SetText(Charname);
            playerdmg_slot[5]->SetText(DMG);
            break;
        default:
            break;
    }
}


void CIFFortressWar::ClearGuild() const {
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

void CIFFortressWar::ClearUni() const {

    unionname_slot[1]->SetText(L"<None>");
    uniondmg_slot[1]->SetText(L"-");

    unionname_slot[2]->SetText(L"<None>");
    uniondmg_slot[2]->SetText(L"-");

    unionname_slot[3]->SetText(L"<None>");
    uniondmg_slot[3]->SetText(L"-");

    unionname_slot[4]->SetText(L"<None>");
    uniondmg_slot[4]->SetText(L"-");

    unionname_slot[5]->SetText(L"<None>");
    uniondmg_slot[5]->SetText(L"-");
}

void CIFFortressWar::ClearPlayer() const
{

    playername_slot[1]->SetText(L"<None>");
    playerdmg_slot[1]->SetText(L"-");

    playername_slot[2]->SetText(L"<None>");
    playerdmg_slot[2]->SetText(L"-");

    playername_slot[3]->SetText(L"<None>");
    playerdmg_slot[3]->SetText(L"-");

    playername_slot[4]->SetText(L"<None>");
    playerdmg_slot[4]->SetText(L"-");

    playername_slot[5]->SetText(L"<None>");
    playerdmg_slot[5]->SetText(L"-");

}

void CIFFortressWar::UpdateMenuSize()
{
    const ClientResolutonData &res = CGame::GetClientDimensionStuff();
    MoveGWnd(((res.width - GetSize().width) - 20), GetPos().y);
    BringToFront();

}
