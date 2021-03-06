/* $NetBSD: t_setdomainname.c,v 1.1 2011/06/03 05:42:09 jruoho Exp $ */

/*-
 * Copyright (c) 2011 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Jukka Ruohonen.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <sys/cdefs.h>
__RCSID("$NetBSD: t_setdomainname.c,v 1.1 2011/06/03 05:42:09 jruoho Exp $");

#include <sys/param.h>

#include <atf-c.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

static char domain[MAXHOSTNAMELEN];

static const char domains[][MAXHOSTNAMELEN] = {
	"1234567890",
	"abcdefghijklmnopqrst",
	"!#�%&/(..xasS812=!=!(I(!;X;;X.as.dasa=?;,..<>|**^�",
	"--------------------------------------------------------------------"
};

ATF_TC_WITH_CLEANUP(setdomainname_basic);
ATF_TC_HEAD(setdomainname_basic, tc)
{
	atf_tc_set_md_var(tc, "descr", "A basic test of setdomainname(3)");
	atf_tc_set_md_var(tc, "require.user", "root");
}

ATF_TC_BODY(setdomainname_basic, tc)
{
	char name[MAXHOSTNAMELEN];
	size_t i;

	for (i = 0; i < __arraycount(domains); i++) {

		(void)memset(name, 0, sizeof(name));

		ATF_REQUIRE(setdomainname(domains[i],sizeof(domains[i])) == 0);
		ATF_REQUIRE(getdomainname(name, sizeof(name)) == 0);
		ATF_REQUIRE(strcmp(domains[i], name) == 0);
	}

	(void)setdomainname(domain, sizeof(domain));
}

ATF_TC_CLEANUP(setdomainname_basic, tc)
{
	(void)setdomainname(domain, sizeof(domain));
}

ATF_TC_WITH_CLEANUP(setdomainname_limit);
ATF_TC_HEAD(setdomainname_limit, tc)
{
	atf_tc_set_md_var(tc, "descr", "Too long domain name errors out?");
	atf_tc_set_md_var(tc, "require.user", "root");
}

ATF_TC_BODY(setdomainname_limit, tc)
{
	char name[MAXHOSTNAMELEN + 1];

	(void)memset(name, 0, sizeof(name));

	ATF_REQUIRE(setdomainname(name, sizeof(name)) == -1);
}

ATF_TC_CLEANUP(setdomainname_limit, tc)
{
	(void)setdomainname(domain, sizeof(domain));
}

ATF_TC_WITH_CLEANUP(setdomainname_perm);
ATF_TC_HEAD(setdomainname_perm, tc)
{
	atf_tc_set_md_var(tc, "descr", "Can normal user set the domain name?");
	atf_tc_set_md_var(tc, "require.user", "unprivileged");
}

ATF_TC_BODY(setdomainname_perm, tc)
{

	errno = 0;

	ATF_REQUIRE_ERRNO(EPERM, setdomainname(domain, sizeof(domain)) == -1);
}

ATF_TC_CLEANUP(setdomainname_perm, tc)
{
	(void)setdomainname(domain, sizeof(domain));
}

ATF_TP_ADD_TCS(tp)
{

	(void)memset(domain, 0, sizeof(domain));

	ATF_REQUIRE(getdomainname(domain, sizeof(domain)) == 0);

	ATF_TP_ADD_TC(tp, setdomainname_basic);
	ATF_TP_ADD_TC(tp, setdomainname_limit);
	ATF_TP_ADD_TC(tp, setdomainname_perm);

	return atf_no_error();
}
