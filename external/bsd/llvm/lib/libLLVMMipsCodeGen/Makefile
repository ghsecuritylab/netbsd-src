#	$NetBSD: Makefile,v 1.8 2012/02/28 17:09:30 joerg Exp $

LIB=	LLVMMipsCodeGen

.include <bsd.init.mk>

.PATH: ${LLVM_SRCDIR}/lib/Target/Mips

SRCS+=	MipsAnalyzeImmediate.cpp \
	MipsAsmPrinter.cpp \
	MipsCodeEmitter.cpp \
	MipsDelaySlotFiller.cpp \
	MipsEmitGPRestore.cpp \
	MipsExpandPseudo.cpp \
	MipsFrameLowering.cpp \
	MipsInstrInfo.cpp \
	MipsISelDAGToDAG.cpp \
	MipsISelLowering.cpp \
	MipsJITInfo.cpp \
	MipsMachineFunction.cpp \
	MipsMCInstLower.cpp \
	MipsRegisterInfo.cpp \
	MipsSubtarget.cpp \
	MipsTargetMachine.cpp \
	MipsTargetObjectFile.cpp \
	MipsSelectionDAGInfo.cpp

TABLEGEN_SRC=		Mips.td
TABLEGEN_INCLUDES=	-I${LLVM_SRCDIR}/lib/Target/Mips
TABLEGEN_OUTPUT= \
	MipsGenRegisterInfo.inc|-gen-register-info \
	MipsGenInstrInfo.inc|-gen-instr-info \
	MipsGenAsmWriter.inc|-gen-asm-writer \
	MipsGenCallingConv.inc|-gen-callingconv \
	MipsGenCodeEmitter.inc|-gen-emitter \
	MipsGenDAGISel.inc|-gen-dag-isel \
	MipsGenMCCodeEmitter.inc|-gen-emitter^-mc-emitter \
	MipsGenSubtargetInfo.inc|-gen-subtarget

.include "${.PARSEDIR}/../../tablegen.mk"

.if defined(HOSTLIB)
.include <bsd.hostlib.mk>
.else
.include <bsd.lib.mk>
.endif
