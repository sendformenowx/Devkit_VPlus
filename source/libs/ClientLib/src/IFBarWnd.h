#pragma once

#include "IFWnd.h"
#include "IFMainFrame.h"

class CIFBarWnd : public CIFWnd {
GFX_DECLARE_DYNAMIC_EXISTING(CIFBarWnd, 0x00eecaf4)
public:
    void sub_64F8A0(std::n_wstring &str, int a3, int a4, int a5, int a6, int a7, int a8);
BEGIN_FIXTURE()
        ENSURE_SIZE(876)
    END_FIXTURE()
    RUN_FIXTURE(CIFBarWnd)

};
