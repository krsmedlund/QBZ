#############################################################################
# Makefile for building: QBZ.app/Contents/MacOS/QBZ
# Generated by qmake (2.01a) (Qt 4.7.4) on: Sun Sep 25 04:18:13 2011
# Project:  QBZ.pro
# Template: app
# Command: /Users/krs/QtSDK/Desktop/Qt/474/gcc/bin/qmake -spec ../../QtSDK/Desktop/Qt/474/gcc/mkspecs/macx-g++ -o Makefile QBZ.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_DECLARATIVE_LIB -DQT_SCRIPT_LIB -DQT_XML_LIB -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB
CFLAGS        = -pipe -g -gdwarf-2 -arch x86_64 -Xarch_x86_64 -mmacosx-version-min=10.5 -Wall -W $(DEFINES)
CXXFLAGS      = -pipe -g -gdwarf-2 -arch x86_64 -Xarch_x86_64 -mmacosx-version-min=10.5 -Wall -W $(DEFINES)
INCPATH       = -I../../QtSDK/Desktop/Qt/474/gcc/mkspecs/macx-g++ -I. -I../../QtSDK/Desktop/Qt/474/gcc/lib/QtDesigner.framework/Versions/4/Headers -I../../QtSDK/Desktop/Qt/474/gcc/include/QtDesigner -I../../QtSDK/Desktop/Qt/474/gcc/lib/QtCore.framework/Versions/4/Headers -I../../QtSDK/Desktop/Qt/474/gcc/include/QtCore -I../../QtSDK/Desktop/Qt/474/gcc/lib/QtGui.framework/Versions/4/Headers -I../../QtSDK/Desktop/Qt/474/gcc/include/QtGui -I../../QtSDK/Desktop/Qt/474/gcc/lib/QtOpenGL.framework/Versions/4/Headers -I../../QtSDK/Desktop/Qt/474/gcc/include/QtOpenGL -I../../QtSDK/Desktop/Qt/474/gcc/lib/QtXml.framework/Versions/4/Headers -I../../QtSDK/Desktop/Qt/474/gcc/include/QtXml -I../../QtSDK/Desktop/Qt/474/gcc/lib/QtScript.framework/Versions/4/Headers -I../../QtSDK/Desktop/Qt/474/gcc/include/QtScript -I../../QtSDK/Desktop/Qt/474/gcc/lib/QtDeclarative.framework/Versions/4/Headers -I../../QtSDK/Desktop/Qt/474/gcc/include/QtDeclarative -I../../QtSDK/Desktop/Qt/474/gcc/include -I. -Isrc -I/usr/include -I/usr/local/include -I/usr/include -I/usr/local/include -I/opt/local/include -Iframeworks -Iframeworks/assimp/include -Iframeworks/CLAM/include -I/System/Library/Frameworks/OpenGL.framework/Versions/A/Headers -I/System/Library/Frameworks/AGL.framework/Headers -I. -I. -F/Users/krs/QtSDK/Desktop/Qt/474/gcc/lib
LINK          = g++
LFLAGS        = -headerpad_max_install_names -arch x86_64 -Xarch_x86_64 -mmacosx-version-min=10.5
LIBS          = $(SUBLIBS) -F/Users/krs/QtSDK/Desktop/Qt/474/gcc/lib -L/Users/krs/QtSDK/Desktop/Qt/474/gcc/lib -framework CoreMidi -framework CoreAudio -framework CoreFoundation -framework CoreServices -framework Appkit -framework Cocoa -framework ApplicationServices -framework AudioToolbox -Lframeworks/assimp/lib -lassimp /Users/krs/QtSDK/Desktop/Qt/474/gcc/lib/libQtUiTools.a -framework QtDeclarative -framework QtScript -framework QtXml -framework QtOpenGL -framework QtGui -framework QtCore -framework QtDesigner -framework OpenGL -framework AGL 
AR            = ar cq
RANLIB        = ranlib -s
QMAKE         = /Users/krs/QtSDK/Desktop/Qt/474/gcc/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
STRIP         = 
INSTALL_FILE  = $(COPY_FILE)
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = $(COPY_FILE)
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
export MACOSX_DEPLOYMENT_TARGET = 10.4

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = src/System/main.cpp \
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
		src/composer.cpp moc_mainwindow.cpp \
		moc_midithread.cpp \
		moc_ofwidget.cpp \
		qrc_QBZ.cpp
