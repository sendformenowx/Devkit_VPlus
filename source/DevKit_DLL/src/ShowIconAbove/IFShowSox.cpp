#include "IFShowSox.h"
#include <BSLib/Debug.h>
#include <GlobalHelpersThatHaveNoHomeYet.h>

#include <BSLib/multibyte.h>
#include <GInterface.h>
#include <Game.h>

GFX_IMPLEMENT_DYNCREATE(CIFShowSox, CIFDecoratedStatic)


CIFShowSox::CIFShowSox(void)
{
    BS_DEBUG("> " __FUNCTION__);
}



CIFShowSox::~CIFShowSox(void)
{
    BS_DEBUG("> " __FUNCTION__);
}

bool CIFShowSox::OnCreate(long ln)
{

    CIFDecoratedStatic::OnCreate(ln);

   // TB_Func_13("interface\\alchemy\\alcm_button_01_focus.ddj", 0, 0);
   // sub_634470("interface\\alchemy\\alcm_effect_success.ddj");

   // set_N00009BD4(2);
   // set_N00009BD3(500);
  //  sub_634470("interface\\alchemy\\alcm_effect_success.ddj");
    RECT Butt1rect2 = { 18,18,32,32 };
    icon2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), Butt1rect2, 1, 0);

    UpdateMenuSize();
    this->ShowGWnd(false);
    return true;
}

void CIFShowSox::UpdateMenuSize()
{
    const ClientResolutonData &res = CGame::GetClientDimensionStuff();

    MoveGWnd(((res.width - GetSize().width) - 776), GetPos().y);
    BringToFront();

}

void CIFShowSox::OnUpdate()
{

    //icon->TB_Func_13("interface\\brmenu\\logo1.ddj", 0, 0);
    //icon->sub_634470("interface\\brmenu\\logo2.ddj");

    //icon->set_N00009BD4(2);
    //icon->set_N00009BD3(500);

}
#define TIMERSHOWICON 10001
void CIFShowSox::OnTimer(int timerId) {
    if (timerId == TIMERSHOWICON) {


        this->KillTimer(TIMERSHOWICON);

        this->ShowGWnd(false);
    }
}


void CIFShowSox::OpenIconWnd(int timeoutSeconds) {

    UpdateMenuSize();
    this->ShowGWnd(true);
    this->IconShowingLeft = timeoutSeconds;
    this->StartTimer(TIMERSHOWICON, 10000);
}

