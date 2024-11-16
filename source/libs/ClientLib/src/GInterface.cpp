#include "StdAfx.h"
#include "GInterface.h"
#include "IFNotify.h"
#include "IFChatViewer.h"
#include "IFNotify.h"
#include "GlobalDataManager.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFMainMenu.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFMainMenuGuide.h"
#include "../../../DevKit_DLL/src/ShowIconAbove/IFShowSox.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFChest.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFChestGuide.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFEventMenu.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFAttendance.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFEventMenuGuide.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFAttendanceEvent.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFDiscord.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFDiscordGuide.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFFacebook.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFFacebookGuide.h"
#include "GEffSoundBody.h"
#include "../../../DevKit_DLL/src/NewReverse/IFSavedLocation.h"
#include "../../../DevKit_DLL/src/GameHelpers/GameMain.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFDps.h"

#include <remodel/MemberFunctionHook.h>

HOOK_ORIGINAL_MEMBER(0x0079D5B0, &CGInterface::ToggleActionWnd);
void CGInterface::ToggleActionWnd() {
    // If MainPopup is visible and page 'action' is active
    if (m_mainPopup->IsVisible() && m_mainPopup->IsSubPageActive(GDR_ACTION)) {
        m_mainPopup->ShowGWnd(false);
        FUN_0079a7e0(m_mainPopup);
    }
    else {
        m_mainPopup->ShowGWnd(true);
        m_mainPopup->ShowSubPage(GDR_ACTION);
        FUN_0079a7e0(m_mainPopup);
    }
}

HOOK_ORIGINAL_MEMBER(0x0079B0B0, &CGInterface::ToggleApprenticeshipWnd);
void CGInterface::ToggleApprenticeshipWnd() {
    // If MainPopup is visible and page 'apprenticeship' is active
    if (m_mainPopup->IsVisible() && m_mainPopup->IsSubPageActive(GDR_APPRENTICESHIP)) {
        m_mainPopup->ShowGWnd(false);
        FUN_0079a7e0(m_mainPopup);
        g_CGlobalDataManager->FUN_008cbac0(GDR_APPRENTICESHIP);
    }
    else {
        m_mainPopup->ShowGWnd(true);
        if (!m_mainPopup->GetApprenticeShip()->IsVisible()) {
            m_mainPopup->ShowSubPage(GDR_APPRENTICESHIP);
        }
        FUN_0079a7e0(m_mainPopup);
        g_CGlobalDataManager->FUN_008cbac0(GDR_APPRENTICESHIP);
    }
}

HOOK_ORIGINAL_MEMBER(0x0079ACE0, &CGInterface::TogglePlayerInfoWnd);
void CGInterface::TogglePlayerInfoWnd() {
    // If MainPopup is visible and page 'playerinfo' is active
    if (m_mainPopup->IsVisible() && m_mainPopup->IsSubPageActive(GDR_PLAYERINFO)) {
        m_mainPopup->ShowGWnd(false);
        FUN_0079a7e0(m_mainPopup);
    }
    else {
        m_mainPopup->ShowGWnd(true);
        if (!m_mainPopup->GetPlayerInfo()->IsVisible()) {
            m_mainPopup->ShowSubPage(GDR_PLAYERINFO);
        }
        FUN_0079a7e0(m_mainPopup);
    }
}

void CGInterface::RenderToggle_GDR_GAMEGUIDE() {
    return reinterpret_cast<void(__thiscall*)(void*)>(0x0079F690)(this);
}

HOOK_ORIGINAL_MEMBER(0x0079B020, &CGInterface::ToggleInventoryWnd);
void CGInterface::ToggleInventoryWnd() {
    // If MainPopup is visible and page 'inventory' is active
    if (m_mainPopup->IsVisible() && m_mainPopup->IsSubPageActive(GDR_INVENTORY)) {
        m_mainPopup->ShowGWnd(false);
        FUN_0079a7e0(m_mainPopup);
    }
    else {
        m_mainPopup->ShowGWnd(true);
        if (!m_mainPopup->GetInventory()->IsVisible()) {
            m_mainPopup->ShowSubPage(GDR_INVENTORY);
        }
        FUN_0079a7e0(m_mainPopup);
    }
}

