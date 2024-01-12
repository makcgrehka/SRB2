// SONIC ROBO BLAST 2
//-----------------------------------------------------------------------------
// Copyright (C) 1993-1996 by id Software, Inc.
// Copyright (C) 1998-2000 by DooM Legacy Team.
// Copyright (C) 2024 by Sonic Team Junior.
//
// This program is free software distributed under the
// terms of the GNU General Public License, version 2.
// See the 'LICENSE' file for more details.
//-----------------------------------------------------------------------------
/// \file  p_dialog.h
/// \brief Text prompt system

#ifndef __P_DIALOG__
#define __P_DIALOG__

#include "doomtype.h"

#include "d_player.h"
#include "d_event.h"

//
// CUTSCENE TEXT WRITING
//
typedef struct
{
	const char *basetext;
	size_t basetextlength;
	char *disptext;
	size_t disptextsize;
	UINT32 baseptr;
	UINT32 writeptr;
	INT32 textcount;
	INT32 textspeed;
	INT32 numtowrite;
	boolean boostspeed;
} textwriter_t;

UINT8 P_CutsceneWriteText(textwriter_t *writer);
void P_ResetTextWriter(textwriter_t *writer, const char *basetext, size_t basetextlength);

//
// PROMPT STATE
//
typedef struct dialog_s
{
	INT32 promptnum;
	INT32 pagenum;

	textprompt_t *prompt;
	textpage_t *page;
	player_t *callplayer;
	textwriter_t writer;

	char *pagetext;
	size_t pagetextlength;
	char *disptext;
	size_t disptextsize;

	boolean blockcontrols;
	INT32 timetonext;
	INT16 postexectag;

	INT32 picnum;
	INT32 pictoloop;
	INT32 pictimer;
	INT32 picmode;
	INT32 numpics;
	cutscene_pic_t *pics;

	char speaker[256];
	char icon[256];
	boolean iconflip;

	boolean showchoices;
	INT32 curchoice;
	INT32 numchoices;
	INT32 nochoice;
	INT32 longestchoice;
	boolean selectedchoice;
} dialog_t;

void P_LoadDialogueLumps(UINT16 wadnum);

void P_StartTextPrompt(player_t *player, INT32 promptnum, INT32 pagenum, UINT16 postexectag, boolean blockcontrols, boolean freezerealtime, boolean allplayers);
void P_EndTextPrompt(player_t *player, boolean forceexec, boolean noexec);
void P_EndAllTextPrompts(boolean forceexec, boolean noexec);
void P_RunDialog(player_t *player);
void P_FreeDialog(dialog_t *dialog);
void P_DialogSetText(dialog_t *dialog, char *pagetext, size_t textlength);
void P_DialogUpdateLongestChoice(dialog_t *dialog);

boolean P_SetCurrentDialogChoice(player_t *player, INT32 choice);
boolean P_SelectDialogChoice(player_t *player, INT32 choice);

boolean F_GetPromptHideHudAll(void);
boolean F_GetPromptHideHud(fixed_t y);
void F_TextPromptDrawer(void);

INT32 P_GetTextPromptByName(const char *name);
INT32 P_GetPromptPageByName(textprompt_t *prompt, const char *name);
void P_GetPromptPageByNamedTag(const char *tag, INT32 *promptnum, INT32 *pagenum);
void P_SetMetaPage(textpage_t *page, textpage_t *metapage);
void P_SetPicsMetaPage(textpage_t *page, textpage_t *metapage);
void P_FreeTextPrompt(textprompt_t *prompt);

char *P_ConvertSOCPageDialog(char *text, size_t *text_length);
INT32 P_ParsePromptBackColor(const char *word);

#endif
