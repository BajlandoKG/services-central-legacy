# This file is generated by gyp; do not edit.

TOOLSET := target
TARGET := peerconnection_client
DEFS_Debug := '-D_FILE_OFFSET_BITS=64' \
	'-DCHROMIUM_BUILD' \
	'-DUSE_NSS=1' \
	'-DTOOLKIT_USES_GTK=1' \
	'-DGTK_DISABLE_SINGLE_INCLUDES=1' \
	'-DENABLE_REMOTING=1' \
	'-DENABLE_P2P_APIS=1' \
	'-DENABLE_CONFIGURATION_POLICY' \
	'-DENABLE_INPUT_SPEECH' \
	'-DENABLE_NOTIFICATIONS' \
	'-DENABLE_GPU=1' \
	'-DENABLE_EGLIMAGE=1' \
	'-DUSE_SKIA=1' \
	'-DENABLE_REGISTER_PROTOCOL_HANDLER=1' \
	'-DENABLE_WEB_INTENTS=1' \
	'-DENABLE_PLUGIN_INSTALLATION=1' \
	'-DWEBRTC_TARGET_PC' \
	'-DWEBRTC_LINUX' \
	'-DWEBRTC_THREAD_RR' \
	'-DFEATURE_ENABLE_SSL' \
	'-DFEATURE_ENABLE_VOICEMAIL' \
	'-DEXPAT_RELATIVE_PATH' \
	'-DWEBRTC_RELATIVE_PATH' \
	'-DLINUX' \
	'-DPOSIX' \
	'-D__STDC_FORMAT_MACROS' \
	'-DDYNAMIC_ANNOTATIONS_ENABLED=1' \
	'-DWTF_USE_DYNAMIC_ANNOTATIONS=1' \
	'-D_DEBUG'

# Flags passed to all source files.
CFLAGS_Debug := -Werror \
	-pthread \
	-fno-exceptions \
	-fno-strict-aliasing \
	-Wall \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers \
	-fvisibility=hidden \
	-pipe \
	-fPIC \
	-Wextra \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers \
	-pthread \
	-I/usr/include/gtk-2.0 \
	-I/usr/lib64/gtk-2.0/include \
	-I/usr/include/atk-1.0 \
	-I/usr/include/cairo \
	-I/usr/include/gdk-pixbuf-2.0 \
	-I/usr/include/pango-1.0 \
	-I/usr/include/glib-2.0 \
	-I/usr/lib64/glib-2.0/include \
	-I/usr/include/pixman-1 \
	-I/usr/include/freetype2 \
	-I/usr/include/libpng12 \
	-O0 \
	-g

# Flags passed to only C files.
CFLAGS_C_Debug := 

# Flags passed to only C++ files.
CFLAGS_CC_Debug := -fno-rtti \
	-fno-threadsafe-statics \
	-fvisibility-inlines-hidden \
	-Wsign-compare

INCS_Debug := -Isrc \
	-I. \
	-Isrc/modules/interface \
	-Ithird_party/libjingle/source

DEFS_Release := '-D_FILE_OFFSET_BITS=64' \
	'-DCHROMIUM_BUILD' \
	'-DUSE_NSS=1' \
	'-DTOOLKIT_USES_GTK=1' \
	'-DGTK_DISABLE_SINGLE_INCLUDES=1' \
	'-DENABLE_REMOTING=1' \
	'-DENABLE_P2P_APIS=1' \
	'-DENABLE_CONFIGURATION_POLICY' \
	'-DENABLE_INPUT_SPEECH' \
	'-DENABLE_NOTIFICATIONS' \
	'-DENABLE_GPU=1' \
	'-DENABLE_EGLIMAGE=1' \
	'-DUSE_SKIA=1' \
	'-DENABLE_REGISTER_PROTOCOL_HANDLER=1' \
	'-DENABLE_WEB_INTENTS=1' \
	'-DENABLE_PLUGIN_INSTALLATION=1' \
	'-DWEBRTC_TARGET_PC' \
	'-DWEBRTC_LINUX' \
	'-DWEBRTC_THREAD_RR' \
	'-DFEATURE_ENABLE_SSL' \
	'-DFEATURE_ENABLE_VOICEMAIL' \
	'-DEXPAT_RELATIVE_PATH' \
	'-DWEBRTC_RELATIVE_PATH' \
	'-DLINUX' \
	'-DPOSIX' \
	'-D__STDC_FORMAT_MACROS' \
	'-DNDEBUG' \
	'-DNVALGRIND' \
	'-DDYNAMIC_ANNOTATIONS_ENABLED=0'

