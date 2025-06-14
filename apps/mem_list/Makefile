#
# Copyright (C) 2015-2018,  Netronome Systems, Inc.  All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# @file         apps/lab_template/Makefile
# @brief        Makefile for a template lab
#

# Define src_dir FIRST - it is the directory that this makefile resides in
# MUST OCCUR BEFORE ANY include's (which will change MAKEFILE_LIST)
app_src_dir     := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
ROOT_SRC_DIR  ?= $(realpath $(app_src_dir)/../..)
base_dir        := $(ROOT_SRC_DIR)

microc_blocks_dir   := $(base_dir)/microc/blocks
microc_libs_dir     := $(base_dir)/microc/lib
microc_inc_dir      := $(base_dir)/microc/include
scripts_dir         := $(base_dir)/scripts

include $(scripts_dir)/Makefile.nfp.config
-include Makefile.nfp.config

FW_BUILD     := $(app_src_dir)
FW_FW        := $(app_src_dir)
include $(scripts_dir)/Makefile.templates

#
# Application definition starts here
#
$(eval $(call micro_c.compile_with_rtl,mem_list_obj,mem_list.c)) 
$(eval $(call micro_c.add_fw_libs,mem_list_obj,nfp)) 
$(eval $(call micro_c.add_std_libs,mem_list_obj,nfp_cluster_target intrinsic nfp_cluster_target_ring)) 
$(eval $(call micro_c.add_flags,mem_list_obj,-Qnctx=4)) 
$(eval $(call fw.add_obj,mem_list,mem_list_obj,i32.me0)) 
$(eval $(call fw.link_with_rtsyms,mem_list))
#
# Debug
#
include $(scripts_dir)/Makefile.debug

