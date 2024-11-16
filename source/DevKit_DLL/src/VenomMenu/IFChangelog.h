#pragma once
#include "IFMainFrame.h"
#include "IFTextBox.h"
#include "IFNormalTile.h"
#include "IFVerticalScroll.h"
class CIFChangelog : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFChangelog)
GFX_DECLARE_MESSAGE_MAP(CIFChangelog)



public:
    void UpdateMenuSize();
    bool OnCreate(long ln) override;
    void OnUpdate() override;
private:
    void On_BtnClick();

public:
    CIFTextBox* my_textbox;
    CIFFrame* frame;
    CIFNormalTile* tile;
    CIFNormalTile* tile2;
    CIFStatic* paper;

};