# Flags passed to all source files.
CFLAGS_Release := -Werror \
	-pthread \
	-fno-exceptions \
	-fno-strict-aliasing \
	-Wall \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers \
	-fvisibility=hidden \
	-pipe \
	-fPIC \
	-Wextra \
	-Wno-unused-parameter \
	-Wno-missing-field-initializers \
	-pthread \
	-I/usr/include/gtk-2.0 \
	-I/usr/lib64/gtk-2.0/include \
	-I/usr/include/atk-1.0 \
	-I/usr/include/cairo \
	-I/usr/include/gdk-pixbuf-2.0 \
	-I/usr/include/pango-1.0 \
	-I/usr/include/glib-2.0 \
	-I/usr/lib64/glib-2.0/include \
	-I/usr/include/pixman-1 \
	-I/usr/include/freetype2 \
	-I/usr/include/libpng12 \
	-O2 \
	-fno-ident \
	-fdata-sections \
	-ffunction-sections

# Flags passed to only C files.
CFLAGS_C_Release := 

# Flags passed to only C++ files.
CFLAGS_CC_Release := -fno-rtti \
	-fno-threadsafe-statics \
	-fvisibility-inlines-hidden \
	-Wsign-compare

INCS_Release := -Isrc \
	-I. \
	-Isrc/modules/interface \
	-Ithird_party/libjingle/source

OBJS := $(obj).target/$(TARGET)/third_party/libjingle/source/talk/examples/peerconnection/client/conductor.o \
	$(obj).target/$(TARGET)/third_party/libjingle/source/talk/examples/peerconnection/client/defaults.o \
	$(obj).target/$(TARGET)/third_party/libjingle/source/talk/examples/peerconnection/client/linux/main.o \
	$(obj).target/$(TARGET)/third_party/libjingle/source/talk/examples/peerconnection/client/linux/main_wnd.o \
	$(obj).target/$(TARGET)/third_party/libjingle/source/talk/examples/peerconnection/client/peer_connection_client.o

# Add to the list of files we specially track dependencies for.
all_deps += $(OBJS)

# Make sure our dependencies are built before any of us.
$(OBJS): | $(obj).target/third_party/libjingle/libjingle_app.a $(obj).target/third_party/expat/expat.stamp $(obj).target/third_party/jsoncpp/libjsoncpp.a $(obj).target/third_party/libsrtp/libsrtp.a $(obj).target/src/modules/libvideo_capture_module.a $(obj).target/src/modules/libwebrtc_utility.a $(obj).target/src/modules/libaudio_coding_module.a $(obj).target/src/modules/libCNG.a $(obj).target/src/common_audio/libsignal_processing.a $(obj).target/src/modules/libG711.a $(obj).target/src/modules/libG722.a $(obj).target/src/modules/libiLBC.a $(obj).target/src/modules/libiSAC.a $(obj).target/src/modules/libiSACFix.a $(obj).target/src/modules/libPCM16B.a $(obj).target/src/modules/libNetEq.a $(obj).target/src/common_audio/libresampler.a $(obj).target/src/common_audio/libvad.a $(obj).target/src/system_wrappers/source/libsystem_wrappers.a $(obj).target/src/modules/libwebrtc_video_coding.a $(obj).target/src/modules/libwebrtc_i420.a $(obj).target/src/modules/libwebrtc_vp8.a $(obj).target/src/common_video/libwebrtc_libyuv.a $(obj).target/third_party/libyuv/libyuv.a $(obj).target/third_party/libvpx/libvpx.a $(obj).target/src/modules/libvideo_render_module.a $(obj).target/src/video_engine/libvideo_engine_core.a $(obj).target/src/common_video/libwebrtc_jpeg.a $(obj).target/third_party/libjpeg_turbo/libjpeg_turbo.a $(obj).target/src/modules/libmedia_file.a $(obj).target/src/modules/librtp_rtcp.a $(obj).target/src/modules/libudp_transport.a $(obj).target/src/modules/libvideo_processing.a $(obj).target/src/modules/libvideo_processing_sse2.a $(obj).target/src/voice_engine/libvoice_engine_core.a $(obj).target/src/modules/libaudio_conference_mixer.a $(obj).target/src/modules/libaudio_processing.a $(obj).target/src/modules/libaec.a $(obj).target/src/modules/libapm_util.a $(obj).target/src/modules/libaec_sse2.a $(obj).target/src/modules/libaecm.a $(obj).target/src/modules/libagc.a $(obj).target/src/modules/libns.a $(obj).target/src/modules/libaudioproc_debug_proto.a $(obj).target/third_party/protobuf/libprotobuf_lite.a $(obj).target/src/modules/libaudio_device.a $(obj).target/third_party/libjingle/libjingle_p2p.a $(obj).target/third_party/libjingle/libjingle.a