OBJECTS       = main.o \
		RtMidi.o \
		CppTweener.o \
		rendertarget.o \
		registry.o \
		mainwindow.o \
		network.o \
		deferredrenderer.o \
		depthfbo.o \
		fbo.o \
		mesh.o \
		renderprogram.o \
		skybox.o \
		vbo.o \
		terrain.o \
		library.o \
		midithread.o \
		tgatexture.o \
		ofwidget.o \
		animator.o \
		camera.o \
		harmonics.o \
		lightdot.o \
		model.o \
		plane.o \
		projection_simple.o \
		projectionarea.o \
		world.o \
		composer.o \
		moc_mainwindow.o \
		moc_midithread.o \
		moc_ofwidget.o \
		qrc_QBZ.o
DIST          = ../../QtSDK/Desktop/Qt/474/gcc/mkspecs/common/unix.conf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/common/mac.conf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/common/mac-g++.conf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/qconfig.pri \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/modules/qt_webkit_version.pri \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/qt_functions.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/qt_config.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/exclusive_builds.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/default_pre.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/mac/default_pre.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/mac/dwarf2.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/debug.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/default_post.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/mac/default_post.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/mac/x86_64.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/mac/objective_c.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/qt.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/designer.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/unix/opengl.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/unix/thread.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/moc.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/warn_on.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/mac/rez.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/mac/sdk.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/resources.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/uic.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/yacc.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/lex.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/include_source_dir.prf \
		QBZ.pro
QMAKE_TARGET  = QBZ
DESTDIR       = 
TARGET        = QBZ.app/Contents/MacOS/QBZ

####### Custom Compiler Variables
QMAKE_COMP_QMAKE_OBJECTIVE_CFLAGS = -pipe \
		-g \
		-gdwarf-2 \
		-arch \
		x86_64 \
		-Xarch_x86_64 \
		-mmacosx-version-min=10.5 \
		-Wall \
		-W


first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile QBZ.app/Contents/PkgInfo QBZ.app/Contents/Resources/empty.lproj QBZ.app/Contents/Info.plist $(TARGET)

$(TARGET): ui_mainwindow.h $(OBJECTS)  
	@$(CHK_DIR_EXISTS) QBZ.app/Contents/MacOS/ || $(MKDIR) QBZ.app/Contents/MacOS/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: QBZ.pro  ../../QtSDK/Desktop/Qt/474/gcc/mkspecs/macx-g++/qmake.conf ../../QtSDK/Desktop/Qt/474/gcc/mkspecs/common/unix.conf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/common/mac.conf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/common/mac-g++.conf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/qconfig.pri \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/modules/qt_webkit_version.pri \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/qt_functions.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/qt_config.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/exclusive_builds.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/default_pre.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/mac/default_pre.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/mac/dwarf2.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/debug.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/default_post.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/mac/default_post.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/mac/x86_64.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/mac/objective_c.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/qt.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/designer.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/unix/opengl.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/unix/thread.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/moc.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/warn_on.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/mac/rez.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/mac/sdk.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/resources.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/uic.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/yacc.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/lex.prf \
		../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/include_source_dir.prf
	$(QMAKE) -spec ../../QtSDK/Desktop/Qt/474/gcc/mkspecs/macx-g++ -o Makefile QBZ.pro
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/common/unix.conf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/common/mac.conf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/common/mac-g++.conf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/qconfig.pri:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/modules/qt_webkit_version.pri:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/qt_functions.prf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/qt_config.prf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/exclusive_builds.prf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/default_pre.prf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/mac/default_pre.prf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/mac/dwarf2.prf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/debug.prf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/default_post.prf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/mac/default_post.prf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/mac/x86_64.prf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/mac/objective_c.prf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/qt.prf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/designer.prf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/unix/opengl.prf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/unix/thread.prf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/moc.prf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/warn_on.prf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/mac/rez.prf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/mac/sdk.prf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/resources.prf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/uic.prf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/yacc.prf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/lex.prf:
../../QtSDK/Desktop/Qt/474/gcc/mkspecs/features/include_source_dir.prf:
qmake:  FORCE
	@$(QMAKE) -spec ../../QtSDK/Desktop/Qt/474/gcc/mkspecs/macx-g++ -o Makefile QBZ.pro

QBZ.app/Contents/PkgInfo: 
	@$(CHK_DIR_EXISTS) QBZ.app/Contents || $(MKDIR) QBZ.app/Contents 
	@$(DEL_FILE) QBZ.app/Contents/PkgInfo
	@echo "APPL????" >QBZ.app/Contents/PkgInfo
