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
// cameraDef.h 
#ifndef __CAMERADEF_H__
#define __CAMERADEF_H__

#include <math/vec3.h>
#include <math/axis.h>
#include <math/frustum.h>

#include <api/rbAPI.h>

class cameraDef_c {
	projDef_s proj;
	vec3_c origin;
	//vec3_c angles;
	axis_c axis;
	frustum_c frustum;
public:
	void setup(const vec3_c &newOrigin, const axis_c &newAxis, const projDef_s &pd) {
		origin = newOrigin;
		axis = newAxis;
		proj = pd;
		frustum.setup(proj.fovX,proj.fovY,proj.zFar,axis,origin);
	}

	const frustum_c &getFrustum() const {
		return frustum;
	}
	const vec3_c &getOrigin() const {
		return origin;
	}
};

#endif // __CAMERADEF_H__