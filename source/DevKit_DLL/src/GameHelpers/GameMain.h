#ifndef Q_GLOBAL_GAME_MAIN_H
#define Q_GLOBAL_GAME_MAIN_H

#include <BSLib/MsgHandler.h>
#include "MemoryHelper.h"
#include "../ItemLinking/GlobalItemLinking.h"
#include "CStringHelper.h"
#include <NetProcessIn.h>

extern CMsgStreamBuffer* buffer;

extern MemoryHelper* g_MemoryHelper;
extern GlobalItemLinking* g_global;
extern CNetProcessIn* netprocess;
extern CStringHelper* g_StringHelper;
#endif