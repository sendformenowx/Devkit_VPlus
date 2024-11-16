#include "NetProcessIn.h"
#include "unsorted.h"
#include "ICPlayer.h"
#include <BSLib/multibyte.h>
#include <BSLib/Debug.h>
#include "CharacterDependentData.h"
#include "TextStringManager.h"
#include "Game.h"
#include "PSMission.h"
#include "GInterface.h"
#include "GlobalDataManager.h"
#include "../../../DevKit_DLL/src/GameHelpers/GameMain.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFMainMenu.h"
#include "../../DiscordRichPresence/src/DiscordRichPresence/DiscordManager.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFChest.h"
#include "IFTargetWindow.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFDiscord.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFFacebook.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFAttendance.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFEventMenu.h"
#include "../../../DevKit_DLL/src/Special/NotificationHandler.h"
#include <string>
#include <Psapi.h>
#include <tlhelp32.h>
#define GET_OWN_GAME_ID() \
	MEMUTIL_READ_BY_PTR_OFFSET(g_pCICPlayer, 0xF8, DWORD)


#ifdef CONFIG_DEBUG_NET_RECEIVE
#define DEBUG_PRINT_CALL() printf("%s\n", __FUNCTION__);
#else
#define DEBUG_PRINT_CALL()
#endif
byte CNetProcessIn::CurrentZerk;
void CNetProcessIn::RegisterPacketHandlers() {
    BS_DEBUG("Registering Handlers");
    m_handlers.insert(std::make_pair(0x3027, &CNetProcessIn::OnUpdateGameTime));
    m_handlers.insert(std::make_pair(0x3809, &CNetProcessIn::On3809));
    m_handlers.insert(std::make_pair(0x3055, &CNetProcessIn::OnResetClient));
    m_handlers.insert(std::make_pair(0xb005, &CNetProcessIn::OnLogoutAck));
    m_handlers.insert(std::make_pair(0xb006, &CNetProcessIn::Onb006));
    m_handlers.insert(std::make_pair(0x300a, &CNetProcessIn::On300a));
    m_handlers.insert(std::make_pair(0x3405, &CNetProcessIn::On3405));
    m_handlers.insert(std::make_pair(0x34b5, &CNetProcessIn::On34b5));
    m_handlers.insert(std::make_pair(0x300c, &CNetProcessIn::On300c));
    m_handlers.insert(std::make_pair(0x34a5, &CNetProcessIn::On34a5));
    m_handlers.insert(std::make_pair(0x3013, &CNetProcessIn::OnMyCharacterData));
    m_handlers.insert(std::make_pair(0x34a6, &CNetProcessIn::On34a6));
    m_handlers.insert(std::make_pair(0x3020, &CNetProcessIn::On3020));
    m_handlers.insert(std::make_pair(0x3017, &CNetProcessIn::OnObjectListBegin));
    m_handlers.insert(std::make_pair(0x3019, &CNetProcessIn::OnObjectListData));
    m_handlers.insert(std::make_pair(0x3018, &CNetProcessIn::OnObjectListEnd));
    m_handlers.insert(std::make_pair(0x3047, &CNetProcessIn::OnChestDataBegin));
    m_handlers.insert(std::make_pair(0x3049, &CNetProcessIn::OnChestDataData));
    m_handlers.insert(std::make_pair(0x3048, &CNetProcessIn::OnChestDataEnd));
    m_handlers.insert(std::make_pair(0x3015, &CNetProcessIn::OnObjectEntered));
    m_handlers.insert(std::make_pair(0x3016, &CNetProcessIn::OnObjectLeft));
    m_handlers.insert(std::make_pair(0x3076, &CNetProcessIn::On3076));
    m_handlers.insert(std::make_pair(0x30bf, &CNetProcessIn::On30bf));
    m_handlers.insert(std::make_pair(0xb0cb, &CNetProcessIn::Onb0cb));
    m_handlers.insert(std::make_pair(0xb03c, &CNetProcessIn::Onb03c));
    m_handlers.insert(std::make_pair(0x3092, &CNetProcessIn::On3092));
    m_handlers.insert(std::make_pair(0x30df, &CNetProcessIn::On30df));
    m_handlers.insert(std::make_pair(0x30cd, &CNetProcessIn::On30cd));
    m_handlers.insert(std::make_pair(0x30ce, &CNetProcessIn::On30ce));
    m_handlers.insert(std::make_pair(0x30d3, &CNetProcessIn::On30d3));
    m_handlers.insert(std::make_pair(0x30C1, &CNetProcessIn::On30C1));
    m_handlers.insert(std::make_pair(0x30C2, &CNetProcessIn::On30C2));
    m_handlers.insert(std::make_pair(0x30C3, &CNetProcessIn::On30C3));
    m_handlers.insert(std::make_pair(0x30C8, &CNetProcessIn::On30C8));
    m_handlers.insert(std::make_pair(0xB0C6, &CNetProcessIn::OnB0C6));
    m_handlers.insert(std::make_pair(0x30C9, &CNetProcessIn::On30C9));
    m_handlers.insert(std::make_pair(0x30E7, &CNetProcessIn::On30E7));
    m_handlers.insert(std::make_pair(0xB0C7, &CNetProcessIn::OnB0C7));
    m_handlers.insert(std::make_pair(0x30CA, &CNetProcessIn::On30CA));
    m_handlers.insert(std::make_pair(0xB116, &CNetProcessIn::OnB116));
    m_handlers.insert(std::make_pair(0xB117, &CNetProcessIn::OnB117));
    m_handlers.insert(std::make_pair(0xB420, &CNetProcessIn::OnB420));
    m_handlers.insert(std::make_pair(0x30D4, &CNetProcessIn::On30D4));
    m_handlers.insert(std::make_pair(0x3054, &CNetProcessIn::On3054));
    m_handlers.insert(std::make_pair(0x3056, &CNetProcessIn::On3056));
    m_handlers.insert(std::make_pair(0x304E, &CNetProcessIn::On304E));
    m_handlers.insert(std::make_pair(0x3052, &CNetProcessIn::On3052));
    m_handlers.insert(std::make_pair(0x3057, &CNetProcessIn::On3057));
    m_handlers.insert(std::make_pair(0xB045, &CNetProcessIn::OnB045));
    m_handlers.insert(std::make_pair(0x303D, &CNetProcessIn::On303D));
    m_handlers.insert(std::make_pair(0x30D2, &CNetProcessIn::On30D2));
    m_handlers.insert(std::make_pair(0x30CF, &CNetProcessIn::On30CF));
    m_handlers.insert(std::make_pair(0x3011, &CNetProcessIn::On3011));
    m_handlers.insert(std::make_pair(0x3058, &CNetProcessIn::On3058));
    m_handlers.insert(std::make_pair(0xB025, &CNetProcessIn::OnB025));
    m_handlers.insert(std::make_pair(0x3026, &CNetProcessIn::OnChatReceive));
    m_handlers.insert(std::make_pair(0x3091, &CNetProcessIn::On3091));
    m_handlers.insert(std::make_pair(0x302D, &CNetProcessIn::On302D));
    m_handlers.insert(std::make_pair(0xB021, &CNetProcessIn::OnB021));
    m_handlers.insert(std::make_pair(0xB024, &CNetProcessIn::OnB024));
    m_handlers.insert(std::make_pair(0xB023, &CNetProcessIn::OnB023));
    m_handlers.insert(std::make_pair(0x3028, &CNetProcessIn::On3028));
    m_handlers.insert(std::make_pair(0xB04F, &CNetProcessIn::OnB04F));
    m_handlers.insert(std::make_pair(0x30D0, &CNetProcessIn::On30D0));
    m_handlers.insert(std::make_pair(0x3200, &CNetProcessIn::On3200));
    m_handlers.insert(std::make_pair(0xB070, &CNetProcessIn::OnB070));
    m_handlers.insert(std::make_pair(0xB071, &CNetProcessIn::OnB071));
    m_handlers.insert(std::make_pair(0xB0BD, &CNetProcessIn::OnB0BD));
    m_handlers.insert(std::make_pair(0x330F, &CNetProcessIn::On330F));
    m_handlers.insert(std::make_pair(0xB0BE, &CNetProcessIn::OnB0BE));
    m_handlers.insert(std::make_pair(0xB0BC, &CNetProcessIn::OnB0BC));
    m_handlers.insert(std::make_pair(0xB072, &CNetProcessIn::OnB072));
    m_handlers.insert(std::make_pair(0x30A6, &CNetProcessIn::On30A6));
    m_handlers.insert(std::make_pair(0x30D1, &CNetProcessIn::On30D1));
    m_handlers.insert(std::make_pair(0x3206, &CNetProcessIn::On3206));
    m_handlers.insert(std::make_pair(0xB0A1, &CNetProcessIn::OnB0A1));
    m_handlers.insert(std::make_pair(0xB0A2, &CNetProcessIn::OnB0A2));
    m_handlers.insert(std::make_pair(0xB203, &CNetProcessIn::OnB203));
    m_handlers.insert(std::make_pair(0xB202, &CNetProcessIn::OnB202));
    m_handlers.insert(std::make_pair(0xB034, &CNetProcessIn::OnB034));
    m_handlers.insert(std::make_pair(0x3555, &CNetProcessIn::On3535));
    m_handlers.insert(std::make_pair(0x3038, &CNetProcessIn::On3038));
    m_handlers.insert(std::make_pair(0x3039, &CNetProcessIn::On3039));
    m_handlers.insert(std::make_pair(0x3036, &CNetProcessIn::On3036));
    m_handlers.insert(std::make_pair(0xB03E, &CNetProcessIn::OnB03E));
    m_handlers.insert(std::make_pair(0xB03F, &CNetProcessIn::OnB03F));
    m_handlers.insert(std::make_pair(0x304D, &CNetProcessIn::On304D));
    m_handlers.insert(std::make_pair(0xB04C, &CNetProcessIn::OnB04C));
    m_handlers.insert(std::make_pair(0x3068, &CNetProcessIn::On3068));
    m_handlers.insert(std::make_pair(0x305C, &CNetProcessIn::On305C));
    m_handlers.insert(std::make_pair(0x30E0, &CNetProcessIn::On30E0));
    m_handlers.insert(std::make_pair(0x3040, &CNetProcessIn::On3040));
    m_handlers.insert(std::make_pair(0x3201, &CNetProcessIn::On3201));
    m_handlers.insert(std::make_pair(0x3041, &CNetProcessIn::On3041));
    m_handlers.insert(std::make_pair(0x3042, &CNetProcessIn::On3042));
    m_handlers.insert(std::make_pair(0x3153, &CNetProcessIn::On3153));
    m_handlers.insert(std::make_pair(0x3154, &CNetProcessIn::On3154));
    m_handlers.insert(std::make_pair(0xB046, &CNetProcessIn::OnB046));
    m_handlers.insert(std::make_pair(0xB04B, &CNetProcessIn::OnB04B));
    m_handlers.insert(std::make_pair(0xB0C0, &CNetProcessIn::OnB0C0));
    m_handlers.insert(std::make_pair(0xB050, &CNetProcessIn::OnB050));
    m_handlers.insert(std::make_pair(0xB051, &CNetProcessIn::OnB051));
    m_handlers.insert(std::make_pair(0xB0C5, &CNetProcessIn::OnB0C5));
    m_handlers.insert(std::make_pair(0xB059, &CNetProcessIn::OnB059));
    m_handlers.insert(std::make_pair(0xB05A, &CNetProcessIn::OnB05A));
    m_handlers.insert(std::make_pair(0xB074, &CNetProcessIn::OnB074));
    m_handlers.insert(std::make_pair(0x30EB, &CNetProcessIn::On30EB));
    m_handlers.insert(std::make_pair(0xB0EA, &CNetProcessIn::OnB0EA));
    m_handlers.insert(std::make_pair(0xB05B, &CNetProcessIn::OnB05B));
    m_handlers.insert(std::make_pair(0x34B1, &CNetProcessIn::On34B1));
    m_handlers.insert(std::make_pair(0xB060, &CNetProcessIn::OnB060));
    m_handlers.insert(std::make_pair(0x3864, &CNetProcessIn::On3864));
    m_handlers.insert(std::make_pair(0x3065, &CNetProcessIn::On3065));
    m_handlers.insert(std::make_pair(0xB062, &CNetProcessIn::OnB062));
    m_handlers.insert(std::make_pair(0xB067, &CNetProcessIn::OnB067));
    m_handlers.insert(std::make_pair(0xB069, &CNetProcessIn::OnB069));
    m_handlers.insert(std::make_pair(0xB06A, &CNetProcessIn::OnB06A));
    m_handlers.insert(std::make_pair(0xB06B, &CNetProcessIn::OnB06B));
    m_handlers.insert(std::make_pair(0xB06C, &CNetProcessIn::OnB06C));
    m_handlers.insert(std::make_pair(0x706D, &CNetProcessIn::On706D));
    m_handlers.insert(std::make_pair(0xB06D, &CNetProcessIn::OnB06D));
    m_handlers.insert(std::make_pair(0xB081, &CNetProcessIn::OnB081));
    m_handlers.insert(std::make_pair(0x3080, &CNetProcessIn::On3080));
    m_handlers.insert(std::make_pair(0x3085, &CNetProcessIn::On3085));
    m_handlers.insert(std::make_pair(0xB082, &CNetProcessIn::OnB082));
    m_handlers.insert(std::make_pair(0xB083, &CNetProcessIn::OnB083));
    m_handlers.insert(std::make_pair(0xB084, &CNetProcessIn::OnB084));
    m_handlers.insert(std::make_pair(0x3089, &CNetProcessIn::On3089));
    m_handlers.insert(std::make_pair(0x3086, &CNetProcessIn::On3086));
    m_handlers.insert(std::make_pair(0x3087, &CNetProcessIn::On3087));
    m_handlers.insert(std::make_pair(0x3088, &CNetProcessIn::On3088));
    m_handlers.insert(std::make_pair(0x30E8, &CNetProcessIn::On30E8));
    m_handlers.insert(std::make_pair(0x308C, &CNetProcessIn::On308C));
    m_handlers.insert(std::make_pair(0xB0B1, &CNetProcessIn::OnB0B1));
    m_handlers.insert(std::make_pair(0x30B8, &CNetProcessIn::On30B8));
    m_handlers.insert(std::make_pair(0xB0B2, &CNetProcessIn::OnB0B2));
    m_handlers.insert(std::make_pair(0x30B9, &CNetProcessIn::On30B9));
    m_handlers.insert(std::make_pair(0x30B7, &CNetProcessIn::On30B7));
    m_handlers.insert(std::make_pair(0xB0B3, &CNetProcessIn::OnB0B3));
    m_handlers.insert(std::make_pair(0xB0B5, &CNetProcessIn::OnB0B5));
    m_handlers.insert(std::make_pair(0xB0B4, &CNetProcessIn::OnB0B4));
    m_handlers.insert(std::make_pair(0xB0BA, &CNetProcessIn::OnB0BA));
    m_handlers.insert(std::make_pair(0x30BB, &CNetProcessIn::On30BB));
    m_handlers.insert(std::make_pair(0xB0A7, &CNetProcessIn::OnB0A7));
    m_handlers.insert(std::make_pair(0xB010, &CNetProcessIn::OnB010));
    m_handlers.insert(std::make_pair(0x30D6, &CNetProcessIn::On30D6));
    m_handlers.insert(std::make_pair(0x30D7, &CNetProcessIn::On30D7));
    m_handlers.insert(std::make_pair(0x30D5, &CNetProcessIn::On30D5));
    m_handlers.insert(std::make_pair(0xB0D8, &CNetProcessIn::OnB0D8));
    m_handlers.insert(std::make_pair(0xB0D9, &CNetProcessIn::OnB0D9));
    m_handlers.insert(std::make_pair(0x30EC, &CNetProcessIn::On30EC));
    m_handlers.insert(std::make_pair(0x30DC, &CNetProcessIn::On30DC));
    m_handlers.insert(std::make_pair(0xB515, &CNetProcessIn::OnB515));
    m_handlers.insert(std::make_pair(0x3514, &CNetProcessIn::On3514));
    m_handlers.insert(std::make_pair(0x3CA2, &CNetProcessIn::On3CA2));
    m_handlers.insert(std::make_pair(0x30E6, &CNetProcessIn::On30E6));
    m_handlers.insert(std::make_pair(0xB0E1, &CNetProcessIn::OnB0E1));
    m_handlers.insert(std::make_pair(0xB0E2, &CNetProcessIn::OnB0E2));
    m_handlers.insert(std::make_pair(0xB0E3, &CNetProcessIn::OnB0E3));
    m_handlers.insert(std::make_pair(0xB0E4, &CNetProcessIn::OnB0E4));
    m_handlers.insert(std::make_pair(0xB0E5, &CNetProcessIn::OnB0E5));
    m_handlers.insert(std::make_pair(0xB0E6, &CNetProcessIn::OnB0E6));
    m_handlers.insert(std::make_pair(0xB0F0, &CNetProcessIn::OnB0F0));
    m_handlers.insert(std::make_pair(0x38F5, &CNetProcessIn::On38F5));
    m_handlers.insert(std::make_pair(0xB0F1, &CNetProcessIn::OnB0F1));
    m_handlers.insert(std::make_pair(0xB0F8, &CNetProcessIn::OnB0F8));
    m_handlers.insert(std::make_pair(0xB0F3, &CNetProcessIn::OnB0F3));
    m_handlers.insert(std::make_pair(0x30FF, &CNetProcessIn::On30FF));
    m_handlers.insert(std::make_pair(0x3100, &CNetProcessIn::On3100));
    m_handlers.insert(std::make_pair(0xB0F2, &CNetProcessIn::OnB0F2));
    m_handlers.insert(std::make_pair(0xB0F4, &CNetProcessIn::OnB0F4));
    m_handlers.insert(std::make_pair(0x34B3, &CNetProcessIn::On34B3));
    m_handlers.insert(std::make_pair(0x3101, &CNetProcessIn::On3101));
    m_handlers.insert(std::make_pair(0x34B4, &CNetProcessIn::On34B4));
    m_handlers.insert(std::make_pair(0xB0F9, &CNetProcessIn::OnB0F9));
    m_handlers.insert(std::make_pair(0xB0F6, &CNetProcessIn::OnB0F6));
    m_handlers.insert(std::make_pair(0xB0FA, &CNetProcessIn::OnB0FA));
    m_handlers.insert(std::make_pair(0xB103, &CNetProcessIn::OnB103));
    m_handlers.insert(std::make_pair(0xB104, &CNetProcessIn::OnB104));
    m_handlers.insert(std::make_pair(0xB105, &CNetProcessIn::OnB105));
    m_handlers.insert(std::make_pair(0xB106, &CNetProcessIn::OnB106));
    m_handlers.insert(std::make_pair(0x3908, &CNetProcessIn::On3908));
    m_handlers.insert(std::make_pair(0xB107, &CNetProcessIn::OnB107));
    m_handlers.insert(std::make_pair(0xB0FB, &CNetProcessIn::OnB0FB));
    m_handlers.insert(std::make_pair(0x3102, &CNetProcessIn::On3102));
    m_handlers.insert(std::make_pair(0xB0FC, &CNetProcessIn::OnB0FC));
    m_handlers.insert(std::make_pair(0xB0FD, &CNetProcessIn::OnB0FD));
    m_handlers.insert(std::make_pair(0x3109, &CNetProcessIn::On3109));
    m_handlers.insert(std::make_pair(0x7110, &CNetProcessIn::On7110));
    m_handlers.insert(std::make_pair(0xB110, &CNetProcessIn::OnB110));
    m_handlers.insert(std::make_pair(0xB112, &CNetProcessIn::OnB112));
    m_handlers.insert(std::make_pair(0xB114, &CNetProcessIn::OnB114));
    m_handlers.insert(std::make_pair(0xB113, &CNetProcessIn::OnB113));
    m_handlers.insert(std::make_pair(0xB501, &CNetProcessIn::OnB501));
    m_handlers.insert(std::make_pair(0x30EF, &CNetProcessIn::On30EF));
    m_handlers.insert(std::make_pair(0x3305, &CNetProcessIn::On3305));
    m_handlers.insert(std::make_pair(0xB302, &CNetProcessIn::OnB302));
    m_handlers.insert(std::make_pair(0xB304, &CNetProcessIn::OnB304));
    m_handlers.insert(std::make_pair(0x7302, &CNetProcessIn::On7302));
    m_handlers.insert(std::make_pair(0xB30B, &CNetProcessIn::OnB30B));
    m_handlers.insert(std::make_pair(0xB308, &CNetProcessIn::OnB308));
    m_handlers.insert(std::make_pair(0xB309, &CNetProcessIn::OnB309));
    m_handlers.insert(std::make_pair(0xB30A, &CNetProcessIn::OnB30A));
    m_handlers.insert(std::make_pair(0x3B07, &CNetProcessIn::On3B07));
    m_handlers.insert(std::make_pair(0x3204, &CNetProcessIn::On3204));
    m_handlers.insert(std::make_pair(0xB155, &CNetProcessIn::OnB155));
    m_handlers.insert(std::make_pair(0x3156, &CNetProcessIn::On3156));
    m_handlers.insert(std::make_pair(0xB157, &CNetProcessIn::OnB157));
    m_handlers.insert(std::make_pair(0xB150, &CNetProcessIn::OnB150));
    m_handlers.insert(std::make_pair(0xB151, &CNetProcessIn::OnB151));
    m_handlers.insert(std::make_pair(0xB16A, &CNetProcessIn::OnB16A));
    m_handlers.insert(std::make_pair(0x3207, &CNetProcessIn::On3207));
    m_handlers.insert(std::make_pair(0xB0ED, &CNetProcessIn::OnB0ED));
    m_handlers.insert(std::make_pair(0x34BA, &CNetProcessIn::On34BA));
    m_handlers.insert(std::make_pair(0xB402, &CNetProcessIn::OnB402));
    m_handlers.insert(std::make_pair(0xFFC, &CNetProcessIn::OnFFC));
    m_handlers.insert(std::make_pair(0x2000, &CNetProcessIn::On2000));
    m_handlers.insert(std::make_pair(0xFFD, &CNetProcessIn::OnFFD));
    m_handlers.insert(std::make_pair(0xB05E, &CNetProcessIn::OnB05E));
    m_handlers.insert(std::make_pair(0x3078, &CNetProcessIn::On3078));
    ///MENU PACKETS
    m_handlers.insert(std::make_pair(0x180F, &CNetProcessIn::NoticeColor));
    m_handlers.insert(std::make_pair(0x181A, &CNetProcessIn::UniqueLog));
    m_handlers.insert(std::make_pair(0x181B, &CNetProcessIn::DynamicRanking));
    m_handlers.insert(std::make_pair(0x5097, &CNetProcessIn::LoadChest));
    m_handlers.insert(std::make_pair(0x5098, &CNetProcessIn::AddItemChest));
    m_handlers.insert(std::make_pair(0x5099, &CNetProcessIn::RemoveItemChest));

    m_handlers.insert(std::make_pair(0x5100, &CNetProcessIn::Charlock));
    m_handlers.insert(std::make_pair(0x5101, &CNetProcessIn::TitleManager));
    m_handlers.insert(std::make_pair(0x5102, &CNetProcessIn::TitleManageriSro));
    m_handlers.insert(std::make_pair(0x5103, &CNetProcessIn::CharAnalyzer));
    m_handlers.insert(std::make_pair(0x5104, &CNetProcessIn::EventSchedule));
    m_handlers.insert(std::make_pair(0x5105, &CNetProcessIn::ChangeLog));
    ///MENU PACKETS END
    ///Character Icon Packets
    /// Left Icons
    m_handlers.insert(std::make_pair(0x5106, &CNetProcessIn::LeftCharIconPath));
    m_handlers.insert(std::make_pair(0x5107, &CNetProcessIn::LeftCharIcon));
    m_handlers.insert(std::make_pair(0x5108, &CNetProcessIn::UpdateLeftIcon));
    m_handlers.insert(std::make_pair(0x5109, &CNetProcessIn::RemoveLeftIcon));
    ///end left icon packets
    /// RightIcons
    m_handlers.insert(std::make_pair(0x5110, &CNetProcessIn::RightIconPath));
    m_handlers.insert(std::make_pair(0x5111, &CNetProcessIn::RightIcon));
    m_handlers.insert(std::make_pair(0x5112, &CNetProcessIn::UpdateRightIcon));
    m_handlers.insert(std::make_pair(0x5113, &CNetProcessIn::RemoveRightIcon));
    /// end right icons
    /// Up Icons
    m_handlers.insert(std::make_pair(0x5114, &CNetProcessIn::UpCharIconPath));
    m_handlers.insert(std::make_pair(0x5115, &CNetProcessIn::UpCharIcon));
    m_handlers.insert(std::make_pair(0x5116, &CNetProcessIn::UpdateUpIcon));
    m_handlers.insert(std::make_pair(0x5117, &CNetProcessIn::RemoveUpIcon));
    /// end up icons
    /// name title colors
    m_handlers.insert(std::make_pair(0x5118, &CNetProcessIn::CharNameColor));
    m_handlers.insert(std::make_pair(0x5119, &CNetProcessIn::UpdateNameColor));
    m_handlers.insert(std::make_pair(0x5120, &CNetProcessIn::RemoveNameColor));
    m_handlers.insert(std::make_pair(0x5121, &CNetProcessIn::TitleColor));
    m_handlers.insert(std::make_pair(0x5122, &CNetProcessIn::UpdateTitleColor));;
    m_handlers.insert(std::make_pair(0x5123, &CNetProcessIn::RemoveTitleColor));;
    /// end of colors
    /// newtitles
    m_handlers.insert(std::make_pair(0x5124, &CNetProcessIn::NewTitles));
    m_handlers.insert(std::make_pair(0x5136, &CNetProcessIn::NewCostomTitleAdd));
    m_handlers.insert(std::make_pair(0x5137, &CNetProcessIn::NewCostomTitlesAddAll));
    m_handlers.insert(std::make_pair(0x5138, &CNetProcessIn::NewisroTitlesAdd));
    m_handlers.insert(std::make_pair(0x5139, &CNetProcessIn::NewisroTitlesAddAll));    
    m_handlers.insert(std::make_pair(0x5140, &CNetProcessIn::TitleManagerColors));

    m_handlers.insert(std::make_pair(0x5141, &CNetProcessIn::BotSettings));


    m_handlers.insert(std::make_pair(0x5125, &CNetProcessIn::UpdateNewTitles));
    m_handlers.insert(std::make_pair(0x5126, &CNetProcessIn::RemoveNewTitles));

    ///others
    m_handlers.insert(std::make_pair(0x5127, &CNetProcessIn::DpsMeter));
    m_handlers.insert(std::make_pair(0x5128, &CNetProcessIn::SurvivalKills));
    m_handlers.insert(std::make_pair(0x5129, &CNetProcessIn::FtwPlayerKills));
    m_handlers.insert(std::make_pair(0x5130, &CNetProcessIn::FtwGuildKills));
    m_handlers.insert(std::make_pair(0x5131, &CNetProcessIn::FtwUnionKills));

    m_handlers.insert(std::make_pair(0x1339, &CNetProcessIn::LinkedItemColor));
    m_handlers.insert(std::make_pair(0x1325, &CNetProcessIn::RegisterStatus));
    ///REVERSE
    m_handlers.insert(std::make_pair(0x181F, &CNetProcessIn::SavedLocations));
    m_handlers.insert(std::make_pair(0x201A, &CNetProcessIn::AttendanceRewards));
    m_handlers.insert(std::make_pair(0x201B, &CNetProcessIn::AttendanceEvent));

    m_handlers.insert(std::make_pair(0x5135, &CNetProcessIn::EventSuitRegionId));
}

