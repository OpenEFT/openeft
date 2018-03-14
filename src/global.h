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

#include <stdint.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <thread>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>

enum EFT_ERROR_CODE {
  EFT_OK = 0,
  EFT_NOK,
  EFT_ARG_ERR,
  EFT_ERROR_CODE_LAST
};


#define ANSI_COLOR_RED     "\x1b[31m "
#define ANSI_COLOR_GREEN   "\x1b[32m "
#define ANSI_COLOR_YELLOW  "\x1b[33m "
#define ANSI_COLOR_BLUE    "\x1b[34m "
#define ANSI_COLOR_MAGENTA "\x1b[35m "
#define ANSI_COLOR_CYAN    "\x1b[36m "
#define ANSI_COLOR_RESET   " \x1b[0m"
#define MOV_COL_RIGHT_BOOT "\033[70G"
#define MOV_COL_RIGHT_CMD   "\033[20G"

#define BOOT_OK  MOV_COL_RIGHT_BOOT "[" ANSI_COLOR_GREEN "DONE" ANSI_COLOR_RESET "]" 
#define BOOT_FAILED MOV_COL_RIGHT_BOOT "[" ANSI_COLOR_RED "FAILED" ANSI_COLOR_RESET "]"


#define USE_THREAD_LOCAL

/* 
 ** I will keep openeft single-threaded as much as I can but
 ** if in turned out that we need to play with threads, we
 ** need to make sure to thread-safe global variables properly
 ** and prevent Race conditions.
 */
#ifdef USE_THREAD_LOCAL
#define THREAD_LOCAL thread_local
#else
#define THREAD_LOCAL __thread
#endif


#undef DEBUG_UNINITIALIZED_MEMORY

#define OPENEFT_HEARTBEAT_MICROSEC 100
#endif
