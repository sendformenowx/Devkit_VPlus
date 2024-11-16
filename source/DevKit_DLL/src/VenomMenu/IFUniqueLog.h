#pragma once
#include "IFMainFrame.h"
#include "IFUniqueList.h"
#include "IFChatViewer.h"
#include "IFSpinButton.h"
#include <list>
#include <IFCheckBox.h>
#include "IFBarWnd.h"
#include "IFNormalTile.h"
#include "IFStretchWnd.h"


class CIFUniqueLog : public CIFMainFrame
{
GFX_DECLARE_DYNCREATE(CIFUniqueLog)
GFX_DECLARE_MESSAGE_MAP(CIFUniqueLog)

public:
    bool OnCreate(long ln) override;
    void OnUpdate() override;
    bool IsGameChecked() const;
    void UpdateMenuSize();
    void On_BtnClick();
    void HideLists();
    void ShowList(BYTE listid);
    static bool UqListContains(const wchar_t* UqName);
    void UpdateLog();
    bool IsPageFull(BYTE PageID, BYTE LineID);
    CIFSpinControl* m_spin;
public:
    static struct UniqueLogstru
    {
        std::wstring UqName;
        std::wstring LifeState;
        std::wstring Killer;
    };

    static std::vector<UniqueLogstru> UQlist;

    CIFUniqueList* m_slot1;
    CIFUniqueList* m_slot2;
    CIFUniqueList* m_slot3;
    CIFUniqueList* m_slot4;
    CIFUniqueList* m_slot5;
    CIFUniqueList* m_slot6;
    CIFUniqueList* m_slot7;
    CIFUniqueList* m_slot8;
    CIFUniqueList* m_slot9;
    CIFUniqueList* m_slot10;


    CIFStatic* m_custom_label;
    //CIFStretchWnd* m_custom_label2;
    CIFStatic* Count;
    CIFBarWnd* UniqueName;
    CIFBarWnd* Killer;
    CIFBarWnd* Status;
    CIFBarWnd* TimeLabel;
    CIFNormalTile* tile;
    CIFFrame* frame;
    CIFStretchWnd* blacksquare;
    CIFButton* btn;
    CIFCheckBox* checkdps;
};