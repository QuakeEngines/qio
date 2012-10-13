/*
============================================================================
Copyright (C) 2012 V.

This file is part of Qio source code.

Qio source code is free software; you can redistribute it 
and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

Qio source code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA,
or simply visit <http://www.gnu.org/licenses/>.
============================================================================
*/
// BaseEntity.h - base class for all entities

#include "../g_local.h"
#include "BaseEntity.h"
#include <math/vec3.h>
#include "Player.h"

DEFINE_CLASS(BaseEntity, "None");

// use this to force BaseEntity::ctor() to use a specific edict instead of allocating a new one
static edict_s *be_forcedEdict = 0;
void BE_SetForcedEdict(edict_s *nfe) {
	be_forcedEdict = nfe;
}

BaseEntity::BaseEntity() {
	if(be_forcedEdict) {
		myEdict = be_forcedEdict;
		be_forcedEdict = 0;
		// HACK: use playerState_s for players
		Player *pl = (Player*)this;
		// playerState_s is a superset of entityState, so we can point s to ps
		playerState_s *ps = pl->getPlayerState();
		myEdict->s = ps;
		_myEntityState = 0;
		// save clientNum
		ps->clientNum = myEdict - g_entities;
		// set entity type
		myEdict->s->eType = ET_PLAYER;
	} else {
		myEdict = G_Spawn();
		// if that's not a player, alloc an entityState_s
		_myEntityState = myEdict->s = new entityState_s;
		// set entity type
		myEdict->s->eType = ET_GENERAL;
	}
	// set entityState_s::number
	myEdict->s->number = myEdict - g_entities;
	myEdict->ent = this;
}
BaseEntity::~BaseEntity() {
	if(_myEntityState) {
		// free the entityState_s that we have alloced
		assert(_myEntityState == myEdict->s);
		delete _myEntityState;
		_myEntityState = 0;
	}
	//G_FreeEntity(myEdict);
	memset (myEdict, 0, sizeof(*myEdict));
	myEdict->freetime = level.time;
	myEdict->s = 0;
}
void BaseEntity::setKeyValue(const char *key, const char *value) {
	if(!stricmp(key,"origin")) {
		this->setOrigin(value);
	} else if(!stricmp(key,"angles")) {
		this->setAngles(value);
	} else {

	}
}
void BaseEntity::setOrigin(const vec3_c &newXYZ) {
	myEdict->s->origin = newXYZ;
}
void BaseEntity::setAngles(const class vec3_c &newAngles) {
	myEdict->s->angles = newAngles;
}
const vec3_c &BaseEntity::getOrigin() const {
	return myEdict->s->origin;
}
const vec3_c &BaseEntity::getAngles() const {
	return myEdict->s->angles;
}
