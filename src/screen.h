// SONIC ROBO BLAST 2
//-----------------------------------------------------------------------------
// Copyright (C) 1998-2000 by DooM Legacy Team.
// Copyright (C) 1999-2023 by Sonic Team Junior.
//
// This program is free software distributed under the
// terms of the GNU General Public License, version 2.
// See the 'LICENSE' file for more details.
//-----------------------------------------------------------------------------
/// \file  screen.h
/// \brief Handles multiple resolutions

#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "command.h"

#if defined (_WIN32) && !defined (__CYGWIN__)
#define RPC_NO_WINDOWS_H
#include <windows.h>
#define DNWH HWND
#else
#define DNWH void * // unused in DOS version
#endif

// quickhack for V_Init()... to be cleaned up
#ifdef NOPOSTPROCESSING
#define NUMSCREENS 2
#else
#define NUMSCREENS 5
#endif

// Size of statusbar.
#define ST_HEIGHT 32
#define ST_WIDTH 320

// NEVER CHANGE THIS! This is the original resolution of the graphics.
#define BASEVIDWIDTH 320
#define BASEVIDHEIGHT 200

// Max screen size
#define MAXVIDWIDTH 8192
#define MAXVIDHEIGHT 4608

// global video state
typedef struct viddef_s
{
	UINT8 *buffer; // invisible screens buffer
	size_t rowbytes; // bytes per scanline of the VIDEO mode
	INT32 width; // PIXELS per scanline
	INT32 height;
	INT32 recalc; // if true, recalc vid-based stuff

	INT32 dup; // scale 1, 2, 3 value for menus & overlays
	INT32/*fixed_t*/ fdup; // same as dup, but exact value when aspect ratio isn't 320/200
	INT32 bpp; // BYTES per pixel: 1 = 256color

	INT32 baseratio; // Used to get the correct value for lighting walls

	// for Win32 version
	DNWH WndParent; // handle of the application's window
	UINT8 smalldup; // factor for a little bit of scaling
	UINT8 meddup; // factor for moderate, but not full, scaling

	INT32 fdup; // same as dupx, dupy, but exact value when aspect ratio isn't 320/200
	INT32 bpp; // BYTES per pixel: 1 = 256color, 2 = highcolor

	struct {
		INT32 width;
		INT32 height;
		INT32 renderer;
		UINT8 set;
	} change;

#ifdef HWRENDER
	UINT8 glstate;
#endif
} viddef_t;

enum
{
	VID_RESOLUTION_UNCHANGED,
	VID_RESOLUTION_CHANGED,
	VID_RESOLUTION_RESIZED_WINDOW
};

enum
{
	VID_GL_LIBRARY_NOTLOADED,
	VID_GL_LIBRARY_LOADED,
	VID_GL_LIBRARY_ERROR
};

#define MAXWINMODES 18

extern INT32 windowedModes[MAXWINMODES][2];

// ---------------------------------------------
// color mode dependent drawer function pointers
// ---------------------------------------------

#define BASEDRAWFUNC 0

enum
{
	COLDRAWFUNC_BASE = BASEDRAWFUNC,
	COLDRAWFUNC_FUZZY,
	COLDRAWFUNC_TRANS,
	COLDRAWFUNC_SHADE,
	COLDRAWFUNC_SHADOWED,
	COLDRAWFUNC_TRANSTRANS,
	COLDRAWFUNC_FOG,

	COLDRAWFUNC_MAX
};

extern void (*colfunc)(void);
extern void (*colfuncs[COLDRAWFUNC_MAX])(void);

enum
{
	SPANDRAWFUNC_BASE = BASEDRAWFUNC,
	SPANDRAWFUNC_TRANS,
	SPANDRAWFUNC_TILTED,
	SPANDRAWFUNC_TILTEDTRANS,

	SPANDRAWFUNC_SPLAT,
	SPANDRAWFUNC_TRANSSPLAT,
	SPANDRAWFUNC_TILTEDSPLAT,

	SPANDRAWFUNC_SPRITE,
	SPANDRAWFUNC_TRANSSPRITE,
	SPANDRAWFUNC_TILTEDSPRITE,
	SPANDRAWFUNC_TILTEDTRANSSPRITE,

	SPANDRAWFUNC_WATER,
	SPANDRAWFUNC_TILTEDWATER,

	SPANDRAWFUNC_SOLID,
	SPANDRAWFUNC_TRANSSOLID,
	SPANDRAWFUNC_TILTEDSOLID,
	SPANDRAWFUNC_TILTEDTRANSSOLID,
	SPANDRAWFUNC_WATERSOLID,
	SPANDRAWFUNC_TILTEDWATERSOLID,

	SPANDRAWFUNC_FOG,
	SPANDRAWFUNC_TILTEDFOG,

	SPANDRAWFUNC_MAX
};

extern void (*spanfunc)(void);
extern void (*spanfuncs[SPANDRAWFUNC_MAX])(void);
extern void (*spanfuncs_npo2[SPANDRAWFUNC_MAX])(void);

// ----------------
// screen variables
// ----------------
extern viddef_t vid;

extern double averageFPS;

void SCR_ChangeResolution(INT32 width, INT32 height);
void SCR_SetWindowSize(INT32 width, INT32 height);
void SCR_SetSizeNoRestore(INT32 width, INT32 height);
void SCR_ChangeRenderer(void);

const char *SCR_GetModeName(INT32 modeNum);
INT32 SCR_GetModeForSize(INT32 w, INT32 h);

boolean SCR_IsValidResolution(INT32 width, INT32 height);

extern CV_PossibleValue_t cv_renderer_t[];

extern INT32 scr_bpp;

extern consvar_t cv_scr_width, cv_scr_height, cv_scr_width_w, cv_scr_height_w, cv_scr_depth, cv_fullscreen;
extern consvar_t cv_renderwalls, cv_renderfloors, cv_renderthings;
extern consvar_t cv_renderview, cv_renderer;
extern consvar_t cv_renderhitbox, cv_renderhitboxinterpolation, cv_renderhitboxgldepth;
// wait for page flipping to end or not
extern consvar_t cv_vidwait;
extern consvar_t cv_timescale;

// Initialize the screen
void SCR_Startup(void);

// Change video mode, only at the start of a refresh.
void SCR_SetMode(void);

// Set drawer functions for Software
void SCR_SetDrawFuncs(void);

// Recalc screen size dependent stuff
void SCR_Recalc(void);

// Check parms once at startup
void SCR_CheckDefaultMode(void);

// Set the resolution which is saved in the config
void SCR_SetDefaultMode(INT32 width, INT32 height);

void SCR_CalculateFPS(void);

FUNCMATH boolean SCR_IsAspectCorrect(INT32 width, INT32 height);

// move out to main code for consistency
void SCR_DisplayTicRate(void);
void SCR_ClosedCaptions(void);
void SCR_DisplayLocalPing(void);
void SCR_DisplayMarathonInfo(void);
#undef DNWH
#endif //__SCREEN_H__
