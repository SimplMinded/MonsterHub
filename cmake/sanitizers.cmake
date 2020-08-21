if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(SANITIZERS "")

    option(ENABLE_ADDRESS_SANITIZER "Enable address sanitizer" OFF)
    if(ENABLE_ADDRESS_SANITIZER)
        list(APPEND SANITIZERS "address")
        message(STATUS "Build with address sanitizer")
    endif()

    option(ENABLE_LEAK_SANITIZER "Enable leak sanitizer" OFF)
    if(ENABLE_LEAK_SANITIZER)
        list(APPEND SANITIZERS "leak")
        message(STATUS "Build with leak sanitizer")
    endif()

    option(ENABLE_UB_SANITIZER "Enable undefined behavior sanitizer" OFF)
    if(ENABLE_UB_SANITIZER)
        list(APPEND SANITIZERS "undefined")
        message(STATUS "Build with undefined behavior sanitizer")
    endif()

    option(ENABLE_THREAD_SANITIZER "Enable thread sanitizer" OFF)
    if(ENABLE_THREAD_SANITIZER)
        if (ENABLE_ADDRESS_SANITIZER OR ENABLE_LEAK_SANITIZER)
            message(WARNING "Thread sanitizer doesn't work with address or leak sanitizer")
        else()
            list(APPEND SANITIZERS "thread")
            message(STATUS "Build with thread sanitizer")
        endif()
    endif()

    option(ENABLE_MEMORY_SANITIZER "Enable memory sanitizer" OFF)
    if(ENABLE_MEMORY_SANITIZER)
        if(ENABLE_ADDRESS_SANITIZER OR ENABLE_LEAK_SANITIZER OR ENABLE_THREAD_SANITIZER)
            message(WARNING "Memory sanitizer doesn't work with address, leak or thread sanitizer")
        else()
            list(APPEND SANITIZERS "memory")
            message(STATUS "Build with memory sanitizer")
        endif()
    endif()

    list(JOIN SANITIZERS "," LIST_OF_SANITIZERS)
else()
    set(LIST_OF_SANITIZERS "")
endif()

if(LIST_OF_SANITIZERS)
    add_compile_options(-fsanitize=${LIST_OF_SANITIZERS})
    add_link_options(-fsanitize=${LIST_OF_SANITIZERS})
endif()
