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
// trace.cpp
#include "trace.h"
#include "collisionUtils.h"

void trace_c::setupRay(const vec3_c &newFrom, const vec3_c &newTo) {
	this->to = newTo;
	this->from = newFrom;
	this->hitPos = this->to;
	this->delta = newTo - newFrom;
	this->len = this->delta.len();
	this->fraction = 1.f;
	this->traveled = this->len;
	recalcRayTraceBounds();
}
void trace_c::recalcRayTraceBounds() {
	traceBounds.reset(from);
	traceBounds.addPoint(hitPos);
	traceBounds.extend(0.25f);
}
void trace_c::updateForNewHitPos() {
	this->traveled = (hitPos - from).len();
	this->fraction = this->traveled / this->len;
	recalcRayTraceBounds();
}
bool trace_c::clipByTriangle(const vec3_c &p0, const vec3_c &p1, const vec3_c &p2, bool twoSided) {
	vec3_c newHit;
	int res = CU_RayTraceTriangle(from,hitPos,p0,p1,p2,&newHit);
	if(res != 1) {
		return false; 
	}
#if 1
	float checkLen = newHit.dist(from);
	if(checkLen >= this->traveled) {
		return false;
	}
#endif
	hitPos = newHit;
	this->updateForNewHitPos();
	return true;
}
