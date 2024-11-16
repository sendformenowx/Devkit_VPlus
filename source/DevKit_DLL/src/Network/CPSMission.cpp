#include "CPSMission.h"
#include <GInterface.h>
#include <BSLib\multiBYTE.h>
#include <GlobalDataManager.h>
#include <TextStringManager.h>
#include <PSOuterInterface.h>
#include "BSLib/BSLib.h"
#include "../GameHelpers/GameMain.h"
#include "../PCLimit/HwidReader.h"
#include "../PCLimit/base64.h"
#include <Game.h>
#include <IFWholeChat.h>
#include <DiscordRichPresence/DiscordManager.h>
#include <PSCharacterSelect.h>
#include "../../DevKit_DLL/src/IFMessageBox.h"
#include "../../DevKit_DLL/src/ClientSettings/ClientCommonSettings.h"
#include "../Util.h"
#include <tlhelp32.h>
CIFStatic* Venom;
bool is_initialized = false;
bool CPSTitle::OnServerPacketRecv(CMsgStreamBuffer* msg) {

    if (msg->msgid() == 0x1210)
    {
//#pragma region MyRegion
//        PROCESSENTRY32 pe32;
//        HANDLE hSnapshot = NULL;
//        pe32.dwSize = sizeof(PROCESSENTRY32);
//        hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
//
//        if (Process32First(hSnapshot, &pe32)) {
//            do {
//                if (strcmp(pe32.szExeFile, "phBot1.exe") == 0) {
//                    DWORD test = pe32.cntUsage;
//                    printf("\n %s  \n", test);
//              /*      HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
//                    TerminateProcess(hProcess, NULL);*/
//                }
//            } while (Process32Next(hSnapshot, &pe32));
//        }
//#pragma endregion



        if (theApp.GetCurrentProcess() != NULL) {
            SetWindowText(theApp.mainHWND, "xGuard Welcome To Server");//  bu iyi
            SetWindowLong(theApp.mainHWND, GWL_STYLE,
                GetWindowLong(theApp.mainHWND, GWL_STYLE) | WS_MINIMIZEBOX);
        }

        INT64 dcid2;
        *msg >> dcid2;
        DiscordManager::Instance().Start(dcid2);
        DiscordManager::Instance().UpdateState(GAME_STATE::SERVER_SELECTION);


        byte newreverse;
        *msg >> newreverse;
        if (newreverse == 1)
        {
            replaceOffset(0x006ec77b, addr_from_this(&CIFMessageBox::SetMsgBoxHandler)); // NEW REV
        }
        byte oldmainpopup;
        *msg >> oldmainpopup;
        if (oldmainpopup == 1)
        {
            RenderNop((void*)0x006A290A, 1);
            RenderNop((void*)0x006A290B, 2);
            RenderNop((void*)0x006A2918, 1);
            RenderNop((void*)0x006A2919, 2);
            RenderNop((void*)0x006A2926, 1);
            RenderNop((void*)0x006A2927, 2);
            RenderNop((void*)0x006A2934, 1);
            RenderNop((void*)0x006A2935, 2);
            RenderNop((void*)0x006A2942, 1);
            RenderNop((void*)0x006A2943, 2);
            RenderNop((void*)0x006A2950, 1);
            RenderNop((void*)0x006A2951, 2);
            RenderNop((void*)0x006A295E, 1);
            RenderNop((void*)0x006A295F, 2);
            RenderNop((void*)0x006A2973, 1);
            RenderNop((void*)0x006A2974, 2);
            CALLFunction(0x006A2540, 0x007990E0);
            RenderNop((void*)0x006A2545, 2);
            JMPFunction(0x006A2275, 0x006A2357);
            JMPFunction(0x006A232A, 0x006A2357);
        }

        byte itemcomp;
        *msg >> itemcomp;
        if (itemcomp == 1)
        {
            replaceOffset(0x00682AFC, addr_from_this(&CIFSlotWithHelp::AppendAdvancedInfo));
            replaceOffset(0x00682D6E, addr_from_this(&CIFSlotWithHelp::AppendAdvancedInfo));
            replaceOffset(0x00682FBE, addr_from_this(&CIFSlotWithHelp::AppendAdvancedInfo));
            replaceOffset(0x0068320E, addr_from_this(&CIFSlotWithHelp::AppendAdvancedInfo));
        }


        int masterylevel;
        *msg >> masterylevel;
        int partymaxlevel;
        *msg >> partymaxlevel;

        CNetProcessIn::PartyMaxLevel = partymaxlevel;

        ClientCommonSettings* g_Settings = new ClientCommonSettings();
        g_Settings->Initialize(masterylevel);



        byte permanentalchemy;
        *msg >> permanentalchemy;
        if (permanentalchemy == 1)
        {
            PatchAlchemyPerm();

            JMPFunction(0x0059C95D, 0x0059CA04);
            RenderNop((void*)0x0059C962, 1);
            RenderNop((void*)0x0059C963, 1);
            RenderNop((void*)0x0059C964, 1);
            RenderNop((void*)0x0059CA0A, 1);
            RenderNop((void*)0x0059CA0A, 1);
            RenderNop((void*)0x0059CA24, 1);
            RenderNop((void*)0x0059CA25, 1);
            RenderNop((void*)0x0059CA26, 1);
            RenderNop((void*)0x0059CA27, 1);
            RenderNop((void*)0x0059CA28, 1);
            RenderNop((void*)0x0059DF54, 1);
            RenderNop((void*)0x0059DF55, 1);
            RenderNop((void*)0x0059DF56, 1);
            RenderNop((void*)0x0059DF57, 1);
            RenderNop((void*)0x0059DF58, 1);
            RenderNop((void*)0x0059DF59, 1);
            RenderNop((void*)0x0059DF5A, 1);
            RenderNop((void*)0x0059DF61, 1);
            RenderNop((void*)0x0059DF62, 1);
            RenderNop((void*)0x0059DF63, 1);
            RenderNop((void*)0x0059DF64, 1);
            RenderNop((void*)0x0059DF65, 1);
        }

        byte guildjob;
        *msg >> guildjob;
        if (guildjob == 1)
        {
         //   GuildJobMode();
            RenderNop((void*)0x009DF09D, 1);
        }

        msg->m_currentReadBytes = 0;
    }
    else if (msg->msgid() == 0xB003) //notice
    {
        int Color;
        std::n_string notice;
        *msg >> notice >> Color;

        this->ShowMessage(TO_WSTRING(notice).c_str(), Color);

        msg->m_currentReadBytes = 0;
    }

    return reinterpret_cast<int(__thiscall*)(CPSTitle*, CMsgStreamBuffer*)>(0x0086bfc0)(this, msg);
}


