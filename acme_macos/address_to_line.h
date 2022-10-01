//
//  address_to_line.h
//  acme_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 30/09/22 23:05
//
//
//  address_to_line.hpp
//  acme_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 30/09/22.
//

//
//  _001TryClassify_addr2line.c
//  acme_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 30/09/22.
//
//
//  aaa_addr2line.c
//  acme_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 30/09/22.
//

/* addr2line.c -- convert addresses to line number and function name
   Copyright 1997, 1998, 1999, 2000, 2001, 2002, 2003, 2004, 2006
   Free Software Foundation, Inc.
   Contributed by Ulrich Lauther <Ulrich.Lauther@mchp.siemens.de>

   This file is part of GNU Binutils.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.  */

/* Derived from objdump.c and nm.c by Ulrich.Lauther@mchp.siemens.de

   Usage:
   addr2line [options] addr addr ...
   or
   addr2line [options]

   both forms write results to stdout, the second form reads addresses
   to be converted from stdin.  */
#pragma once
//#include "config.h"
//#include <string.h>

#include <bfd.h>
//#include "getopt.h"
//#include "libiberty.h"
//#include "demangle.h"
//#include "bucomm.h"
//#include "budemang.h"

#include "acme_posix/address_to_line.h"

namespace acme_macos
{

class address_to_line :
virtual public ::acme_posix::address_to_line
{
public:
   
   bfd_boolean unwind_inlines;   /* -i, unwind inlined functions. */
   bfd_boolean with_functions;   /* -f, show function names.  */
   bfd_boolean do_demangle;      /* -C, demangle names.  */
   bfd_boolean base_names;      /* -s, strip directory names.  */
   
   int naddr;      /* Number of addresses to process.  */
   //char **addr;      /* Hex addresses to process.  */
   
   void * addr;
   
   asymbol **syms;      /* Symbol table.  */
   
   address_to_line();
   ~address_to_line() override;
   
   // simples usage ( addr2line <address> -> line and function name )
   int get_address_line(::string & strFunction, void * addr) override;
   
   void usage (FILE *, int);
   void slurp_symtab (bfd *);
   void find_address_in_section (bfd *, asection *, void *);
   void find_offset_in_section (bfd *, asection *);
   void translate_addresses (bfd *, asection *);
   
   /* Print a usage message to STREAM and exit with STATUS.  */
   
   //   void
   //   usage (FILE *stream, int status);   
   //   /* Read in the symbol table.  */
   
   void
   slurp_symtab (bfd *abfd);
   
   /* These global variables are used to pass information between
    translate_addresses and find_address_in_section.  */
   
   bfd_vma pc;
   const char *filename;
   const char *functionname;
   unsigned int line;
   bfd_boolean found;
   
   /* Look for an address in a section.  This is called via
    bfd_map_over_sections.  */
   
   void
   find_address_in_section (bfd *abfd, asection *section,
                            void *data ATTRIBUTE_UNUSED);
   
   /* Look for an offset in a section.  This is directly called.  */
   
   void
   find_offset_in_section (bfd *abfd, asection *section);
   
   /* Read hexadecimal addresses from stdin, translate into
    file_name:line_number and optionally function name.  */
   
   void
   translate_addresses (bfd *abfd, asection *section);
   
   /* Process a file.  Returns an exit value for main().  */
   
   int
   process_file (const char *file_name, const char *section_name,
                 const char *target);
   
   //   int
   //   main (int argc, char **argv);
   
   
};


} // namespace acme_macos

