cmake_minimum_required(VERSION 3.24)
project(life)

set(CMAKE_CXX_STANDARD 17)

# Spécifiez les répertoires d'en-tête et de bibliothèques SFML
set(SFML_INCLUDE_DIR "C:\\SFML-64\\include")
set(SFML_LIBRARY_DIR "C:\\SFML-64\\lib")
set(SFML_DIR "C:\\SFML-64\\lib\\cmake\\SFML")

# Ajoutez le répertoire de configuration CMake de SFML à la variable CMAKE_MODULE_PATH
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};C:\\SFML-64\\cmake\\SFML")


add_executable(life src/main.cpp src/core.cpp src/core.h src/entity.cpp src/entity.h src/friendly.cpp src/friendly.h src/hostil.cpp src/hostil.h)

# Trouvez les bibliothèques SFML nécessaires pour le projet
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
find_package(SFML 2.5 COMPONENTS system REQUIRED)
find_package(SFML 2.5 COMPONENTS window REQUIRED)

# Liez les bibliothèques SFML au projet
target_link_libraries(life sfml-graphics sfml-system sfml-window)

#
foreach(SFML_LIB graphics system window)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "C:\\SFML-64\\bin\\sfml-${SFML_LIB}-d-2.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
endforeach()