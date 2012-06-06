
add_library(hash SHARED hash.c)
target_link_libraries(hash m)

install(TARGETS hash DESTINATION lib64)
install(FILES "${PROJECT_SOURCE_DIR}/include/hash.h" DESTINATION include)