# CFLAGS et al overrides must be target-local.
# See "Target-specific Variable Values" in the GNU Make manual.
$(OBJS): TOOLSET := $(TOOLSET)
$(OBJS): GYP_CFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_C_$(BUILDTYPE))
$(OBJS): GYP_CXXFLAGS := $(DEFS_$(BUILDTYPE)) $(INCS_$(BUILDTYPE))  $(CFLAGS_$(BUILDTYPE)) $(CFLAGS_CC_$(BUILDTYPE))

# Suffix rules, putting all outputs into $(obj).

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(srcdir)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# Try building from generated source, too.

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj).$(TOOLSET)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

$(obj).$(TOOLSET)/$(TARGET)/%.o: $(obj)/%.cc FORCE_DO_CMD
	@$(call do_cmd,cxx,1)

# End of this set of suffix rules
### Rules for final target.
LDFLAGS_Debug := -pthread \
	-Wl,-z,noexecstack \
	-fPIC \
	-B$(builddir)/../../third_party/gold

LDFLAGS_Release := -pthread \
	-Wl,-z,noexecstack \
	-fPIC \
	-B$(builddir)/../../third_party/gold \
	-Wl,-O1 \
	-Wl,--as-needed \
	-Wl,--gc-sections

LIBS := -lgtk-x11-2.0 \
	-lgdk-x11-2.0 \
	-latk-1.0 \
	-lgio-2.0 \
	-lpangoft2-1.0 \
	-lpangocairo-1.0 \
	-lgdk_pixbuf-2.0 \
	-lpng12 \
	-lm \
	-lcairo \
	-lpango-1.0 \
	-lfreetype \
	-lfontconfig \
	-lgobject-2.0 \
	-lgmodule-2.0 \
	-lgthread-2.0 \
	-lrt \
	-lglib-2.0 \
	-lX11 \
	-lXext \
	-lexpat \
	-ldl \
	-lasound \
	-lpulse

