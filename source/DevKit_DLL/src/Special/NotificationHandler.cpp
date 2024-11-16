#include <NetProcessIn.h>
#include "NotificationHandler.h"
#include "GInterface.h"

NotificationHandler g_notificationhandler;

std::wstring* NotificationHandler::GetSpawnNotify(std::wstring namestr)
{
    std::map<std::wstring, std::wstring>::iterator it = SpawnUniqueNotifies.find(namestr);
    if (it != SpawnUniqueNotifies.end())
        return &it->second;
    return NULL;
}

std::wstring* NotificationHandler::GetDespawnNotify(std::wstring namestr)
{
    std::map<std::wstring, std::wstring>::iterator it = DespawnUniqueNotifies.find(namestr);
    if (it != DespawnUniqueNotifies.end())
        return &it->second;
    return NULL;
}

std::wstring* NotificationHandler::GetKillNotify(std::wstring namestr)
{
    std::map<std::wstring, std::wstring>::iterator it = KillUniqueNotifies.find(namestr);
    if (it != KillUniqueNotifies.end())
        return &it->second;
    return NULL;
}

void NotificationHandler::Load(void)
{

    // Tg
    std::wstring TgSpawn = L"Tiger Girl  has appeared on Tiger Mountain.";
    std::wstring TgKill = L"[%s] killed Tiger girl  from Tiger Mountain.";
    std::wstring TgdeSpawn = L"Tiger Girl  has disappeared from Tiger Mountain.";
    SpawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_CH_TIGERWOMAN", TgSpawn.c_str()));
    DespawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_CH_TIGERWOMAN", TgdeSpawn.c_str()));
    KillUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_CH_TIGERWOMAN", TgKill.c_str()));

    std::wstring TgSpawn1 = L"Tiger Girl  has appeared on Tiger Mountain.";
    std::wstring TgKill1 = L"[%s] killed Tiger girl  from Tiger Mountain.";
    std::wstring TgdeSpawn1 = L"Tiger Girl  has disappeared from Tiger Mountain.";
    SpawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_CH_TIGERWOMAN_STR", TgSpawn1.c_str()));
    DespawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_CH_TIGERWOMAN_STR", TgdeSpawn1.c_str()));
    KillUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_CH_TIGERWOMAN_STR", TgKill1.c_str()));

    // uru
    std::wstring uruspawn = L"Uruchi  has appeared in Tarim Basin.";
    std::wstring urudespawn = L"Uruchi  has disappeared from Tarim Basin.";
    std::wstring urukill = L"[%s] killed Uruchi  from Tarim Basin.";
    SpawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_OA_URUCHI", uruspawn.c_str()));
    DespawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_OA_URUCHI", urudespawn.c_str()));
    KillUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_OA_URUCHI", urukill.c_str()));

    std::wstring uruspawn1 = L"Uruchi  has appeared in Tarim Basin.";
    std::wstring urudespawn1 = L"Uruchi  has disappeared from Tarim Basin.";
    std::wstring urukill1 = L"[%s] killed Uruchi  from Tarim Basin.";
    SpawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_OA_URUCHI_STR", uruspawn1.c_str()));
    DespawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_OA_URUCHI_STR", urudespawn1.c_str()));
    KillUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_OA_URUCHI_STR", urukill1.c_str()));

    // isyu
    std::wstring isyspawn = L"Isyutaru  has appeared in Karakoram.";
    std::wstring isydespawn = L"Isyutaru  has disappeared from Karakoram.";
    std::wstring isykill = L"[%s] killed Isyutaru  from Karakoram.";
    SpawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_KK_ISYUTARU", isyspawn.c_str()));
    DespawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_KK_ISYUTARU", isydespawn.c_str()));
    KillUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_KK_ISYUTARU", isykill.c_str()));

    std::wstring isyspawn1 = L"Isyutaru  has appeared in Karakoram.";
    std::wstring isydespawn1 = L"Isyutaru  has disappeared from Karakoram.";
    std::wstring isykill1 = L"[%s] killed Isyutaru  from Karakoram.";
    SpawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_KK_ISYUTARU_STR", isyspawn1.c_str()));
    DespawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_KK_ISYUTARU_STR", isydespawn1.c_str()));
    KillUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_KK_ISYUTARU_STR", isykill1.c_str()));


    //lord
    std::wstring lordspawn = L"Lord Yarkan  has appeared in Taklamakan.";
    std::wstring lorddespawn = L"Lord Yarkan  has disappeared from Taklamakan.";
    std::wstring lordkill = L"[%s] killed Lord Yarkan  from Taklamakan.";
    SpawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_TK_BONELORD", lordspawn.c_str()));
    DespawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_TK_BONELORD", lorddespawn.c_str()));
    KillUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_TK_BONELORD", lordkill.c_str()));

    std::wstring lordspawn1 = L"Lord Yarkan  has appeared in Taklamakan.";
    std::wstring lorddespawn1 = L"Lord Yarkan  has disappeared from Taklamakan.";
    std::wstring lordkill1 = L"[%s] killed Lord Yarkan  from Taklamakan.";
    SpawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_TK_BONELORD_STR", lordspawn1.c_str()));
    DespawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_TK_BONELORD_sTR", lorddespawn1.c_str()));
    KillUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_TK_BONELORD_STR", lordkill1.c_str()));



    //demon
    std::wstring demonspawn = L"Demon Shaitan  has appeared on Mt. Roc.";
    std::wstring demondespawn = L"Demon Shaitan  has disappeared from Mt. Roc.";
    std::wstring demonkill = L"[%s] killed Demon Shaitan  from Mt. Roc.";
    SpawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_RM_TAHOMET", demonspawn.c_str()));
    DespawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_RM_TAHOMET", demondespawn.c_str()));
    KillUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_RM_TAHOMET", demonkill.c_str()));


    std::wstring demonspawn1 = L"Demon Shaitan  has appeared on Mt. Roc.";
    std::wstring demondespawn1 = L"Demon Shaitan  has disappeared from Mt. Roc.";
    std::wstring demonkill1 = L"[%s] killed Demon Shaitan  from Mt. Roc.";
    SpawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_RM_TAHOMET_STR", demonspawn1.c_str()));
    DespawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_RM_TAHOMET_STR", demondespawn1.c_str()));
    KillUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_RM_TAHOMET_STR", demonkill1.c_str()));

    //extras
    //CERBERUS
    std::wstring CerbSpawn = L"Cerberus  has appeared in Desperado Hill.";
    std::wstring CerbdeSpawn = L"Cerberus  has disappeared from Desperado Hill.";
    std::wstring CerbdeadNotice = L"[%s] killed Cerberus  from Desperado Hill.";
    SpawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_EU_KERBEROS", CerbSpawn.c_str()));
    DespawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_EU_KERBEROS", CerbdeSpawn.c_str()));
    KillUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_EU_KERBEROS", CerbdeadNotice.c_str()));


    //extras
    //CERBERUS STR
    std::wstring CerbSpawn1 = L"Cerberus  has appeared in Desperado Hill.";
    std::wstring CerbdeSpawn1 = L"Cerberus  has disappeared from Desperado Hill.";
    std::wstring CerbdeadNotice1 = L"[%s] killed Cerberus  from Desperado Hill.";
    SpawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_EU_KERBEROS_STR", CerbSpawn1.c_str()));
    DespawnUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_EU_KERBEROS_STR", CerbdeSpawn1.c_str()));
    KillUniqueNotifies.insert(std::pair<std::wstring, std::wstring>(L"SN_MOB_EU_KERBEROS_STR", CerbdeadNotice1.c_str()));


}

void NotificationHandler::Initialize(void)
{
    Load();

    replaceAddr(0x0086FCDD, addr_from_this(&CNetProcessIn::On300c));
}
