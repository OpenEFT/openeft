//----------------------------------------------------------------------
// Copyright (C) 2018  openeft.org
// Copyright (C) Reza Schadmani <reza.schadmani@openeft.org>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------

#include "global.h"
#include "eftclass.h"


uint32_t eftClass::mem_used = 0;
uint32_t eftClass::num_objects = 0;

eftClass::~eftClass() {
}

void* eftClass::operator new(size_t s) {
  int *p;

  /* Using the first memory location to store
   the size of the allocated memory for this object */

  s += sizeof (int);
  p = (int *) malloc(s);
  *p = s;
  mem_used += s;
  num_objects++;

  return p + 1;
}

void eftClass::operator delete(void *ptr) {
  int *p;

  if (ptr) {
    p = ((int *) ptr) - 1;
    mem_used -= *p;
    num_objects--;
    free(p);
  }
}

void eftClass::find_uninitialized_mem() {
#ifdef DEBUG_UNINITIALIZED_MEMORY
  unsigned long *ptr = ((unsigned long *) this) - 1;
  int size = *ptr;
  assert((size & 3) == 0);
  size >>= 2;
  for (int i = 0; i < size; i++) {
    if (ptr[i] == unassigned_mem) {
      log(LOG_DEBUG, "There is and uninitialized memory at offset %x in this object", ptr);
    }
  }
#endif
}