BYTE CNetProcessIn::AttendanceSetting;
BYTE CNetProcessIn::EventMenuSetting;
BYTE CNetProcessIn::FacebookSetting;
BYTE CNetProcessIn::DiscordSetting;
BYTE CNetProcessIn::ChestSetting;
std::n_string CNetProcessIn::DiscordURL;
std::n_string CNetProcessIn::FacebookURL;
int CNetProcessIn::PartyMaxLevel;
void CNetProcessIn::EventSuitRegionId(CMsgStreamBuffer& msg)
{
    int sCount;
    msg >> sCount;
    unsigned __int16 RegionID;
    BYTE i = 0;
    while (i < sCount && sCount > 0) {
        i++;
        msg >> RegionID;

        std::map<unsigned __int16, int>::iterator region = g_pCICPlayer->SuitRegions.find(RegionID);
        if (region == g_pCICPlayer->SuitRegions.end())
        {
            g_pCICPlayer->SuitRegions.insert((std::pair<unsigned __int16, int>(RegionID, 1)));
        }

    }
}

void CNetProcessIn::AttendanceEvent(CMsgStreamBuffer& msg) {
    BYTE DayCount = 0;
    int i = 0;
    while (i < 28 && 28 > 0) {
        i++;
        msg >> DayCount;
        CIFAttendance::ATTW->OK[i - 1]->ShowGWnd(DayCount);
    }
    msg.FlushRemaining();
}
void CNetProcessIn::AttendanceRewards(CMsgStreamBuffer& msg)
{
    int count;
    msg >> count;
    int i = 0;
    while (i < count && count > 0) {
        i++;
        BYTE RewardID = 0;
        msg >> RewardID;

        int Days2;
        msg >> Days2;

        int ItemID;
        msg >> ItemID;

        int Unit;
        msg >> Unit;

        std::wstring itemname = L"";
        std::wstring iconpath = L"";
        if (CGlobalDataManager* g_datamanager = CGlobalDataManager::Get()) {
            if (ObjectData* uqdata = g_datamanager->GetObjectData(ItemID))
            {
                itemname = g_CTextStringManager->GetStringByNameStrID(&uqdata->ObjNameStrID)->c_str();
                iconpath = TO_WSTRING(&uqdata->AssocFileIcon);
            }
        }
        wchar_t Days[255];
        swprintf_s(Days, L"%d Days", Days2);

        wchar_t Units[255];
        swprintf_s(Units, L"%d", Unit);
        std::n_wstring test(Units);
        std::n_wstring UnitCount = test + L" Count";
        if (RewardID >= 1 && RewardID <= 10)
        {
            CIFAttendance::ATTW->items[RewardID - 1]->TB_Func_13(TO_NSTRING(iconpath), 0, 0);
            CIFAttendance::ATTW->items[RewardID - 1]->SetTooltipText(&UnitCount);;
            CIFAttendance::ATTW->items[RewardID - 1]->SetToolTipSetting(0x80);
            CIFAttendance::ATTW->itemnames[RewardID - 1]->SetText(itemname.c_str());
            CIFAttendance::ATTW->writeday[RewardID - 1]->SetText(Days);
        }

    }
}
void CNetProcessIn::SavedLocations(CMsgStreamBuffer& msg)
{
    int count;
    msg >> count;
    int i = 0;
    while (i < count && count > 0) {
        i++;

        BYTE locationID;
        std::n_wstring RegionName;
        msg >> locationID >> RegionName;
        if (locationID == 1)
        {
            CIFMainMenu::SavedLoca->TeleportLoc1->SetText(RegionName.c_str());
        }
        if (locationID == 2)
        {
            CIFMainMenu::SavedLoca->TeleportLoc2->SetText(RegionName.c_str());
        }
        if (locationID == 3)
        {
            CIFMainMenu::SavedLoca->TeleportLoc3->SetText(RegionName.c_str());
        }
        if (locationID == 4)
        {
            CIFMainMenu::SavedLoca->TeleportLoc4->SetText(RegionName.c_str());
        }
    }
    msg.FlushRemaining();
}
void CNetProcessIn::RegisterStatus(CMsgStreamBuffer& msg)
{
    byte status = 0;
    msg >> status;
    if (status == 0) // deactive
    {
        CIFEventMenu::EventW->regstatus[1]->SetText(L"Registers closed.");
        CIFEventMenu::EventW->regstatus[1]->m_FontTexture.SetColor(D3DCOLOR_ARGB(255, 255, 0, 0));

    }
    else if (status == 1) //active
    {
        CIFEventMenu::EventW->regstatus[1]->SetText(L"Registers opened.");
        CIFEventMenu::EventW->regstatus[1]->m_FontTexture.SetColor(D3DCOLOR_ARGB(255, 0, 255, 0));
    }
    else if (status == 2)
    {
        CIFEventMenu::EventW->regstatus[2]->SetText(L"Registers closed.");
        CIFEventMenu::EventW->regstatus[2]->m_FontTexture.SetColor(D3DCOLOR_ARGB(255, 255, 0, 0));
    }
    else if (status == 3)
    {
        CIFEventMenu::EventW->regstatus[2]->SetText(L"Registers opened.");
        CIFEventMenu::EventW->regstatus[2]->m_FontTexture.SetColor(D3DCOLOR_ARGB(255, 0, 255, 0));
    }
    else if (status == 4)
    {
        CIFEventMenu::EventW->regstatus[3]->SetText(L"Registers closed.");
        CIFEventMenu::EventW->regstatus[3]->m_FontTexture.SetColor(D3DCOLOR_ARGB(255, 255, 0, 0));
    }
    else if (status == 5)
    {
        CIFEventMenu::EventW->regstatus[3]->SetText(L"Registers opened.");
        CIFEventMenu::EventW->regstatus[3]->m_FontTexture.SetColor(D3DCOLOR_ARGB(255, 0, 255, 0));
    }
}

