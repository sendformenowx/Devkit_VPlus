#pragma once

#include <string>
#include <BSLib/BSLib.h>

class CTextStringManager {
public:
    //void ReadTranslationFile(char *filename, int lang, IFileManager *fm, int a5, int a6);
    //void sub_8CA8F0(const char * file, IFileManager *fm);

    /// Get translated string by identifier-token
    /// \address 008C9C30
    /// \param identifier Identifier for the string to translate. Example: "UIIT_STT_CANT_CHATTING"
    /// \returns The translated string
    const std::n_wstring *GetString(const wchar_t *identifier);


    /// \address 008c9bb0
    const std::n_wstring &FUN_008c9bb0(const std::n_wstring &identifier);

    std::wstring *GetStringByNameStrID(std::wstring *NameStrID);

    std::wstring *GetStringTextByCode(const wchar_t *code);

    void OnUniqueNameRetrieve(std::wstring* NameStrID);
    void CALL(std::wstring * NameStrID);
};

#define g_CTextStringManager ((CTextStringManager*)0x00EEDE90)

#define TSM_GETTEXTPTR(text) (g_CTextStringManager->GetString(text)->c_str())
#define TSM_GETTEXT(text) (g_CTextStringManager->GetString(text))
