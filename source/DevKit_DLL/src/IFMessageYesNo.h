#pragma once
#include "IFMainFrame.h"
#include "IFNormalTile.h"


class CIFMessageYesNo : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFMessageYesNo)
GFX_DECLARE_MESSAGE_MAP(CIFMessageYesNo)

public:
    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void UpdateMenuSize();
    static CIFWnd* DCICON;
    static CIFMessageYesNo* DCW;
    CIFNormalTile* mytile[10];
    CIFButton* button[10];
    CIFFrame* frame;
    CIFStatic* write;
    CIFStatic* test;
    static int UniqueID;
    static byte TeleportType;
    static int targetTeleport;
private:
    void On_BtnClick_1();

    void On_BtnClick_2();

    void OnClick_Exit();


};
