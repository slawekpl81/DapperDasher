cmake_minimum_required(VERSION 3.28)
project(DapperDasher VERSION 1.0 LANGUAGES CXX)

# Ustaw standard C++ (opcjonalne, ale zalecane dla raylib)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Włącz FetchContent
include(FetchContent)

# Pobierz raylib z GitHuba
FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5  # Stabilna wersja; zmień na master dla najnowszej
)
FetchContent_MakeAvailable(raylib)

# Dodaj executable z plików w src/
add_executable(${PROJECT_NAME}
        src/main.cpp  # Dodaj tu inne pliki: src/other.cpp
)

# Nagłówki z include/
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Linkuj z raylib
target_link_libraries(${PROJECT_NAME} raylib)

# Opcjonalnie: dla Windows/MSVC, ustaw ikony itp. (raylib to obsługuje)
if (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            WIN32_EXECUTABLE TRUE
    )
endif()

# Opcjonalnie: zainstaluj (make install)
install(TARGETS ${PROJECT_NAME} DESTINATION bin)