/// MENU
void CNetProcessIn::NoticeColor(CMsgStreamBuffer& msg)
{
    __int8 operators = 0;
    msg >> operators;
    std::n_wstring Message;
    msg >> Message;

    D3DCOLOR color;
    color = D3DCOLOR_RGBA(0xff, 0xae, 0xc3, 255);
    if (operators == 1) {
        g_pCGInterface->ShowMessage_Quest(Message.c_str());
        g_pCGInterface->ShowLogMessage(0x11654c, Message.c_str());
    }
    else if (operators == 2) {
        g_pCGInterface->ShowMessage_Notice(Message.c_str());
        g_pCGInterface->FUN_00777c30(CHAT_AllGM, Message.c_str(), color, 1);
    }
    else if (operators == 3) {
        g_pCGInterface->ShowMessage_Warning(Message.c_str());
        g_pCGInterface->ShowLogMessage(0x314169, Message.c_str());
    }
    else if (operators == 4) {
        g_pCGInterface->ShowMessage_Purble(Message.c_str());
        g_pCGInterface->ShowLogMessage(0x4B0082, Message.c_str());
    }
    else if (operators == 5) {
        g_pCGInterface->ShowMessage_Orange(Message.c_str());
        g_pCGInterface->ShowLogMessage(0xff6347, Message.c_str());
    }
    else if (operators == 6) {
        g_pCGInterface->ShowMessage_Quest(Message.c_str());
    }
    else if (operators == 7) {
        g_pCGInterface->ShowMessage_Notice(Message.c_str());
    }
    else if (operators == 8) {
        g_pCGInterface->ShowMessage_Warning(Message.c_str());
    }
    else if (operators == 9) {
        g_pCGInterface->ShowMessage_Purble(Message.c_str());
    }
    else if (operators == 10) {
        g_pCGInterface->ShowMessage_Orange(Message.c_str());
    }
    else if (operators == 11) {
        g_pCGInterface->ShowLogMessage(color, Message.c_str()); // RED SYSTEM MESSAGE
    }

    else;

    msg.FlushRemaining();
}


void CNetProcessIn::UniqueLog(CMsgStreamBuffer& msg)
{

    unsigned __int8 sCount;
    msg >> sCount;// bunu düzenleyebilrmisin jendine göre
    BYTE i = 0;

    CIFUniqueLog::UQlist.clear();

    while (i < sCount && sCount > 0)
    {
        i++;
        int DBID;
        msg >> DBID;
        std::n_wstring State;
        msg >> State;
        std::n_wstring Killer;
        msg >> Killer;

        std::n_wstring UqName = L"";
        if (CGlobalDataManager* g_datamanager = CGlobalDataManager::Get())
        {
            if (CharData* uqdata = g_datamanager->GetCharData(DBID))
            {
                UqName = g_CTextStringManager->GetStringByNameStrID(&uqdata->ObjNameStrID)->c_str();
            }
        }

        CIFUniqueLog::UniqueLogstru uq = CIFUniqueLog::UniqueLogstru();
        uq.LifeState = State.c_str();
        uq.Killer = Killer.c_str();
        uq.UqName = UqName.c_str();
        CIFUniqueLog::UQlist.push_back(uq);
    }
    CIFMainMenu::UniqueW->UpdateLog();
    msg.FlushRemaining();


}

void CNetProcessIn::DynamicRanking(CMsgStreamBuffer& msg) {
    BYTE sCount;
    BYTE RankType;
    msg >> RankType >> sCount;
    BYTE i = 0;

    while (i < sCount && sCount > 0) {
        i++;
        int No;
        std::n_wstring Name;
        std::n_wstring Guild;
        std::n_wstring Points;
        msg >> No >> Name >> Guild >> Points;

        CIFRank::RankStruct uqR = CIFRank::RankStruct();
        uqR.LineNum = No;
        uqR.Charname = Name.c_str();

        if (Guild == L"dummy")
        {
            uqR.Guild = L"<No Guild>";
        }
        else
        {
            uqR.Guild = Guild.c_str();
        }
        uqR.Points = Points.c_str();


        if (RankType == 1)//uq rank
        {
            CIFRank::UniquesRankList.push_back(uqR);
            CIFMainMenu::RankW->UpdateUniqueRank();
        }
        if (RankType == 2)//honor rank
        {
            CIFRank::HonorRankList.push_back(uqR);
            CIFMainMenu::RankW->UpdateHonorRank();
        }
        if (RankType == 3)//pvp rank
        {
            CIFRank::JobTraderRank.push_back(uqR);
            CIFMainMenu::RankW->UpdateTraderRank();

        }
        if (RankType == 4)//Hunter rank
        {
            CIFRank::JobHunterRank.push_back(uqR);
            CIFMainMenu::RankW->UpdateHunterRank();
        }
        if (RankType == 5)//Thief rank bu kod buraya neden sekiyor aq anlamadm ki
        {
            CIFRank::JobRankTFList.push_back(uqR);
            CIFMainMenu::RankW->UpdateJobThiefRank();
        }
    }

}

void CNetProcessIn::LoadChest(CMsgStreamBuffer& msg) {

    int sCount;
    int No;
    std::n_string ItemIDs;
    std::n_string ItemCode;
    std::n_string CodeName;
    bool RandomStat;
    std::n_string Count;
    std::n_string From;
    std::n_string Date;
    std::n_string OptLevel;
    msg >> sCount;
    BYTE i = 0;
    while (i < sCount && sCount > 0) {
        i++;
        msg >> ItemIDs >> No >> ItemCode >> CodeName >> Count >> RandomStat >> OptLevel >> From >> Date;

        std::wstring ItemName = g_CTextStringManager->GetStringTextByCode(Convert(ItemCode))->c_str();

        CIFPlayerChest::Chest ChestStru = CIFPlayerChest::Chest();
        ChestStru.ItemID = TO_WSTRING(ItemIDs).c_str();
        ChestStru.LineNum = No;
        ChestStru.NameStrID128 = ItemName.c_str();
        ChestStru.CodeName128 = TO_WSTRING(CodeName).c_str();
        ChestStru.Count = TO_WSTRING(Count).c_str();
        ChestStru.RandomStat = RandomStat;
        ChestStru.OptLevel = OptLevel;
        ChestStru.From = TO_WSTRING(From).c_str();
        ChestStru.Date = TO_WSTRING(Date).c_str();
        CIFPlayerChest::ChestW->ChestList.push_back(ChestStru);

    }
    CIFPlayerChest::ChestW->UpdateChest();
    msg.FlushRemaining();
}
void CNetProcessIn::AddItemChest(CMsgStreamBuffer& msg)
{
    int No;
    std::n_string ItemIDs;
    std::n_string ItemCode;
    std::n_string CodeName;
    bool RandomStat;
    std::n_string Count;
    std::n_string From;
    std::n_string Date;
    std::n_string OptLevel;
    msg >> ItemIDs >> No >> ItemCode >> CodeName >> Count >> RandomStat >> OptLevel >> From >> Date;

    std::wstring ItemName = g_CTextStringManager->GetStringTextByCode(Convert(ItemCode))->c_str();

    CIFPlayerChest::Chest ChestStru = CIFPlayerChest::Chest();
    ChestStru.ItemID = TO_WSTRING(ItemIDs).c_str();
    ChestStru.LineNum = No;
    ChestStru.NameStrID128 = ItemName.c_str();
    ChestStru.CodeName128 = TO_WSTRING(CodeName).c_str();
    ChestStru.Count = TO_WSTRING(Count).c_str();
    ChestStru.RandomStat = RandomStat;
    ChestStru.OptLevel = OptLevel;
    ChestStru.From = TO_WSTRING(From).c_str();
    ChestStru.Date = TO_WSTRING(Date).c_str();

    if (CIFPlayerChest::ChestList.size() < 101) {
        CIFPlayerChest::ChestList.push_back(ChestStru);
        CIFPlayerChest::ChestW->UpdateChest();
    }
    msg.FlushRemaining();
}
void CNetProcessIn::RemoveItemChest(CMsgStreamBuffer& msg)
{
    BYTE TYPE;
    std::n_string CodeName;
    msg >> TYPE;
    if (TYPE == 1) {
        msg >> CodeName;
        for (std::vector<CIFPlayerChest::Chest>::iterator it = CIFPlayerChest::ChestList.begin();
            it != CIFPlayerChest::ChestList.end(); ++it) {
            if (wcscmp(it->ItemID.c_str(), TO_WSTRING(CodeName).c_str()) == 0) {
                CIFPlayerChest::ChestW->Clear();
                CIFPlayerChest::ChestList.erase(it);
                CIFPlayerChest::ChestW->UpdateChest();
                break;
            }
        }
    }
    else if (TYPE == 2) {
        CIFPlayerChest::ChestW->Clear();
        CIFPlayerChest::ChestList.clear();
    }
    msg.FlushRemaining();
}
void CNetProcessIn::Charlock(CMsgStreamBuffer& msg)
{
    byte ShowHide = 0;
    msg >> ShowHide;
    if (ShowHide == 2) // itemlock
    {

        CIFMainMenu::MenuW->lockstatus->SetText(L"LOCKED");
        CIFMainMenu::MenuW->charlockicon->TB_Func_13("interface\\ifcommon\\quickparty_move_lock_focus.ddj", 0, 0);
    }
    else if (ShowHide == 1) // unlock
    {
        CIFMainMenu::MenuW->lockstatus->SetText(L"UNLOCKED");
        CIFMainMenu::MenuW->charlockicon->TB_Func_13("interface\\ifcommon\\quickparty_move_unlock_focus.ddj", 0, 0);
    }
}
void CNetProcessIn::TitleManager(CMsgStreamBuffer& msg) {

    BYTE count;
    BYTE ID;
    std::n_string Name;
    msg >> count;
    BYTE i = 0;

    while (i < count && count > 0) {
        i++;
        msg >> ID >> Name;

        wchar_t buffer1[255];
        std::wstring TitleName = g_CTextStringManager->GetStringTextByCode(Convert(Name))->c_str();

        if (TitleName.empty())
            TitleName = L"<Unknown>";

        CIFTitleManager::RankStruct Evs = CIFTitleManager::RankStruct();
        Evs.LineNum = i;
        Evs.Id = ID;
        Evs.Titlename = TitleName;
        CIFTitleManager::TitleNameRankList.push_back(Evs);

    }
    CIFMainMenu::TitleW->ActivateTabPage(0);
    msg.FlushRemaining();
}
void CNetProcessIn::TitleManageriSro(CMsgStreamBuffer& msg) {
    BYTE count;
    BYTE ID;
    std::n_string TitleName;

    msg >> count;
    BYTE i = 0;

    while (i < count && count > 0) {
        i++;
        msg >> ID >> TitleName;


        std::wstring TitleName1 = TO_NWSTRING(TitleName).c_str();
        CIFTitleManager::RankStruct Evs = CIFTitleManager::RankStruct();
        Evs.LineNum = i;
        Evs.Id = ID;
        Evs.Titlename = TitleName1;
        CIFTitleManager::TapNameRankList.push_back(Evs);
    }

    msg.FlushRemaining();
}

