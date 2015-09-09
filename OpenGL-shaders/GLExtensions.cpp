#include "stdafx.h"
#include "GLExtensions.h"

PFNGLDELETEOBJECTARBPROC glDeleteObjectARB;
PFNGLGETHANDLEARBPROC glGetHandleARB;
PFNGLDETACHOBJECTARBPROC glDetachObjectARB;
PFNGLCREATESHADEROBJECTARBPROC glCreateShaderObjectARB;
PFNGLSHADERSOURCEARBPROC glShaderSourceARB;
PFNGLCOMPILESHADERARBPROC glCompileShaderARB;
PFNGLCREATEPROGRAMOBJECTARBPROC glCreateProgramObjectARB;
PFNGLATTACHOBJECTARBPROC glAttachObjectARB;
PFNGLLINKPROGRAMARBPROC glLinkProgramARB;
PFNGLUSEPROGRAMOBJECTARBPROC glUseProgramObjectARB;
PFNGLVALIDATEPROGRAMARBPROC glValidateProgramARB;
PFNGLGETINFOLOGARBPROC glGetInfoLogARB;

void QueryGLExtFunctionPointers()
{
	 glDeleteObjectARB= (PFNGLDELETEOBJECTARBPROC) wglGetProcAddress("glDeleteObjectARB");
	 glGetHandleARB= (PFNGLGETHANDLEARBPROC) wglGetProcAddress("glGetHandleARB");
	 glDetachObjectARB= (PFNGLDETACHOBJECTARBPROC)  wglGetProcAddress("glDetachObjectARB");
	 glCreateShaderObjectARB= (PFNGLCREATESHADEROBJECTARBPROC) wglGetProcAddress("glCreateShaderObjectARB");
	 glShaderSourceARB= (PFNGLSHADERSOURCEARBPROC) wglGetProcAddress("glShaderSourceARB");
	 glCompileShaderARB= (PFNGLCOMPILESHADERARBPROC) wglGetProcAddress("glCompileShaderARB");
	 glCreateProgramObjectARB= (PFNGLCREATEPROGRAMOBJECTARBPROC) wglGetProcAddress("glCreateProgramObjectARB");
	 glAttachObjectARB= (PFNGLATTACHOBJECTARBPROC) wglGetProcAddress("glAttachObjectARB");
	 glLinkProgramARB= (PFNGLLINKPROGRAMARBPROC) wglGetProcAddress("glLinkProgramARB");
	 glUseProgramObjectARB= (PFNGLUSEPROGRAMOBJECTARBPROC) wglGetProcAddress("glUseProgramObjectARB");
	 glValidateProgramARB= (PFNGLVALIDATEPROGRAMARBPROC) wglGetProcAddress("glValidateProgramARB");
	 glGetInfoLogARB= (PFNGLGETINFOLOGARBPROC) wglGetProcAddress("glGetInfoLogARB");
}