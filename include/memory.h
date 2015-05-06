/*
 * Localize Bug Fix
 * Copyright (c) 2013 - 2014 AGHL.RU Dev Team
 * 
 * http://aghl.ru/forum/ - Russian Half-Life and Adrenaline Gamer Community
 *
 *
 *    This program is free software; you can redistribute it and/or modify it
 *    under the terms of the GNU General Public License as published by the
 *    Free Software Foundation; either version 2 of the License, or (at
 *    your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful, but
 *    WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software Foundation,
 *    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *    In addition, as a special exception, the author gives permission to
 *    link the code of this program with the Half-Life Game Engine ("HL
 *    Engine") and Modified Game Libraries ("MODs") developed by Valve,
 *    L.L.C ("Valve").  You must obey the GNU General Public License in all
 *    respects for all of the code used other than the HL Engine and MODs
 *    from Valve.  If you modify this file, you may extend this exception
 *    to your version of the file, but you are not obligated to do so.  If
 *    you do not wish to do so, delete this exception statement from your
 *    version.
 *
 */

#ifndef _MEMORY_H_
#define _MEMORY_H_

#ifdef _WIN32
	#include <windows.h>
	#include <psapi.h>
#ifdef _MSC_VER <= 1600
	#define PSAPI_VERSION 1
#endif
#else
	#include <dlfcn.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <sys/mman.h>
	#include <string.h>
	#include <link.h>
	
	#define Align(addr)	((void *)(((long)addr) & ~(sysconf(_SC_PAGESIZE) - 1)))
#endif

#ifdef _MSC_VER
	#pragma comment(lib,"psapi.lib")
#endif

#ifndef dword
	#define dword unsigned long
#endif

struct lib_t
{
	char *base;
	void *handle;
	dword size;
};

int lib_load_info(void *addr,lib_t *lib);

char *lib_find_pattern(lib_t *lib,const char *pattern,int len);
char *lib_find_pattern_fstr(lib_t *lib,const char *string,int range,const char *pattern,int len);

char *mem_find_ref(char *start,int range,int opcode,dword ref,int relative);
char *mem_find_pattern(char *pos,int range,const char *pattern,int len);

int mem_change_protection(void *addr,const char *patch,int len);

#ifndef _WIN32
char *lib_find_symbol(lib_t *lib,const char *symbol);
#endif

#endif //_MEMORY_H_

