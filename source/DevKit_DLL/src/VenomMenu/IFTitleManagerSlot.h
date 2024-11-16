#pragma once
#include "IFMainFrame.h"
#include "IFBarWnd.h"

class CIFTitleManagerSlot : public CIFWnd {
GFX_DECLARE_DYNCREATE(CIFTitleManagerSlot)
GFX_DECLARE_MESSAGE_MAP(CIFTitleManagerSlot)
public:
    CIFTitleManagerSlot(void);
    ~CIFTitleManagerSlot(void);

    bool OnCreate(long ln) override;
    int OnMouseLeftUp(int a1, int x, int y) override;

    void SetName(const wchar_t* name, int color);
    void ClearDDJ();
public:
    CIFStatic* m_custom_label1;
    CIFBarWnd* bars;

    std::wstring CurrText;
    int testcolor;
};
