#
# Copyright 2014, NICTA
#
# This software may be distributed and modified according to the terms of
# the GNU General Public License version 2. Note that NO WARRANTY is provided.
# See "LICENSE_GPLv2.txt" for details.
#
# @TAG(NICTA_GPL)
#

TARGETS := $(notdir ${SOURCE_DIR}).cdl
ADL := $(notdir ${SOURCE_DIR}).camkes

Producer_CFILES := src/producer.c
Consumer_CFILES := src/consumer.c
Buffer_CFILES := src/buffer.c

include ${PWD}/tools/camkes/camkes.mk
