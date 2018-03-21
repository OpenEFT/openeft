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

#ifndef _OPENEFT_LOG_H
#define _OPENEFT_LOG_H

#include "global.h"
#include "utils/utils.h"
#include "config/config.h"

#define LOG_EMERG    0
#define LOG_ALERT    1
#define LOG_CRIT     2
#define LOG_ERR      3
#define LOG_WARNING  4
#define LOG_NOTICE   5
#define LOG_INFO     6
#define LOG_DEBUG    7
#define LOG_TRACE    8
#define LOG_DEFAULT  9
#define LOG_CONT     10

#define LOG_CONSOLE  11


void dumpb(const uint8_t *buffer, uint32_t len);

/*
 ** Log format
 ** [File Name][Line No][Function Name][PID] [Log Content...]
 ** 
 */

#define log(level, fmt, ...) \
        do { \
          if (level == LOG_CONSOLE) \
            dprintf(eftConfig::log_fp, ANSI_COLOR_BLUE fmt ANSI_COLOR_RESET"\n", \
                                  ## __VA_ARGS__); \
          if(eftConfig::log_enabled) \
            if (level <= eftConfig::log_run_level) \
              dprintf(eftConfig::log_fp, "[%s][%d][%s()][%u:%u]""\033[100G" fmt "\n", \
                                  __FILE__, \
                                  __LINE__, \
                                  __func__, \
                                  get_process_id(), \
                                  get_thread_id(), \
                                  ## __VA_ARGS__); \
        } while (0)

#define logb(level, string, buf, len) \
        do { \
          if(eftConfig::log_enabled) \
            if (level <= eftConfig::log_run_level) \
              dprintf(eftConfig::log_fp, "[%s][%d][%s()][%u:%u]\033[90G%s:\n", \
                                  __FILE__, \
                                  __LINE__, \
                                  __func__, \
                                  get_process_id(), \
                                  get_thread_id(), \
                                  string); \
              dprintf(eftConfig::log_fp, "\n"); \
              dumpb(buf, len); \
              dprintf(eftConfig::log_fp, "\n"); \
        } while (0)


#endif