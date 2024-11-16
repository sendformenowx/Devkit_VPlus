#pragma once

#include "IFWnd.h"
#include "IFStatic.h"

class CIFTargetWindowPlayer : public CIFWnd {
GFX_DECLARE_DYNAMIC_EXISTING(CIFTargetWindowPlayer, 0x00eea5dc)

    GFX_DECLARE_DYNCREATE_FN(CIFTargetWindowPlayer)

GFX_DECLARE_MESSAGE_MAP(CIFTargetWindowPlayer)

public:
    /// \address 0069b180
    bool OnCreate(long ln) override;

    /// \address 0069b0d0
    void FUN_0069b0d0(int objectId);

private:
    int m_objectId; //0x036C
    CIFStatic * m_custom_label;

};
