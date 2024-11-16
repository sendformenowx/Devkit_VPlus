#include "IFMessageBox.h"
#include <remodel/MemberFunctionHook.h>
#include <imgui/imgui.h>
#include <IFSystemMessage.h>
#include <GInterface.h>
#include "Game.h"

#define GDR_MBIN_BTN_CANCEL 201
#define REVERSE_MOVETOPARTY 8000
#define REVERSE_MOVETOLOCATION 8001


GFX_IMPLEMENT_DYNAMIC_EXISTING(CIFMessageBox, 0x00EE95A0)
GFX_IMPLEMENT_DYNCREATE_FN(CIFMessageBox, CIFWnd)

GFX_BEGIN_MESSAGE_MAP(CIFMessageBox, CIFWnd)
                    ONG_COMMAND(REVERSE_MOVETOPARTY, &CIFMessageBox::FUN_BTNPARTY)
                    ONG_COMMAND(REVERSE_MOVETOLOCATION, &CIFMessageBox::FUN_BTNLOCATION)
GFX_END_MESSAGE_MAP()


void CIFMessageBox::SetMsgBoxHandler(int Id, int a3) {
    reinterpret_cast<void (__thiscall *)(CIFMessageBox *, int, int)>(0x00644c90)(this, Id, a3);
    if (Id == 33) {

        wnd_rect sz;
        this->SetGWndSize(300, 280);


        sz.pos.x = 25;
        sz.pos.y = 169;
        sz.size.width = 252;
        sz.size.height = 24;
        BTNPARTY = (CIFButton *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, REVERSE_MOVETOPARTY, 0);
        BTNPARTY->SetText(L"Move to party member.");
        BTNPARTY->m_FontTexture.SetColor(D3DCOLOR_ARGB(255,254,251,216));
        BTNPARTY->TB_Func_13("interface\\ifcommon\\com_return_button.ddj", 0, 0);


        sz.pos.x = 25;
        sz.pos.y = 169;
        sz.size.width = 252;
        sz.size.height = 24;
        BTNLOCATION = (CIFButton *) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, REVERSE_MOVETOLOCATION, 0);
        BTNLOCATION->SetText(L"Move to saved location.");
        BTNLOCATION->m_FontTexture.SetColor(D3DCOLOR_ARGB(255,254,251,216));
        BTNLOCATION->TB_Func_13("interface\\ifcommon\\com_return_button.ddj", 0, 0);
        BTNLOCATION->MoveGWnd(BTNPARTY->GetBounds().pos.x, BTNPARTY->GetBounds().pos.y + 31);


        // test->MoveGWnd(CancelBtn->GetBounds().pos.x, CancelBtn->GetBounds().pos.y + 30);

        CancelBtn = m_IRM.GetResObj<CIFButton>(GDR_MBIN_BTN_CANCEL, 1);
        CancelBtn->MoveGWnd(BTNLOCATION->GetBounds().pos.x, BTNLOCATION->GetBounds().pos.y + 31);

    }
}

void CIFMessageBox::FUN_BTNPARTY()
{

}

void CIFMessageBox::FUN_BTNLOCATION()
{

}