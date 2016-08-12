/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.

This file is part of Qio source code.

Qio source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Qio source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Qio source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/

#include "../qcommon/qcommon.h"
#include "sys_local.h"

#define MAX_LOG 32768

static char          consoleLog[ MAX_LOG ];
static unsigned int  writePos = 0;
static unsigned int  readPos = 0;

/*
==================
CON_LogSize
==================
*/
unsigned int CON_LogSize()
{
	if( readPos <= writePos )
		return writePos - readPos;
	else
		return writePos + MAX_LOG - readPos;
}

/*
==================
CON_LogFree
==================
*/
static unsigned int CON_LogFree()
{
	return MAX_LOG - CON_LogSize( ) - 1;
}

/*
==================
CON_LogWrite
==================
*/
unsigned int CON_LogWrite( const char *in )
{
	unsigned int length = strlen( in );
	unsigned int firstChunk;
	unsigned int secondChunk;

	while( CON_LogFree( ) < length && CON_LogSize( ) > 0 )
	{
		// Free enough space
		while( consoleLog[ readPos ] != '\n' && CON_LogSize( ) > 1 )
			readPos = ( readPos + 1 ) % MAX_LOG;

		// Skip past the '\n'
		readPos = ( readPos + 1 ) % MAX_LOG;
	}

	if( CON_LogFree( ) < length )
		return 0;

	if( writePos + length > MAX_LOG )
	{
		firstChunk  = MAX_LOG - writePos;
		secondChunk = length - firstChunk;
	}
	else
	{
		firstChunk  = length;
		secondChunk = 0;
	}

	memcpy( consoleLog + writePos, in, firstChunk );
	memcpy( consoleLog, in + firstChunk, secondChunk );

	writePos = ( writePos + length ) % MAX_LOG;

	return length;
}

/*
==================
CON_LogRead
==================
*/
unsigned int CON_LogRead( char *out, unsigned int outSize )
{
	unsigned int firstChunk;
	unsigned int secondChunk;

	if( CON_LogSize( ) < outSize )
		outSize = CON_LogSize( );

	if( readPos + outSize > MAX_LOG )
	{
		firstChunk  = MAX_LOG - readPos;
		secondChunk = outSize - firstChunk;
	}
	else
	{
		firstChunk  = outSize;
		secondChunk = 0;
	}

	memcpy( out, consoleLog + readPos, firstChunk );
	memcpy( out + firstChunk, out, secondChunk );

	readPos = ( readPos + outSize ) % MAX_LOG;

	return outSize;
}
