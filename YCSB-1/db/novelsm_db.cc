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

#include "novelsm_db.h"
using namespace std;
using namespace leveldb;
#include <iostream>
namespace ycsbc
{

string Novel::encode_key_table_(const string& table, const string& key){
string encode;
encode = table + key;
return encode;
}

Novel::Novel(const std::string &dbdisk, const std::string &dbmem)
{
    leveldb::Options options;
    options.create_if_missing = true;

   leveldb::Status status = leveldb::DB::Open(options, dbdisk, dbmem, &db);
}
Novel::~Novel()
{
    delete db;
}


int Novel::Read(const std::string &table, const std::string &key, const std::vector<std::string> *fields, std::vector<KVPair> &result)
{
	string result_record;
	string key_table = encode_key_table_(table, key);
	db->Get(leveldb::ReadOptions(), key_table, &result_record);
	vector<DB::KVPair> restore;
	deserialize(restore, result_record.c_str(), sizeof(result_record));
    	parse_response(result, fields, restore);
	
	
	

    
    return kOK;
}

int Novel::Scan(const std::string &table, const std::string &key, int record_count, const std::vector<std::string> *fields,std::vector<std::vector<KVPair>> &result)
{

    return kOK;
}

int Novel::Update(const std::string &table, const std::string &key, std::vector<KVPair> &values)
{
    unsigned int total_count = 0;
    string to_save = serialize(values, &total_count);
    string key_table = encode_key_table_(table, key);
    db->Put(leveldb::WriteOptions(), key_table, to_save);

    return kOK;
}

int Novel::Insert(const std::string &table, const std::string &key, std::vector<KVPair> &values)
{

return Update(table, key, values);

}

int Novel::Delete(const std::string &table, const std::string &key)
{
   string key_table = encode_key_table_(table, key);
   db->Delete(leveldb::WriteOptions(), key_table);
    return kOK;
}

std::string Novel::serialize(std::vector<DB::KVPair> &pairs, unsigned int *count) {
    unsigned int total_count = 0;

    for(int i = 0; i < pairs.size(); i++ ) {
        // cout << v[i]<< endl;
        total_count += pairs[i].first.length() + 1;
        total_count += pairs[i].second.length() + 1;
    }

    char *buffer = new char[total_count];

    int idx = 0;

    for(int i = 0; i < pairs.size(); i++ ) {
        string s = pairs[i].first;
        for (int j = 0; j < s.size(); j ++ ) {
            buffer[idx ++] = s[j];
        }
        buffer[idx ++] = 0;
        string s2 = pairs[i].second;
        for (int j = 0; j < s2.size(); j ++ ) {
            buffer[idx ++] = s2[j];
        }
        buffer[idx ++] = 0;
    }

    *count  = total_count;
    
    const char *begin = &(buffer[0]);  
    std::string test = string(begin, total_count);
    return test;
}

void Novel::parse_response(vector<DB::KVPair> &result, const std::vector<std::string> *fields, vector<DB::KVPair> &result_record){
	
	if (fields) {
	
	for(int j=0; j< fields->size(); j++){
	
		for (int i = 0; i< result_record.size(); i++){
		cout<<result_record[i].first<<fields->operator[](j)<<endl;
			if(strcmp(result_record[i].first.c_str(),fields->operator[](j).c_str())==0){
				cout<<result_record[i].first.c_str()<<":"<<(fields->operator[](j)).c_str()<<endl;
				result.push_back(result_record[i]);
			
			}
		}
	
	}
	
	}

}
void Novel::deserialize(vector<DB::KVPair> &result,  const char* s, int total_count) {
    string tmp;
    for(int i = 0; i < total_count; i ++ ) {
        const char *begin = &(s[i-1]);
        if (i == 0)
        	begin = &(s[i]);
        int size = 0;
        while(s[i++] != 0) {
        //cout<<s.data()[i++]<<endl;
            size += 1;
        }
        //cout<<size<<endl;
        tmp = string(begin, size+1);
        begin = &(s[i]);
        size = 0;
        while(s[i++] != 0) {
        //cout<<s.data()[i++]<<endl;
            size += 1;
        }
        result.push_back(make_pair(tmp, (string(begin, size+1))));
    }
}


}
