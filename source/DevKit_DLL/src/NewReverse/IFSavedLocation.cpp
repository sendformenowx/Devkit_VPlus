#include "IFSavedLocation.h"
#include <ctime>
#include <Windows.h>
#include <ShellAPI.h>
#include <ICPlayer.h>
#include "ClientNet/MsgStreamBuffer.h"
#include <BSLib\multibyte.h>
#include <memory\hook.h>
#include <TextStringManager.h>
#include <sstream>
#include <GInterface.h>

#define BACKGROUND 1
#define Location1 99
#define Location2 100
#define Location3 101
#define Location4 102
#define SaveButton1 200
#define SaveButton2 201
#define SaveButton3 202
#define SaveButton4 203
#define RemoveButton1 204
#define RemoveButton2 205
#define RemoveButton3 206
#define RemoveButton4 207




GFX_IMPLEMENT_DYNCREATE(CIFSavedLocation, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFSavedLocation, CIFMainFrame)
                    ONG_COMMAND(SaveButton1, &CIFSavedLocation::SaveButton1Click)
                    ONG_COMMAND(SaveButton2, &CIFSavedLocation::SaveButton2Click)
                    ONG_COMMAND(SaveButton3, &CIFSavedLocation::SaveButton3Click)
                    ONG_COMMAND(SaveButton4, &CIFSavedLocation::SaveButton4Click)
                    ONG_COMMAND(Location1, &CIFSavedLocation::Teleport1Loc)
                    ONG_COMMAND(Location2, &CIFSavedLocation::Teleport2Loc)
                    ONG_COMMAND(Location3, &CIFSavedLocation::Teleport3Loc)
                    ONG_COMMAND(Location4, &CIFSavedLocation::Teleport4Loc)
                    ONG_COMMAND(RemoveButton1, &CIFSavedLocation::Remove1Loc)
                    ONG_COMMAND(RemoveButton2, &CIFSavedLocation::Remove2Loc)
                    ONG_COMMAND(RemoveButton3, &CIFSavedLocation::Remove3Loc)
                    ONG_COMMAND(RemoveButton4, &CIFSavedLocation::Remove4Loc)
                    ONG_COMMAND(312, &CIFSavedLocation::CloseWnd)
GFX_END_MESSAGE_MAP()


