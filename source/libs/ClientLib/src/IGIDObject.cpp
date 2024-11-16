#include "IGIDObject.h"

const std::n_wstring &CIGIDObject::GetName() const {
    return m_name;
}

unsigned __int32 CIGIDObject::GetUniqueID()
{
    return m_uniqueId;
}
void CIGIDObject::ChangeTitleColor(D3DCOLOR Color)
{
    fonttexture_title.SetColor(Color);
}

void CIGIDObject::ChangeTitle(std::n_wstring Title)
{
    fonttexture_title.sub_8B3B60(&Title);
}
void CIGIDObject::ChangeNameColor(D3DCOLOR Color)
{
    fonttexture_playername.SetColor(Color);
}

void CIGIDObject::ChangeName(std::n_wstring Name)
{
    fonttexture_playername.sub_8B3B60(&Name);
}

const CCharacterData::SData* CIGIDObject::GetSData() const {
    return m_characterData;
}

const int CIGIDObject::GetUniqueId() const {
    return m_uniqueId;
}

unsigned __int32 CIGIDObject::GetObj()
{
    return m_refObjID;
}


bool CIGIDObject::GetCaracterinfo()
{
    bool test = false;
    if (m_refObjID >= 1907 && m_refObjID <= 1932)
        test = true;

    if (m_refObjID >= 14875 && m_refObjID <= 14900)
        test = true;

    return test;
}