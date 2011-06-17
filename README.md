# Description

The independent repository of MySQL 5.5 Example Storage Engine. You're able to
start developing brand-new storage engine from here.

This repository supports:

* Build System by autotools
* SQL-based test system by mysql-test-run.pl

# Build

## Build MySQL 5.5

First, you need to build MySQL 5.5.

```bash
cmake . -DCMAKE_INSTALL_PREFIX=/home/kzk/mysql/ -DDEFAULT_CHARSET=utf8 -DDEFAULT_COLLATION=utf8_general_ci
```

## Build ha_example

Second, you can build this repository.

```bash
./autogen.sh
./configure --with-mysql-source=$MYSQL_SOURCE_DIR
make clean; make;
```

# Run SQL tests

```bash
./test/run-sql-test.sh
```

# Directories

## src/ha_example.h, src/ha_example.cpp

Storage engine implementation.

## test/sql/

SQL test code directory.

### test/sql/t

SQL test scripts.

### test/sql/r

SQL results.

# Thanks

This project is greatly influenced by mroonga project. Thanks!

* https://github.com/mroonga/mroonga
