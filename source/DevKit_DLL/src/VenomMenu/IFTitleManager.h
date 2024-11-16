#pragma once
#include "IFMainFrame.h"
#include "IFBarWnd.h"
#include "IFSpinButtonCtrl.h"
#include "IFVerticalScroll.h"
#include "IFScrollManager.h"
#include "IFTextBox.h"
#include "IFNormalTile.h"
#include "IFStretchWnd.h"
#include "IFSelectableArea.h"
#include "IFTitleManagerSlot.h"

class CIFTitleManager : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFTitleManager)
GFX_DECLARE_MESSAGE_MAP(CIFTitleManager)

public:
    bool OnCreate(long ln) override;

    void OnUpdate() override;

    void UpdateMenuSize();

public:
    int Func_4(int a2) override;
    /// \brief Show the given page
    /// \param page Page Number (0 to N)
    void OnUnknownStuff();
    void On_BtnClick();   
    void On_scrollBtnClick();
    void On_BtnClickRemove();

    void ActivateTabPage(BYTE page);
    void ClearDDJ();
    void Clear();
    void UpdateTitleName();
    void UpdateTapName();

    static struct RankStruct
    {
        int LineNum;
        int Id;
        std::wstring Titlename;
    };

    static struct ColorStruct
    {
        int ID;
        __int32 Color;
    };

    static std::vector<RankStruct> TitleNameRankList;
    static std::vector<RankStruct> TapNameRankList;
    static int selecttitlecolor;

    static std::vector<ColorStruct> TitleColor;
public:
    static const int numberOfTabs = 2;
    static const int tabWidth = 74;
    static const int tabHeight = 24;
    static const int tabMarginLeft = 55;
    static const int tabFirstId = 100;
    CIFTitleManagerSlot* m_slot[50];
    CIFTextBox* my_textbox;
    CIFTextBox* my_textbox2;
    CIFFrame* frame[50];
    CIFSelectableArea** m_pTabs;
    CIFEdit* owntitle;
    CIFEdit* owntitlenew;
    CIFStatic* label[10];
    CIFButton* removebtn;
    CIFButton* usebtn;
    CIFNormalTile* tile;
    CIFNormalTile* tile2;
    CIFStretchWnd* blacksquare;
    CIFBarWnd* bars[10];
    CIFScrollManager* m_scroll;
    CIFBarWnd* m_mybar[10];
    CIFStatic* m_custom_label6;

};