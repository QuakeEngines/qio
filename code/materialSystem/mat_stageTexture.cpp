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
// mat_stageTexture.cpp
#include "mat_stageTexture.h"
#include "mat_local.h"
#include <shared/parser.h>
#include <api/coreAPI.h>
#include <api/textureAPI.h>
#include <shared/textureWrapMode.h>
#include <api/vfsAPI.h>

// http://wiki.splashdamage.com/index.php/Materials
const char *imageOps [] = {
	"addNormals",
	"heightmap",
	"makealpha",
	"add",
	"scale",
	"invertAlpha",
	"invertColor",
	"makeIntensity",
	"makeAlpha",
};

u32 numImageOps = sizeof(imageOps)/sizeof(imageOps[0]);

inline void parseTextureName(str &out, parser_c &p) {
	// first check for image operator commands which may have whitespaces in syntex
	// (they were added for Doom3)
	for(u32 i = 0; i < numImageOps; i++) {
		const char *opText = imageOps[i];
		if(p.atWord_dontNeedWS(opText)) {
			out = opText;
			p.getBracedBlock();
			out.append(p.getLastStoredToken());
			return; // done
		}
	}

	// no image operators, get texture file name
	out = p.getToken();
}

void textureAnimation_c::uploadTextures() {
	unloadTextures();
	textures.resize(texNames.size());
	for(u32 i = 0; i < texNames.size(); i++) {
		const char *tName = texNames[i];
		textureAPI_i *t = MAT_RegisterTexture(tName,TWM_REPEAT);
		textures[i] = t;
	}
}
void textureAnimation_c::unloadTextures() {
	for(u32 i = 0; i < textures.size(); i++) {
		//MAT_FreeTexture(&textures[i]);
	}
}
textureAnimation_c::~textureAnimation_c() {
	unloadTextures();
}
bool textureAnimation_c::parseAnimMapDir(parser_c &p) {
	frequency = p.getFloat();
	if(frequency == 0) {
		g_core->RedWarning("textureAnimation_c::parseAnimMapDir: frequency is %s (see line %i of file %s)\n",p.getLastStoredToken(),p.getCurrentLineNumber(),p.getDebugFileName());
		return true; // error
	}
	str dir = p.getNextWordInLine();
	return loadAnimMapImagesFromDirectory(dir);
}
bool textureAnimation_c::loadAnimMapImagesFromDirectory(const char *dir) {
	int count = 0;
	char **list = g_vfs->FS_ListFiles(dir,0,&count);
	for(u32 i = 0; i < count; i++) {
		str f = dir;
		f.appendChar('/');
		f.append(list[i]);
		texNames.push_back(f);
	}
	g_vfs->FS_FreeFileList(list);
	if(count == 0) {
		g_core->RedWarning("textureAnimation_c::loadAnimMapImagesFromDirectory: no textures found in %s, animMap will not work.\n",dir);
		return true;
	}
	return false;
}
bool textureAnimation_c::parseAnimMap(parser_c &p) {
	frequency = p.getFloat();
	if(frequency == 0) {
		g_core->RedWarning("textureAnimation_c::parseAnimMap: frequency is %s (see line %i of file %s)\n",p.getLastStoredToken(),p.getCurrentLineNumber(),p.getDebugFileName());
		return true; // error
	}
	while(p.getNextWordInLine()) {
		const char *imgName = p.getLastStoredToken();
		//g_core->Print("Img %i is %s\n",texNames.size(),imgName);
		texNames.push_back(imgName);
	}
	if(texNames.size() == 1) {
		str dir = texNames[0];
		texNames.clear();
		return loadAnimMapImagesFromDirectory(dir);
	}
	return false; // no error
}
textureAPI_i *textureAnimation_c::getTexture(u32 idx) {
	if(idx >= textures.size()) {
		return MAT_GetDefaultTexture();
	}
	return textures[idx];
}
textureAPI_i *textureAnimation_c::getTextureForTime(float time) {
	if(textures.size() == 0)
		return MAT_GetDefaultTexture();; // avoid integer division by 0
	int idx = int(time * frequency * 1024);
	idx >>= 10;
	if(idx<0)
		idx = 0;
	idx %= textures.size();
	return textures[idx];
}
stageTexture_c::stageTexture_c() {
	singleTexture = 0;
	animated = 0;
	bClamp = false;
}
void stageTexture_c::uploadTexture() {
	unloadTexture();
	if(animated) {
		animated->uploadTextures();
	}
	if(mapName.length() == 0 || !_stricmp(mapName,"$lightmap")) {
		return;
	}
	if(this->bClamp) {
		singleTexture = MAT_RegisterTexture(mapName,TWM_CLAMP);
	} else {
		singleTexture = MAT_RegisterTexture(mapName,TWM_REPEAT);
	}
}
void stageTexture_c::unloadTexture() {
	if(singleTexture) {
		// NOTE: MAT_FreeTexture will not crash even if 
		// singleTexture ptr points to r_defaultTexture 
		//MAT_FreeTexture(&singleTexture);
		singleTexture = 0;
	}
	if(animated) {
		animated->unloadTextures();
	}
}
stageTexture_c::~stageTexture_c() {
	unloadTexture();
	if(animated) {
		 delete animated;
	}
}
bool stageTexture_c::isAnimated() const {
	if(animated == 0) {
		return false;
	}
	return true; 
}
bool stageTexture_c::hasTexture() const {
	if(animated || singleTexture) {
		return true;
	}
	return false;
}
bool stageTexture_c::parseMap(parser_c &p) {
#if 0
	mapName = p.getWord();
#else
	// handle Doom3 texture modifiers as well
	parseTextureName(mapName,p);
#endif
	return false; // no error
}
bool stageTexture_c::parseAnimMap(parser_c &p) {
	if(animated == 0) {
		animated = new textureAnimation_c;
	}
	return animated->parseAnimMap(p);	
}
bool stageTexture_c::parseAnimMapDir(parser_c &p) {
	if(animated == 0) {
		animated = new textureAnimation_c;
	}
	return animated->parseAnimMapDir(p);	
}
bool stageTexture_c::isLightmap() const {
	if(!_stricmp(mapName,"$lightmap")) {
		return true;
	}
	return false;
}
void stageTexture_c::setDefaultTexture() {
	singleTexture = MAT_GetDefaultTexture();
}
textureAPI_i *stageTexture_c::getAnyTexture() const {
	if(singleTexture)
		return singleTexture;
	if(animated) {
		return animated->getTexture(0);
	}
	//return 0;
	return MAT_GetDefaultTexture();
}
textureAPI_i *stageTexture_c::getTexture(float time) const {
	if(singleTexture)
		return singleTexture;
	if(animated) {
		return animated->getTextureForTime(time);
	}
	//return 0;
	return MAT_GetDefaultTexture();
}
textureAPI_i *stageTexture_c::getTextureForFrameNum(u32 frameNum) const {
	if(singleTexture)
		return singleTexture;
	if(animated) {
		return animated->getTexture(frameNum);
	}
	//return 0;
	return MAT_GetDefaultTexture();
}
void stageTexture_c::fromTexturePointer(textureAPI_i *newTexturePtr) {
	unloadTexture();
	this->singleTexture = newTexturePtr;
	this->mapName = newTexturePtr->getName();
}
bool stageTexture_c::isEmpty() const {
	if(mapName.length())
		return false;
	if(animated)
		return false;
	return true; // nothing loaded
}
void stageTexture_c::setBClamp(bool newBClamp) {
	bClamp = newBClamp;
}
u32 stageTexture_c::getNumFrames() const {
	if(animated) {
		return animated->getNumFrames();
	}
	return 1;
}
