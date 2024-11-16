#pragma once
#include "IFMainFrame.h"
#include "IFNormalTile.h"

class CIFFacebook : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFFacebook)
GFX_DECLARE_MESSAGE_MAP(CIFFacebook)

public:
    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void UpdateMenuSize();
    static CGWnd* FBICON;
    static CIFFacebook* FBW;
    CIFNormalTile* mytile[10];
    CIFButton* button[10];
    CIFFrame* frame;
    CIFStatic* write;
private:
    void On_BtnClick_1();

    void On_BtnClick_2();

    void OnClick_Exit();


};