HOOK_ORIGINAL_MEMBER(0x0079ad70, &CGInterface::ToggleEquipmentWnd);
void CGInterface::ToggleEquipmentWnd() {
    // If MainPopup is visible and page 'equipment' is active
    if (m_mainPopup->IsVisible() && m_mainPopup->IsSubPageActive(GDR_INVENTORY)) {
        m_mainPopup->ShowGWnd(false);
        FUN_0079a7e0(m_mainPopup);
    }
    else {
        m_mainPopup->ShowGWnd(true);
        if (!m_mainPopup->GetEquipment()->IsVisible()) {
            m_mainPopup->ShowSubPage(GDR_INVENTORY);
        }
        FUN_0079a7e0(m_mainPopup);
    }
}

HOOK_ORIGINAL_MEMBER(0x0079AE90, &CGInterface::TogglePartyWnd);
void CGInterface::TogglePartyWnd() {
    // If MainPopup is visible and page 'party' is active
    if (m_mainPopup->IsVisible() && m_mainPopup->IsSubPageActive(GDR_PARTY)) {
        m_mainPopup->ShowGWnd(false);
        FUN_0079a7e0(m_mainPopup);
        g_CGlobalDataManager->FUN_008cbac0(GDR_PARTY);
    }
    else {
        m_mainPopup->ShowGWnd(true);
        if (!m_mainPopup->GetParty()->IsVisible()) {
            m_mainPopup->ShowSubPage(GDR_PARTY);
        }
        FUN_0079a7e0(m_mainPopup);
        g_CGlobalDataManager->FUN_008cbac0(GDR_PARTY);
    }
}

HOOK_ORIGINAL_MEMBER(0x0079AE00, &CGInterface::ToggleSkillWnd);
void CGInterface::ToggleSkillWnd() {
    // If MainPopup is visible and page 'skill' is active
    if (m_mainPopup->IsVisible() && m_mainPopup->IsSubPageActive(GDR_SKILL)) {
        m_mainPopup->ShowGWnd(false);
        FUN_0079a7e0(m_mainPopup);
    }
    else {
        m_mainPopup->ShowGWnd(true);
        if (!m_mainPopup->GetSkill()->IsVisible()) {
            m_mainPopup->ShowSubPage(GDR_SKILL);
        }
        FUN_0079a7e0(m_mainPopup);
    }
}

HOOK_ORIGINAL_MEMBER(0x0079af20, &CGInterface::ShowInventoryWnd);
void CGInterface::ShowInventoryWnd() {
    m_mainPopup->ShowGWnd(true);
    if (!m_mainPopup->GetInventory()->IsVisible()) {
        m_mainPopup->ShowSubPage(GDR_INVENTORY);
    }
    FUN_0079a7e0(m_mainPopup);
}

HOOK_ORIGINAL_MEMBER(0x0079af70, &CGInterface::ShowApprenticeshipWnd);
void CGInterface::ShowApprenticeshipWnd() {
    m_mainPopup->ShowGWnd(true);
    if (!m_mainPopup->GetApprenticeShip()->IsVisible()) {
        m_mainPopup->ShowSubPage(GDR_APPRENTICESHIP);
    }
    FUN_0079a7e0(m_mainPopup);
}

void CGInterface::ToggleMainPopup() {
    m_mainPopup->ShowGWnd(!m_mainPopup->IsVisible());
    FUN_0079a7e0(m_mainPopup);
}

void CGInterface::RenderToggle_WORLDMAP_GUIDE() {
    return reinterpret_cast<void(__thiscall*)(void*)>(0x0079ABE0)(this);
}

void CGInterface::Render_GDR_AUTO_POTION(bool visible) {
    return reinterpret_cast<void(__thiscall*)(void*, bool)>(0x0079C750)(this, visible);
}


CGInterface* CGInterface::GetInterface(void)
{
    return *reinterpret_cast<CGInterface**>(0x0110F80C);
}

