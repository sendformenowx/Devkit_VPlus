#include "IFAttendance.h"
#include "Game.h"

#define ATTENDANCE 3
#define REWARD 4
#define GDR_CHEST_BG 31

CIFAttendance* CIFAttendance::ATTW;
CIFWnd* CIFAttendance::ATTICON;

GFX_IMPLEMENT_DYNCREATE(CIFAttendance, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFAttendance, CIFMainFrame)
ONG_COMMAND(200, &CIFAttendance::OnUnknownStuff)
ONG_COMMAND(201, &CIFAttendance::OnUnknownStuff)
ONG_COMMAND(ATTENDANCE, &CIFAttendance::On_BtnClick_1)
ONG_COMMAND(REWARD, &CIFAttendance::On_BtnClick_2)
GFX_END_MESSAGE_MAP()



bool CIFAttendance::OnCreate(long ln)
{

    CIFMainFrame::OnCreate(ln);
    //  TB_Func_13("interface\\frame\\event_sub_wnd_", 0, 0);
    TB_Func_13("interface\\frame\\frame_make_", 0, 0);



    wnd_rect sz;
    sz.pos.x = 0;
    sz.pos.y = 0;
    sz.size.width = 598;
    sz.size.height = 420;
    mytile[0] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_CHEST_BG, 1);
    mytile[0]->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_g.ddj", 0, 0);

    m_close->TB_Func_13("interface\\event\\summer_close.ddj", 0, 0);
    m_close->BringToFront();
    m_handleBar->BringToFront();
    m_handleBar->SetGWndSize(550, 50);

    sz.pos.x = 342;
    sz.pos.y = 20;
    sz.size.width = 36;
    sz.size.height = 44;
    Year[0] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_CHEST_BG, 1);
    Year[0]->TB_Func_13("interface\\event\\summer_count_2.ddj", 0, 0);


    sz.pos.x = 376;
    sz.pos.y = 20;
    sz.size.width = 36;
    sz.size.height = 44;
    Year[1] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_CHEST_BG, 1);
    Year[1]->TB_Func_13("interface\\event\\summer_count_0.ddj", 0, 0);


    sz.pos.x = 414;
    sz.pos.y = 20;
    sz.size.width = 36;
    sz.size.height = 44;
    Year[2] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_CHEST_BG, 1);
    Year[2]->TB_Func_13("interface\\event\\summer_count_2.ddj", 0, 0);


    sz.pos.x = 450;
    sz.pos.y = 20;
    sz.size.width = 36;
    sz.size.height = 44;
    Year[3] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_CHEST_BG, 1);
    Year[3]->TB_Func_13("interface\\event\\summer_count_2.ddj", 0, 0);

    sz.pos.x = 11;
    sz.pos.y = 70;
    sz.size.width = 583;
    sz.size.height = 306;
    mytile[1] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_CHEST_BG, 1);
    mytile[1]->TB_Func_13("interface\\event\\summer_main_box.ddj", 0, 0);



    sz.pos.x = 21;
    sz.pos.y = 86;
    sz.size.width = 560;
    sz.size.height = 28;
    mytile[2] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_CHEST_BG, 1);
    mytile[2]->TB_Func_13("interface\\event\\summer_day_tab.ddj", 0, 0);
    mytile[2]->SetText(L"Attendance Days Count");
    mytile[2]->TB_Func_5(1);
    mytile[2]->TB_Func_6(1);


    m_pTabs = new CIFSelectableArea * [numberOfTabs];

    for (int i = 0; i < numberOfTabs; i++) {

        sz.pos.x = 11;
        sz.pos.y = 48;
        sz.size.width = 96;
        sz.size.height = 24;

        m_pTabs[i] = (CIFSelectableArea*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSelectableArea),
            sz, tabFirstId + i, 0);
        m_pTabs[i]->SetFont(this->N00009C2F);


        m_pTabs[i]->sub_64CE30("interface\\event\\summer_tab_on.ddj",
            "interface\\event\\summer_tab_off.ddj", "interface\\event\\summer_tab_off.ddj");


        switch (i) {
        case 0:
            m_pTabs[0]->sub_64CC30(1);
            break;
        case 1:
            m_pTabs[1]->MoveGWnd(m_pTabs[0]->GetPos().x + m_pTabs[0]->GetSize().width + 6, m_pTabs[0]->GetPos().y);
            m_pTabs[1]->sub_64CC30(0);
            break;
        }
    }

    m_pTabs[0]->SetText(L"Attendance");
    m_pTabs[1]->SetText(L"Rewards");



    sz.pos.x = 235;
    sz.pos.y = 387;
    sz.size.width = 132;
    sz.size.height = 24;
    button[0] = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, ATTENDANCE, 0);
    button[0]->TB_Func_13("interface\\event\\summer_button.ddj", 0, 0);
    button[0]->SetText(L"Check the attendance");


    /// DAY BOX 1. HAFTA
    sz.pos.x = 21;
    sz.pos.y = 122;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[0] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    // dayframes[0]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[0]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);


    sz.pos.x = 10;
    sz.pos.y = 148;
    sz.size.width = 68;
    sz.size.height = 24;
    start = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    start->TB_Func_13("interface\\event\\summer_start_icon.ddj", 0, 0);





    sz.pos.x = 51;
    sz.pos.y = 122;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[0] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[0]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[0]->ShowGWnd(false);

    sz.pos.x = 101;
    sz.pos.y = 122;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[1] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[1]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[1]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);

    sz.pos.x = 131;
    sz.pos.y = 122;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[1] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[1]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[1]->ShowGWnd(false);


    sz.pos.x = 181;
    sz.pos.y = 122;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[2] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[2]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[2]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);


    sz.pos.x = 211;
    sz.pos.y = 122;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[2] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[2]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[2]->ShowGWnd(false);


    sz.pos.x = 261;
    sz.pos.y = 122;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[3] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[3]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[3]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);

    sz.pos.x = 291;
    sz.pos.y = 122;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[3] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[3]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[3]->ShowGWnd(false);


    sz.pos.x = 341;
    sz.pos.y = 122;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[4] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[4]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[4]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);

    sz.pos.x = 371;
    sz.pos.y = 122;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[4] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[4]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[4]->ShowGWnd(false);




    sz.pos.x = 421;
    sz.pos.y = 122;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[5] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[5]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[5]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);

    sz.pos.x = 451;
    sz.pos.y = 122;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[5] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[5]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[5]->ShowGWnd(false);



    sz.pos.x = 501;
    sz.pos.y = 122;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[6] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[6]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[6]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);


    sz.pos.x = 531;
    sz.pos.y = 122;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[6] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[6]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[6]->ShowGWnd(false);



    /// DAY BOX 2. HAFTA
    sz.pos.x = 21;
    sz.pos.y = 170;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[7] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[7]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[7]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);


    sz.pos.x = 51;
    sz.pos.y = 170;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[7] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[7]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[7]->ShowGWnd(false);



    sz.pos.x = 101;
    sz.pos.y = 170;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[8] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[8]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[8]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);


    sz.pos.x = 131;
    sz.pos.y = 170;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[8] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[8]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[8]->ShowGWnd(false);




    sz.pos.x = 181;
    sz.pos.y = 170;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[9] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[9]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[9]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);


    sz.pos.x = 211;
    sz.pos.y = 170;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[9] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[9]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[9]->ShowGWnd(false);


    sz.pos.x = 261;
    sz.pos.y = 170;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[10] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[10]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[10]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);

    sz.pos.x = 291;
    sz.pos.y = 170;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[10] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[10]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[10]->ShowGWnd(false);


    sz.pos.x = 341;
    sz.pos.y = 170;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[11] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[11]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[11]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);


    sz.pos.x = 371;
    sz.pos.y = 170;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[11] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[11]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[11]->ShowGWnd(false);




    sz.pos.x = 421;
    sz.pos.y = 170;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[12] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[12]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[12]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);

    sz.pos.x = 451;
    sz.pos.y = 170;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[12] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[12]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[12]->ShowGWnd(false);




    sz.pos.x = 501;
    sz.pos.y = 170;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[13] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[13]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[13]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);

    sz.pos.x = 531;
    sz.pos.y = 170;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[13] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[13]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[13]->ShowGWnd(false);



    /// DAY BOX 3. HAFTA
    sz.pos.x = 21;
    sz.pos.y = 218;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[14] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[14]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[14]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);


    sz.pos.x = 51;
    sz.pos.y = 218;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[14] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[14]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[14]->ShowGWnd(false);


    sz.pos.x = 101;
    sz.pos.y = 218;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[15] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[15]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[15]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);


    sz.pos.x = 131;
    sz.pos.y = 218;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[15] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[15]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[15]->ShowGWnd(false);

    sz.pos.x = 181;
    sz.pos.y = 218;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[16] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[16]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[16]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);


    sz.pos.x = 211;
    sz.pos.y = 218;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[16] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[16]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[16]->ShowGWnd(false);


    sz.pos.x = 261;
    sz.pos.y = 218;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[17] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[17]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[17]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);


    sz.pos.x = 291;
    sz.pos.y = 218;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[17] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[17]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[17]->ShowGWnd(false);


    sz.pos.x = 341;
    sz.pos.y = 218;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[18] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[18]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[18]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);

    sz.pos.x = 371;
    sz.pos.y = 218;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[18] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[18]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[18]->ShowGWnd(false);

    sz.pos.x = 421;
    sz.pos.y = 218;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[19] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[19]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[19]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);


    sz.pos.x = 451;
    sz.pos.y = 218;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[19] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[19]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[19]->ShowGWnd(false);


    sz.pos.x = 501;
    sz.pos.y = 218;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[20] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[20]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[20]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);

    sz.pos.x = 531;
    sz.pos.y = 218;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[20] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[20]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[20]->ShowGWnd(false);

    /// DAY BOX 4. HAFTA
    sz.pos.x = 21;
    sz.pos.y = 266;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[21] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    // dayframes[21]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[21]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);


    sz.pos.x = 51;
    sz.pos.y = 266;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[21] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[21]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[21]->ShowGWnd(false);


    sz.pos.x = 101;
    sz.pos.y = 266;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[22] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    // dayframes[22]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[22]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);


    sz.pos.x = 131;
    sz.pos.y = 266;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[22] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[22]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[22]->ShowGWnd(false);




    sz.pos.x = 181;
    sz.pos.y = 266;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[23] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[23]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[23]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);


    sz.pos.x = 211;
    sz.pos.y = 266;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[23] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[23]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[23]->ShowGWnd(false);



    sz.pos.x = 261;
    sz.pos.y = 266;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[24] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[24]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[24]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);


    sz.pos.x = 291;
    sz.pos.y = 266;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[24] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[24]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[24]->ShowGWnd(false);



    sz.pos.x = 341;
    sz.pos.y = 266;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[25] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[25]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[25]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);


    sz.pos.x = 371;
    sz.pos.y = 266;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[25] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[25]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[25]->ShowGWnd(false);




    sz.pos.x = 421;
    sz.pos.y = 266;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[26] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[26]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[26]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);

    sz.pos.x = 451;
    sz.pos.y = 266;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[26] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[26]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[26]->ShowGWnd(false);



    sz.pos.x = 501;
    sz.pos.y = 266;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[27] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    //dayframes[27("interface\\event\\summer_day_frame.ddj", 0, 0);
    dayframes[27]->TB_Func_13("interface\\event\\summer_select_box.ddj", 0, 0);


    sz.pos.x = 497;
    sz.pos.y = 290;
    sz.size.width = 68;
    sz.size.height = 24;
    end = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    end->TB_Func_13("interface\\event\\summer_end_icon.ddj", 0, 0);


    sz.pos.x = 531;
    sz.pos.y = 266;
    sz.size.width = 44;
    sz.size.height = 44;
    OK[27] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    OK[27]->TB_Func_13("interface\\event\\summer_stamp.ddj", 0, 0);
    OK[27]->ShowGWnd(false);




    /// DAY BOX 5. HAFTA
    sz.pos.x = 21;
    sz.pos.y = 314;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[28] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    dayframes[28]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);



    sz.pos.x = 101;
    sz.pos.y = 314;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[29] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    dayframes[29]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);



    sz.pos.x = 181;
    sz.pos.y = 314;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[30] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    dayframes[30]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);



    sz.pos.x = 261;
    sz.pos.y = 314;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[31] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    dayframes[31]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);

    sz.pos.x = 341;
    sz.pos.y = 314;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[32] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    dayframes[32]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);


    sz.pos.x = 421;
    sz.pos.y = 314;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[33] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    dayframes[33]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);


    sz.pos.x = 501;
    sz.pos.y = 314;
    sz.size.width = 80;
    sz.size.height = 48;
    dayframes[34] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    dayframes[34]->TB_Func_13("interface\\event\\summer_day_frame.ddj", 0, 0);





    sz.pos.x = 19;
    sz.pos.y = 118;
    sz.size.width = 570;
    sz.size.height = 248;
    mytile[5] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_CHEST_BG, 1);
    mytile[5]->TB_Func_13("interface\\event\\summer_main_box.ddj", 0, 0);




    /// DAYS

    sz.pos.x = 21;
    sz.pos.y = 122;
    sz.size.width = 24;
    sz.size.height = 20;
    days[0] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[0]->TB_Func_13("interface\\event\\summer_day_1.ddj", 0, 0);




    sz.pos.x = 101;
    sz.pos.y = 122;
    sz.size.width = 24;
    sz.size.height = 20;
    days[1] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[1]->TB_Func_13("interface\\event\\summer_day_2.ddj", 0, 0);




    sz.pos.x = 181;
    sz.pos.y = 122;
    sz.size.width = 24;
    sz.size.height = 20;
    days[2] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[2]->TB_Func_13("interface\\event\\summer_day_3.ddj", 0, 0);





    sz.pos.x = 261;
    sz.pos.y = 122;
    sz.size.width = 24;
    sz.size.height = 20;
    days[3] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[3]->TB_Func_13("interface\\event\\summer_day_4.ddj", 0, 0);




    sz.pos.x = 341;
    sz.pos.y = 122;
    sz.size.width = 24;
    sz.size.height = 20;
    days[4] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[4]->TB_Func_13("interface\\event\\summer_day_5.ddj", 0, 0);



    sz.pos.x = 421;
    sz.pos.y = 122;
    sz.size.width = 24;
    sz.size.height = 20;
    days[5] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[5]->TB_Func_13("interface\\event\\summer_day_6.ddj", 0, 0);




    sz.pos.x = 501;
    sz.pos.y = 122;
    sz.size.width = 24;
    sz.size.height = 20;
    days[6] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[6]->TB_Func_13("interface\\event\\summer_day_7.ddj", 0, 0);



    sz.pos.x = 21;
    sz.pos.y = 170;
    sz.size.width = 24;
    sz.size.height = 20;
    days[7] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[7]->TB_Func_13("interface\\event\\summer_day_8.ddj", 0, 0);



    sz.pos.x = 101;
    sz.pos.y = 170;
    sz.size.width = 24;
    sz.size.height = 20;
    days[8] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[8]->TB_Func_13("interface\\event\\summer_day_9.ddj", 0, 0);



    ///10
    sz.pos.x = 181;
    sz.pos.y = 170;
    sz.size.width = 24;
    sz.size.height = 20;
    days[9] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[9]->TB_Func_13("interface\\event\\summer_day_1.ddj", 0, 0);



    sz.pos.x = 191;
    sz.pos.y = 170;
    sz.size.width = 24;
    sz.size.height = 20;
    days[10] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[10]->TB_Func_13("interface\\event\\summer_day_0.ddj", 0, 0);


    ///11
    sz.pos.x = 261;
    sz.pos.y = 170;
    sz.size.width = 24;
    sz.size.height = 20;
    days[11] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[11]->TB_Func_13("interface\\event\\summer_day_1.ddj", 0, 0);

    sz.pos.x = 271;
    sz.pos.y = 170;
    sz.size.width = 24;
    sz.size.height = 20;
    days[12] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[12]->TB_Func_13("interface\\event\\summer_day_1.ddj", 0, 0);


    ///12
    sz.pos.x = 341;
    sz.pos.y = 170;
    sz.size.width = 24;
    sz.size.height = 20;
    days[13] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[13]->TB_Func_13("interface\\event\\summer_day_1.ddj", 0, 0);



    sz.pos.x = 351;
    sz.pos.y = 170;
    sz.size.width = 24;
    sz.size.height = 20;
    days[14] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[14]->TB_Func_13("interface\\event\\summer_day_2.ddj", 0, 0);


    ///13
    sz.pos.x = 421;
    sz.pos.y = 170;
    sz.size.width = 24;
    sz.size.height = 20;
    days[15] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[15]->TB_Func_13("interface\\event\\summer_day_1.ddj", 0, 0);



    sz.pos.x = 431;
    sz.pos.y = 170;
    sz.size.width = 24;
    sz.size.height = 20;
    days[16] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[16]->TB_Func_13("interface\\event\\summer_day_3.ddj", 0, 0);


    ///14
    sz.pos.x = 501;
    sz.pos.y = 170;
    sz.size.width = 24;
    sz.size.height = 20;
    days[17] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[17]->TB_Func_13("interface\\event\\summer_day_1.ddj", 0, 0);



    sz.pos.x = 511;
    sz.pos.y = 170;
    sz.size.width = 24;
    sz.size.height = 20;
    days[18] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[18]->TB_Func_13("interface\\event\\summer_day_4.ddj", 0, 0);



    ///15
    sz.pos.x = 21;
    sz.pos.y = 218;
    sz.size.width = 24;
    sz.size.height = 20;
    days[19] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[19]->TB_Func_13("interface\\event\\summer_day_1.ddj", 0, 0);



    sz.pos.x = 31;
    sz.pos.y = 218;
    sz.size.width = 24;
    sz.size.height = 20;
    days[20] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[20]->TB_Func_13("interface\\event\\summer_day_5.ddj", 0, 0);



    ///16
    sz.pos.x = 101;
    sz.pos.y = 218;
    sz.size.width = 24;
    sz.size.height = 20;
    days[21] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[21]->TB_Func_13("interface\\event\\summer_day_1.ddj", 0, 0);



    sz.pos.x = 111;
    sz.pos.y = 218;
    sz.size.width = 24;
    sz.size.height = 20;
    days[22] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[22]->TB_Func_13("interface\\event\\summer_day_6.ddj", 0, 0);



    ///17
    sz.pos.x = 181;
    sz.pos.y = 218;
    sz.size.width = 24;
    sz.size.height = 20;
    days[23] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[23]->TB_Func_13("interface\\event\\summer_day_1.ddj", 0, 0);



    sz.pos.x = 191;
    sz.pos.y = 218;
    sz.size.width = 24;
    sz.size.height = 20;
    days[24] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[24]->TB_Func_13("interface\\event\\summer_day_7.ddj", 0, 0);


    ///18
    sz.pos.x = 261;
    sz.pos.y = 218;
    sz.size.width = 24;
    sz.size.height = 20;
    days[25] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[25]->TB_Func_13("interface\\event\\summer_day_1.ddj", 0, 0);



    sz.pos.x = 271;
    sz.pos.y = 218;
    sz.size.width = 24;
    sz.size.height = 20;
    days[26] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[26]->TB_Func_13("interface\\event\\summer_day_8.ddj", 0, 0);




    ///19
    sz.pos.x = 341;
    sz.pos.y = 218;
    sz.size.width = 24;
    sz.size.height = 20;
    days[27] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[27]->TB_Func_13("interface\\event\\summer_day_1.ddj", 0, 0);



    sz.pos.x = 351;
    sz.pos.y = 218;
    sz.size.width = 24;
    sz.size.height = 20;
    days[28] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[28]->TB_Func_13("interface\\event\\summer_day_9.ddj", 0, 0);



    ///20
    sz.pos.x = 421;
    sz.pos.y = 218;
    sz.size.width = 24;
    sz.size.height = 20;
    days[29] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[29]->TB_Func_13("interface\\event\\summer_day_2.ddj", 0, 0);



    sz.pos.x = 431;
    sz.pos.y = 218;
    sz.size.width = 24;
    sz.size.height = 20;
    days[30] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[30]->TB_Func_13("interface\\event\\summer_day_0.ddj", 0, 0);


    ///21
    sz.pos.x = 501;
    sz.pos.y = 218;
    sz.size.width = 24;
    sz.size.height = 20;
    days[31] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[31]->TB_Func_13("interface\\event\\summer_day_2.ddj", 0, 0);



    sz.pos.x = 511;
    sz.pos.y = 218;
    sz.size.width = 24;
    sz.size.height = 20;
    days[32] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[32]->TB_Func_13("interface\\event\\summer_day_1.ddj", 0, 0);



    ///22
    sz.pos.x = 21;
    sz.pos.y = 266;
    sz.size.width = 24;
    sz.size.height = 20;
    days[33] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[33]->TB_Func_13("interface\\event\\summer_day_2.ddj", 0, 0);



    sz.pos.x = 31;
    sz.pos.y = 266;
    sz.size.width = 24;
    sz.size.height = 20;
    days[34] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[34]->TB_Func_13("interface\\event\\summer_day_2.ddj", 0, 0);



    ///23
    sz.pos.x = 101;
    sz.pos.y = 266;
    sz.size.width = 24;
    sz.size.height = 20;
    days[35] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[35]->TB_Func_13("interface\\event\\summer_day_2.ddj", 0, 0);



    sz.pos.x = 111;
    sz.pos.y = 266;
    sz.size.width = 24;
    sz.size.height = 20;
    days[36] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[36]->TB_Func_13("interface\\event\\summer_day_3.ddj", 0, 0);



    ///24
    sz.pos.x = 181;
    sz.pos.y = 266;
    sz.size.width = 24;
    sz.size.height = 20;
    days[37] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[37]->TB_Func_13("interface\\event\\summer_day_2.ddj", 0, 0);



    sz.pos.x = 191;
    sz.pos.y = 266;
    sz.size.width = 24;
    sz.size.height = 20;
    days[38] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[38]->TB_Func_13("interface\\event\\summer_day_4.ddj", 0, 0);


    ///25
    sz.pos.x = 261;
    sz.pos.y = 266;
    sz.size.width = 24;
    sz.size.height = 20;
    days[39] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[39]->TB_Func_13("interface\\event\\summer_day_2.ddj", 0, 0);



    sz.pos.x = 271;
    sz.pos.y = 266;
    sz.size.width = 24;
    sz.size.height = 20;
    days[40] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[40]->TB_Func_13("interface\\event\\summer_day_5.ddj", 0, 0);



    ///26
    sz.pos.x = 341;
    sz.pos.y = 266;
    sz.size.width = 24;
    sz.size.height = 20;
    days[41] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[41]->TB_Func_13("interface\\event\\summer_day_2.ddj", 0, 0);



    sz.pos.x = 351;
    sz.pos.y = 266;
    sz.size.width = 24;
    sz.size.height = 20;
    days[42] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[42]->TB_Func_13("interface\\event\\summer_day_6.ddj", 0, 0);


    ///27
    sz.pos.x = 421;
    sz.pos.y = 266;
    sz.size.width = 24;
    sz.size.height = 20;
    days[43] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[43]->TB_Func_13("interface\\event\\summer_day_2.ddj", 0, 0);



    sz.pos.x = 431;
    sz.pos.y = 266;
    sz.size.width = 24;
    sz.size.height = 20;
    days[44] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[44]->TB_Func_13("interface\\event\\summer_day_7.ddj", 0, 0);


    ///28
    sz.pos.x = 501;
    sz.pos.y = 266;
    sz.size.width = 24;
    sz.size.height = 20;
    days[45] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[45]->TB_Func_13("interface\\event\\summer_day_2.ddj", 0, 0);



    sz.pos.x = 511;
    sz.pos.y = 266;
    sz.size.width = 24;
    sz.size.height = 20;
    days[46] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[46]->TB_Func_13("interface\\event\\summer_day_8.ddj", 0, 0);


    ///29
    sz.pos.x = 21;
    sz.pos.y = 314;
    sz.size.width = 24;
    sz.size.height = 20;
    days[47] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[47]->TB_Func_13("interface\\event\\summer_day_2.ddj", 0, 0);



    sz.pos.x = 31;
    sz.pos.y = 314;
    sz.size.width = 24;
    sz.size.height = 20;
    days[48] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[48]->TB_Func_13("interface\\event\\summer_day_9.ddj", 0, 0);



    ///30
    sz.pos.x = 101;
    sz.pos.y = 314;
    sz.size.width = 24;
    sz.size.height = 20;
    days[49] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[49]->TB_Func_13("interface\\event\\summer_day_3.ddj", 0, 0);


    sz.pos.x = 111;
    sz.pos.y = 314;
    sz.size.width = 24;
    sz.size.height = 20;
    days[50] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[50]->TB_Func_13("interface\\event\\summer_day_0.ddj", 0, 0);



    ///31
    sz.pos.x = 181;
    sz.pos.y = 314;
    sz.size.width = 24;
    sz.size.height = 20;
    days[51] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[51]->TB_Func_13("interface\\event\\summer_day_3.ddj", 0, 0);



    sz.pos.x = 191;
    sz.pos.y = 314;
    sz.size.width = 24;
    sz.size.height = 20;
    days[52] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    days[52]->TB_Func_13("interface\\event\\summer_day_1.ddj", 0, 0);





    /// REWARDS sol taraf




    sz.pos.x = 21;
    sz.pos.y = 122;
    sz.size.width = 268;
    sz.size.height = 48;
    rewards[0] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    rewards[0]->TB_Func_13("interface\\event\\summer_item_tab.ddj", 0, 0);
    rewards[0]->ShowGWnd(false);


    sz.pos.x = 21;
    sz.pos.y = 170;
    sz.size.width = 268;
    sz.size.height = 48;
    rewards[1] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    rewards[1]->TB_Func_13("interface\\event\\summer_item_tab.ddj", 0, 0);
    rewards[1]->ShowGWnd(false);


    sz.pos.x = 21;
    sz.pos.y = 218;
    sz.size.width = 268;
    sz.size.height = 48;
    rewards[2] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    rewards[2]->TB_Func_13("interface\\event\\summer_item_tab.ddj", 0, 0);
    rewards[2]->ShowGWnd(false);


    sz.pos.x = 21;
    sz.pos.y = 266;
    sz.size.width = 268;
    sz.size.height = 48;
    rewards[3] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    rewards[3]->TB_Func_13("interface\\event\\summer_item_tab.ddj", 0, 0);
    rewards[3]->ShowGWnd(false);



    sz.pos.x = 21;
    sz.pos.y = 314;
    sz.size.width = 268;
    sz.size.height = 48;
    rewards[4] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    rewards[4]->TB_Func_13("interface\\event\\summer_item_tab.ddj", 0, 0);
    rewards[4]->ShowGWnd(false);



    /// sağ taraf rewards
    sz.pos.x = 311;
    sz.pos.y = 122;
    sz.size.width = 268;
    sz.size.height = 48;
    rewards[5] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    rewards[5]->TB_Func_13("interface\\event\\summer_item_tab.ddj", 0, 0);
    rewards[5]->ShowGWnd(false);


    sz.pos.x = 311;
    sz.pos.y = 170;
    sz.size.width = 268;
    sz.size.height = 48;
    rewards[6] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    rewards[6]->TB_Func_13("interface\\event\\summer_item_tab.ddj", 0, 0);
    rewards[6]->ShowGWnd(false);


    sz.pos.x = 311;
    sz.pos.y = 218;
    sz.size.width = 268;
    sz.size.height = 48;
    rewards[7] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    rewards[7]->TB_Func_13("interface\\event\\summer_item_tab.ddj", 0, 0);
    rewards[7]->ShowGWnd(false);


    sz.pos.x = 311;
    sz.pos.y = 266;
    sz.size.width = 268;
    sz.size.height = 48;
    rewards[8] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    rewards[8]->TB_Func_13("interface\\event\\summer_item_tab.ddj", 0, 0);
    rewards[8]->ShowGWnd(false);



    sz.pos.x = 311;
    sz.pos.y = 314;
    sz.size.width = 268;
    sz.size.height = 48;
    rewards[9] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    rewards[9]->TB_Func_13("interface\\event\\summer_item_tab.ddj", 0, 0);
    rewards[9]->ShowGWnd(false);


    /// days

    sz.pos.x = 38;
    sz.pos.y = 135;
    sz.size.width = 83;
    sz.size.height = 20;
    writeday[0] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    writeday[0]->ShowGWnd(false);



    sz.pos.x = 38;
    sz.pos.y = 183;
    sz.size.width = 83;
    sz.size.height = 20;
    writeday[1] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    writeday[1]->ShowGWnd(false);




    sz.pos.x = 38;
    sz.pos.y = 231;
    sz.size.width = 83;
    sz.size.height = 20;
    writeday[2] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    writeday[2]->ShowGWnd(false);



    sz.pos.x = 38;
    sz.pos.y = 279;
    sz.size.width = 83;
    sz.size.height = 20;
    writeday[3] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    writeday[3]->ShowGWnd(false);




    sz.pos.x = 38;
    sz.pos.y = 327;
    sz.size.width = 83;
    sz.size.height = 20;
    writeday[4] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    writeday[4]->ShowGWnd(false);




    sz.pos.x = 327;
    sz.pos.y = 135;
    sz.size.width = 83;
    sz.size.height = 20;
    writeday[5] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    writeday[5]->ShowGWnd(false);




    sz.pos.x = 327;
    sz.pos.y = 183;
    sz.size.width = 83;
    sz.size.height = 20;
    writeday[6] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    writeday[6]->ShowGWnd(false);


    sz.pos.x = 327;
    sz.pos.y = 231;
    sz.size.width = 83;
    sz.size.height = 20;
    writeday[7] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    writeday[7]->ShowGWnd(false);


    sz.pos.x = 327;
    sz.pos.y = 279;
    sz.size.width = 83;
    sz.size.height = 20;
    writeday[8] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    writeday[8]->ShowGWnd(false);



    sz.pos.x = 327;
    sz.pos.y = 327;
    sz.size.width = 83;
    sz.size.height = 20;
    writeday[9] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    writeday[9]->ShowGWnd(false);




    /// days

    sz.pos.x = 180;
    sz.pos.y = 135;
    sz.size.width = 83;
    sz.size.height = 20;
    itemnames[0] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    itemnames[0]->ShowGWnd(false);



    sz.pos.x = 180;
    sz.pos.y = 183;
    sz.size.width = 83;
    sz.size.height = 20;
    itemnames[1] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    itemnames[1]->ShowGWnd(false);



    sz.pos.x = 180;
    sz.pos.y = 231;
    sz.size.width = 83;
    sz.size.height = 20;
    itemnames[2] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    itemnames[2]->ShowGWnd(false);


    sz.pos.x = 180;
    sz.pos.y = 279;
    sz.size.width = 83;
    sz.size.height = 20;
    itemnames[3] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    itemnames[3]->ShowGWnd(false);



    sz.pos.x = 180;
    sz.pos.y = 327;
    sz.size.width = 83;
    sz.size.height = 20;
    itemnames[4] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    itemnames[4]->ShowGWnd(false);



    sz.pos.x = 469;
    sz.pos.y = 135;
    sz.size.width = 83;
    sz.size.height = 20;
    itemnames[5] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    itemnames[5]->ShowGWnd(false);


    sz.pos.x = 469;
    sz.pos.y = 183;
    sz.size.width = 83;
    sz.size.height = 20;
    itemnames[6] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    itemnames[6]->ShowGWnd(false);


    sz.pos.x = 469;
    sz.pos.y = 231;
    sz.size.width = 83;
    sz.size.height = 20;
    itemnames[7] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    itemnames[7]->ShowGWnd(false);


    sz.pos.x = 469;
    sz.pos.y = 279;
    sz.size.width = 83;
    sz.size.height = 20;
    itemnames[8] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    itemnames[8]->ShowGWnd(false);


    sz.pos.x = 469;
    sz.pos.y = 327;
    sz.size.width = 83;
    sz.size.height = 20;
    itemnames[9] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    itemnames[9]->ShowGWnd(false);


    ///ITEM ICONS


    sz.pos.x = 124;
    sz.pos.y = 129;
    sz.size.width = 32;
    sz.size.height = 32;
    items[0] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    items[0]->ShowGWnd(false);


    sz.pos.x = 124;
    sz.pos.y = 177;
    sz.size.width = 32;
    sz.size.height = 32;
    items[1] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    items[1]->ShowGWnd(false);


    sz.pos.x = 124;
    sz.pos.y = 225;
    sz.size.width = 32;
    sz.size.height = 32;
    items[2] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    items[2]->ShowGWnd(false);

    sz.pos.x = 124;
    sz.pos.y = 273;
    sz.size.width = 32;
    sz.size.height = 32;
    items[3] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    items[3]->ShowGWnd(false);

    sz.pos.x = 124;
    sz.pos.y = 321;
    sz.size.width = 32;
    sz.size.height = 32;
    items[4] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    items[4]->ShowGWnd(false);



    sz.pos.x = 414;
    sz.pos.y = 129;
    sz.size.width = 32;
    sz.size.height = 32;
    items[5] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    items[5]->ShowGWnd(false);


    sz.pos.x = 414;
    sz.pos.y = 177;
    sz.size.width = 32;
    sz.size.height = 32;
    items[6] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    items[6]->ShowGWnd(false);


    sz.pos.x = 414;
    sz.pos.y = 225;
    sz.size.width = 32;
    sz.size.height = 32;
    items[7] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    items[7]->ShowGWnd(false);

    sz.pos.x = 414;
    sz.pos.y = 273;
    sz.size.width = 32;
    sz.size.height = 32;
    items[8] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    items[8]->ShowGWnd(false);

    sz.pos.x = 414;
    sz.pos.y = 321;
    sz.size.width = 32;
    sz.size.height = 32;
    items[9] = (CIFStatic*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 31, 1);
    items[9]->ShowGWnd(false);



    this->ShowGWnd(false);

    UpdateMenuSize();
    return true;
}



