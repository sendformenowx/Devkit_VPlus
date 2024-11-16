#include "ICPlayer.h"
#include "GlobalDataManager.h"
#include "GInterface.h"
#include "CharacterDependentData.h"
#include "../../../third-party/memory/include/memory/hook.h"

GFX_IMPLEMENT_DYNAMIC_EXISTING(CICPlayer, 0x00ef1b44)

std::map<std::wstring, unsigned __int32> CICPlayer::m_LeftCharIcons;
std::map<int, void*> CICPlayer::m_LeftIconsData;

std::map<std::wstring, unsigned __int32> CICPlayer::m_RightCharIcons;
std::map<int, void*> CICPlayer::m_RightIconsData;
std::map<std::wstring, unsigned __int32> CICPlayer::m_UpCharIcons;
std::map<int, void*> CICPlayer::m_UpIconsData;

std::map<std::wstring, unsigned __int32> CICPlayer::m_NameColors;


std::map<int, int> CICPlayer::UniqueTargetHashmap;
std::map<int, int> CICPlayer::UniqueTargetHashmapPlayer;



std::map<std::wstring, std::wstring> CICPlayer::NewTitles;
std::map<std::wstring, unsigned __int32> CICPlayer::TitleColors;
std::map<std::wstring, std::wstring> CICPlayer::NewCostomTitle;
std::map<std::wstring, std::wstring> CICPlayer::NewisroTitle;

std::map<unsigned __int32, int> CICPlayer::EventSuit;

std::map<unsigned __int16, int> CICPlayer::SuitRegions;


wchar_t buffer[255];
std::n_wstring mymsg;


// CICPlayer::IsGameMasterMAYBE(void) .text 009D4C40 00000009   R . . . . T .
bool CICPlayer::IsGameMaster() {
    return N000094A7 & 1;
}

// sub_9D6580 .text 009D6580 00000032 00000008 00000004 R . . . . T .
// I am pretty sure this func simply returned a copy of the players name ... ridiculous!
std::n_wstring *CICPlayer::sub_9D6580(std::n_wstring *str) {
    return reinterpret_cast<std::n_wstring*(__thiscall*)(CICPlayer*, std::n_wstring*)>(0x9D6580)(this, str);
}

std::n_wstring CICPlayer::GetCharName() const {
    return m_charname;
}

void CICPlayer::Render()
{
    CLASSLINK_LOOP_BEGIN(CICUser)

    std::map<std::wstring, unsigned __int32>::iterator colordata = g_pCICPlayer->TitleColors.find(obj->GetName().c_str());
    if (colordata != TitleColors.end())
    {
        obj->ChangeTitleColor(colordata->second);
    }

    std::map<std::wstring, std::wstring>::iterator titledata = g_pCICPlayer->NewTitles.find(obj->GetName().c_str());
    if (titledata != NewTitles.end())
    {
        swprintf_s(buffer, sizeof(buffer), L"<%s> %s", titledata->second.c_str(), obj->GetName().c_str());
        mymsg.assign(buffer);
        obj->ChangeName(mymsg);
    }
    std::map<std::wstring, std::wstring>::iterator CostomTitle = g_pCICPlayer->NewCostomTitle.find(obj->GetName().c_str());
    if (CostomTitle != NewCostomTitle.end())
    {
        swprintf_s(buffer, sizeof(buffer), L"%s", CostomTitle->second.c_str());
        mymsg.assign(buffer);
        obj->ChangeTitle(mymsg);
    }

    CLASSLINK_LOOP_END(CICUser)

        CLASSLINK_LOOP_BEGIN(CICharactor)
        //for (std::map<unsigned __int16, int>::iterator RegionID = SuitRegions.begin(); RegionID != SuitRegions.end(); ++RegionID)
        //{
        std::map<unsigned __int16, int>::iterator RegionID = g_pCICPlayer->SuitRegions.find(GetRegion().r);
            if (RegionID != SuitRegions.end())
            {
                if (obj->GetCaracterinfo())
                {
                    std::map<unsigned __int32, int>::iterator test = EventSuit.find(obj->GetUniqueID());
                    if (test == EventSuit.end())
                    {
                        //printf("%ls vvvv \n", obj->GetName().c_str());
                        EventSuit.insert(std::pair<__int32, int>(obj->GetUniqueID(), 1));

                        obj->m_pCCObjAnimation->SetOptimizeCloth(4);
                        obj->m_pCCObjAnimation->SetClothesApply();
                    }
                }
            }

            else
                EventSuit.clear();
    CLASSLINK_LOOP_END(CICharactor)

    reinterpret_cast<void(__thiscall*)(CICPlayer*)>(0x009D87C0)(this); //Render
}



CICPlayer* CICPlayer::GetCICPlayerByUniqueID(DWORD UniqueID)
{
    return reinterpret_cast<CICPlayer*(__cdecl*)(DWORD)>(0x009C3220)(UniqueID);
}

DWORD CICPlayer::GetObjEffect() /// 009cf990 DWORD PTR
{//Does this gets the proper NEEDED effect or it might be getting another effect? well, its the proper addr of the effect of the whole objects in sro, and i got it from makeeffect function so xD
    return *(DWORD*)((0x009CF960) + 0x754);

}

