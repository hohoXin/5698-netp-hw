#
#  [2019] Signet Lab - Programming for ICT
#  [2020, 2021] Northeastern University - Network Programming
#  All Rights Reserved.
#
#  Authors Filippo Campagnaro and Michele Polese 
#

AUTOMAKE_OPTIONS = foreign

SUBDIRS = m4 \
    basic_utilities \
    examples/lesson_1_hello_world
#     examples/types_declarations_example \
#     examples/statements_example \
#     examples/functions_example \
#     examples/structs_enums_example \
#     examples/pointers_arrays_references_example \
#     examples/argc_argv_example \
#     examples/socket_example \
#     examples/tcp_socket_example \
#     examples/namespaces_example \
#     examples/classes_example \
#     examples/lab_3_example \
#     examples/lab_4_example \
#     examples/lab_5_example \
#     examples/lab_6_example \
#     examples/lab_7_example \
#     examples/memory_example \
#     examples/proxy_example \
#     examples/operator_overloading_example \
#     examples/rtti_example \
#     examples/subclassing_example \
#     examples/templates_example \
#     examples/stdlib_example \
#     examples/constructors_example \
#     examples/tcp_wrapper_example \
#     examples/socket_wrapper_example \
#     examples/threads_example \
#     examples/threads_sync_example \
#     examples/smartpointers_example \
#     conc_queue


if WITH_TEST 
  SUBDIRS +=  \
    test/basic_utilities_test 
  TESTS = \
    test/basic_utilities_test/basic_utilities_test 
endif

ACLOCAL_AMFLAGS = -I m4
