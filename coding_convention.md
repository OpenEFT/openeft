# License
```C++
//----------------------------------------------------------------------
// Copyright (C) YYYY  openeft.org
// Copyright (C) Reza Schadmani <reza.schadmani@openeft.org>
// Copyright (C) OpenEFT development team.
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
```
Where YYYY in the license's first line will be replaced by the current year.
* License must hold both the notice and the GPL free software note.

# Formatting
```C++
#include <iostream>

/*
 ** Description Line
 ** Description Line
 */
class eftComseClass {
  private:
    byte          *data;
    time_t         time;
    vector<pair<double, double, double>> listOfPairs;

    void					RequestResponse(void);
  public:
    struct entityFlags_s {
      bool				condition; /* some comments */
      int         importantVar;
    } fl;

    struct exitFlags_s {
      static bool				condition     = false;	/* some comments */
      static int        importantVar  = 1;
    } fl;

    void                Cleanup(time_t time, int param);
  protected:
};

void OfSomeClass::RequestResponse(void) {
  switch(variable) {
    case a:
      RunFunction();
    break;
    case b:
      DoNothing();
    default:
    break;
  }
  return;
}

int OfSomeClass::Cleanup(time_t time, int param) {
  if ( !file ) {
    for(;;) {
      break;
    }
    return OK;
  }
  return NOK;
}

namespace MySpace {
  typedef enum {
    EN_STATIC,
    EN_CACHED,
    EN_CONTINUOUS
  } aModel_t;

  #define EVENT_INTEGER       'd'
  #define EVENT_FLOAT         'f'
}
```
# File and directory naming
* Only Linux style file/directory naming. For example: codeing_convention blockchain/ config.cpp
    eft_serivces/ dev_notes.txt

# Header file organizations
* Ensure that every header file \#includes all other necessary headers or forward-declarations
  necessary for independent compilation.
* No "everything_in_here" header file. For example "global.h". They make big troubles down the road!
* Put a set of related (and interdependent) functionality into a single file.
* Prefer forward declaration over \#includes whenever possible. This allows you to break the cyclic
  header dependencies.
* Separate your public interface from your private implementation at the filesystem level.
  Use include/ and src/ subdirectories, where include/ has all of my public headers, and src/ has
  all of my sources. and private headers. It will help us in the future when we need to make libraries.

