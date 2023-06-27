// SONIC ROBO BLAST 2
//-----------------------------------------------------------------------------
// Copyright (C) 1993-1996 by id Software, Inc.
// Copyright (C) 1998-2000 by DooM Legacy Team.
// Copyright (C) 1999-2023 by Sonic Team Junior.
//
// This program is free software distributed under the
// terms of the GNU General Public License, version 2.
// See the 'LICENSE' file for more details.
//-----------------------------------------------------------------------------
/// \file  p_setup.h
/// \brief Setup a game, startup stuff

#ifndef __P_SETUP__
#define __P_SETUP__

#include "doomdata.h"
#include "doomstat.h"
#include "r_defs.h"

// map md5, sent to players via PT_SERVERINFO
extern unsigned char mapmd5[16];

extern UINT8 levelfadecol;

/* for levelflat type */
enum
{
	LEVELFLAT_NONE,/* HOM time my friend */
	LEVELFLAT_FLAT,
	LEVELFLAT_PATCH,
	LEVELFLAT_PNG,
	LEVELFLAT_TEXTURE,
};

//
// MAP used flats lookup table
//
typedef struct
{
	char name[9]; // resource name from wad

	UINT8  type;
	union
	{
		struct
		{
			lumpnum_t     lumpnum; // lump number of the flat
			// for flat animation
			lumpnum_t baselumpnum;
		}
		flat;
		struct
		{
			INT32             num;
			INT32         lastnum; // texture number of the flat
			// for flat animation
			INT32         basenum;
		}
		texture;
	}
	u;

	UINT16 width, height;

	// for flat animation
	INT32 animseq; // start pos. in the anim sequence
	INT32 numpics;
	INT32 speed;

	// for textures
	UINT8 *picture;
#ifdef HWRENDER
	void *mipmap;
	void *mippic;
#endif
} levelflat_t;

INT32 P_AddLevelFlat(const char *flatname, levelflat_t *levelflat);
INT32 P_AddLevelFlatRuntime(const char *flatname);
INT32 P_CheckLevelFlat(const char *flatname);

typedef struct actioncache_s
{
	struct actioncache_s *next;
	struct actioncache_s *prev;
	struct mobj_s *mobj;
	INT32 statenum;
} actioncache_t;

extern size_t nummapthings;
extern mapthing_t *mapthings;

void P_SetupLevelSky(INT32 skynum, boolean global);
void P_SetupSkyTexture(INT32 skynum);
#ifdef SCANTHINGS
void P_ScanThings(INT16 mapnum, INT16 wadnum, INT16 lumpnum);
#endif
void P_RespawnThings(void);
boolean P_LoadLevel(boolean fromnetsave, boolean reloadinggamestate);
boolean P_LoadWorld(boolean fromnetsave);

boolean P_AddWadFile(const char *wadfilename);
boolean P_AddFolder(const char *folderpath);
boolean P_RunSOC(const char *socfilename);
void P_LoadSoundsRange(UINT16 wadnum, UINT16 first, UINT16 num);
void P_LoadMusicsRange(UINT16 wadnum, UINT16 first, UINT16 num);
//void P_WriteThings(void);
size_t P_PrecacheLevelFlats(void);
void P_AllocMapHeader(INT16 i);

void P_SetDemoFlickies(INT16 i);
void P_DeleteFlickies(INT16 i);

// Needed for NiGHTS
void P_ReloadRings(void);
void P_SwitchSpheresBonusMode(boolean bonustime);
void P_DeleteGrades(INT16 i);
void P_AddGradesForMare(INT16 i, UINT8 mare, char *gtext);
UINT8 P_GetGrade(UINT32 pscore, INT16 map, UINT8 mare);
UINT8 P_HasGrades(INT16 map, UINT8 mare);
UINT32 P_GetScoreForGrade(INT16 map, UINT8 mare, UINT8 grade);
UINT32 P_GetScoreForGradeOverall(INT16 map, UINT8 grade);

#endif
