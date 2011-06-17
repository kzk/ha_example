disable_query_log;
if (!`SELECT 1 FROM information_schema.plugins WHERE plugin_name="example"`)
{
  INSTALL PLUGIN example SONAME 'ha_example.so';
}
set storage_engine=example;
enable_query_log;
