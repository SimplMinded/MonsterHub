option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors" ON)

if(MSVC)
    add_compile_options(
        /W4          # baseline reasonable warnings
        /w14242      # 'identifier': conversion from 'type1' to 'type2',
                     # possible loss of data
        /w14254      # 'operator': conversion from 'type`:field_bits' to
                     # 'type2:field_bits', posible loss of data
        /w14263      # 'function': member function does not override any base
                     # class virtual member function
        /w14265      # 'classname': class has virtual functions, but destructor
                     # is not virtual
        /w14287      # 'operator': unsigned/megative constant mismatch
        /w14289      # nonstandard extension used: 'variable': loop control
                     # variable declared on the for-loop is used outside the
                     # for-loop scope
        /w14296      # 'operator': expression is always 'boolean_value'
        /w14311      # 'variable': pointer truncation from 'type1' to 'type2'
        /w14545      # expression before comma evaluates to a function which is
                     # missing an argument list
        /w14546      # function call before comma missing argument list
        /w14547      # 'operator': operator before comma has no effect;
                     # expected operator with side-effect
        /w14549      # 'operator': operator before comma has no effect; did you
                     # intend 'operator'?
        /w14555      # expression has no effect; expected expression with
                     # side-effect
        /w14619      # pragma warning: there is no warning number 'number'
        /w14640      # 'instance': construction of local static object is not
                     # thread-safe
        /w14826      # Conversion from 'type1' to 'type2' is sign-extended.
                     # This may cause unexpected runtime behavior.
        /w14905      # wide string literal cast to 'LPSTR'
        /w14906      # string literal cast to 'LPWSTR'
        /w14928      # illegal copy-initialization; more than one user-defined
                     # conversion has been implicitly applied
        /permissive- # standard conformance mode for MSVC compiler
        /wd4996      # 'identifier': This function or variable may be unsafe.
                     # Consider using 'identifier' instead.
    )

    if(WARNINGS_AS_ERRORS)
        add_compile_options(/WX)
        message(STATUS "Treating compiler warnings as errors")
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang" OR
       CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(
        -Wall
        -Wextra              # reasonable and standard
        -Wshadow             # warn the user if a variable declaration shadows
                             # one from a parent context
        -Wnon-virtual-dtor   # warn the user if a class with virtual functions
                             # has a non-virtual destructor
        -Wold-style-cast     # warn for C-style casts
        -Wcast-align         # warn for potential performance problem casts
        -Wunused             # warn on anything being unused
        -Woverloaded-virtual # warn if you overload (not override) a virtual
                             #function
        -Wpedantic           # warn if non-standard C++ is used
        -Wconversion         # warn on type conversions that may lose data
        -Wsign-conversion    # warn on sign conversions
        -Wnull-dereference   # warn if a null dereference is detected
        -Wdouble-promotion   # warn if float is implicit promoted to double
        -Wno-format
    )

    if(WARNINGS_AS_ERRORS)
        add_compile_options(-Werror)
        message(STATUS "Treating compiler warnings as errors")
    endif()
else()
    message(FATAL "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

