#ifndef __MAT_PUBLIC_H__
#define __MAT_PUBLIC_H__

#include <shared/typedefs.h>

// material stage type.
enum stageType_e {
	ST_NOT_SET,
	ST_LIGHTMAP, // draw only lightmap (0th texture slot)
	ST_COLORMAP, // draw only colormap (0th texture slot)
	ST_COLORMAP_LIGHTMAPPED, // draw lightmapped colormap (colormap at slot 0, lightmap at slot 1)
	// added for Doom3
	ST_BUMPMAP, // normal map
	ST_SPECULARMAP,
	// added by me, heightmaps are not used directly in Doom3
	// (they are converted to bump maps)
	ST_HEIGHTMAP,
	// This is an RGBA image with bumpmap in RGB channels
	// and heightmap in Alpha channel
	ST_BUMPHEIGHTMAP,
	// skybox stage (with a cubemap texture)
	// Set by "stage skyboxmap" in material,
	// also set by Doom3 "texgen skybox" command.
	// Used in Doom3 sky materials.
	// Also used for sky in test_tree.pk3.
	ST_CUBEMAP_SKYBOX,
	// glass reflection stage (with a cubemap texture)
	// Set by "stage reflectionMap" in material,
	// also set by Doom3 "texgen reflect" command.
	// Used in Doom3 glass materials.
	ST_CUBEMAP_REFLECTION,
	// this will automatically use nearest 'env_cubemap' for reflections
	ST_ENV_CUBEMAP,
	// only for editor (qer_editorImage)
	ST_EDITORIMAGE,
	// for terrain... blending some textures together in pixel shader
	ST_BLENDMAP,
};

// hardcoded alpha func test values (for non-blended transparency)
enum alphaFunc_e {
	// Quake3 alphaFuncs
	AF_NONE,
	AF_GT0,
	AF_LT128,
	AF_GE128,
	// Doom3 "alphaTest" <expression>
	// (The expression is evaluated at runtime)
	AF_D3_ALPHATEST,
};

// texCoordGens automatically
// overwrites existing texcoords
enum texCoordGen_e {
	TCG_NONE,
	TCG_ENVIRONMENT,
	// added for Doom3
	//TCG_SKYBOX,
	//TCG_REFLECT,
	TCG_NUM_GENS,
};

// vertex color generator (red, green, blue)
enum rgbGen_e {
	RGBGEN_NONE,
	RGBGEN_WAVE,
	RGBGEN_VERTEX,
	RGBGEN_CONST,
	RGBGEN_IDENTITY,
	RGBGEN_IDENTITYLIGHTING,
	RGBGEN_STATIC,
	RGBGEN_LIGHTINGSPHERICAL,
	RGBGEN_EXACTVERTEX,
	RGBGEN_CONSTLIGHTING,
	RGBGEN_LIGHTINGDIFFUSE,
	// now D3 rgbgens:
	RGBGEN_AST, // one D3 material script expression for r,g,b
};

// TODO
enum alphaGen_e {
	ALPHAGEN_NOT_SET,
	ALPHAGEN_VERTEX,
};

// blend modes; abstracted so they can apply to both opengl and dx
// if you edit this enum, remember to mirror your changes in blendModeEnumToGLBlend array.
enum blendMode_e {
	BM_NOT_SET,
	BM_ZERO,
	BM_ONE,
	BM_ONE_MINUS_SRC_COLOR,
	BM_ONE_MINUS_DST_COLOR,
	BM_ONE_MINUS_SRC_ALPHA,
	BM_ONE_MINUS_DST_ALPHA,
	BM_DST_COLOR,
	BM_DST_ALPHA,
	BM_SRC_COLOR,
	BM_SRC_ALPHA,
	BM_SRC_ALPHA_SATURATE,

	BM_NUM_BLEND_TYPES,
};

struct blendDef_s {
	u16 src;
	u16 dst;

	blendDef_s() {
		src = BM_NOT_SET;
		dst = BM_NOT_SET;
	}
	bool isNonZero() const {
		if(src)
			return true;
		if(dst)
			return true;
		return false;
	}
};

class skyBoxAPI_i {
public:
	virtual class textureAPI_i *getUp() const = 0;
	virtual class textureAPI_i *getDown() const = 0;
	virtual class textureAPI_i *getRight() const = 0;
	virtual class textureAPI_i *getLeft() const = 0;
	virtual class textureAPI_i *getFront() const = 0;
	virtual class textureAPI_i *getBack() const = 0;

	virtual bool isValid() const = 0;
};

class skyParmsAPI_i {
public:
	virtual float getCloudHeight() const = 0;
	virtual const skyBoxAPI_i *getFarBox() const = 0;
	virtual const skyBoxAPI_i *getNearBox() const = 0;
};

class sunParmsAPI_i {
public:
	virtual const class vec3_c &getSunDir() const = 0;
	virtual const class vec3_c &getSunColor() const = 0;
};

#endif // __MAT_PUBLIC_H__
