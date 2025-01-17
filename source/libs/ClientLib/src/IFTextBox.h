#pragma once

#include "IFListCtrl.h"

class CIFTextBox : public CIFListCtrl {
GFX_DECLARE_DYNAMIC_EXISTING(CIFTextBox, 0x00ee9760)
// TODO: Add Runtime Class Info
public:
    /// \address 00638B50
    void sub_638B50(int a2);

    /// \address 0064E380
    void sub_64E380(int a2);

    /// \address 00638C70
    void sub_638C70(int a2);

    /// \address 00638D50
    void sub_638D50(int a2);

    /// \address 00638D40
    void sub_638D40(int a2);

    /// \address 0064F8A0
    void sub_64F8A0(std::n_wstring &str, int a3, int a4, int a5, int a6, int a7, int a8);

    /// \address 0064F660
    void sub_64F660(std::n_string &str, int a3, int a4, int a5, int a6, int a7, int a8);
    void Removeline(int line);

public:
    char N00009D87; //0x03CC
    char pad_03CD[15]; //0x03CD

    /// Number of lines currently stored in the text box
    int m_CurrentLines; //0x03DC


    BEGIN_FIXTURE()
        ENSURE_SIZE(992)
        ENSURE_OFFSET(m_CurrentLines, 0x3DC)
    END_FIXTURE()

    RUN_FIXTURE(CIFTextBox)
};
