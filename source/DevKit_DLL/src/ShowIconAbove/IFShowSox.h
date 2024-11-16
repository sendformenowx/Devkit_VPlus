#pragma once
#include "IFMainFrame.h"
#include "IFSpinButtonCtrl.h"
#include "IFVerticalScroll.h"
#include "IFTextBox.h"
#include "IFNormalTile.h"
#include "IFStretchWnd.h"
#include <IFDecoratedStatic.h>

class CIFShowSox : public CIFDecoratedStatic
{
GFX_DECLARE_DYNCREATE(CIFShowSox)

public:

    CIFShowSox(void);
    ~CIFShowSox(void);

    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void OnTimer(int) override;
    void OpenIconWnd(int timeoutSeconds);
    void UpdateMenuSize();
public:
    CIFDecoratedStatic* icon;
    int IconShowingLeft; //0x03F4
    CIFStatic* icon2;


};