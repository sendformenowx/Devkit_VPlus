#include <IFChatViewer.h>
#include <IFMainPopup.h>
#include <IFChatOptionBoard.h>
#include "hooks/Hooks.h"
#include "Util.h"
#include "imgui_windows/ImGui_Windows.h"
#include <IFWholeChat.h>
#include <IFMagicStateBoard.h>
#include <DiscordRichPresence/DiscordManager.h>
#include <VMProtectSDK.h>

#include "GameHelpers/GameMain.h"
#include "ClientSettings/ClientCommonSettings.h"
#include "IFMessageBox.h"
#include "../../../DevKit_DLL/src/ItemLinking/GetItemName.h"
#include "LicenseManager/LicenseManager.h"
#include "Special/NotificationHandler.h"
#include <NIFUnderMenuBar.h>
#include "OldLoginScreen/char_select.h"

//Custom Unique Notifies with IFSystemMessage Colors
HMODULE sro_client = 0;
HMODULE g_hModule;
extern "C" _declspec(dllexport) BOOL WINAPI DllMain(HINSTANCE hModule, DWORD fdwReason, LPVOID lpReserved) {
    if (fdwReason == DLL_PROCESS_ATTACH) {
        // Setup all the required hooks

        g_global = new GlobalItemLinking();
        g_global->Initialize();

        g_MemoryHelper = new MemoryHelper();


        // discord
        LicenseManager* LicenseMgr = new LicenseManager();
        //LicenseMgr->Initialize(VMProtectDecryptStringA("25.31.203.241"));
        OnWndProc(New_WndProc);


        Setup();
       // OverrideObject<CIFWholeChat, 0x00eec7a8>();


        // Inject all the new objects

#ifdef CONFIG_OLD_MAINPOPUP
        OverrideObject<CIFMainPopup, 0x00eea6dc>();
#endif

        OverrideObject<CIFChatOptionBoard, 0x00eec128>();
      //  OverrideObject<CIFMessageBox, 0x00EE95A0>();
        // Override existing objects
#ifdef CONFIG_CHATVIEWER
        OverrideObject<CIFChatViewer, 0x00EEC168>();
#endif // CONFIG_CHATVIEWER

#ifdef CONFIG_WHOLE_CHAT
        OverrideObject<CIFWholeChat, 0x00eec7a8>();
#endif // CONFIG_WHOLE_CHAT
        
        
        //old login
        g_hModule = hModule;
        sro_client = GetModuleHandle(NULL);
        char_select_override();
#ifdef CONFIG_IMGUI
 /*       OnCreate(ImGui_OnCreate);
        OnEndScene(ImGui_OnEndScene);
        OnWndProc(ImGui_WndProc);

        OnPreSetSize(ImGui_OnPreSetSize);
        OnPostSetSize(ImGui_OnPostSetSize);*/
#endif // CONFIG_IMGUI
//
//#ifdef CONFIG_OLD_UNDERBAR
//        // https://www.elitepvpers.com/forum/sro-pserver-guides-releases/4256375-source-fix-old-exp-bar-writing-code.html
        replaceAddr(0x00D9841C, addr_from_this(&NIFUnderMenuBar::Update));
//#endif // CONFIG_OLD_UNDERBAR

        OnPreInitGameAssets(InstallRuntimeClasses);
    }

    return TRUE;
}
