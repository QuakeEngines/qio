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
// img_api.cpp - image loader interface

#include "img_local.h"
#include <api/iFaceMgrAPI.h>
#include <api/vfsAPI.h>
#include <api/cvarAPI.h>
#include <api/coreAPI.h>
#include <api/imgAPI.h>

class imgAPIImpl_c : public imgAPI_i {
	virtual void getDefaultImage(byte **outData, u32 *outW, u32 *outH) {
		IMG_GetDefaultImage(outData,outW,outH);
	}
	virtual const char *loadImage(const char *fname, byte **outData, u32 *outW, u32 *outH) {
		const char *ret = IMG_LoadImageInternal(fname,outData,outW,outH);
#if 0
		if(outData && *outData && *outW) {
			writeWebPLossless("webptest.webp",*outData,*outW,*outH,4);
		}
#endif
		return ret;
	}
	virtual void freeImageData(byte *data) {
		free(data);
	}
	virtual void convert8BitImageToRGBA32(byte **converted, u32 *outWidth, u32 *outHeight, const byte *pixels, u32 width, u32 height, const byte *palette) {
		return IMG_Convert8BitImageToRGBA32(converted, outWidth, outHeight, pixels,width,height,palette);
	}	
	virtual void rotatePic(byte *pic, u32 w) {
		IMG_RotatePic(pic,w);
	}
	virtual void horizontalFlip(byte *pic, u32 w, u32 h) {
		IMG_HorizontalFlip(pic,w,h);
	}
	virtual void verticalFlip(byte *pic, u32 w, u32 h) {
		IMG_VerticalFlip(pic,w,h);
	}
	virtual bool writeTGA(const char *fname, byte *pic, u32 width, u32 height, u32 bpp) {
		return IMG_WriteTGA(fname,pic,width,height,bpp);
	}
	virtual bool writeWebPLossless(const char *fname, byte *pic, u32 width, u32 height, u32 bpp) {
		return IMG_SaveWEBPLossless(fname,pic,width,height,bpp);
	}
};

// interface manager (import)
class iFaceMgrAPI_i *g_iFaceMan = 0;
// imports
vfsAPI_s *g_vfs = 0;
cvarsAPI_s *g_cvars = 0;
coreAPI_s *g_core = 0;
// exports
static imgAPIImpl_c g_staticMaterialSystemAPI;
imgAPI_i *g_img = &g_staticMaterialSystemAPI;

void ShareAPIs(iFaceMgrAPI_i *iFMA) {
	g_iFaceMan = iFMA;

	// exports
	g_iFaceMan->registerInterface((iFaceBase_i *)(void*)g_img,IMG_API_IDENTSTR);

	// imports
	g_iFaceMan->registerIFaceUser(&g_vfs,VFS_API_IDENTSTR);
	g_iFaceMan->registerIFaceUser(&g_cvars,CVARS_API_IDENTSTR);
	g_iFaceMan->registerIFaceUser(&g_core,CORE_API_IDENTSTR);

	IMG_InitDevil();
}

qioModule_e IFM_GetCurModule() {
	return QMD_IMAGELIB;
}

