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
// modelDeclAPI.h
#ifndef __MODELDECLAPI_H__
#define __MODELDECLAPI_H__

class animDefAPI_i {
public:
	//virtual const char *getAlias() const = 0;
	//virtual const char *getAnimFileName() const = 0;
	//virtual class skelAnimAPI_i *getAnim() const = 0;
};

class modelDeclAPI_i {
public:
	virtual const char *getModelDeclName() = 0;
	virtual const char *getMeshName() = 0;
	virtual class skelModelAPI_i *getSkelModel() = 0;

	virtual u32 getNumSurfaces() = 0;

	//// animations list access
	//virtual u32 getNumAnims() const = 0;
	//virtual const char *animAliasForNum(u32 index) = 0;
	//virtual const char *animFileNameForNum(u32 index) = 0;
	//virtual const class animDefAPI_i *animDefForNum(u32 index) = 0;
	//virtual int animIndexForAnimAlias(const char *alias) = 0;
};

#endif // __MODELDECLAPI_H__