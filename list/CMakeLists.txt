# Linked list implementation


add_library(llist sllist dllist)
add_executable(sllist_test sllist_test)
target_link_libraries(sllist_test llist)

