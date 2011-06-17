AC_INIT([example-storage-engine], [0.1], [kazuki.ohta@gmail.com])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_PROG_CC
AC_PROG_CXX
AC_PROG_CPP
AC_PROG_LIBTOOL

standalone_build=

AC_DEFUN([CONFIG_OPTION_PLUGINS],
  AC_MSG_CHECKING([standalone build])
  AC_ARG_WITH([plugins],,
    [
      standalone_build="no"
      AC_MSG_RESULT([no])
    ],
    [
      standalone_build="yes"
      AC_MSG_RESULT([yes])
    ])
)

AC_DEFUN([CONFIG_OPTION_MYSQL],[
  AC_MSG_CHECKING([mysql source])

  ac_mysql_source_dir=
  AC_ARG_WITH([mysql-source],
    [AS_HELP_STRING([--with-mysql-source=PATH], [MySQL source directory PATH])],
    [
      ac_mysql_source_dir="$withval"
      if test -f "$ac_mysql_source_dir/sql/handler.h" ; then
        MYSQL_INC="-I$ac_mysql_source_dir/sql"
        MYSQL_INC="$MYSQL_INC -I$ac_mysql_source_dir/include"
        MYSQL_INC="$MYSQL_INC -I$ac_mysql_source_dir/regex"
        MYSQL_INC="$MYSQL_INC -I$ac_mysql_source_dir"
        AC_SUBST(MYSQL_INC)
        AC_MSG_RESULT([yes])
      else
        AC_MSG_ERROR([invalid MySQL source directory])
      fi
    ],
    [AC_MSG_ERROR([--with-mysql-source=PATH is required for standalone build])]
  )
  MYSQL_SOURCE="$ac_mysql_source_dir"
  AC_SUBST(MYSQL_SOURCE)

  ac_mysql_build_dir=
  AC_ARG_WITH([mysql-build],
    [AS_HELP_STRING([--with-mysql-build=PATH], [MySQL build directory PATH])],
    [ac_mysql_build_dir="$withval"],
    [ac_mysql_build_dir="$ac_mysql_source_dir"]
  )
  MYSQL_BUILD="$ac_mysql_build_dir"
  AC_SUBST(MYSQL_BUILD)

  AC_MSG_CHECKING([mysql_config])
  AC_ARG_WITH([mysql-config],
    [AS_HELP_STRING([--with-mysql-config=PATH],
                    [mysql_config PATH])],
    [ac_mysql_config="$withval"],
    [ac_mysql_config=])
  if test -z "$ac_mysql_config"; then
    AC_PATH_PROG(ac_mysql_config, mysql_config, mysql-config-not-found)
  fi
  if test "$ac_mysql_config" = "mysql-config-not-found"; then
    AC_MSG_ERROR([can't detect mysql_config. Please specify mysql_config path by --with-mysql-config=PATH.])
  fi
  AC_MSG_RESULT([$ac_mysql_config])
  plugindir="$($ac_mysql_config --plugindir)"
  if test $? -ne 0; then
    AC_MSG_ERROR([failed to run "$ac_mysql_config": $plugindir])
  fi
  MYSQL_INC="$MYSQL_INC $($ac_mysql_config --include)"
  ac_mysql_major_version="`$ac_mysql_config --version | cut -b 1,3`"
  MYSQL_CFLAGS="$MYSQL_CFLAGS $($ac_mysql_config --cflags)"
  if test $ac_mysql_major_version -lt 55; then
    MYSQL_VERSION_CFLAGS="-DMYSQL51"
    AC_SUBST(MYSQL_VERSION_CFLAGS)
    MYSQL_VERSION="5.1"
  else
    MYSQL_VERSION="5.5"
  fi
  AC_SUBST(MYSQL_VERSION)
  AC_SUBST(plugindir)
])

AC_ARG_WITH(debug,
    [  --with-debug            Add debug code
  --with-debug=full       Add debug code (adds memory checker, very slow)],
    [with_debug=$withval],
    [with_debug=no])
if test "$with_debug" = "yes"
then
  # Medium debug.
  AC_DEFINE([DBUG_ON], [1], [Use libdbug])
  CFLAGS="$DEBUG_CFLAGS $DEBUG_OPTIMIZE_CC -DSAFE_MUTEX $CFLAGS"
  CXXFLAGS="$DEBUG_CXXFLAGS $DEBUG_OPTIMIZE_CXX -DSAFE_MUTEX $CXXFLAGS"
elif test "$with_debug" = "full"
then
  # Full debug. Very slow in some cases
  AC_DEFINE([DBUG_ON], [1], [Use libdbug])
  CFLAGS="$DEBUG_CFLAGS -DSAFE_MUTEX -DSAFEMALLOC $CFLAGS"
  CXXFLAGS="$DEBUG_CXXFLAGS -DSAFE_MUTEX -DSAFEMALLOC $CXXFLAGS"
else
  # Optimized version. No debug
  AC_DEFINE([DBUG_OFF], [1], [Don't use libdbug])
  CFLAGS="$OPTIMIZE_CFLAGS $CFLAGS"
  CXXFLAGS="$OPTIMIZE_CXXFLAGS $CXXFLAGS"
fi

CONFIG_OPTION_PLUGINS
if test "$standalone_build" = "yes"; then
  CONFIG_OPTION_MYSQL
else
  MYSQL_INC="-I../../sql -I../../include -I../../regex -I../.."
  plugindir="\$(pkglibdir)/plugin"
fi
AC_SUBST(MYSQL_INC)
AC_SUBST(MYSQL_CFLAGS)
AC_SUBST(plugindir)

CFLAGS="$CFLAGS -Werror"
CXXFLAGS="$CXXFLAGS -Werror -fno-implicit-templates -fno-exceptions -fno-rtti -felide-constructors"

AC_CONFIG_FILES([
  Makefile
  src/Makefile
])
AC_OUTPUT
