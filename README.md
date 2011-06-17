# Description

The independent repository of MySQL 5.5 Example Storage Engine. You're able to
start developing brand-new storage engine from here.

# Build

```bash
./autogen.sh
./configure --with-mysql-source=$MYSQL_SOURCE_DIR
make clean; make;
```

# Test

```bash
./test/run-sql-test.sh
```
