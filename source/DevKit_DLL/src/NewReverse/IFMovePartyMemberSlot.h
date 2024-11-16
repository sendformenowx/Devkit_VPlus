#pragma once
#include "IFMainFrame.h"

class CIFMovePartyMemberSlot : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFMovePartyMemberSlot)
GFX_DECLARE_MESSAGE_MAP(CIFMovePartyMemberSlot)

public:
    CIFMovePartyMemberSlot(void);
    ~CIFMovePartyMemberSlot(void);
    int OnMouseLeftUp(int a1, int x, int y) override;
    bool OnCreate(long ln) override;
public:
    CIFStatic* m_custom_label1;
    CIFStatic* m_custom_label2;
    CIFStatic* m_custom_label3;
    CIFStatic* m_custom_label4;
    CIFStatic* m_custom_label5;
    CIFStatic* m_custom_label6;
    void WriteLine(const wchar_t* fakenum, int num, const wchar_t* CharName);
};
