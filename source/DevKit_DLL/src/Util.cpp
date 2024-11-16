#include "Util.h"

#include <sys/stat.h>

#include <memory/hook.h>

#include "hooks/Hooks.h"
#include "hooks/GFXVideo3d_Hook.h"
#include "hooks/CGame_Hook.h"

#include "hooks/WndProc_Hook.h"

#include <GInterface.h>
#include <IFChatViewer.h>
#include <NetProcessIn.h>
#include <NetProcessSecond.h>
#include <NetProcessThird.h>
#include <BSLib/Debug.h>
#include "QuickStart.h"
#include "GameHelpers/GameMain.h"
#include "IFMessageBox.h"
#include "ItemLinking/GlobalItemLinking.h"
#include "ClientSettings/ClientCommonSettings.h"
#include "Network/CPSMission.h"
#include <PSCharacterSelect.h>

#include "ICPlayer.h"
#include "ICMonster.h"
#include "Special/NotificationHandler.h"

#include <ICUser.h>
#include <GFX3DFunction/RStateMgr.h>
#include <DiscordRichPresence/DiscordManager.h>
#include "OldItemMall/OldItemMall.h"


std::vector<const CGfxRuntimeClass *> register_objects;
std::vector<overrideFnPtr> override_objects;

QuickStart quickstart;

