#include "usercmd.h"

#include "../entity.h"

CUserCmd* CUserCmd::Get()
{
	// https://www.unknowncheats.me/forum/4230480-post5932.html
	auto controller = CCSPlayerController::GetLocalPlayerController();
	if (!controller)
		return nullptr;

	static void*(__fastcall * GetCommandIndex)(void* pController, int* index) = reinterpret_cast<decltype(GetCommandIndex)>(MEM::GetAbsoluteAddress(MEM::FindPattern(CLIENT_DLL, ("E8 ? ? ? ? 8B 8D ? ? ? ? 8D 51")), 0x1, 0x0));

	if (!GetCommandIndex)
		return nullptr;

	int index = 0;
	GetCommandIndex(controller, &index);
	int commandIndex = index - 1;

	if (commandIndex == -1)
		commandIndex = 0xFFFFFFFF;

	static void*(__fastcall * GetUserCmdBase)(void* a1, int a2) = reinterpret_cast<decltype(GetUserCmdBase)>(MEM::GetAbsoluteAddress(MEM::FindPattern(CLIENT_DLL, ("E8 ? ? ? ? 48 8B CF 4C 8B E8 44 8B B8")), 0x1, 0x0));

	if (!GetUserCmdBase)
		return nullptr;

	static void* off_181D9AAA0 = *reinterpret_cast<void**>(MEM::ResolveRelativeAddress(MEM::FindPattern(CLIENT_DLL, ("48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B CF 4C 8B E8")), 0x3, 0x7));

	if (!off_181D9AAA0)
		return nullptr;

	void* pUserCmdBase = GetUserCmdBase(off_181D9AAA0, commandIndex);
	if (!pUserCmdBase)
		return nullptr;

	DWORD sequenceNumber = *reinterpret_cast<DWORD*>((uintptr_t)pUserCmdBase + 0x5C00);
	static CUserCmd*(__fastcall * GetUserCmd)(void* pController, DWORD sequenceNumber) = reinterpret_cast<decltype(GetUserCmd)>(MEM::GetAbsoluteAddress(MEM::FindPattern(CLIENT_DLL, ("E8 ? ? ? ? 48 8B 0D ? ? ? ? 45 33 E4 48 89 44 24")), 0x1, 0x0));

	if (!GetUserCmd)
		return nullptr;

	CUserCmd* pUserCmd = GetUserCmd(controller, sequenceNumber);
	if (!pUserCmd)
		return nullptr;

	if (pUserCmd->csgoUserCmd.pBaseCmd->pViewAngles != nullptr)
	{
		pUserCmd->csgoUserCmd.pBaseCmd->pViewAngles->angValue.x = 0;
		pUserCmd->csgoUserCmd.pBaseCmd->pViewAngles->angValue.y = 0;
	}

	return pUserCmd;
}
