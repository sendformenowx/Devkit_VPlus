#pragma once

#include "ICUser.h"
#include "SOItem.h"

class CICPlayer : public CICUser {
    GFX_DECLARE_DYNAMIC_EXISTING(CICPlayer, 0x00ef1b44)
public:

    bool IsGameMaster();
    static std::map<int, int> UniqueTargetHashmap;
    static std::map<int, int> UniqueTargetHashmapPlayer;
    static std::map<std::wstring, unsigned __int32> m_LeftCharIcons;
    static std::map<int, void*> m_LeftIconsData;

    static std::map<std::wstring, unsigned __int32> m_RightCharIcons;
    static std::map<int, void*> m_RightIconsData;



    static std::map<std::wstring, unsigned __int32> m_UpCharIcons;
    static std::map<int, void*> m_UpIconsData;

    static std::map<std::wstring, std::wstring> NewTitles;
    static std::map<std::wstring, std::wstring> NewCostomTitle;
    static std::map<std::wstring, std::wstring> NewisroTitle;
    static std::map<std::wstring, unsigned __int32> m_NameColors;
    static std::map<std::wstring, unsigned __int32> TitleColors;


    static std::map<unsigned __int32, int> CICPlayer::EventSuit;

    static std::map<unsigned __int16, int> SuitRegions;
    std::n_wstring *sub_9D6580(std::n_wstring *str);

    /// \address 009d49c0
    void Func_15(int param_1, float *param_2) override;
    void Func_15_impl(int param_1, float *param_2);


    /// \address 009d6580
    std::n_wstring GetCharName() const;
    BYTE GetSlotCount();

    void UpdateNameColor(unsigned __int32 Color);


    CICPlayer* GetCICPlayerByUniqueID(DWORD UniqueID);
    DWORD GetObjEffect();
    void MakeEffect(unsigned __int32 effectID);
    void RemoveEffect(unsigned __int32 effectID);
    void RemoveExistingUniqueData(const DWORD dead_object);

    /// \address 009d68f0
    undefined4 FUN_009d68f0();
    unsigned char GetCurrentLevel() const;

    long long int GetCurrentExp() const;

    short GetStatPointAvailable() const;

    short GetStrength() const;

    short GetIntelligence() const;

    /// \address 009d65c0
    /// \remark Optimized to return const reference instead of object
    const std::n_wstring &GetJobAlias() const;
    const std::n_wstring &GetTitleName() const;

    /// \address 009d4d20
    int GetCurrentJobExperiencePoints() const;
    int GetWorldID();
    void Render();
public:
    char pad_082C[32]; //0x082C
    std::n_wstring m_charname; //0x084C
public:
    unsigned char m_level; //0x0868 level of your character, crashes when set too high
private:
    char pad_0869[7]; //0x0869
public:
    long long int m_exp_current; //0x0870
    int m_skillpoint_progress; //0x0878
private:
    short m_str_stat; //0x087C
    short m_int_stat; //0x087E
public:
    int m_skillpoint; //0x0880
private:
    short m_statpoint_available; //0x0884
    char pad_0886[26]; //0x0886
    CSOItem N0000947A; //0x08A0
    CSOItem N0000947B; //0x0A70
    CSOItem N0000947C; //0x0C40
    CSOItem N0000947D; //0x0E10
    CSOItem N0000947E; //0x0FE0
    CSOItem N0000947F; //0x11B0
    CSOItem N00009480; //0x1380
    CSOItem N00009481; //0x1550
    CSOItem N00009482; //0x1720
    CSOItem N00009483; //0x18F0
    CSOItem N00009484; //0x1AC0
    CSOItem N00009485; //0x1C90
    CSOItem N00009486; //0x1E60
    char pad_2030[96]; //0x2030
    char N000094A7; //0x2090 bit 0 = isGameMaster
    char pad_2091[7]; //0x2091
    std::n_wstring m_jobAlias; // 0x2098
    char pad_20b4[100]; //0x20b4


    BEGIN_FIXTURE()
        ENSURE_SIZE(0x2118)

        ENSURE_OFFSET(m_charname, 0x084C)
        ENSURE_OFFSET(m_level, 0x0868)
        ENSURE_OFFSET(m_exp_current, 0x0870)
        ENSURE_OFFSET(m_skillpoint_progress, 0x0878)
        ENSURE_OFFSET(m_str_stat, 0x087C)
        ENSURE_OFFSET(m_int_stat, 0x087E)
        ENSURE_OFFSET(m_skillpoint, 0x0880)
        ENSURE_OFFSET(m_statpoint_available, 0x0884)
        ENSURE_OFFSET(m_jobAlias, 0x2098)
    END_FIXTURE()

    RUN_FIXTURE(CICPlayer)



};

#define g_pCICPlayer (*((CICPlayer**)0x00EEF5EC))
