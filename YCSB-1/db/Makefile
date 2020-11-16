CC=g++
CFLAGS=-std=c++11 -c -g -Wall -fgnu-tm
INCLUDES=-I../ -I/usr/local/include -I./
SOURCES=$(wildcard *.cc)
OBJECTS=$(SOURCES:.cc=.o)

all: $(SOURCES) $(OBJECTS)

novelsm_db.o: novelsm_db.cc
	g++ -I../ -I../../ -I../../include -std=c++0x -fno-builtin-memcmp -fpermissive -pthread -DOS_LINUX -DLEVELDB_PLATFORM_POSIX -DMULTILEVEL_IMMUTABLE -DUSE_OFFSETS -DENABLE_RECOVERY -D_ENABLE_PREDICTION  -O3 -march=native -DNDEBUG -std=gnu++0x -c novelsm_db.cc -o novelsm_db.o

novel_db_pref.o: novel_db_pref.cc
	g++ -I../ -I../../ -I../../include -std=c++0x -fno-builtin-memcmp -fpermissive -pthread -DOS_LINUX -DLEVELDB_PLATFORM_POSIX -DMULTILEVEL_IMMUTABLE -DUSE_OFFSETS -DENABLE_RECOVERY -D_ENABLE_PREDICTION -O3 -march=native -DNDEBUG -std=gnu++0x -c novel_db_pref.cc -o novel_db_pref.o



db_factory.o: db_factory.cc
	g++ -I../ -I./  -I../../ -I../../include -std=c++0x -fno-builtin-memcmp -fpermissive -pthread -DOS_LINUX -DLEVELDB_PLATFORM_POSIX -DMULTILEVEL_IMMUTABLE -DUSE_OFFSETS -DENABLE_RECOVERY -D_ENABLE_PREDICTION -O3 -march=native -DNDEBUG -std=gnu++0x  -c db_factory.cc -o db_factory.o


.cc.o:
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@


clean:
	$(RM) $(OBJECTS)

