#
#  [2019] Signet Lab - Programming for ICT
#  [2020, 2021] Northeastern University - Network Programming
#  All Rights Reserved.
#
#  Authors Filippo Campagnaro and Michele Polese 
#

AC_INIT(PFICT,1.0)
AM_INIT_AUTOMAKE 
AC_LANG(C++)
AC_PROG_CXX
AM_PROG_AR
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL
LT_INIT
AC_CONFIG_MACRO_DIR([m4])
AC_DISABLE_STATIC
AC_LIBTOOL_WIN32_DLL





#######################################################################

AC_DEFINE(CPP_NAMESPACE,std) 

AC_CHECK_LIB(pthread, pthread_create, [LIBS="$LIBS -lpthread"]) 

AC_ARG_WITH([test],
  AC_HELP_STRING([--with-test=VAL],
    [Test library enable]),
  [with_test="$withval"],
  [with_test=""])

PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/basic_utilities'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/conc_queue'
PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/lesson_1_hello_world'
PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/types_declarations_example'
PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/pointers_arrays_references_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/structs_enums_examples'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/functions_examples'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/statements_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/argc_argv_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/socket_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/tcp_socket_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/namespaces_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/classes_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/constructors_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/lab_3_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/lab_4_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/lab_5_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/lab_6_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/lab_7_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/memory_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/proxy_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/operator_overloading_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/templates_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/stdlib_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/rtti_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/subclassing_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/tcp_wrapper_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/socket_wrapper_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/smartpointers_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/threads_example'
# PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'-I$(top_srcdir)/examples/threads_sync_example'
PFICT_CPPFLAGS="$PFICT_CPPFLAGS "'$(GCC6_FLAG)'

PFICT_CXXFLAGS="$PFICT_CXXFLAGS "'-Wall'
PFICT_CXXFLAGS="$PFICT_CXXFLAGS "'-ggdb3'
PFICT_CXXFLAGS="$PFICT_CXXFLAGS "'-std=c++11'

PFICT_LDFLAGS="$PFICT_LDFLAGS "'-L$(top_srcdir)/basic_utilities'
# PFICT_LDFLAGS="$PFICT_LDFLAGS "'-L$(top_srcdir)/conc_queue'

PFICT_LIBADD="$PFICT_LIBADD"

BUTILS_LDADD="$BUTILS_LDADD "'-lbasic_utilities'
# CONCQ_LDADD="$BUTILS_LDADD "'-lconc_queue'

PFICT_LDADD="$PFICT_LDADD $BUTILS_LDADD"
# PFICT_LDADD="$PFICT_LDADD $BUTILS_LDADD $CONCQ_LDADD"

AM_CONDITIONAL(WITH_TEST, test "x${with_test}" != "x")

if test "x${with_test}" != "x"; then  
  AC_ARG_WITH_TEST
fi

AC_SUBST(PFICT_CPPFLAGS) 
AC_SUBST(PFICT_CXXFLAGS)
AC_SUBST(PFICT_LDFLAGS)
AC_SUBST(PFICT_LIBADD)
AC_SUBST(PFICT_LDADD)
AC_SUBST(BUTILS_LDADD)
AC_SUBST(CONCQ_LDADD)
AC_SUBST(top_srcdir)
AC_SUBST(with_test)

AC_CONFIG_FILES([
  Makefile
  m4/Makefile
  basic_utilities/Makefile
  examples/lesson_1_hello_world/Makefile
  examples/types_declarations_example/Makefile
  examples/pointers_arrays_references_example/Makefile
  test/basic_utilities_test/Makefile
  ])

# examples/statements_example/Makefile
# examples/structs_enums_example/Makefile
# examples/functions_example/Makefile
# examples/argc_argv_example/Makefile
# examples/socket_example/Makefile
# examples/tcp_socket_example/Makefile
# examples/namespaces_example/Makefile
# examples/classes_example/Makefile
# examples/constructors_example/Makefile
# examples/lab_3_example/Makefile
# examples/lab_4_example/Makefile
# examples/lab_5_example/Makefile
# examples/lab_6_example/Makefile
# examples/lab_7_example/Makefile
# examples/memory_example/Makefile
# examples/proxy_example/Makefile
# examples/operator_overloading_example/Makefile
# examples/rtti_example/Makefile
# examples/subclassing_example/Makefile
# examples/templates_example/Makefile
# examples/stdlib_example/Makefile
# examples/tcp_wrapper_example/Makefile
# examples/socket_wrapper_example/Makefile
# examples/smartpointers_example/Makefile
# examples/threads_example/Makefile
# examples/threads_sync_example/Makefile
# conc_queue/Makefile


AC_OUTPUT
