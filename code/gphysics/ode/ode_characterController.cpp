/*
============================================================================
Copyright (C) 2013 V.

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
// ode_characterController.cpp
#include "ode_characterController.h"
#include "ode_headers.h"
#include "ode_world.h"
#include "ode_convert.h"
#include <api/coreAPI.h>

odeCharacterController_c::odeCharacterController_c() {
	this->geom = 0;
	this->body = 0;
	this->myWorld = 0;
}
odeCharacterController_c::~odeCharacterController_c() {
	destroyCharacter();
}
void odeCharacterController_c::setCharacterVelocity(const class vec3_c &newVel) {

}
void odeCharacterController_c::setCharacterEntity(class BaseEntity *ent) {

}
void odeCharacterController_c::update(const class vec3_c &dir) {
	if(isOnGround() == false)
		return;

	lastDir = dir;

	vec3_c scaled = dir*5;
	g_core->Print("dir : %f %f %f\n",dir.x,dir.y,dir.z);
	//dBodySetLinearVel(body,scaled.x,scaled.y,scaled.z);
	//dBodyAddForce(body,scaled.x,scaled.y,scaled.z);
	vec3_c curVel = dBodyGetLinearVel(body);
	//vec2_c dir2d = dir;
	//vec2_c vel2d = curVel;
	//float len = dir2d.len();
	//if(vel2d.len() > len) {
	//	vel2d.setLen(len);
	//}
	//curVel.x = vel2d.x;
	//curVel.y = vel2d.y;
	curVel.x = dir.x;
	curVel.y = dir.y;
	if(curVel.z < 0.f) { 
		curVel.z -= 1.f;
	}
	dBodySetLinearVel(body,curVel.x,curVel.y,curVel.z);

	dQuaternion q;
	dQSetIdentity(q);
	dBodySetQuaternion(body,q);
	dBodyEnable(body);
}
const class vec3_c &odeCharacterController_c::getPos() const {
	lastPos = dBodyGetPosition(body);
	//lastPos.z -= (characterHeight);
	lastPos *= ODE_TO_QIO;
	return lastPos;
}
bool odeCharacterController_c::isOnGround() const {
	// FIXME
	//vec3_c curVel = dBodyGetLinearVel(body);
	//if(curVel.z < 0) 
	//	return false; // falling
	return true;
}
bool odeCharacterController_c::tryToJump() {
	//if(isOnGround() == false)
		return false; // didnt jump
	//dBodyAddForce(body,0,0,100.f);
	//return true;
}


void odeCharacterController_c::init(class odePhysicsWorld_c *pWorld, const class vec3_c &pos, float _characterHeight, float _characterWidth) {
	this->myWorld = pWorld;

	_characterHeight += _characterWidth*2;

	characterHeight = _characterHeight * QIO_TO_ODE;;
	characterWidth = _characterWidth * QIO_TO_ODE;;

	vec3_c posScaled = pos * QIO_TO_ODE;
//	posScaled.z += (characterHeight);

	vec3_c sizes(characterWidth,characterWidth,characterHeight);
	geom = dCreateBox(pWorld->getODESpace(),sizes.x,sizes.y,sizes.z);
	body = dBodyCreate(pWorld->getODEWorld());
	dBodySetMaxAngularSpeed(body,0);

	dMass m;
	dMassSetBox (&m,5.0,sizes[0],sizes[1],sizes[2]);
    dBodySetMass (body,&m);
    dGeomSetBody (geom,body);
	dBodySetPosition(body,posScaled.x,posScaled.y,posScaled.z);
}
void odeCharacterController_c::destroyCharacter() {


}

