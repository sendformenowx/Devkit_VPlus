#include <Game.h>
#include "IFEventMenu.h"


#define GDR_OK_BTN 3
#define GDR_CANCEL_BTN 4
#define GDR_CHEST_BG 31
#define GDR_REG_BTN_LMS 15
#define GDR_REG_BTN_LT 16
#define GDR_REG_BTN_SURV 17
CIFEventMenu* CIFEventMenu::EventW;
CIFWnd* CIFEventMenu::EventIcon;

GFX_IMPLEMENT_DYNCREATE(CIFEventMenu, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFEventMenu, CIFMainFrame)
                    ONG_COMMAND(GDR_REG_BTN_LMS, &CIFEventMenu::RegisterLMS)
                    ONG_COMMAND(GDR_REG_BTN_LT, &CIFEventMenu::RegisterLG)
                    ONG_COMMAND(GDR_REG_BTN_SURV, &CIFEventMenu::RegisterSURV)
GFX_END_MESSAGE_MAP()


bool CIFEventMenu::OnCreate(long ln)
{
    //	printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);
    // TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);


    m_title->SetText(L"Event Register Menu");
    TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);

    wnd_rect sz;


    sz.pos.x= 16;
    sz.pos.y = 44;
    sz.size.width = 420;
    sz.size.height = 396;
    mytile[1] = (CIFNormalTile* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFNormalTile), sz, 101, 1);
    mytile[1]->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_b.ddj", 0, 0);



/// BIG FRAME
    sz.pos.x= 13;
    sz.pos.y = 43;
    sz.size.width = 424;
    sz.size.height = 401;
    frame[0] = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), sz, 200, 0);
    frame[0]->TB_Func_13("interface\\inventory\\int_window_", 0, 0);


///blacksquare
    sz.pos.x= 24;
    sz.pos.y = 159;
    sz.size.width = 401;
    sz.size.height = 269;
    blacksquare = (CIFStretchWnd* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStretchWnd), sz, 201, 0);

    blacksquare->SetEdgeTextures("interface\\ifcommon\\com_blacksquare_right_side.ddj", "interface\\ifcommon\\com_blacksquare_left_up.ddj",
                                 "interface\\ifcommon\\com_blacksquare_left_side.ddj", "interface\\ifcommon\\com_blacksquare_left_up.ddj");




    /// 2 FRAME
    sz.pos.x= 25;
    sz.pos.y = 60;
    sz.size.width = 399;
    sz.size.height = 89;
    frame[0] = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), sz, 300, 0);
    frame[0]->TB_Func_13("interface\\frame\\frameg_wnd_", 0, 0);



    sz.pos.x= 41;
    sz.pos.y = 83;
    sz.size.width = 359;
    sz.size.height = 14;
    write[0] = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 203, 0);
    write[0]->SetText(L"Do you want see event schedule?");
    write[0]->m_FontTexture.SetColor(D3DCOLOR_ARGB(255,239,218,164));




    sz.pos.x= 41;
    sz.pos.y = 106;
    sz.size.width = 359;
    sz.size.height = 14;
    write[1] = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 205, 0);
    write[1]->SetText(L"You can check the event hours from the Main Menu.");
    write[1]->m_FontTexture.SetColor(D3DCOLOR_ARGB(255,239,218,164));



    sz.pos.x= 26;
    sz.pos.y = 161;
    sz.size.width = 148;
    sz.size.height = 24;
    gills[0] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, 206, 0);
    gills[0]->SetText(L"Event Name");
    gills[0]->m_FontTexture.SetColor(D3DCOLOR_ARGB(255,239,218,164));
    gills[0]->TB_Func_13("interface\\ifcommon\\com_bar02_", 0, 0);



    sz.pos.x= 174;
    sz.pos.y = 161;
    sz.size.width = 156;
    sz.size.height = 24;
    gills[1] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, 208, 0);
    gills[1]->SetText(L"Register Status");
    gills[1]->m_FontTexture.SetColor(D3DCOLOR_ARGB(255,239,218,164));
    gills[1]->TB_Func_13("interface\\ifcommon\\com_bar02_", 0, 0);


    sz.pos.x= 330;
    sz.pos.y = 161;
    sz.size.width = 96;
    sz.size.height = 24;
    gills[2] = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, 208, 0);
    gills[2]->SetText(L"Register");
    gills[2]->m_FontTexture.SetColor(D3DCOLOR_ARGB(255,239,218,164));
    gills[2]->TB_Func_13("interface\\ifcommon\\com_bar02_", 0, 0);



