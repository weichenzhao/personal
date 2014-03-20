#!/bin/bash

SCRIPTDIR=$(cd $(dirname $0); pwd)

#
# we need information about the platform
#

# sorce it again, to really get valuable variables

# the emulator to run
if test "${PTXCONF_ARCH_STRING}" = "i386"; then
	ARCH_STRING="x86_64"
	# Machine to emulate
	QEMU_MACHINE=pc
else
	ARCH_STRING="${PTXCONF_ARCH_STRING}"
	# Machine to emulate
	QEMU_MACHINE=${PTXCONF_PLATFORM}
fi

# we should prefer the QEMU which comes with this BSP
QEMU_EXEC_PATH="${PTXCONF_SYSROOT_HOST}/bin"

# the QEMU to be used
QEMU_EXEC=qemu-system-${ARCH_STRING}

if [ -x "${QEMU_EXEC_PATH}/${QEMU_EXEC}" ]; then
	QEMU_EXEC="${QEMU_EXEC_PATH}/${QEMU_EXEC}"
fi

# disable this, if you want to have some graphics output
QEMU_NOGRAPHIC=--nographic

#
# 'user mode' network related settings
#
PLATFORM_IP="10.0.2.7"

# the port a 'telned' would connect to (in the emulated system)
TELNET_INTERNAL_PORT=23
# port QEMU opens at the host side to give access to the ${TELNET_INTERNAL_PORT}
TELNET_EXTERNAL_PORT=4444

# do the job
#echo ${QEMU_EXEC}
#echo ${QEMU_MACHINE}
#echo ${PTXDIST_PLATFORMDIR}

#qemu-system-i386 ${QEMU_NOGRAPHIC} \
qemu-system-i386 ${QEMU_NOGRAPHIC} \
	-M pc \
	-no-reboot \
	-redir tcp:${TELNET_EXTERNAL_PORT}:${PLATFORM_IP}:${TELNET_INTERNAL_PORT} \
	-kernel linuximage \
	-hda hd.img.qcow2 \
	-netdev user,id=user.0 -device e1000,netdev=user.0 \
	-net nic,vlan=1 \
	-net user,vlan=1 \

	#-loadvm chardev \
#use tap
#qemu-system-i386 ${QEMU_NOGRAPHIC} \
#	-M ${QEMU_MACHINE} \
#	-no-reboot \
#	-redir tcp:${TELNET_EXTERNAL_PORT}:${PLATFORM_IP}:${TELNET_INTERNAL_PORT} \
#	-kernel ${PTXDIST_PLATFORMDIR}/images/linuximage \
#	-hda ${PTXDIST_PLATFORMDIR}/images/hd.img \
#	-device e1000,netdev=net0,mac='DE:AD:BE:EF:12:23' -netdev tap,id=net0,script=/home/richard/qemu-ifup.sh \
#	-append "root=/dev/sda1 rw console=ttyS0,115200 debug"
