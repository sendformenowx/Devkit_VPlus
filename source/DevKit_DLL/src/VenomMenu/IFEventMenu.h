#pragma once
#include "IFMainFrame.h"
#include "IFNormalTile.h"
#include "IFStretchWnd.h"
#include "IFBarWnd.h"
class CIFEventMenu : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFEventMenu)
GFX_DECLARE_MESSAGE_MAP(CIFEventMenu)

public:
    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void UpdateMenuSize();
    static CIFWnd* EventIcon;
    static CIFEventMenu* EventW;
    CIFNormalTile* mytile[10];
    CIFButton* button[10];
    CIFFrame* frame[10];
    CIFStatic* write[10];
    CIFStatic* eventname[10];
    CIFStatic* regstatus[10];
    CIFBarWnd* gills[10];
    CIFStretchWnd* blacksquare;
    CIFBarWnd* lines[10];
private:
    void RegisterLMS();
    void RegisterSURV();
    void RegisterLG();
    void OnClick_Exit();


};
