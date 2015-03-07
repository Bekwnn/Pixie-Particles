add_executable(${EXECUTABLE_NAME} main.cpp)

#set to statically link
set(SFML_STATIC_LIBRARIES TRUE)

#find sfml components
find_package(SFML REQUIRED system graphics window)

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})

install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)