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
        src/qbz_midithread.h \
        src/qbz_baseapp.h \
        src/qbz_skybox.h \
        src/qbz_deferredrenderer.h \
        src/qbz_ofwidget.h \
        src/qbz_composer.h \
        src/qbz_world.h \
        src/qbz_renderprogram.h \
        src/qbz_animator.h \
        src/qbz_fbo.h \
        src/qbz_shader.h \
        src/qbz_lightdot.h \
        src/qbz_model.h \
        src/qbz_mesh.h \	
        src/qbz_camera.h \
        src/qbz_projection_simple.h \
        src/qbz_projectionarea.h \
        src/mainwindow.h \
        src/qbz_glthread.h \
        src/qbz_particlebase.h \
        src/qbz_terrain.h \
        src/qbz_vbo.h \
        src/qbz_library.h \
        src/qbz_depthfbo.h \
        src/qbz_harmonics.h \
        src/qbz_network.h \
        src/rendertarget.h \
        src/registry.h \ 
        src/RtMidi.h \
        src/RtError.h \
        src/CppTweener.h \
        qbz_renderwidget.h \
		   
SOURCES += src/main.cpp \
        src/qbz_midithread.cpp \
        src/qbz_deferredrenderer.cpp \
        src/qbz_skybox.cpp \
        src/qbz_ofwidget.cpp \
        src/qbz_composer.cpp \
        src/qbz_world.cpp \
        src/qbz_renderprogram.cpp \
        src/qbz_animator.cpp \
        src/qbz_fbo.cpp \
        src/qbz_shader.cpp \
        src/qbz_lightdot.cpp \
        src/qbz_model.cpp \
        src/qbz_mesh.cpp \
        src/qbz_camera.cpp \
        src/qbz_projection_simple.cpp \
        src/qbz_projectionarea.cpp \
        src/mainwindow.cpp \
        src/qbz_glthread.cpp \
        qbz_renderwidget.cpp \
        src/qbz_particlebase.cpp \
        src/qbz_terrain.cpp \
        src/qbz_vbo.cpp \
        src/qbz_library.cpp \
        src/qbz_depthfbo.cpp \
        src/qbz_harmonics.cpp \
        src/qbz_network.cpp \
        src/rendertarget.cpp \
        src/registry.cpp \
        src/RtMidi.cpp \
        src/CppTweener.cpp \

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





