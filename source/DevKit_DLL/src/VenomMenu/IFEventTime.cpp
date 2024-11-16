#include "IFEventTime.h"
#include "Game.h"

#define GDR_SPIN_BUTTON 4
#define GDR_EVENTS_BG 100
#define GDR_EVENTS_FRAME 101
#define GDR_EVENTS_BLACKSQUARE 102
#define GDR_EVENTS_LABEL_TIMER 103
#define GDR_EVENTS_LABEL 104

std::vector<CIFEventTime::EventSetting> CIFEventTime::EventList;

GFX_IMPLEMENT_DYNCREATE(CIFEventTime, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFEventTime, CIFMainFrame)
GFX_END_MESSAGE_MAP()


bool CIFEventTime::OnCreate(long ln)
{

    // Populate inherited members
    CIFMainFrame::OnCreate(ln);
    SetText(L"Event Schedule");
    TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);
    RECT lable4rect = { 151,267,50,16 };

    wnd_rect sz;
    sz.pos.x = 13;
    sz.pos.y =  42;
    sz.size.width = 320;
    sz.size.height = 248;
    tile = (CIFNormalTile*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFNormalTile), sz, GDR_EVENTS_BG, 0);
    tile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_b.ddj", 1, 1);


    sz.pos.x = 10;
    sz.pos.y =  36;
    sz.size.width = 331;
    sz.size.height = 258;
    Frame = (CIFFrame*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), sz, GDR_EVENTS_FRAME, 0);
    Frame->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 1);


    sz.pos.x= 21;
    sz.pos.y = 46;
    sz.size.width = 310;
    sz.size.height = 220;
    blacksquare = (CIFStretchWnd* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStretchWnd), sz, GDR_EVENTS_BLACKSQUARE, 0);
    blacksquare->SetEdgeTextures("interface\\ifcommon\\com_blacksquare_right_side.ddj", "interface\\ifcommon\\com_blacksquare_left_up.ddj",
                                 "interface\\ifcommon\\com_blacksquare_left_side.ddj", "interface\\ifcommon\\com_blacksquare_left_up.ddj");

    sz.pos.x = 22;
    sz.pos.y =  50;
    sz.size.width = 132;
    sz.size.height = 24;
    m_custom_label5 = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_EVENTS_LABEL, 0);
    m_custom_label5->TB_Func_13("interface\\guild\\gil_subj_button10.ddj", 1, 1);
    m_custom_label5->SetText(L"Name");



    sz.pos.x = 154;
    sz.pos.y =  50;
    sz.size.width = 88;
    sz.size.height = 24;
    m_custom_label6 = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_EVENTS_LABEL_TIMER, 0);
    m_custom_label6->TB_Func_13("interface\\guild\\gil_subj_button10.ddj", 1, 1);
    m_custom_label6->SetText(L"Day");



    sz.pos.x = 242;
    sz.pos.y =  50;
    sz.size.width = 90;
    sz.size.height = 24;
    m_custom_label7 = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, GDR_EVENTS_LABEL, 0);
    m_custom_label7->TB_Func_13("interface\\guild\\gil_subj_button10.ddj", 1, 1);
    m_custom_label7->SetText(L"Schedule");

    m_spin = (CIFSpinControl*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSpinControl), lable4rect, GDR_SPIN_BUTTON, 0);




    RECT rect = { 0,0,0,0 };
    Slot1 = (CIFEventTimeList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeList), rect, 40, 0);
    Slot2 = (CIFEventTimeList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeList), rect, 41, 0);
    Slot3 = (CIFEventTimeList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeList), rect, 42, 0);
    Slot4 = (CIFEventTimeList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFEventTimeList), rect, 43, 0);

    Slot1->ShowGWnd(true);
    Slot2->ShowGWnd(false);
    Slot3->ShowGWnd(false);
    Slot4->ShowGWnd(false);


    m_spin->SetMinValue(1);
    m_spin->SetCurrentValue(1);
    m_spin->SetMaxValue(4);
    m_spin->ShowGWnd(true);


    this->ShowGWnd(false);
    UpdateMenuSize();
    return true;
}
void CIFEventTime::UpdateMenuSize()
{
    const ClientResolutonData &res = CGame::GetClientDimensionStuff();
    MoveGWnd(((res.width - GetSize().width) - 400), GetPos().y);
    BringToFront();

}
void CIFEventTime::OnUpdate()
{
}

