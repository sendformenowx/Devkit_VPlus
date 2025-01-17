#pragma once

#include "IFStretchWnd.h"

class CIFNotify : public CIFStretchWnd {
GFX_DECLARE_DYNAMIC_EXISTING(CIFNotify, 0xEEC208)
public:
    /// Show the notification message
    /// \address 007b3eb0
    /// \param msg Message to be shown
    void ShowMessage(const std::n_wstring& msg);

    /// \brief Set the Y position of this element
    /// \details This value is used for auto-positioning.
    /// \address 007b3d40
    void SetYPosition(int yposition);

    /// \brief Sets the background color
    /// \address 007b3d10
    void SetColor(unsigned char red, unsigned char green, unsigned char blue);

private:
    char pad7c8[16]; // 0x07c8
    int m_yposition; // 0x07d4
    unsigned char m_red; // 0x7d8
    unsigned char m_green; // 0x7d9
    unsigned char m_blue; // 0x7da

private:
BEGIN_FIXTURE()
        ENSURE_SIZE(0x7dc)
        ENSURE_OFFSET(m_yposition, 0x7d4)
        ENSURE_OFFSET(m_red, 0x7d8)
        ENSURE_OFFSET(m_green, 0x7d9)
        ENSURE_OFFSET(m_blue, 0x7da)
    END_FIXTURE()

    RUN_FIXTURE(CIFNotify)
};