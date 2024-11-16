#include "IFFacebook.h"
#include "Game.h"
#include <NetProcessIn.h>

#define GDR_OK_BTN 3
#define GDR_CANCEL_BTN 4
#define GDR_CHEST_BG 31
CIFFacebook* CIFFacebook::FBW;
CGWnd* CIFFacebook::FBICON;

GFX_IMPLEMENT_DYNCREATE(CIFFacebook, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFFacebook, CIFMainFrame)
                    ONG_COMMAND(GDR_OK_BTN, &CIFFacebook::On_BtnClick_1)
                    ONG_COMMAND(GDR_CANCEL_BTN, &CIFFacebook::On_BtnClick_2)
GFX_END_MESSAGE_MAP()



bool CIFFacebook::OnCreate(long ln)
{
    //	printf("> " __FUNCTION__ "(%d)\n", ln);

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);
    // TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);


    m_title->SetText(L"Confirmation Window");
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
    write->SetText(L"Do you agree to redirect to the official facebook page?");
    write->m_FontTexture.SetColor(D3DCOLOR_ARGB(255,239,218,164));


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

void CIFFacebook::OnUpdate()
{
}

void CIFFacebook::UpdateMenuSize()
{
    const ClientResolutonData &res = CGame::GetClientDimensionStuff();

    MoveGWnd(((res.width - GetSize().width) - 80), GetPos().y);
    ////  MoveGWnd(((res.width - GetSize().width) - 80), (res.height - GetSize().height) - 300);
    BringToFront();

}

void CIFFacebook::On_BtnClick_1()
{
    ShellExecute(NULL, "open", CNetProcessIn::FacebookURL.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void CIFFacebook::On_BtnClick_2()
{
    this->OnCloseWnd();
}
