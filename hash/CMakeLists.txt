
add_library(hash SHARED hash.c)
target_link_libraries(hash m)

add_library(set SHARED set.c)
target_link_libraries(set hash)

add_executable(set_test set_test.c)
target_link_libraries(set_test set)

install(TARGETS hash DESTINATION lib64)
install(FILES "${PROJECT_SOURCE_DIR}/include/hash.h" DESTINATION include)

