#pragma once
#include "IFMainFrame.h"
#include "IFNormalTile.h"


class CIFDiscord : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFDiscord)
GFX_DECLARE_MESSAGE_MAP(CIFDiscord)

public:
    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void UpdateMenuSize();
    static CIFWnd* DCICON;
    static CIFDiscord* DCW;
    CIFNormalTile* mytile[10];
    CIFButton* button[10];
    CIFFrame* frame;
    CIFStatic* write;
    CIFStatic* test;
private:
    void On_BtnClick_1();

    void On_BtnClick_2();

    void OnClick_Exit();


};
