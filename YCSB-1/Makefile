CC=g++
CFLAGS=-std=c++11 -g -Wall -pthread -I./ -L/usr/local/lib -I../
LDFLAGS= -lpthread -ltbb -lhiredis -lleveldb -lsnappy
SUBDIRS=core db
SUBSRCS=$(wildcard core/*.cc) $(wildcard db/*.cc)
OBJECTS=$(SUBSRCS:.cc=.o)
EXEC=ycsbc

INCL := $(shell find $(../out-static/db) -name '*.o')
INCL1 := $(shell find $(../out-static/port) -name '*.o')
INCL2 := $(shell find $(../out-static/table) -name '*.o')
INCL3 := $(shell find $(../out-static/util) -name '*.o')




all: $(SUBDIRS) $(EXEC)

$(SUBDIRS):
	$(MAKE) -C $@
$(EXEC): $(wildcard *.cc) $(OBJECTS)
	g++ -pthread -I../ -I./ -I./YCSB-C-1 -I../include -std=c++0x -fno-builtin-memcmp -fpermissive -pthread -DOS_LINUX -DLEVELDB_PLATFORM_POSIX -DMULTILEVEL_IMMUTABLE -DUSE_OFFSETS -DENABLE_RECOVERY -D_ENABLE_PREDICTION -DSNAPPY -O3 -march=native -DNDEBUG -std=gnu++0x ycsbc.cc out-static/db/builder.o out-static/db/dbformat.o out-static/db/db_impl.o out-static/db/db_iter.o out-static/db/dumpfile.o out-static/db/filename.o out-static/db/log_reader.o out-static/db/log_writer.o out-static/db/memtable.o out-static/db/table_cache.o out-static/db/version_edit.o out-static/db/version_set.o out-static/db/write_batch.o out-static/table/block_builder.o out-static/table/block.o out-static/table/filter_block.o out-static/table/format.o out-static/table/iterator.o out-static/table/merger.o out-static/table/table_builder.o out-static/table/table.o out-static/table/two_level_iterator.o out-static/util/arena.o out-static/util/bloom.o out-static/util/BloomFilter.o out-static/util/cache.o out-static/util/coding.o out-static/util/comparator.o out-static/util/cpumap.o out-static/util/crc32c.o out-static/util/debug.o out-static/util/env.o out-static/util/env_posix.o out-static/util/filter_policy.o out-static/util/hash.o out-static/util/histogram.o out-static/util/logging.o out-static/util/MurmurHash3.o out-static/util/options.o out-static/util/status.o out-static/util/thpool.o out-static/port/port_posix.o out-static/util/testutil.o db/novelsm_db.o core/core_workload.o db/db_factory.o   db/novel_db_pref.o -lnuma ../libsnappy.a -o $@
clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir $@; \
	done
	$(RM) $(EXEC)

.PHONY: $(SUBDIRS) $(EXEC)