void CGInterface::CreateFlorian0Event() {
    CIFMainMenu::MenuI = GetAlarmManager()->GetGuide(GUIDE_MAINMENU);
    wnd_rect sz;
    sz.pos.x = 800;
    sz.pos.y = 300;
    sz.size.width = 451;
    sz.size.height = 460;
    CIFEventMenu::EventW = (CIFEventMenu*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventMenu), sz, EventWnd, 0);

    sz.pos.x = 800;
    sz.pos.y = 400;
    sz.size.width = 357;
    sz.size.height = 155;
    CIFDiscord::DCW = (CIFDiscord*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFDiscord), sz, DCWnd, 0);
    
    
    
    sz.pos.x = 800;
    sz.pos.y = 400;
    sz.size.width = 357;
    sz.size.height = 155;
    CIFMainMenu::MessageYesNo = (CIFMessageYesNo*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFMessageYesNo), sz, yesno, 0);
    
    
    sz.pos.x = 800;
    sz.pos.y = 400;
    sz.size.width = 357;
    sz.size.height = 155;
    CIFFacebook::FBW = (CIFFacebook*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFFacebook), sz, FaceWndID, 0);

    sz.pos.x = 1293;
    sz.pos.y = 250;
    sz.size.width = 701;
    sz.size.height = 356;
    CIFPlayerChest::ChestW = (CIFPlayerChest*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFPlayerChest), sz, ChestID, 0);



    sz.pos.x = 800;
    sz.pos.y = 300;
    sz.size.width = 598;
    sz.size.height = 420;
    CIFAttendance::ATTW = (CIFAttendance*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFAttendance), sz, ATTWnd, 0);

    sz.pos.x = 1293;
    sz.pos.y = 250;
    sz.size.width = 208;
    sz.size.height = 404;
    CIFMainMenu::MenuW = (CIFMainMenu*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFMainMenu), sz, MenuID, 0);

    sz.pos.x = 906;
    sz.pos.y = 250;
    sz.size.width = 357;
    sz.size.height = 155;
    CIFMainMenu::GrantNameW = (CIFGrantName*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFGrantName), sz, GrantnameID, 0);





    sz.pos.x = 906;
    sz.pos.y = 250;
    sz.size.width = 357;
    sz.size.height = 155;
    CIFMainMenu::CharlockW = (CIFCharlock*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFCharlock), sz, CharlockID, 0);



    sz.pos.x = 600;
    sz.pos.y = 250;
    sz.size.width = 490;
    sz.size.height = 291;
    CIFMainMenu::TitleW = (CIFTitleManager*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFTitleManager), sz, TitleID, 0);


    sz.pos.x = 800;
    sz.pos.y = 250;
    sz.size.width = 220;
    sz.size.height = 273;
    CIFMainMenu::CharW = (CIFCharAnalyzer*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFCharAnalyzer), sz, CharAnalyzerID, 0);


    sz.pos.x = 400;
    sz.pos.y = 250;
    sz.size.width = 381;
    sz.size.height = 354;
    CIFMainMenu::RankW = (CIFRank*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFRank), sz, RankID, 0);



    sz.pos.x = 0;
    sz.pos.y = 243;
    sz.size.width = 64;
    sz.size.height = 64;
    CIFMainMenu::SoxWnd = (CIFShowSox*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFShowSox), sz, ShowSoxItem, 0);


    sz.pos.x = 800;
    sz.pos.y = 250;
    sz.size.width = 386;
    sz.size.height = 320;
    CIFMainMenu::UniqueW = (CIFUniqueLog*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueLog), sz, UniqueIDW, 0);


    sz.pos.x = 800;
    sz.pos.y = 250;
    sz.size.width = 352;
    sz.size.height = 306;
    CIFMainMenu::EventW = (CIFEventTime*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTime), sz, EventIDW, 0);



    sz.pos.x = 800;
    sz.pos.y = 250;
    sz.size.width = 352;
    sz.size.height = 306;
    CIFMainMenu::ChangeW = (CIFChangelog*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFChangelog), sz, ChangeID, 0);


    sz.pos.x = 1200;
    sz.pos.y = 0;
    sz.size.width = 242;
    sz.size.height = 220;
    CIFMainMenu::DpsW = (CIFDps*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFDps), sz, DPSID, 0);

    sz.pos.x = 1600;
    sz.pos.y = 400;
    sz.size.width = 211;
    sz.size.height = 180;
    CIFMainMenu::FTWW = (CIFFortressWar*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFFortressWar), sz, FTWID, 0);


    sz.pos.x = 1600;
    sz.pos.y = 400;
    sz.size.width = 211;
    sz.size.height = 162;
    CIFMainMenu::SurvivalW = (CIFSurvivalArena*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFSurvivalArena), sz, SURVIVALID, 0);


    sz.pos.x = 0;
    sz.pos.y = 0;
    sz.size.width = 395;
    sz.size.height = 375;
    CIFMainMenu::OrangeNoitfy = (CIFNotify*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFNotify), sz, OrangeNotify, 0);
    CIFMainMenu::OrangeNoitfy->SetEdgeTextures(
        "interface\\ifcommon\\cop_notice_edge2.ddj",
        "interface\\ifcommon\\cop_notice_edge.ddj",
        "interface\\ifcommon\\cop_notice_edge2.ddj",
        "interface\\ifcommon\\cop_notice_edge.ddj");
    CIFMainMenu::OrangeNoitfy->SetCornerTextures("interface\\ifcommon\\cop_notice_corner.ddj");
    CIFMainMenu::OrangeNoitfy->SetYPosition(40);
    CIFMainMenu::OrangeNoitfy->SetColor(255, 99, 71);

    // purple
    CIFMainMenu::PurbleNoitfy = (CIFNotify*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFNotify), sz, PurbleNotify, 0);
    CIFMainMenu::PurbleNoitfy->SetEdgeTextures(
        "interface\\ifcommon\\coq_notice_edge2.ddj",
        "interface\\ifcommon\\coq_notice_edge.ddj",
        "interface\\ifcommon\\coq_notice_edge2.ddj",
        "interface\\ifcommon\\coq_notice_edge.ddj");

    CIFMainMenu::PurbleNoitfy->SetCornerTextures("interface\\ifcommon\\coq_notice_corner.ddj");
    CIFMainMenu::PurbleNoitfy->SetYPosition(70);
    CIFMainMenu::PurbleNoitfy->SetColor(75, 0, 130);




    RECT SavedLocationRect = { 0,0,332,240 };
    CIFMainMenu::SavedLoca = (CIFSavedLocation*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFSavedLocation), SavedLocationRect, SavedLoc, 0);


    RECT CIFSlot = { 0,0,0,0 };
    CIFMainMenu::CIFSlots = (CIFSlotWithHelp*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSlotWithHelp), CIFSlot, 500, 1);


    sz.pos.x = 900;
    sz.pos.y = 250;
    sz.size.width = 376;
    sz.size.height = 284;
    CIFMainMenu::MoveParty = (CIFMovePartyMember*)CreateInstance(this, GFX_RUNTIME_CLASS(CIFMovePartyMember), sz, MovePartys, 0);


}