bool CIFSavedLocation::OnCreate(long ln)
{
    //printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);
    TB_Func_13("interface\\messagebox\\msgbox2_window_", 0, 0);
    m_title->SetText(L"Saved locations window");
    m_close->ShowGWnd(false);
    wnd_rect sz;
    sz.pos.x = 173;
    sz.pos.y = 70;
    sz.size.width = 55;
    sz.size.height = 15;
    background = (CIFNormalTile*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFNormalTile), sz, BACKGROUND, 0);
    background->SetGWndSize(GetSize().width - 31, GetSize().height - 56);
    background->MoveGWnd(this->GetPos().x + 16, this->GetPos().y + 40);
    background->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_b.ddj", 0, 0);


    sz.pos.x = 80;
    sz.pos.y = 70;
    sz.size.width = 194;
    sz.size.height = 15;
    reversewindowstext = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 150, 0);
    reversewindowstext->SetText(L"Save and move to your desired location.");
    reversewindowstext->MoveGWnd(this->GetPos().x+66, this->GetPos().y+46);


    sz.pos.x = 40;
    sz.pos.y = 68;
    sz.size.width = 252;
    sz.size.height = 24;
    TeleportLoc1 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, Location1, 0);
    TeleportLoc1->SetText(L"<None>");
    TeleportLoc1->m_FontTexture.SetColor(D3DCOLOR_ARGB(255,254,251,216));
    TeleportLoc1->TB_Func_13("interface\\ifcommon\\com_return_button.ddj", 0, 0);



    sz.pos.x = 40;
    sz.pos.y = 68;
    sz.size.width = 20;
    sz.size.height = 20;
    SaveLoc1 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, SaveButton1, 0);
    SaveLoc1->TB_Func_13("interface\\ifcommon\\com_plus_button.ddj", 0, 0);
    SaveLoc1->MoveGWnd(TeleportLoc1->GetBounds().pos.x + 258, TeleportLoc1->GetBounds().pos.y + 2);


    sz.pos.x = 40;
    sz.pos.y = 68;
    sz.size.width = 20;
    sz.size.height = 20;
    RemoveLoc1 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, RemoveButton1, 0);
    RemoveLoc1->TB_Func_13("interface\\ifcommon\\com_minus_button.ddj", 0, 0);
    RemoveLoc1->MoveGWnd(TeleportLoc1->GetBounds().pos.x - 26, TeleportLoc1->GetBounds().pos.y + 2);


    sz.pos.x = 40;
    sz.pos.y = 99;
    sz.size.width = 252;
    sz.size.height = 24;
    TeleportLoc2 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, Location2, 0);
    TeleportLoc2->SetText(L"<None>");
    TeleportLoc2->m_FontTexture.SetColor(D3DCOLOR_ARGB(255,254,251,216));
    TeleportLoc2->TB_Func_13("interface\\ifcommon\\com_return_button.ddj", 0, 0);

    sz.pos.x = 40;
    sz.pos.y = 68;
    sz.size.width = 20;
    sz.size.height = 20;
    SaveLoc2 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, SaveButton2, 0);
    SaveLoc2->TB_Func_13("interface\\ifcommon\\com_plus_button.ddj", 0, 0);
    SaveLoc2->MoveGWnd(TeleportLoc2->GetBounds().pos.x + 258, TeleportLoc2->GetBounds().pos.y + 2);

    sz.pos.x = 40;
    sz.pos.y = 68;
    sz.size.width = 20;
    sz.size.height = 20;
    RemoveLoc2 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, RemoveButton2, 0);
    RemoveLoc2->TB_Func_13("interface\\ifcommon\\com_minus_button.ddj", 0, 0);
    RemoveLoc2->MoveGWnd(TeleportLoc2->GetBounds().pos.x - 26, TeleportLoc2->GetBounds().pos.y + 2);


    sz.pos.x = 40;
    sz.pos.y = 130;
    sz.size.width = 252;
    sz.size.height = 24;
    TeleportLoc3 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, Location3, 0);
    TeleportLoc3->SetText(L"<None>");
    TeleportLoc3->m_FontTexture.SetColor(D3DCOLOR_ARGB(255,254,251,216));
    TeleportLoc3->TB_Func_13("interface\\ifcommon\\com_return_button.ddj", 0, 0);

    sz.pos.x = 40;
    sz.pos.y = 68;
    sz.size.width = 20;
    sz.size.height = 20;
    SaveLoc3 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, SaveButton3, 0);
    SaveLoc3->TB_Func_13("interface\\ifcommon\\com_plus_button.ddj", 0, 0);
    SaveLoc3->MoveGWnd(TeleportLoc3->GetBounds().pos.x + 258, TeleportLoc3->GetBounds().pos.y + 2);

    sz.pos.x = 40;
    sz.pos.y = 68;
    sz.size.width = 20;
    sz.size.height = 20;
    RemoveLoc3 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, RemoveButton3, 0);
    RemoveLoc3->TB_Func_13("interface\\ifcommon\\com_minus_button.ddj", 0, 0);
    RemoveLoc3->MoveGWnd(TeleportLoc3->GetBounds().pos.x - 26, TeleportLoc3->GetBounds().pos.y + 2);



    sz.pos.x = 40;
    sz.pos.y = 161;
    sz.size.width = 252;
    sz.size.height = 24;
    TeleportLoc4 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, Location4, 0);
    TeleportLoc4->SetText(L"<None>");
    TeleportLoc4->m_FontTexture.SetColor(D3DCOLOR_ARGB(255,254,251,216));
    TeleportLoc4->TB_Func_13("interface\\ifcommon\\com_return_button.ddj", 0, 0);


    sz.pos.x = 40;
    sz.pos.y = 68;
    sz.size.width = 20;
    sz.size.height = 20;
    SaveLoc4 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, SaveButton4, 0);
    SaveLoc4->TB_Func_13("interface\\ifcommon\\com_plus_button.ddj", 0, 0);
    SaveLoc4->MoveGWnd(TeleportLoc4->GetBounds().pos.x + 258, TeleportLoc4->GetBounds().pos.y + 2);


    sz.pos.x = 40;
    sz.pos.y = 68;
    sz.size.width = 20;
    sz.size.height = 20;
    RemoveLoc4 = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, RemoveButton4, 0);
    RemoveLoc4->TB_Func_13("interface\\ifcommon\\com_minus_button.ddj", 0, 0);
    RemoveLoc4->MoveGWnd(TeleportLoc4->GetBounds().pos.x - 26, TeleportLoc4->GetBounds().pos.y + 2);


    sz.pos.x = 40;
    sz.pos.y = 192;
    sz.size.width = 252;
    sz.size.height = 24;
    CancelBtn = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, 312, 0);
    CancelBtn->SetText(L"Cancel");
    CancelBtn->m_FontTexture.SetColor(D3DCOLOR_ARGB(255,254,251,216));
    CancelBtn->TB_Func_13("interface\\ifcommon\\com_return_button.ddj", 0, 0);



    this->ShowGWnd(false);
    ResetPosition();
    return true;
}

