#pragma once
#include "IFMainFrame.h"


class CIFRankSlot : public CIFWnd
{
GFX_DECLARE_DYNCREATE(CIFRankSlot)
GFX_DECLARE_MESSAGE_MAP(CIFRankSlot)

public:

    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void WriteLine(const wchar_t* num, const wchar_t* Charname, const wchar_t* Guild, const wchar_t* Points);
    void ShowIcon();
public:
    CIFStatic* m_custom_label1;
    CIFStatic* m_custom_label2;
    CIFStatic* m_custom_label3;
    CIFStatic* m_custom_label4;
    CIFStatic* m_custom_label5;
};