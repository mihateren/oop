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

# Указываем директорию, в которой находятся все заголовочные файлы
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# Указываем директорию, в которой находятся все исходные файлы
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Указываем директорию, в которой находятся все тестовые файлы
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

# Находим все заголовочные файлы в директории и её поддиректориях
file(GLOB_RECURSE HEADERS ${INCLUDE_DIR}/*.hpp)

# Находим все исходные файлы в директории и её поддиректориях
file(GLOB_RECURSE SRC_SOURCES LIST_DIRECTORIES false ${SRC_DIR}/*.cpp ${SRC_DIR}/*.tpp)

# Находим все тестовые файлы в директории и её поддиректориях
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false ${TEST_DIR}/*.cpp)

# Добавляем все найденные директории в список включаемых директорий
foreach(HEADER ${HEADERS})
    get_filename_component(HEADER_DIR ${HEADER} DIRECTORY)
    include_directories(${HEADER_DIR})
endforeach()

# Добавляем исходные файлы проекта
set(SOURCE_FILES
    main.cpp
    ${SRC_SOURCES}
)

# Добавляем исполняемый файл
add_executable(lr6 ${SOURCE_FILES})

# Добавляем директории с заголовочными файлами для исполняемого файла
target_include_directories(lr6 PRIVATE ${INCLUDE_DIR})

# Добавляем исполняемый файл для тестов
add_executable(tests ${TEST_SOURCES})

# Добавляем директории с заголовочными файлами для тестов
target_include_directories(tests PRIVATE ${INCLUDE_DIR})

# Линковка с библиотеками для тестов
target_link_libraries(tests PRIVATE gtest gtest_main)

# Регистрация тестов для запуска
add_test(NAME MyProjectTests COMMAND tests)