#ifndef DEF_TEXTURE
#define DEF_TEXTURE

//#include <GLES3/gl3.h>
//#include <GLES2/gl2ext.h>
#include <epoxy/egl.h>
//#include <EGL/eglext.h>
#include <epoxy/gl.h>
#include <interface/vcsm/user-vcsm.h>
#include <cstring>

#include "shader.hpp"

struct egl_image_brcm_vcsm_info {
   unsigned width;
   unsigned height;
   unsigned int vcsm_handle;
};
#define EGL_IMAGE_BRCM_VCSM              0x99930C3
/*
 * Abstract GL Texture
 */
class Texture
{
	public:
	int width, height;

	virtual void setSource (ShaderProgram *shader, int slot) = 0;
};

/*
 * External EGL Texture
 */
class ExternalTexture : public Texture
{
	public:
	ExternalTexture (GLint texHandle, int Width, int Height);
	virtual void setSource (ShaderProgram *shader, int slot) override;

	protected:
	GLuint ID;
};
/*
 * Abstract Render Target
 */
class RenderTarget : public Texture
{
	public:
	virtual void setTarget (void) = 0;
	virtual void setSource (ShaderProgram *shader, int slot) = 0;

	protected:
	GLuint FBO_ID;
};

/*
 * A simple texture target with one color buffer (read-write)
 */
class FrameRenderTarget : public RenderTarget
{
	public:
	FrameRenderTarget (int Width, int Height, GLenum format, GLenum type);
	~FrameRenderTarget (void);
	void setTarget (void) override;
	void setSource (ShaderProgram *shader, int slot) override;

	private:
	GLuint colorBuffer_ID;
};

/*
 * A simple RenderBuffer target with one color buffer (write-only)
 */
class BufferRenderTarget : public RenderTarget
{
	public:
	BufferRenderTarget (int Width, int Height, GLenum format);
	~BufferRenderTarget (void);
	void setTarget (void) override;
	void setSource (ShaderProgram *shader, int slot) override;

	private:
	GLuint colorBuffer_ID;
};

/*
 * A VCOS shared memory render target with one RGBA buffer (read-write)
 * VCOS only support POT textures, so only a part will be used
 */
class VCSMRenderTarget : public RenderTarget
{
	public:
	int bufferWidth, bufferHeight;
	VCSMRenderTarget (int Width, int Height, EGLDisplay Display);
	~VCSMRenderTarget (void);
	void setTarget (void) override;
	void setSource (ShaderProgram *shader, int slot) override;
	uint8_t* lock(void);
	void unlock(void);
	
	private:
	GLuint TEX_ID;
	egl_image_brcm_vcsm_info VCSM;
	EGLImageKHR eglImg;
	uint8_t *vcsmBuffer;
	EGLDisplay eglDisplay;
};

#endif
