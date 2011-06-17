AUTOMAKE_OPTIONS = 1.9.7

AM_CPPFLAGS = $(MYSQL_INC) $(EXAMPLE_CFLAGS) $(MYSQL_VERSION_CFLAGS)
ACLOCAL_AMFLAGS = $$ACLOCAL_ARGS

noinst_HEADERS = ha_example.h

plugin_LTLIBRARIES     = ha_example.la
ha_example_la_LDFLAGS  = -module $(EXAMPLE_LIBS) -L$(MYSQL_BUILD)/libservices/ -lmysqlservices
ha_example_la_CXXFLAGS = $(AM_CFLAGS) $(MYSQL_CFLAGS) -DMYSQL_DYNAMIC_PLUGIN
ha_example_la_CFLAGS   = $(AM_CFLAGS) $(MYSQL_CFLAGS) -DMYSQL_DYNAMIC_PLUGIN
ha_example_la_SOURCES  = ha_example.cc

plugin_LIBRARIES                    = libexample_storage_engine.a
libexample_storage_engine_a_LDFLANGS  = $(EXAMPLE_LIBS)
libexample_storage_engine_a_CXXFLAGS  = $(AM_CFLAGS) $(MYSQL_CFLAGS)
libexample_storage_engine_a_CFLAGS    = $(AM_CFLAGS) $(MYSQL_CFLAGS)
libexample_storage_engine_a_SOURCES   = ha_example.cc

EXTRA_DIST = plug.in
