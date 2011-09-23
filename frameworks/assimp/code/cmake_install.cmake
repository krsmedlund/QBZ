# Install script for directory: /Users/krs/Code/qbz2/frameworks/assimp/code

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/libassimp.1.0.0.dylib;/usr/local/lib/libassimp.1.dylib;/usr/local/lib/libassimp.dylib")
FILE(INSTALL DESTINATION "/usr/local/lib" TYPE SHARED_LIBRARY FILES
    "/Users/krs/Code/qbz2/frameworks/assimp/lib/libassimp.1.0.0.dylib"
    "/Users/krs/Code/qbz2/frameworks/assimp/lib/libassimp.1.dylib"
    "/Users/krs/Code/qbz2/frameworks/assimp/lib/libassimp.dylib"
    )
  FOREACH(file
      "$ENV{DESTDIR}/usr/local/lib/libassimp.1.0.0.dylib"
      "$ENV{DESTDIR}/usr/local/lib/libassimp.1.dylib"
      "$ENV{DESTDIR}/usr/local/lib/libassimp.dylib"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      EXECUTE_PROCESS(COMMAND "/usr/bin/install_name_tool"
        -id "libassimp.1.dylib"
        "${file}")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "${file}")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDFOREACH()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/assimp/aiAnim.h;/usr/local/include/assimp/aiAssert.h;/usr/local/include/assimp/aiCamera.h;/usr/local/include/assimp/aiColor4D.h;/usr/local/include/assimp/aiColor4D.inl;/usr/local/include/assimp/aiConfig.h;/usr/local/include/assimp/aiDefines.h;/usr/local/include/assimp/aiFileIO.h;/usr/local/include/assimp/aiLight.h;/usr/local/include/assimp/aiMaterial.h;/usr/local/include/assimp/aiMaterial.inl;/usr/local/include/assimp/aiMatrix3x3.h;/usr/local/include/assimp/aiMatrix3x3.inl;/usr/local/include/assimp/aiMatrix4x4.h;/usr/local/include/assimp/aiMatrix4x4.inl;/usr/local/include/assimp/aiMesh.h;/usr/local/include/assimp/aiPostProcess.h;/usr/local/include/assimp/aiQuaternion.h;/usr/local/include/assimp/aiScene.h;/usr/local/include/assimp/aiTexture.h;/usr/local/include/assimp/aiTypes.h;/usr/local/include/assimp/aiVector2D.h;/usr/local/include/assimp/aiVector3D.h;/usr/local/include/assimp/aiVector3D.inl;/usr/local/include/assimp/aiVersion.h;/usr/local/include/assimp/assimp.h;/usr/local/include/assimp/assimp.hpp;/usr/local/include/assimp/DefaultLogger.h;/usr/local/include/assimp/IOStream.h;/usr/local/include/assimp/IOSystem.h;/usr/local/include/assimp/Logger.h;/usr/local/include/assimp/LogStream.h;/usr/local/include/assimp/NullLogger.h")
FILE(INSTALL DESTINATION "/usr/local/include/assimp" TYPE FILE FILES
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiAnim.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiAssert.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiCamera.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiColor4D.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiColor4D.inl"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiConfig.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiDefines.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiFileIO.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiLight.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiMaterial.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiMaterial.inl"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiMatrix3x3.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiMatrix3x3.inl"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiMatrix4x4.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiMatrix4x4.inl"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiMesh.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiPostProcess.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiQuaternion.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiScene.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiTexture.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiTypes.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiVector2D.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiVector3D.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiVector3D.inl"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/aiVersion.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/assimp.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/assimp.hpp"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/DefaultLogger.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/IOStream.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/IOSystem.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/Logger.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/LogStream.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/NullLogger.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/assimp/Compiler/pushpack1.h;/usr/local/include/assimp/Compiler/poppack1.h;/usr/local/include/assimp/Compiler/pstdint.h")
FILE(INSTALL DESTINATION "/usr/local/include/assimp/Compiler" TYPE FILE FILES
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/Compiler/pushpack1.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/../include/Compiler/poppack1.h"
    "/Users/krs/Code/qbz2/frameworks/assimp/code/pstdint.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

