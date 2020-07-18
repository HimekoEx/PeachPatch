LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := PeachPatch

LOCAL_SRC_FILES := \
  MemTools.cpp \
  PeachMemory.cpp \
  Peach.cpp

LOCAL_C_INCLUDES := PeachPatch/

LOCAL_CFLAGS := -std=c11 -Wall -O2 -U_FORTIFY_SOURCE -fstack-protector-all
LOCAL_CPPFLAGS := -std=c++17 -fexceptions -frtti

include $(BUILD_STATIC_LIBRARY)
