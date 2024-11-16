#include "GlobalItemLinking.h"
#include "..\..\DevKit_DLL\src\GameHelpers\GameMain.h"
#include "GInterface.h"
#include "IFWholeChat.h"
#include "../VenomMenu/IFMainMenu.h"
#include <algorithm>
#include <ICPlayer.h>
CIFEdit* g_CIFEdit;
// CIFEdit::GetText(void) .text 00653350 00000017   R . . . . . .

const DWORD cdwOnCIFEditWndProcHandleAddr = 0x00637A50;
const DWORD cdwOnCIFEditWndProcHandleJmpback = 0x00637A55;

const DWORD callOrigAddr = 0x00636CD0;
__declspec (naked) void ASM_OnCIFEditWndProcHandle()
{
	__asm
	{
		pushad;
		pushfd;
		PUSH EAX;
		CALL GlobalItemLinking::FUN_00636cd0;
		popfd;
		popad;

		call callOrigAddr;
		jmp cdwOnCIFEditWndProcHandleJmpback;
	}
}
void GlobalItemLinking::FUN_00636cd0(CIFEdit* pCIFEdit)
{
	if (g_CIFEdit)
		g_CIFEdit = NULL;
	if (g_pCGInterface)
	{
		CIFWholeChat* pWholeChat = reinterpret_cast<CIFWholeChat*>(g_pCGInterface->m_IRM.GetResObj(56, 1));
		if (pWholeChat)
		{
			g_CIFEdit = pWholeChat->m_pEdit;
		}
		else
		{
			g_global->m_LinkedGlobalItemEnd = 0;
			g_global->m_LinkedGlobalItemBegin = 0;
			g_global->m_CurrentLinkedItemName = std::wstring();
		}
	}
	if (pCIFEdit && !g_global->m_CurrentLinkedItemName.empty())
	{
		if (g_CIFEdit != NULL && g_CIFEdit == pCIFEdit) // if its equals to current global window
		{
			short backSpaceState = GetKeyState(VK_BACK);
			short deleteState = GetKeyState(VK_DELETE);
			short leftArrowKeyState = GetKeyState(VK_LEFT);
			short rightArrowKeyState = GetKeyState(VK_RIGHT);

			int CurrIndex = pCIFEdit->GetCurrentIndex();
			std::wstring CurrText = std::wstring(pCIFEdit->GetText());
			if (!CurrText.empty())
			{
				int begin = CurrText.find(L"͟<");
				if (begin != std::wstring::npos)
					g_global->m_LinkedGlobalItemBegin = begin;
				int end = CurrText.find(L"͟>");
				if (end != std::wstring::npos)
					g_global->m_LinkedGlobalItemEnd = end + 2;


				if (pCIFEdit->GetAreaSize() == 100 && g_global->m_LinkedGlobalItemEnd != 0)
					pCIFEdit->SetTextAreaSize(100 + g_global->m_CurrentLinkedItemName.length());
				if (pCIFEdit->GetAreaSize() != 100 && g_global->m_LinkedGlobalItemEnd == 0)
					pCIFEdit->SetTextAreaSize(100);
			}
			//if left
			if ((leftArrowKeyState == -127 || leftArrowKeyState == -128) && CurrIndex - 1 <= g_global->m_LinkedGlobalItemEnd && CurrIndex >= g_global->m_LinkedGlobalItemBegin)
			{
				//printf("left called %d\n", leftArrowKeyState);
				pCIFEdit->SetCurrentIndex(g_global->m_LinkedGlobalItemBegin);
				return;
			}
			//if right
			if ((rightArrowKeyState == -127 || rightArrowKeyState == -128) && CurrIndex + 1 >= g_global->m_LinkedGlobalItemBegin && CurrIndex <= g_global->m_LinkedGlobalItemEnd)
			{
				//printf("right called %d\n", rightArrowKeyState);
				pCIFEdit->SetCurrentIndex(g_global->m_LinkedGlobalItemEnd);
				return;
			}

			//printf("ChatIndex = %d - Size = %d\n", pCIFEdit->GetCurrentIndex(), pCIFEdit->GetAreaSize());


			if ((backSpaceState == -127 || backSpaceState == -128) && (CurrIndex >= g_global->m_LinkedGlobalItemBegin && CurrIndex - 1 <= g_global->m_LinkedGlobalItemEnd))
			{
				std::wstring new_str = CurrText.c_str();
				int findedstring = CurrText.find(g_global->m_CurrentLinkedItemName.c_str());
				if (findedstring != std::wstring::npos)
				{
					CurrText.erase(g_global->m_LinkedGlobalItemBegin, g_global->m_CurrentLinkedItemName.size());

					pCIFEdit->SetText(CurrText.c_str());
					if (CurrText.length() > 0)
						pCIFEdit->SetCurrentIndex(g_global->m_LinkedGlobalItemBegin);
					else
						pCIFEdit->SetCurrentIndex(0);
					g_global->m_LinkedGlobalItemEnd = 0;
					g_global->m_LinkedGlobalItemBegin = 0;
					g_global->m_CurrentLinkedItemName = std::wstring();
					return;
				}
			}
			if ((deleteState == -127 || deleteState == -128) && (CurrIndex + 2 >= g_global->m_LinkedGlobalItemBegin && CurrIndex <= g_global->m_LinkedGlobalItemEnd))
			{
				std::wstring new_str = CurrText.c_str();
				int findedstring = CurrText.find(g_global->m_CurrentLinkedItemName.c_str());
				if (findedstring != std::wstring::npos)
				{
					CurrText.erase(g_global->m_LinkedGlobalItemBegin, g_global->m_CurrentLinkedItemName.size());

					pCIFEdit->SetText(CurrText.c_str());
					pCIFEdit->SetCurrentIndex(CurrText.length());
					g_global->m_LinkedGlobalItemEnd = 0;
					g_global->m_LinkedGlobalItemBegin = 0;
					g_global->m_CurrentLinkedItemName = std::wstring();
					return;
				}
			}
		}

	}
}
const DWORD cdwOnIndexChanged = 0x0063A389;
const DWORD cdwOnIndexChangedJmpback = 0x0063A38F;