void CIFAttendance::OnUnknownStuff() {
    int id = GetIDOfInterfaceUnderCursor();
    int i = 0;

    for (int i = 0; i < numberOfTabs; ++i) {
        if (id == m_pTabs[i]->UniqueID()) {
            ActivateTabPage(i);
            return;
        }
    }
}


void CIFAttendance::ActivateTabPage(BYTE page) {

    for (int i = 0; i < numberOfTabs; i++) {
        if (i == page)
            continue;

        m_pTabs[i]->sub_64CC30(0);
    }

    m_pTabs[page]->sub_64CC30(1);


    switch (page)
    {
    case 0:
    {
        CMsgStreamBuffer buf(0x180A);
        byte type = 5;
        buf << type;
        SendMsg(buf);
        for (int i = 0; i < 53; i++) {

            days[i]->ShowGWnd(true);
            mytile[2]->SetText(L"Attendance Days Count");
            mytile[5]->ShowGWnd(false);
            rewards[0]->ShowGWnd(false);
            rewards[1]->ShowGWnd(false);
            rewards[2]->ShowGWnd(false);
            rewards[3]->ShowGWnd(false);
            rewards[4]->ShowGWnd(false);
            rewards[5]->ShowGWnd(false);
            rewards[6]->ShowGWnd(false);
            rewards[7]->ShowGWnd(false);
            rewards[8]->ShowGWnd(false);
            rewards[9]->ShowGWnd(false);
            start->ShowGWnd(true);
            end->ShowGWnd(true);
            button[0]->ShowGWnd(true);
        }
        for (int i = 0; i < 35; i++) {

            dayframes[i]->ShowGWnd(true);

        }
        for (int i = 0; i < 10; i++) {

            items[i]->ShowGWnd(false);

        }
        for (int i = 0; i < 7; i++) {

            writeday[i]->ShowGWnd(false);

        }
        for (int i = 0; i < 7; i++) {

            itemnames[i]->ShowGWnd(false);

        }

    }
    break;
    case 1:
        for (int i = 0; i < 53; i++) {

            days[i]->ShowGWnd(false);
            mytile[2]->SetText(L"Attendance Rewards");
            mytile[5]->ShowGWnd(true);
            rewards[0]->ShowGWnd(true);
            rewards[1]->ShowGWnd(true);
            rewards[2]->ShowGWnd(true);
            rewards[3]->ShowGWnd(true);
            rewards[4]->ShowGWnd(true);
            rewards[5]->ShowGWnd(true);
            rewards[6]->ShowGWnd(true);
            rewards[7]->ShowGWnd(true);
            rewards[8]->ShowGWnd(true);
            rewards[9]->ShowGWnd(true);
            start->ShowGWnd(false);
            end->ShowGWnd(false);
            button[0]->ShowGWnd(false);

        }
        for (int i = 0; i < 35; i++) {

            dayframes[i]->ShowGWnd(false);

        }
        for (int i = 0; i < 10; i++) {

            items[i]->ShowGWnd(true);

        }
        for (int i = 0; i < 10; i++) {

            writeday[i]->ShowGWnd(true);

        }
        for (int i = 0; i < 10; i++) {

            itemnames[i]->ShowGWnd(true);

        }
        for (int i = 0; i < 27; i++) {

            OK[i]->ShowGWnd(false);

        }
        break;
    }
}



void CIFAttendance::OnUpdate()
{
    CIFWnd::RenderMyself();
}

void CIFAttendance::UpdateMenuSize()
{
    const ClientResolutonData& res = CGame::GetClientDimensionStuff();

    MoveGWnd(((res.width - GetSize().width) - 80), GetPos().y);
    ////  MoveGWnd(((res.width - GetSize().width) - 80), (res.height - GetSize().height) - 300);
    BringToFront();

}

void CIFAttendance::On_BtnClick_1()
{
    CMsgStreamBuffer buf(0x1101);
    SendMsg(buf);
}

void CIFAttendance::On_BtnClick_2() {

}