QBZ.app/Contents/Resources/empty.lproj: 
	@$(CHK_DIR_EXISTS) QBZ.app/Contents/Resources || $(MKDIR) QBZ.app/Contents/Resources 
	@touch QBZ.app/Contents/Resources/empty.lproj
	
QBZ.app/Contents/Info.plist: 
	@$(CHK_DIR_EXISTS) QBZ.app/Contents || $(MKDIR) QBZ.app/Contents 
	@$(DEL_FILE) QBZ.app/Contents/Info.plist
	@sed -e "s,@ICON@,,g" -e "s,@EXECUTABLE@,QBZ,g" -e "s,@TYPEINFO@,????,g" ../../QtSDK/Desktop/Qt/474/gcc/mkspecs/macx-g++/Info.plist.app >QBZ.app/Contents/Info.plist
dist: 
	@$(CHK_DIR_EXISTS) .tmp/QBZ1.0.0 || $(MKDIR) .tmp/QBZ1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/QBZ1.0.0/ && $(COPY_FILE) --parents src/qbz.h src/Ext/RtMidi.h src/Ext/RtError.h src/Ext/CppTweener.h src/GL/rendertarget.h src/Network/registry.h src/System/mainwindow.h src/Network/network.h src/GL/deferredrenderer.h src/GL/depthfbo.h src/GL/fbo.h src/GL/mesh.h src/GL/renderprogram.h src/GL/skybox.h src/GL/terrain.h src/GL/vbo.h src/System/library.h src/System/midithread.h src/System/ofwidget.h src/System/tgatexture.h src/World/animator.h src/World/camera.h src/World/harmonics.h src/World/lightdot.h src/World/model.h src/World/plane.h src/World/projection_simple.h src/World/projectionarea.h src/World/world.h src/baseapp.h src/composer.h .tmp/QBZ1.0.0/ && $(COPY_FILE) --parents QBZ.qrc .tmp/QBZ1.0.0/ && $(COPY_FILE) --parents src/System/main.cpp src/Ext/RtMidi.cpp src/Ext/CppTweener.cpp src/GL/rendertarget.cpp src/Network/registry.cpp src/System/mainwindow.cpp src/Network/network.cpp src/GL/deferredrenderer.cpp src/GL/depthfbo.cpp src/GL/fbo.cpp src/GL/mesh.cpp src/GL/renderprogram.cpp src/GL/skybox.cpp src/GL/vbo.cpp src/GL/terrain.cpp src/System/library.cpp src/System/midithread.cpp src/System/tgatexture.cpp src/System/ofwidget.cpp src/World/animator.cpp src/World/camera.cpp src/World/harmonics.cpp src/World/lightdot.cpp src/World/model.cpp src/World/plane.cpp src/World/projection_simple.cpp src/World/projectionarea.cpp src/World/world.cpp src/composer.cpp .tmp/QBZ1.0.0/ && $(COPY_FILE) --parents ui/mainwindow.ui .tmp/QBZ1.0.0/ && (cd `dirname .tmp/QBZ1.0.0` && $(TAR) QBZ1.0.0.tar QBZ1.0.0 && $(COMPRESS) QBZ1.0.0.tar) && $(MOVE) `dirname .tmp/QBZ1.0.0`/QBZ1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/QBZ1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) -r QBZ.app
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_objective_c_make_all:
compiler_objective_c_clean:
compiler_moc_header_make_all: moc_mainwindow.cpp moc_midithread.cpp moc_ofwidget.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_midithread.cpp moc_ofwidget.cpp
moc_mainwindow.cpp: src/System/mainwindow.h
	/Users/krs/QtSDK/Desktop/Qt/474/gcc/bin/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ src/System/mainwindow.h -o moc_mainwindow.cpp

moc_midithread.cpp: src/System/midithread.h
	/Users/krs/QtSDK/Desktop/Qt/474/gcc/bin/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ src/System/midithread.h -o moc_midithread.cpp

moc_ofwidget.cpp: src/System/ofwidget.h
	/Users/krs/QtSDK/Desktop/Qt/474/gcc/bin/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ src/System/ofwidget.h -o moc_ofwidget.cpp

compiler_rcc_make_all: qrc_QBZ.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_QBZ.cpp
qrc_QBZ.cpp: QBZ.qrc \
		ui/mainwindow.ui \
		qmlsrc/Main.qml
	/Users/krs/QtSDK/Desktop/Qt/474/gcc/bin/rcc -name QBZ QBZ.qrc -o qrc_QBZ.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_rez_source_make_all:
