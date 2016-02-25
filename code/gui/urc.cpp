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
// urc.cpp
#include "urc.h"
#include "urc_element_label.h"
#include <shared/parser.h>
#include <api/rAPI.h>
#include <api/coreAPI.h>

void urc_c::drawURC() {	
	for(u32 i = 0; i < elements.size(); i++) {
		urcElementBase_c *el = elements[i];
		const rect_c &r = el->getRect();
		const char *matName = el->getMatName();
		if(matName[0]) {
			g_core->Print("Material %s\n",matName);
			rf->drawStretchPic(r.getX(),r.getY(),r.getW(),r.getH(),0,0,1,1,matName);
		}
	}
}
bool urc_c::loadURCFile() {
	parser_c p;
	if(p.openFile(fname))
		return true;

	while(p.atEOF() == false) {
		if(p.atWord("resource")) {
			urcElementBase_c *el;
			if(p.atWord("Label")) {
				el = new urcElementLabel_c();
			} else if(p.atWord("Button")) {
				el = new urcElementLabel_c();
			} else {
				str type = p.getToken();
				el = new urcElementLabel_c();
			}
			if(el->parseURCElement(p)) {
				delete el;
				return true;
			}
			elements.push_back(el);
		} else {
			p.getToken();
		}
	}
	return false;
}
