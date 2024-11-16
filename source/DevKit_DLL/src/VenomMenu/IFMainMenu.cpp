#include "IFMainMenu.h"
#include <ctime>
#include <BSLib/Debug.h>
#include <Data/LevelData.h>
#include <GlobalDataManager.h>
#include "GInterface.h"
#include "GEffSoundBody.h"

#include "ICPlayer.h"
#include "IFSystemMessage.h"
#include "Game.h"



#define GDR_MAINMENU_TILE 5
#define GDR_MAINMENU_FRAME 6
#define GDR_MAINMENU_BTN_GRANTNAME 11
#define GDR_MAINMENU_BTN_TITLE 20
#define GDR_MAINMENU_RANK 21
#define GDR_MAINMENU_UQHISTORY 22
#define GDR_MAINMENU_EVENT 23
#define GDR_MAINMENU_CHARLOCK 24
#define GDR_MAINMENU_CHANGELOG 25
#define GDR_MAINMENU_CHARANALIZ 26


GFX_IMPLEMENT_DYNCREATE(CIFMainMenu, CIFMainFrame)

GFX_BEGIN_MESSAGE_MAP(CIFMainMenu, CIFMainFrame)
                    ONG_COMMAND(GDR_MAINMENU_BTN_GRANTNAME, &On_BtnClickGrantName)
                    ONG_COMMAND(GDR_MAINMENU_BTN_TITLE, &On_BtnClickTitle)
                    ONG_COMMAND(GDR_MAINMENU_CHARLOCK, &On_BtnClickCharLock)
                    ONG_COMMAND(GDR_MAINMENU_UQHISTORY, &On_BtnClickUnique)
                    ONG_COMMAND(GDR_MAINMENU_EVENT, &On_BtnClickEvent)
                    ONG_COMMAND(GDR_MAINMENU_RANK, &On_BtnClickRanks)
                    ONG_COMMAND(GDR_MAINMENU_CHANGELOG, &On_BtnClickLog)
                    ONG_COMMAND(GDR_MAINMENU_CHARANALIZ, &On_BtnClickAnalyzer)
GFX_END_MESSAGE_MAP()

CIFWnd* CIFMainMenu::MenuI;

CIFMainMenu* CIFMainMenu::MenuW;
CIFGrantName* CIFMainMenu::GrantNameW;
CIFCharlock* CIFMainMenu::CharlockW;
CIFTitleManager* CIFMainMenu::TitleW;
CIFCharAnalyzer* CIFMainMenu::CharW;
CIFRank* CIFMainMenu::RankW;
CIFUniqueLog* CIFMainMenu::UniqueW;
CIFEventTime* CIFMainMenu::EventW;
CIFChangelog* CIFMainMenu::ChangeW;
CIFDps* CIFMainMenu::DpsW;
CIFFortressWar * CIFMainMenu::FTWW;
CIFSurvivalArena* CIFMainMenu::SurvivalW;

CIFNotify* CIFMainMenu::PurbleNoitfy;
CIFNotify* CIFMainMenu::OrangeNoitfy;
CIFMessageYesNo* CIFMainMenu::MessageYesNo;

CIFShowSox*  CIFMainMenu::SoxWnd;

CIFSlotWithHelp * CIFMainMenu::CIFSlots;
CIFSavedLocation * CIFMainMenu::SavedLoca;
CIFMovePartyMember * CIFMainMenu::MoveParty;

