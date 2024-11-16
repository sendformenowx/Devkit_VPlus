#pragma once

union uregion {
	struct {
		char y;
		char x;
	} single;
	short r;
};

class CControler
{
public:
    char pad_0000[80]; //0x0000
    unsigned __int32 cursorPosX; //0x0050
    unsigned __int32 cursorPosY; //0x0054
    char pad_0058[4072]; //0x0058
}; //Size: 0x1040
#define g_CurrentIfUnderCursor (*(CGWndBase**)0x0110F608)
#define g_Controler (*(CControler**)0x0110F7D4)

#define g_Region (*(uregion*)0xEEF68C)


#define CLIENT_SCREEN_WIDTH (*(int*)0x00ED7CB8)
#define CLIENT_SCREEN_HEIGHT (*(int*)0x00ED7CBC)

#define SendMsg(x) reinterpret_cast<void (__cdecl *)(CMsgStreamBuffer&)>(0x008418D0)(x)
#define SendMsgClient(x) reinterpret_cast<void (__cdecl *)(CMsgStreamBuffer&)>(0x008A7630)(x)



#define EventWnd 1332
#define FaceWndID 1334
#define DCWnd 1335
#define ATTWnd 1336
#define ChestID 1337
#define MenuID 1338
#define GrantnameID 1339
#define CharlockID 1340
#define TitleID 1341
#define CharAnalyzerID 1342
#define RankID 1343
#define UniqueIDW 1344
#define EventIDW 1345
#define ChangeID 1346
#define DPSID 1347
#define FTWID 1348
#define SURVIVALID 1349
#define Costomtitle 1350
#define yesno 1351

#define PurbleNotify 11455
#define OrangeNotify 11456
#define SavedLoc 114999
#define MovePartys 114998
#define ShowSoxItem 13370
#define CustomSlot 501