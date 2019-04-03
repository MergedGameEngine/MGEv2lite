


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#include "GL/glew.h"
#include <GL/gl.h>
#include <GL/glx.h>
#include <sys/time.h>
#include <unistd.h>

//#define _DOOM_powered_by_MGEv2_


#ifdef _DOOM_powered_by_MGEv2_

#include "_DOOM_with_MGEv2/DOOMcvt.h"

#else

#include "./_MGEv1_Test/RendererOutput.h"

#endif

GLboolean stereo = GL_FALSE;	/* Enable stereo.  */
GLint samples = 0;               /* Choose visual with at least N samples. */

void _XSetNoBorder( Display *dpy, Window w) {
	static const unsigned MWM_HINTS_DECORATIONS = (1 << 1);
	static const int PROP_MOTIF_WM_HINTS_ELEMENTS = 5;

	typedef struct {
		unsigned long       flags;
		unsigned long       functions;
		unsigned long       decorations;
		long                inputMode;
		unsigned long       status;
	} PropMotifWmHints;

	PropMotifWmHints motif_hints;
	Atom prop, proptype;
	unsigned long flags = 0;

	/* setup the property */
	motif_hints.flags = MWM_HINTS_DECORATIONS;
	motif_hints.decorations = flags;

	/* get the atom for the property */
	prop = XInternAtom( dpy, "_MOTIF_WM_HINTS", True );
	if (!prop) {
		/* something went wrong! */
		return;
	}

	/* not sure this is correct, seems to work, XA_WM_HINTS didn't work */
	proptype = prop;

	XChangeProperty(	dpy, w,                         /* display, window */
				prop, proptype,                 /* property, type */
				32,                             /* format: 32-bit datums */
				PropModeReplace,                /* mode */
				(unsigned char *) &motif_hints, /* data */
				PROP_MOTIF_WM_HINTS_ELEMENTS    /* nelements */
			);
}

void __XCreateWindow(		Display *dpy, const char *name,
				int x, int y, int width, int height,
				Window *winRet, GLXContext *ctxRet, VisualID *visRet) {
	int attribs[64];
	int i = 0;

	int scrnum;
	XSetWindowAttributes attr;
	unsigned long mask;
	Window root;
	Window win;
	GLXContext ctx;
	XVisualInfo *visinfo;

	/* Singleton attributes. */
	attribs[i++] = GLX_RGBA;
	attribs[i++] = GLX_DOUBLEBUFFER;
	if (stereo)
		attribs[i++] = GLX_STEREO;

	/* Key/value attributes. */
	attribs[i++] = GLX_RED_SIZE;
	attribs[i++] = 1;
	attribs[i++] = GLX_GREEN_SIZE;
	attribs[i++] = 1;
	attribs[i++] = GLX_BLUE_SIZE;
	attribs[i++] = 1;
	attribs[i++] = GLX_DEPTH_SIZE;
	attribs[i++] = 1;
	if (samples > 0) {
		attribs[i++] = GLX_SAMPLE_BUFFERS;
		attribs[i++] = 1;
		attribs[i++] = GLX_SAMPLES;
		attribs[i++] = samples;
	}

	attribs[i++] = None;

	scrnum = DefaultScreen( dpy );
	root = RootWindow( dpy, scrnum );

	visinfo = glXChooseVisual(dpy, scrnum, attribs);
	if (!visinfo) {
		printf("Error: couldn't get an RGB, Double-buffered");
		if (stereo)
			printf(", Stereo");
		if (samples > 0)
			printf(", Multisample");
		printf(" visual\n");
		exit(1);
	}

	/* window attributes */
	attr.background_pixel = 0;
	attr.border_pixel = 0;
	attr.colormap = XCreateColormap( dpy, root, visinfo->visual, AllocNone);
	attr.event_mask = StructureNotifyMask | ExposureMask | KeyPressMask |
		PointerMotionMask | Button1MotionMask;//| ButtonPressMask | ButtonReleaseMask;
	/* XXX this is a bad way to get a borderless window! */
	mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask ;//| CWCursor;

	win = XCreateWindow( dpy, root, x, y, width, height,
			     0, visinfo->depth, InputOutput,
			     visinfo->visual, mask, &attr );

	// fullscreen
	_XSetNoBorder(dpy, win);

	/* set hints and properties */
	{
		XSizeHints sizehints;
		sizehints.x = x;
		sizehints.y = y;
		sizehints.width  = width;
		sizehints.height = height;
		sizehints.flags = USSize | USPosition;
		XSetNormalHints(dpy, win, &sizehints);
		XSetStandardProperties(dpy, win, name, name, None, (char **)NULL, 0, &sizehints);
	}
	
	ctx = glXCreateContext( dpy, visinfo, NULL, True );
	if (!ctx) {
		printf("Error: glXCreateContext failed\n");
		exit(1);
	}

	*winRet = win;
	*ctxRet = ctx;
	*visRet = visinfo->visualid;

	XFree(visinfo);
}


