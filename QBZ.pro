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
    src/Network/registry.h \
    src/System/mainwindow.h \
    src/Network/network.h \
    src/GL/deferredrenderer.h \
    src/GL/depthfbo.h \
    src/GL/fbo.h \
    src/GL/mesh.h \
    src/GL/renderprogram.h \
    src/GL/skybox.h \
    src/GL/terrain.h \
    src/GL/vbo.h \
    src/System/library.h \
    src/System/midithread.h \
    src/System/ofwidget.h \
    src/System/tgatexture.h \
    src/World/animator.h \
    src/World/camera.h \
    src/World/harmonics.h \
    src/World/lightdot.h \
    src/World/model.h \
    src/World/plane.h \
    src/World/projection_simple.h \
    src/World/projectionarea.h \
    src/World/world.h \
    src/baseapp.h \
    src/composer.h \
    src/World/modelfile.h \
    src/GL/finalout.h
		   
SOURCES += src/System/main.cpp \
    src/Ext/RtMidi.cpp \
    src/Ext/CppTweener.cpp \
    src/GL/rendertarget.cpp \
    src/Network/registry.cpp \
    src/System/mainwindow.cpp \
    src/Network/network.cpp \
    src/GL/deferredrenderer.cpp \
    src/GL/depthfbo.cpp \
    src/GL/fbo.cpp \
    src/GL/mesh.cpp \
    src/GL/renderprogram.cpp \
    src/GL/skybox.cpp \
    src/GL/vbo.cpp \
    src/GL/terrain.cpp \
    src/System/library.cpp \
    src/System/midithread.cpp \
    src/System/tgatexture.cpp \
    src/System/ofwidget.cpp \
    src/World/animator.cpp \
    src/World/camera.cpp \
    src/World/harmonics.cpp \
    src/World/lightdot.cpp \
    src/World/model.cpp \
    src/World/plane.cpp \
    src/World/projection_simple.cpp \
    src/World/projectionarea.cpp \
    src/World/world.cpp \
    src/composer.cpp \
    src/World/modelfile.cpp \
    src/GL/finalout.cpp

INCLUDEPATH +=  frameworks \
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
    qmlsrc/Model.qml \
    qmlsrc/Main.qml \
    qmlsrc/Components.js \
    qmlsrc/NodeList.qml \
    qmlsrc/RenderTarget.qml \
    qmlsrc/ConfigWindow.js \
    qmlsrc/RenderProgram.qml \
    qmlsrc/NodeListWindow.qml \
    qmlsrc/InputListWindow.qml \
    qmlsrc/ResourceWindow.qml \
    qmlsrc/ModelFile.qml \
    qmlsrc/FinalOut.qml \
    qmlsrc/MusicChannel.qml \
    qmlsrc/TimeChannel.qml



























































































































