const DWORD cdwOnIndexHover = 0x0063A1A3;
const DWORD cdwOnIndexHoverJmpback = 0x0063A1A8;

const DWORD cdwOnChatTypeChanged = 0x007AA74D;
const DWORD cdwOnChatTypeChangedJmpback = cdwOnChatTypeChanged + 6;
DWORD GlobalItemLinking::SelectedGameChatType;
bool compare_fn(GlobalChat lhs) {
	return lhs.index < 0;
};
__declspec (naked) void ASM_OnIndexChanged()
{
	__asm
	{
		PUSHAD;
		PUSHFD;
		PUSH EBX;
		CALL GlobalItemLinking::AppendTextToChatBox;
		POPFD;
		POPAD;
		TEST EBP, EBP;
		PUSH ESI;
		PUSH EDI;
		MOV ESI, ECX;
		JMP cdwOnIndexChangedJmpback;
	}
}


const DWORD call1_addr = 0x008B4750;

__declspec (naked) void ASM_OnIndexHover()
{
	__asm
	{
		PUSHAD;
		PUSHFD;
		PUSH EBP;
		PUSH EDX;
		CALL GlobalItemLinking::OnIndexHovered;
		POPFD;
		POPAD;
		CALL call1_addr;
		JMP cdwOnIndexHoverJmpback;
	}
}

