#include <IFButton.h>
#include <IFNormalTile.h>
#include "IFFrame.h"
#include "Test/TEST.H"
#include "IFWnd.h"

class CIFMessageBox : public CIFFrame {

GFX_DECLARE_DYNAMIC_EXISTING(CIFMessageBox, 0x00EE95A0)

    GFX_DECLARE_DYNCREATE_FN(CIFMessageBox)

GFX_DECLARE_MESSAGE_MAP(CIFMessageBox)

public:
    void SetMsgBoxHandler(int Id, int a3);
    void FUN_BTNPARTY();
    void FUN_BTNLOCATION();
public:
    CIFButton* CancelBtn;
    CIFButton* BTNPARTY;
    CIFButton* BTNLOCATION;
};