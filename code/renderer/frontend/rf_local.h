/*
============================================================================
Copyright (C) 2012 V.

This file is part of Qio source code.

Qio source code is free software; you can redistribute it 
and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

Qio source code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA,
or simply visit <http://www.gnu.org/licenses/>.
============================================================================
*/
// rf_local.h - local header for renderer frontend module
#ifndef __RF_LOCAL_H__
#define __RF_LOCAL_H__

#include "../cameraDef.h"
#include <shared/array.h>

// for Doom3 .proc and QioBSP areaPortals
#define MAX_PORTAL_VISIT_COUNT 4

// rf_main.cpp
void RF_InitMain();
void RF_Draw3DView();
void RF_AddGenericDrawCalls();
bool RF_IsUsingDynamicLights();
bool RF_IsUsingShadowVolumes();
bool RF_IsUsingShadowMapping();
bool RF_IsDrawingPrelitGeometry();
int RF_GetShadowingMode();
bool RF_MaterialNeedsCPU(const class mtrAPI_i *mat);
enum cullResult_e RF_CullEntitySpaceBounds(const class aabb &bb);

// rf_debugDrawing.cpp
void RF_DoDebugDrawing();
void RFDL_DrawDebugLines();
u32 RFDL_AddDebugLine(const vec3_c &from, const vec3_c &to, const vec3_c &color, float life);
u32 RFDL_AddDebugBB(const aabb &bb, const vec3_c &color, float life);
void RFDL_DrawDebugBBs();

// rf_entities.cpp
class rEntityAPI_i *RFE_AllocEntity();
void RFE_RemoveEntity(class rEntityAPI_i *ent);
void RFE_AddEntityDrawCalls();
void RFE_ClearEntities();
void RFE_MarkEntityMaterials();
void RFE_DrawEntityAbsBounds();
bool RF_TraceSceneRay(class trace_c &tr, bool bSkipPlayerModels);
bool RF_DoCameraTrace(class trace_c &tr, bool bSkipPlayerModels);
u32 RFE_BoxEntities(const class aabb &absBounds, arraySTD_c<class rEntityImpl_c*> &out);
// "forceThirdPerson" is true while generating shadow map drawcalls
void RFE_AddEntity(class rEntityImpl_c *ent, const class frustum_c *customFrustum = 0, bool forceThirdPerson = false);
void RFE_IterateEntities(void (*callback)(class rEntityImpl_c *ent));
void RF_GetEntitiesBounds(class aabb &out);

// rf_lights.cpp
class rLightAPI_i *RFL_AllocLight();
void RFL_RemoveLight(class rLightAPI_i *ent);
void RFL_AddLightInteractionsDrawCalls();
void RFL_RecalculateLightsInteractions();
void RFL_FreeAllLights();
void RFL_RemoveAllReferencesToEntity(class rEntityImpl_c *ent);
u32 RFL_GetNumAllocatedLights();
class rLightAPI_i *RFL_GetLight(u32 i);

 // called when depth pass if done
void RFL_AssignLightOcclusionQueries();
bool RFL_GPUOcclusionQueriesForLightsEnabled();

// rf_sky.cpp
void RF_InitSky();
void RF_ShutdownSky();
void RF_DrawSky();
bool RF_HasSky();
void RF_SetSkyMaterial(class mtrAPI_i *newSkyMaterial);
void RF_SetSkyMaterial(const char *skyMaterialName);
class mtrAPI_i *RF_GetSkyMaterial();
void RF_SetSunMaterial(class mtrAPI_i *newSunMaterial);
bool RF_HasSunMaterial();
const class mtrAPI_i *RF_GetSunMaterial();
const class vec3_c &RF_GetSunDirection();

// rf_decals.cpp
void RF_InitDecals();
void RF_ShutdownDecals();
void RF_AddWorldDecalDrawCalls();
class simpleDecalBatcher_c *RF_GetWorldDecalBatcher();

// rf_anims.cpp
void RF_ClearAnims();

// rf_map.cpp - load world map directly from .map file
class r_model_c *RF_LoadMAPFile(const char *fname);

// rf_water.cpp
void RF_SetWaterLevel(const char *waterLevel);
void RF_AddWaterDrawCalls();
void RF_ShutdownWater();

// rf_explosions.cpp
u32 RF_AddExplosion(const class vec3_c &pos, float radius, class mtrAPI_i *material);
u32 RF_AddExplosion(const vec3_c &pos, float radius, const char *matName);
void RF_AddExplosionDrawCalls();
void RF_ShutdownExplosions();

// rf_lightGrid_debug.cpp
void RF_AddLightGridDebugModelDrawCalls();

// rf_custom.cpp - custom drawable objects
void RF_AddCustomDrawCalls();
void RF_AddCustomRenderObject(class customRenderObjectAPI_i *api);
void RF_RemoveCustomRenderObject(class customRenderObjectAPI_i *api);

// rf_cubeMap.cpp - env_cubemap support, "buildCubeMaps" command.
bool RF_LoadWorldMapCubeMaps(const char *mapName);
class rCubeMap_c *RF_FindNearestEnvCubeMap(const class vec3_c &p);
class cubeMapAPI_i *RF_FindNearestEnvCubeMap_Image(const class vec3_c &p);

// rf_staticModel.cpp
class rStaticModelAPI_i *RF_AllocStaticModel();
void RF_RemoveStaticModel(class rStaticModelAPI_i *ent);
void RF_AddStaticModelDrawCalls();
void RF_MarkStaticModelMaterials();

// rf_terrain.cpp
void RFT_InitTerrain();
void RFT_AddTerrainDrawCalls();
void RFT_ShutdownTerrain();
bool RFT_RayTraceTerrain(class trace_c &tr);

// rf_font.cpp
void RF_InitFonts();
void RF_ShutdownFonts();
class fontAPI_i *RF_RegisterFont(const char *name);

extern class cameraDef_c rf_camera;
extern int rf_curTimeMsec;
extern float rf_curTimeSeconds;
extern u32 rf_draw3DViewCount;
extern class rLightAPI_i *rf_curLightAPI;
// NULL == worldspawn
extern class rEntityAPI_i *rf_currentEntity;

#endif // __RF_LOCAL_H__