void CICPlayer::MakeEffect(unsigned __int32 effectID)
{
    reinterpret_cast<void* (__thiscall*)(CICPlayer*, unsigned __int32)>(0x009CF960)(this, effectID);
}

void CICPlayer::RemoveEffect(unsigned __int32 effectID)
{
    reinterpret_cast<void* (__thiscall*)(CICPlayer*, unsigned __int32)>(0x009CD2B0)(this, effectID);
}


void CICPlayer::RemoveExistingUniqueData(const DWORD dead_object)
{
    if (g_pCICPlayer)
    {
        bool remove_key_player = false;
        bool remove_key_unique = false;
        unsigned __int32 remove_val_key = 0;

        std::map<int, int>::iterator it_1 = g_pCICPlayer->UniqueTargetHashmapPlayer.find(dead_object);
        if (it_1 != g_pCICPlayer->UniqueTargetHashmapPlayer.end()) //player gitti, player map'ten playerı sil, unique map'ten value 0 yap.
        {
            remove_key_player = true;
            remove_val_key = it_1->second;
        }

        if (!remove_key_player) //player değil ise bak
        {
            std::map<int, int>::iterator it_2 = g_pCICPlayer->UniqueTargetHashmap.find(dead_object);
            if (it_2 != g_pCICPlayer->UniqueTargetHashmap.end()) //unique gitti, player mapten unique'i 0 yap, unique map'ten unique'i sil.
            {
                remove_key_unique = true;
                remove_val_key = it_2->first;

                CICPlayer* LastTarget = g_pCICPlayer->GetCICPlayerByUniqueID(it_2->second);
                if (LastTarget)
                {
                    LastTarget->RemoveEffect(g_CGlobalDataManager->GetEffectIdByName(L"SYSTEM_AGGRO_EFFECT"));
                }
            }
        }
        else //player gitmiş
        {
            g_pCICPlayer->UniqueTargetHashmapPlayer.erase(remove_val_key);

            if (g_pCICPlayer->UniqueTargetHashmap.count(remove_val_key) > 0)
                g_pCICPlayer->UniqueTargetHashmap[remove_val_key] = 0;

            return;
        }

        if (remove_key_unique)
        {
            g_pCICPlayer->UniqueTargetHashmap.erase(remove_val_key);

            if (g_pCICPlayer->UniqueTargetHashmapPlayer.count(remove_val_key) > 0)
                g_pCICPlayer->UniqueTargetHashmapPlayer[remove_val_key] = 0;
        }
    }
}



undefined4 CICPlayer::FUN_009d68f0() {
    return reinterpret_cast<undefined4 (__thiscall *)(const CICPlayer*)>(0x009d68f0)(this);
}

int CICPlayer::GetWorldID()
{
    return reinterpret_cast<int(__thiscall*)(CICPlayer*)>(0x009D4D90)(this) % 65536;
}

unsigned char CICPlayer::GetCurrentLevel() const {
    return m_level;
}

long long int CICPlayer::GetCurrentExp() const {
    return m_exp_current;
}

short CICPlayer::GetStatPointAvailable() const {
    return m_statpoint_available;
}

short CICPlayer::GetStrength() const {
    return m_str_stat;
}

short CICPlayer::GetIntelligence() const {
    return m_int_stat;
}

const std::n_wstring &CICPlayer::GetJobAlias() const {
    return m_jobAlias;
}

const std::n_wstring &CICPlayer::GetTitleName() const
{
    return m_titleText;
}

int CICPlayer::GetCurrentJobExperiencePoints() const {
    return reinterpret_cast<int (__thiscall *)(const CICPlayer *)>(0x009d4d20)(this);
}

void CICPlayer::UpdateNameColor(unsigned __int32 Color)
{
    if (GetJobType() == 4 &&  !g_CCharacterDependentData.IsInParty())
    {
        for (std::map<std::wstring, unsigned __int32>::iterator Player = m_NameColors.begin(); Player != m_NameColors.end(); ++Player)
        {
            if (this->GetName().c_str() == Player->first)
            {
                reinterpret_cast<void(__thiscall*)(CICPlayer*, unsigned __int32)>(0x009C1920)(this, Player->second);
                break;
            }
        }
    }
    else
        reinterpret_cast<void(__thiscall*)(CICPlayer*, unsigned __int32)>(0x009C1920)(this, Color);
}



void CICPlayer::Func_15(int param_1, float *param_2) {
    //reinterpret_cast<void (__thiscall *)(const CICharactor *, int param_1, float *param_2)>(0x009d49c0)(this, param_1, param_2);
    if ((param_1 == 3) && (g_pCGInterface != NULL)) {
        g_pCGInterface->FUN_00777a70(0,1);
    }
    CICUser::Func_15(param_1,param_2);
}

void CICPlayer::Func_15_impl(int param_1, float *param_2) {
    CICPlayer::Func_15(param_1, param_2);
}


BYTE CICPlayer::GetSlotCount()
{
    return  MEMUTIL_READ_BY_PTR_OFFSET(this, 0x2048, BYTE);
    //return *(BYTE*)(this + 0x2048);
}