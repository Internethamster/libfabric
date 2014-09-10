/*
 * Copyright (c) 2014 Intel Corporation, Inc.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#if HAVE_CONFIG_H
#  include <config.h>
#endif /* HAVE_CONFIG_H */

#include "sock.h"


static int sock_getinfo(int version, const char *node, const char *service,
			uint64_t flags, struct fi_info *hints, struct fi_info **info)
{
	if (hints) {
		switch (hints->type) {
		case FID_RDM:
			return sock_rdm_getinfo(version, node, service, flags,
						hints, info);
		default:
			return -FI_ENODATA;
		}
	} else {
		/* Call all socket endpoint providers. */
		return sock_rdm_getinfo(version, node, service, flags,
					hints, info);
	}

	return -FI_ENODATA;
}


static struct fi_ops_prov sock_ops = {
	.size = sizeof(struct fi_ops_prov),
	.getinfo = sock_getinfo,
	.freeinfo = NULL, /* use default */
	.domain = sock_domain,
	.fabric = __fi_fabric,
};

void sock_ini(void)
{
	(void) fi_register(&sock_ops);
}

void sock_fini(void)
{
}