void CNetProcessIn::TitleManagerColors(CMsgStreamBuffer& msg) {
    int count;
    int ID;
    int Colors;

    msg >> count;
    int i = 0;
    while (i < count && count > 0) {
        i++;
        msg >> ID >> Colors;

        CIFTitleManager::ColorStruct Evs = CIFTitleManager::ColorStruct();
        Evs.ID = i;
        Evs.Color = Colors;
        CIFMainMenu::TitleW->TitleColor.push_back(Evs);
    }

    msg.FlushRemaining();
}
void CNetProcessIn::CharAnalyzer(CMsgStreamBuffer& msg) {

    int FormID = 0;
    int SurvivalKill = 0;
    int FtwKill = 0;
    int BattleArenaKills = 0;
    int JobKills = 0;
    int GlobalPoints = 0;
    int HonorPoints = 0;

    msg >> FormID >> SurvivalKill >> FtwKill >> BattleArenaKills >> JobKills >> GlobalPoints >> HonorPoints;

    if (FormID == 5010) {

        wchar_t buffer1[255];
        swprintf_s(buffer1, L"%d", SurvivalKill);
        CIFMainMenu::CharW->survkillslot->SetText(buffer1);


        wchar_t buffer2[255];
        swprintf_s(buffer2, L"%d", FtwKill);
        CIFMainMenu::CharW->ctfkillslot->SetText(buffer2);


        wchar_t buffer3[255];
        swprintf_s(buffer3, L"%d", BattleArenaKills);
        CIFMainMenu::CharW->battlekillslot->SetText(buffer3);



        wchar_t buffer4[255];
        swprintf_s(buffer4, L"%d", JobKills);
        CIFMainMenu::CharW->jobkillslot->SetText(buffer4);



        wchar_t buffer5[255];
        swprintf_s(buffer5, L"%d", GlobalPoints);
        CIFMainMenu::CharW->globalrankslot->SetText(buffer5);



        wchar_t buffer6[255];
        swprintf_s(buffer6, L"%d", HonorPoints);
        CIFMainMenu::CharW->honorslot->SetText(buffer6);



    }
    msg.FlushRemaining();
}
void CNetProcessIn::EventSchedule(CMsgStreamBuffer& msg) {
    int sCount;
    std::n_string IDs;
    std::n_string EventName;
    std::n_string Day;
    std::n_string Time;
    msg >> sCount;
    int i = 0;

    CIFEventTime::EventList.clear();
    while (i < sCount && sCount > 0) {
        i++;

        msg >> IDs >> EventName >> Day >> Time;

        CIFEventTime::EventSetting Evs = CIFEventTime::EventSetting();
        Evs.ID = TO_WSTRING(IDs).c_str();
        Evs.LineNum = i;
        Evs.EventName = TO_WSTRING(EventName).c_str();
        Evs.Day = TO_WSTRING(Day).c_str();
        Evs.Time = TO_WSTRING(Time).c_str();

        CIFEventTime::EventList.push_back(Evs);
    }

    CIFMainMenu::EventW->UpdateLog();
    msg.FlushRemaining();
}
void CNetProcessIn::ChangeLog(CMsgStreamBuffer& msg)
{
    std::n_string Message;
    msg >> Message;
    while (CIFMainMenu::ChangeW->my_textbox->GetNumberOfItems() > 0) {
        CIFMainMenu::ChangeW->my_textbox->Removeline(0);
    }
    CIFMainMenu::ChangeW->my_textbox->SetText(TO_WSTRING(Message).c_str());
}
/// left icons
void CNetProcessIn::LeftCharIconPath(CMsgStreamBuffer& msg) {

    int count;
    msg >> count;
    int i = 0;
    while (i < count && count > 0) {
        i++;

        int IconID;
        msg >> IconID;


        std::n_string IconPath;
        msg >> IconPath;




        std::map<int, void*>::iterator foundData = g_pCICPlayer->m_LeftIconsData.find(IconID);
        if (foundData == g_pCICPlayer->m_LeftIconsData.end()) {
            void* Resource = Fun_CacheTexture_Create(std::n_string(IconPath));
            if (Resource != NULL) {
                g_pCICPlayer->m_LeftIconsData.insert(std::pair<int, void*>(IconID, Resource));
            }
        }

    }
    msg.FlushRemaining();
}
void CNetProcessIn::LeftCharIcon(CMsgStreamBuffer& msg) {

    int count;
    msg >> count;
    int i = 0;
    while (i < count && count > 0) {
        i++;

        std::n_wstring Charname;
        msg >> Charname;

        int IconID;
        msg >> IconID;


        std::map<std::wstring, unsigned __int32>::iterator iconData = g_pCICPlayer->m_LeftCharIcons.find(Charname.c_str());
        if (iconData == g_pCICPlayer->m_LeftCharIcons.end())
        {
            g_pCICPlayer->m_LeftCharIcons.insert((std::pair<std::wstring, unsigned __int32>(Charname.c_str(), IconID)));
        }
        else // if exists
        {
            for (std::map<std::wstring, unsigned __int32>::iterator it = g_pCICPlayer->m_LeftCharIcons.begin(); it != g_pCICPlayer->m_LeftCharIcons.end(); ++it)
            {
                if (it->first == Charname.c_str())
                {
                    if (it->second != IconID)
                        it->second = IconID;
                }
            }

        }
    }
    msg.FlushRemaining();
}
void CNetProcessIn::UpdateLeftIcon(CMsgStreamBuffer& msg)
{
    std::n_wstring CharName16;
    int IconID;
    msg >> CharName16 >> IconID;

    bool isFoundAndUpdated = false;
    for (std::map<std::wstring, unsigned __int32>::iterator it = g_pCICPlayer->m_LeftCharIcons.begin(); it != g_pCICPlayer->m_LeftCharIcons.end(); ++it)
    {
        if (it->first == CharName16.c_str())
        {
            isFoundAndUpdated = true;
            it->second = IconID;
            break;
        }
    }
    if (!isFoundAndUpdated)
        g_pCICPlayer->m_LeftCharIcons.insert((std::pair<std::wstring, unsigned __int32>(CharName16.c_str(), IconID)));

}
void CNetProcessIn::RemoveLeftIcon(CMsgStreamBuffer& msg) {

    std::n_wstring CharName16;
    msg >> CharName16;

    if (g_pCICPlayer->m_LeftCharIcons.find(CharName16.c_str()) != g_pCICPlayer->m_LeftCharIcons.end())
    {
        g_pCICPlayer->m_LeftCharIcons.erase(CharName16.c_str());
    }
    msg.FlushRemaining();
}
/// right icons
void CNetProcessIn::RightIconPath(CMsgStreamBuffer& msg) {

    int count;
    msg >> count;
    int i = 0;
    while (i < count && count > 0) {
        i++;
        int IconID;
        msg >> IconID;


        std::n_string IconPath;
        msg >> IconPath;



        std::map<int, void*>::iterator foundData = g_pCICPlayer->m_RightIconsData.find(IconID);
        if (foundData == g_pCICPlayer->m_RightIconsData.end()) {
            void* Resource = Fun_CacheTexture_Create(std::n_string(IconPath));
            if (Resource != NULL) {
                g_pCICPlayer->m_RightIconsData.insert(std::pair<int, void*>(IconID, Resource));
            }
        }

    }
    msg.FlushRemaining();
}
void CNetProcessIn::RightIcon(CMsgStreamBuffer& msg) {

    int count;
    msg >> count;
    int i = 0;
    while (i < count && count > 0) {
        i++;

        std::n_wstring Charname;
        msg >> Charname;

        int IconID;
        msg >> IconID;


        std::map<std::wstring, unsigned __int32>::iterator iconData = g_pCICPlayer->m_RightCharIcons.find(Charname.c_str());
        if (iconData == g_pCICPlayer->m_RightCharIcons.end())
        {
            g_pCICPlayer->m_RightCharIcons.insert((std::pair<std::wstring, unsigned __int32>(Charname.c_str(), IconID)));
        }
        else // if exists
        {
            for (std::map<std::wstring, unsigned __int32>::iterator it = g_pCICPlayer->m_RightCharIcons.begin(); it != g_pCICPlayer->m_RightCharIcons.end(); ++it)
            {
                if (it->first == Charname.c_str())
                {
                    if (it->second != IconID)
                        it->second = IconID;
                }
            }

        }
    }
    msg.FlushRemaining();
}
void CNetProcessIn::UpdateRightIcon(CMsgStreamBuffer& msg)
{

    std::n_wstring CharName16;
    int IconID;
    msg >> CharName16 >> IconID;

    bool isFoundAndUpdated = false;
    for (std::map<std::wstring, unsigned __int32>::iterator it = g_pCICPlayer->m_RightCharIcons.begin(); it != g_pCICPlayer->m_RightCharIcons.end(); ++it)
    {
        if (it->first == CharName16.c_str())
        {
            isFoundAndUpdated = true;
            it->second = IconID;
            break;
        }
    }
    if (!isFoundAndUpdated)
        g_pCICPlayer->m_RightCharIcons.insert((std::pair<std::wstring, unsigned __int32>(CharName16.c_str(), IconID)));

}
void CNetProcessIn::RemoveRightIcon(CMsgStreamBuffer& msg) {

    std::n_wstring CharName16;
    msg >> CharName16;

    if (g_pCICPlayer->m_RightCharIcons.find(CharName16.c_str()) != g_pCICPlayer->m_RightCharIcons.end())
    {
        g_pCICPlayer->m_RightCharIcons.erase(CharName16.c_str());
    }
    msg.FlushRemaining();
}
/// up icons
void CNetProcessIn::UpCharIconPath(CMsgStreamBuffer& msg) {

    int count;
    msg >> count;
    int i = 0;
    while (i < count && count > 0) {
        i++;

        int IconID;
        msg >> IconID;


        std::n_string IconPath;
        msg >> IconPath;




        std::map<int, void*>::iterator foundData = g_pCICPlayer->m_UpIconsData.find(IconID);
        if (foundData == g_pCICPlayer->m_UpIconsData.end()) {
            void* Resource = Fun_CacheTexture_Create(std::n_string(IconPath));
            if (Resource != NULL) {
                g_pCICPlayer->m_UpIconsData.insert(std::pair<int, void*>(IconID, Resource));
            }
        }

    }
    msg.FlushRemaining();
}
void CNetProcessIn::UpCharIcon(CMsgStreamBuffer& msg) {

    int count;
    msg >> count;
    int i = 0;
    while (i < count && count > 0) {
        i++;

        std::n_wstring Charname;
        msg >> Charname;

        int IconID;
        msg >> IconID;


        std::map<std::wstring, unsigned __int32>::iterator iconData = g_pCICPlayer->m_UpCharIcons.find(Charname.c_str());
        if (iconData == g_pCICPlayer->m_UpCharIcons.end())
        {
            g_pCICPlayer->m_UpCharIcons.insert((std::pair<std::wstring, unsigned __int32>(Charname.c_str(), IconID)));
        }
        else // if exists
        {
            for (std::map<std::wstring, unsigned __int32>::iterator it = g_pCICPlayer->m_UpCharIcons.begin(); it != g_pCICPlayer->m_UpCharIcons.end(); ++it)
            {
                if (it->first == Charname.c_str())
                {
                    if (it->second != IconID)
                        it->second = IconID;
                }
            }

        }
    }
    msg.FlushRemaining();
}
void CNetProcessIn::UpdateUpIcon(CMsgStreamBuffer& msg)
{

    std::n_wstring CharName16;
    int IconID;
    msg >> CharName16 >> IconID;

    bool isFoundAndUpdated = false;
    for (std::map<std::wstring, unsigned __int32>::iterator it = g_pCICPlayer->m_UpCharIcons.begin(); it != g_pCICPlayer->m_UpCharIcons.end(); ++it)
    {
        if (it->first == CharName16.c_str())
        {
            isFoundAndUpdated = true;
            it->second = IconID;
            break;
        }
    }
    if (!isFoundAndUpdated)
        g_pCICPlayer->m_UpCharIcons.insert((std::pair<std::wstring, unsigned __int32>(CharName16.c_str(), IconID)));

}
void CNetProcessIn::RemoveUpIcon(CMsgStreamBuffer& msg) {

    std::n_wstring CharName16;
    msg >> CharName16;

    if (g_pCICPlayer->m_UpCharIcons.find(CharName16.c_str()) != g_pCICPlayer->m_UpCharIcons.end())
    {
        g_pCICPlayer->m_UpCharIcons.erase(CharName16.c_str());
    }
    msg.FlushRemaining();
}
///colors
void CNetProcessIn::CharNameColor(CMsgStreamBuffer& msg) {

    int count;
    msg >> count;
    int i = 0;

    while (i < count && count > 0) {
        i++;
        std::n_wstring CharName16;
        msg >> CharName16;

        unsigned __int32 Color;
        msg >> Color;

        std::map<std::wstring, unsigned __int32>::iterator colordata = g_pCICPlayer->m_NameColors.find(CharName16.c_str());
        if (colordata == g_pCICPlayer->m_NameColors.end())
        {
            g_pCICPlayer->m_NameColors.insert((std::pair<std::wstring, unsigned __int32>(CharName16.c_str(), Color)));
        }
        else // if exists
        {
            for (std::map<std::wstring, unsigned __int32>::iterator it = g_pCICPlayer->m_NameColors.begin(); it != g_pCICPlayer->m_NameColors.end(); ++it)
            {
                if (it->first == CharName16.c_str())
                {
                    if (it->second != Color)
                        it->second = Color;
                }
            }

        }
        CLASSLINK_LOOP_BEGIN(CICUser)
            if (wcscmp(obj->GetName().c_str(), CharName16.c_str()) == 0)
                obj->ChangeNameColor(Color);
        CLASSLINK_LOOP_END(CICUser)
    }
    msg.FlushRemaining();
}
void CNetProcessIn::UpdateNameColor(CMsgStreamBuffer& msg)
{

    std::n_wstring CharName16;
    unsigned __int32 NewColor;
    msg >> CharName16 >> NewColor;
    g_pCICPlayer->UpdateNameColor(NewColor);
    bool isFoundAndUpdated = false;
    CLASSLINK_LOOP_BEGIN(CICUser)
        if (wcscmp(obj->GetName().c_str(), CharName16.c_str()) == 0)
            obj->ChangeNameColor(NewColor);
    CLASSLINK_LOOP_END(CICUser)
        for (std::map<std::wstring, unsigned __int32>::iterator it = g_pCICPlayer->m_NameColors.begin(); it != g_pCICPlayer->m_NameColors.end(); ++it)
        {
            if (it->first == CharName16.c_str())
            {
                isFoundAndUpdated = true;
                it->second = NewColor;
                break;
            }
        }
    if (!isFoundAndUpdated)
        g_pCICPlayer->m_NameColors.insert((std::pair<std::wstring, unsigned __int32>(CharName16.c_str(), NewColor)));
}
void CNetProcessIn::RemoveNameColor(CMsgStreamBuffer& msg) {

    std::n_wstring CharName16;
    msg >> CharName16;

    if (g_pCICPlayer->m_NameColors.find(CharName16.c_str()) != g_pCICPlayer->m_NameColors.end())
    {
        g_pCICPlayer->m_NameColors.erase(CharName16.c_str());
    }
    CLASSLINK_LOOP_BEGIN(CICUser)
        if (wcscmp(obj->GetName().c_str(), CharName16.c_str()) == 0)
            obj->ChangeNameColor(0xFFFFFFFE);
    CLASSLINK_LOOP_END(CICUser)
        msg.FlushRemaining();
}
void CNetProcessIn::TitleColor(CMsgStreamBuffer& msg) {

    int count;
    msg >> count;
    int i = 0;
    while (i < count && count > 0) {
        i++;
        std::n_wstring CharName16;
        msg >> CharName16;

        unsigned __int32 Color;
        msg >> Color;

        std::map<std::wstring, unsigned __int32>::iterator colordata = g_pCICPlayer->TitleColors.find(CharName16.c_str());
        if (colordata == g_pCICPlayer->TitleColors.end())
        {
            g_pCICPlayer->TitleColors.insert((std::pair<std::wstring, unsigned __int32>(CharName16.c_str(), Color)));
        }
        else // if exists
        {
            for (std::map<std::wstring, unsigned __int32>::iterator it = g_pCICPlayer->TitleColors.begin(); it != g_pCICPlayer->TitleColors.end(); ++it)
            {
                if (it->first == CharName16.c_str())
                {
                    if (it->second != Color)
                        it->second = Color;
                }
            }

        }
        CLASSLINK_LOOP_BEGIN(CICUser)
            if (wcscmp(obj->GetName().c_str(), CharName16.c_str()) == 0)
                obj->ChangeTitleColor(Color);
        CLASSLINK_LOOP_END(CICUser)
    }
}
void CNetProcessIn::UpdateTitleColor(CMsgStreamBuffer& msg) {
    std::n_wstring CharName16;
    unsigned __int32 NewColor;
    msg >> CharName16 >> NewColor;

    bool isFoundAndUpdated = false;
    CLASSLINK_LOOP_BEGIN(CICUser)
        if (wcscmp(obj->GetName().c_str(), CharName16.c_str()) == 0)
            obj->ChangeTitleColor(NewColor);
    CLASSLINK_LOOP_END(CICUser)
        for (std::map<std::wstring, unsigned __int32>::iterator it = g_pCICPlayer->TitleColors.begin(); it != g_pCICPlayer->TitleColors.end(); ++it)
        {
            if (it->first == CharName16.c_str())
            {
                isFoundAndUpdated = true;
                it->second = NewColor;
                break;
            }
        }
    if (!isFoundAndUpdated)
        g_pCICPlayer->TitleColors.insert((std::pair<std::wstring, unsigned __int32>(CharName16.c_str(), NewColor)));
}
void CNetProcessIn::RemoveTitleColor(CMsgStreamBuffer& msg) {
    std::n_wstring CharName16;
    msg >> CharName16;

    if (g_pCICPlayer->TitleColors.find(CharName16.c_str()) != g_pCICPlayer->TitleColors.end())
    {
        g_pCICPlayer->TitleColors.erase(CharName16.c_str());
    }
    CLASSLINK_LOOP_BEGIN(CICUser)
        if (wcscmp(obj->GetName().c_str(), CharName16.c_str()) == 0)
            obj->ChangeTitleColor(0xFFE65B);
    CLASSLINK_LOOP_END(CICUser)
        msg.FlushRemaining();
}
///Newtitles
void CNetProcessIn::NewCostomTitleAdd(CMsgStreamBuffer& msg)
{
    std::n_wstring CharName16;
    std::n_wstring Title;
    msg >> CharName16 >> Title;


    std::map<std::wstring, std::wstring>::iterator titledata = g_pCICPlayer->NewCostomTitle.find(CharName16.c_str());
    if (titledata == g_pCICPlayer->NewCostomTitle.end()) {
        g_pCICPlayer->NewCostomTitle.insert(
            (std::pair<std::wstring, std::wstring>(CharName16.c_str(), Title.c_str())));
    }
    else
    {
        for (std::map<std::wstring, std::wstring>::iterator it = g_pCICPlayer->NewCostomTitle.begin();
            it != g_pCICPlayer->NewCostomTitle.end(); ++it) {
            if (it->first == CharName16.c_str()) {
                if (it->second != Title.c_str())
                    it->second = Title.c_str();
            }
        }
    }
    msg.FlushRemaining();

}
void CNetProcessIn::NewCostomTitlesAddAll(CMsgStreamBuffer& msg)
{
    int count;
    std::n_wstring CharName16;
    std::n_wstring Title;
    msg >> count;
    int i = 0;

    while (i < count && count > 0) {
        i++;
        msg >> CharName16 >> Title;

        std::map<std::wstring, std::wstring>::iterator titledata = g_pCICPlayer->NewCostomTitle.find(CharName16.c_str());
        if (titledata == g_pCICPlayer->NewCostomTitle.end()) {
            g_pCICPlayer->NewCostomTitle.insert(
                (std::pair<std::wstring, std::wstring>(CharName16.c_str(), Title.c_str())));
        }
        else // if exists
        {
            for (std::map<std::wstring, std::wstring>::iterator it = g_pCICPlayer->NewCostomTitle.begin();
                it != g_pCICPlayer->NewCostomTitle.end(); ++it) {
                if (it->first == CharName16.c_str()) {
                    if (it->second != Title.c_str())
                        it->second = Title.c_str();
                }
            }

        }
    }

    msg.FlushRemaining();
}
void CNetProcessIn::NewisroTitlesAddAll(CMsgStreamBuffer& msg)
{
    int count;
    std::n_wstring CharName16;
    std::n_wstring Title;
    msg >> count;
    int i = 0;

    while (i < count && count > 0) {
        i++;
        msg >> CharName16 >> Title;

        std::map<std::wstring, std::wstring>::iterator titledata = g_pCICPlayer->NewTitles.find(CharName16.c_str());
        if (titledata == g_pCICPlayer->NewTitles.end()) {
            g_pCICPlayer->NewTitles.insert(
                (std::pair<std::wstring, std::wstring>(CharName16.c_str(), Title.c_str())));
        }
        else // if exists
        {
            for (std::map<std::wstring, std::wstring>::iterator it = g_pCICPlayer->NewTitles.begin();
                it != g_pCICPlayer->NewTitles.end(); ++it) {
                if (it->first == CharName16.c_str()) {
                    if (it->second != Title.c_str())
                        it->second = Title.c_str();
                }
            }

        }
    }
    msg.FlushRemaining();
}



void CNetProcessIn::NewisroTitlesAdd(CMsgStreamBuffer& msg)
{
    std::n_wstring CharName16;
    std::n_wstring Title;
    msg >> CharName16 >> Title;


    std::map<std::wstring, std::wstring>::iterator titledata = g_pCICPlayer->NewTitles.find(CharName16.c_str());
    if (titledata == g_pCICPlayer->NewTitles.end()) {
        g_pCICPlayer->NewTitles.insert(
            (std::pair<std::wstring, std::wstring>(CharName16.c_str(), Title.c_str())));
    }
    else
    {
        for (std::map<std::wstring, std::wstring>::iterator it = g_pCICPlayer->NewTitles.begin();
            it != g_pCICPlayer->NewTitles.end(); ++it) {
            if (it->first == CharName16.c_str()) {
                if (it->second != Title.c_str())
                    it->second = Title.c_str();
            }
        }
    }
    msg.FlushRemaining();
}


