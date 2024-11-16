#include <vector>
#include <string>
#include <sstream>
#include "CStringHelper.h"


std::vector<std::wstring> CStringHelper::wsplit(const std::wstring &InputString, wchar_t delimiterChar) {
    std::vector<std::wstring> ResultVec;
    std::wstringstream sStream(InputString);
    std::wstring item;

    while (std::getline(sStream, item, delimiterChar)) {
        ResultVec.push_back(item);
    }
    return ResultVec;
};