void Setup() {

#ifdef CONFIG_DEBUG_CONSOLE
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONIN$", "r", stdin);
#endif
    //OldItemMall::Initialize();
    //fun_15
    vftableHook(0x00de2e7c, 15, addr_from_this(&CICUser::Func_15_impl));
    vftableHook(0x00de256c, 15, addr_from_this(&CICharactor::Func_15_impl));
    vftableHook(0x00de2c24, 15, addr_from_this(&CICPlayer::Func_15_impl));
    vftableHook(0x00de26c4, 15, addr_from_this(&CICMonster::Func_15_impl));
    replaceOffset(0x009ded0d, addr_from_this(&CRStateMgr::FUN_00470060));
    replaceAddr(0x00DE2C4C, addr_from_this(&CICPlayer::Render)); // Some Color & Name Funcs


    vftableHook(0x00E0963C, 17, addr_from_this(&CGFXVideo3D_Hook::CreateThingsHook));
    vftableHook(0x00E0963C, 26, addr_from_this(&CGFXVideo3D_Hook::EndSceneHook));
    vftableHook(0x00E0963C, 20, addr_from_this(&CGFXVideo3D_Hook::SetSizeHook));

    vftableHook(0x00db95a4, 10, addr_from_this(&CGInterface::OnCreateIMPL));
   // vftableHook(0x00dd811c, 10, addr_from_this(&CPSCharacterSelect::OnCreateIMPL));

    replaceAddr(0x00831337 + 4, (int) &WndProcHook);

    placeHook(0x0065c6f0, addr_from_this(&CAlramGuideMgrWnd::GetGuide));

    replaceOffset(0x008491d1, addr_from_this(&CGame_Hook::LoadGameOption));

    replaceOffset(0x00832a11, addr_from_this(&CGame_Hook::InitGameAssets_Impl));

    replaceOffset(0x0084c9bf, addr_from_this(&CNetProcessIn::RegisterPacketHandlers));
    replaceOffset(0x00898656, addr_from_this(&CNetProcessSecond::RegisterPacketHandlers));
    replaceOffset(0x008a4876, addr_from_this(&CNetProcessThird::RegisterPacketHandlers));

    //placeHook(0x0049d620, Put);

    replaceOffset(0x009D0221, addr_from_this(&CICPlayer::UpdateNameColor)); //charname color hook

    replaceAddr(0x00dd92d4, addr_from_this(&CPSTitle::OnServerPacketRecv));
    replaceAddr(0x00dd8134, addr_from_this(&CPSCharacterSelect::OnServerPacketRecv));
    replaceAddr(0x00DE2C4C, addr_from_this(&CICPlayer::Render));

    

    replaceOffset(0x0078B6CE, addr_from_this(&CGInterface::OnEscapePressed)); // ESC HOOK
   // replaceOffset(0x006ec77b, addr_from_this(&CIFMessageBox::SetMsgBoxHandler)); // NEW REV
   /* replaceOffset(0x004f8e51, addr_from_this(&CIFMessageBox::SetMsgBoxHandler));
    replaceOffset(0x00676cc3, addr_from_this(&CIFMessageBox::SetMsgBoxHandler));


   replaceOffset(0x0086252a, addr_from_this(&CIFMessageBox::SetMsgBoxHandler));
   replaceOffset(0x0086c5a8, addr_from_this(&CIFMessageBox::SetMsgBoxHandler));
   replaceOffset(0x0087acdd, addr_from_this(&CIFMessageBox::SetMsgBoxHandler));
   replaceOffset(0x00883af9, addr_from_this(&CIFMessageBox::SetMsgBoxHandler));*/


    //replaceOffset(0x00682AFC, addr_from_this(&CIFSlotWithHelp::AppendAdvancedInfo));
    //replaceOffset(0x00682D6E, addr_from_this(&CIFSlotWithHelp::AppendAdvancedInfo));
    //replaceOffset(0x00682FBE, addr_from_this(&CIFSlotWithHelp::AppendAdvancedInfo));
    //replaceOffset(0x0068320E, addr_from_this(&CIFSlotWithHelp::AppendAdvancedInfo));
//Gold 0x00678e1f
    replaceOffset(0x00678e1f, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    //Silk
    replaceOffset(0x00678ee8, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    //Silk
    replaceOffset(0x00678fb1, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    //PSilk
    replaceOffset(0x00679143, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    //GP
    replaceOffset(0x0067907a, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    //Point
    replaceOffset(0x0067920c, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    //TokenSD1
    replaceOffset(0x006792d5, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    //TokenSD2
    replaceOffset(0x0067939d, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    //TokenSD3
    replaceOffset(0x00679469, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    //TokenSD4
    replaceOffset(0x00679535, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    //ArenaCoin
    replaceOffset(0x00679601, addr_from_this(&CIFHelperBubbleWindow::WriteLine));
    //
    replaceOffset(0x00678ced, addr_from_this(&CIFHelperBubbleWindow::WriteLine));

    DWORD v10 = 0x2710;
    MEMUTIL_WRITE_VALUE(DWORD, 0x00BA2156 + 6, v10);

    g_notificationhandler.Initialize();

    PatchChatLamps();
    PatchWatermark();


    //RenderNop((void*)0x009DF09D, 6);
    //GuildJobMode();


    quickstart.Setup();

#ifdef CONFIG_DEBUG_REDIRECT_PUTDUMP
  //  replaceAddr(0x00832927 + 1, (int) &DebugPrintCallback);
#endif // CONFIG_DEBUG_REDIRECT_PUTDUMP

#ifdef CONFIG_TRANSLATIONS_DEBUG
    placeHook(0x008C9C30, addr_from_this(&CTextStringManager::GetString));
#endif // CONFIG_TRANSLATIONS_DEBUG

#ifdef CONFIG_CHATVIEWER
    replaceOffset(0x008774f4, (int)&WriteToChatWindow);
    replaceOffset(0x00877b5c, (int)&WriteToChatWindow);

    placeHook(0x007a9bd0, addr_from_this(&CIFChatViewer::ShowHideControls));
#endif // CONFIG_CHATVIEWER

}

bool DoesFileExists(const std::string &name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

void RegisterObject(const CGfxRuntimeClass *obj) {
    register_objects.push_back(obj);
}

void OverrideObject(overrideFnPtr fn) {
    override_objects.push_back(fn);
}

void InstallRuntimeClasses(CGame *) {
    // Replace Create & Delete for existing classes
    // Note: We can't just inject existing objects like we would do with new objects.
    //       Joymax uses == on GFX_RUNTIME_CLASS(), so we would end up breaking this comparison

    for (std::vector<const CGfxRuntimeClass *>::const_iterator it = register_objects.begin();
         it != register_objects.end(); ++it) {
        reinterpret_cast<void (__thiscall *)(const CGfxRuntimeClass *, const char *, void *, void *,const CGfxRuntimeClass *, size_t, int)>(0x00B9C9C0)(*it,(*it)->m_lpszClassName, (*it)->m_pfnCreateObject, (*it)->m_pfnDeleteObject, (*it)->m_pBaseClass, (*it)->m_nObjectSize, 0);
    }

    for (std::vector<overrideFnPtr>::const_iterator it = override_objects.begin(); it != override_objects.end(); ++it) {
        (*it)();
    }
}


void PatchAdvColor()
{
#pragma pack(push, 1)
    struct
    {
        byte opcode;
        int color;
    } colorPatch;
#pragma pack(pop)
    colorPatch.opcode = 0x68; // push (constant)
    colorPatch.color = 0xFFEFDAA4;
    CopyBytes(0x0066FE61, &colorPatch, sizeof(colorPatch));

#pragma pack(push, 1)
    struct
    {
        byte opcode;
        byte size;
    } colorwide;
#pragma pack(pop)
    colorwide.opcode = 0x6A; // push (constant)
    colorwide.size = 0x1;
    CopyBytes(0x0066FE5D, &colorwide, sizeof(colorwide));

#pragma pack(push, 1)
    struct
    {
        byte opcode;
        byte size;
    } colorwide1;
#pragma pack(pop)
    colorwide1.opcode = 0x6A; // push (constant)
    colorwide1.size = 0x1;
    CopyBytes(0x0066FE21, &colorwide1, sizeof(colorwide1));
}

void PatchWatermark()
{

#pragma pack(push, 1)
   struct
    {
        byte opcode;
        int color;
    } colorPatch;
#pragma pack(pop)
    colorPatch.opcode = 0x68; // push (constant)
    colorPatch.color = 0X00FFFF;
    CopyBytes(0x0086BC33, &colorPatch, sizeof(colorPatch));

    static std::wstring versionFormat;
    if (versionFormat.length() == 0)
    {
        versionFormat.append(L"Version %d.%03d\nxGuard");

    }


#pragma pack(push, 1)
    struct
    {
        byte opcode;
        const wchar_t* address;
    } textPatch;
#pragma pack(pop)
    textPatch.opcode = 0x68;
    textPatch.address = versionFormat.c_str();
    CopyBytes(0x0086BC6F, &textPatch, sizeof(textPatch));
}

void PatchAlchemyPerm()
{
#pragma pack(push, 1)
    struct {
        BYTE opcode;
        BYTE puch;
    } Pushing;
#pragma pack(pop)
    Pushing.opcode = 0x6A; // push (constant)
    Pushing.puch = 1;
    CopyBytes(0x0059EB2F, &Pushing, sizeof(Pushing));
}
void PatchChatLamps()
{

#pragma pack(push, 1)
    struct
    {
        byte opcode;
        byte opcode2;
    } FirstLamp;
#pragma pack(pop)
    FirstLamp.opcode = 0x80; // push (constant)
    FirstLamp.opcode2 = 0x04;
    CopyBytes(0x007A9B18, &FirstLamp, sizeof(FirstLamp));

#pragma pack(push, 1)
    struct
    {
        byte opcode;
        byte opcode2;
    } SecondLamp;
#pragma pack(pop)
    SecondLamp.opcode = 0x7C;
    SecondLamp.opcode2 = 0x04;
    CopyBytes(0x007A9B20, &SecondLamp, sizeof(SecondLamp));
}


void GuildJobMode()
{
#pragma pack(push, 1)
    struct
    {
        byte opcode;
        byte code;
    } Guild;
#pragma pack(pop)
    Guild.opcode = 0x00;
    Guild.code = 0x00;
    CopyBytes(0x00D92240, &Guild, sizeof(Guild));
}

void PatchWrongPassword()
{
#pragma pack(push, 1)
    struct
    {
        byte opcode;
    } First;
#pragma pack(pop)
    First.opcode = 0x52; // push (constant)
    CopyBytes(0x0086C0EF, &First, sizeof(First));

#pragma pack(push, 1)
    struct
    {
        byte opcode;
    } Second;
#pragma pack(pop)
    Second.opcode = 0x51; // push (constant)
    CopyBytes(0x0086C0F0, &Second, sizeof(Second));
}

