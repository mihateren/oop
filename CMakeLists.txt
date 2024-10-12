cmake_minimum_required(VERSION 3.10)
project(lr3)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление опций компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

# Установка Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  TLS_VERIFY false
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Установка директорий
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${INCLUDE_DIR})

# Указание исходных файлов для библиотеки
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false ${SOURCE_DIR}/*.cpp)

# Создание библиотеки
add_library(lr_03_lib ${SOURCES})

# Создание исполняемого файла для основной программы
add_executable(lr_03_exe main.cpp)
target_link_libraries(lr_03_exe PRIVATE lr_03_lib)

# # Настройка тестов
enable_testing()

# # Создание исполняемого файла для тестов
add_executable(tests test/lrTests.cpp)
target_link_libraries(tests PRIVATE lr_03_lib gtest_main)

# # Регистрация тестов для запуска
add_test(NAME MyProjectTests COMMAND tests)
