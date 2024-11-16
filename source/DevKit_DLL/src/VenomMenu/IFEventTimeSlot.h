#pragma once
#include "IFMainFrame.h"

class CIFEventTimeSlot : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFEventTimeSlot)
GFX_DECLARE_MESSAGE_MAP(CIFEventTimeSlot)

public:

    bool OnCreate(long ln) override;
    void WriteLine(const wchar_t* test, const wchar_t* EventName, const wchar_t* DAY, const wchar_t* Time);
public:
    CIFStatic* m_custom_label1;
    CIFStatic* m_custom_label2;
    CIFStatic* m_custom_label3;
    CIFStatic* m_custom_label4;

};

