#pragma once
#include "IFMainFrame.h"
#include "IFEdit.h"
#include "IFNormalTile.h"

class CIFCharlock : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFCharlock)
GFX_DECLARE_MESSAGE_MAP(CIFCharlock)

public:
    bool OnCreate(long ln) override;
    void OnUpdate() override;
private:
    void On_BtnClick();
    void On_BtnClickUnlock();

public:
    CIFButton *m_mybutton;
    CIFButton *m_mybutton2;
    CIFStatic* m_custom_label;
    CIFEdit *m_myname;
    CIFNormalTile* m_mytile1;
    CIFNormalTile* m_mytile2;
    CIFNormalTile* m_mytile3;
    void UpdateMenuSize();
};
