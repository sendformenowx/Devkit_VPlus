#include "IFDps.h"
#include "Game.h"

#define GDR_DPS_BAR1 20
#define GDR_DPS_BAR2 21
#define GDR_DPS_BAR3 22
#define GDR_DPS_BAR4 23
#define GDR_DPS_BAR5 24
#define GDR_DPS_BAR6 25
#define GDR_DPS_BAR7 26
#define GDR_DPS_BAR8 27
#define GDR_DPS_RANK_LABEL 50
#define GDR_DPS_NAME_LABEL 60
#define GDR_DPS_TITLE_LABEL 10
#define GDR_DPS_DMG_LABEL 51
#define GDR_DPS_RANK1 30
#define GDR_DPS_RANK2 31
#define GDR_DPS_RANK3 32
#define GDR_DPS_RANK4 33
#define GDR_DPS_RANK5 34
#define GDR_DPS_RANK6 35
#define GDR_DPS_RANK7 36
#define GDR_DPS_RANK8 37
#define GDR_DPS_NAME1 38
#define GDR_DPS_NAME2 39
#define GDR_DPS_NAME3 40
#define GDR_DPS_NAME4 41
#define GDR_DPS_NAME5 42
#define GDR_DPS_NAME6 43
#define GDR_DPS_NAME7 44

#define GDR_DPS_DMG1 70
#define GDR_DPS_DMG2 71
#define GDR_DPS_DMG3 72
#define GDR_DPS_DMG4 73
#define GDR_DPS_DMG5 74
#define GDR_DPS_DMG6 75
#define GDR_DPS_DMG7 76

#define GDR_DPS_UNIQUENAME 45
#define GDR_DPS_BLACKSQUARE 1
GFX_IMPLEMENT_DYNCREATE(CIFDps, CIFMainFrame)