void CGInterface::CreateChest() {
    CIFPlayerChest::ChestIcon = GetAlarmManager()->GetGuide(GUIDE_CHEST);
  
}

void CGInterface::CreateFB() {
    CIFFacebook::FBICON = GetAlarmManager()->GetGuide(GUIDE_FACEBOOK);

}

void CGInterface::CreateDSCRD() {
    CIFDiscord::DCICON = GetAlarmManager()->GetGuide(GUIDE_DC);
   
}

void CGInterface::CreateAttendance() {

    CIFAttendance::ATTICON = GetAlarmManager()->GetGuide(GUIDE_ATTENDANCE);


}

void CGInterface::CreateEvents() {

    CIFEventMenu::EventIcon = GetAlarmManager()->GetGuide(GUIDE_EVENTS);


}

CAlramGuideMgrWnd* CGInterface::GetAlarmManager() {
    return m_IRM.GetResObj<CAlramGuideMgrWnd>(GDR_ALRAM_GUIDE_MGR_WND, 1);
}

bool CGInterface::OnCreateIMPL(long ln) {

    BeforeOnCreate();

    bool b = reinterpret_cast<bool(__thiscall*)(CGInterface*, long)>(0x0078c910)(this, ln);

    AfterOnCreate();

    return b;
}

void CGInterface::BeforeOnCreate() {

}

int CGInterface::sub_799970(void)
{
    return reinterpret_cast<int(__thiscall*)(CGInterface*)>(0x00799970)(this);
}


void CGInterface::AfterOnCreate() {
    CreateFlorian0Event();

    if (CNetProcessIn::ChestSetting == 1)
    {
        CreateChest();
    }
    if (CNetProcessIn::EventMenuSetting == 1)
    {
        CreateEvents();
    }
    if (CNetProcessIn::AttendanceSetting == 1)
    {
        CreateAttendance();
    }
    if (CNetProcessIn::FacebookSetting == 1)
    {
        CreateFB();
    }
    if (CNetProcessIn::DiscordSetting == 1)
    {
        CreateDSCRD();
    }


}

void CGInterface::ShowMessage_Quest(const std::n_wstring& msg) {
    CIFNotify* notify = m_IRM.GetResObj<CIFNotify>(GDR_UPDATE_QUEST_INFO, 1);
    notify->ShowMessage(msg);
}

void CGInterface::ShowMessage_Notice(const std::n_wstring& msg) {
    CIFNotify* notify = m_IRM.GetResObj<CIFNotify>(GDR_NOTICE, 1);
    notify->ShowMessage(msg);
}

