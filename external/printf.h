/*
File: printf.h

Effective as of 8th February 2021 this library can be licensed either under MIT, BSD or LGPL license.

------------------------------------------------------------------------------------------------
MIT LICENSE

Copyright (C) 2004,2008  Kustaa Nyholm

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense,  and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.



------------------------------------------------------------------------------------------------
LGPL LICENSE

Copyright (C) 2004,2008  Kustaa Nyholm

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


------------------------------------------------------------------------------------------------
BSD 2-CLAUSE LICENSE

Copyright (C) 2004,2008  Kustaa Nyholm

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
OF THE POSSIBILITY OF SUCH DAMAGE.


------------------------------------------------------------------------------------------------

This library is realy just two files: 'printf.h' and 'printf.c'.

They provide a simple and small (+100 loc) printf functionality to
be used in embedded systems.

I've found them so usefull in debugging that I do not bother with a
debugger at all.

They are distributed in source form, so to use them, just compile them
into your project.

The formats supported by this implementation are: 'd' 'u' 'c' 's' 'x' 'X'.

Zero padding and field width (limited to 255) are also supported.

The memory foot print of course depends on the target cpu, compiler and
compiler options, but a rough guestimate (based on a HC08 target) is about
600 - 1100 bytes for code and some twenty bytes of static data.  Note
that this printf is not re-entrant.

Note that the code expects that int size is 16 bits, and that char is
8 bits.

To use the printf you need to supply your own character output function,
something like :

void putchar (char c)
	{
	while (!SERIAL_PORT_EMPTY) ;
	SERIAL_PORT_TX_REGISTER = c;
	}


The printf function is actually a macro that translates to 'tfp_printf'.
This makes it possible to use it along with 'stdio.h' printf's in a single
source file. You just need to undef the names before you include the 'stdio.h'.
Note that these are not function-like macros, so if you have variables
or struct members with these names, things will explode in your face.
Without variadic macros this is the best we can do. If it is a  problem
just give up the macros and use the functions directly or rename them.

For further details see source code.

regs Kusti, 26.2.2008
*/


#ifndef __TFP_PRINTF__
#define __TFP_PRINTF__

#include "va_args.h"

void tfp_printf(char *fmt, ...);

#define printf tfp_printf

#endif