bool CIFMainMenu::OnCreate(long ln)
{

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);
    m_title->SetText(L"Main Menu");
    TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);


    wnd_rect sz;

    sz.pos.x= 15;
    sz.pos.y = 45;
    sz.size.width = 178;
    sz.size.height = 343;
    background = (CIFNormalTile*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFNormalTile), sz, GDR_MAINMENU_TILE, 0);
    background->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_b.ddj", 0, 0);


    sz.pos.x= 10;
    sz.pos.y = 40;
    sz.size.width = 189;
    sz.size.height = 353;
    menuframe = (CIFFrame*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), sz, GDR_MAINMENU_FRAME, 0);
    menuframe->TB_Func_13("interface\\inventory\\int_window_", 0, 0);




    sz.pos.x= 14;
    sz.pos.y = 46;
    sz.size.width = 57;
    sz.size.height = 56;
    charframe = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 1, 1);
    charframe->TB_Func_13("interface\\messagebox\\msgbox_itemwindow.ddj", 0,0);




    sz.pos.x= 68;
    sz.pos.y = 46;
    sz.size.width = 127;
    sz.size.height = 18;
    charname = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 2, 1);
    charname->TB_Func_13("interface\\exchange\\exc_box.ddj", 0, 0);


    sz.pos.x= 68;
    sz.pos.y = 64;
    sz.size.width = 127;
    sz.size.height = 18;
    guildname = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 2, 1);
    guildname->TB_Func_13("interface\\exchange\\exc_box.ddj", 0, 0);




    sz.pos.x= 68;
    sz.pos.y = 82;
    sz.size.width = 127;
    sz.size.height = 18;
    levelframe = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 4, 1);
    levelframe->TB_Func_13("interface\\exchange\\exc_box.ddj", 0, 0);




    sz.pos.x= 68;
    sz.pos.y = 82;
    sz.size.width = 127;
    sz.size.height = 18;
    lbl_level = (CNIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 3, 1);




    sz.pos.x= 13;
    sz.pos.y = 102;
    sz.size.width = 183;
    sz.size.height = 24;
    ozelbolme = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 1, 1);
    ozelbolme->TB_Func_13("interface\\exchange\\exc_box.ddj", 0, 0);
    //   ozelbolme->SetText(L"UNLOCKED");




    sz.pos.x= 28;
    sz.pos.y = 104;
    sz.size.width = 155;
    sz.size.height = 20;
    lockstatus = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 1, 1);
    lockstatus->m_FontTexture.SetColor(D3DCOLOR_ARGB(255,239,218,164));


    sz.pos.x= 18;
    sz.pos.y = 104;
    sz.size.width = 20;
    sz.size.height = 20;
    charlockicon = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 1, 1);
    charlockicon->m_FontTexture.SetColor(D3DCOLOR_ARGB(255,0,0,0));


    sz.pos.x= 16;
    sz.pos.y = 132;
    sz.size.width = 176;
    sz.size.height = 28;
    grantname = (CIFButton*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, GDR_MAINMENU_BTN_GRANTNAME, 0);
    grantname -> SetText(L"Grant Name");
    grantname->TB_Func_13("interface\\messagebox\\msgbox_rebirth_button.ddj", 1, 0);



    sz.pos.x= 16;
    sz.pos.y = 164;
    sz.size.width = 176;
    sz.size.height = 28;
    charlock = (CIFButton*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, GDR_MAINMENU_CHARLOCK, 0);
    charlock -> SetText(L"Character Lock");
    charlock->TB_Func_13("interface\\messagebox\\msgbox_rebirth_button.ddj", 1, 0);


    sz.pos.x= 16;
    sz.pos.y = 196;
    sz.size.width = 176;
    sz.size.height = 28;
    titlemanager = (CIFButton*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, GDR_MAINMENU_BTN_TITLE, 0);
    titlemanager -> SetText(L"Title Manager");
    titlemanager->TB_Func_13("interface\\messagebox\\msgbox_rebirth_button.ddj", 1, 0);


    sz.pos.x= 16;
    sz.pos.y = 228;
    sz.size.width = 176;
    sz.size.height = 28;
    analyzer = (CIFButton*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, GDR_MAINMENU_CHARANALIZ, 0);
    analyzer -> SetText(L"Character Analyzer");
    analyzer->TB_Func_13("interface\\messagebox\\msgbox_rebirth_button.ddj", 1, 0);



    sz.pos.x= 16;
    sz.pos.y = 260;
    sz.size.width = 176;
    sz.size.height = 28;
    ranking = (CIFButton*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, GDR_MAINMENU_RANK, 0);
    ranking -> SetText(L"Dynamic Ranking");
    ranking->TB_Func_13("interface\\messagebox\\msgbox_rebirth_button.ddj", 1, 0);


    sz.pos.x= 16;
    sz.pos.y = 292;
    sz.size.width = 176;
    sz.size.height = 28;
    uniquehistory = (CIFButton*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, GDR_MAINMENU_UQHISTORY, 0);
    uniquehistory -> SetText(L"Unique History");
    uniquehistory->TB_Func_13("interface\\messagebox\\msgbox_rebirth_button.ddj", 1, 0);



    sz.pos.x= 16;
    sz.pos.y = 324;
    sz.size.width = 176;
    sz.size.height = 28;
    eventtimer = (CIFButton*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, GDR_MAINMENU_EVENT, 0);
    eventtimer -> SetText(L"Event Schedule");
    eventtimer->TB_Func_13("interface\\messagebox\\msgbox_rebirth_button.ddj", 1, 0);


    sz.pos.x= 16;
    sz.pos.y = 356;
    sz.size.width = 176;
    sz.size.height = 28;
    changelog = (CIFButton*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, GDR_MAINMENU_CHANGELOG, 0);
    changelog -> SetText(L"Changelog");
    changelog->TB_Func_13("interface\\messagebox\\msgbox_rebirth_button.ddj", 1, 0);




    sz.pos.x= 20;
    sz.pos.y = 56;
    sz.size.width = 38;
    sz.size.height = 38;
    charface = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 153, 1);


    sz.pos.x= 52;
    sz.pos.y = 44;
    sz.size.width = 16;
    sz.size.height = 16;
    charicon = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 154, 1);



    this->ShowGWnd(false);

    UpdateMenuSize();
    return true;
}

