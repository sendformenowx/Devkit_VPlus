#include "IFUniqueLog.h"
#include "Game.h"

#define GDR_UNIQUE_NAME 22
#define GDR_UNIQUE_STATUS 24
#define GDR_UNIQUE_KILLER 23
#define TIMER_CHATBLOCK 230
#define GDR_UNIQUE_BG 5
#define GDR_UNIQUE_FRAME 3
#define GDR_UNIQUE_BLACKSQUARE 1
#define UNIQUE_REF_BUTON 50
GFX_IMPLEMENT_DYNCREATE(CIFUniqueLog, CIFMainFrame)
GFX_BEGIN_MESSAGE_MAP(CIFUniqueLog, CIFMainFrame)
                    ONG_COMMAND(UNIQUE_REF_BUTON, &On_BtnClick)
GFX_END_MESSAGE_MAP()

static int RefreshTimes = 0;

std::vector<CIFUniqueLog::UniqueLogstru> CIFUniqueLog::UQlist;


bool CIFUniqueLog::OnCreate(long ln)
{
    // Populate inherited members
    CIFMainFrame::OnCreate(ln);
    SetText(L"Unique History (F6)");
    TB_Func_13("interface\\frame\\mframe_wnd_", 0, 0);
    wnd_rect sz;


    sz.pos.x = 13;
    sz.pos.y = 42;
    sz.size.width = 360;
    sz.size.height = 265;
    tile = (CIFNormalTile*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFNormalTile), sz, GDR_UNIQUE_BG, 0);
    tile->TB_Func_13("interface\\ifcommon\\bg_tile\\com_bg_tile_b.ddj", 1, 1);



    sz.pos.x = 8;
    sz.pos.y = 37;
    sz.size.width = 370;
    sz.size.height = 275;
    frame = (CIFFrame*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFFrame), sz, GDR_UNIQUE_FRAME, 1);
    frame->TB_Func_13("interface\\frame\\frameg_wnd_", 1, 1);



    sz.pos.x= 23;
    sz.pos.y = 50;
    sz.size.width = 343;
    sz.size.height = 218;
    blacksquare = (CIFStretchWnd* ) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStretchWnd), sz, GDR_UNIQUE_BLACKSQUARE, 0);
    blacksquare->SetEdgeTextures("interface\\ifcommon\\com_blacksquare_right_side.ddj", "interface\\ifcommon\\com_blacksquare_left_up.ddj",
                                 "interface\\ifcommon\\com_blacksquare_left_side.ddj", "interface\\ifcommon\\com_blacksquare_left_up.ddj");



    sz.pos.x= 24;
    sz.pos.y = 52;
    sz.size.width = 160;
    sz.size.height = 24;
    UniqueName = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_UNIQUE_NAME, 0);
    UniqueName->SetText(L"Uniques");
    UniqueName->TB_Func_13("interface\\ifcommon\\com_bar02_", 1, 1);

    sz.pos.x= 184;
    sz.pos.y = 52;
    sz.size.width = 110;
    sz.size.height = 24;
    Killer = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_UNIQUE_STATUS, 0);
    Killer->SetText(L"Killer");
    Killer->TB_Func_13("interface\\ifcommon\\com_bar02_", 1, 1);


    sz.pos.x= 294;
    sz.pos.y = 52;
    sz.size.width = 72;
    sz.size.height = 24;
    Status = (CIFBarWnd*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFBarWnd), sz, GDR_UNIQUE_KILLER, 0);
    Status->SetText(L"Status");
    Status->TB_Func_13("interface\\ifcommon\\com_bar02_", 1, 1);


    sz.pos.x = 169;
    sz.pos.y = 280;
    sz.size.width = 50;
    sz.size.height = 16;
    m_spin = (CIFSpinControl*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFSpinControl), sz,4, 0);


  /*  sz.pos.x = 281;
    sz.pos.y = 276;
    sz.size.width = 75;
    sz.size.height = 24;
    btn = (CIFButton*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFButton), sz, UNIQUE_REF_BUTON, 0);
    btn->TB_Func_13("interface\\system\\sys_button.ddj", 1, 1);
    btn->SetText(L"Refresh");
    */
    RECT rect = { 0,0,0,0 };
    m_slot1 = (CIFUniqueList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueList), rect, 40, 0);
    m_slot2 = (CIFUniqueList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueList), rect, 41, 0);
    m_slot3 = (CIFUniqueList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueList), rect, 42, 0);
    m_slot4 = (CIFUniqueList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueList), rect, 43, 0);
    m_slot5 = (CIFUniqueList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueList), rect, 44, 0);
    m_slot6 = (CIFUniqueList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueList), rect, 45, 0);
    m_slot7 = (CIFUniqueList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueList), rect, 46, 0);
    m_slot8 = (CIFUniqueList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueList), rect, 47, 0);
    m_slot9 = (CIFUniqueList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueList), rect, 48, 0);
    m_slot10 = (CIFUniqueList*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFUniqueList), rect, 49, 0);

    m_slot1->MoveGWnd(m_slot1->GetPos().x + 7, m_slot1->GetPos().y + 5);
    m_slot2->MoveGWnd(m_slot2->GetPos().x + 7, m_slot2->GetPos().y + 5);
    m_slot3->MoveGWnd(m_slot3->GetPos().x + 7, m_slot3->GetPos().y + 5);
    m_slot4->MoveGWnd(m_slot4->GetPos().x + 7, m_slot4->GetPos().y + 5);
    m_slot5->MoveGWnd(m_slot5->GetPos().x + 7, m_slot5->GetPos().y + 5);
    m_slot6->MoveGWnd(m_slot6->GetPos().x + 7, m_slot6->GetPos().y + 5);
    m_slot7->MoveGWnd(m_slot7->GetPos().x + 7, m_slot7->GetPos().y + 5);
    m_slot8->MoveGWnd(m_slot8->GetPos().x + 7, m_slot8->GetPos().y + 5);
    m_slot9->MoveGWnd(m_slot9->GetPos().x + 7, m_slot9->GetPos().y + 5);
    m_slot10->MoveGWnd(m_slot10->GetPos().x + 7, m_slot10->GetPos().y + 5);

    HideLists();
    m_slot1->ShowGWnd(true);
    m_spin->SetMinValue(1);
    m_spin->SetCurrentValue(1);
    m_spin->SetMaxValue(10);
    m_spin->ShowGWnd(true);

    //tests

    sz.pos.x= 25;
    sz.pos.y = 277;
    sz.size.width = 16;
    sz.size.height = 16;
    checkdps = (CIFCheckBox*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFCheckBox), sz, 200, 0);



    sz.pos.x= 62;
    sz.pos.y = 277;
    sz.size.width = 16;
    sz.size.height = 16;
    m_custom_label = (CIFStatic*) CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), sz, 201, 0);
    m_custom_label->SetText(L"Dps Meter");


    UpdateMenuSize();
    this->ShowGWnd(false);
    return true;
}
void CIFUniqueLog::OnUpdate()
{
}

