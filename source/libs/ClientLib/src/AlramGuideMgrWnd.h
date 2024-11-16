#pragma once

#include "IFWnd.h"

#define GDR_ALRAM_GUIDE_MGR_WND 158

class CAlramGuideMgrWnd : public CIFWnd {

GFX_DECLARE_DYNAMIC_EXISTING(CAlramGuideMgrWnd, 0x00ee99a8)

public:
    CAlramGuideMgrWnd();

    CIFWnd*GetGuide(int windowId);

    void UpdatePositions();

private:
    unsigned char m_numberOfIcons;
    std::list<CIFWnd*> m_list;
};
