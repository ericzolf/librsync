/*				       	-*- c-file-style: "bsd" -*-
 *
 * $Id$
 * 
 * Copyright (C) 2000 by Martin Pool
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * hs_hose: sloppy output function, good for writing to nonblocking
 * output channels.  This is the brother of hs_mapptr, except that it
 * doesn't support random access.
 *
 * We try to be smart by only copying data into the buffer if it can't
 * be written immediately.
 */

/*
 * hs_host_t structure
 *
 * This is a buffer filled by output from the library, and squirted
 * out into the kernel whenever possible.  */
struct hs_hose_t {
    int		tag;
    int		fd;
};
const int hs_hose_tag = 892138;


hs_hose_t
hs_hose_file(int fd)
{
    hs_hose_t		*hose;

    hose = _hs_alloc_struct(hs_hose_t);
    
    hose->tag = hs_hose_tag;
    hose->fd = fd;

    return hose;
}



void
hs_hose_close(hs_hose_t *hose)
{
    assert(hose->tag == hs_hose_tag);
    hs_bzero(hose, sizeof *hose);
    free(hose);
}


hs_result_t
hs_hose_out(hs_hose_t *hose, char const *buf, size_t len)
{
    ssize_t		ret;
    
    assert(hose->tag == hs_hose_tag);
    
    ret = write(host->fd, buf, len);
    if (ret < 0) {
	_hs_fatal("error hosing out data: %s",
		  strerror(errno));
    } else if (ret != len) {
	_hs_fatal("unexpected return from write: %d != %d",
		  ret, len);
    }

    return len;
}