bool CIFUniqueLog::IsGameChecked() const {
    return checkdps->GetCheckedState_MAYBE();
}

void CIFUniqueLog::UpdateMenuSize()
{
    const ClientResolutonData &res = CGame::GetClientDimensionStuff();
    MoveGWnd(((res.width - GetSize().width) - 400), GetPos().y);
    BringToFront();

}

//but show the sent id
void CIFUniqueLog::HideLists()
{
    m_slot1->ShowGWnd(false);
    m_slot2->ShowGWnd(false);
    m_slot3->ShowGWnd(false);
    m_slot4->ShowGWnd(false);
    m_slot5->ShowGWnd(false);
    m_slot6->ShowGWnd(false);
    m_slot7->ShowGWnd(false);
    m_slot8->ShowGWnd(false);
    m_slot9->ShowGWnd(false);
    m_slot10->ShowGWnd(false);
}

void CIFUniqueLog::ShowList(BYTE listid)
{
    switch (listid)
    {
        case 1:
            HideLists();
            m_slot1->ShowGWnd(true);
            break;
        case 2:
            HideLists();
            m_slot2->ShowGWnd(true);
            break;
        case 3:
            HideLists();
            m_slot3->ShowGWnd(true);
            break;
        case 4:
            HideLists();
            m_slot4->ShowGWnd(true);
            break;
        case 5:
            HideLists();
            m_slot5->ShowGWnd(true);
            break;
        case 6:
            HideLists();
            m_slot6->ShowGWnd(true);
            break;
        case 7:
            HideLists();
            m_slot7->ShowGWnd(true);
            break;
        case 8:
            HideLists();
            m_slot8->ShowGWnd(true);
            break;
        case 9:
            HideLists();
            m_slot9->ShowGWnd(true);
            break;
        case 10:
            HideLists();
            m_slot10->ShowGWnd(true);
            break;
    }
}