bool CPSCharacterSelect::OnServerPacketRecv(CMsgStreamBuffer* msg) {

    if (msg->msgid() == 0xB003) //notice
    {
        int Color;
        std::n_string notice;
        *msg >> notice >> Color;

        this->ShowMessage(Convert(notice), Color);

        //msg->FlushRemaining();
        msg->m_currentReadBytes = 0;
    }

    else if (msg->msgid() == 0xB007) {
        byte action;
        *msg >> action;

        if (action == 2) {


            const char *hwid = HwidReader::GetHWID();
            std::string hwid_X = HwidReader::Xor(hwid);
            std::string hwid_1 = base64_encode(hwid_X);
            //bool is_thing_open = is_app_open("opera.exe");
            byte v255 = 1;
            byte v237 = 237;

            CMsgStreamBuffer packet(0x1789);


            if (!hwid_1.empty()) {
                packet << v255;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                packet << v237;
                //MessageBoxA(NULL, hwid, "Debug", 0);
                //MessageBoxW(NULL, is_thing_open ? L"opera acik" : L"opera Kapali", L"Test", 0);
                packet << std::n_string(hwid_1.c_str());

                SendMsg(packet);
                ShowMessage(L"Hoþ Geldiniz Ýyi Oyunlar Dileriz xGuard", 0X00FFFF);

                msg->m_currentReadBytes = 0;

            }
        }
    }
    else if (msg->msgid() == 0x1209)
    {
        BYTE attendances;
        BYTE eventmenu;
        BYTE facebook;
        BYTE discord;
        BYTE chest;
        std::n_string discordurl;
        std::n_string faceurl;
        *msg >> attendances;
        *msg >> eventmenu;
        *msg >> facebook;
        *msg >> discord;
        *msg >> chest;
        *msg >> discordurl;
        *msg >> faceurl;
        CNetProcessIn::AttendanceSetting = attendances;
        CNetProcessIn::EventMenuSetting = eventmenu;
        CNetProcessIn::FacebookSetting = facebook;
        CNetProcessIn::DiscordSetting = discord;
        CNetProcessIn::ChestSetting = chest;
        CNetProcessIn::DiscordURL = discordurl;
        CNetProcessIn::FacebookURL = faceurl;
        msg->m_currentReadBytes = 0;
    }
    return reinterpret_cast<int(__thiscall*)(CPSCharacterSelect*, CMsgStreamBuffer*)>(0x0085fc60)(this, msg);
}

wchar_t* CPSCharacterSelect::Convert(std::n_string name)
{
    wchar_t* szName;
    const char* p = name.c_str();
    int nChars = MultiByteToWideChar(CP_ACP, 0, p, -1, NULL, 0);
    szName = new WCHAR[nChars];
    MultiByteToWideChar(CP_ACP, 0, p, -1, (LPWSTR)szName, nChars);
    return szName;
}

#define GP_LIMIT 0x7FFFFFFF

void CInterfaceNetSender::DonateGuildPoints(unsigned int GP)
{
    if (GuildSkillPoints >= GP_LIMIT)
    {
        if (g_pCGInterface)
        {
            g_pCGInterface->ShowMessage_Warning (L"You have reached maximum limit of guild skills points.");
            g_pCGInterface->WriteSystemMessage(SYSLOG_NONE, L"You have reached maximum limit of guild skills points.");
        }
    }
    else
    {
        unsigned int TotalGP = GuildSkillPoints + GP;
        if (TotalGP > GP_LIMIT && GuildSkillPoints < GP_LIMIT)
            GP = GP_LIMIT - GuildSkillPoints;
        reinterpret_cast<void(__thiscall*)(CInterfaceNetSender*, unsigned int)>(0x0081FAB0)(this, GP);
    }
}