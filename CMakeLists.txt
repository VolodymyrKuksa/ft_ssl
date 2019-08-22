cmake_minimum_required(VERSION 3.14)
project(ft_ssl C)

FILE(GLOB_RECURSE LIBFT_DIR "libft/src/*.c")
add_library(libft STATIC ${LIBFT_DIR})

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        src/main.c
        includes/ft_ssl.h
        src/md5/md5.c
        src/md5/md5_round_functions.c includes/md5.h src/padding.c includes/data_types.h src/common.c src/md5/md5_g_functions.c src/md5/md5_constants.c src/sha256/sha256.c includes/sha256.h src/sha256/sha256_constants.c)

set(INCLUDE_DIRECTORIES
        includes
        libft/includes)

include_directories(${INCLUDE_DIRECTORIES})

add_executable(ft_ssl ${SOURCE_FILES})

target_link_libraries(ft_ssl libft)