#pragma once

#include <IFNormalTile.h>
#include "IFMainFrame.h"
#include "IFTextBox.h"
#include "IFVerticalScroll.h"
#include "IFEdit.h"


class CIFSavedLocation : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFSavedLocation)
GFX_DECLARE_MESSAGE_MAP(CIFSavedLocation)

public:
    void Send181C(byte telslot);
    void SaveButton1Click();
    void SaveButton2Click();
    void SaveButton3Click();
    void SaveButton4Click();
    void Teleport1Loc();
    void Teleport2Loc();
    void Teleport3Loc();
    void Teleport4Loc();
    void Remove1Loc();
    void Remove2Loc();
    void Remove3Loc();
    void Remove4Loc();

    void CloseWnd();
    bool OnCreate(long ln) override;
    void OnUpdate() override;
    void ResetPosition();
private:
private:
public:
    CIFEdit *m_edit;
    CIFVerticalScroll *m_vericalSroll;
    CIFTextBox *m_textbox;
    CIFButton *TeleportLoc1;
    CIFButton *TeleportLoc2;
    CIFButton *TeleportLoc3;
    CIFButton *TeleportLoc4;
    CIFButton *SaveLoc1;
    CIFButton *SaveLoc2;
    CIFButton *SaveLoc3;
    CIFButton *SaveLoc4;
    CIFButton *RemoveLoc1;
    CIFButton *RemoveLoc2;
    CIFButton *RemoveLoc3;
    CIFButton *RemoveLoc4;

    CIFButton *CancelBtn;
    CIFStatic* m_custom_label1;
    CIFStatic* reversewindowstext;
    CIFNormalTile* background;

};



