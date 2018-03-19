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
#include "utils.h"

uint32_t get_thread_id() {
  std::string thread_id = boost::lexical_cast<std::string>(boost::this_thread::get_id());
  uint32_t thread_no = 0;
  sscanf(thread_id.c_str(), "%x", &thread_no);
  return thread_no;
}

uint32_t get_process_id() {
  std::string proc_id = boost::lexical_cast<std::string>(boost::this_process::get_id());
  uint32_t proc_no = 0;
  sscanf(proc_id.c_str(), "%x", &proc_no);
  return proc_no;
}
