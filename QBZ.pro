TEMPLATE = app
CONFIG	+= designer ui
QT += opengl declarative

RESOURCES += QBZ.qrc
INCLUDEPATH += . src

macx {
	INCLUDEPATH += \
		/usr/include \
		/usr/local/include
}

unix {
	INCLUDEPATH += \
		/usr/include \
		/usr/local/include \
		/opt/local/include \
}

FORMS = ui/mainwindow.ui

HEADERS += src/qbz.h \
    src/Ext/RtMidi.h \
    src/Ext/RtError.h \
    src/Ext/CppTweener.h \
    src/GL/rendertarget.h \
    src/GL/qbz_vbo.h \
    src/GL/qbz_terrain.h \
    src/GL/qbz_skybox.h \
    src/GL/qbz_shader.h \
    src/GL/qbz_renderwidget.h \
    src/GL/qbz_renderprogram.h \
    src/GL/qbz_mesh.h \
    src/GL/qbz_fbo.h \
    src/GL/qbz_depthfbo.h \
    src/GL/qbz_deferredrenderer.h \
    src/Network/qbz_network.h \
    src/System/registry.h \
    src/System/qbz_tgatexture.h \
    src/System/qbz_ofwidget.h \
    src/System/qbz_midithread.h \
    src/System/qbz_library.h \
    src/System/qbz_glwidget.h \
    src/System/qbz_glthread.h \
    src/System/qbz_clam.h \
    src/System/qbz_clam_pitchprofile.h \
    src/System/mainwindow.h \
    src/World/qbz_world.h \
    src/World/qbz_projectionmapper.h \
    src/World/qbz_projectionarea.h \
    src/World/qbz_projection_simple.h \
    src/World/qbz_plane.h \
    src/World/qbz_path.h \
    src/World/qbz_particlebase.h \
    src/World/qbz_model.h \
    src/World/qbz_lightdot.h \
    src/World/qbz_light.h \
    src/World/qbz_harmonics.h \
    src/World/qbz_camera.h \
    src/World/qbz_animator.h \
    src/qbz_composer.h \
    src/qbz_baseapp.h
		   
SOURCES += src/main.cpp \
    src/Ext/RtMidi.cpp \
    src/Ext/CppTweener.cpp \
    src/GL/rendertarget.cpp \
    src/GL/qbz_vbo.cpp \
    src/GL/qbz_terrain.cpp \
    src/GL/qbz_skybox.cpp \
    src/GL/qbz_shader.cpp \
    src/GL/qbz_renderwidget.cpp \
    src/GL/qbz_renderprogram.cpp \
    src/GL/qbz_mesh.cpp \
    src/GL/qbz_fbo.cpp \
    src/GL/qbz_depthfbo.cpp \
    src/GL/qbz_deferredrenderer.cpp \
    src/Network/qbz_network.cpp \
    src/System/registry.cpp \
    src/System/qbz_tgatexture.cpp \
    src/System/qbz_ofwidget.cpp \
    src/System/qbz_midithread.cpp \
    src/System/qbz_library.cpp \
    src/System/qbz_glwidget.cpp \
    src/System/qbz_glthread.cpp \
    src/System/qbz_clam.cpp \
    src/System/qbz_clam_pitchprofile.cpp \
    src/System/mainwindow.cpp \
    src/System/main.cpp \
    src/World/qbz_world.cpp \
    src/World/qbz_projectionmapper.cpp \
    src/World/qbz_projectionarea.cpp \
    src/World/qbz_projection_simple.cpp \
    src/World/qbz_plane.cpp \
    src/World/qbz_path.cpp \
    src/World/qbz_particlebase.cpp \
    src/World/qbz_model.cpp \
    src/World/qbz_lightdot.cpp \
    src/World/qbz_light.cpp \
    src/World/qbz_harmonics.cpp \
    src/World/qbz_camera.cpp \
    src/World/qbz_animator.cpp \
    src/qbz_composer.cpp

INCLUDEPATH +=  frameworks \
        frameworks/cpptweener/src \
        frameworks/assimp/include \
        frameworks/CLAM/include \
	
macx {
	LIBS += \
        -framework CoreMidi \
	-framework CoreAudio \
	-framework CoreFoundation \
	-framework CoreServices \
	-framework Appkit \
	-framework Cocoa \
	-framework ApplicationServices \
	-framework AudioToolbox \
	-Lframeworks/assimp/lib -lassimp \
        #-Lframeworks/CLAM/lib -lclam_core -lclam_audioio -lclam_processing \

	LIBS += /Users/krs/QtSDK/Desktop/Qt/474/gcc/lib/libQtUiTools.a
}

OTHER_FILES += \
    foo.qml \
    qmlsrc/Dial.qml \
    qmlsrc/Renderer.qml \
    qmlsrc/OutPort.qml \
    qmlsrc/InPort.qml \
    qmlsrc/DeferredRenderer.qml \
    qmlsrc/PostProcessor.qml \
    qmlsrc/LFO.qml \
    qmlsrc/Animator.qml \
    qmlsrc/GridMenu.qml \
    qmlsrc/BackgroundCanvas.qml \
    qmlsrc/Cable.qml \
    data/blur_horizontal.vert \
    data/color_separate_cmyk.vert \
    data/projection.vert \
    data/simplemodel.vert \
    data/smart_aa_bloom.vert \
    data/blur_vertical.vert \
    data/simplemodel.frag \
    data/model.frag \
    data/smart_aa_bloom.frag \
    data/basic.frag \
    data/basic.vert \
    data/model.vert \
    data/model_green.vert \
    data/model_green.frag \
    data/color_separate_rgb.vert \
    data/color_separate_rgb.frag \
    data/final.frag \
    data/final.vert \
    data/deferred0_normalmap.vert \
    data/deferred0_normalmap.frag \
    data/deferred0_normalmap_specmap.frag \
    data/glow.vert \
    data/blur_horizontal.frag \
    data/blur_vertical.frag \
    data/glow.frag \
    data/depthoffield_V.vert \
    data/depthoffield_U.vert \
    data/SSAO.vert \
    data/blurSSAO.vert \
    data/deferred1.vert \
    data/deferred0_billboard.vert \
    data/deferred1.frag \
    data/directional_light.vert \
    data/wireframe.frag \
    data/wireframe.vert \
    data/point_light.vert \
    data/depthoffield_V.frag \
    data/depthoffield_U.frag \
    data/deferred0_billboard.frag \
    data/deferred0.frag \
    data/color_separate_cmyk.frag \
    data/blurSSAO.frag \
    data/SSAO.frag \
    data/projection.frag \
    data/deferred0.vert \
    data/directional_light.frag \
    data/point_light.frag \
    data/shadowmap0.frag \
    data/shadowmap0.vert \
    data/shadowmap1.vert \
    data/shadowmap1.frag \
    qmlsrc/ConfigWindow.qml \
    qmlsrc/MainMenu.qml \
    qmlsrc/Button.qml \
    qmlsrc/Cables.js \
    qmlsrc/Model.qml

















