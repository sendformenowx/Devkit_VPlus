#pragma once
#include "IFMainFrame.h"
#include "IFTileWnd.h"
#include "IFNormalTile.h"
#include <IFNotify.h>
#include <IFSlotWithHelp.h>
#include "NIFStatic.h"
#include "../ShowIconAbove/IFShowSox.h"
#include "IFGrantName.h"
#include "IFCharlock.h"
#include "IFCharAnalyzer.h"
#include "IFRank.h"
#include "IFEventTime.h"
#include "IFUniqueLog.h"
#include "IFChangelog.h"
#include "IFTitleManager.h"
#include "../NewReverse/IFSavedLocation.h"
#include "IFDps.h"
#include "IFFortressWar.h"
#include "IFSurvivalArena.h"
#include "../NewReverse/IFMovePartyMember.h"
#include "../IFMessageYesNo.h"
class CIFMainMenu : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFMainMenu)
GFX_DECLARE_MESSAGE_MAP(CIFMainMenu)

public:
    bool OnCreate(long ln) override;
    void OnUpdate() override;
public:
    void On_BtnClickGrantName();
    void On_BtnClickTitle();
    void On_BtnClickCharLock();
    void On_BtnClickUnique();
    void On_BtnClickEvent();
    void On_BtnClickRanks();
    void On_BtnClickLog();
    void On_BtnClickAnalyzer();
    void UpdateMenuSize();
public:
    CIFNormalTile* background;
    CIFFrame* menuframe;
    CIFStatic* charframe;
    CIFStatic* charname;
    CIFStatic* guildname;
    CNIFStatic* lbl_level;
    CIFStatic* levelframe;
    CIFStatic* ozelbolme;
    CIFButton* charlock;
    CIFStatic* charlockicon;
    CIFStatic* lockstatus;
    CIFButton* analyzer;
    CIFButton* grantname;
    CIFButton* titlemanager;
    CIFButton* uniquehistory;
    CIFButton* ranking;
    CIFButton* eventtimer;
    CIFButton* changelog;
    CIFStatic* charface;
    CIFStatic* charicon;

public:
    static CIFWnd* MenuI;
    static CIFMainMenu* MenuW;
    static CIFGrantName* GrantNameW;
    static CIFCharlock* CharlockW;
    static CIFTitleManager* TitleW;
    static CIFCharAnalyzer* CharW;
    static CIFRank* RankW;
    static CIFUniqueLog* UniqueW;
    static CIFEventTime* EventW;
    static CIFChangelog* ChangeW;
    static CIFDps* DpsW;
    static CIFFortressWar* FTWW;
    static CIFSurvivalArena* SurvivalW;


    static CIFShowSox* SoxWnd;

    static CIFNotify* PurbleNoitfy;
    static CIFNotify* OrangeNoitfy;
    static CIFSavedLocation * SavedLoca;
    static CIFSlotWithHelp* CIFSlots;
    static CIFMovePartyMember* MoveParty;
    static CIFMessageYesNo* MessageYesNo;

};

