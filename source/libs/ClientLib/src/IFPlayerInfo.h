#pragma once

#include "IFButton.h"
#include "IFGauge.h"
#include "IFStatic.h"
#include "IFWnd.h"

class CIFPlayerInfo : public CIFWnd {
GFX_DECLARE_DYNAMIC_EXISTING(CIFPlayerInfo, 0x00eea7e8)

    GFX_DECLARE_DYNCREATE_FN(CIFPlayerInfo)

GFX_DECLARE_MESSAGE_MAP(CIFPlayerInfo)

public:
    /// \address 006b84e0
    bool OnCreate(long ln) override;

    /// \address 006b8910
    void OnUpdate() override;

    /// \address 006b8310
    void ShowGWnd(bool bVisible) override;

private:
    /// \address 006b83f0
    void OnClick_IncrementStr();

    /// \address 006b8410
    void OnClick_IncrementInt();

private:
    CIFStatic* m_pGDR_PI_TEXT_LEVEL; //0x036C
    CIFStatic* m_pGDR_PI_TEXT_CURXP2; //0x0370
    CIFStatic* m_pGDR_PI_TEXT_NEXTXP2; //0x0374
    CIFStatic* m_pGDR_PI_TEXT_STAT2; //0x0378
    CIFStatic* m_pGDR_PI_HONOR_DATA; //0x037C
    CIFStatic* m_pGDR_PI_TEXT_HONOR_STATIC; //0x0380
    CIFStatic* m_pGDR_PI_TEXT_HP_DAT; //0x0384
    CIFStatic* m_pGDR_PI_TEXT_STRENGTH_DAT; //0x0388
    CIFStatic* m_pGDR_PI_TEXT_MP_DAT; //0x038C
    CIFStatic* m_pGDR_PI_TEXT_INTELLECT_DAT; //0x0390
    CIFButton* m_pGDR_PI_BTN_ADDMP; //0x0394
    CIFButton* m_pGDR_PI_BTN_ADDHP; //0x0398
    CIFGauge* m_pGDR_PI_GAUGE_HPGAUGE; //0x039C
    CIFGauge* m_pGDR_PI_GAUGE_MPGAUGE; //0x03A0
    CIFStatic* m_pGDR_PI_TEXT_PHYATT_DAT; //0x03A4
    CIFStatic* m_pGDR_PI_TEXT_PHYDEF_DAT; //0x03A8
    CIFStatic* m_pGDR_PI_TEXT_PHYBAL_DAT; //0x03AC
    CIFStatic* m_pGDR_PI_TEXT_HIT_DAT; //0x03B0
    CIFStatic* m_pGDR_PI_TEXT_MAGATT_DAT; //0x03B4
    CIFStatic* m_pGDR_PI_TEXT_MAGDEF_DAT; //0x03B8
    CIFStatic* m_pGDR_PI_TEXT_MAGBAL_DAT; //0x03BC
    CIFStatic* m_pGDR_PI_TEXT_PARRY_DAT; //0x03C0
    CIFStatic* m_pGDR_PI_JOB_ALIAS; //0x03C4
    CIFStatic* m_pGDR_PI_JOB_ICON; //0x03C8
    CIFStatic* m_pGDR_PI_JOB_TITLE; //0x03CC
    CIFStatic* m_pGDR_PI_JOB_GRADE; //0x03D0
    CIFStatic* m_pGDR_PI_JOB_EXP; //0x03D4
    CIFGauge* m_pGDR_PI_JOB_EXP_GAUGE; //0x03D8

private:
BEGIN_FIXTURE()
        ENSURE_SIZE(0x3dc)
        ENSURE_OFFSET(m_pGDR_PI_TEXT_LEVEL, 0x036C)
        ENSURE_OFFSET(m_pGDR_PI_TEXT_CURXP2, 0x0370)
        ENSURE_OFFSET(m_pGDR_PI_TEXT_NEXTXP2, 0x0374)
        ENSURE_OFFSET(m_pGDR_PI_TEXT_STAT2, 0x0378)
        ENSURE_OFFSET(m_pGDR_PI_HONOR_DATA, 0x037C)
        ENSURE_OFFSET(m_pGDR_PI_TEXT_HONOR_STATIC, 0x0380)
        ENSURE_OFFSET(m_pGDR_PI_TEXT_HP_DAT, 0x0384)
        ENSURE_OFFSET(m_pGDR_PI_TEXT_STRENGTH_DAT, 0x0388)
        ENSURE_OFFSET(m_pGDR_PI_TEXT_MP_DAT, 0x038C)
        ENSURE_OFFSET(m_pGDR_PI_TEXT_INTELLECT_DAT, 0x0390)
        ENSURE_OFFSET(m_pGDR_PI_BTN_ADDMP, 0x0394)
        ENSURE_OFFSET(m_pGDR_PI_BTN_ADDHP, 0x0398)
        ENSURE_OFFSET(m_pGDR_PI_GAUGE_HPGAUGE, 0x039C)
        ENSURE_OFFSET(m_pGDR_PI_GAUGE_MPGAUGE, 0x03A0)
        ENSURE_OFFSET(m_pGDR_PI_TEXT_PHYATT_DAT, 0x03A4)
        ENSURE_OFFSET(m_pGDR_PI_TEXT_PHYDEF_DAT, 0x03A8)
        ENSURE_OFFSET(m_pGDR_PI_TEXT_PHYBAL_DAT, 0x03AC)
        ENSURE_OFFSET(m_pGDR_PI_TEXT_HIT_DAT, 0x03B0)
        ENSURE_OFFSET(m_pGDR_PI_TEXT_MAGATT_DAT, 0x03B4)
        ENSURE_OFFSET(m_pGDR_PI_TEXT_MAGDEF_DAT, 0x03B8)
        ENSURE_OFFSET(m_pGDR_PI_TEXT_MAGBAL_DAT, 0x03BC)
        ENSURE_OFFSET(m_pGDR_PI_TEXT_PARRY_DAT, 0x03C0)
        ENSURE_OFFSET(m_pGDR_PI_JOB_ALIAS, 0x03C4)
        ENSURE_OFFSET(m_pGDR_PI_JOB_ICON, 0x03C8)
        ENSURE_OFFSET(m_pGDR_PI_JOB_TITLE, 0x03CC)
        ENSURE_OFFSET(m_pGDR_PI_JOB_GRADE, 0x03D0)
        ENSURE_OFFSET(m_pGDR_PI_JOB_EXP, 0x03D4)
        ENSURE_OFFSET(m_pGDR_PI_JOB_EXP_GAUGE, 0x03D8)
    END_FIXTURE()

    RUN_FIXTURE(CIFPlayerInfo)


}; //Size=0x03DC
