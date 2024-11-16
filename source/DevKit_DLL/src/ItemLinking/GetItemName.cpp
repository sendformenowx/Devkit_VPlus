#include "GetItemName.h"
#include <Windows.h>
#include "imgui/imgui.h"
#include "imgui/examples/imgui_impl_dx9.h"
#include "imgui/examples/imgui_impl_win32.h"

#include <GFX3DFunction/GFXVideo3d.h>
#include <GFX3DFunction/DrawingHelpers.h>

#include <GInterface.h>
#include "unsorted.h"
#include "../hooks/Hooks.h"
#include "../MathUtil.h"
#include "IFSystemMessage.h"
#include <BSLib/multibyte.h>
#include <BSLib/Debug.h>
#include <NetProcessIn.h>
#include <ctime>
#include <ICPlayer.h>
#include <PSCharacterSelect.h>
#include "GlobalDataManager.h"
#include "IFWholeChat.h"
#include "TextStringManager.h"
#include "../GameHelpers/GameMain.h"
#include "../VenomMenu/IFMainMenu.h"


time_t lastClickTime;



#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
extern LRESULT New_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK New_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    BS_DEBUG_LOW("New_WndProc");


    New_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam);
    MSG new_msg;
    new_msg.hwnd = hWnd;
    new_msg.message = message;
    new_msg.wParam = wParam;
    new_msg.lParam = lParam;

    //if (*(DWORD**)0x0110F80C) // if cginterface is set
    //{
    //    switch (new_msg.message)
    //    {
    //    case WM_CLOSE:
    //        exit(EXIT_SUCCESS);
    //        break;
    //    case WM_KEYDOWN:
    //        if (new_msg.wParam == 'f' || new_msg.wParam == 'F')
    //        {
    //            if (g_pCICPlayer)
    //            {
    //                if (g_CNIRMManager->GetWindowActive(0x96) == 0)
    //                {
    //                    g_pCGInterface->SwitchToStallNetwork(true);
    //                    CGEffSoundBody::get()->PlaySound(L"snd_window_open");
    //                }
    //                else
    //                {
    //                    g_pCGInterface->SwitchToStallNetwork(false);
    //                    CGEffSoundBody::get()->PlaySound(L"snd_window_close");
    //                }
    //            }
    //        }
    //        break;
    //    }
    //}
    CPSCharacterSelect* pProcess = (CPSCharacterSelect*)theApp.GetCurrentProcess();
    if (new_msg.message == WM_LBUTTONDBLCLK)
    {


        //ptr CPSCharacterSelect::vftable
        if (*(DWORD*)pProcess == 0x00dd811c)
        {
            CPSCharacterSelect* asdasd = (CPSCharacterSelect*)g_CurrentIfUnderCursor;
            if (asdasd->m_seconds_elapsed != 0)
            if (pProcess->m_IRM.GetResObj<CIFStatic>(14, 1)->IsVisible())
            {
                CIFStatic* name = pProcess->m_IRM.GetResObj<CIFStatic>(31, 1);
                CMsgStreamBuffer buf(0x7001);
                buf << std::string(TO_STRING(name->GetNText())); // Character Name
                SendMsg(buf);
            }
        }
    }


    if (g_pCGInterface && wParam == VK_F6)
    {
        short ALTState = GetKeyState(VK_F6);
        if (ALTState == -127 || ALTState == -128)
        {
            if (CIFMainMenu::UniqueW->IsVisible())
            {
                CIFMainMenu::UniqueW->ShowGWnd(false);
                CGEffSoundBody::get()->PlaySound(L"snd_window_close");
            }
            else
            {
                CGEffSoundBody::get()->PlaySound(L"snd_window_open");
                CIFMainMenu::UniqueW->ShowGWnd(true);
                CIFMainMenu::UniqueW->UpdateMenuSize();
                CIFMainMenu::UniqueW->BringToFront();
            }
        }
    }
    if (g_pCGInterface && new_msg.message == WM_LBUTTONDOWN) {
        CIFSlotWithHelp* slotptr = (CIFSlotWithHelp*)g_CurrentIfUnderCursor;
        //printf("current if under cursor = %02x\n", slotptr);
        short ALTState = GetKeyState(VK_CONTROL);
        short MouseState = GetKeyState(VK_LBUTTON);
        if (slotptr && (ALTState == -127 || ALTState == -128) && (MouseState == -127 || MouseState == -128)) {
            if (*(DWORD*)slotptr == 0xDA18E4 || *(DWORD*)slotptr == 0xD9E0FC) {
              /*  if (*(DWORD*)slotptr == 0xD9E0FC) {
                    CGWndBase* shit;
                    if (shit) {
                        slotptr = reinterpret_cast<CIFSlotWithHelp*>(shit->m_parentControl);
                    }
                }*/
                int slotId = (slotptr->m_UniqueID - 87);
                if (slotptr->Type == 70 && (slotId >= 13 && slotId <= 108)) {
                    if (slotptr->ItemInfo) {
                        CIFWholeChat* pWholeChat = (CIFWholeChat*)g_pCGInterface->m_IRM.GetResObj(56, 0);
                        if (pWholeChat) {
                            CIFEdit* pCIFEdit;
                            pCIFEdit = pWholeChat->m_pEdit;
                            if (pCIFEdit) {
                                if (g_global->m_LinkedGlobalItemEnd > 0) {

                                    g_pCGInterface->ShowMessage_Warning(
                                        L"You're allowed to link only one item once per global.");
                                    return 1;
                                }
                                std::wstring currStr = std::wstring(pCIFEdit->GetText());
                                currStr.append(L" ");
                                g_global->m_LinkedGlobalItemBegin = currStr.length();

                                std::wstring ItemNames = L"";
                                if (CGlobalDataManager* g_datamanager = CGlobalDataManager::Get()) {
                                    if (ObjectData* uqdata = g_datamanager->GetObjectData(
                                        slotptr->ItemInfo->m_refObjItemId)) {
                                        ItemNames = g_CTextStringManager->GetStringByNameStrID(
                                            &uqdata->ObjNameStrID)->c_str();
                                    }
                                }

                                std::wstring Item = L"<" + ItemNames + L">";
                                std::wstring underline = L"\u035F";
                                std::wstring ItemName;
                                for (int i = 0; i < Item.size(); i++) {
                                    std::wstring bkp = Item.substr(i, 1);
                                    ItemName.append(underline);
                                    ItemName.append(bkp);
                                }

                                pCIFEdit->SetText(std::wstring(currStr).append(ItemName.append(L" ")).c_str());

                                g_global->m_LinkedGlobalItemEnd = std::wstring(pCIFEdit->GetText()).length();
                                g_global->m_CurrentLinkedItemName = ItemName;
                                g_global->m_LinkedGlobalSlot = slotId;
                            }
                        }

                        return TRUE;
                    }

                }
            }
        }
       
            if (g_pCICPlayer) {
                CIFButton *CurBtn1 = (CIFButton *) g_CurrentIfUnderCursor;
                if (GetAsyncKeyState(KEY_DOWN(VK_LBUTTON)) < 0 && CurBtn1->UniqueID() == 8001) {
                    if (CIFMainMenu::MoveParty->IsVisible())
                    {
                        CIFMainMenu::MoveParty->ShowGWnd(false);
                    }
                    if (CIFMainMenu::SavedLoca->IsVisible())
                    {
                        CIFMainMenu::SavedLoca->ShowGWnd(false);
                    }
                    else
                    {
                        CIFMainMenu::SavedLoca->ShowGWnd(true); // np :) done
                        CIFMainMenu::SavedLoca->BringToFront();
                        CIFMainMenu::SavedLoca->ResetPosition();
                    }
                }
            }
        if (g_pCICPlayer) {
            CIFButton *CurBtn21 = (CIFButton *) g_CurrentIfUnderCursor;
            if (GetAsyncKeyState(KEY_DOWN(VK_LBUTTON)) < 0 && CurBtn21->UniqueID() == 8000) {
                if (CIFMainMenu::SavedLoca->IsVisible())
                {
                    CIFMainMenu::SavedLoca->ShowGWnd(false);
                }
                if (CIFMainMenu::MoveParty->IsVisible())
                {
                    CIFMainMenu::MoveParty->ShowGWnd(false);
                }
                else
                {
                    CIFMainMenu::MoveParty->ShowGWnd(true); // np :) done
                    CIFMainMenu::MoveParty->BringToFront();
                    CIFMainMenu::MoveParty->UpdateMenuSize();
                }
            }
        }
            return RESULT_PASS;
        }

    }
