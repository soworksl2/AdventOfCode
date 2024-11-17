add_executable(day4 main.c)
target_link_libraries(day4 PRIVATE sow_std)

add_custom_command(TARGET day4 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_CURRENT_LIST_DIR}/input.txt $<TARGET_FILE_DIR:day4>
)

