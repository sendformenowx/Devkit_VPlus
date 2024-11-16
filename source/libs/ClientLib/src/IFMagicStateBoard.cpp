#include "IFMagicStateBoard.h"
#include "GInterface.h"
#include "Game.h"
#include "IFButton.h"
#include "TextStringManager.h"
#include "../../../DevKit_DLL/src/GameHelpers/GameMain.h"
#include <remodel/MemberFunctionHook.h>

GFX_IMPLEMENT_DYNAMIC_EXISTING(CIFMagicStateBoard, 0x00eec928)
GFX_IMPLEMENT_DYNCREATE_FN(CIFMagicStateBoard, CIFWnd)


enum {
    GDR_MSB_CURSE_9 = 19,
    GDR_MSB_CURSE_8 = 18,
    GDR_MSB_CURSE_7 = 17,
    GDR_MSB_CURSE_6 = 16,
    GDR_MSB_CURSE_5 = 15,
    GDR_MSB_CURSE_4 = 14,
    GDR_MSB_CURSE_3 = 13,
    GDR_MSB_CURSE_2 = 12,
    GDR_MSB_CURSE_1 = 11,
    GDR_MSB_BLESS_9 = 9,
    GDR_MSB_BLESS_8 = 8,
    GDR_MSB_BLESS_7 = 7,
    GDR_MSB_BLESS_6 = 6,
    GDR_MSB_BLESS_5 = 5,
    GDR_MSB_BLESS_4 = 4,
    GDR_MSB_BLESS_3 = 3,
    GDR_MSB_BLESS_2 = 2,
    GDR_MSB_BLESS_1 = 1,
    GDR_MSB_CURSE_GAUGE_9 = 39,
    GDR_MSB_CURSE_GAUGE_8 = 38,
    GDR_MSB_CURSE_GAUGE_7 = 37,
    GDR_MSB_CURSE_GAUGE_6 = 36,
    GDR_MSB_CURSE_GAUGE_5 = 35,
    GDR_MSB_CURSE_GAUGE_4 = 34,
    GDR_MSB_CURSE_GAUGE_3 = 33,
    GDR_MSB_CURSE_GAUGE_2 = 32,
    GDR_MSB_CURSE_GAUGE_1 = 31,
    GDR_MSB_BLESS_GAUGE_9 = 29,
    GDR_MSB_BLESS_GAUGE_8 = 28,
    GDR_MSB_BLESS_GAUGE_7 = 27,
    GDR_MSB_BLESS_GAUGE_6 = 26,
    GDR_MSB_BLESS_GAUGE_5 = 25,
    GDR_MSB_BLESS_GAUGE_4 = 24,
    GDR_MSB_BLESS_GAUGE_3 = 23,
    GDR_MSB_BLESS_GAUGE_2 = 22,
    GDR_MSB_BLESS_GAUGE_1 = 21
};

GFX_BEGIN_MESSAGE_MAP(CIFMagicStateBoard, CIFWnd)
GFX_END_MESSAGE_MAP()


