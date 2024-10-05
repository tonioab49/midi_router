cmake_minimum_required(VERSION 3.25)

project(midi_router)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/libremidi)

if(APPLE)
    find_library(CORE_FOUNDATION CoreFoundation)
    find_library(CORE_MIDI CoreMidi)
endif()

add_executable(MIDIMonitor main.cpp MIDIExecutor.cpp filters.cpp log.cpp)
target_include_directories(MIDIMonitor PRIVATE lib)
target_link_libraries(MIDIMonitor ${CORE_FOUNDATION} ${CORE_MIDI} libremidi)
