#include "IFSpinButton.h"
#include "GlobalHelpersThatHaveNoHomeYet.h"
#include "IFUniqueLog.h"
#include "IFRank.h"
#include "IFEventTime.h"
#include "IFMainMenu.h"
#include "IFChest.h"
#define GDR_SPIN_BTN_NEXT 2
#define GDR_SPIN_BTN_PREV 1
#define GDR_SPIN_TEXT_PAGE 0

GFX_IMPLEMENT_DYNCREATE(CIFSpinControl, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFSpinControl, CIFWnd)
                    ONG_COMMAND(GDR_SPIN_BTN_NEXT, &CIFSpinControl::OnNext)
                    ONG_COMMAND(GDR_SPIN_BTN_PREV, &CIFSpinControl::OnPrev)
GFX_END_MESSAGE_MAP()

CIFSpinControl::CIFSpinControl() :
        m_buttonPrev(0),
        m_buttonNext(0),
        m_text(0),
        m_valueCurrent(1),
        m_valueMin(1),
        m_valueMax(1) {
//#ifdef CONFIG_SPINBUTTONCTRL_DEBUG
//    printf("%s\n", __FUNCTION__);
//#endif
}

void CIFSpinControl::UpdateText() {
#ifdef CONFIG_SPINBUTTONCTRL_DEBUG
    printf("%s\n", __FUNCTION__);
#endif

    wchar_t buf[8];
    swprintf_s(buf, L"%d", m_valueCurrent);

    m_text->SetText(buf);

}

CIFSpinControl::~CIFSpinControl(void)
{
}

void CIFSpinControl::SetMaxValue(int value) {
#ifdef CONFIG_SPINBUTTONCTRL_DEBUG
    printf("%s(%d)\n", __FUNCTION__, value);
#endif
    m_valueMax = value;
}

int CIFSpinControl::GetMaxValue() const {
    return m_valueMax;
}

void CIFSpinControl::SetMinValue(int value) {
#ifdef CONFIG_SPINBUTTONCTRL_DEBUG
    printf("%s(%d)\n", __FUNCTION__, value);
#endif
    m_valueMin = value;
}

int CIFSpinControl::GetMinValue() const {
    return m_valueMin;
}

void CIFSpinControl::SetCurrentValue(int value) {
#ifdef CONFIG_SPINBUTTONCTRL_DEBUG
    printf("%s(%d)\n", __FUNCTION__, value);
#endif
    m_valueCurrent = value;
    UpdateText();
}

int CIFSpinControl::GetCurrentValue() const {
    return m_valueCurrent;
}

bool CIFSpinControl::OnCreate(long ln) {
#ifdef CONFIG_SPINBUTTONCTRL_DEBUG
    printf("%s(%d)\n", __FUNCTION__, ln);
#endif

    //m_IRM.LoadFromFile("resinfo\\ifspincontrol.txt");
    //m_IRM.CreateInterfaceSection("Create", this);

    RECT labrect = { 16,4,18,12 };
    RECT Butt1rect = { 0,0,16,16 };
    RECT Butt2rect = { 34,0,16,16 };

    m_text = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), labrect, GDR_SPIN_TEXT_PAGE, 0);
    m_buttonPrev = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Butt1rect, GDR_SPIN_BTN_PREV, 0);
    m_buttonNext = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), Butt2rect, GDR_SPIN_BTN_NEXT, 0);

    m_buttonPrev->TB_Func_13("interface\\ifcommon\\com_left_arrow.ddj", 0, 0);
    m_buttonNext->TB_Func_13("interface\\ifcommon\\com_right_arrow.ddj", 0, 0);

    TB_Func_13("interface\\store\\str_slot_02.ddj", 0, 0);

    UpdateText();

    m_uniquelogpage = 1;
    m_Ranklogpage = 1;
    m_EventPage = 1;
    m_ChestPage = 1;
    this->ShowGWnd(false);
    return true;
}