bool CIFMagicStateBoard::OnCreate(long ln) {
    CIFFrame::OnCreate(ln);

    m_IRM.LoadFromFile("resinfo\\ifmagicstateboard.txt");
    m_IRM.CreateInterfaceSection("Create", this);


    GDR_MSB_CURSE_91 = m_IRM.GetResObj<CIFStatic>(GDR_MSB_CURSE_9, 1);
    GDR_MSB_CURSE_81 = m_IRM.GetResObj<CIFStatic>(GDR_MSB_CURSE_8, 1);
    GDR_MSB_CURSE_71 = m_IRM.GetResObj<CIFStatic>(GDR_MSB_CURSE_7, 1);
    GDR_MSB_CURSE_61 = m_IRM.GetResObj<CIFStatic>(GDR_MSB_CURSE_6, 1);
    GDR_MSB_CURSE_51 = m_IRM.GetResObj<CIFStatic>(GDR_MSB_CURSE_5, 1);
    GDR_MSB_CURSE_41 = m_IRM.GetResObj<CIFStatic>(GDR_MSB_CURSE_4, 1);
    GDR_MSB_CURSE_31 = m_IRM.GetResObj<CIFStatic>(GDR_MSB_CURSE_3, 1);
    GDR_MSB_CURSE_21 = m_IRM.GetResObj<CIFStatic>(GDR_MSB_CURSE_2, 1);
    GDR_MSB_CURSE_11 = m_IRM.GetResObj<CIFStatic>(GDR_MSB_CURSE_1, 1);

    GDR_MSB_BLESS_91 = m_IRM.GetResObj<CIFStatic>(GDR_MSB_BLESS_9 , 1);
    GDR_MSB_BLESS_81 = m_IRM.GetResObj<CIFStatic>(GDR_MSB_BLESS_8 , 1);
    GDR_MSB_BLESS_71 = m_IRM.GetResObj<CIFStatic>(GDR_MSB_BLESS_7 , 1);
    GDR_MSB_BLESS_61 = m_IRM.GetResObj<CIFStatic>(GDR_MSB_BLESS_6 , 1);
    GDR_MSB_BLESS_51 = m_IRM.GetResObj<CIFStatic>(GDR_MSB_BLESS_5 , 1);
    GDR_MSB_BLESS_41 = m_IRM.GetResObj<CIFStatic>(GDR_MSB_BLESS_4 , 1);
    GDR_MSB_BLESS_31 = m_IRM.GetResObj<CIFStatic>(GDR_MSB_BLESS_3 , 1);
    GDR_MSB_BLESS_21 = m_IRM.GetResObj<CIFStatic>(GDR_MSB_BLESS_2 , 1);
    GDR_MSB_BLESS_11 = m_IRM.GetResObj<CIFStatic>(GDR_MSB_BLESS_1 , 1);

    GDR_MSB_CURSE_GAUGE_91 = m_IRM.GetResObj<CIFGauge>(GDR_MSB_CURSE_GAUGE_9, 1);
    GDR_MSB_CURSE_GAUGE_81 = m_IRM.GetResObj<CIFGauge>(GDR_MSB_CURSE_GAUGE_8, 1);
    GDR_MSB_CURSE_GAUGE_71 = m_IRM.GetResObj<CIFGauge>(GDR_MSB_CURSE_GAUGE_7, 1);
    GDR_MSB_CURSE_GAUGE_61 = m_IRM.GetResObj<CIFGauge>(GDR_MSB_CURSE_GAUGE_6, 1);
    GDR_MSB_CURSE_GAUGE_51 = m_IRM.GetResObj<CIFGauge>(GDR_MSB_CURSE_GAUGE_5, 1);
    GDR_MSB_CURSE_GAUGE_41 = m_IRM.GetResObj<CIFGauge>(GDR_MSB_CURSE_GAUGE_4, 1);
    GDR_MSB_CURSE_GAUGE_31 = m_IRM.GetResObj<CIFGauge>(GDR_MSB_CURSE_GAUGE_3, 1);
    GDR_MSB_CURSE_GAUGE_21 = m_IRM.GetResObj<CIFGauge>(GDR_MSB_CURSE_GAUGE_2, 1);
    GDR_MSB_CURSE_GAUGE_11 = m_IRM.GetResObj<CIFGauge>(GDR_MSB_CURSE_GAUGE_1, 1);



    GDR_MSB_BLESS_GAUGE_91 = m_IRM.GetResObj<CIFGauge>(GDR_MSB_BLESS_GAUGE_9, 1);
    GDR_MSB_BLESS_GAUGE_81 = m_IRM.GetResObj<CIFGauge>(GDR_MSB_BLESS_GAUGE_8, 1);
    GDR_MSB_BLESS_GAUGE_71 = m_IRM.GetResObj<CIFGauge>(GDR_MSB_BLESS_GAUGE_7, 1);
    GDR_MSB_BLESS_GAUGE_61 = m_IRM.GetResObj<CIFGauge>(GDR_MSB_BLESS_GAUGE_6, 1);
    GDR_MSB_BLESS_GAUGE_51 = m_IRM.GetResObj<CIFGauge>(GDR_MSB_BLESS_GAUGE_5, 1);
    GDR_MSB_BLESS_GAUGE_41 = m_IRM.GetResObj<CIFGauge>(GDR_MSB_BLESS_GAUGE_4, 1);
    GDR_MSB_BLESS_GAUGE_31 = m_IRM.GetResObj<CIFGauge>(GDR_MSB_BLESS_GAUGE_3, 1);
    GDR_MSB_BLESS_GAUGE_21 = m_IRM.GetResObj<CIFGauge>(GDR_MSB_BLESS_GAUGE_2, 1);
    GDR_MSB_BLESS_GAUGE_11 = m_IRM.GetResObj<CIFGauge>(GDR_MSB_BLESS_GAUGE_1, 1);


    //
    GDR_MSB_CURSE_91->ShowGWnd(false);
    GDR_MSB_CURSE_81->ShowGWnd(false);
    GDR_MSB_CURSE_71->ShowGWnd(false);
    GDR_MSB_CURSE_61->ShowGWnd(false);
    GDR_MSB_CURSE_51->ShowGWnd(false);
    GDR_MSB_CURSE_41->ShowGWnd(false);
    GDR_MSB_CURSE_31->ShowGWnd(false);
    GDR_MSB_CURSE_21->ShowGWnd(false);
    GDR_MSB_CURSE_11->ShowGWnd(false);

    GDR_MSB_BLESS_91->ShowGWnd(false);
    GDR_MSB_BLESS_81->ShowGWnd(false);
    GDR_MSB_BLESS_71->ShowGWnd(false);
    GDR_MSB_BLESS_61->ShowGWnd(false);
    GDR_MSB_BLESS_51->ShowGWnd(false);
    GDR_MSB_BLESS_41->ShowGWnd(false);
    GDR_MSB_BLESS_31->ShowGWnd(false);
    GDR_MSB_BLESS_21->ShowGWnd(false);
    GDR_MSB_BLESS_11->ShowGWnd(false);

    GDR_MSB_CURSE_GAUGE_91->ShowGWnd(false);
    GDR_MSB_CURSE_GAUGE_81 ->ShowGWnd(false);
    GDR_MSB_CURSE_GAUGE_71->ShowGWnd(false);
    GDR_MSB_CURSE_GAUGE_61->ShowGWnd(false);
    GDR_MSB_CURSE_GAUGE_51 ->ShowGWnd(false);
    GDR_MSB_CURSE_GAUGE_41 ->ShowGWnd(false);
    GDR_MSB_CURSE_GAUGE_31 ->ShowGWnd(false);
    GDR_MSB_CURSE_GAUGE_21->ShowGWnd(false);
    GDR_MSB_CURSE_GAUGE_11 ->ShowGWnd(false);



    GDR_MSB_BLESS_GAUGE_91->ShowGWnd(false);
    GDR_MSB_BLESS_GAUGE_81->ShowGWnd(false);
    GDR_MSB_BLESS_GAUGE_71->ShowGWnd(false);
    GDR_MSB_BLESS_GAUGE_61 ->ShowGWnd(false);
    GDR_MSB_BLESS_GAUGE_51->ShowGWnd(false);
    GDR_MSB_BLESS_GAUGE_41->ShowGWnd(false);
    GDR_MSB_BLESS_GAUGE_31->ShowGWnd(false);
    GDR_MSB_BLESS_GAUGE_21->ShowGWnd(false);
    GDR_MSB_BLESS_GAUGE_11->ShowGWnd(false);


    this->ShowGWnd(true);
    return true;
}