bool CIFDps::OnCreate(long ln) {

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);
    m_close->ShowGWnd(false);
    m_handleBar->ShowGWnd(false);
    // SetText(L"Dps Meter");
    TB_Func_13("interface\\frame\\sframe_wnd_", 1, 1);

    wnd_rect sz;

    sz.pos.x= 7;
    sz.pos.y = 31;
    sz.size.width = 227;
    sz.size.height = 178;
    blacksquare = (CIFStretchWnd* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStretchWnd), sz, GDR_DPS_BLACKSQUARE, 0);
    blacksquare->SetEdgeTextures("interface\\ifcommon\\com_blacksquare_right_side.ddj", "interface\\ifcommon\\com_blacksquare_left_up.ddj",
                                 "interface\\ifcommon\\com_blacksquare_left_side.ddj", "interface\\ifcommon\\com_blacksquare_left_up.ddj");




    sz.pos.x= 48;
    sz.pos.y = 33;
    sz.size.width = 114;
    sz.size.height = 25;
    rank_label = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_DPS_RANK_LABEL, 0);
    rank_label->SetText(L"Name");
    rank_label->TB_Func_13("interface\\ifcommon\\com_bar02_", 1, 1);


    sz.pos.x= 8;
    sz.pos.y = 33;
    sz.size.width = 40;
    sz.size.height = 25;
    name_label = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_DPS_NAME_LABEL, 0);
    name_label -> SetText(L"Rank");
    name_label->TB_Func_13("interface\\ifcommon\\com_bar02_", 1, 1);

    sz.pos.x= 162;
    sz.pos.y = 33;
    sz.size.width = 71;
    sz.size.height = 25;
    dmg_label = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_DPS_DMG_LABEL, 0);
    dmg_label -> SetText(L"Damage");
    dmg_label->TB_Func_13("interface\\ifcommon\\com_bar02_", 1, 1);


    sz.pos.x= 4;
    sz.pos.y = 3;
    sz.size.width = 242;
    sz.size.height = 22;
    dps_title = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_TITLE_LABEL, 0);
    dps_title->SetText(L"DPS Meter");



    sz.pos.x= 8;
    sz.pos.y = 56;
    sz.size.width = 224;
    sz.size.height = 20;
    bars[1] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_DPS_BAR1, 0);
    bars[1]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x= 8;
    sz.pos.y = 75;
    sz.size.width = 224;
    sz.size.height = 20;
    bars[2] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_DPS_BAR2, 0);
    bars[2]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x= 8;
    sz.pos.y = 94;
    sz.size.width = 224;
    sz.size.height = 20;
    bars[3] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_DPS_BAR3, 0);
    bars[3]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x= 8;
    sz.pos.y = 113;
    sz.size.width = 224;
    sz.size.height = 20;
    bars[4] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_DPS_BAR4, 0);
    bars[4]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x= 8;
    sz.pos.y = 132;
    sz.size.width = 224;
    sz.size.height = 20;
    bars[5] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_DPS_BAR5, 0);
    bars[5]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x= 8;
    sz.pos.y = 150;
    sz.size.width = 224;
    sz.size.height = 20;
    bars[6] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_DPS_BAR6, 0);
    bars[6]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x= 8;
    sz.pos.y = 170;
    sz.size.width = 224;
    sz.size.height = 20;
    bars[7] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_DPS_BAR7, 0);
    bars[7]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);

    sz.pos.x= 8;
    sz.pos.y = 189;
    sz.size.width = 224;
    sz.size.height = 20;
    bars[8] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_DPS_BAR8, 0);
    bars[8]->TB_Func_13("interface\\ifcommon\\com_bar01_", 1, 1);





    sz.pos.x = 10;
    sz.pos.y = 57;
    sz.size.width = 32;
    sz.size.height = 15;
    rank_slot[1] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_RANK1, 1);
    rank_slot[1]->SetText(L"1.");
    //  rank_slot[1]->SetTextColor(0xeb345b);


    sz.pos.x = 10;
    sz.pos.y = 77;
    sz.size.width = 32;
    sz.size.height = 15;
    rank_slot[2] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_RANK2, 1);
    rank_slot[2]->SetText(L"2.");
    //  rank_slot[2]->SetTextColor(0xfef29d);

    sz.pos.x = 10;
    sz.pos.y = 96;
    sz.size.width = 32;
    sz.size.height = 15;
    rank_slot[3] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_RANK3, 1);
    rank_slot[3]->SetText(L"3.");
    //   rank_slot[3]->SetTextColor(0x5ad3a9);

    sz.pos.x = 10;
    sz.pos.y = 115;
    sz.size.width = 32;
    sz.size.height = 15;
    rank_slot[4] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_RANK4, 1);
    rank_slot[4]->SetText(L"4.");

    sz.pos.x = 10;
    sz.pos.y = 134;
    sz.size.width = 32;
    sz.size.height = 15;
    rank_slot[5] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_RANK5, 1);
    rank_slot[5]->SetText(L"5.");

    sz.pos.x = 10;
    sz.pos.y = 153;
    sz.size.width = 32;
    sz.size.height = 15;
    rank_slot[6] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_RANK6, 1);
    rank_slot[6]->SetText(L"6.");

    sz.pos.x = 10;
    sz.pos.y = 172;
    sz.size.width = 32;
    sz.size.height = 15;
    rank_slot[7] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_RANK7, 1);
    rank_slot[7]->SetText(L"7.");


    sz.pos.x = 17;
    sz.pos.y = 191;
    sz.size.width = 16;
    sz.size.height = 16;
    rank_slot[8] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_RANK8, 1);
    rank_slot[8]->TB_Func_13("icon\\etc\\unique_icon.ddj", 1, 1);

    //

    sz.pos.x = 49;
    sz.pos.y = 57;
    sz.size.width = 109;
    sz.size.height = 15;
    name_slot[1] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_NAME1, 1);
    //  name_slot[1]->SetTextColor(0xeb345b);


    sz.pos.x = 49;
    sz.pos.y = 77;
    sz.size.width = 109;
    sz.size.height = 15;
    name_slot[2] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_NAME2, 1);
    //name_slot[2]->SetTextColor(0xfef29d);


    sz.pos.x = 49;
    sz.pos.y = 96;
    sz.size.width = 109;
    sz.size.height = 15;
    name_slot[3] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_NAME3, 1);
    //name_slot[3]->SetTextColor(0x5ad3a9);


    sz.pos.x = 49;
    sz.pos.y = 115;
    sz.size.width = 109;
    sz.size.height = 15;
    name_slot[4] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_NAME4, 1);


    sz.pos.x = 49;
    sz.pos.y = 134;
    sz.size.width = 109;
    sz.size.height = 15;
    name_slot[5] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_NAME5, 1);


    sz.pos.x = 49;
    sz.pos.y = 153;
    sz.size.width = 109;
    sz.size.height = 15;
    name_slot[6] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_NAME6, 1);


    sz.pos.x = 49;
    sz.pos.y = 172;
    sz.size.width = 109;
    sz.size.height = 15;
    name_slot[7] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_NAME7, 1);


    sz.pos.x = 46;
    sz.pos.y = 191;
    sz.size.width = 171;
    sz.size.height = 15;
    unique_slot = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_UNIQUENAME, 1);
    unique_slot->m_FontTexture.SetColor(D3DCOLOR_ARGB(255, 84, 254, 0));

