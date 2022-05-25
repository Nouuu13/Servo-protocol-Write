#!/bin/sh
PATH=/cygdrive/c/intelFPGA_lite/18.1/quartus/sopc_builder/bin:$PATH 
PATH=C:/intelFPGA_lite/18.1/quartus/sopc_builder/bin:$PATH 
sopc-create-header-files \
"$PWD/soc_system.sopcinfo" \
--single hps_0.h \
--module hps_0
