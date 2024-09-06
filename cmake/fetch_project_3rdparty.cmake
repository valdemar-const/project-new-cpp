# -- Add static 3rdparty dependencies
add_subdirectory(${CMAKE_SOURCE_DIR}/3rdparty)

# -- Support installable packages
CPMAddPackage(NAME PackageProject.cmake
  VERSION        1.11.2
  GIT_REPOSITORY "https://github.com/TheLartians/PackageProject.cmake"
  GIT_TAG        v1.11.2
  GIT_SHALLOW
  EXCLUDE_FROM_ALL)

# -- Configure glad

CPMAddPackage(NAME Glad
  VERSION        2.0.7
  URL            "https://github.com/Dav1dde/glad/archive/refs/tags/v2.0.7.zip"
  URL_HASH       "SHA256=6645cc2ebeeff637ef59e0736c2c14eb83b607f65221429c5ddc5202101eab1e"
  # GIT_REPOSITORY "https://github.com/Dav1dde/glad"
  # GIT_TAG        v2.0.7
  # GIT_SHALLOW
  SOURCE_SUBDIR  cmake
  EXCLUDE_FROM_ALL)

glad_add_library(glad_gl_core46_noext_gles_core30_noext_mx STATIC EXCLUDE_FROM_ALL REPRODUCIBLE QUIET MX LANGUAGE cpp API gl:core=4.6 API gles2:core=3.0 EXTENSIONS NONE)
add_library(glad::gl_core46_noext_gles_core30_noext_mx ALIAS glad_gl_core46_noext_gles_core30_noext_mx)

# -- Configure glbinding

CPMAddPackage(NAME glbinding
  VERSION        3.3.0
  URL            "https://github.com/cginternals/glbinding/archive/refs/tags/v3.3.0.zip"
  URL_HASH       "SHA256=e035385dab8e9e687229e6b95b36c00bc0407669691913de5b63ca734e82b617"
  # GIT_REPOSITORY "https://github.com/cginternals/glbinding"
  # GIT_TAG        v3.3.0
  # GIT_SHALLOW
  EXCLUDE_FROM_ALL)

# -- Configure C++ Core Guidelines Support Library (GSL)

CPMAddPackage(NAME GSL
  VERSION  4.0.0
  URL      https://github.com/microsoft/GSL/archive/refs/tags/v4.0.0.zip
  URL_HASH "SHA256=eb91fcb10a6aa5ccb1d224e07a56c8ecffe9a1bb601fa1848276ec46a2200bfb"
  # GIT_REPOSITORY https://github.com/microsoft/GSL
  # GIT_TAG        v4.0.0
  # GIT_SHALLOW    ON
  OVERRIDE_FIND_PACKAGE
  EXCLUDE_FROM_ALL
  )

# -- Configure Boost

if (UNIX) # Setup ICU for Boost::locale
  set(MY_ICU_CFG "--disable-dyload")

  set(BUILD_ICU         YES           CACHE BOOL   "Enable compilation of ICU")
  set(ICU_BUILD_VERSION 75.1          CACHE STRING "ICU version to build")
  set(ICU_CFG_OPTIONS   ${MY_ICU_CFG} CACHE STRING "Additional ICU configuration options")
  set(ICU_STATIC        YES           CACHE BOOL   "Use static instead of shared ICU (does not work for system)")
  set(SYSTEM_ICU        OFF           CACHE BOOL   "Use system-provided icu libraries (instead of prebuilts or building")

  CPMAddPackage(NAME ICU
    VERSION           75.1
    GITHUB_REPOSITORY valdemar-const/icu-cmake
    GIT_TAG           master
    GIT_SHALLOW
    OVERRIDE_FIND_PACKAGE
    EXCLUDE_FROM_ALL
    )


  set(BOOST_LOCALE_ENABLE_ICONV OFF)
  set(BOOST_LOCALE_ENABLE_POSIX OFF)
  set(BOOST_LOCALE_ENABLE_STD   OFF)
  set(BOOST_LOCALE_ENABLE_ICU   ON)
endif ()

list(APPEND BOOST_INCLUDE_LIBRARIES json spirit fusion geometry thread locale signals2)

if (NOT EMSCRIPTEN)
  list(APPEND BOOST_INCLUDE_LIBRARIES test)
endif()

CPMAddPackage(NAME Boost
  VERSION  1.85.0
  URL      https://github.com/boostorg/boost/releases/download/boost-1.85.0/boost-1.85.0-cmake.7z
  URL_HASH "SHA256=2399fb7b15c84c9dafc4ffb1be69c076da36e541fb960fd971b960c180023f2b"
  OVERRIDE_FIND_PACKAGE
  EXCLUDE_FROM_ALL
  )

# -- Configure wxWidgets

set(wxBUILD_SHARED OFF)
set(wxBUILD_VENDOR skif)
set(wxUSE_STL      ON)

CPMAddPackage(NAME wxWidgets
  VERSION          3.2.5
  URL              "https://github.com/wxWidgets/wxWidgets/releases/download/v3.2.5/wxWidgets-3.2.5.7z"
  URL_HASH         "SHA256=9efad97c9eac8be6ce2b71723027070987fd519860bdefde2cf6c438b3383f6d"
  # GIT_REPOSITORY   "https://github.com/wxWidgets/wxWidgets"
  # GIT_TAG          v3.2.5
  # GIT_SHALLOW
  EXCLUDE_FROM_ALL)

# -- Configure GLFW

CPMAddPackage(NAME GLFW
  VERSION          3.4
  URL              "https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip"
  URL_HASH         "SHA256=b5ec004b2712fd08e8861dc271428f048775200a2df719ccf575143ba749a3e9"
  # GIT_REPOSITORY   "https://github.com/glfw/glfw"
  # GIT_TAG          3.4
  # GIT_SHALLOW
  EXCLUDE_FROM_ALL)

# -- Configure glm

CPMAddPackage(NAME glm
  URL      https://github.com/g-truc/glm/releases/download/1.0.1/glm-1.0.1-light.7z
  VERSION  1.0.1
  URL_HASH "SHA256=5f9b8ddd74ff6bdff6403877d492665c57b70cff019c59fbce86e205667fbd16"
  PATCHES "${CMAKE_SOURCE_DIR}/cmake/patches/glm-1.0.1/fix_include.patch"
  # GITHUB_REPOSITORY g-truc/glm
  # GIT_TAG           1.0.1
  EXCLUDE_FROM_ALL
  OVERRIDE_FIND_PACKAGE)

# -- Configure toml++

CPMAddPackage(NAME tomlplusplus
  URL      https://github.com/marzer/tomlplusplus/archive/refs/tags/v3.4.0.zip
  VERSION  3.4.0
  URL_HASH "SHA256=ad2a4cd786e25305d802e7490ea65a2531195e5834bf6b4fa5a323421fd81f9b"
  # GITHUB_REPOSITORY marzer/tomlplusplus
  # GIT_TAG           v3.4.0
  EXCLUDE_FROM_ALL
  OVERRIDE_FIND_PACKAGE)
