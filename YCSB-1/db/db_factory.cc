//
//  basic_db.cc
//  YCSB-C
//
//  Created by Jinglei Ren on 12/17/14.
//  Copyright (c) 2014 Jinglei Ren <jinglei@ren.systems>.
//

#include "db/db_factory.h"
#include <string>
#include "db/basic_db.h"
#include "db/novelsm_db.h"
#include "db/novel_db_pref.h"

using namespace std;
using ycsbc::DB;
using ycsbc::DBFactory;

DB* DBFactory::CreateDB(utils::Properties &props) {
  if (props["dbname"] == "basic") {
    return new BasicDB;
  } else if (props["dbname"] == "novelsm") {
  if(props["key"] == "serialize"){
    return new Novel(props["dbmem"], props["dbdisk"]);}
    else if(props["key"]=="suffix"){
    return new NovelPref(props["dbmem"], props["dbdisk"]);
    }
  }
   else return NULL;
}

