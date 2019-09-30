include	$(WORK)/build/makefile.cc.header
##########################################
MODULES_BASE      := $(WORK)/Cataleya/src
#RV_LIB_DIR        := ReleaseDnsMCastIpv6Nolog
RV_LIB_DIR        := ReleaseWsDnsTlsIpv6Nolog
RV_SIP_STACK_HOME  := $(WORK)/thirdparty/radvision/sip/Spirent_SIP_Linux_Ver_7.2/SipTK_Linux_src/
MODULES           :=  main messages config sip tasks
INCLUDES          := $(WORK)/common/base/src/utils \
                     $(WORK)/common/base/src/logger \
                     $(WORK)/common/base/src/protocol \
                     $(WORK)/common/base/src/transport \
                     $(WORK)/common/config/src/ \
                     $(WORK)/common/sip/base/src/ \
                     $(WORK)/common/config/src/ \
                     $(WORK)/common/stats/include/ \
                     $(WORK)/common/mirroring/src/ \
                     $(WORK)/common/alarms/src/ \
                     $(WORK)/common/admin/src \
                     $(WORK)/thirdparty/protobuf/protobuf-2.4.1/include/ \
                     $(WORK)/thirdparty/sctp/sctp-1.0.15/include/ \
                     $(WORK)/thirdparty/re2/re2-20130802/include/re2/ \
                     $(WORK)/thirdparty/re2/re2-20130802/include/ \
                     $(WORK)/thirdparty/zlog/include/ \
                     $(RV_SIP_STACK_HOME)/include/sip \
                     $(RV_SIP_STACK_HOME)/include/common \
                     $(RV_SIP_STACK_HOME)/include/ads \
                     $(RV_SIP_STACK_HOME)/include/sdp \
                     $(RV_SIP_STACK_HOME)/common/config

USR_LIBS          := $(WORK)/common/base/lib/libcommon.a \
                     $(WORK)/common/sip/base/lib/libsipcommon.a \
                     $(WORK)/common/config/lib/libconfig.a \
                     $(WORK)/common/alarms/lib/libalarms.a \
                     $(WORK)/common/ruletree/lib/libruletree.a \
                     $(WORK)/thirdparty/zlog/lib/libzlog.a \
                     $(WORK)/common/admin/lib/libadmin.a \
                     $(WORK)/thirdparty/re2/re2-20130802/lib/libre2.a \
                     $(WORK)/thirdparty/sctp/sctp-1.0.15/lib/libsctp.a \
                     $(WORK)/thirdparty/protobuf/protobuf-2.4.1/lib/libprotobuf.a \
                     $(RV_SIP_STACK_HOME)/binaries/linux_redhat-Server_64bits/$(RV_LIB_DIR)/lib/librvads.a \
                     $(RV_SIP_STACK_HOME)/binaries/linux_redhat-Server_64bits/$(RV_LIB_DIR)/lib/librvcommon.a  \
                     $(RV_SIP_STACK_HOME)/binaries/linux_redhat-Server_64bits/$(RV_LIB_DIR)/lib/librvsdp.a \
                     $(RV_SIP_STACK_HOME)/binaries/linux_redhat-Server_64bits/$(RV_LIB_DIR)/lib/librvsip.a \
                     $(RV_SIP_STACK_HOME)/binaries/linux_redhat-Server_64bits/$(RV_LIB_DIR)/lib/libsimpleOSUtils.a

TARGET            :=  Cataleya
USR_CFLAGS        := -std=c++0x -DRV_WEBSOCKET -DRV_CFLAG_NOLOG
USR_LDFLAGS       := -lssl -lcrypto -lstdc++ -lpcap -lpthread
##########################################
include	$(WORK)/build/makefile.footer
