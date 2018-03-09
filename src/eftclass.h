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
#ifndef _OPENEFT_EFTCLASS_H
#define _OPENEFT_EFTCLASS_H

/*
 ** Use OPENEFT_STD_CLASS to streamline type checking, class instanciation
 ** and runtime communications.
 */
#define OPENEFT_STD_CLASS(nameofclass)   		\
public:


class eftClass {
public:
  OPENEFT_STD_CLASS(eftClass);

  void* operator new(size_t);
  void* operator new[](size_t);
  
  void operator delete(void *);
  void operator delete[](void *);
  
  void findUninitializedMem();
  
  virtual ~eftClass();
  
  
private:
  /* Keep tracking of the memory usage */
  static uint32_t memused;
  static uint32_t numobjects;
};

#endif /* EFTCLASS_H */

