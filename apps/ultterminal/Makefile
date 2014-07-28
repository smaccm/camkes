#
# Copyright 2014, NICTA
#
# This software may be distributed and modified according to the terms of
# the GNU General Public License version 2. Note that NO WARRANTY is provided.
# See "LICENSE_GPLv2.txt" for details.
#
# @TAG(NICTA_GPL)
#

# Build system description of sources that comprise each component. This is
# mostly build system boiler plate and can be ignored unless you want to do
# something unconventional.

TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := ultterminal.camkes

SerialDriver_HFILES := \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/SerialDriver/*.h))
SerialDriver_CFILES := \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/SerialDriver/*.c))
SerialDriver_LIBS += ringbuffer

Switch_HFILES := \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Switch/*.h))
Switch_CFILES := \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/Switch/*.c))
Switch_LIBS += ringbuffer

MockLinux_HFILES := \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/MockLinux/*.h))
MockLinux_CFILES := \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/MockLinux/*.c))
MockLinux_LIBS += ringbuffer

VESADriver_HFILES := \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/VESADriver/*.h))
VESADriver_CFILES := \
    $(patsubst ${SOURCE_DIR}/%,%,$(wildcard ${SOURCE_DIR}/components/VESADriver/*.c))
VESADriver_LIBS += ringbuffer

include ${PWD}/tools/camkes/camkes.mk
