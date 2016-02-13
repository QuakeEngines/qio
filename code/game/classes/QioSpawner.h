/*
============================================================================
Copyright (C) 2016 V.

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
// QioSpawner.h

#ifndef __LOGIC_BLINKER_H__
#define __LOGIC_BLINKER_H__

#include "BaseEntity.h"

class QioSpawner : public BaseEntity {
	bool bEnabled;
	u32 interval;
	u32 intervalToWait;
	u32 random;
	u32 elapsed;
	u32 spawnLimit;
	u32 spawnedCount;
	str modelToSpawn;
public:
	QioSpawner();

	DECLARE_CLASS( QioSpawner );

	virtual void runFrame();

	virtual void setKeyValue(const char *key, const char *value); 
};

#endif // __CONSTRAINT_H__