$(builddir)/peerconnection_client: GYP_LDFLAGS := $(LDFLAGS_$(BUILDTYPE))
$(builddir)/peerconnection_client: LIBS := $(LIBS)
$(builddir)/peerconnection_client: LD_INPUTS := $(OBJS) $(obj).target/third_party/libjingle/libjingle_app.a $(obj).target/third_party/jsoncpp/libjsoncpp.a $(obj).target/third_party/libsrtp/libsrtp.a $(obj).target/src/modules/libvideo_capture_module.a $(obj).target/src/modules/libwebrtc_utility.a $(obj).target/src/modules/libaudio_coding_module.a $(obj).target/src/modules/libCNG.a $(obj).target/src/common_audio/libsignal_processing.a $(obj).target/src/modules/libG711.a $(obj).target/src/modules/libG722.a $(obj).target/src/modules/libiLBC.a $(obj).target/src/modules/libiSAC.a $(obj).target/src/modules/libiSACFix.a $(obj).target/src/modules/libPCM16B.a $(obj).target/src/modules/libNetEq.a $(obj).target/src/common_audio/libresampler.a $(obj).target/src/common_audio/libvad.a $(obj).target/src/system_wrappers/source/libsystem_wrappers.a $(obj).target/src/modules/libwebrtc_video_coding.a $(obj).target/src/modules/libwebrtc_i420.a $(obj).target/src/modules/libwebrtc_vp8.a $(obj).target/src/common_video/libwebrtc_libyuv.a $(obj).target/third_party/libyuv/libyuv.a $(obj).target/third_party/libvpx/libvpx.a $(obj).target/src/modules/libvideo_render_module.a $(obj).target/src/video_engine/libvideo_engine_core.a $(obj).target/src/common_video/libwebrtc_jpeg.a $(obj).target/third_party/libjpeg_turbo/libjpeg_turbo.a $(obj).target/src/modules/libmedia_file.a $(obj).target/src/modules/librtp_rtcp.a $(obj).target/src/modules/libudp_transport.a $(obj).target/src/modules/libvideo_processing.a $(obj).target/src/modules/libvideo_processing_sse2.a $(obj).target/src/voice_engine/libvoice_engine_core.a $(obj).target/src/modules/libaudio_conference_mixer.a $(obj).target/src/modules/libaudio_processing.a $(obj).target/src/modules/libaec.a $(obj).target/src/modules/libapm_util.a $(obj).target/src/modules/libaec_sse2.a $(obj).target/src/modules/libaecm.a $(obj).target/src/modules/libagc.a $(obj).target/src/modules/libns.a $(obj).target/src/modules/libaudioproc_debug_proto.a $(obj).target/third_party/protobuf/libprotobuf_lite.a $(obj).target/src/modules/libaudio_device.a $(obj).target/third_party/libjingle/libjingle_p2p.a $(obj).target/third_party/libjingle/libjingle.a
$(builddir)/peerconnection_client: TOOLSET := $(TOOLSET)
$(builddir)/peerconnection_client: $(OBJS) $(obj).target/third_party/libjingle/libjingle_app.a $(obj).target/third_party/jsoncpp/libjsoncpp.a $(obj).target/third_party/libsrtp/libsrtp.a $(obj).target/src/modules/libvideo_capture_module.a $(obj).target/src/modules/libwebrtc_utility.a $(obj).target/src/modules/libaudio_coding_module.a $(obj).target/src/modules/libCNG.a $(obj).target/src/common_audio/libsignal_processing.a $(obj).target/src/modules/libG711.a $(obj).target/src/modules/libG722.a $(obj).target/src/modules/libiLBC.a $(obj).target/src/modules/libiSAC.a $(obj).target/src/modules/libiSACFix.a $(obj).target/src/modules/libPCM16B.a $(obj).target/src/modules/libNetEq.a $(obj).target/src/common_audio/libresampler.a $(obj).target/src/common_audio/libvad.a $(obj).target/src/system_wrappers/source/libsystem_wrappers.a $(obj).target/src/modules/libwebrtc_video_coding.a $(obj).target/src/modules/libwebrtc_i420.a $(obj).target/src/modules/libwebrtc_vp8.a $(obj).target/src/common_video/libwebrtc_libyuv.a $(obj).target/third_party/libyuv/libyuv.a $(obj).target/third_party/libvpx/libvpx.a $(obj).target/src/modules/libvideo_render_module.a $(obj).target/src/video_engine/libvideo_engine_core.a $(obj).target/src/common_video/libwebrtc_jpeg.a $(obj).target/third_party/libjpeg_turbo/libjpeg_turbo.a $(obj).target/src/modules/libmedia_file.a $(obj).target/src/modules/librtp_rtcp.a $(obj).target/src/modules/libudp_transport.a $(obj).target/src/modules/libvideo_processing.a $(obj).target/src/modules/libvideo_processing_sse2.a $(obj).target/src/voice_engine/libvoice_engine_core.a $(obj).target/src/modules/libaudio_conference_mixer.a $(obj).target/src/modules/libaudio_processing.a $(obj).target/src/modules/libaec.a $(obj).target/src/modules/libapm_util.a $(obj).target/src/modules/libaec_sse2.a $(obj).target/src/modules/libaecm.a $(obj).target/src/modules/libagc.a $(obj).target/src/modules/libns.a $(obj).target/src/modules/libaudioproc_debug_proto.a $(obj).target/third_party/protobuf/libprotobuf_lite.a $(obj).target/src/modules/libaudio_device.a $(obj).target/third_party/libjingle/libjingle_p2p.a $(obj).target/third_party/libjingle/libjingle.a FORCE_DO_CMD
	$(call do_cmd,link)

all_deps += $(builddir)/peerconnection_client
# Add target alias
.PHONY: peerconnection_client
peerconnection_client: $(builddir)/peerconnection_client

# Add executable to "all" target.
.PHONY: all
all: $(builddir)/peerconnection_client

