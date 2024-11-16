#include <Game.h>
#include "IFMessageYesNo.h"
#include <NetProcessIn.h>


#define GDR_OK_BTN 3
#define GDR_CANCEL_BTN 4
#define GDR_CHEST_BG 31
CIFMessageYesNo* CIFMessageYesNo::DCW;
CIFWnd* CIFMessageYesNo::DCICON;

GFX_IMPLEMENT_DYNCREATE(CIFMessageYesNo, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFMessageYesNo, CIFMainFrame)
ONG_COMMAND(GDR_OK_BTN, &CIFMessageYesNo::On_BtnClick_1)
ONG_COMMAND(GDR_CANCEL_BTN, &CIFMessageYesNo::On_BtnClick_2)
GFX_END_MESSAGE_MAP()
int CIFMessageYesNo::UniqueID;
byte CIFMessageYesNo::TeleportType;
int CIFMessageYesNo::targetTeleport;

bool CIFMessageYesNo::OnCreate(long ln)
{
    //	printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);
    // TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);


    m_title->SetText(L"Job bot Control");
    TB_Func_13("interface\\messagebox\\msgbox2_window_", 0, 0);
    wnd_rect sz;


    sz.pos.x= 16;
    sz.pos.y = 40;
    sz.size.width = 325;
    sz.size.height = 100;
    mytile[1] = (CIFNormalTile* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFNormalTile), sz, 101, 1);
    mytile[1]->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_b.ddj", 0, 0);



    sz.pos.x= 26;
    sz.pos.y = 60;
    sz.size.width = 302;
    sz.size.height = 25;
    write = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_CHEST_BG, 0);
    write->SetText(L"Are you sure you want to teleport?");
    write->m_FontTexture.SetColor(D3DCOLOR_ARGB(255,239,218,164));



    sz.pos.x= 26;
    sz.pos.y = 60;
    sz.size.width = 32;
    sz.size.height = 32;
    test = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 105, 0);




    sz.pos.x= 185;
    sz.pos.y = 105;
    sz.size.width = 75;
    sz.size.height = 25;
    button[1] = (CIFButton*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, GDR_OK_BTN, 0);
    button[1]->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    button[1]->SetText(L"Confirm");



    sz.pos.x= 85;
    sz.pos.y = 105;
    sz.size.width = 75;
    sz.size.height = 25;

    button[0] = (CIFButton*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, GDR_CANCEL_BTN, 0);
    button[0]->TB_Func_13("interface\\ifcommon\\com_mid_button.ddj", 0, 0);
    button[0]->SetText(L"Cancel");





    this->m_close->ShowGWnd(false);

    this->ShowGWnd(false);

    UpdateMenuSize();


    return true;
}

void CIFMessageYesNo::OnUpdate()
{
}

void CIFMessageYesNo::UpdateMenuSize()
{


    const ClientResolutonData& res = CGame::GetClientDimensionStuff();
    MoveGWnd(((res.width - GetSize().width) - 400), ((res.height - GetSize().height) - 350));
    BringToFront();

}

void CIFMessageYesNo::On_BtnClick_1()
{
    CMsgStreamBuffer buf(0x1319);
    __int8 TelType = TeleportType;
    int targetTeleports= targetTeleport;
    buf << UniqueID << TelType << targetTeleports;
    this->OnCloseWnd();
    SendMsg(buf);

}

void CIFMessageYesNo::On_BtnClick_2() {
    this->OnCloseWnd();
    CMsgStreamBuffer buf(0x704B);
      buf << UniqueID;
      SendMsg(buf);
}