void CNetProcessIn::NewTitles(CMsgStreamBuffer& msg)
{
    int count;
    std::n_wstring CharName16;
    std::n_wstring Title;
    msg >> count;
    int i = 0;

    while (i < count && count > 0) {
        i++;
        msg >> CharName16 >> Title;

        std::map<std::wstring, std::wstring>::iterator titledata = g_pCICPlayer->NewTitles.find(CharName16.c_str());
        if (titledata == g_pCICPlayer->NewTitles.end()) {
            g_pCICPlayer->NewTitles.insert(
                (std::pair<std::wstring, std::wstring>(CharName16.c_str(), Title.c_str())));
        }
        else // if exists
        {
            for (std::map<std::wstring, std::wstring>::iterator it = g_pCICPlayer->NewTitles.begin();
                it != g_pCICPlayer->NewTitles.end(); ++it) {
                if (it->first == CharName16.c_str()) {
                    if (it->second != Title.c_str())
                        it->second = Title.c_str();
                }
            }

        }
    }

    msg.FlushRemaining();
}
void CNetProcessIn::UpdateNewTitles(CMsgStreamBuffer& msg) {
    std::n_wstring CharName16;

    std::n_wstring NewTitle;
    msg >> CharName16 >> NewTitle;

    bool isFoundAndUpdated = false;
    for (std::map<std::wstring, std::wstring>::iterator it = g_pCICPlayer->NewTitles.begin(); it != g_pCICPlayer->NewTitles.end(); ++it)
    {
        if (it->first == CharName16.c_str())
        {
            isFoundAndUpdated = true;
            it->second = NewTitle.c_str();
            break;
        }
    }
    if (!isFoundAndUpdated)
        g_pCICPlayer->NewTitles.insert((std::pair<std::wstring, std::wstring>(CharName16.c_str(), NewTitle.c_str())));
}
void CNetProcessIn::RemoveNewTitles(CMsgStreamBuffer& msg) {
    std::n_wstring CharName16;
    msg >> CharName16;

    if (g_pCICPlayer->NewTitles.find(CharName16.c_str()) != g_pCICPlayer->NewTitles.end())
    {
        g_pCICPlayer->NewTitles.erase(CharName16.c_str());
    }
    CLASSLINK_LOOP_BEGIN(CICUser)
        if (wcscmp(obj->GetName().c_str(), CharName16.c_str()) == 0)
            obj->ChangeName(CharName16);
    CLASSLINK_LOOP_END(CICUser)
        msg.FlushRemaining();

}
/// others
void CNetProcessIn::DpsMeter(CMsgStreamBuffer& msg) {

    std::n_string DMG;
    std::n_string PlayerID;
    int MobID;
    BYTE RecordCount;//BYTE a çevirdim az paket olsun diye :D iyi ypamışsın :D dene bakalım

    std::wstring UniqueName = L"";
    msg >> MobID >> RecordCount;
    BYTE i = 0;

    if (CGlobalDataManager* g_datamanager = CGlobalDataManager::Get()) {
        if (CharData* uqdata = g_datamanager->GetCharData(MobID)) {
            UniqueName = g_CTextStringManager->GetStringByNameStrID(&uqdata->ObjNameStrID)->c_str();
        }
    }

    CIFMainMenu::DpsW->Clear();
    CIFMainMenu::DpsW->unique_slot->SetText(UniqueName.c_str());

    bool test = CIFMainMenu::UniqueW->IsGameChecked();

    //get the target mob
    CIFTargetWindow* target = g_pCGInterface->m_IRM.GetResObj<CIFTargetWindow>(16, 1);
    //show the dmg meter
    CIFMainMenu::DpsW->Clear();
    if (test == true)
    {
        CIFMainMenu::DpsW->OpenDPS(10000);
    }



    while (i < RecordCount && RecordCount > 0) {
        i++;
        msg >> PlayerID >> DMG;
        CIFMainMenu::DpsW->WriteLine(i, TO_WSTRING(PlayerID).c_str(), TO_WSTRING(DMG).c_str());
    }
    msg.FlushRemaining();
}
void CNetProcessIn::SurvivalKills(CMsgStreamBuffer& msg) {
    BYTE sCount;
    std::n_string Player;
    std::n_string Kills;
    msg >> sCount;
    BYTE i = 0;

    CIFMainMenu::SurvivalW->Clear();

    while (i < sCount && sCount > 0) {
        i++;
        msg >> Player >> Kills;
        CIFMainMenu::SurvivalW->WriteLine(i, TO_WSTRING(Player).c_str(), TO_WSTRING(Kills).c_str());
        //std::wcout << "Player " << TO_WSTRING(Player).c_str() << " Kills " << TO_WSTRING(Kills).c_str() << std::endl;

    }
    CIFMainMenu::SurvivalW->UpdateMenuSize();
    CIFMainMenu::SurvivalW->ShowGWnd(true);
    msg.FlushRemaining();
}

void CNetProcessIn::FtwPlayerKills(CMsgStreamBuffer& msg)
{
    BYTE RankType;
    BYTE sCount;
    std::n_string Player;
    std::n_string Kills;
    msg >> sCount;
    BYTE i = 0;

    CIFMainMenu::FTWW->ClearPlayer();


    while (i < sCount && sCount > 0) {
        i++;
        msg >> Player >> Kills;
        CIFMainMenu::FTWW->WriteLine3(i, TO_WSTRING(Player).c_str(), TO_WSTRING(Kills).c_str());

    }
    CIFMainMenu::FTWW->UpdateMenuSize();
    CIFMainMenu::FTWW->ShowGWnd(true);
    msg.FlushRemaining();
}


void CNetProcessIn::FtwGuildKills(CMsgStreamBuffer& msg)
{
    BYTE RankType;
    BYTE sCount;
    std::n_string Player;
    std::n_string Kills;
    msg >> sCount;
    BYTE i = 0;

    CIFMainMenu::FTWW->ClearGuild();


    while (i < sCount && sCount > 0) {
        i++;
        msg >> Player >> Kills;
        CIFMainMenu::FTWW->WriteLine(i, TO_WSTRING(Player).c_str(), TO_WSTRING(Kills).c_str()); // guild

    }
    CIFMainMenu::FTWW->UpdateMenuSize();
    CIFMainMenu::FTWW->ShowGWnd(true);
    msg.FlushRemaining();

}

void CNetProcessIn::FtwUnionKills(CMsgStreamBuffer& msg)
{
    BYTE RankType;
    BYTE sCount;
    std::n_string Player;
    std::n_string Kills;
    msg >> sCount;
    BYTE i = 0;

    CIFMainMenu::FTWW->ClearUni();


    while (i < sCount && sCount > 0) {
        i++;
        msg >> Player >> Kills;
        CIFMainMenu::FTWW->WriteLine2(i, TO_WSTRING(Player).c_str(), TO_WSTRING(Kills).c_str()); // union

    }
    CIFMainMenu::FTWW->UpdateMenuSize();
    CIFMainMenu::FTWW->ShowGWnd(true);
    msg.FlushRemaining();
}

static void StringReplaceAll(std::n_wstring& Value, const std::wstring& From, const std::wstring& To)
{
    if (From.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = Value.find(From.c_str(), start_pos)) != std::wstring::npos)
    {
        Value.replace(start_pos, From.length(), To.c_str());
        start_pos += To.length(); // Increase the same length in case 'To' contains 'From', like replacing 'x' with 'yx'
    }
}
void CNetProcessIn::LinkedItemColor(CMsgStreamBuffer& msg) {

    int aaaaaa = msg.m_availableBytesForReading;
    unsigned __int8 GlobalStatus = 0;
    msg >> GlobalStatus;// aga bizim burada aldığımız paketi tamamen okuyup sonra yazmamız lazım bildiğim o :D

    std::n_wstring Message;   msg >> Message;

    UINT32 color = 0;   msg >> color;

    switch (GlobalStatus)
    {
    case 1://global link
    {
        CMsgStreamBuffer* temporaryPacket = new CMsgStreamBuffer(0xB034);
        for (size_t i = 0; i < ((aaaaaa - 7) - (Message.length() * 2)); i++)
        {
            byte bytesa;
            msg >> bytesa;
            *temporaryPacket << bytesa;

        }

        GlobalChat chat;

        chat.index = 0;
        chat.msg = Message.c_str();
        chat.completed = false;
        chat.buffer = temporaryPacket;
        g_global->GlobalChatLog.push_back(chat);


        g_pCGInterface->FUN_00777c30(CHAT_Global, Message.c_str(), color, 1);


        std::wstring newmsg = Message.c_str();
        std::vector<std::wstring> splitted = g_StringHelper->wsplit(newmsg, L':');
        std::wstring string = std::wstring(splitted[1]);
        std::wstring charname = std::wstring(splitted[0]);
        CICharactor* entity = 0;

        CLASSLINK_LOOP_BEGIN(CICharactor)
            if (obj->GetName() == charname.c_str())
            {
                entity = obj;
                if (entity)
                    entity->ShowMessageAboveEntity(string.c_str(), color);
            }
        CLASSLINK_LOOP_END(CICharactor)
    }
    break;
    case 2://Normal global
    {
        g_pCGInterface->FUN_00777c30(CHAT_Global, Message.c_str(), color, 1);

        std::wstring newmsg = Message.c_str();
        std::vector<std::wstring> splitted = g_StringHelper->wsplit(newmsg, L':');
        std::wstring string = std::wstring(splitted[1]);
        std::wstring charname = std::wstring(splitted[0]);
        CICharactor* entity = 0;

        CLASSLINK_LOOP_BEGIN(CICharactor)
            if (obj->GetName() == charname.c_str())
            {
                entity = obj;
                if (entity)
                    entity->ShowMessageAboveEntity(string.c_str(), color);
            }
        CLASSLINK_LOOP_END(CICharactor)
    }
    break;
    case 3://sox
    {
        int refitemid = 0;    msg >> refitemid;

        std::wstring ItemNames = L"";
        if (CGlobalDataManager* g_datamanager = CGlobalDataManager::Get()) {
            if (ObjectData* uqdata = g_datamanager->GetObjectData(refitemid)) { ItemNames = g_CTextStringManager->GetStringByNameStrID(&uqdata->ObjNameStrID)->c_str(); }
        }

        std::wstring Item = L"<" + ItemNames + L">";
        std::wstring underline = L"\u035F";
        std::wstring ItemName;
        for (int i = 0; i < Item.size(); i++) {
            std::wstring bkp = Item.substr(i, 1);
            ItemName.append(underline);
            ItemName.append(bkp);
        }

        CMsgStreamBuffer* temporaryPacket = new CMsgStreamBuffer(0xB034);
        for (size_t i = 0; i < ((aaaaaa - 11) - (Message.length() * 2)); i++)
        {
            byte bytesa;
            msg >> bytesa;
            *temporaryPacket << bytesa;
        }

        StringReplaceAll(Message, L"{wpname}", ItemName.c_str());
        // noticeyidemi buraya gönderiyon aga  bildiyin gulobal gibi çalışıyor işte :D

        GlobalChat chat;

        chat.index = 0;
        chat.msg = Message.c_str();
        chat.completed = false;
        chat.buffer = temporaryPacket;
        g_global->GlobalChatLog.push_back(chat);

        g_pCGInterface->FUN_00777c30(CHAT_Global, Message.c_str(), color, 1);
        g_pCGInterface->ShowMessage_Orange(Message.c_str());

    }
    break;
    }

    msg.FlushRemaining();

}

void CNetProcessIn::OnUpdateGameTime(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()

        CPSMission* pM = (CPSMission*)theApp.GetCurrentProcess();

    msg >> pM->m_wDay >> pM->m_byHour >> pM->m_byMin;

    if (g_pCGInterface->field_0x7cd)
        return;

    CLocalTime_Sub localTimeSub;

    Fun_GetCfgGame()->m_LocalTime.FUN_008b01b0(&localTimeSub);

    Fun_GetCfgGame()->m_LocalTime.InitTimer(pM->m_dwRealTime, pM->m_wDay, pM->m_byHour, pM->m_byMin, 0);
}

void CNetProcessIn::On3809(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008a6f50)(this, msg);
}

void CNetProcessIn::OnResetClient(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0086dab0)(this, msg);
}

void CNetProcessIn::OnLogoutAck(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0086db40)(this, msg);
}

void CNetProcessIn::Onb006(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0086dbd0)(this, msg);
}

void CNetProcessIn::On300a(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0086d550)(this, msg);
}

void CNetProcessIn::On3405(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0086e5b0)(this, msg);
}

void CNetProcessIn::On34b5(CMsgStreamBuffer& msg) {
    CIFMainMenu::MoveParty->ShowGWnd(false);
    CIFMainMenu::SavedLoca->ShowGWnd(false);
    CIFMainMenu::MenuW->ShowGWnd(false);
    CIFMainMenu::GrantNameW->ShowGWnd(false);
    CIFMainMenu::CharlockW->ShowGWnd(false);
    CIFMainMenu::TitleW->ShowGWnd(false);
    CIFMainMenu::CharW->ShowGWnd(false);
    CIFMainMenu::RankW->ShowGWnd(false);
    CIFMainMenu::UniqueW->ShowGWnd(false);
    CIFMainMenu::EventW->ShowGWnd(false);
    CIFMainMenu::ChangeW->ShowGWnd(false);
    CIFMainMenu::DpsW->ShowGWnd(false);
    CIFMainMenu::FTWW->ShowGWnd(false);
    CIFMainMenu::SurvivalW->ShowGWnd(false);
    CIFPlayerChest::ChestW->ShowGWnd(false);
    CIFDiscord::DCW->ShowGWnd(false);
    CIFFacebook::FBW->ShowGWnd(false);
    CIFAttendance::ATTW->ShowGWnd(false);
    CIFEventMenu::EventW->ShowGWnd(false);
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0086e100)(this, msg);
}

#define UNIQUE_SPAWN_SYSTEM_COLOR 0xFFDBC99B
#define UNIQUE_KILL_SYSTEM_COLOR 0xFFDBC99B
#define DEFAULT_SYSTEM_COLOR 0xFFDBC99B

