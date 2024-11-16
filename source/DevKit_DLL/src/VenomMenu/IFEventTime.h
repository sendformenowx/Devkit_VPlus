#pragma once
#include "IFMainFrame.h"
#include "IFEventTimeSlot.h"
#include "IFEventTimeSlotList.h"
#include "IFSpinButton.h"
#include "IFNormalTile.h"
#include "IFStretchWnd.h"
class CIFEventTime : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFEventTime)
GFX_DECLARE_MESSAGE_MAP(CIFEventTime)

public:
    bool OnCreate(long ln) override;
    void OnUpdate() override;

    void UpdateMenuSize();

    void HideLists();

    void ShowList(BYTE listid);

    bool EventListContains(const wchar_t* UqName);

    void UpdateLog();

    bool IsPageFull(BYTE PageID, BYTE LineID);

private:
    void On_BtnClick();
    void On_BtnClick1();
    void OnClick_Exit();
public:
    static struct EventSetting
    {
        std::wstring ID;
        int LineNum;
        std::wstring EventName;
        std::wstring Day;
        std::wstring Time;
        std::wstring State;
    };

    static std::vector<EventSetting> EventList;

    CIFStatic* m_custom_label2;
    CIFStatic* m_custom_label5;
    CIFStatic* m_custom_label6;
    CIFStatic* m_custom_label7;

    CIFFrame* Frame;
    CIFEventTimeList* Slot1;
    CIFEventTimeList* Slot2;
    CIFEventTimeList* Slot3;
    CIFEventTimeList* Slot4;
    CIFSpinControl* m_spin;
    CIFNormalTile* tile;
    CIFStretchWnd* blacksquare;

};