__declspec (naked) void ASM_OnChatTypeChanged()
{
	__asm
	{
		MOV GlobalItemLinking::SelectedGameChatType, EBP;
		MOV DWORD PTR DS : [ESI + 0x420] , EBP;
		jmp cdwOnChatTypeChangedJmpback;
	}
}
enum ChatType2
{
	NormalChat = 16,
	PartyChat = 17,
	GuildChat = 18,
	UnionChat = 19,
	AcademyChat = 30
};
class CIFTextBox2
{
public:
	char pad_0000[48]; //0x0000
	CIFChatViewer2* pChatViewer; //0x0030
	DWORD m_ChatType; // 0x34
	char pad_0034[904]; //0x0038
	UINT32 LastIndex; //0x03C0
};

void GlobalItemLinking::AppendTextToChatBox(std::wstring* text)
{
	try
	{
		bool inserted_new = false;
		CIFTextBox2* pCIFTextBox = 0;
		_asm {mov pCIFTextBox, ecx};
		if (CNetProcessIn::CharDead == false)
		if (text && pCIFTextBox && pCIFTextBox->pChatViewer && pCIFTextBox->pChatViewer->selfPtr == 0xDBBA44 && pCIFTextBox->m_ChatType == ChatType2::NormalChat)
		{
			int index = pCIFTextBox->LastIndex;
			//printf("appended new text index = %d - pointer = %02x and msg = %ls\n", index, pCIFTextBox, text->c_str());
			if (index == 100)
			{
				index = 99;
				for (std::list<GlobalChat>::iterator currentGlobalData = g_global->GlobalChatLog.begin(); currentGlobalData != g_global->GlobalChatLog.end(); currentGlobalData++)
				{
					if (currentGlobalData->completed)
					{
						currentGlobalData->index -= 1; //99 =98
					}
				}
			}
			const wchar_t* g_LastChatMsg = text->c_str();
			//std::wcout << g_LastChatMsg << L" and index " << index << std::endl;
			if (g_LastChatMsg != NULL && g_LastChatMsg != 0 && *(DWORD*)g_LastChatMsg != 0x00200020)
			{
				std::wstring isGlobalCheck(g_LastChatMsg);
				if (!isGlobalCheck.empty() && isGlobalCheck.find(L"͟>") != std::wstring::npos)
				{
					std::wstring GlobalMsg(g_LastChatMsg);
					if (!GlobalMsg.empty() && GlobalMsg.find(L":") != std::wstring::npos)
					{
						GlobalChat chatp;
						for (std::list<GlobalChat>::iterator chat = g_global->GlobalChatLog.begin(); chat != g_global->GlobalChatLog.end(); chat++)
						{
							std::wstring MsgInList = std::wstring(chat->msg);
							if (GlobalMsg == MsgInList)
							{
								//wprintf(L"before->text = %s-%s, index = %d, completed = %d\n", MsgInList.c_str(), GlobalMsg.c_str(), chat.index, chat.completed);
								if (!chat->completed)
								{
									chat->completed = true;
									chat->index = index;
									//wprintf(L"after->text = %s-%s, index = %d, completed = %d\n", MsgInList.c_str(), GlobalMsg.c_str(), chat.index, chat.completed);
									break;
								}
								else if (chat->completed)
								{
									if (index != 0)
										chatp.index = index;
									chatp.msg = GlobalMsg;
									chatp.completed = true;
									chatp.buffer = chat->buffer;
									inserted_new = true;
								}
							}
						}
						if (inserted_new)
							g_global->GlobalChatLog.push_back(chatp);
						//wprintf(L"ChatIndex[%d]:%s\n", index, GlobalMsg.c_str());
					}
				}
			}

			std::remove_if(g_global->GlobalChatLog.begin(), g_global->GlobalChatLog.end(), &compare_fn);
		}
	}
	catch (std::exception& ex)
	{
	}
	catch (...)
	{
	}
}