void CNetProcessIn::On300c(CMsgStreamBuffer& msg)
{
    unsigned short type = 0;
    msg >> type;

    CIFUniqueLog::UniqueLogstru newuq = CIFUniqueLog::UniqueLogstru();
    time_t rawtime;
    struct tm* timeinfo;
    wchar_t buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    wcsftime(buffer, sizeof(buffer), L"%H:%M", timeinfo);

    CIFSystemMessage* systemmessage = g_pCGInterface->GetSystemMessageView();
    std::wstring* chat;

    switch (type)
    {
    case 0x0C05: //Unique Spawn
    {
        unsigned int UniqueID;
        msg >> UniqueID;
        if (CGlobalDataManager* g_datamanager = CGlobalDataManager::Get())
        {
            if (CharData* uqdata = g_datamanager->GetCharData(UniqueID))
            {
                std::wstring UniqueName = g_CTextStringManager->GetStringByNameStrID(&uqdata->ObjNameStrID)->c_str();
                if (CIFUniqueLog::UqListContains(UniqueName.c_str()))
                {
                    for (int i = 0; i < CIFUniqueLog::UQlist.size(); ++i)
                    {
                        if (wcscmp(CIFUniqueLog::UQlist[i].UqName.c_str(), UniqueName.c_str()) == 0)
                        {
                            CIFUniqueLog::UQlist[i].UqName = UniqueName.c_str();
                            CIFUniqueLog::UQlist[i].LifeState = L"<Alive>";
                            CIFUniqueLog::UQlist[i].Killer = L"<None>";
                        }

                    }
                }
                else
                {
                    CIFUniqueLog::UniqueLogstru Unique = CIFUniqueLog::UniqueLogstru();
                    Unique.UqName = UniqueName.c_str();
                    Unique.LifeState = L"<Alive>";
                    Unique.Killer = L"<None>";
                    CIFUniqueLog::UQlist.push_back(Unique);
                }


                if (chat = g_notificationhandler.GetSpawnNotify(uqdata->ObjNameStrID))
                {
                    g_pCGInterface->ShowMessage_Warning(chat->c_str());

                    systemmessage->WriteMessage(255, 0x00ff00, chat->c_str(), 7, 7);
                    //systemmessage->WriteMessage(255, DEFAULT_SYSTEM_COLOR, chat->c_str(), 7, 7);


                }
                else
                {
                    wchar_t buffer[0x100];
                    swprintf_s(buffer, sizeof(buffer), g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_APPEAR_UNIC")->c_str(), UniqueName.c_str());
                    g_pCGInterface->ShowMessage_Warning(buffer);
                    systemmessage->WriteMessage(255, 0x00ff00, buffer, 7, 7);
                    // systemmessage->WriteMessage(255, DEFAULT_SYSTEM_COLOR, buffer, 7, 7);
                }
            }
        }
        CIFMainMenu::UniqueW->UpdateLog();
        break;
    }

    case 0x0C06: //Unique Kill
    {
        unsigned int UniqueID;
        msg >> UniqueID;
        std::n_string KillerName;
        msg >> KillerName;


        if (CGlobalDataManager* g_datamanager = CGlobalDataManager::Get())
        {
            if (CharData* uqdata = g_datamanager->GetCharData(UniqueID))
            {
                std::wstring UniqueName = g_CTextStringManager->GetStringByNameStrID(&uqdata->ObjNameStrID)->c_str();
                //std::wcout << L"Kill " << UniqueName << L"\n" << std::endl;

                if (CIFUniqueLog::UqListContains(UniqueName.c_str()))
                {
                    for (int i = 0; i < CIFUniqueLog::UQlist.size(); ++i)
                    {
                        if (wcscmp(CIFUniqueLog::UQlist[i].UqName.c_str(), UniqueName.c_str()) == 0)
                        {
                            CIFUniqueLog::UQlist[i].UqName = UniqueName.c_str();
                            CIFUniqueLog::UQlist[i].LifeState = buffer;
                            CIFUniqueLog::UQlist[i].Killer = TO_WSTRING(KillerName).c_str();
                            CIFMainMenu::UniqueW->UpdateLog();
                            break;
                        }
                    }
                }
                else
                {

                    newuq.LifeState = buffer;
                    newuq.Killer = TO_WSTRING(KillerName).c_str();
                    newuq.UqName = UniqueName.c_str();
                    CIFUniqueLog::UQlist.push_back(newuq);
                    CIFMainMenu::UniqueW->UpdateLog();

                }
                //

                if (TO_WSTRING(KillerName).compare(L"???") == 0)
                {
                    if (chat = g_notificationhandler.GetDespawnNotify(uqdata->ObjNameStrID))
                    {
                        g_pCGInterface->ShowMessage_Warning(chat->c_str());
                        systemmessage->WriteMessage(255, 0xFF0000, chat->c_str(), 7, 7);
                        /*systemmessage->WriteMessage(255, DEFAULT_SYSTEM_COLOR, chat->c_str(), 7, 7);*/
                    }
                    else
                    {
                        wchar_t buffer[0x100];
                        swprintf(buffer, sizeof(buffer), g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_DEAD_UNIC")->c_str(), UniqueName.c_str());
                        g_pCGInterface->ShowMessage_Warning(buffer);
                        systemmessage->WriteMessage(255, 0xFF0000, buffer, 7, 7);
                        /*   systemmessage->WriteMessage(255, DEFAULT_SYSTEM_COLOR, buffer, 7, 7);*/
                    }
                }
                else
                {
                    wchar_t buffer[0x100];

                    if (chat = g_notificationhandler.GetKillNotify(uqdata->ObjNameStrID))
                    {
                        swprintf_s(buffer, sizeof(buffer), (chat)->c_str(), TO_WSTRING(KillerName).c_str());
                        g_pCGInterface->ShowMessage_Warning(buffer);
                        systemmessage->WriteMessage(255, 0xFF0000, buffer, 7, 7);
                        //systemmessage->WriteMessage(255, UNIQUE_KILL_SYSTEM_COLOR, buffer, 7, 7);
                    }
                    else
                    {
                        swprintf_s(buffer, sizeof(buffer), g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_ANYONE_DEAD_UNIC")->c_str(), TO_WSTRING(KillerName).c_str(), UniqueName.c_str());
                        g_pCGInterface->ShowMessage_Warning(buffer);
                        systemmessage->WriteMessage(255, 0xFF0000, buffer, 7, 7);
                        //systemmessage->WriteMessage(255, UNIQUE_KILL_SYSTEM_COLOR, buffer, 7, 7);
                    }
                }
            }
        }
        break;
    }

    case 0x0C07:
    {
        unsigned char type;
        msg >> type;
        std::n_string guildname;
        msg >> guildname;
        switch (type)
        {
        case 1:
        {
            chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EVENT_051021_BADGEGAIN_BLUEDRAGON");
            break;
        }
        case 2:
        {
            chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EVENT_051021_BADGEGAIN_PHOENIX");
            break;
        }
        case 3:
        {
            chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EVENT_051021_BADGEGAIN_WHITETIGER");
            break;
        }
        case 4:
        {
            chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EVENT_051021_BADGEGAIN_TURTLE");
            break;
        }
        case 5:
        {
            chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EVENT_051021_BADGEGAIN_WHITETIGER");
            break;
        }
        case 6:
        {
            chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EVENT_051021_BADGEGAIN_WHITETIGER");
            break;
        }
        }

        wchar_t buffer[0x100];
        swprintf_s(buffer, sizeof(buffer), chat->c_str(), TO_WSTRING(guildname).c_str());
        g_pCGInterface->ShowMessage_Warning(buffer);
        g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, buffer);
        break;
    }

    case 0x0C08:
    {
        g_pCGInterface->WriteErrorMessage(17, type, DEFAULT_SYSTEM_COLOR, 0, 1);
        break;
    }

    case 0x0C10:
    {
        chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_TQ_F4_TELEPORT_OPEN");
        g_pCGInterface->ShowMessage_Warning(chat->c_str());
        g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, chat->c_str());
        break;
    }

    case 0x0C11:
    {
        chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_TQ_F4_TELEPORT_CLOSE");
        g_pCGInterface->ShowMessage_Warning(chat->c_str());
        g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, chat->c_str());
        break;
    }

    case 0x0C12:
    {
        chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_QUEST_ROC_APPEAR");
        g_pCGInterface->ShowMessage_Warning(chat->c_str());
        g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, chat->c_str());
        break;
    }

    case 0x0C13:
    {
        chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_QUEST_ROC_DISAPPEAR");
        g_pCGInterface->ShowMessage_Warning(chat->c_str());
        g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, chat->c_str());
        break;
    }

    case 0x0C14:
    {
        char mins;
        msg >> mins;
        switch (mins)
        {
        case 0:
        {
            chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_QUEST_ROC_BERSERKER_START");
            g_pCGInterface->ShowMessage_Warning(chat->c_str());
            g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, chat->c_str());
            break;
        }

        case -1:
        {
            chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_QUEST_ROC_BERSERKER_AGAIN");
            g_pCGInterface->ShowMessage_Warning(chat->c_str());
            g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, chat->c_str());
            break;
        }

        default:
        {
            chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_QUEST_ROC_BERSERKER");
            wchar_t buffer[0x100];
            swprintf_s(buffer, sizeof(buffer), chat->c_str(), mins);
            g_pCGInterface->ShowMessage_Warning(buffer);
            g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, buffer);
            break;
        }
        }
        break;
    }

    case 0x0C15:
    {
        wchar_t buffer[0x100];
        chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_QUEST_ROC_BYEBYE");
        char tq;
        msg >> tq;
        swprintf_s(buffer, sizeof(buffer), chat->c_str(), tq);
        g_pCGInterface->ShowMessage_Warning(buffer);
        g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, buffer);
        break;
    }

    case 0x0C16:
    {
        std::n_string cht;
        msg >> cht;
        g_pCGInterface->WriteSystemMessage(SYSLOG_NONE, TO_WSTRING(cht).c_str());
        g_pCGInterface->ShowMessage_Warning(TO_WSTRING(cht).c_str());
        break;
    }

    case 0x0C17:
    {
        wchar_t buffer[0x100];
        std::wstring fullchat;
        unsigned char flag;
        msg >> flag;
        //unsigned char mins = msg->Read<unsigned char>();

        switch (flag)
        {
        case 0:
        {
            fullchat.assign(*g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21837_2"));
            fullchat.append(L"]/[");
            fullchat.append(*g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21836_2"));
            break;
        }

        case 1:
        {
            fullchat.assign(*g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21836_4"));
            break;
        }

        case 2:
        {
            fullchat.assign(*g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21835_3"));
            fullchat.append(L"]/[");
            fullchat.append(*g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21835_5"));
            break;
        }
        }

        unsigned char flag1;
        msg >> flag1;
        swprintf_s(buffer, sizeof(buffer), g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EGYPT_SHRINE_ENTRANCE_ALARM")->c_str(), fullchat.c_str(), flag1);

        g_pCGInterface->ShowMessage_Warning(buffer);
        g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, buffer);
        break;
    }

    case 0x0C18:
    {
        wchar_t buffer[0x100];
        std::wstring fullchat, dunion;
        unsigned char flag;
        unsigned char uniontype;
        msg >> flag >> uniontype;
        switch (flag)
        {
        case 0:
        {
            fullchat.assign(*g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21837_2"));
            fullchat.append(L"]/[");
            fullchat.append(*g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21836_2"));
            break;
        }

        case 1:
        {
            fullchat.assign(*g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21836_4"));
            break;
        }

        case 2:
        {
            fullchat.assign(*g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21835_3"));
            fullchat.append(L"]/[");
            fullchat.append(*g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21835_5"));
            break;
        }
        }

        switch (uniontype)
        {
        case 0:
        {
            dunion.assign(*g_CTextStringManager->GetStringTextByCode(L"UIIT_STT_EGYPT_SHRINE_ENTRANCE_UNION_EMPTY"));
            break;
        }

        case 1:
        {
            dunion.assign(*g_CTextStringManager->GetStringTextByCode(L"UIIT_PAG_COMPANY_MERCHANT"));
            fullchat.append(L" / ");
            break;
        }

        case 2:
        {
            dunion.assign(*g_CTextStringManager->GetStringTextByCode(L"UIIT_PAG_COMPANY_THIEF"));
            break;
        }

        case 3:
        {
            dunion.assign(*g_CTextStringManager->GetStringTextByCode(L"UIIT_STT_EGYPT_SHRINE_ENTRANCE_UNION_ALL"));
            break;
        }
        }

        if (flag == 1 && !uniontype)
            swprintf_s(buffer, sizeof(buffer), g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EGYPT_SHRINE_ENTRANCE_UNION_ALARM_04")->c_str(), g_CTextStringManager->GetStringTextByCode(L"UIIT_STT_EGYPT_SHRINE_ENTRANCE_UNION_ALL")->c_str(), fullchat.c_str());
        else
            swprintf_s(buffer, sizeof(buffer), g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EGYPT_SHRINE_ENTRANCE_UNION_ALARM_01")->c_str(), dunion.c_str(), fullchat.c_str());

        g_pCGInterface->ShowMessage_Warning(buffer);
        g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, buffer);

        if (flag < 2)
        {
            /*msg->Read<unsigned char>();
            msg->Read<unsigned char>();
            msg->Read<unsigned char>();
            msg->Read<unsigned char>();
            msg->Read<unsigned char>();
            msg->Read<unsigned char>();
            msg->Read<unsigned char>();
            msg->Read<unsigned char>();*/
            // msg->Read<long long>();
            long uk;
            msg >> uk;
            if (CGlobalDataManager* g_datamanager = CGlobalDataManager::Get())
            {
                g_datamanager->TEMPLE_93AEF0(0, uniontype);
                if (g_pCGInterface->sub_799970())
                    g_pCGInterface->sub_799970();
            }
        }
        break;
    }

    case 0x0C19:
    {
        unsigned char flag;
        msg >> flag;
        if (flag < 2)
        {
            unsigned char templething;
            msg >> templething;
            CGlobalDataManager* g_datamanager = CGlobalDataManager::Get();
            if (g_datamanager)
            {
                g_datamanager->TEMPLE_93AEF0(flag, templething);
                if (g_pCGInterface->sub_799970())
                    g_pCGInterface->sub_799970();
            }
        }
        break;
    }

    case 0x0C1A:
    {
        chat = g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EGYPT_DUNGEON_DESTROY_ALARM");
        wchar_t buffer[0x100];
        unsigned char flag;
        msg >> flag;
        swprintf_s(buffer, sizeof(buffer), chat->c_str(), flag);
        g_pCGInterface->ShowMessage_Warning(buffer);
        g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, buffer);
        break;
    }

    case 0x0C1B:
    {
        unsigned short WorldID;
        msg >> WorldID;
        if (CGlobalDataManager* g_datamanager = CGlobalDataManager::Get())
        {
            std::wstring WorldCode;
            g_datamanager->GetWorldCodeByID(&WorldCode, WorldID);

            wchar_t buffer[0x100];
            if (WorldCode.compare(L"INS_PHARAOH_NOVICE") == 0)
                swprintf_s(buffer, sizeof(buffer), g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EGYPT_TOMB_ENTRANCE_CONDITION_ERROR_04")->c_str(), g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21836_10")->c_str());
            else if (WorldCode.compare(L"INS_PHARAOH_EXPERT") == 0)
                swprintf_s(buffer, sizeof(buffer), g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EGYPT_TOMB_ENTRANCE_CONDITION_ERROR_04")->c_str(), g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21836_11")->c_str());
            else if (WorldCode.compare(L"INS_PHARAOH_MASTER") == 0)
                swprintf_s(buffer, sizeof(buffer), g_CTextStringManager->GetStringTextByCode(L"UIIT_MSG_EGYPT_TOMB_ENTRANCE_CONDITION_ERROR_04")->c_str(), g_CTextStringManager->GetStringTextByCode(L"SN_ZONE_21836_12")->c_str());
            else
                swprintf_s(buffer, sizeof(buffer), WorldCode.c_str());

            g_pCGInterface->ShowMessage_Warning(buffer);
            g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, buffer);
        }
        break;
    }

    case 0x0C1C:
    {
        unsigned char flag;
        msg >> flag;
        // std::wstring msgcode(msg->ReadStringW());
        std::n_string msgcode;
        msg >> msgcode;
        switch (flag)
        {
        case 1:
        {
            chat = g_CTextStringManager->GetStringByNameStrID(&TO_WSTRING(msgcode));
            g_pCGInterface->ShowMessage_Warning(chat->c_str());
            break;
        }

        case 2:
        {
            chat = g_CTextStringManager->GetStringByNameStrID(&TO_WSTRING(msgcode));
            g_pCGInterface->ShowLogMessage(DEFAULT_SYSTEM_COLOR, chat->c_str());
            break;
        }
        }
        break;
    }

    default:
    {
        g_pCGInterface->WriteErrorMessage(17, type, DEFAULT_SYSTEM_COLOR, 0, 1);
        break;
    }
    }

    msg.FlushRemaining();

    // DEBUG_PRINT_CALL()
    //reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00874ea0)(this, msg);
}


void CNetProcessIn::On34a5(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008a6580)(this, msg);
}
byte CNetProcessIn::FvkingInventorySlot;
void CNetProcessIn::OnMyCharacterData(CMsgStreamBuffer& msg) {
    if (msg.GetLength() > 59)
    {
        CharDead = false;
        unsigned __int32 serverTime;
        unsigned __int32 refObjId;// 4   uint    RefObjID
        unsigned __int8 scale;  // 1   byte    Scale
        unsigned __int8 curLevel; // 1   byte    CurLevel
        unsigned __int8 maxLevel; // 1   byte    MaxLevel
        unsigned __int64 expOffset; // 8   ulong   ExpOffset
        unsigned __int32 sExpOffset; // 4   uint    SExpOffset
        unsigned __int64 remainGold; // 8   ulong   RemainGold
        unsigned __int32 remainSkillPoint; // 4   uint    RemainSkillPoint
        unsigned __int16 remainStatPoint; // 2   ushort  RemainStatPoint
        unsigned __int8 remainHwanCount; // 1   byte    RemainHwanCount
        unsigned __int32 gatheredExpPoint; // 4   uint    GatheredExpPoint
        unsigned __int32 hp; // 4   uint    HP
        unsigned __int32 mp; // 4   uint    MP
        unsigned __int8 autoInverstExp;// 1   byte    AutoInverstExp
        unsigned __int8 dailyPk;  // 1   byte    DailyPK
        unsigned __int16 totalPk; // 2   ushort  TotalPK
        unsigned __int32 pkPenaltyPoint; // 4   uint    PKPenaltyPoint
        unsigned __int8 HwanLv;
        unsigned __int8 wtf;
        unsigned __int8 InventorySlot;


        msg >> serverTime;
        msg >> refObjId;
        msg >> scale;
        msg >> curLevel;
        msg >> maxLevel;
        msg >> expOffset;
        msg >> sExpOffset;
        msg >> remainGold;
        msg >> remainSkillPoint;
        msg >> remainStatPoint;
        msg >> remainHwanCount;
        msg >> gatheredExpPoint;
        msg >> hp;
        msg >> mp;
        msg >> autoInverstExp;
        msg >> dailyPk;
        msg >> totalPk;
        msg >> pkPenaltyPoint;
        msg >> HwanLv;
        msg >> wtf;
        msg >> InventorySlot;
        CNetProcessIn::FvkingInventorySlot = InventorySlot;
        CurrentZerk = HwanLv;

        switch (refObjId) {
        case 1907: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_man1.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);

        }
                 break;
        case 1908: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_man2.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1909: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_man3.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1910: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_man4.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1911: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_man5.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1912: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_man6.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1913: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_man7.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1914: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_man8.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1915: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_man9.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1916: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_man10.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1917: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_man11.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1918: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_man12.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1919: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_man13.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1920: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_woman1.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1921: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_woman2.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1922: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_woman3.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1923: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_woman4.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1924: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_woman5.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1925: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_woman6.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1926: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_woman7.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1927: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_woman8.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1928: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_woman9.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1929: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_woman10.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1930: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_woman111.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1931: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_woman12.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);
        }
                 break;
        case 1932: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_ch_woman13.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_china.ddj", 0,
                0);

        }
                 break;

        case 14875: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_man1.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);
        }
                  break;
        case 14876: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_man2.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);
        }
                  break;
        case 14877: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_man3.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);
        }
                  break;
        case 14878: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_man4.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);

        }
                  break;
        case 14879: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_man5.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);
        }
                  break;
        case 14880: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_man6.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);

        }
                  break;
        case 14881: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_man7.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);
        }
                  break;
        case 14882: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_man8.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);
        }
                  break;
        case 14883: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_man9.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);
        }
                  break;
        case 14884: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_man10.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);

        }
                  break;
        case 14885: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_man11.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);
        }
                  break;
        case 14886: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_man12.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);
        }
                  break;
        case 14887: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_man13.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);
        }
                  break;

        case 14888: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_woman1.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);
        }
                  break;
        case 14889: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_woman2.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);
        }
                  break;
        case 14890: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_woman3.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);
        }
                  break;
        case 14891: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_woman4.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);
        }
                  break;
        case 14892: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_woman5.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);
        }
                  break;
        case 14893: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_woman6.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);
        }
                  break;
        case 14894: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_woman7.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);
        }
                  break;
        case 14895: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_woman8.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);
        }
                  break;
        case 14896: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_woman9.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);
        }
                  break;
        case 14897: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_woman10.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);
        }
                  break;
        case 14898: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_woman11.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);
        }
                  break;
        case 14899: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_woman12.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);

        }
                  break;
        case 14900: {
            CIFMainMenu::MenuW->charface->TB_Func_13("interface\\character\\char_eu_woman13.ddj", 0, 0);
            CIFMainMenu::MenuW->charicon->TB_Func_13("interface\\ifcommon\\ifcommon\\com_kindred_europe.ddj", 0,
                0);

        }
                  break;
        }
    }

    msg.m_currentReadBytes = 0;

    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008a8c00)(this, msg);
}

