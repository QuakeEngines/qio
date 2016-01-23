/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.

This file is part of Quake III Arena source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Quake III Arena source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/
//
// bg_misc.c -- both games misc functions, all completely stateless

#include "../qcommon/q_shared.h"
#include <shared/entityType.h>
#include <protocol/userCmd.h>
#include <protocol/playerState.h>
#include "bg_public.h"

/*
========================
BG_PlayerStateToEntityState

This is done after each set of userCmd_s on the server,
and after local prediction on the client
========================
*/
void BG_PlayerStateToEntityState( playerState_s *ps, entityState_s *s, bool snap ) {

	//if ( ps->pm_type == PM_INTERMISSION || ps->pm_type == PM_SPECTATOR ) {
	//	s->eType = ET_INVISIBLE;
	//} else if ( ps->stats[STAT_HEALTH] <= GIB_HEALTH ) {
	//	s->eType = ET_INVISIBLE;
	//} else 
	{
		s->eType = ET_PLAYER;
	}

	s->number = ps->clientNum;

	s->origin = ps->origin;
	s->scale = ps->scale;

	// copy angles (NOT viewangles)
	s->angles = ps->angles;

	s->animIndex = ps->animIndex;
	s->torsoAnim = ps->torsoAnim;
	s->parentNum = ps->parentNum;
	s->parentTagNum = ps->parentTagNum;
	s->eFlags = ps->eFlags;

	// set the trDelta for flag direction
	//VectorCopy( ps->velocity, s->pos.trDelta );


	//s->apos.trType = TR_INTERPOLATE;
	//VectorCopy( ps->viewangles, s->apos.trBase );
	//if ( snap ) {
	//	SnapVector( s->apos.trBase );
	//}

//	s->angles2[YAW] = ps->movementDir;

////	s->clientNum = ps->clientNum;		// ET_PLAYER looks here instead of at number
										// so corpses can also reference the proper config

	s->rModelIndex = ps->rModelIndex;
	s->rSkinIndex = ps->rSkinIndex;
	s->colModelIndex = ps->colModelIndex;
	s->groundEntityNum = ps->groundEntityNum;
}


/*
================
PM_UpdateViewAngles

This can be used as another entry point when only the viewangles
are being updated isntead of a full move
================
*/
void PM_UpdateViewAngles( playerState_s *ps, const userCmd_s *cmd ) {
	short		temp;
	int		i;


	// circularly clamp the angles with deltas
	for (i=0 ; i<3 ; i++) {
		temp = cmd->angles[i] + ps->delta_angles[i];
		if ( i == PITCH ) {
			// don't let the player look up or down more than 90 degrees
			if ( temp > 16000 ) {
				ps->delta_angles[i] = 16000 - cmd->angles[i];
				temp = 16000;
			} else if ( temp < -16000 ) {
				ps->delta_angles[i] = -16000 - cmd->angles[i];
				temp = -16000;
			}
		}
		ps->viewangles[i] = SHORT2ANGLE(temp);
	}

}