void CIFMainMenu::OnUpdate()
{
    time_t rawtime;
    struct tm * timeinfo;
    wchar_t buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    wcsftime(buffer,sizeof(buffer),L"%d-%m-%Y %H:%M:%S",timeinfo);

    /// CHAR INFOS
    std::n_wstring input_text =g_pCICPlayer ->m_charname.c_str();
    this->charname->SetText(input_text.c_str());


    CLevelData *data = g_CGlobalDataManager->m_levelDataMap[g_pCICPlayer->m_level];


    this->lbl_level->SetText(L"Lv. %d", g_pCICPlayer->m_level);

    std::n_wstring guildname2 =g_pCICPlayer->GetGuildName().c_str();
    guildname->SetText(guildname2.c_str());

    if(guildname2.empty())
    {
        guildname->SetText(L"<No Guild>");
    }

}

void CIFMainMenu::On_BtnClickAnalyzer()
{
    if (CIFMainMenu::GrantNameW->IsVisible())
    {
        CIFMainMenu::GrantNameW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::CharlockW->IsVisible())
    {
        CIFMainMenu::CharlockW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::TitleW->IsVisible())
    {
        CIFMainMenu::TitleW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::UniqueW->IsVisible())
    {
        CIFMainMenu::UniqueW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::EventW->IsVisible())
    {
        CIFMainMenu::EventW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::RankW->IsVisible())
    {
        CIFMainMenu::RankW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::ChangeW->IsVisible())
    {
        CIFMainMenu::ChangeW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }

    if (CIFMainMenu::CharW->IsVisible())
    {
        CIFMainMenu::CharW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    } else
    {
        CGEffSoundBody::get()->PlaySound(L"snd_window_open");
        CIFMainMenu::CharW->ShowGWnd(true);
        CIFMainMenu::CharW->UpdateMenuSize();
        CIFMainMenu::CharW->BringToFront();
        CMsgStreamBuffer buf(0x180A);
        byte type = 2;
        buf << type;
        SendMsg(buf);
    }
}
void CIFMainMenu::On_BtnClickGrantName() {

    if (CIFMainMenu::TitleW->IsVisible())
    {
        CIFMainMenu::TitleW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::CharlockW->IsVisible())
    {
        CIFMainMenu::CharlockW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::CharW->IsVisible())
    {
        CIFMainMenu::CharW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::UniqueW->IsVisible())
    {
        CIFMainMenu::UniqueW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::EventW->IsVisible())
    {
        CIFMainMenu::EventW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::RankW->IsVisible())
    {
        CIFMainMenu::RankW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::ChangeW->IsVisible())
    {
        CIFMainMenu::ChangeW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }

    if (CIFMainMenu::GrantNameW->IsVisible())
    {
        CIFMainMenu::GrantNameW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    } else
    {
        CGEffSoundBody::get()->PlaySound(L"snd_window_open");
        CIFMainMenu::GrantNameW->ShowGWnd(true);
        CIFMainMenu::GrantNameW->UpdateMenuSize();
        CIFMainMenu::GrantNameW->BringToFront();
        CIFMainMenu::GrantNameW->m_myname->SetText(L"");

    }
}
void CIFMainMenu::UpdateMenuSize()
{
    const ClientResolutonData &res = CGame::GetClientDimensionStuff();

    MoveGWnd(((res.width - GetSize().width) - 80), GetPos().y);
    BringToFront();

}

