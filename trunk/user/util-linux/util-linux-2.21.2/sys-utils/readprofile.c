/*
 *  readprofile.c - used to read /proc/profile
 *
 *  Copyright (C) 1994,1996 Alessandro Rubini (rubini@ipvvis.unipv.it)
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * 1999-02-22 Arkadiusz Mi¶kiewicz <misiek@pld.ORG.PL>
 * - added Native Language Support
 * 1999-09-01 Stephane Eranian <eranian@cello.hpl.hp.com>
 * - 64bit clean patch
 * 3Feb2001 Andrew Morton <andrewm@uow.edu.au>
 * - -M option to write profile multiplier.
 * 2001-11-07 Werner Almesberger <wa@almesberger.net>
 * - byte order auto-detection and -n option
 * 2001-11-09 Werner Almesberger <wa@almesberger.net>
 * - skip step size (index 0)
 * 2002-03-09 John Levon <moz@compsoc.man.ac.uk>
 * - make maplineno do something
 * 2002-11-28 Mads Martin Joergensen +
 * - also try /boot/System.map-`uname -r`
 * 2003-04-09 Werner Almesberger <wa@almesberger.net>
 * - fixed off-by eight error and improved heuristics in byte order detection
 * 2003-08-12 Nikita Danilov <Nikita@Namesys.COM>
 * - added -s option; example of use:
 * "readprofile -s -m /boot/System.map-test | grep __d_lookup | sort -n -k3"
 */

#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <unistd.h>

#include "nls.h"
#include "xalloc.h"

#define S_LEN 128

/* These are the defaults */
static char defaultmap[]="/boot/System.map";
static char defaultpro[]="/proc/profile";

static FILE *myopen(char *name, char *mode, int *flag)
{
	int len = strlen(name);

	if (!strcmp(name + len - 3, ".gz")) {
		FILE *res;
		char *cmdline = xmalloc(len + 6);
		sprintf(cmdline, "zcat %s", name);
		res = popen(cmdline, mode);
		free(cmdline);
		*flag = 1;
		return res;
	}
	*flag = 0;
	return fopen(name, mode);
}

#ifndef BOOT_SYSTEM_MAP
#define BOOT_SYSTEM_MAP "/boot/System.map-"
#endif

static char *boot_uname_r_str(void)
{
	struct utsname uname_info;
	char *s;
	size_t len;

	if (uname(&uname_info))
		return "";
	len = strlen(BOOT_SYSTEM_MAP) + strlen(uname_info.release) + 1;
	s = xmalloc(len);
	strcpy(s, BOOT_SYSTEM_MAP);
	strcat(s, uname_info.release);
	return s;
}

static void __attribute__ ((__noreturn__))
    usage(FILE * out)
{
	fputs(USAGE_HEADER, out);
	fprintf(out, _(" %s [options]\n"), program_invocation_short_name);
	fputs(USAGE_OPTIONS, out);

	fprintf(out,
	      _(" -m, --mapfile <mapfile>   (defaults: \"%s\" and\n"), defaultmap);
	fprintf(out,
	      _("                                      \"%s\")\n"), boot_uname_r_str());
	fprintf(out,
	      _(" -p, --profile <pro-file>  (default:  \"%s\")\n"), defaultpro);
	fputs(_(" -M, --multiplier <mult>   set the profiling multiplier to <mult>\n"), out);
	fputs(_(" -i, --info                print only info about the sampling step\n"), out);
	fputs(_(" -v, --verbose             print verbose data\n"), out);
	fputs(_(" -a, --all                 print all symbols, even if count is 0\n"), out);
	fputs(_(" -b, --histbin             print individual histogram-bin counts\n"), out);
	fputs(_(" -s, --counters            print individual counters within functions\n"), out);
	fputs(_(" -r, --reset               reset all the counters (root only)\n"), out);
	fputs(_(" -n, --no-auto             disable byte order auto-detection\n"), out);
	fputs(USAGE_SEPARATOR, out);
	fputs(USAGE_HELP, out);
	fputs(USAGE_VERSION, out);
	fprintf(out, USAGE_MAN_TAIL("readprofile(8)"));
	exit(out == stderr ? EXIT_FAILURE : EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
	return 0;
}