///BARS
    sz.pos.x= 26;
    sz.pos.y = 182;
    sz.size.width = 397;
    sz.size.height = 33;
    // m_mybar1 = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_CHEST_SLOT1, 0);
    //m_mybar1->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);
    lines[0] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, 31, 0);
    lines[0]->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);

    sz.pos.x= 26;
    sz.pos.y = 212;
    sz.size.width = 397;
    sz.size.height = 33;
    // m_mybar1 = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_CHEST_SLOT1, 0);
    //m_mybar1->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);
    lines[1] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, 31, 0);
    lines[1]->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);


    sz.pos.x= 26;
    sz.pos.y = 242;
    sz.size.width = 397;
    sz.size.height = 33;
    // m_mybar1 = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_CHEST_SLOT1, 0);
    //m_mybar1->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);
    lines[2] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, 31, 0);
    lines[2]->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);



    sz.pos.x= 26;
    sz.pos.y = 272;
    sz.size.width = 397;
    sz.size.height = 33;
    // m_mybar1 = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_CHEST_SLOT1, 0);
    //m_mybar1->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);
    lines[3] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, 31, 0);
    lines[3]->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);


    sz.pos.x= 26;
    sz.pos.y = 302;
    sz.size.width = 397;
    sz.size.height = 33;
    // m_mybar1 = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_CHEST_SLOT1, 0);
    //m_mybar1->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);
    lines[4] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, 31, 0);
    lines[4]->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);

    sz.pos.x= 26;
    sz.pos.y = 332;
    sz.size.width = 397;
    sz.size.height = 33;
    // m_mybar1 = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_CHEST_SLOT1, 0);
    //m_mybar1->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);
    lines[5] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, 31, 0);
    lines[5]->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);


    sz.pos.x= 26;
    sz.pos.y = 362;
    sz.size.width = 397;
    sz.size.height = 33;
    // m_mybar1 = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_CHEST_SLOT1, 0);
    //m_mybar1->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);
    lines[6] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, 31, 0);
    lines[6]->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);


    sz.pos.x= 26;
    sz.pos.y = 392;
    sz.size.width = 397;
    sz.size.height = 33;
    // m_mybar1 = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_CHEST_SLOT1, 0);
    //m_mybar1->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);
    lines[7] = (CIFBarWnd*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, 31, 0);
    lines[7]->TB_Func_13("interface\\ifcommon\\com_bar01_", 0 ,0);





    sz.pos.x= 35;
    sz.pos.y = 192;
    sz.size.width = 140;
    sz.size.height = 14;
    eventname[1] = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 205, 0);
    eventname[1]->SetText(L"Last Man Standing");
    eventname[1]->TB_Func_5(1);
    eventname[1]->TB_Func_6(1);


    sz.pos.x= 35;
    sz.pos.y = 223;
    sz.size.width = 140;
    sz.size.height = 14;
    eventname[2] = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 205, 0);
    eventname[2]->SetText(L"Survival Arena");
    eventname[2]->TB_Func_5(1);
    eventname[2]->TB_Func_6(1);


    sz.pos.x= 35;
    sz.pos.y = 254;
    sz.size.width = 140;
    sz.size.height = 14;
    eventname[3] = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 205, 0);
    eventname[3]->SetText(L"Lottery Gold");
    eventname[3]->TB_Func_5(1);
    eventname[3]->TB_Func_6(1);


    sz.pos.x= 181;
    sz.pos.y = 192;
    sz.size.width = 140;
    sz.size.height = 14;
    regstatus[1] = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 205, 0);
    regstatus[1]->TB_Func_5(1);
    regstatus[1]->TB_Func_6(1);


    sz.pos.x= 181;
    sz.pos.y = 223;
    sz.size.width = 140;
    sz.size.height = 14;
    regstatus[2] = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 205, 0);
    regstatus[2]->TB_Func_5(1);
    regstatus[2]->TB_Func_6(1);


    sz.pos.x= 181;
    sz.pos.y = 254;
    sz.size.width = 140;
    sz.size.height = 14;
    regstatus[3] = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 205, 0);
    regstatus[3]->TB_Func_5(1);
    regstatus[3]->TB_Func_6(1);





    sz.pos.x= 338;
    sz.pos.y = 186;
    sz.size.width = 76;
    sz.size.height = 23;
    button[0] = (CIFButton*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, GDR_REG_BTN_LMS, 0);
    button[0]->SetText(L"Register");
    button[0]->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);


    sz.pos.x= 338;
    sz.pos.y = 217;
    sz.size.width = 76;
    sz.size.height = 23;
    button[1] = (CIFButton*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, GDR_REG_BTN_SURV, 0);
    button[1]->SetText(L"Register");
    button[1]->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);



    sz.pos.x= 338;
    sz.pos.y = 246;
    sz.size.width = 76;
    sz.size.height = 23;
    button[2] = (CIFButton*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, GDR_REG_BTN_LT, 0);
    button[2]->SetText(L"Register");
    button[2]->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);



    this->ShowGWnd(false);

    UpdateMenuSize();

    return true;
}

void CIFEventMenu::OnUpdate()
{
}

void CIFEventMenu::UpdateMenuSize()
{
    const ClientResolutonData &res = CGame::GetClientDimensionStuff();

    MoveGWnd(((res.width - GetSize().width) - 80), GetPos().y);
    ////  MoveGWnd(((res.width - GetSize().width) - 80), (res.height - GetSize().height) - 300);
    BringToFront();

}

void CIFEventMenu::RegisterLMS()
{
    CMsgStreamBuffer buf(0x1322);

    buf << std::n_string("!registerlms");//1 tane string gönderiyorsun
    SendMsg(buf);

}

void CIFEventMenu::RegisterSURV()  {
    CMsgStreamBuffer buf(0x1322);

    buf << std::n_string("!registersurv");//1 tane string gönderiyorsun
    SendMsg(buf);

}

void CIFEventMenu::RegisterLG()  {
    CMsgStreamBuffer buf(0x1322);

    buf << std::n_string("!registerlg");//1 tane string gönderiyorsun
    SendMsg(buf);

}
