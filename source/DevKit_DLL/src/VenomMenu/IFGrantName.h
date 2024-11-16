#pragma once
#include "IFMainFrame.h"
#include "IFEdit.h"
#include "IFNormalTile.h"

class CIFGrantName : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFGrantName)
GFX_DECLARE_MESSAGE_MAP(CIFGrantName)

public:
    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void UpdateMenuSize();
private:
    void On_BtnClick();

public:
    CIFButton *m_mybutton;
    CIFStatic* m_custom_label;
    CIFEdit *m_myname;
    CIFNormalTile* m_mytile1;
    CIFNormalTile* m_mytile2;
    CIFNormalTile* m_mytile3;
};