void CNetProcessIn::On34a6(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008abba0)(this, msg);
}

void CNetProcessIn::On3020(CMsgStreamBuffer& msg) {

    if (g_pCICPlayer) {
        BYTE JOBTYPE = g_pCICPlayer->GetJobType();
        uregion CurRegion = g_pCICPlayer->GetRegion();
        USHORT RegionID = CurRegion.r;
        int WorldID = g_pCICPlayer->GetWorldID();

        CMsgStreamBuffer buf(0x3560);
        buf << JOBTYPE;
        buf << RegionID;
        buf << WorldID;
        SendMsg(buf);
    }

    if (theApp.GetCurrentProcess() != NULL) {
        std::n_wstring test = g_pCICPlayer->GetCharName();
        std::n_string wtf = TO_NSTRING(test) + " - " + "Venom Test Server";
        SetWindowText(theApp.mainHWND, wtf.c_str());
        SetWindowLong(theApp.mainHWND, GWL_STYLE,
            GetWindowLong(theApp.mainHWND, GWL_STYLE) | WS_MINIMIZEBOX);
    }

    DiscordManager::Instance().UpdateState(GAME_STATE::IN_GAME);
    msg.m_currentReadBytes = 0;
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008a6dc0)(this, msg);
}
std::vector<DWORD> g_despawned_objects;
unsigned __int8 g_GroupSpawn_Type;

void CNetProcessIn::OnObjectListBegin(CMsgStreamBuffer& msg) {

    msg >> g_GroupSpawn_Type;
    msg.m_currentReadBytes = 0;
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008ac0e0)(this, msg);
}

void CNetProcessIn::OnObjectListData(CMsgStreamBuffer& msg) {

    if (g_GroupSpawn_Type == 2)
    {
        for (size_t i = 0; i < (msg.m_availableBytesForReading / 4); i++)
        {
            DWORD dead_object;
            msg >> dead_object;
            g_despawned_objects.push_back(dead_object);
            for (std::map<unsigned __int32, int>::iterator test = g_pCICPlayer->EventSuit.begin(); test != g_pCICPlayer->EventSuit.end(); test++)
            {
                g_pCICPlayer->EventSuit.clear();
            }
        }
    }
    msg.m_currentReadBytes = 0;
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008ac170)(this, msg);
}
void CNetProcessIn::OnObjectListEnd(CMsgStreamBuffer& msg) {

    if (g_GroupSpawn_Type == 2)
    {
        for (std::vector<DWORD>::iterator shit = g_despawned_objects.begin(); shit != g_despawned_objects.end(); shit++)
        {
            g_pCICPlayer->RemoveExistingUniqueData(*shit);
        }

        g_despawned_objects.clear();
        std::vector<DWORD>(g_despawned_objects).swap(g_despawned_objects);
    }
    msg.m_currentReadBytes = 0;
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008ac3d0)(this, msg);
}

void CNetProcessIn::OnChestDataBegin(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008a74f0)(this, msg);
}

void CNetProcessIn::OnChestDataData(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008a8c10)(this, msg);
}

void CNetProcessIn::OnChestDataEnd(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008a9100)(this, msg);
}

void CNetProcessIn::OnObjectEntered(CMsgStreamBuffer& msg) {

    //UINT refobjId;
    //msg >> refobjId;

    //ObjectData * data = g_CGlobalDataManager->GetObjectData(refobjId);
    //if (data->TID == 1)
    //{

    //}

    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008a6ca0)(this, msg);
}

void CNetProcessIn::OnObjectLeft(CMsgStreamBuffer& msg) {
    if (g_pCICPlayer)
    {
        DWORD dead_object;
        msg >> dead_object;
        g_pCICPlayer->RemoveExistingUniqueData(dead_object);
        for (std::map<unsigned __int32, int>::iterator test = g_pCICPlayer->EventSuit.begin(); test != g_pCICPlayer->EventSuit.end(); test++)
        {
            g_pCICPlayer->EventSuit.erase(dead_object);
        }

    }

    msg.m_currentReadBytes = 0;
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008a6cc0)(this, msg);
}

void CNetProcessIn::On3076(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008a6640)(this, msg);
}

void CNetProcessIn::On30bf(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008a80a0)(this, msg);
}

void CNetProcessIn::Onb0cb(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008a7720)(this, msg);
}

void CNetProcessIn::Onb03c(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008a8ea0)(this, msg);
}

void CNetProcessIn::On3092(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008a7550)(this, msg);
}

void CNetProcessIn::On30df(CMsgStreamBuffer& msg) {
    unsigned int ID;
    BYTE Zerk;
    msg >> ID >> Zerk;

    if (ID == GET_OWN_GAME_ID()) {
        CurrentZerk = Zerk;
    }
    msg.m_currentReadBytes = 0;
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008a7630)(this, msg);
}

void CNetProcessIn::On30cd(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881090)(this, msg);
}

void CNetProcessIn::On30ce(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881100)(this, msg);
}

void CNetProcessIn::On30d3(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881170)(this, msg);
}

void CNetProcessIn::On30C1(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A8FC0)(this, msg);
}

void CNetProcessIn::On30C2(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A9000)(this, msg);
}

void CNetProcessIn::On30C3(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A7870)(this, msg);
}

void CNetProcessIn::On30C8(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A6650)(this, msg);
}

void CNetProcessIn::OnB0C6(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A7A70)(this, msg);
}

void CNetProcessIn::On30C9(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008AA340)(this, msg);
}

void CNetProcessIn::On30E7(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00883B10)(this, msg);
}

void CNetProcessIn::OnB0C7(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A7AC0)(this, msg);
}

void CNetProcessIn::On30CA(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A7690)(this, msg);
}

void CNetProcessIn::OnB116(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A7B30)(this, msg);
}

void CNetProcessIn::OnB117(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A7B80)(this, msg);
}

void CNetProcessIn::OnB420(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A7D20)(this, msg);
}

void CNetProcessIn::On30D4(CMsgStreamBuffer& msg) {
    uint32_t uniqueID;
    msg >> uniqueID;

    // Check if my character level up KARAKTER LEVEL ATLADI
    if (uniqueID == GET_OWN_GAME_ID()) {
        DiscordManager::Instance().UpdateState();
    }
    msg.m_currentReadBytes = 0;
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00889D90)(this, msg);
}

void CNetProcessIn::On3054(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A7020)(this, msg);
}

void CNetProcessIn::On3056(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A97C0)(this, msg);
}

void CNetProcessIn::On304E(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A70D0)(this, msg);
}

void CNetProcessIn::On3052(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008ADF50)(this, msg);
}
bool CNetProcessIn::CharDead=false;
void CNetProcessIn::On3057(CMsgStreamBuffer& msg) {
    UINT Uinque_ID;
    __int8 aaa1;
    __int8 aaa2;
    __int8 typeofpddate;
    msg >> Uinque_ID;
    if (g_pCICPlayer->GetUniqueID() == Uinque_ID)
    {
        msg >> aaa1;
        msg >> aaa2;
        msg >> typeofpddate;
        if (typeofpddate == 0x01)
        {
            UINT hp;
            msg >> hp;
            if (hp == 0)
                CharDead = true;
            else
            {
                CharDead = false;
            }
        }
    }
    msg.m_currentReadBytes = 0;
    
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A9E30)(this, msg);
}

void CNetProcessIn::OnB045(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0088B200)(this, msg);
}

void CNetProcessIn::On303D(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00880F80)(this, msg);
}

void CNetProcessIn::On30D2(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008ADD60)(this, msg);
}

void CNetProcessIn::On30CF(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008726E0)(this, msg);
}

void CNetProcessIn::On3011(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00872710)(this, msg);
}

void CNetProcessIn::On3058(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00872740)(this, msg);
}

void CNetProcessIn::OnB025(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00877340)(this, msg);
}

void CNetProcessIn::OnChatReceive(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
#if 1
        std::n_wstring senderW;
    std::n_wstring messageW;
    std::n_string messageA;
    std::n_string senderA;

    int entityId;
    bool bIsFromMyself = false;

    ChatType chatType;

    msg >> chatType;

    switch (chatType) {
    case CHAT_All:
    case CHAT_AllGM: {
        msg >> entityId >> messageA;

        messageW = acp_n_decode(messageA);

        CIGIDObject* pObject = GetCharacterObjectByID_MAYBE(entityId);

        if (pObject == NULL) {
            senderW = L"???";
        }
        else {
            if (pObject->IsSame(GFX_RUNTIME_CLASS(CICPlayer)))
                return;

            senderW = pObject->GetName();

            if (pObject->IsKindOf(GFX_RUNTIME_CLASS(CICUser))) {
                BS_DEBUG("Job type is %d", reinterpret_cast<CICUser*>(pObject)->GetJobType());

                if (reinterpret_cast<CICUser*>(pObject)->GetJobType() != TRIJOB_NOJOB) {
                    senderW.insert(0, L"*");
                }
            }
        }
        break;
    }

    default: {
        msg >> senderA >> messageA;

        messageW = acp_n_decode(messageA);
        senderW = acp_n_decode(senderA);

        if (senderW == g_pCICPlayer->GetCharName())
            return;

        break;
    }

    case CHAT_Party: {
        msg >> senderA >> messageA;

        senderW = acp_n_decode(senderA);
        messageW = acp_n_decode(messageA);

        if (g_pCICPlayer->GetName() == senderW)
            return;

        if (g_pCICPlayer->GetJobType() != TRIJOB_NOJOB) {
            senderW.insert(0, L"*");
        }
        break;
    }

    case CHAT_Global: {
        msg >> senderA >> messageA;

        messageW = acp_n_decode(messageA);

        if (senderA.length() == 0) {
            senderW = L"???";
        }
        else {
            senderW = acp_n_decode(senderA);
        }

        if (g_pCICPlayer->GetCharName() == senderW) {
            bIsFromMyself = true;
        }

        break;
    }

    case CHAT_Notice: {
        msg >> messageA;
        messageW = acp_n_decode(messageA);
        bIsFromMyself = false;
        break;
    }

    case CHAT_Stall: {
        msg >> senderA >> messageA;

        messageW = acp_n_decode(messageA);
        senderW = acp_n_decode(senderA);

        if (g_pCICPlayer->GetName() == senderW)
            return;

        break;
    }

    case CHAT_NPC: {
        msg >> entityId >> messageA;

        CIGIDObject* pObject = GetCharacterObjectByID_MAYBE(entityId);

        if (pObject == NULL) {
            senderW = L"???";
        }
        else {
            if (pObject->IsSame(GFX_RUNTIME_CLASS(CICPlayer))) {
                senderW = reinterpret_cast<CICPlayer*>(pObject)->GetCharName();
                bIsFromMyself = true;
            }
            else {
                senderW = pObject->GetName();
            }
        }

        messageW = g_CTextStringManager->FUN_008c9bb0(messageW);

        if (pObject->IsKindOf(GFX_RUNTIME_CLASS(CICUser))) {
            chatType = CHAT_All;
        }

        break;
    }

    case CHAT_Academy: {
        msg >> senderA >> messageA;

        messageW = acp_n_decode(messageA);
        senderW = acp_n_decode(senderA);

        if (g_pCICPlayer->GetCharName() == senderW)
            return;


    }

    }

    if (g_pCICPlayer == NULL)
        return;


    if (senderW.length() == 0) {
        senderW = acp_n_decode(senderA);
    }

    if (messageW.length() == 0) {
        messageW = acp_n_decode(messageA);
    }

    WriteToChatWindow(chatType, senderW, entityId, messageW, bIsFromMyself);

#else
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00877810)(this, msg);
#endif
}

void CNetProcessIn::On3091(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A7950)(this, msg);
}

void CNetProcessIn::On302D(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00872010)(this, msg);
}

void CNetProcessIn::OnB021(CMsgStreamBuffer& msg) {
    uint32_t uniqueID;
    msg >> uniqueID;

    // Check my character movements
    if (uniqueID == GET_OWN_GAME_ID()) {
        // Check if new zone has been triggered
        if (DiscordManager::Instance().m_IsRegionChange) {
            DiscordManager::Instance().m_IsRegionChange = false;
            DiscordManager::Instance().UpdateState();
        }
        // Read packet
        byte hasCoordinate;
        msg >> hasCoordinate;
        if (hasCoordinate == 1) {
            short newRegionID;
            msg >> newRegionID;
            // Check if the region will be changed in the next step
            if (g_pCICPlayer->GetRegion().r != newRegionID) {
                // We guess the next movement will be from a new region
                DiscordManager::Instance().m_IsRegionChange = true;
            }
        }
    }
    msg.m_currentReadBytes = 0;
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A5750)(this, msg);
}

void CNetProcessIn::OnB024(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A4EC0)(this, msg);
}

void CNetProcessIn::OnB023(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A4F80)(this, msg);
}

void CNetProcessIn::On3028(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A50E0)(this, msg);
}

void CNetProcessIn::OnB04F(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A51E0)(this, msg);
}

void CNetProcessIn::On30D0(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A5280)(this, msg);
}

void CNetProcessIn::On3200(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A52F0)(this, msg);
}
int damage;
int testaaaa;


void CNetProcessIn::OnB070(CMsgStreamBuffer& msg) {

    unsigned __int8 bSuccessFlag;
    msg >> bSuccessFlag;
    if (g_pCICPlayer && bSuccessFlag == 1 && msg.m_availableBytesForReading >= 20) // i'am just checking static size here, so i guess no any problems may occur while parsing.
    {
        unsigned __int8 _type;
        msg >> _type;
        unsigned __int8 _reason;
        msg >> _reason;
        if (_type == 2)//Attack action
        {
            unsigned __int32 skillID; 
            msg >> skillID;
            unsigned __int32 AttackerID;
            msg >> AttackerID;
            unsigned __int32 SkillInstanceUniqueID;
            msg >> SkillInstanceUniqueID;
            unsigned __int32 AttackedID;
            msg >> AttackedID;// MAIN TARGET Unique ID
            if (AttackerID > 0)//Attacker ID will never be 0
            {
                //CICPlayer* CICAttackerss = g_pCICPlayer->GetCICPlayerByUniqueID(AttackedID);

                //if (CICAttackerss != 0)
                //{
                //    ObjectData* m_ObjectDatat = g_CGlobalDataManager->GetObjectData(CICAttackerss->GetObj());


                //    if (CICAttackerss != 0 && m_ObjectDatat->ObjID== 1954)
                //    {
                //        std::wstring aaaaa = m_ObjectDatat->ObjCodeName.c_str();
                //        unsigned __int8 aaa;//1
                //        msg >> aaa;//1
                //        if (aaa == 1)
                //        {
                //            unsigned __int8 atacknum;//1
                //            msg >> atacknum;//111
                //            unsigned __int8 ySec;//1
                //            msg >> ySec;//1
                //            if (ySec == 1)
                //            {
                //                unsigned __int8 ySeca;//240
                //                msg >> ySeca;//ySec
                //                unsigned __int8 ySeca1;//237
                //                msg >> ySeca1;//ySec
                //                unsigned __int32 dmg1;
                //                msg >> dmg1;// MAIN TARGET Unique ID
                //                unsigned __int32 dmg;
                //                msg >> dmg;// MAIN TARGET Unique ID
                //                printf("%d \n", dmg);
                //                std::wstring UniqueName = L"";
                //                if (CGlobalDataManager* g_datamanager = CGlobalDataManager::Get()) {
                //                    if (CharData* uqdata = g_datamanager->GetCharData(m_ObjectDatat->ObjID)) {
                //                        UniqueName = g_CTextStringManager->GetStringByNameStrID(&uqdata->ObjNameStrID)->c_str();
                //                    }
                //                }

                //                CIFMainMenu::DpsW->Clear();
                //                CIFMainMenu::DpsW->unique_slot->SetText(UniqueName.c_str());

                //                bool test = CIFMainMenu::UniqueW->IsGameChecked();

                //                //get the target mob
                //                CIFTargetWindow* target = g_pCGInterface->m_IRM.GetResObj<CIFTargetWindow>(16, 1);
                //                //show the dmg meter
                //                CIFMainMenu::DpsW->Clear();
                //                if (test == true)
                //                {
                //                    CIFMainMenu::DpsW->OpenDPS(10000);
                //                }
                //                if (AttackedID == testaaaa)
                //                    damage += atacknum * dmg;
                //                else
                //                {
                //                    testaaaa = AttackedID;
                //                    damage = atacknum * dmg;
                //                }
                //                wchar_t buffer1[255];

                //                swprintf_s(buffer1, L"%d", damage);
                //                CICPlayer* CICAttackersss = g_pCICPlayer->GetCICPlayerByUniqueID(AttackerID);

                //                CIFMainMenu::DpsW->WriteLine(1, CICAttackersss->m_charname.c_str(), buffer1);
                //            }

                //        }
                //    }
                //}






                //well, i'm stressed the one that i've used here,GetCICPlayerByUniqueID this function is nullable
                //well, no problems but I firstly need to verify that parsing xD kk
                CICPlayer* CICAttacker = g_pCICPlayer->GetCICPlayerByUniqueID(AttackerID);
                DWORD check_shit = *(DWORD*)(CICAttacker);
                if (CICAttacker && check_shit == 0xDE26C4) // checking if the unique id is MOB exactly a MOnster you know :D ye but the thing is that those client functions are already crashable
                {


                    ObjectData* m_ObjectData = g_CGlobalDataManager->GetObjectData(CICAttacker->GetObj());
                    if (m_ObjectData && (m_ObjectData->Rarity == 3 || m_ObjectData->Rarity == 8))
                    {


                        DWORD effect = g_CGlobalDataManager->GetEffectIdByName(L"SYSTEM_AGGRO_EFFECT");
                        std::map<int, int>::iterator it = g_pCICPlayer->UniqueTargetHashmap.find(AttackerID);
                        if (it == g_pCICPlayer->UniqueTargetHashmap.end()) // first attack, let the shit begin.
                        {
                            g_pCICPlayer->UniqueTargetHashmap[AttackerID] = AttackedID;//i'am using these maps for unique target, lel this packet is a pain in the ass, i hope you are parsing it correctly xDD
                            g_pCICPlayer->UniqueTargetHashmapPlayer[AttackedID] = AttackerID;

                            CICPlayer* CICAttacked = g_pCICPlayer->GetCICPlayerByUniqueID(AttackedID);
                            if (CICAttacked)
                            {
                                CICAttacked->MakeEffect(effect);
                            }
                        }
                        else
                        {
                            if (it->second != AttackedID) // Attacker is changed, let them switch.
                            {
                                UINT32 oldTarget = it->second;

                                CICPlayer* CICOldTarget = g_pCICPlayer->GetCICPlayerByUniqueID(oldTarget);
                                if (CICOldTarget) CICOldTarget->RemoveEffect(effect);

                                CICPlayer* CICNewTarget = g_pCICPlayer->GetCICPlayerByUniqueID(AttackedID);
                                if (CICNewTarget) CICNewTarget->MakeEffect(effect);


                                g_pCICPlayer->UniqueTargetHashmap[AttackerID] = AttackedID;
                                g_pCICPlayer->UniqueTargetHashmap[AttackedID] = AttackedID;

                                g_pCICPlayer->UniqueTargetHashmapPlayer.erase(oldTarget);
                            }
                            else if (it->second == AttackedID) //attacker is same, check if he still have the effect
                            {
                                CICPlayer* CICCurrentTarget = g_pCICPlayer->GetCICPlayerByUniqueID(AttackedID);
                                if (CICCurrentTarget)
                                {
                                    if (CICCurrentTarget->GetObjEffect() != effect)
                                        CICCurrentTarget->MakeEffect(effect);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    msg.m_currentReadBytes = 0;

    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A5FD0)(this, msg);
}

void CNetProcessIn::OnB071(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A4960)(this, msg);
}

void CNetProcessIn::OnB0BD(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A59E0)(this, msg);
}

void CNetProcessIn::On330F(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A4A30)(this, msg);
}

void CNetProcessIn::OnB0BE(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A5DA0)(this, msg);
}

void CNetProcessIn::OnB0BC(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A4B00)(this, msg);
}

void CNetProcessIn::OnB072(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A4DE0)(this, msg);
}

void CNetProcessIn::On30A6(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A4980)(this, msg);
}

