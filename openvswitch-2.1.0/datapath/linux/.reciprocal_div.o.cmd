cmd_/home/richard/personal/openvswitch-2.1.0/datapath/linux/reciprocal_div.o := gcc -Wp,-MD,/home/richard/personal/openvswitch-2.1.0/datapath/linux/.reciprocal_div.o.d  -nostdinc -isystem /usr/lib/gcc/i686-linux-gnu/4.6/include -I/home/richard/personal/openvswitch-2.1.0/include -I/home/richard/personal/openvswitch-2.1.0/datapath/linux/compat -I/home/richard/personal/openvswitch-2.1.0/datapath/linux/compat/include  -I/usr/src/linux-headers-3.5.0-23-generic/arch/x86/include -Iarch/x86/include/generated -Iinclude  -include /usr/src/linux-headers-3.5.0-23-generic/include/linux/kconfig.h -Iubuntu/include  -D__KERNEL__ -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -O2 -m32 -msoft-float -mregparm=3 -freg-struct-return -mpreferred-stack-boundary=2 -march=i686 -mtune=generic -maccumulate-outgoing-args -Wa,-mtune=generic32 -ffreestanding -fstack-protector -DCONFIG_AS_CFI=1 -DCONFIG_AS_CFI_SIGNAL_FRAME=1 -DCONFIG_AS_CFI_SECTIONS=1 -DCONFIG_AS_AVX=1 -pipe -Wno-sign-compare -fno-asynchronous-unwind-tables -mno-sse -mno-mmx -mno-sse2 -mno-3dnow -mno-avx -Wframe-larger-than=1024 -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -pg -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -DCC_HAVE_ASM_GOTO -DVERSION=\"2.1.0\" -I/home/richard/personal/openvswitch-2.1.0/datapath/linux/.. -I/home/richard/personal/openvswitch-2.1.0/datapath/linux/.. -g -include /home/richard/personal/openvswitch-2.1.0/datapath/linux/kcompat.h  -DMODULE  -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(reciprocal_div)"  -D"KBUILD_MODNAME=KBUILD_STR(openvswitch)" -c -o /home/richard/personal/openvswitch-2.1.0/datapath/linux/.tmp_reciprocal_div.o /home/richard/personal/openvswitch-2.1.0/datapath/linux/reciprocal_div.c

source_/home/richard/personal/openvswitch-2.1.0/datapath/linux/reciprocal_div.o := /home/richard/personal/openvswitch-2.1.0/datapath/linux/reciprocal_div.c

deps_/home/richard/personal/openvswitch-2.1.0/datapath/linux/reciprocal_div.o := \
  /home/richard/personal/openvswitch-2.1.0/datapath/linux/kcompat.h \
  /usr/src/linux-headers-3.5.0-23-generic/arch/x86/include/asm/div64.h \
    $(wildcard include/config/x86/32.h) \
  /home/richard/personal/openvswitch-2.1.0/include/linux/types.h \
  /home/richard/personal/openvswitch-2.1.0/datapath/linux/compat/include/linux/types.h \
  include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /usr/src/linux-headers-3.5.0-23-generic/arch/x86/include/asm/types.h \
  include/asm-generic/types.h \
  include/asm-generic/int-ll64.h \
  /usr/src/linux-headers-3.5.0-23-generic/arch/x86/include/asm/bitsperlong.h \
  include/asm-generic/bitsperlong.h \
  include/linux/posix_types.h \
  /home/richard/personal/openvswitch-2.1.0/datapath/linux/compat/include/linux/stddef.h \
  include/linux/stddef.h \
  /home/richard/personal/openvswitch-2.1.0/datapath/linux/compat/include/linux/compiler.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  /home/richard/personal/openvswitch-2.1.0/datapath/linux/compat/include/linux/compiler-gcc.h \
  include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  include/linux/compiler-gcc4.h \
  /usr/src/linux-headers-3.5.0-23-generic/arch/x86/include/asm/posix_types.h \
  /usr/src/linux-headers-3.5.0-23-generic/arch/x86/include/asm/posix_types_32.h \
  include/asm-generic/posix_types.h \
  /home/richard/personal/openvswitch-2.1.0/datapath/linux/compat/include/linux/log2.h \
  include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  include/linux/bitops.h \
  /usr/src/linux-headers-3.5.0-23-generic/arch/x86/include/asm/bitops.h \
    $(wildcard include/config/x86/64.h) \
    $(wildcard include/config/x86/cmov.h) \
  /usr/src/linux-headers-3.5.0-23-generic/arch/x86/include/asm/alternative.h \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/paravirt.h) \
  include/linux/stringify.h \
  /usr/src/linux-headers-3.5.0-23-generic/arch/x86/include/asm/asm.h \
  /usr/src/linux-headers-3.5.0-23-generic/arch/x86/include/asm/cpufeature.h \
    $(wildcard include/config/x86/invlpg.h) \
  /usr/src/linux-headers-3.5.0-23-generic/arch/x86/include/asm/required-features.h \
    $(wildcard include/config/x86/minimum/cpu/family.h) \
    $(wildcard include/config/math/emulation.h) \
    $(wildcard include/config/x86/pae.h) \
    $(wildcard include/config/x86/cmpxchg64.h) \
    $(wildcard include/config/x86/use/3dnow.h) \
    $(wildcard include/config/x86/p6/nop.h) \
  include/asm-generic/bitops/fls64.h \
  include/asm-generic/bitops/find.h \
    $(wildcard include/config/generic/find/first/bit.h) \
  include/asm-generic/bitops/sched.h \
  /usr/src/linux-headers-3.5.0-23-generic/arch/x86/include/asm/arch_hweight.h \
  include/asm-generic/bitops/const_hweight.h \
  include/asm-generic/bitops/le.h \
  /usr/src/linux-headers-3.5.0-23-generic/arch/x86/include/asm/byteorder.h \
  include/linux/byteorder/little_endian.h \
  include/linux/swab.h \
  /usr/src/linux-headers-3.5.0-23-generic/arch/x86/include/asm/swab.h \
    $(wildcard include/config/x86/bswap.h) \
  include/linux/byteorder/generic.h \
  include/asm-generic/bitops/ext2-atomic-setbit.h \
  include/linux/reciprocal_div.h \
  include/linux/version.h \

/home/richard/personal/openvswitch-2.1.0/datapath/linux/reciprocal_div.o: $(deps_/home/richard/personal/openvswitch-2.1.0/datapath/linux/reciprocal_div.o)

$(deps_/home/richard/personal/openvswitch-2.1.0/datapath/linux/reciprocal_div.o):