void CIFEventTime::On_BtnClick()
{

}

void CIFEventTime::HideLists()
{
    Slot1->ShowGWnd(false);
    Slot2->ShowGWnd(false);
    Slot3->ShowGWnd(false);
    Slot4->ShowGWnd(false);
}

void CIFEventTime::ShowList(BYTE listid)
{
    switch (listid)
    {
        case 1:
            HideLists();
            Slot1->ShowGWnd(true);
            break;
        case 2:
            HideLists();
            Slot2->ShowGWnd(true);
            break;
        case 3:
            HideLists();
            Slot3->ShowGWnd(true);
            break;
        case 4:
            HideLists();
            Slot4->ShowGWnd(true);
            break;
    }
}

bool CIFEventTime::EventListContains(const wchar_t* UqName)
{
    for (std::vector<CIFEventTime::EventSetting>::iterator it = CIFEventTime::EventList.begin(); it != CIFEventTime::EventList.end(); ++it)
        if (wcscmp((*it).EventName.c_str(), UqName) == 0)
            return true;
    return false;
}

void CIFEventTime::UpdateLog()
{
    for (std::vector<CIFEventTime::EventSetting>::iterator it = CIFEventTime::EventList.begin(); it != CIFEventTime::EventList.end(); ++it)
    {
        switch ((*it).LineNum)
        {
            case 1:
            {
                Slot1->Line1->WriteLine((*it).ID.c_str(), (*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 2:
            {
                Slot1->Line2->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 3:
            {
                Slot1->Line3->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 4:
            {
                Slot1->Line4->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 5:
            {
                Slot1->Line5->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 6:
            {
                Slot1->Line6->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 7:
            {
                Slot1->Line7->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 8:
            {
                Slot1->Line8->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 9:
            {
                Slot1->Line9->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 10:
            {
                Slot1->Line10->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 11:
            {
                Slot2->Line1->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 12:
            {
                Slot2->Line2->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 13:
            {
                Slot2->Line3->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 14:
            {
                Slot2->Line4->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 15:
            {
                Slot2->Line5->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 16:
            {
                Slot2->Line6->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 17:
            {
                Slot2->Line7->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 18:
            {
                Slot2->Line8->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 19:
            {
                Slot2->Line9->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 20:
            {
                Slot2->Line10->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 21:
            {
                Slot3->Line1->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 22:
            {
                Slot3->Line2->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 23:
            {
                Slot3->Line3->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 24:
            {
                Slot3->Line4->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 25:
            {
                Slot3->Line5->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 26:
            {
                Slot3->Line6->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 27:
            {
                Slot3->Line7->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 28:
            {
                Slot3->Line8->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 29:
            {
                Slot3->Line9->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 30:
            {
                Slot3->Line10->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 31:
            {
                Slot4->Line1->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 32:
            {
                Slot4->Line2->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 33:
            {
                Slot4->Line3->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 34:
            {
                Slot4->Line4->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 35:
            {
                Slot4->Line5->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 36:
            {
                Slot4->Line6->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 37:
            {
                Slot4->Line7->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 38:
            {
                Slot4->Line8->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 39:
            {
                Slot4->Line9->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
            case 40:
            {
                Slot4->Line10->WriteLine((*it).ID.c_str(),(*it).EventName.c_str(), (*it).Day.c_str(), (*it).Time.c_str());
            }
                break;
        }
    }
}

bool CIFEventTime::IsPageFull(BYTE PageID, BYTE LineID)
{
    bool full = false;
    if (PageID == 1)
    {
        if (LineID == 30)
        {
            if (Slot1->Line1->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (Slot1->Line10->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 2)
    {
        if (LineID == 30)
        {
            if (Slot2->Line1->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (Slot2->Line10->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 3)
    {
        if (LineID == 30)
        {
            if (Slot3->Line1->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (Slot3->Line10->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 4)
    {
        if (LineID == 30)
        {
            if (Slot4->Line1->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (Slot4->Line10->m_custom_label1->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }


    return full;
}