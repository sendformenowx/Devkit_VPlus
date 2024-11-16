#ifndef Q_LIBRARY_GLOBAL_ITEM_LINKING_H
#define Q_LIBRARY_GLOBAL_ITEM_LINKING_H

#include <IFEdit.h>
#include "StdAfx.h"


struct GlobalChat
{
	int index;
	std::wstring msg;
	bool completed;
	CMsgStreamBuffer* buffer;
	int size;
	byte data;
};



class CInstanceEdit
{
private:
	DWORD SelfPtr;
public:
	DWORD GetPtr()
	{
		return this->SelfPtr;
	}
};

class CIFChatViewer2
{
public:
	DWORD selfPtr;
};
class CIFChatWndCtrl
{
public:
	char pad_0000[56]; //0x0000
	UINT32 Instance; //0x0038
	char pad_003C[44]; //0x003C
	CIFChatViewer2* pCIFChatViewer; //0x0068
	char pad_006C[980]; //0x006C
}; //Size: 0x0440

class GlobalItemLinking
{
public:
	void Initialize();
	void FUN_00636cd0(CIFEdit* pCIFEdit);
	void AppendTextToChatBox(std::wstring* text);
	void OnIndexHovered(const DWORD EDX, const DWORD EBP);
	static int LastEmptySlot;
	static DWORD SelectedGameChatType;
	std::list<GlobalChat> GlobalChatLog;
	std::wstring m_CurrentLinkedItemName;
	DWORD m_LinkedGlobalItemBegin;
	DWORD m_LinkedGlobalItemEnd;
	unsigned __int8 m_LinkedGlobalSlot;
private:

};
#endif