void CIFSavedLocation::OnUpdate()
{
}
void CIFSavedLocation::CloseWnd()
{
    this->OnCloseWnd();
}

void CIFSavedLocation::Remove1Loc() {
    if (TeleportLoc1->GetNText() != L"<None>")
    {
        TeleportLoc1->SetText(L"<None>");
        CMsgStreamBuffer buf(0x200F);
        buf << 1;
        SendMsg(buf);
    }
}

void CIFSavedLocation::Remove2Loc() {
    if (TeleportLoc2->GetNText() != L"<None>")
    {
       TeleportLoc2->SetText(L"<None>");
        CMsgStreamBuffer buf(0x200F);
        buf << 2;
        SendMsg(buf);
    }
}

void CIFSavedLocation::Remove3Loc() {
    if (TeleportLoc3->GetNText() != L"<None>")
    {
        TeleportLoc3->SetText(L"<None>");
        CMsgStreamBuffer buf(0x200F);
        buf << 3;
        SendMsg(buf);
    }
}
void CIFSavedLocation::Remove4Loc() {
    if (TeleportLoc4->GetNText() != L"<None>")
    {
        TeleportLoc4->SetText(L"<None>");
        CMsgStreamBuffer buf(0x200F);
        buf << 4;
        SendMsg(buf);
    }
}



void CIFSavedLocation::Teleport1Loc() {
    if (TeleportLoc1->GetNText() != L"<None>") {
        this->ShowGWnd(false);
        Send181C(1);
    }
}

void CIFSavedLocation::Teleport2Loc()
{
    if (TeleportLoc2->GetNText() != L"<None>") {
        this->ShowGWnd(false);
        Send181C(2);
    }
}
void CIFSavedLocation::Teleport3Loc()
{
    if (TeleportLoc3->GetNText() != L"<None>") {
        this->ShowGWnd(false);
        Send181C(3);
    }
}
void CIFSavedLocation::Teleport4Loc()
{
    if (TeleportLoc4->GetNText() != L"<None>") {
        this->ShowGWnd(false);
        Send181C(4);
    }
}
void CIFSavedLocation::SaveButton1Click() {
    if (TeleportLoc1->GetNText() != L"<None>") {
        g_pCGInterface->ShowMessage_Quest(L"You already saved location.");
        return;
    } else {
        D3DVECTOR CurPos = g_pCICPlayer->GetLocation();
        int WorldID = g_pCICPlayer->GetWorldID();
        std::wstringstream Reg;
        Reg << g_pCICPlayer->GetRegion().r;
        const std::n_wstring *regionname = g_CTextStringManager->GetString(Reg.str().c_str());
        TeleportLoc1->SetText(regionname->c_str());

        byte LocationID = 1;
        CMsgStreamBuffer buf(0x200A);
        buf << LocationID;
        buf << g_pCICPlayer->GetRegion().r << int(CurPos.x) << int(CurPos.y) << int(CurPos.z);
        buf << WorldID << std::n_string(TO_NSTRING(g_CTextStringManager->GetString(Reg.str().c_str())));

        SendMsg(buf);
    }
}

