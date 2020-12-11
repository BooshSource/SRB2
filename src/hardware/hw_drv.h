// SONIC ROBO BLAST 2
//-----------------------------------------------------------------------------
// Copyright (C) 1998-2000 by DooM Legacy Team.
// Copyright (C) 1999-2020 by Sonic Team Junior.
//
// This program is free software distributed under the
// terms of the GNU General Public License, version 2.
// See the 'LICENSE' file for more details.
//-----------------------------------------------------------------------------
/// \file hw_drv.h
/// \brief imports/exports for the 3D hardware low-level interface API

#ifndef __HWR_DRV_H__
#define __HWR_DRV_H__

// this must be here 19991024 by Kin
#include "../screen.h"
#include "hw_data.h"
#include "hw_defs.h"
#include "hw_md2.h"

#include "hw_dll.h"

// ==========================================================================
//                                                       STANDARD DLL EXPORTS
// ==========================================================================

EXPORT boolean HWRAPI(Init) (void);
#ifndef HAVE_SDL
EXPORT void HWRAPI(Shutdown) (void);
#endif
#ifdef _WINDOWS
EXPORT void HWRAPI(GetModeList) (vmode_t **pvidmodes, INT32 *numvidmodes);
#endif
EXPORT void HWRAPI(SetPalette) (RGBA_t *ppal);
EXPORT void HWRAPI(FinishUpdate) (INT32 waitvbl);
EXPORT void HWRAPI(Draw2DLine) (F2DCoord *v1, F2DCoord *v2, RGBA_t Color);
EXPORT void HWRAPI(DrawPolygon) (FSurfaceInfo *pSurf, FOutVector *pOutVerts, UINT32 iNumPts, UINT32 PolyFlags);
EXPORT void HWRAPI(DrawIndexedTriangles) (FSurfaceInfo *pSurf, FOutVector *pOutVerts, UINT32 iNumPts, UINT32 PolyFlags, UINT32 *IndexArray);
EXPORT void HWRAPI(RenderSkyDome) (FSkyDome *sky);
EXPORT void HWRAPI(SetBlend) (UINT32 PolyFlags);
EXPORT void HWRAPI(ClearBuffer) (boolean ColorMask, boolean DepthMask, FRGBAFloat *ClearColor);
EXPORT void HWRAPI(SetTexture) (HWRTexture_t *TexInfo);
EXPORT void HWRAPI(UpdateTexture) (HWRTexture_t *TexInfo);
EXPORT void HWRAPI(DeleteTexture) (HWRTexture_t *TexInfo);
EXPORT void HWRAPI(ReadRect) (INT32 x, INT32 y, INT32 width, INT32 height, INT32 dst_stride, UINT16 *dst_data);
EXPORT void HWRAPI(GClipRect) (INT32 minx, INT32 miny, INT32 maxx, INT32 maxy, float nearclip);
EXPORT void HWRAPI(ClearTextureCache) (void);

//Hurdler: added for backward compatibility
EXPORT void HWRAPI(SetState) (INT32 State, INT32 Value);

//Hurdler: added for new development
EXPORT void HWRAPI(DrawModel) (model_t *model, INT32 frameIndex, INT32 duration, INT32 tics, INT32 nextFrameIndex, FTransform *pos, float scale, UINT8 flipped, UINT8 hflipped, FSurfaceInfo *Surface);
EXPORT void HWRAPI(CreateModelVBOs) (model_t *model);
EXPORT void HWRAPI(SetTransform) (FTransform *ptransform);
EXPORT INT32 HWRAPI(GetTextureUsed) (void);

EXPORT void HWRAPI(FlushScreenTextures) (void);
EXPORT void HWRAPI(StartScreenWipe) (void);
EXPORT void HWRAPI(EndScreenWipe) (void);
EXPORT void HWRAPI(DoScreenWipe) (void);
EXPORT void HWRAPI(DrawIntermissionBG) (void);
EXPORT void HWRAPI(MakeScreenTexture) (void);
EXPORT void HWRAPI(MakeScreenFinalTexture) (void);
EXPORT void HWRAPI(DrawScreenFinalTexture) (int width, int height);

#define SCREENVERTS 10
EXPORT void HWRAPI(PostImgRedraw) (float points[SCREENVERTS][SCREENVERTS][2]);

// jimita
EXPORT boolean HWRAPI(CompileShaders) (void);
EXPORT void HWRAPI(CleanShaders) (void);
EXPORT void HWRAPI(SetShader) (int type);
EXPORT void HWRAPI(UnSetShader) (void);

EXPORT void HWRAPI(SetShaderInfo) (INT32 info, INT32 value);
EXPORT void HWRAPI(LoadCustomShader) (int number, char *code, size_t size, boolean isfragment);

// ==========================================================================
//                                      HWR DRIVER OBJECT, FOR CLIENT PROGRAM
// ==========================================================================

#if !defined (_CREATE_DLL_)

struct hwdriver_s
{
	Init                pfnInit;
	SetPalette          pfnSetPalette;
	FinishUpdate        pfnFinishUpdate;
	Draw2DLine          pfnDraw2DLine;
	DrawPolygon         pfnDrawPolygon;
	DrawIndexedTriangles    pfnDrawIndexedTriangles;
	RenderSkyDome       pfnRenderSkyDome;
	SetBlend            pfnSetBlend;
	ClearBuffer         pfnClearBuffer;
	SetTexture          pfnSetTexture;
	UpdateTexture       pfnUpdateTexture;
	DeleteTexture       pfnDeleteTexture;
	ReadRect            pfnReadRect;
	GClipRect           pfnGClipRect;
	ClearTextureCache   pfnClearTextureCache;
	SetState            pfnSetState;
	DrawModel           pfnDrawModel;
	CreateModelVBOs     pfnCreateModelVBOs;
	SetTransform        pfnSetTransform;
	GetTextureUsed      pfnGetTextureUsed;
#ifdef _WINDOWS
	GetModeList         pfnGetModeList;
#endif
#ifndef HAVE_SDL
	Shutdown            pfnShutdown;
#endif
	PostImgRedraw       pfnPostImgRedraw;
	FlushScreenTextures pfnFlushScreenTextures;
	StartScreenWipe     pfnStartScreenWipe;
	EndScreenWipe       pfnEndScreenWipe;
	DoScreenWipe        pfnDoScreenWipe;
	DrawIntermissionBG  pfnDrawIntermissionBG;
	MakeScreenTexture   pfnMakeScreenTexture;
	MakeScreenFinalTexture  pfnMakeScreenFinalTexture;
	DrawScreenFinalTexture  pfnDrawScreenFinalTexture;

	CompileShaders      pfnCompileShaders;
	CleanShaders        pfnCleanShaders;
	SetShader           pfnSetShader;
	UnSetShader         pfnUnSetShader;

	SetShaderInfo       pfnSetShaderInfo;
	LoadCustomShader    pfnLoadCustomShader;
};

extern struct hwdriver_s hwdriver;

#define HWD hwdriver

#endif //not defined _CREATE_DLL_

#endif //__HWR_DRV_H__

