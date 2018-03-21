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


#include "log.h"

void dumpb(const uint8_t *buffer, uint32_t len) {
  uint32_t i, j;
  char tmp[128];
  char line[128];

  for (i = 0; i < len; i += 16) {
    snprintf(tmp, sizeof (tmp), "%4.4d( %4.4x )  ", i, i);
    strncpy(line, tmp, sizeof (line));

    for (j = 0; j < 8; ++j) {
      if (i + j < len) {
        snprintf(tmp, sizeof (tmp), "%2.2x ", buffer[i + j]);
        strncat(line, tmp, sizeof (line) - strlen(line) - 1);
      } else {
        snprintf(tmp, sizeof (tmp), "   ");
        strncat(line, tmp, sizeof (line) - strlen(line) - 1);
      }
    }

    strncat(line, " ", sizeof (line) - strlen(line) - 1);

    for (j = 8; j < 16; ++j) {
      if (i + j < len) {
        snprintf(tmp, sizeof (tmp), "%2.2x ", buffer[i + j]);
        strncat(line, tmp, sizeof (line) - strlen(line) - 1);
      } else {
        snprintf(tmp, sizeof (tmp), "   ");
        strncat(line, tmp, sizeof (line) - strlen(line) - 1);
      }
    }

    strncat(line, " ", sizeof (line) - strlen(line) - 1);

    for (j = 0; j < 16 && i + j < len; ++j) {
      snprintf(tmp, sizeof (tmp), "%c",
        (unsigned) ((' ' <= buffer[i + j] && buffer[i + j] < 127) ?
        buffer[i + j] :
        '.'));

      strncat(line, tmp, sizeof (line) - strlen(line) - 1);
    }
    
    dprintf(eftConfig::log_fp, "%s\n", line);
  }
}