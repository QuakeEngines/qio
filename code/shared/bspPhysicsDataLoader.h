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
// bspPhysicsDataLoader.h - simple loader for bsp brushes/surfaces
// This is for physics system only, so texture coordinate, vertex normals,
// lightmaps, etc are ignored.
#ifndef __BSPPHYSICSDATALOADER_H__
#define __BSPPHYSICSDATALOADER_H__

#include "typedefs.h"
#include "array.h"
#include "str.h"

class bspPhysicsDataLoader_c {
	struct q3Header_s *h;
	str fileName;

	u32 getMaterialContentFlags(u32 matNum) const;
public:
	bspPhysicsDataLoader_c();
	~bspPhysicsDataLoader_c();

	void clear();
	bool loadBSPFile(const char *fname);

	const char *getFileName() const {
		return fileName;
	}

	void nodeBrushes_r(int nodeNum, arraySTD_c<u32> &out) const;
	void iterateModelBrushes(u32 modelNum, void (*perBrushCallback)(u32 brushNum, u32 contentFlags));
	void iterateModelTriSurfs(u32 modelNum, void (*perSurfCallback)(u32 surfNum, u32 contentFlags));
	void iterateModelBezierPatches(u32 modelNum, void (*perBezierPatchCallback)(u32 surfNum, u32 contentFlags));
	void iterateModelDisplacementSurfaces(u32 modelNum, void (*perDisplacementSurfaceCallback)(u32 surfNum, u32 contentFlags));
	void iterateStaticProps(void (*perStaticPropCallback)(u32 propNum, u32 contentFlags));

	void iterateModelBrushes2(u32 modelNum, class brushCreatorAPI_i *callback);

	void iterateBrushPlanes(u32 brushNum, void (*sideCallback)(const float planeEq[4])) const;
	void iterateBrushPlanes(u32 brushNum, class perPlaneCallbackListener_i *callBack) const;
	void convertBezierPatchToTriSurface(u32 surfNum, u32 tesselationLevel, class cmSurface_c &out) const;
	void convertDisplacementToTriSurface(u32 surfNum, class cmSurface_c &out) const;
	void convertStaticPropToSurface(u32 staticPropNum, class cmSurface_c &out) const;
	void getTriangleSurface(u32 surfNum, class cmSurface_c &out) const;

	u32 getNumInlineModels() const;
	void getInlineModelBounds(u32 modelNum, class aabb &bb) const;
	u32 getInlineModelBrushCount(u32 modelNum) const;
	u32 getInlineModelSurfaceCount(u32 modelNum) const;
	u32 getInlineModelNonBrushSurfacesCount(u32 modelNum) const;
	u32 getInlineModelGlobalBrushIndex(u32 subModelNum, u32 localBrushIndex) const;
	u32 getInlineModelFirstSurface(u32 modelNum) const;
	int getSurfaceType(u32 sfNum) const;

	bool isCoD1BSP() const;
	bool isHLBSP() const;
};

#endif // __BSPPHYSICSDATALOADER_H__
