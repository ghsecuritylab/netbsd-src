#	$NetBSD: Makefile,v 1.1 2012/01/22 03:53:29 tsutsui Exp $

.include <bsd.own.mk>

INSTIMGBASE=	amd64inst		# gives ${IMGBASE}.img

BOOTDISK=	sd0			# for USB flash etc.
IMAGEMB=	550			# for all installation binaries

PRIMARY_BOOT=		bootxx_ffsv1
SECONDARY_BOOT=		boot
SECONDARY_BOOT_ARG=	# unnecessary

USE_MBR=		yes

CLEANFILES+=	boot.cfg

prepare_md_post:
	${TOOL_SED}							\
	    -e "s/@@MACHINE@@/${MACHINE}/"				\
	    -e "s/@@VERSION@@/${DISTRIBVER}/"				\
	    < ${.CURDIR}/boot.cfg.in > boot.cfg

DISTRIBDIR!= cd ${.CURDIR}/../.. ; pwd
SYSINSTDIR!= cd ${DISTRIBDIR}/utils/sysinst/arch/${MACHINE} && ${PRINTOBJDIR}

SPEC_EXTRA=		${.CURDIR}/spec.inst
IMGFILE_EXTRA=								\
	${DISTRIBDIR}/common/10-resolv.conf	libexec/dhcpcd-hooks	\
	${DISTRIBDIR}/common/99-print-sysinst	libexec/dhcpcd-hooks	\
	${.CURDIR}/etc.ttys		etc/ttys			\
	${.CURDIR}/etc.rc		etc/rc				\
	${.CURDIR}/install.sh		.				\
	${.OBJDIR}/boot.cfg		.				\
	${SYSINSTDIR}/sysinstmsgs.de	.				\
	${SYSINSTDIR}/sysinstmsgs.es	.				\
	${SYSINSTDIR}/sysinstmsgs.fr	.				\
	${SYSINSTDIR}/sysinstmsgs.pl	.				\
	${SYSINSTDIR}/sysinst		.

.include "${DISTRIBDIR}/common/bootimage/Makefile.installimage"
