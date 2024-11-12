option(SOW_STD_EXAMPLES "build examples of the sow_std library" ON)


set(SRC 
    sstr.c
    svector.c
    svectorstr.c)

set(HFILES
    smath.h
    sstr.h
    svector.h
    svectorstr.h)

add_library(sow_std STATIC ${SRC} ${HFILES})

if (SOW_STD_EXAMPLES)
    add_executable(sstr mainsstr.c)
    target_link_libraries(sstr sow_std)

    add_executable(smath mainsmath.c)
    target_link_libraries(smath sow_std)

    add_executable(svector mainsvector.c)
    target_link_libraries(svector sow_std)

    add_executable(svectorstr mainsvectorstr.c)
    target_link_libraries(svectorstr sow_std)
endif()