void CIFMainMenu::On_BtnClickTitle() {



    if (CIFMainMenu::GrantNameW->IsVisible())
    {
        CIFMainMenu::GrantNameW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::CharlockW->IsVisible())
    {
        CIFMainMenu::CharlockW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::CharW->IsVisible())
    {
        CIFMainMenu::CharW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::UniqueW->IsVisible())
    {
        CIFMainMenu::UniqueW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::EventW->IsVisible())
    {
        CIFMainMenu::EventW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::RankW->IsVisible())
    {
        CIFMainMenu::RankW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::ChangeW->IsVisible())
    {
        CIFMainMenu::ChangeW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }

    if (CIFMainMenu::TitleW->IsVisible())
    {
        CIFMainMenu::TitleW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    } else
    {
        CGEffSoundBody::get()->PlaySound(L"snd_window_open");
        CIFMainMenu::TitleW->ShowGWnd(true);
        CIFMainMenu::TitleW->ActivateTabPage(0);



    }
}

void CIFMainMenu::On_BtnClickCharLock()
{


    if (CIFMainMenu::TitleW->IsVisible())
    {
        CIFMainMenu::TitleW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::GrantNameW->IsVisible())
    {
        CIFMainMenu::GrantNameW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::CharW->IsVisible())
    {
        CIFMainMenu::CharW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::UniqueW->IsVisible())
    {
        CIFMainMenu::UniqueW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::EventW->IsVisible())
    {
        CIFMainMenu::EventW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::RankW->IsVisible())
    {
        CIFMainMenu::RankW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::ChangeW->IsVisible())
    {
        CIFMainMenu::ChangeW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }

    if (CIFMainMenu::CharlockW->IsVisible())
    {
        CIFMainMenu::CharlockW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    } else
    {
        CGEffSoundBody::get()->PlaySound(L"snd_window_open");
        CIFMainMenu::CharlockW->ShowGWnd(true);
        CIFMainMenu::CharlockW->UpdateMenuSize();
        CIFMainMenu::CharlockW->BringToFront();
        CIFMainMenu::CharlockW->m_myname->SetText(L"");
    }


}
void CIFMainMenu::On_BtnClickUnique()
{
    if (CIFMainMenu::TitleW->IsVisible())
    {
        CIFMainMenu::TitleW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::GrantNameW->IsVisible())
    {
        CIFMainMenu::GrantNameW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::CharW->IsVisible())
    {
        CIFMainMenu::CharW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::CharlockW->IsVisible())
    {
        CIFMainMenu::CharlockW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::EventW->IsVisible())
    {
        CIFMainMenu::EventW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::RankW->IsVisible())
    {
        CIFMainMenu::RankW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::ChangeW->IsVisible())
    {
        CIFMainMenu::ChangeW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }

    if (CIFMainMenu::UniqueW->IsVisible())
    {
        CIFMainMenu::UniqueW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    } else
    {
        CGEffSoundBody::get()->PlaySound(L"snd_window_open");
        CIFMainMenu::UniqueW->ShowGWnd(true);
        CIFMainMenu::UniqueW->UpdateMenuSize();
        CIFMainMenu::UniqueW->BringToFront();
    }
}
void CIFMainMenu::On_BtnClickEvent()
{
    if (CIFMainMenu::TitleW->IsVisible())
    {
        CIFMainMenu::TitleW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::GrantNameW->IsVisible())
    {
        CIFMainMenu::GrantNameW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::CharW->IsVisible())
    {
        CIFMainMenu::CharW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::CharlockW->IsVisible())
    {
        CIFMainMenu::CharlockW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::UniqueW->IsVisible())
    {
        CIFMainMenu::UniqueW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::RankW->IsVisible())
    {
        CIFMainMenu::RankW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::ChangeW->IsVisible())
    {
        CIFMainMenu::ChangeW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    if (CIFMainMenu::EventW->IsVisible())
    {
        CIFMainMenu::EventW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    } else
    {
        CGEffSoundBody::get()->PlaySound(L"snd_window_open");
        CIFMainMenu::EventW->ShowGWnd(true);
        CIFMainMenu::EventW->UpdateMenuSize();
        CIFMainMenu::EventW->BringToFront();
        CMsgStreamBuffer buf(0x180A);
        byte type = 3;
        buf << type;
        SendMsg(buf);
    }

}

void CIFMainMenu::On_BtnClickRanks()
{
    if (CIFMainMenu::TitleW->IsVisible())
    {
        CIFMainMenu::TitleW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::GrantNameW->IsVisible())
    {
        CIFMainMenu::GrantNameW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::CharW->IsVisible())
    {
        CIFMainMenu::CharW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::CharlockW->IsVisible())
    {
        CIFMainMenu::CharlockW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::UniqueW->IsVisible())
    {
        CIFMainMenu::UniqueW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::EventW->IsVisible())
    {
        CIFMainMenu::EventW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::ChangeW->IsVisible())
    {
        CIFMainMenu::ChangeW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    if (CIFMainMenu::RankW->IsVisible())
    {
        CIFMainMenu::RankW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    } else
    {
        CGEffSoundBody::get()->PlaySound(L"snd_window_open");
        CIFMainMenu::RankW->ShowGWnd(true);
        CIFMainMenu::RankW->UpdateMenuSize();
        CIFMainMenu::RankW->BringToFront();
        CIFMainMenu::RankW->ActivateTabPage(0);
    }
}

void CIFMainMenu::On_BtnClickLog()
{
    if (CIFMainMenu::TitleW->IsVisible())
    {
        CIFMainMenu::TitleW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::GrantNameW->IsVisible())
    {
        CIFMainMenu::GrantNameW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::CharW->IsVisible())
    {
        CIFMainMenu::CharW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::CharlockW->IsVisible())
    {
        CIFMainMenu::CharlockW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::UniqueW->IsVisible())
    {
        CIFMainMenu::UniqueW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::EventW->IsVisible())
    {
        CIFMainMenu::EventW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::RankW->IsVisible())
    {
        CIFMainMenu::RankW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    if (CIFMainMenu::ChangeW->IsVisible())
    {
        CIFMainMenu::ChangeW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    } else
    {
        CGEffSoundBody::get()->PlaySound(L"snd_window_open");
        CIFMainMenu::ChangeW->ShowGWnd(true);
        CIFMainMenu::ChangeW->UpdateMenuSize();
        CIFMainMenu::ChangeW->BringToFront();
        CMsgStreamBuffer buf(0x180A);
        byte type = 4;
        buf << type;
        SendMsg(buf);

    }

}
