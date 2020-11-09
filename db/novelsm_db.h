#ifndef YCSB_C_NOVELSM_H
#define YCSB_C_NOVELSM_H
#include "core/db.h"
#include <sys/types.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "db/db_impl.h"
#include "db/version_set.h"
#include "leveldb/cache.h"
#include "leveldb/db.h"
#include "leveldb/env.h"
#include "leveldb/write_batch.h"
#include "port/port.h"
#include "util/crc32c.h"
#include "util/histogram.h"
#include "util/mutexlock.h"
#include "util/random.h"
#include "util/testutil.h"

#include <streambuf>
#include <string>
#include <istream>
using namespace std;
namespace ycsbc
{

class Novel : public DB
{
    leveldb::DB *db;
    int serializator = 0;
 

public:
	
    Novel(const std::string&, const std::string&);
    ~Novel();

    int Read(const std::string&, const std::string&, const std::vector<std::string>*, std::vector<KVPair>&);

    int Scan(const std::string&, const std::string&, int, const std::vector<std::string>*,std::vector<std::vector<KVPair>>&);

    int Update(const std::string&, const std::string&, std::vector<KVPair>&);

    int Insert(const std::string&, const std::string&, std::vector<KVPair>&);

    int Delete(const std::string&, const std::string&);

private:
std::string serialize(std::vector<DB::KVPair> &pairs, unsigned int *count);
void deserialize(vector<DB::KVPair> &result,  const char* s, int total_count);
std::string encode_key_table_(const std::string&, const std::string&);
void parse_response(vector<DB::KVPair> &result, const std::vector<std::string> *fields, vector<DB::KVPair> &result_record);
};


}

#endif
