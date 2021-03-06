#ifndef GLHELP_H
#define GLHELP_H

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2ext.h>

/// Some gl extensions that don't seem to be part of raspberry gl. 
/// I think you could get these from other places like GLAD or libepoxy.
///

//EGLAPI EGLImageKHR EGLAPIENTRY eglCreateImageKHR (EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list);
//EGLAPI EGLBoolean EGLAPIENTRY eglDestroyImageKHR (EGLDisplay dpy, EGLImageKHR image);
EGLAPI EGLImageKHR EGLAPIENTRY eglCreateImageKHR(EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list) __attribute__((weak)); // May not be in libEGL symbol table, resolve manually :(
EGLAPI EGLImageKHR EGLAPIENTRY eglCreateImageKHR(EGLDisplay dpy, EGLContext ctx, EGLenum target, EGLClientBuffer buffer, const EGLint *attrib_list)
{
	static PFNEGLCREATEIMAGEKHRPROC createImageProc = 0;
	if(!createImageProc) {
		createImageProc = (PFNEGLCREATEIMAGEKHRPROC)eglGetProcAddress("eglCreateImageKHR");
	}
	return createImageProc(dpy, ctx, target, buffer, attrib_list);
}

EGLBoolean eglDestroyImageKHR(EGLDisplay dpy, EGLImageKHR image) __attribute__((weak)); // May not be in libEGL symbol table, resolve manually :(
EGLBoolean eglDestroyImageKHR(EGLDisplay dpy, EGLImageKHR image)
{
	static PFNEGLDESTROYIMAGEKHRPROC destroyImageProc = 0;
	if(!destroyImageProc) {
		destroyImageProc = (PFNEGLDESTROYIMAGEKHRPROC)eglGetProcAddress("eglDestroyImageKHR");
	}
	return destroyImageProc(dpy, image);
}

void glDebugMessageCallbackKHR(GLDEBUGPROCKHR callback, const void *userParam) __attribute__((weak)); // May not be in libEGL symbol table, resolve manually :(
void glDebugMessageCallbackKHR(GLDEBUGPROCKHR callback, const void *userParam)
{
	static PFNGLDEBUGMESSAGECALLBACKKHRPROC debugMessageCallbackProc = 0;
	if(!debugMessageCallbackProc) {
		debugMessageCallbackProc = (PFNGLDEBUGMESSAGECALLBACKKHRPROC)eglGetProcAddress("glDebugMessageCallbackKHR");
	}
	debugMessageCallbackProc(callback, userParam);
}


void glEGLImageTargetTexture2DOES(GLenum target, GLeglImageOES image) __attribute__((weak)); // May not be in libEGL symbol table, resolve manually :(
void glEGLImageTargetTexture2DOES(GLenum target, GLeglImageOES image)
{
	static PFNGLEGLIMAGETARGETTEXTURE2DOESPROC imageTargetTexture2DOES = 0;
	if(!imageTargetTexture2DOES) {
		imageTargetTexture2DOES = (PFNGLEGLIMAGETARGETTEXTURE2DOESPROC)eglGetProcAddress("glEGLImageTargetTexture2DOES");
	}
	imageTargetTexture2DOES(target, image);
}
/// END Gl Extensions --------------------------------------------------



#endif
