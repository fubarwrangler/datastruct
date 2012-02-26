
add_executable(sllist_test sllist_test.c)
target_link_libraries(sllist_test llist)

add_executable(dllist_test dllist_test.c)
target_link_libraries(dllist_test llist)

add_executable(stack_test stack_test.c)
target_link_libraries(stack_test llist)

#add_executable(queue_test queue_test.c)
#target_link_libraries(queue_test llist)

add_executable(hash_test hash_test.c)
target_link_libraries(hash_test hash)