void CIFSavedLocation::SaveButton2Click() {
    if (TeleportLoc2->GetNText() != L"<None>") {
        g_pCGInterface->ShowMessage_Quest(L"You already saved location.");
        return;
    } else {
        D3DVECTOR CurPos = g_pCICPlayer->GetLocation();
        int WorldID = g_pCICPlayer->GetWorldID();
        std::wstringstream Reg;
        Reg << g_pCICPlayer->GetRegion().r;
        const std::n_wstring *regionname = g_CTextStringManager->GetString(Reg.str().c_str());
        TeleportLoc2->SetText(regionname->c_str());

        byte LocationID = 2;
        CMsgStreamBuffer buf(0x200A);
        buf << LocationID;
        buf << g_pCICPlayer->GetRegion().r << int(CurPos.x) << int(CurPos.y) << int(CurPos.z);
        buf << WorldID << std::n_string(TO_NSTRING(g_CTextStringManager->GetString(Reg.str().c_str())));

        SendMsg(buf);
    }
}

void CIFSavedLocation::SaveButton3Click() {
    if (TeleportLoc3->GetNText() != L"<None>") {
        g_pCGInterface->ShowMessage_Quest(L"You already saved location.");
        return;
    } else {
        D3DVECTOR CurPos = g_pCICPlayer->GetLocation();
        int WorldID = g_pCICPlayer->GetWorldID();
        std::wstringstream Reg;
        Reg << g_pCICPlayer->GetRegion().r;
        const std::n_wstring *regionname = g_CTextStringManager->GetString(Reg.str().c_str());
        TeleportLoc3->SetText(regionname->c_str());

        byte LocationID = 3;
        CMsgStreamBuffer buf(0x200A);
        buf << LocationID;
        buf << g_pCICPlayer->GetRegion().r << int(CurPos.x) << int(CurPos.y) << int(CurPos.z);
        buf << WorldID << std::n_string(TO_NSTRING(g_CTextStringManager->GetString(Reg.str().c_str())));

        SendMsg(buf);
    }
}

void CIFSavedLocation::SaveButton4Click() {
    if (TeleportLoc4->GetNText() != L"<None>") {
        g_pCGInterface->ShowMessage_Quest(L"You already saved location.");
        return;
    } else {
        D3DVECTOR CurPos = g_pCICPlayer->GetLocation();
        int WorldID = g_pCICPlayer->GetWorldID();
        std::wstringstream Reg;
        Reg << g_pCICPlayer->GetRegion().r;
        const std::n_wstring *regionname = g_CTextStringManager->GetString(Reg.str().c_str());
        TeleportLoc4->SetText(regionname->c_str());

        byte LocationID = 4;
        CMsgStreamBuffer buf(0x200A);
        buf << LocationID;
        buf << g_pCICPlayer->GetRegion().r << int(CurPos.x) << int(CurPos.y) << int(CurPos.z);
        buf << WorldID << std::n_string(TO_NSTRING(g_CTextStringManager->GetString(Reg.str().c_str())));

        SendMsg(buf);
    }
}


void CIFSavedLocation::ResetPosition()
{
    USHORT PosX = 0, PosY = 0;
    PosY = (CLIENT_SCREEN_HEIGHT/2) - (this->GetSize().height/2);
    PosX = (CLIENT_SCREEN_WIDTH/2) - (this->GetSize().width/2);
    this->MoveGWnd(PosX, PosY);
}

void CIFSavedLocation::Send181C(byte telslot)
{
    CIFSlotWithHelp* pSlot;
    CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
    for (int i = 0; i < 96; i++)
    {
        pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));
        if (pSlot->ItemInfo)
            if (pSlot->ItemInfo->GetObjectData()->TID == 0x19EC || pSlot->ItemInfo->GetObjectData()->TID == 0x19ED)
            {
                byte slot = pSlot->m_UniqueID - 87;
                CMsgStreamBuffer buf(0x181C);
                buf << telslot;
                buf << slot << pSlot->ItemInfo->GetObjectData()->TID;
                SendMsg(buf);
                break;
            }
    }
}