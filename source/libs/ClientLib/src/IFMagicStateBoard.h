#pragma once

#include "IFFrame.h"
#include "IFDragableArea.h"
#include "IFEdit.h"
#include "IFGauge.h"

class CIFMagicStateBoard : public CIFFrame {

GFX_DECLARE_DYNAMIC_EXISTING(CIFMagicStateBoard, 0x00eec928)

    GFX_DECLARE_DYNCREATE_FN(CIFMagicStateBoard)

GFX_DECLARE_MESSAGE_MAP(CIFMagicStateBoard)

public:
    /// \address 007ef6f0
    bool OnCreate(long ln) override;

public:
    CIFStatic * GDR_MSB_CURSE_91;
    CIFStatic * GDR_MSB_CURSE_81;
    CIFStatic * GDR_MSB_CURSE_71;
    CIFStatic * GDR_MSB_CURSE_61;
    CIFStatic * GDR_MSB_CURSE_51;
    CIFStatic * GDR_MSB_CURSE_41;
    CIFStatic * GDR_MSB_CURSE_31;
    CIFStatic * GDR_MSB_CURSE_21;
    CIFStatic * GDR_MSB_CURSE_11;
    CIFStatic * GDR_MSB_BLESS_91;
    CIFStatic * GDR_MSB_BLESS_81;
    CIFStatic * GDR_MSB_BLESS_71;
    CIFStatic * GDR_MSB_BLESS_61;
    CIFStatic * GDR_MSB_BLESS_51;
    CIFStatic * GDR_MSB_BLESS_41;
    CIFStatic * GDR_MSB_BLESS_31;
    CIFStatic * GDR_MSB_BLESS_21;
    CIFStatic * GDR_MSB_BLESS_11;
    CIFGauge * GDR_MSB_CURSE_GAUGE_91;
    CIFGauge * GDR_MSB_CURSE_GAUGE_81;
    CIFGauge * GDR_MSB_CURSE_GAUGE_71;
    CIFGauge * GDR_MSB_CURSE_GAUGE_61;
    CIFGauge * GDR_MSB_CURSE_GAUGE_51;
    CIFGauge * GDR_MSB_CURSE_GAUGE_41;
    CIFGauge * GDR_MSB_CURSE_GAUGE_31;
    CIFGauge * GDR_MSB_CURSE_GAUGE_21;
    CIFGauge * GDR_MSB_CURSE_GAUGE_11;
    CIFGauge * GDR_MSB_BLESS_GAUGE_91;
    CIFGauge * GDR_MSB_BLESS_GAUGE_81;
    CIFGauge * GDR_MSB_BLESS_GAUGE_71;
    CIFGauge * GDR_MSB_BLESS_GAUGE_61;
    CIFGauge * GDR_MSB_BLESS_GAUGE_51;
    CIFGauge * GDR_MSB_BLESS_GAUGE_41;
    CIFGauge * GDR_MSB_BLESS_GAUGE_31;
    CIFGauge * GDR_MSB_BLESS_GAUGE_21;
    CIFGauge * GDR_MSB_BLESS_GAUGE_11;

};
