# This is the root ITK CMakeLists file.
cmake_minimum_required(VERSION 2.8.9)
if(COMMAND CMAKE_POLICY)
  cmake_policy(SET CMP0003 NEW)
endif()


# This project is designed to be built outside the Insight source tree.
project(RayTracing)

# Find ITK.
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

add_executable(RayTracing    	Main.cpp
				Common.h
				Ray.h
				Ray.cpp
				Object.h
				Object.cpp
				Camera.h
				Camera.cpp
				RGBColor.h
				RGBColor.cpp
				Light.h
				Light.cpp
				Scene.h
				Scene.cpp
)

target_link_libraries(RayTracing ${ITK_LIBRARIES})