#pragma once
#include "IFMainFrame.h"
#include "IFEventTimeSlot.h"
#include "IFBarWnd.h"


class CIFEventTimeList : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFEventTimeList)
GFX_DECLARE_MESSAGE_MAP(CIFEventTimeList)

public:

    bool OnCreate(long ln) override;
    void OnUpdate() override;
private:
    CIFStatic* m_custom_label2;
    CIFBarWnd* bars[50];
public:
    CIFEventTimeSlot* Line1;
    CIFEventTimeSlot* Line2;
    CIFEventTimeSlot* Line3;
    CIFEventTimeSlot* Line4;
    CIFEventTimeSlot* Line5;
    CIFEventTimeSlot* Line6;
    CIFEventTimeSlot* Line7;
    CIFEventTimeSlot* Line8;
    CIFEventTimeSlot* Line9;
    CIFEventTimeSlot* Line10;
};



