cmake_minimum_required(VERSION 3.10)
project(lr6)

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
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)  # Папка с исходными файлами
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)  # Папка с тестами

# Указываем, что все заголовочные файлы находятся в директории include и её поддиректориях
include_directories(${INCLUDE_DIR})
include_directories(${INCLUDE_DIR}/Mobs)

# Добавляем исходные файлы из папки src
file(GLOB_RECURSE SRC_SOURCES LIST_DIRECTORIES false ${SRC_DIR}/*.cpp ${SRC_DIR}/*.tpp)

# Создание исполняемого файла для основной программы
add_executable(lr_06 main.cpp ${SRC_SOURCES})

# Настройка тестов
enable_testing()

# Автоматическое добавление всех файлов из директории test
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false ${TEST_DIR}/*.cpp)

# Создание исполняемого файла для тестов
add_executable(tests ${TEST_SOURCES} ${SRC_SOURCES})  # Линкование тестов с исходниками

# Линковка с библиотеками
target_link_libraries(tests PRIVATE gtest gtest_main)

# Регистрация тестов для запуска
add_test(NAME MyProjectTests COMMAND tests)