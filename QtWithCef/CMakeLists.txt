
set(CEF_TARGET "QtWithCef")
project(${CEF_TARGET})   
SET(CMAKE_PREFIX_PATH D:\\Qt5.15\\5.15.2\\msvc2019_64)
message(STATUS "CMAKE_PREFIX_PATH:                    ${CMAKE_PREFIX_PATH}")
message(STATUS "CMAKE_EXE_LINKER_FLAGS_DEBUG:                    ${CMAKE_EXE_LINKER_FLAGS_DEBUG}")
message(STATUS "CMAKE_EXE_LINKER_FLAGS_DEBUG:                    ${CEF_INCLUDE_PATH}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_definitions(-DQT_PROJECT)
FIND_PACKAGE(Qt5Widgets REQUIRED)
FIND_PACKAGE(Qt5Gui REQUIRED)
FIND_PACKAGE(Qt5Core REQUIRED)

set(QtWithCef_SRCS
  ../tests/cefsimple/simple_app.cc
  ../tests/cefsimple/simple_app.h
  ../tests/cefsimple/simple_handler.cc
  ../tests/cefsimple/simple_handler.h
  ./CCefEngine.h
  ./CCefEngine.cpp
  ./main.cpp
  ./QtWithCef.cpp
  ./QtWithCef.h
  ./QtWithCef.ui
  )
  
#FILE(GLOB_RECURSE HEADER_FILES "*.h")
#FILE(GLOB_RECURSE SRC_FILES "*.cpp")
#FILE(GLOB_RECURSE FORMS "*.ui")
#FILE(GLOB_RECURSE RESOURCE_FILES "*.qrc")
#FILE(GLOB TS_FILES "*.ts")
#FILE(GLOB MOC_FILES "moc_*.cpp")
IF(FORMS)
	#QT5_WRAP_UI(FORMS_UIC ${FORMS})
ENDIF()

#QT5_WRAP_CPP(MOC_FILES ${HEADER_FILES})

#启用qrc资源文件
#QT5_ADD_RESOURCES(RES_FILES ${CEF_TARGET}.qrc)

# Target executable names.

# Determine the target output directory.
#SOURCE_GROUP("Form Files" FILES ${FORMS})
#将qrc资源文件整理在一个文件夹中
#SOURCE_GROUP("Resource Files" FILES ${RESOURCE_FILES})
#查找当前目录下所有的.h和.cpp文件
#SOURCE_GROUP("Header Files" FILES ${HEADER_FILES})
#SOURCE_GROUP("Source Files" FILES ${SRC_FILES})
#翻译文件
#SOURCE_GROUP("Translation Files" FILES ${TS_FILES})

#将MOC,UI,QRC的中间生成文件编译进EXE中
#SOURCE_GROUP("Generated Files" FILES ${MOC_FILES} ${FORMS_UIC} ${RES_FILES} ${TS_FILES})

# Executable target.
add_executable(${CEF_TARGET} ${QtWithCef_SRCS})
#add_dependencies(${CEF_TARGET} libcef_dll_wrapper)


set_target_properties( ${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
)


target_include_directories(${CEF_TARGET} PRIVATE ${CEF_INCLUDE_PATH})
target_link_libraries(${CEF_TARGET} libcef_dll_wrapper ${CEF_STANDARD_LIBS})
TARGET_LINK_LIBRARIES( ${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Gui)
target_link_libraries(${PROJECT_NAME} 
    $<$<CONFIG:Debug>:${CMAKE_CURRENT_SOURCE_DIR}/../Debug/libcef.lib>
    $<$<NOT:$<CONFIG:Debug>>:${CMAKE_CURRENT_SOURCE_DIR}/../Release/libcef.lib>
)

# Add the custom manifest files to the executable.
ADD_WINDOWS_MANIFEST("${CMAKE_CURRENT_SOURCE_DIR}" "${CEF_TARGET}" "exe")

