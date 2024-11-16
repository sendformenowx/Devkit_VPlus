#include "AlramGuideMgrWnd.h"

#include "IFConfirmReputationGuide.h"
#include "IFEventGuide.h"
#include "IFQuestInfoGuide.h"
#include "IFLetterAlarmGuide.h"
#include "IFServerEventGuide.h"
#include "IFOpenMarketAlramGuide.h"
#include "IFEventGuideSecond.h"
#include "GlobalHelpersThatHaveNoHomeYet.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFMainMenuGuide.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFChestGuide.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFDiscordGuide.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFFacebookGuide.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFEventMenuGuide.h"
#include "../../../DevKit_DLL/src/VenomMenu/IFAttendanceEvent.h"
#include <Game.h>
#include <GInterface.h>

GFX_IMPLEMENT_DYNAMIC_EXISTING(CAlramGuideMgrWnd, 0x00ee99a8)

#define GUIDE_CONFIRMREPUTATION 165
#define GUIDE_EVENT 41
#define GUIDE_QUESTINFO 46
#define GUIDE_LETTERALARM 55
#define GUIDE_SERVEREVENT  179
#define GUIDE_OPENMARKETALRAM  198
#define GUIDE_EVENTSECOND  30006

CAlramGuideMgrWnd::CAlramGuideMgrWnd() :
        m_numberOfIcons(0) {

}

CIFWnd *CAlramGuideMgrWnd::GetGuide(int windowId) {

    // Try to find the element in the list
    for (std::list<CIFWnd*>::iterator it = m_list.begin(); it != m_list.end(); ++it) {
        if ((*it)->UniqueID() == windowId) {
            return *it;
        }
    }

    // List did not contain the element, try to create it
    RECT rect = {0,0, 0x28,0x28};

    CIFWnd* pObj = 0;

    switch(windowId) {
        case GUIDE_CONFIRMREPUTATION:
            pObj = (CIFConfirmReputationGuide*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFConfirmReputationGuide), rect, GUIDE_CONFIRMREPUTATION, 0);
            break;

        case GUIDE_EVENT:
            pObj = (CIFEventGuide*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventGuide), rect, GUIDE_EVENT, 0);
            break;

        case GUIDE_QUESTINFO:
            pObj = (CIFQuestInfoGuide*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFQuestInfoGuide), rect, GUIDE_QUESTINFO, 0);
            break;

        case GUIDE_LETTERALARM:
            pObj = (CIFLetterAlarmGuide*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFLetterAlarmGuide), rect, GUIDE_LETTERALARM, 0);
            break;

        case GUIDE_SERVEREVENT:
            pObj = (CIFServerEventGuide*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFServerEventGuide), rect, GUIDE_SERVEREVENT, 0);
            break;

        case GUIDE_OPENMARKETALRAM:
            pObj = (CIFOpenMarketAlramGuide*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFOpenMarketAlramGuide), rect, GUIDE_OPENMARKETALRAM, 0);
            break;

        case GUIDE_EVENTSECOND:
            pObj = (CIFEventGuideSecond*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventGuideSecond), rect, GUIDE_EVENTSECOND, 0);
            break;

        case GUIDE_MAINMENU:
            pObj = (CIFMainMenuGuide*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFMainMenuGuide), rect, GUIDE_MAINMENU, 0);
            break;
        case GUIDE_CHEST:
            pObj = (CIFChestGuide*)CIFWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFChestGuide), rect, GUIDE_CHEST, 0);
            break;
        case GUIDE_FACEBOOK:
            pObj = (CIFFacebookGuide*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFacebookGuide), rect, GUIDE_FACEBOOK, 0);
            break;
        case GUIDE_DC:
            pObj = (CIFDiscordGuide*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFDiscordGuide), rect, GUIDE_DC, 0);
            break;
        case GUIDE_EVENTS:
            pObj = (CIFEventMenuGuide*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventMenuGuide), rect, GUIDE_EVENTS, 0);
            break;
        case GUIDE_ATTENDANCE:
            pObj = (CIFAttendanceEventGuide*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFAttendanceEventGuide), rect, GUIDE_ATTENDANCE, 0);
        default:

            assert(false);
    }

    m_list.push_back(pObj);
    m_numberOfIcons++;

    UpdatePositions();

    return pObj;
}

void CAlramGuideMgrWnd::UpdatePositions() {
    //reinterpret_cast<void(__thiscall*)(CAlramGuideMgrWnd*)>(0x0065c430)(this);
    //CGWndBase* pCGwndBase = NULL;
    //for (std::n_list<CGWndBase*>::const_iterator it = g_pCGInterface->N00000707.begin();
    //    it != g_pCGInterface->N00000707.end();
    //    ++it) {
    //    if ((*it)->UniqueID() == GUIDE_ATTENDANCE)
    //        pCGwndBase = *it;
    //}
    //if (pCGwndBase)
    //    pCGwndBase->ShowGWnd(!pCGwndBase->IsVisible());

    std::list<CIFWnd*>::iterator it = m_list.begin();
    int iconIndex = 1;
    int posy = 0;

    for (int i = 0; i < m_list.size(); ++i) {
        if (it != m_list.end())
        {

            (*it)->MoveGWnd(CLIENT_SCREEN_WIDTH - (43 * iconIndex), 230 + (44 * posy));

            if (iconIndex < 4)
                iconIndex = iconIndex + 1;

            else
            {
                iconIndex = 1;
                posy = posy + 1;
            }

            std::advance(it, 1);
        }
    }
}