void CGInterface::ShowMessage_Warning(const std::n_wstring& msg) {
    CIFNotify* notify = m_IRM.GetResObj<CIFNotify>(GDR_WARNING_WND, 1);
    notify->ShowMessage(msg);
}

void CGInterface::ShowLogMessage(int color, const wchar_t* msg) {
    GetSystemMessageView()->WriteMessage(0xff, color, msg, 0, 1);
}

void CGInterface::ShowMessage_Purble(const wchar_t* msg) {
    CIFMainMenu::PurbleNoitfy->ShowMessage(msg);
}

void CGInterface::ShowMessage_Orange(const wchar_t* msg) {
    CIFMainMenu::OrangeNoitfy->ShowMessage(msg);
}


int CGInterface::Get_SelectedObjectId() {
    return this->m_selectedObjectId;
}

CIFTimerWnd* CGInterface::Get_TimerWindow() {
    return this->m_timerWindow;
}

CIFQuickStateHalfWnd* CGInterface::Get_QuickStateHalfWnd() {
    return this->N00002637;
}

CIF_NPCWindow* CGInterface::Get_GDR_NPCWINDOW() {
    return (CIF_NPCWindow*)this->m_IRM.GetResObj(GDR_NPCWINDOW, 1);
}

HOOK_ORIGINAL_MEMBER(0x00798D00, &CGInterface::GetMainPopup);
CIFMainPopup* CGInterface::GetMainPopup() {
    return (CIFMainPopup*)this->m_IRM.GetResObj(GDR_MAINPOPUP, 1);
}

CIFStorageRoom* CGInterface::Get_GDR_STORAGEROOM() {
    return (CIFStorageRoom*)this->m_IRM.GetResObj(GDR_STORAGEROOM, 1);
}

CIFStorageRoom* CGInterface::Get_GDR_GUILDSTORAGEROOM() {
    return (CIFStorageRoom*)this->m_IRM.GetResObj(GDR_GUILDSTORAGEROOM, 1);
}

void CGInterface::WriteErrorMessage(byte errorType, unsigned __int16 errorCode, int colorARGB, int a5, int a6) {
    return reinterpret_cast<
        void(__thiscall*)(void*, byte, unsigned __int16, int, int, int)
    >(0x00778190)(this, errorType, errorCode, colorARGB, a5, a6);
}

void CGInterface::WriteSystemMessage(eLogType level, const wchar_t* str) {
    reinterpret_cast<void(__thiscall*)(CGInterface*, eLogType, const wchar_t*)>(0x007781B0)(this, level, str);
}

HOOK_ORIGINAL_MEMBER(0x007901c0, &CGInterface::WriteGlobalMessage)
void CGInterface::WriteGlobalMessage(unsigned char nSlot, std::n_wstring message) {
    CIFMainPopup* popup = GetMainPopup();
    CIFInventory* inventory = popup->GetInventory();

    CSOItem* item = inventory->GetItemBySlot(nSlot);

    if (item->field_28 == 0) {
        return;
    }

    const CItemData::SData* pItemData = item->GetItemData();

    if (pItemData->IsGlobalMessageScroll()) {
    /*    NEWMSG(0x704c)

            pReq << static_cast<unsigned char>(nSlot + 13u) << pItemData->m_typeId << message;

        SENDMSG()*/

            if (!g_global->m_CurrentLinkedItemName.empty() && g_global->m_LinkedGlobalItemEnd != 0) {

                NEWMSG(0x705C)
                    __int8 testaa = 1;
                __int8 testaa2 = static_cast<unsigned char>(nSlot + 13u);

                pReq << testaa << testaa2<< pItemData->m_typeId << message << g_global->m_LinkedGlobalSlot;
                g_global->m_LinkedGlobalItemEnd = 0;
                g_global->m_CurrentLinkedItemName = L"";
                SENDMSG()
            }
            else {

                NEWMSG(0x705C)
                    __int8 testaa = 2;
                __int8 testaa2 = static_cast<unsigned char>(nSlot + 13u);
                pReq << testaa << testaa2 << pItemData->m_typeId << message;
                SENDMSG()
            }
    }
}

void CGInterface::sub_787C10(SChatMetaData& meta) {
    reinterpret_cast<void(__thiscall*)(CGInterface*, SChatMetaData*)>(0x787C10)(this, &meta);
}