void CNetProcessIn::On30D1(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A4990)(this, msg);
}

void CNetProcessIn::On3206(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A5360)(this, msg);
}

void CNetProcessIn::OnB0A1(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00880BE0)(this, msg);
}

void CNetProcessIn::OnB0A2(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00880CC0)(this, msg);
}

void CNetProcessIn::OnB203(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00880E90)(this, msg);
}

void CNetProcessIn::OnB202(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00880DB0)(this, msg);
}

void CNetProcessIn::OnB034(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0087F370)(this, msg);
}

void CNetProcessIn::On3535(CMsgStreamBuffer& msg)
{
    std::n_wstring charname;
    msg >> charname;
    std::n_wstring msg2;
    msg >> msg2;

    int color = D3DCOLOR_RGBA(255, 255, 255, 31);
    CICharactor* entity = 0;

    CLASSLINK_LOOP_BEGIN(CICharactor)
        if (obj->GetName() == charname.c_str())
        {
            entity = obj;
            if (entity)
                entity->ShowMessageAboveEntity(msg2, color);
        }
    CLASSLINK_LOOP_END(CICharactor)
}

void CNetProcessIn::On3038(CMsgStreamBuffer& msg) {
    unsigned __int32 UniqueID;
    msg >> UniqueID;
    g_pCICPlayer->EventSuit.erase(UniqueID);
    msg.m_currentReadBytes = 0;
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A9260)(this, msg);
}

void CNetProcessIn::On3039(CMsgStreamBuffer& msg) {
    unsigned __int32 UniqueID;
    msg >> UniqueID;
    g_pCICPlayer->EventSuit.erase(UniqueID);
    msg.m_currentReadBytes = 0;
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A9560)(this, msg);
}

void CNetProcessIn::On3036(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A78B0)(this, msg);
}

void CNetProcessIn::OnB03E(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00880A20)(this, msg);
}

void CNetProcessIn::OnB03F(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00880A70)(this, msg);
}

void CNetProcessIn::On304D(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A75C0)(this, msg);
}

void CNetProcessIn::OnB04C(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0087A7B0)(this, msg);
}

void CNetProcessIn::On3068(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00873990)(this, msg);
}

void CNetProcessIn::On305C(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008735D0)(this, msg);
}

void CNetProcessIn::On30E0(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881600)(this, msg);
}

void CNetProcessIn::On3040(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0088BF30)(this, msg);
}

void CNetProcessIn::On3201(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00882280)(this, msg);
}

void CNetProcessIn::On3041(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008822C0)(this, msg);
}

void CNetProcessIn::On3042(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008825D0)(this, msg);
}

void CNetProcessIn::On3153(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00882DE0)(this, msg);
}

void CNetProcessIn::On3154(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00882E50)(this, msg);
}

void CNetProcessIn::OnB046(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00888E30)(this, msg);
}

void CNetProcessIn::OnB04B(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00886AC0)(this, msg);
}

void CNetProcessIn::OnB0C0(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0087FFD0)(this, msg);
}

void CNetProcessIn::OnB050(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00880AC0)(this, msg);
}

void CNetProcessIn::OnB051(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00880B10)(this, msg);
}

void CNetProcessIn::OnB0C5(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00872590)(this, msg);
}

void CNetProcessIn::OnB059(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00883520)(this, msg);
}

void CNetProcessIn::OnB05A(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008809D0)(this, msg);
}

void CNetProcessIn::OnB074(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00880B60)(this, msg);
}

void CNetProcessIn::On30EB(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881670)(this, msg);
}

void CNetProcessIn::OnB0EA(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881690)(this, msg);
}

void CNetProcessIn::OnB05B(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008727A0)(this, msg);
}

void CNetProcessIn::On34B1(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00871D50)(this, msg);
}

void CNetProcessIn::OnB060(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00880010)(this, msg);
}

void CNetProcessIn::On3864(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00886B10)(this, msg);
}

void CNetProcessIn::On3065(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00883CC0)(this, msg);
}

void CNetProcessIn::OnB062(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008800B0)(this, msg);
}

void CNetProcessIn::OnB067(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00880120)(this, msg);
}

void CNetProcessIn::OnB069(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00883F90)(this, msg);
}

void CNetProcessIn::OnB06A(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008840D0)(this, msg);
}

void CNetProcessIn::OnB06B(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008801E0)(this, msg);
}

void CNetProcessIn::OnB06C(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008841F0)(this, msg);
}

void CNetProcessIn::On706D(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00884660)(this, msg);
}

void CNetProcessIn::OnB06D(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008847D0)(this, msg);
}

void CNetProcessIn::OnB081(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00880330)(this, msg);
}

void CNetProcessIn::On3080(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0088AA60)(this, msg);
}

void CNetProcessIn::On3085(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008803F0)(this, msg);
}

void CNetProcessIn::OnB082(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00880430)(this, msg);
}

void CNetProcessIn::OnB083(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008804A0)(this, msg);
}

void CNetProcessIn::OnB084(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00880520)(this, msg);
}

void CNetProcessIn::On3089(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00880590)(this, msg);
}

void CNetProcessIn::On3086(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0087FCB0)(this, msg);
}

void CNetProcessIn::On3087(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0088BB50)(this, msg);
}

void CNetProcessIn::On3088(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00880840)(this, msg);
}

void CNetProcessIn::On30E8(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00880970)(this, msg);
}

void CNetProcessIn::On308C(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008806B0)(this, msg);
}

void CNetProcessIn::OnB0B1(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00872040)(this, msg);
}

void CNetProcessIn::On30B8(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00873C10)(this, msg);
}

void CNetProcessIn::OnB0B2(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008720F0)(this, msg);
}

void CNetProcessIn::On30B9(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008721B0)(this, msg);
}

void CNetProcessIn::On30B7(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0087A260)(this, msg);
}

void CNetProcessIn::OnB0B3(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00873FF0)(this, msg);
}

void CNetProcessIn::OnB0B5(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00872450)(this, msg);
}

void CNetProcessIn::OnB0B4(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00872500)(this, msg);
}

void CNetProcessIn::OnB0BA(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00878230)(this, msg);
}

void CNetProcessIn::On30BB(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00873D60)(this, msg);
}

void CNetProcessIn::OnB0A7(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A7A20)(this, msg);
}

void CNetProcessIn::OnB010(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008743A0)(this, msg);
}

void CNetProcessIn::On30D6(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008811E0)(this, msg);
}

void CNetProcessIn::On30D7(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881280)(this, msg);
}

void CNetProcessIn::On30D5(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008812B0)(this, msg);
}

void CNetProcessIn::OnB0D8(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881450)(this, msg);
}

void CNetProcessIn::OnB0D9(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008814B0)(this, msg);
}

void CNetProcessIn::On30EC(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00884A30)(this, msg);
}

void CNetProcessIn::On30DC(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A7EE0)(this, msg);
}

void CNetProcessIn::OnB515(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881570)(this, msg);
}

void CNetProcessIn::On3514(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00884CA0)(this, msg);
}

void CNetProcessIn::On3CA2(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008ABCC0)(this, msg);
}

void CNetProcessIn::On30E6(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00884DD0)(this, msg);
}

void CNetProcessIn::OnB0E1(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008890B0)(this, msg);
}

void CNetProcessIn::OnB0E2(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00889210)(this, msg);
}

void CNetProcessIn::OnB0E3(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00889370)(this, msg);
}

void CNetProcessIn::OnB0E4(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0088A130)(this, msg);
}

void CNetProcessIn::OnB0E5(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008830F0)(this, msg);
}

void CNetProcessIn::OnB0E6(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881740)(this, msg);
}

void CNetProcessIn::OnB0F0(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008852C0)(this, msg);
}

void CNetProcessIn::On38F5(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00887330)(this, msg);
}

void CNetProcessIn::OnB0F1(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881820)(this, msg);
}

void CNetProcessIn::OnB0F8(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881890)(this, msg);
}

void CNetProcessIn::OnB0F3(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881950)(this, msg);
}

void CNetProcessIn::On30FF(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0088A420)(this, msg);
}

void CNetProcessIn::On3100(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008819B0)(this, msg);
}

void CNetProcessIn::OnB0F2(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008819E0)(this, msg);
}

void CNetProcessIn::OnB0F4(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881C60)(this, msg);
}

void CNetProcessIn::On34B3(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0087FCD0)(this, msg);
}

void CNetProcessIn::On3101(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00883060)(this, msg);
}

void CNetProcessIn::On34B4(CMsgStreamBuffer& msg) {
    DiscordManager::Instance().UpdateState();
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00887300)(this, msg);
}

void CNetProcessIn::OnB0F9(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881A70)(this, msg);
}

void CNetProcessIn::OnB0F6(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881AE0)(this, msg);
}

void CNetProcessIn::OnB0FA(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881BD0)(this, msg);
}

void CNetProcessIn::OnB103(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00889680)(this, msg);
}

void CNetProcessIn::OnB104(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881CB0)(this, msg);
}

void CNetProcessIn::OnB105(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008857B0)(this, msg);
}

void CNetProcessIn::OnB106(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881D00)(this, msg);
}

void CNetProcessIn::On3908(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008897C0)(this, msg);
}

void CNetProcessIn::OnB107(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881D80)(this, msg);
}

void CNetProcessIn::OnB0FB(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881DD0)(this, msg);
}

void CNetProcessIn::On3102(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0087FD00)(this, msg);
}

void CNetProcessIn::OnB0FC(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881E20)(this, msg);
}

void CNetProcessIn::OnB0FD(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881E70)(this, msg);
}

void CNetProcessIn::On3109(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0087FD90)(this, msg);
}

void CNetProcessIn::On7110(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00885920)(this, msg);
}

void CNetProcessIn::OnB110(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881EC0)(this, msg);
}

void CNetProcessIn::OnB112(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881F30)(this, msg);
}

void CNetProcessIn::OnB114(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00885AE0)(this, msg);
}

void CNetProcessIn::OnB113(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881F80)(this, msg);
}

void CNetProcessIn::OnB501(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00885C20)(this, msg);
}

void CNetProcessIn::On30EF(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0088A770)(this, msg);
}

void CNetProcessIn::On3305(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0087FDD0)(this, msg);
}

void CNetProcessIn::OnB302(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00885E50)(this, msg);
}

void CNetProcessIn::OnB304(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00881FD0)(this, msg);
}

void CNetProcessIn::On7302(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00886000)(this, msg);
}

void CNetProcessIn::OnB30B(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00882030)(this, msg);
}

void CNetProcessIn::OnB308(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00886170)(this, msg);
}

void CNetProcessIn::OnB309(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008820B0)(this, msg);
}

void CNetProcessIn::OnB30A(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00882130)(this, msg);
}

void CNetProcessIn::On3B07(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00886310)(this, msg);
}

void CNetProcessIn::On3204(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0087FE00)(this, msg);
}

void CNetProcessIn::OnB155(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00872810)(this, msg);
}

void CNetProcessIn::On3156(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00872810)(this, msg);
}

void CNetProcessIn::OnB157(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00872940)(this, msg);
}

void CNetProcessIn::OnB150(CMsgStreamBuffer& msg) {

    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008729E0)(this, msg);
}

void CNetProcessIn::OnB151(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00872CD0)(this, msg);
}

void CNetProcessIn::OnB16A(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00872FA0)(this, msg);
}

void CNetProcessIn::On3207(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0088A820)(this, msg);
}

void CNetProcessIn::OnB0ED(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008821C0)(this, msg);
}

void CNetProcessIn::On34BA(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008867A0)(this, msg);
}

void CNetProcessIn::OnB402(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008A5230)(this, msg);
}

void CNetProcessIn::OnFFC(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x008832A0)(this, msg);
}

void CNetProcessIn::On2000(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00888DA0)(this, msg);
}

void CNetProcessIn::OnFFD(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x0087FE40)(this, msg);
}

void CNetProcessIn::OnB05E(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00878B40)(this, msg);
}

void CNetProcessIn::On3078(CMsgStreamBuffer& msg) {
    DEBUG_PRINT_CALL()
        reinterpret_cast<void(__thiscall*)(CNetProcessIn*, CMsgStreamBuffer&)>(0x00873140)(this, msg);
}

void CNetProcessIn::ProcessItemMovementResult(void* incomingPacket)
{
    return reinterpret_cast<void(__thiscall*)(CNetProcessIn*, void*)>(0x0087F370)(this, incomingPacket);
}
wchar_t* CNetProcessIn::Convert(std::n_string name)
{
    wchar_t* szName;
    const char* p = name.c_str();
    int nChars = MultiByteToWideChar(CP_ACP, 0, p, -1, NULL, 0);
    szName = new WCHAR[nChars];
    MultiByteToWideChar(CP_ACP, 0, p, -1, (LPWSTR)szName, nChars);
    return szName;
}
void CNetProcessIn::BotSettings(CMsgStreamBuffer& msg) {
    int UniqueID;
    byte TelType;
    int targetTeleport;
        msg >> UniqueID >> TelType >> targetTeleport;
        CIFMainMenu::MessageYesNo->UniqueID = UniqueID;
        CIFMainMenu::MessageYesNo->TeleportType = TelType;
        CIFMainMenu::MessageYesNo->targetTeleport = targetTeleport;
        CIFMainMenu::MessageYesNo->UpdateMenuSize();
        //CMsgStreamBuffer buf(0x704B);
        //buf << type;
        //SendMsg(buf);
        CIFMainMenu::MessageYesNo->ShowGWnd(true);
     

  
    msg.FlushRemaining();
}
void Closeexe(char* str)
{
    PROCESSENTRY32 pe32;
    HANDLE hSnapshot = NULL;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32First(hSnapshot, &pe32)) {
        do {
            if (strcmp(pe32.szExeFile, str) == 0) {
                HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
                TerminateProcess(hProcess, NULL);
            }
        } while (Process32Next(hSnapshot, &pe32));
    }

    if (hSnapshot != INVALID_HANDLE_VALUE)
        CloseHandle(hSnapshot);
}
