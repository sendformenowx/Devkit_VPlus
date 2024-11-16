set(SOURCE_FILES
        src/DllMain.cpp
        src/hooks/Hooks.cpp src/hooks/Hooks.h
        src/hooks/GFXVideo3d_Hook.cpp src/hooks/GFXVideo3d_Hook.h
        src/hooks/WndProc_Hook.cpp src/hooks/WndProc_Hook.h
        src/hooks/CGame_Hook.cpp src/hooks/CGame_Hook.h
        src/imgui_windows/ImGui_Windows.cpp src/imgui_windows/ImGui_Windows.h
        src/imgui_windows/InterfaceDebugger.cpp src/imgui_windows/InterfaceDebugger.h
        src/imgui_windows/SoundTool.cpp src/imgui_windows/SoundTool.h
        src/imgui_windows/NavMeshTool.cpp src/imgui_windows/NavMeshTool.h
        src/imgui_windows/EntityExplorer.cpp src/imgui_windows/EntityExplorer.h
        src/imgui_windows/NotificationTool.cpp src/imgui_windows/NotificationTool.h
        src/imgui_windows/About.cpp src/imgui_windows/About.h
        src/imgui_windows/SystemMessage.cpp src/imgui_windows/SystemMessage.h
        src/imgui_windows/ErrorMessageTool.h src/imgui_windows/ErrorMessageTool.cpp
        src/imgui_windows/InterfaceTree.cpp src/imgui_windows/InterfaceTree.h
        src/imgui_windows/ProcessViewer.cpp src/imgui_windows/ProcessViewer.h
        src/ImGui_Windows/Inventory.h src/ImGui_Windows/Inventory.cpp
        src/imgui_windows/PartyInfo.cpp src/imgui_windows/PartyInfo.h
        src/imgui_windows/CharacterData.cpp src/imgui_windows/CharacterData.h
        src/IFMessageYesNo.cpp src/IFMessageYesNo.h
        
        src/OldItemMall/OldItemMall.cpp src/OldItemMall/OldItemMall.h

        src/OldLoginScreen/address_helper.h
        src/OldLoginScreen/char_select.cpp src/OldLoginScreen/char_select.h
        src/OldLoginScreen/Keyframe.h src/OldLoginScreen/Character3D.h
        src/OldLoginScreen/static_constructor.cpp src/OldLoginScreen/static_constructor.h
        src/OldLoginScreen/Vec3.h

        src/Util.cpp src/Util.h
        src/QuickStart.cpp src/QuickStart.h
        src/MathUtil.cpp src/MathUtil.h src/GameHelpers/MemoryHelper.cpp src/GameHelpers/MemoryHelper.h src/GameHelpers/GameMain.cpp src/GameHelpers/GameMain.h src/ClientSettings/ClientCommonSettings.cpp src/ClientSettings/ClientCommonSettings.h src/IFMessageBox.cpp src/IFMessageBox.h src/IFPML.cpp src/IFPML.h src/ItemLinking/GetItemName.cpp src/ItemLinking/GetItemName.h src/ItemLinking/GlobalItemLinking.cpp src/ItemLinking/GlobalItemLinking.h src/Network/CPSMission.cpp src/Network/CPSMission.h src/GameHelpers/CStringHelper.cpp src/GameHelpers/CStringHelper.h src/VenomMenu/IFMainMenu.cpp src/VenomMenu/IFMainMenu.h src/VenomMenu/IFMainMenuGuide.cpp src/VenomMenu/IFMainMenuGuide.h src/ShowIconAbove/IFShowSox.cpp src/ShowIconAbove/IFShowSox.h src/VenomMenu/IFGrantName.cpp src/VenomMenu/IFGrantName.h src/VenomMenu/IFCharlock.cpp src/VenomMenu/IFCharlock.h src/VenomMenu/IFCharAnalyzer.cpp src/VenomMenu/IFCharAnalyzer.h src/VenomMenu/IFRank.cpp src/VenomMenu/IFRank.h src/VenomMenu/IFRankList.cpp src/VenomMenu/IFRankList.h src/VenomMenu/IFRankSlot.cpp src/VenomMenu/IFRankSlot.h src/VenomMenu/IFSpinButton.cpp src/VenomMenu/IFSpinButton.h src/VenomMenu/IFChest.cpp src/VenomMenu/IFChest.h src/VenomMenu/IFChestSlotList.cpp src/VenomMenu/IFChestSlotList.h src/VenomMenu/IFChestSlot.cpp src/VenomMenu/IFChestSlot.h src/VenomMenu/IFChestGuide.cpp src/VenomMenu/IFChestGuide.h src/VenomMenu/IFEventTime.cpp src/VenomMenu/IFEventTime.h src/VenomMenu/IFEventTimeSlot.cpp src/VenomMenu/IFEventTimeSlot.h src/VenomMenu/IFEventTimeSlotList.cpp src/VenomMenu/IFEventTimeSlotList.h src/VenomMenu/IFUniqueList.cpp src/VenomMenu/IFUniqueList.h src/VenomMenu/IFUniqueLog.cpp src/VenomMenu/IFUniqueLog.h src/VenomMenu/IFUniqueLogSlot.cpp src/VenomMenu/IFUniqueLogSlot.h src/VenomMenu/IFChangelog.cpp src/VenomMenu/IFChangelog.h src/VenomMenu/IFTitleManager.cpp src/VenomMenu/IFTitleManager.h src/VenomMenu/IFDiscordGuide.cpp src/VenomMenu/IFDiscordGuide.h src/VenomMenu/IFDiscord.cpp src/VenomMenu/IFDiscord.h src/VenomMenu/IFFacebookGuide.cpp src/VenomMenu/IFFacebookGuide.h src/VenomMenu/IFFacebook.cpp src/VenomMenu/IFFacebook.h src/VenomMenu/IFEventMenuGuide.cpp src/VenomMenu/IFEventMenuGuide.h src/VenomMenu/IFEventMenu.cpp src/VenomMenu/IFEventMenu.h src/VenomMenu/IFAttendanceEvent.cpp src/VenomMenu/IFAttendanceEvent.h src/VenomMenu/IFAttendance.cpp src/VenomMenu/IFAttendance.h src/NewReverse/IFSavedLocation.cpp src/NewReverse/IFSavedLocation.h src/LicenseManager/LicenseManager.cpp src/LicenseManager/LicenseManager.h src/VenomMenu/IFDps.cpp src/VenomMenu/IFDps.h src/VenomMenu/IFFortressWar.cpp src/VenomMenu/IFFortressWar.h src/VenomMenu/IFSurvivalArena.cpp src/VenomMenu/IFSurvivalArena.h src/PCLimit/HwidReader.cpp src/PCLimit/HwidReader.h src/PCLimit/md5.cpp src/PCLimit/md5.h src/PCLimit/base64.cpp src/PCLimit/base64.h src/PCLimit/Base64Encode.h src/NewReverse/IFMovePartyMember.cpp src/NewReverse/IFMovePartyMember.h src/NewReverse/IFMovePartyMemberSlot.cpp src/NewReverse/IFMovePartyMemberSlot.h src/NewReverse/IFMovePartyMemberSlotList.cpp src/NewReverse/IFMovePartyMemberSlotList.h src/Special/NotificationHandler.cpp src/Special/NotificationHandler.h src/VenomMenu/IFTitleManagerSlot.cpp src/VenomMenu/IFTitleManagerSlot.h)

add_library(DevKit_DLL SHARED ${SOURCE_FILES})
target_link_libraries(DevKit_DLL DiscordRichPresence BSLib ClientLib MathHelpers memory winmm)

set_target_properties(DevKit_DLL
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/BinOut/${CMAKE_BUILD_TYPE}/"
        LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/BinOut/${CMAKE_BUILD_TYPE}/"
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/BinOut/${CMAKE_BUILD_TYPE}/"
        )
