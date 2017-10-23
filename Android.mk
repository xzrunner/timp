INNER_SAVED_LOCAL_PATH := $(LOCAL_PATH)

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := timp

LOCAL_C_INCLUDES  := \
	${CLIB_PATH} \
	${TIMP_SRC_PATH}/include/timp \
	${FS_SRC_PATH} \
	${BIMP_SRC_PATH}/include \
	${LOGGER_SRC_PATH} \
	${MEMMGR_SRC_PATH}/include \

LOCAL_SRC_FILES := \
	$(subst $(LOCAL_PATH)/,,$(shell find $(LOCAL_PATH) -name "*.cpp" -print)) \

include $(BUILD_STATIC_LIBRARY)

LOCAL_PATH := $(INNER_SAVED_LOCAL_PATH)