add_executable(day2 main.c)

add_custom_command(TARGET day2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/input.txt $<TARGET_FILE_DIR:day2>
)
