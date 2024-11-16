#include "IFEventTimeSlot.h"
#include <ClientNet\MsgStreamBuffer.h>

#define EVENTNAME 11
#define DAYS 12
#define EVENTTIME 13


GFX_IMPLEMENT_DYNCREATE(CIFEventTimeSlot, CIFWnd)
GFX_BEGIN_MESSAGE_MAP(CIFEventTimeSlot, CIFWnd)
GFX_END_MESSAGE_MAP()


bool CIFEventTimeSlot::OnCreate(long ln)
{
    // Populate inherited members
    CIFWnd::OnCreate(ln);


    RECT eventrect = { 2,5,129,13 };
    RECT dayrect = { 134,5,84,13 };
    RECT timerect = { 224,5,84,13 };

    m_custom_label1 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), eventrect, EVENTNAME, 0);
    m_custom_label2 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), dayrect, DAYS, 0);
    m_custom_label3 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), timerect, EVENTTIME, 0);
    m_custom_label4 = (CIFStatic*)CGWnd::CreateInstance(this, GFX_RUNTIME_CLASS(CIFStatic), timerect, EVENTTIME, 0);

    m_custom_label1->m_FontTexture.SetColor(0xffffff);
    m_custom_label2->m_FontTexture.SetColor(0xffffff);
    m_custom_label3->m_FontTexture.SetColor(0xffffff);
    m_custom_label4->ShowGWnd(false);
    this->ShowGWnd(false);
    m_custom_label4->ShowGWnd(false);
    return true;
}

void CIFEventTimeSlot::WriteLine(const wchar_t * test, const wchar_t* EventName, const wchar_t* DAY, const wchar_t* Time)
{
    m_custom_label1->SetText(EventName);
    m_custom_label2->SetText(DAY);
    m_custom_label3->SetText(Time);
    m_custom_label4->SetText(test);

}