//damage slots

    sz.pos.x = 164;
    sz.pos.y = 57;
    sz.size.width = 62;
    sz.size.height = 15;
    dmg_slot[1] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_DMG1, 1);
    //   dmg_slot[1]->SetTextColor(0xeb345b);


    sz.pos.x = 164;
    sz.pos.y = 77;
    sz.size.width = 62;
    sz.size.height = 15;
    dmg_slot[2] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_DMG2, 1);
    // dmg_slot[2]->SetTextColor(0xfef29d);


    sz.pos.x = 164;
    sz.pos.y = 96;
    sz.size.width = 62;
    sz.size.height = 15;
    dmg_slot[3] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_DMG3, 1);
    //dmg_slot[3]->SetTextColor(0x5ad3a9);


    sz.pos.x = 164;
    sz.pos.y = 115;
    sz.size.width = 62;
    sz.size.height = 15;
    dmg_slot[4] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_DMG4, 1);


    sz.pos.x = 164;
    sz.pos.y = 134;
    sz.size.width = 62;
    sz.size.height = 15;
    dmg_slot[5] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_DMG5, 1);


    sz.pos.x = 164;
    sz.pos.y = 153;
    sz.size.width = 62;
    sz.size.height = 15;
    dmg_slot[6] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_DMG6, 1);


    sz.pos.x = 164;
    sz.pos.y = 172;
    sz.size.width = 62;
    sz.size.height = 15;
    dmg_slot[7] = (CIFStatic *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_DPS_DMG7, 1);



    UpdateMenuSize();
    this->ShowGWnd(false);

    return true;
}

void CIFDps::OnUpdate()
{

}
std::vector<CIFDps::DpsMeter> CIFDps::DpsDamage;


//void CIFDps::UpdateChest()
//{
//    int i = 0;
//    for (std::vector<CIFDps::DpsDamage>::iterator it = CIFDps::DpsDamage.begin(); it != CIFDps::DpsDamage.end(); ++it)
//    {
//        ++i;
//    }
//}



void CIFDps::WriteLine(BYTE Num, const wchar_t* Charname, const wchar_t* DMG) const
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
        case 6:
            name_slot[6]->SetText(Charname);
            dmg_slot[6]->SetText(DMG);
            break;
        case 7:
            name_slot[7]->SetText(Charname);
            dmg_slot[7]->SetText(DMG);
            break;

        default:
            break;
    }
}

void CIFDps::Clear() const
{
    name_slot[1]->SetText(L"");
    dmg_slot[1]->SetText(L"-");

    name_slot[2]->SetText(L"");
    dmg_slot[2]->SetText(L"-");

    name_slot[3]->SetText(L"");
    dmg_slot[3]->SetText(L"-");

    name_slot[4]->SetText(L"");
    dmg_slot[4]->SetText(L"-");

    name_slot[5]->SetText(L"");
    dmg_slot[5]->SetText(L"-");

    name_slot[6]->SetText(L"");
    dmg_slot[6]->SetText(L"-");

    name_slot[7]->SetText(L"");
    dmg_slot[7]->SetText(L"-");
}

void CIFDps::UpdateMenuSize()
{
    const ClientResolutonData &res = CGame::GetClientDimensionStuff();
    MoveGWnd(((res.width - GetSize().width) - 130), GetPos().y);
    BringToFront();
}
#define TIMERSHOWDPS 10002
void CIFDps::OnTimer(int timerId) {
    if (timerId == TIMERSHOWDPS) {


        this->KillTimer(TIMERSHOWDPS);

        this->ShowGWnd(false);
    }
}

void CIFDps::OpenDPS(int timeoutSeconds) {

    UpdateMenuSize();
    this->ShowGWnd(true);
    this->StartTimer(TIMERSHOWDPS, 10000);
}