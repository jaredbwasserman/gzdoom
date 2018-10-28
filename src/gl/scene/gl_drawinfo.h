#ifndef __GL_DRAWINFO_H
#define __GL_DRAWINFO_H

#include "hwrenderer/scene/hw_drawlist.h"
#include "hwrenderer/scene/hw_weapon.h"
#include "hwrenderer/scene/hw_viewpointuniforms.h"

#include "gl/renderer/gl_renderstate.h"	// temporary

#ifdef _MSC_VER
#pragma warning(disable:4244)
#endif

enum DrawListType
{
	GLDL_PLAINWALLS,
	GLDL_PLAINFLATS,
	GLDL_MASKEDWALLS,
	GLDL_MASKEDFLATS,
	GLDL_MASKEDWALLSOFS,
	GLDL_MODELS,
	
	GLDL_TRANSLUCENT,
	GLDL_TRANSLUCENTBORDER,
	
	GLDL_TYPES,
};


struct FDrawInfo : public HWDrawInfo
{
	HWDrawList drawlists[GLDL_TYPES];
	int vpIndex;
	
	void ApplyVPUniforms() override;

	void AddWall(GLWall *wall) override;
    void AddMirrorSurface(GLWall *w) override;
	void AddFlat(GLFlat *flat, bool fog) override;
	void AddSprite(GLSprite *sprite, bool translucent) override;

	int UploadLights(FDynLightData &data) override;

	void Draw(EDrawType dt, FRenderState &state, int index, int count, bool apply = true) override;
	void DrawIndexed(EDrawType dt, FRenderState &state, int index, int count, bool apply = true) override;
	void RenderPortal(HWPortal *p, bool stencil) override;

	void SetDepthMask(bool on) override;
	void SetDepthFunc(int func) override;
	void SetDepthRange(float min, float max) override;
	void EnableDrawBufferAttachments(bool on) override;
	void SetStencil(int offs, int op, int flags) override;
	void SetCulling(int mode) override;
	void EnableClipDistance(int num, bool state) override;

	void StartScene();

	void AddSubsectorToPortal(FSectorPortalGroup *portal, subsector_t *sub) override;
    
    void CreateScene();
    void RenderScene(int recursion);
    void RenderTranslucent();
    void DrawScene(int drawmode) override;
    void ProcessScene(bool toscreen = false);
    void EndDrawScene(sector_t * viewsector);
    void DrawEndScene2D(sector_t * viewsector);
	bool SetDepthClamp(bool on) override;
	void ClearScreen() override;

	static FDrawInfo *StartDrawInfo(FRenderViewpoint &parentvp, HWViewpointUniforms *uniforms);
	FDrawInfo *EndDrawInfo();
};
#endif