void CIFSpinControl::OnPrev() {
#ifdef CONFIG_SPINBUTTONCTRL_DEBUG
    printf("%s\n", __FUNCTION__);
#endif

    if (m_valueMin >= m_valueCurrent)
        return;

    if (m_valueCurrent < m_valueMin)
        return;

    m_valueCurrent--;



    //now its yours
    //printf("UQ ID %d\n", this->GetParentControl()->UniqueID());

    switch (this->GetParentControl()->UniqueID())
    {
        case UniqueIDW:
        {
            m_uniquelogpage--;
            if (m_uniquelogpage > 0)
            {
                m_valueCurrent = m_uniquelogpage;
                CIFMainMenu::UniqueW->ShowList(m_uniquelogpage);
            }
            else
            {
                m_uniquelogpage = 1;
                m_valueCurrent = 1;
                return;
            }
        }
            break;
        case EventIDW:
        {
            m_EventPage--;
            if (m_EventPage > 0)
            {
                m_valueCurrent = m_EventPage;
                CIFMainMenu::EventW->ShowList(m_EventPage);
            }
            else
            {
                m_EventPage = 1;
                m_valueCurrent = 1;
                return;
            }
        }
            break;
        case RankID:
        {
            m_Ranklogpage--;
            if (m_Ranklogpage > 0)
            {
                m_valueCurrent = m_Ranklogpage;
                CIFMainMenu::RankW->ShowList(m_Ranklogpage);
            }
            else
            {
                m_Ranklogpage = 1;
                m_valueCurrent = 1;
                return;
            }
        }
            break;
        case ChestID:
        {
            m_ChestPage--;
            if (m_ChestPage > 0)
            {
                m_valueCurrent = m_ChestPage;
                CIFPlayerChest::ChestW->ShowList(m_ChestPage);
            }
            else
            {
                m_ChestPage = 1;
                m_valueCurrent = 1;
                return;
            }
        }
            break;
    }
    UpdateText();

    g_CurrentIfUnderCursor = 0;
}

void CIFSpinControl::OnNext() {
#ifdef CONFIG_SPINBUTTONCTRL_DEBUG
    printf("%s\n", __FUNCTION__);
#endif

    if (m_valueCurrent > m_valueMax)
        return;

    m_valueCurrent++;
    switch (this->GetParentControl()->UniqueID())
    {
        case UniqueIDW:
        {
            if (CIFMainMenu::UniqueW->IsPageFull(m_uniquelogpage, 39))
            {
                m_uniquelogpage++;

                if (CIFMainMenu::UniqueW->IsPageFull(m_uniquelogpage, 30))
                {
                    m_valueCurrent = m_uniquelogpage;
                    CIFMainMenu::UniqueW->ShowList(m_uniquelogpage);
                }
                else
                {
                    m_valueCurrent = m_uniquelogpage - 1;
                    m_uniquelogpage = m_valueCurrent;
                }
            }
            else
            {
                return;
            }
        }
            break;
        case EventIDW:
        {
            if (CIFMainMenu::EventW->IsPageFull(m_EventPage, 39))
            {
                m_EventPage++;

                if (CIFMainMenu::EventW->IsPageFull(m_EventPage, 30))
                {
                    m_valueCurrent = m_EventPage;
                    CIFMainMenu::EventW->ShowList(m_EventPage);
                }
                else
                {
                    m_valueCurrent = m_EventPage - 1;
                    m_EventPage = m_valueCurrent;
                }
            }
            else
            {
                return;
            }
        }
            break;
        case RankID:
        {
            if (CIFMainMenu::RankW->IsPageFull(m_Ranklogpage, 39))
            {
                m_Ranklogpage++;

                if (CIFMainMenu::RankW->IsPageFull(m_Ranklogpage, 30))
                {
                    m_valueCurrent = m_Ranklogpage;
                    CIFMainMenu::RankW->ShowList(m_Ranklogpage);
                }
                else
                {
                    m_valueCurrent = m_Ranklogpage - 1;
                    m_Ranklogpage = m_valueCurrent;
                }
            }
            else
            {
                return;
            }
        }
            break;
        case ChestID:
        {
            if (CIFPlayerChest::ChestW->IsPageFull(m_ChestPage, 39))
            {
                m_ChestPage++;

                if (CIFPlayerChest::ChestW->IsPageFull(m_ChestPage, 30))
                {
                    m_valueCurrent = m_ChestPage;
                    CIFPlayerChest::ChestW->ShowList(m_ChestPage);
                }
                else
                {
                    m_valueCurrent = m_ChestPage - 1;
                    m_ChestPage = m_valueCurrent;
                }
            }
            else
            {
                return;
            }
        }
            break;
    }

    UpdateText();
    // g_CurrentIfUnderCursor = 0;
}
