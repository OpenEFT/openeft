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

#ifndef _OPENEFT_GLOBAL_H
#define _OPENEFT_GLOBAL_H

enum EFT_ERROR_CODE {
  EFT_OK = 0,
  EFT_NOK,
  EFT_ARG_ERR,
  EFT_ERROR_CODE_LAST
};


#define USE_THREAD_LOCAL

/* 
 ** I will keep openeft single-threaded as much as I can but
 ** if in turned out that we need to play with threads, we
 ** need to make sure to thread-safe global variables properly
 ** and prevent Race conditions.
 */
#ifdef USE_THREAD_LOCAL
#    define THREAD_LOCAL thread_local
#else
#    define THREAD_LOCAL __thread
#endif

#endif