compiler_rez_source_clean:
compiler_uic_make_all: ui_mainwindow.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h
ui_mainwindow.h: ui/mainwindow.ui
	/Users/krs/QtSDK/Desktop/Qt/474/gcc/bin/uic ui/mainwindow.ui -o ui_mainwindow.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

main.o: src/System/main.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o src/System/main.cpp

RtMidi.o: src/Ext/RtMidi.cpp src/Ext/RtMidi.h \
		src/Ext/RtError.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o RtMidi.o src/Ext/RtMidi.cpp

CppTweener.o: src/Ext/CppTweener.cpp src/Ext/CppTweener.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o CppTweener.o src/Ext/CppTweener.cpp

rendertarget.o: src/GL/rendertarget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o rendertarget.o src/GL/rendertarget.cpp

registry.o: src/Network/registry.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o registry.o src/Network/registry.cpp

mainwindow.o: src/System/mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o src/System/mainwindow.cpp

network.o: src/Network/network.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o network.o src/Network/network.cpp

deferredrenderer.o: src/GL/deferredrenderer.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o deferredrenderer.o src/GL/deferredrenderer.cpp

depthfbo.o: src/GL/depthfbo.cpp src/GL/depthfbo.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o depthfbo.o src/GL/depthfbo.cpp

fbo.o: src/GL/fbo.cpp src/GL/fbo.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o fbo.o src/GL/fbo.cpp

mesh.o: src/GL/mesh.cpp src/GL/mesh.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mesh.o src/GL/mesh.cpp

renderprogram.o: src/GL/renderprogram.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o renderprogram.o src/GL/renderprogram.cpp

skybox.o: src/GL/skybox.cpp src/GL/skybox.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o skybox.o src/GL/skybox.cpp

vbo.o: src/GL/vbo.cpp src/GL/vbo.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o vbo.o src/GL/vbo.cpp

terrain.o: src/GL/terrain.cpp src/GL/terrain.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o terrain.o src/GL/terrain.cpp

library.o: src/System/library.cpp src/System/library.h \
		src/System/tgatexture.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o library.o src/System/library.cpp

midithread.o: src/System/midithread.cpp src/System/midithread.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o midithread.o src/System/midithread.cpp

tgatexture.o: src/System/tgatexture.cpp src/System/tgatexture.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tgatexture.o src/System/tgatexture.cpp

ofwidget.o: src/System/ofwidget.cpp src/System/ofwidget.h \
		src/System/midithread.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ofwidget.o src/System/ofwidget.cpp

animator.o: src/World/animator.cpp src/World/animator.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o animator.o src/World/animator.cpp

camera.o: src/World/camera.cpp src/World/camera.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o camera.o src/World/camera.cpp

harmonics.o: src/World/harmonics.cpp src/World/harmonics.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o harmonics.o src/World/harmonics.cpp

lightdot.o: src/World/lightdot.cpp src/World/lightdot.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o lightdot.o src/World/lightdot.cpp

model.o: src/World/model.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o model.o src/World/model.cpp

plane.o: src/World/plane.cpp src/World/plane.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o plane.o src/World/plane.cpp

projection_simple.o: src/World/projection_simple.cpp src/World/projection_simple.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o projection_simple.o src/World/projection_simple.cpp

projectionarea.o: src/World/projectionarea.cpp src/World/projectionarea.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o projectionarea.o src/World/projectionarea.cpp

world.o: src/World/world.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o world.o src/World/world.cpp

composer.o: src/composer.cpp src/composer.h \
		src/qbz.h \
		src/Network/network.h \
		src/Network/registry.h \
		src/System/mainwindow.h \
		src/System/library.h \
		src/GL/renderprogram.h \
		src/GL/deferredrenderer.h \
		src/GL/fbo.h \
		src/GL/rendertarget.h \
		src/World/camera.h \
		src/World/animator.h \
		src/World/world.h \
		src/World/projection_simple.h \
		src/World/projectionarea.h \
		src/World/harmonics.h \
		src/GL/skybox.h \
		src/GL/terrain.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o composer.o src/composer.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_midithread.o: moc_midithread.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_midithread.o moc_midithread.cpp

moc_ofwidget.o: moc_ofwidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ofwidget.o moc_ofwidget.cpp

qrc_QBZ.o: qrc_QBZ.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_QBZ.o qrc_QBZ.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