/**
 * Determine whether or not a GLX extension is supported.
 */
int is_glx_extension_supported(Display *dpy, const char *query) {
	const int scrnum = DefaultScreen(dpy);
	const char *glx_extensions = NULL;
	const size_t len = strlen(query);
	const char *ptr;

	if (glx_extensions == NULL) {
		glx_extensions = glXQueryExtensionsString(dpy, scrnum);
	}

	ptr = strstr(glx_extensions, query);
	return ((ptr != NULL) && ((ptr[len] == ' ') || (ptr[len] == '\0')));
}


/**
 * Attempt to determine whether or not the display is synched to vblank.
 */
void query_vsync(Display *dpy, GLXDrawable drawable) {
	int interval = 0;

#if defined(GLX_EXT_swap_control)
	if (is_glx_extension_supported(dpy, "GLX_EXT_swap_control")) {
		unsigned int tmp = -1;
		glXQueryDrawable(dpy, drawable, GLX_SWAP_INTERVAL_EXT, &tmp);
		interval = tmp;
	} else
#endif
	if (is_glx_extension_supported(dpy, "GLX_MESA_swap_control")) {
		PFNGLXGETSWAPINTERVALMESAPROC pglXGetSwapIntervalMESA =
			(PFNGLXGETSWAPINTERVALMESAPROC)
			glXGetProcAddressARB((const GLubyte *) "glXGetSwapIntervalMESA");

		interval = (*pglXGetSwapIntervalMESA)();
	} else if (is_glx_extension_supported(dpy, "GLX_SGI_swap_control")) {
		/* The default swap interval with this extension is 1.  Assume that it
		 * is set to the default.
		 *
		 * Many Mesa-based drivers default to 0, but all of these drivers also
		 * export GLX_MESA_swap_control.  In that case, this branch will never
		 * be taken, and the correct result should be reported.
		 */
		interval = 1;
	}


	if (interval > 0) {
		printf("Running synchronized to the vertical refresh.  The framerate should be\n");
		if (interval == 1) {
		   printf("approximately the same as the monitor refresh rate.\n");
		} else if (interval > 1) {
		   printf("approximately 1/%d the monitor refresh rate.\n",
			  interval);
		}
	}
}

double GetCurrentTime(void) {
   struct timeval tv;
#ifdef __VMS
   (void) gettimeofday(&tv, NULL );
#else
   struct timezone tz;
   (void) gettimeofday(&tv, &tz);
#endif
   return (double) tv.tv_sec + tv.tv_usec / 1000000.0;
}

void draw_frame(Display *dpy, Window win) {
	static int frames = 0;
	static double tRot0 = -1.0, tRate0 = -1.0;
	double dt, t = GetCurrentTime();

#ifdef _DOOM_powered_by_MGEv2_

	DOOM___RenderScene();
	
#else

	___DoAnimation();
	___SetVarParam();
	___RenderScene();


#endif

	glXSwapBuffers(dpy, win);

	frames++;

	if (tRate0 < 0.0)
		tRate0 = t;
	if (t - tRate0 >= 5.0) {
		GLfloat seconds = t - tRate0;
		GLfloat fps = frames / seconds;
		printf("%d frames in %3.1f seconds = %6.3f FPS\n", frames, seconds, fps);
		fflush(stdout);
		tRate0 = t;
		frames = 0;
	}
}



/* new window size or exposure */
void _XChangeSize(int width, int height) {
	glViewport(0, 0, (GLint) width, (GLint) height);

	if (stereo) {
		GLfloat w;

//      asp = (GLfloat) height / (GLfloat) width;
//      w = fix_point * (1.0 / 5.0);
//
//      left = -5.0 * ((w - 0.5 * eyesep) / fix_point);
//      right = 5.0 * ((w + 0.5 * eyesep) / fix_point);
	} else 
	{
		GLfloat h = (GLfloat) height / (GLfloat) width;

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-1.0, 1.0, -h, h, 5.0, 60.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -40.0);
}
   


/** Event handler results: */
#define NOP 0
#define EXIT 1
#define DRAW 2

