cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{DOLCESDK})
    message("$ENV{DOLCESDK}/share/dolce.toolchain.cmake")
    set(CMAKE_TOOLCHAIN_FILE "$ENV{DOLCESDK}/share/dolce.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define DOLCESDK to point to your SDK path!")
  endif()
endif()

project(memtest C ASM)

include("$ENV{DOLCESDK}/share/dolce.cmake" REQUIRED)

set(DOLCE_MKSFOEX_FLAGS "${DOLCE_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")

add_executable(memtest
    src/main.c
    src/memcpy-neon.S
)

target_link_libraries(memtest
    SceDmacmgr_stub
)

dolce_create_self(memtest.self memtest)

set(VPK "memtest.vpk")
set(TITLE_NAME "memcpy")
set(TITLE_ID "MEMC00001")
set(TITLE_VER "01.00")

dolce_create_vpk("${VPK}" "${TITLE_ID}" "memtest.self"
  NAME "${TITLE_NAME}"
  VERSION "${TITLE_VER}"
  FILE sce_sys sce_sys
)