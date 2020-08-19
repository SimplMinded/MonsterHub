function(add_compile_switch
         SWITCH_NAME SWITCH_DESC SWITCH_DEFAULT)

option(${SWITCH_NAME} "${SWITCH_DESC}" ${SWITCH_DEFAULT})

if(CMAKE_BUILD_TYPE IN_LIST ARGN)
    if(${SWITCH_DEFAULT})
        set(${SWITCH_NAME} OFF)
    else()
        set(${SWITCH_NAME} ON)
    endif()
endif()

if(${${SWITCH_NAME}})
    add_definitions("-D${SWITCH_NAME}=1")
else()
    add_definitions("-D${SWITCH_NAME}=0")
endif()

message(STATUS "Switch ${SWITCH_NAME} is set to ${${SWITCH_NAME}}")

endfunction()

add_compile_switch(
    DEBUG_FEATURE_LOGGING_ENABLED "Enables logging" ON
    "Release")

add_compile_switch(
    DEBUG_OPTION_LOG_TO_TERMINAL_ENABLED "Enable logging to terminal" ON)
add_compile_switch(
    DEBUG_OPTION_LOG_TO_FILE_ENABLED "Enable logging to file" ON)

