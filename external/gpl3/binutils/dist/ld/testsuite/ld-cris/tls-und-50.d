#source: tls-ie-8.s --pic
#as: --no-underscore --em=criself
#ld: -m crislinux --shared
#readelf: -a -x 7

# Undefined reference for a R_CRIS_16_GOT_TPREL in a DSO.  Not an
# error; it's ok for a DSO to have undefined references upon creation
# for global symbols that can be overridden.  Just make sure GOT,
# dynsyms and dynrelocs look right.

#...
Relocation section '.rela.dyn' at offset 0x.* contains 1 entries:
 Offset +Info +Type +Sym.Value +Sym. Name \+ Addend
000021ec +0000021c R_CRIS_32_TPREL +0+ +x \+ 0

There are no unwind sections in this file.

Symbol table '.dynsym' contains . entries:
 +Num: +Value +Size +Type +Bind +Vis +Ndx +Name
#...
 +[0-9]: 00000000 +0 +TLS +GLOBAL +DEFAULT +UND x
#...
Symbol table '.symtab' contains .. entries:
#...
Hex dump of section '.got':
  0x0+21e0 68210000 00000000 00000000 00000000 .*