int CGInterface::TryParseChatCommands(const wchar_t* text, RECT& r, std::vector<void*>& v) {
    return reinterpret_cast<
        int(__thiscall*)(CGInterface*, const wchar_t*, RECT*, std::vector<void*> *)
    >(0x0078BEA0)(this, text, &r, &v);
}

void CGInterface::ToggleQuestNew() {
    reinterpret_cast<void(__thiscall*)(CGInterface*)>(0x007990e0)(this);
}

CNIFCommunityWnd* CGInterface::GetCommunityWnd() {
    return reinterpret_cast<CNIFCommunityWnd * (__thiscall*)(CGInterface*)>(0x007994f0)(this);
}

void CGInterface::FUN_00777c30(ChatType type, const wchar_t* message, D3DCOLOR color, int a5) {
    CIFChatViewer* chatViewer = m_IRM.GetResObj<CIFChatViewer>(GDR_CHATVIEWER, 1);
    chatViewer->FUN_007aca30(type, color, message, 0, a5);
}

void CGInterface::FUN_00778a10(int a2, const wchar_t* message, D3DCOLOR color) {
    reinterpret_cast<
        void(__thiscall*)(CGInterface*, int, const wchar_t*, D3DCOLOR)
    >(0x00778a10)(this, a2, message, color);
}

void CGInterface::FUN_00777cf0(const std::n_wstring& recipient) {
    reinterpret_cast<void(__thiscall*)(CGInterface*, const std::n_wstring*)>(0x00777cf0)(this, &recipient);
}

CIFSystemMessage* CGInterface::GetSystemMessageView() {
    return m_IRM.GetResObj<CIFSystemMessage>(GDR_SYSTEM_MESSAGE_VIEW, 1);
}

void CGInterface::FUN_0079a7e0(CGWndBase* pGWnd) const {
    reinterpret_cast<void(__thiscall*)(const CGInterface*, CGWndBase*)>(0x0079a7e0)(this, pGWnd);
}

void CGInterface::FUN_0079b8a0(undefined1 a1, undefined4 a2) {
    reinterpret_cast<void(__thiscall*)(CGInterface*, undefined1, undefined4)>(0x0079b8a0)(this, a1, a2);
}


void CGInterface::OnEscapePressed() {

    if (CIFFacebook::FBW->IsVisible()) {
        CIFFacebook::FBW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFDiscord::DCW->IsVisible()) {
        CIFDiscord::DCW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::SavedLoca->IsVisible()) {
        CIFMainMenu::SavedLoca->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::MoveParty->IsVisible()) {
        CIFMainMenu::MoveParty->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFAttendance::ATTW->IsVisible()) {
        CIFAttendance::ATTW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFEventMenu::EventW->IsVisible()) {
        CIFEventMenu::EventW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFPlayerChest::ChestW->IsVisible()) {
        CIFPlayerChest::ChestW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::CharW->IsVisible()) {
        CIFMainMenu::CharW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::GrantNameW->IsVisible()) {
        CIFMainMenu::GrantNameW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::TitleW->IsVisible()) {
        CIFMainMenu::TitleW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::CharlockW->IsVisible()) {
        CIFMainMenu::CharlockW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::UniqueW->IsVisible()) {
        CIFMainMenu::UniqueW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::EventW->IsVisible()) {
        CIFMainMenu::EventW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::RankW->IsVisible()) {
        CIFMainMenu::RankW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::ChangeW->IsVisible()) {
        CIFMainMenu::ChangeW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else if (CIFMainMenu::MenuW->IsVisible()) {
        CIFMainMenu::MenuW->ShowGWnd(false);
        CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    }
    else {
        reinterpret_cast<void(__thiscall*)(CGInterface*)>(0x0079d620)(this);
    }
}


void CGInterface::FUN_00777a70(undefined4 param_1, undefined4 param_2) {
    reinterpret_cast<void(__thiscall*)(CGInterface*, undefined4, undefined4)>(0x00777a70)(this, param_1, param_2);
}


void CGInterface::RequestStatIncrement(undefined4 a1, undefined4 a2, undefined4 a3, undefined4 a4) {
    if (a1 == 0x4b) {
        if (a2 == 1) {
            NEWMSG(0x7050)
                SENDMSG()
        }
        else if (a2 == 2) {
            NEWMSG(0x7051)
                SENDMSG()
        }
    }
}

void CGInterface::SwitchToStallNetwork(bool Enabled)
{
    return reinterpret_cast<void(__thiscall*)(CGInterface*, bool)>(0x00799020)(this, Enabled);
}