extern HWND g_orig_wndproc_hwnd;
CIFSlotWithHelp* lastFoundEmptySlot;
int GlobalItemLinking::LastEmptySlot = -1;
void GlobalItemLinking::OnIndexHovered(DWORD EDX, DWORD EBP)
{
	try
	{
		CIFChatWndCtrl* checker = 0;
		_asm mov checker, ebx;
		if (CNetProcessIn::CharDead == false)
		if (checker && checker->Instance == 0xD9E37C)
		{
			if (g_global->SelectedGameChatType == 0 && checker->pCIFChatViewer->selfPtr == 0xDBBA44)
			{
				if (g_global->SelectedGameChatType == 0)
				{
					std::wstring test = L"none";
					int index_stack = EDX;
					//printf("index stack = %d\n", index_stack);
					for (std::list<GlobalChat>::iterator iter = g_global->GlobalChatLog.begin(); iter != g_global->GlobalChatLog.end(); iter++)
					{
						//wprintf(L"[%d]amk yha : %d\n", iter.index, index_stack);
						if (iter->index == index_stack && iter->completed)
						{
							test = iter->msg;
							if (EBP == 1 && iter->msg.find(L"͟>") != std::wstring::npos && iter->msg.find(L"<") != std::wstring::npos)
							{



								if (CIFMainMenu::CIFSlots->ItemInfo == NULL || CIFMainMenu::CIFSlots->ItemInfo == 0)
								{
									CIFInventory* pInventory = g_pCGInterface->GetMainPopup()->GetInventory();
									CIFSlotWithHelp* pEmptySlot;
									bool isFound = false;
									byte tester = g_pCICPlayer->GetSlotCount();
									for (int i = 0; i < 96; i++)
									{
										if (pInventory->GetRemainingSlot() > 0)
										{
											CIFSlotWithHelp* pSlot = *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots + (i * 4));

											if (pSlot->Type == 0 && pSlot->ItemInfo == NULL || pSlot->ItemInfo == 0)
											{
												pEmptySlot = pSlot;
												isFound = true;
												break;
											}
										}
									}
									//printf("ptr of Inventory = %02x - found an empty slot = %d slot ptr = %02x\n", pInventory, emptySlotHolder, pEmptySlot);
									if (isFound && pEmptySlot && pEmptySlot->ItemInfo == NULL)
									{
										lastFoundEmptySlot = pEmptySlot;
										LastEmptySlot = pEmptySlot->m_UniqueID - 87;
										if (pEmptySlot->ItemInfo == NULL && pEmptySlot->ItemInfo == 0)
										{
											pEmptySlot->m_bVisible = false;
											UINT8 Test1 = 1;
											UINT8 Test2 = 6;
											UINT8 Test3 = LastEmptySlot;
											CMsgStreamBuffer* temporaryPacket = new CMsgStreamBuffer(0xB034);
											*temporaryPacket << Test1;
											*temporaryPacket << Test2;
											*temporaryPacket << Test3;
											for (size_t i = 0; i < iter->buffer->m_availableBytesForReading; ++i)
											{
												byte  tesaa;

												*iter->buffer >> tesaa;
												*temporaryPacket << tesaa;
											}
											iter->buffer->Seek(0);
											//firstly get rid of the annoying message (we should hide it xd)
											g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x0087C1F0), 2);
											*(BYTE*)(0x0087C1F0) = 0xEB;
											*(BYTE*)(0x0087C1F0 + 1) = 0x37;
											g_MemoryHelper->ReProtect();
											g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x0087C15B), 1);
											*(BYTE*)(0x0087C15B) = 0x75;
											g_MemoryHelper->ReProtect();
											//first of all make a copy of original item
											netprocess->ProcessItemMovementResult(temporaryPacket);// bu şekide dene :D
											//after giving the item, rollback the item gained msg so player will keep seeing it
											g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x0087C1F0), 2);
											*(BYTE*)(0x0087C1F0) = 0x72;
											*(BYTE*)(0x0087C1F0 + 1) = 0x05;
											g_MemoryHelper->ReProtect();
											g_MemoryHelper->UnProtect(reinterpret_cast<void*>(0x0087C15B), 1);
											*(BYTE*)(0x0087C15B) = 0x74;
											g_MemoryHelper->ReProtect();
                                            CIFMainMenu::CIFSlots->ItemInfo = pEmptySlot->ItemInfo;
											pEmptySlot->m_bVisible = false;// böle denesene
											if (CIFMainMenu::CIFSlots->ItemInfo)
											{
												if (CIFMainMenu::CIFSlots->Type == 0)
												{
                                                    CIFMainMenu::CIFSlots->Type = 70;
													//slot->dwWidth = 1;
													//slot->dwHeight = 1;
												}
												CIFMainMenu::CIFSlots->ItemInfo->Active = true;
                                                CIFMainMenu::CIFSlots->UpdateLocation(g_Controler->cursorPosX + 25, g_Controler->cursorPosY);
                                                CIFMainMenu::CIFSlots->MakeBubble();
											}
										}

									}
									else
									{
										g_pCGInterface->ShowMessage_Warning(L"You need two empty slot in your inventory in order to get global item linking system enabled.");
										if (lastFoundEmptySlot && !lastFoundEmptySlot->m_bVisible)
											lastFoundEmptySlot->m_bVisible = true;
									}
								}
							}
							if (EBP == 0)
							{
								if (lastFoundEmptySlot && lastFoundEmptySlot->ItemInfo)
								{
									if (LastEmptySlot > 0)
									{
										UINT8 Test12 = 1;
										UINT8 Test22 = 7;
										UINT8 Test32 = LastEmptySlot;
										CMsgStreamBuffer* pBuffer = new CMsgStreamBuffer(0xB034);
										*pBuffer << Test12;
										*pBuffer << Test22;
										*pBuffer << Test32;
										netprocess->ProcessItemMovementResult(pBuffer);// bu şekide dene :D
										LastEmptySlot = 0;
									}
								}
								if (lastFoundEmptySlot && !lastFoundEmptySlot->m_bVisible)
									lastFoundEmptySlot->m_bVisible = true;
								if (CIFMainMenu::CIFSlots)
								{
                                    CIFMainMenu::CIFSlots->UpdateLocation(9999, 0);
									//slot->ShowGWnd(false);
									if (CIFMainMenu::CIFSlots->ItemInfo)
									{
                                        CIFMainMenu::CIFSlots->m_bVisible = false;
                                        CIFMainMenu::CIFSlots->ItemInfo = NULL;
										lastFoundEmptySlot->MakeBubble();
										lastFoundEmptySlot = NULL;
									}
								}
								//printf("%02x\n", *reinterpret_cast<CIFSlotWithHelp**>(pInventory->pSlots));
								//printf("reloaded icon new location %d - %d\n", slot->XPos, slot->YPos);
							}

							/*wprintf(L"index = %d - IsFocused = %d\n", index_stack, EBP);
							wprintf(L"___________________________________________________\n");*/
							break;
						}
					}
				}
			}
		}
	}
	catch (const std::exception& ex)
	{

	}
	catch (...)
	{

	}
}
void GlobalItemLinking::Initialize()
{
	g_MemoryHelper->SetNop(cdwOnIndexChanged, 6);
	g_MemoryHelper->Detour(false, reinterpret_cast<void*>(cdwOnIndexChanged), ASM_OnIndexChanged);

	g_MemoryHelper->Detour(false, reinterpret_cast<void*>(cdwOnIndexHover), ASM_OnIndexHover);


	g_MemoryHelper->SetNop(cdwOnChatTypeChanged, 6);
	g_MemoryHelper->Detour(false, reinterpret_cast<void*>(cdwOnChatTypeChanged), ASM_OnChatTypeChanged);
	g_MemoryHelper->Detour(false, reinterpret_cast<void*>(cdwOnCIFEditWndProcHandleAddr), ASM_OnCIFEditWndProcHandle);
}