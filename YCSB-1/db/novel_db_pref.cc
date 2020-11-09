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

#include "novel_db_pref.h"
using namespace std;
using namespace leveldb;
#include <iostream>
namespace ycsbc
{

string  NovelPref::encode_key_table_(const string& table, const string& key, const std::string& fields){
string encode;
encode = table + key + fields;
return encode;
}

 NovelPref:: NovelPref(const std::string &dbdisk, const std::string &dbmem)
{
    leveldb::Options options;
    options.create_if_missing = true;

   leveldb::Status status = leveldb::DB::Open(options, dbdisk, dbmem, &db);
}
 NovelPref::~ NovelPref()
{
    delete db;
}


int  NovelPref::Read(const std::string &table, const std::string &key, const std::vector<std::string> *fields, std::vector<KVPair> &result)
{
	string result_record;
	if (fields){
	for(const auto i : (*fields)){

	string key_table = encode_key_table_(table, key, i);
	db->Get(leveldb::ReadOptions(), key_table, &result_record);
	result.push_back(make_pair(i, result_record));
	}}
	else {
	for(const auto i : fields_set){

	string key_table = encode_key_table_(table, key, i);
	db->Get(leveldb::ReadOptions(), key_table, &result_record);
	result.push_back(make_pair(i, result_record));
	}
	}
	
	
	

    
    return kOK;
}

int  NovelPref::Scan(const std::string &table, const std::string &key, int record_count, const std::vector<std::string> *fields,std::vector<std::vector<KVPair>> &result)
{

    return kOK;
}

int  NovelPref::Update(const std::string &table, const std::string &key, std::vector<KVPair> &values)
{
for(int i = 0; i < values.size(); i++){
    unsigned int total_count = 0;
    string key_table = encode_key_table_(table, key, (values[i]).first);
    db->Put(leveldb::WriteOptions(), key_table, (values[i]).second);
    //fields_set.insert((values[i]).first);
    }

    return kOK;
}

int  NovelPref::Insert(const std::string &table, const std::string &key, std::vector<KVPair> &values)
{

return Update(table, key, values);

}

int  NovelPref::Delete(const std::string &table, const std::string &key)
{
   string test;
   for(auto i : fields_set){
   string key_table = encode_key_table_(table, key, i);

   	db->Delete(leveldb::WriteOptions(), key_table);}
    return kOK;
}







}
