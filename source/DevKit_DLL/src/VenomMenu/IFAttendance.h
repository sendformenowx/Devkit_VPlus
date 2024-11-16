#pragma once
#include "IFMainFrame.h"
#include "IFDragableArea.h"
#include "IFSelectableArea.h"
class CIFAttendance : public CIFMainFrame
{

GFX_DECLARE_DYNCREATE(CIFAttendance)
GFX_DECLARE_MESSAGE_MAP(CIFAttendance)

public:
    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void UpdateMenuSize();
    void OnUnknownStuff();
    void ActivateTabPage(BYTE page);

public:
    static CIFWnd* ATTICON;
    static CIFAttendance* ATTW;
    static const int numberOfTabs = 2;
    static const int tabWidth = 94;
    static const int tabHeight = 24;
    static const int tabMarginLeft = 55;
    static const int tabFirstId = 200;

    CIFSelectableArea** m_pTabs;
    CIFStatic* mytile[10];
    CIFStatic* dayframes[50];
    CIFStatic* OK[29];
    CIFButton* button[10];
    CIFFrame* frame;
    CIFStatic* writeday[100];
    CIFStatic* itemnames[100];
    CIFStatic* days[100];
    CIFStatic* items[100];
    CIFStatic* rewards[10];
    CIFDragableArea* handle;
    CIFStatic* Year[10];
    CIFStatic* start;
    CIFStatic* end;
    void On_BtnClick_1();

    void On_BtnClick_2();

    void OnClick_Exit();


};
