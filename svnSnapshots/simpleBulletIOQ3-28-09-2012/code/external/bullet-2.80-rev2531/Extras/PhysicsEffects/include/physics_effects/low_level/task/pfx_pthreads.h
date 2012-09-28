/*
 Applied Research Associates Inc. (c)2011

 Redistribution and use in source and binary forms,
   with or without modification, are permitted provided that the
   following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Applied Research Associates Inc nor the names
      of its contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _SCE_PFX_PTHREADS_H
#define _SCE_PFX_PTHREADS_H

#include "../../base_level/base/pfx_common.h"
#include <errno.h>

namespace sce {
namespace PhysicsEffects {

class PfxBarrier;
class PfxCriticalSection;
class PfxTaskManager;

#define SCE_PFX_CHECK_PTHREADS_OUTCOME(result) \
    if(0 != result) \
	{ \
        SCE_PFX_PRINTF("pthreads problem at line %i in file %s: %i %d\n", __LINE__, __FILE__, result, errno); \
    }

PfxBarrier *PfxCreateBarrierPthreads(int n);
PfxCriticalSection *PfxCreateCriticalSectionPthreads();
PfxTaskManager *PfxCreateTaskManagerPthreads(PfxUInt32 numTasks,PfxUInt32 maxTasks,void *workBuff,PfxUInt32 workBytes);

} //namespace PhysicsEffects
} //namespace sce

#endif // _SCE_PFX_PTHREADS_H