int _XMessageHandler(Display *dpy, Window win, XEvent *event) {
	(void) dpy;
	(void) win;

	switch (event->type) {
		case Expose:
			return DRAW;
		case ConfigureNotify:
			//_XChangeSize(event->xconfigure.width, event->xconfigure.height);
			break;
		case KeyPress:
			{
				char buffer[10];
				int code;
				code = XLookupKeysym(&event->xkey, 0);
				if (code == XK_Left) {
				}
				else if (code == XK_Right) {
				}
				else if (code == XK_Up) {
				}
				else if (code == XK_Down) {
				}
				else {
					XLookupString(&event->xkey, buffer, sizeof(buffer), NULL, NULL);
					if (buffer[0] == 27) {
						/* escape */
						return EXIT;
					} else {

#ifdef _DOOM_powered_by_MGEv2_

						MGEMessage tmsg;
						tmsg.message = MGEGameCore::GEM_KEYDOWN;
						if ( ( buffer[0] >= 0x61 ) && ( buffer[0] < 0x7F ) ) {
							tmsg.parameter = (unsigned int)(buffer[0]-0x20);
						} else {
							tmsg.parameter = (unsigned int)(buffer[0]);
						}
						_DOOM_.PostMessage(tmsg);
	
#else

						MGEMessage tmsg;
						tmsg.message = MGEGameCore::GEM_KEYDOWN;
						if ( ( buffer[0] >= 0x61 ) && ( buffer[0] < 0x7F ) ) {
							tmsg.parameter = (unsigned int)(buffer[0]-0x20);
						} else {
							tmsg.parameter = (unsigned int)(buffer[0]);
						}
						cs.PostMessage(tmsg);

#endif

					}
				}
				return DRAW;
			}
		case ButtonPress:
			break;
		case MotionNotify:
			{
#ifdef _DOOM_powered_by_MGEv2_

				unsigned int _x = (unsigned int)event->xmotion.x_root;
				unsigned int _y = (unsigned int)event->xmotion.y_root;
				MGEMessage tmsg;
				tmsg.message = MGEGameCore::GEM_MOUSEMOVE;
				tmsg.parameter = ( _x << 16 ) | ( _y & 0x0000FFFF );
				_DOOM_.PostMessage(tmsg);
	
#else

				unsigned int _x = (unsigned int)event->xmotion.x_root;
				unsigned int _y = (unsigned int)event->xmotion.y_root;
				MGEMessage tmsg;
				tmsg.message = MGEGameCore::GEM_MOUSEMOVE;
				tmsg.parameter = ( _x << 16 ) | ( _y & 0x0000FFFF );
				cs.PostMessage(tmsg);

#endif
			}
			break;
	}
	return NOP;
}


int animate = 1;

void _XMessageLoop(Display *dpy, Window win) {
	while (1) {
		int op;
		while ( XPending(dpy) > 0 ) {
			XEvent event;
			XNextEvent(dpy, &event);
			op = _XMessageHandler(dpy, win, &event);
			if (op == EXIT) {
				return;
			} else 
			if (op == DRAW) {
				break;
			}
		}

		draw_frame(dpy, win);
	}
}


int main(int argc, char* argv[]) {
	unsigned int winWidth = 300, winHeight = 300;
	int x = 0, y = 0;
	Display *__disp;
	Window win;
	GLXContext ctx;
	char *dpyName = NULL;
	VisualID visId;
	int i;
	
	__disp = XOpenDisplay(dpyName);
	if (!__disp) {
		printf("Error: couldn't open display %s\n", dpyName ? dpyName : getenv("DISPLAY"));
		return -1;
	}
	
	// fullscreen
	int scrnum = DefaultScreen(__disp);

	x = 0; y = 0;
	winWidth = DisplayWidth(__disp, scrnum);
	winHeight = DisplayHeight(__disp, scrnum);
 
	__XCreateWindow(__disp, "Test3D", x, y, winWidth, winHeight, &win, &ctx, &visId);
	XMapWindow(__disp, win);
	glXMakeCurrent(__disp, win, ctx);
	query_vsync(__disp, win);
	
	
	if ( glewInit() != GLEW_OK ) {
		glXMakeCurrent(__disp, None, NULL);
		glXDestroyContext(__disp, ctx);
		XDestroyWindow(__disp, win);
		XCloseDisplay(__disp);
		return -1;
	}
	
	printf("GL_RENDERER   = %s\n", (char *) glGetString(GL_RENDERER));
	printf("GL_VERSION    = %s\n", (char *) glGetString(GL_VERSION));
	printf("GL_VENDOR     = %s\n", (char *) glGetString(GL_VENDOR));
	printf("VisualID %d, 0x%x\n", (int) visId, (unsigned int) visId);
//	printf("GL_EXTENSIONS = %s\n", (char *) glGetString(GL_EXTENSIONS));

#ifdef _DOOM_powered_by_MGEv2_

	isShutDown = true;
	DOOMinitialization();
		
	_DOOM___interval = 16.0f;
	_DOOM___numCycles = 1.0f;

	_DOOM_.interval = 16;
	_DOOM_.Start();
	
	isShutDown = false;
	
	_DOOM_windowWidth = winWidth;
	_DOOM_windowHeight = winHeight;
	_XChangeSize(winWidth, winHeight);
	_ChangeSize(winWidth, winHeight);
	
#else

	isShutDown = true;
	Initialization();
		
	__interval = 16.0f;
	__numCycles = 1.0f;

	cs.interval = 16;
	cs.Start();
	
	isShutDown = false;
	
	windowWidth = winWidth;
	windowHeight = winHeight;
	_XChangeSize(winWidth, winHeight);
	ChangeSize(winWidth, winHeight);
	
#endif
	_XMessageLoop(__disp, win);

	glXMakeCurrent(__disp, None, NULL);
	glXDestroyContext(__disp, ctx);
	XDestroyWindow(__disp, win);
	XCloseDisplay(__disp);

	return 0;
}


