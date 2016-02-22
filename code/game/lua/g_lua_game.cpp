/*
===========================================================================
Copyright (C) 2006 Robert Beckebans <trebor_7@users.sourceforge.net>
Copyright (C) 2013 V.

This file is part of XreaL source code.

XreaL source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

XreaL source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with XreaL source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/
// lua_game.c -- qagame library for Lua

#ifdef G_ENABLE_LUA_SCRIPTING

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#include "../g_local.h"
#include <api/serverAPI.h>
#include <shared/colorTable.h>
#include <shared/infoString.h>

static int game_Print(lua_State * L)
{
	int             i;
	char            buf[MAX_STRING_CHARS];
	int             n = lua_gettop(L);	// number of arguments

	memset(buf, 0, sizeof(buf));

	lua_getglobal(L, "tostring");
	for(i = 1; i <= n; i++)
	{
		const char     *s;

		lua_pushvalue(L, -1);	// function to be called
		lua_pushvalue(L, i);	// value to print
		lua_call(L, 1, 1);
		s = lua_tostring(L, -1);	// get result

		if(s == NULL)
			return luaL_error(L, "`tostring' must return a string to `print'");

		Q_strcat(buf, sizeof(buf), s);

		lua_pop(L, 1);			// pop result
	}

	G_Printf("%s\n", buf);
	return 0;
}

static int game_Broadcast(lua_State * L)
{
	int             i;
	char            buf[MAX_STRING_CHARS];
	int             n = lua_gettop(L);	// number of arguments

	memset(buf, 0, sizeof(buf));

	lua_getglobal(L, "tostring");
	for(i = 1; i <= n; i++)
	{
		const char     *s;

		lua_pushvalue(L, -1);	// function to be called
		lua_pushvalue(L, i);	// value to print
		lua_call(L, 1, 1);
		s = lua_tostring(L, -1);	// get result

		if(s == NULL)
			return luaL_error(L, "`tostring' must return a string to `print'");

		Q_strcat(buf, sizeof(buf), s);

		lua_pop(L, 1);			// pop result
	}

	g_server->SendServerCommand(-1, va("cp \"" S_COLOR_WHITE "%s\n\"", buf));
	return 0;
}

static const luaL_reg gamelib[] = {
	{"Print", game_Print},
	{"Broadcast", game_Broadcast},
	{NULL, NULL}
};

int luaopen_game(lua_State * L)
{
	luaL_register(L, "game", gamelib);

	lua_pushliteral(L, "_GAMEVERSION");
	lua_pushliteral(L, GAMEVERSION);

	return 1;
}

#endif
