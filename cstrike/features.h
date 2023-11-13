#pragma once

#include "common.h"

class CUserCmd;
class CCSPlayerController;
class CMeshData;

namespace F
{
	bool Setup();
	void Destroy();

	void OnPresent();
	void OnFrameStageNotify(int nStage);
	void OnCreateMove(CUserCmd* pCmd, CCSPlayerController* pLocalController);
	bool OnDrawObject(void* pAnimatableSceneObjectDesc, void* pDx11, CMeshData* arrMeshDraw, int nDataCount, void* pSceneView, void* pSceneLayer, void* pUnk, void* pUnk2);
}