void CIFUniqueLog::On_BtnClick()
{
    CMsgStreamBuffer buf(0x9852);
    SendMsg(buf);
}


bool CIFUniqueLog::UqListContains(const wchar_t* UqName)
{
    for (std::vector<CIFUniqueLog::UniqueLogstru>::iterator it = CIFUniqueLog::UQlist.begin(); it != CIFUniqueLog::UQlist.end(); ++it)
        if (wcscmp((*it).UqName.c_str(), UqName) == 0)
            return true;
    return false;
}
void CIFUniqueLog::UpdateLog()
{
    int aa = 0;
    for (int i = 0; i < CIFUniqueLog::UQlist.size(); ++i)
    {
        aa = aa + 1;
        //std::wcout << L"Page " << UQlist[i].Pagenum << L" LineNum " << UQlist[i].LineNum << L" Uq " << UQlist[i].UqName.c_str() << L" life " << UQlist[i].LifeState.c_str() << L" Killer " << UQlist[i].Killer.c_str() << L" Time " << UQlist[i].Time.c_str() << std::endl;
        switch (aa)
        {
            case 1:
            {
                m_slot1->line1->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 2:
            {
                m_slot1->line2->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 3:
            {
                m_slot1->line3->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 4:
            {
                m_slot1->line4->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 5:
            {
                m_slot1->line5->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 6:
            {
                m_slot1->line6->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 7:
            {
                m_slot1->line7->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 8:
            {
                m_slot1->line8->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 9:
            {
                m_slot1->line9->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 10:
            {
                m_slot1->line10->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 11:
            {
                m_slot2->line1->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 12:
            {
                m_slot2->line2->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 13:
            {
                m_slot2->line3->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 14:
            {
                m_slot2->line4->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 15:
            {
                m_slot2->line5->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 16:
            {
                m_slot2->line6->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 17:
            {
                m_slot2->line7->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 18:
            {
                m_slot2->line8->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 19:
            {
                m_slot2->line9->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 20:
            {
                m_slot2->line10->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 21:
            {
                m_slot3->line1->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 22:
            {
                m_slot3->line2->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 23:
            {
                m_slot3->line3->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 24:
            {
                m_slot3->line4->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 25:
            {
                m_slot3->line5->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 26:
            {
                m_slot3->line6->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 27:
            {
                m_slot3->line7->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 28:
            {
                m_slot3->line8->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 29:
            {
                m_slot3->line9->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 30:
            {
                m_slot3->line10->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 31:
            {
                m_slot4->line1->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 32:
            {
                m_slot4->line2->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 33:
            {
                m_slot4->line3->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 34:
            {
                m_slot4->line4->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 35:
            {
                m_slot4->line5->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 36:
            {
                m_slot4->line6->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 37:
            {
                m_slot4->line7->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 38:
            {
                m_slot4->line8->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 39:
            {
                m_slot4->line9->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
            case 40:
            {
                m_slot4->line10->WriteLine(UQlist[i].UqName.c_str(), UQlist[i].LifeState.c_str(), UQlist[i].Killer.c_str());
            }
                break;
        }
    }
}
bool CIFUniqueLog::IsPageFull(BYTE PageID, BYTE LineID)
{
    bool full = false;
    if (PageID == 1)
    {
        if (LineID == 30)
        {
            if (m_slot1->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot1->line10->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 2)
    {
        if (LineID == 30)
        {
            if (m_slot2->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot2->line10->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 3)
    {
        if (LineID == 30)
        {
            if (m_slot3->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot3->line10->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 4)
    {
        if (LineID == 30)
        {
            if (m_slot4->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot4->line10->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 5)
    {
        if (LineID == 30)
        {
            if (m_slot5->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot5->line10->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 6)
    {
        if (LineID == 30)
        {
            if (m_slot6->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot6->line10->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 7)
    {
        if (LineID == 30)
        {
            if (m_slot7->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot7->line10->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 8)
    {
        if (LineID == 30)
        {
            if (m_slot8->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot8->line10->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 9)
    {
        if (LineID == 30)
        {
            if (m_slot9->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot9->line10->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }
    if (PageID == 10)
    {
        if (LineID == 30)
        {
            if (m_slot10->line1->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
        if (LineID == 39)
        {
            if (m_slot10->line10->m_custom_label2->GetNText().length() > 0)
                full = true;
            else
                full = false;
        }
    }

    return full;
}