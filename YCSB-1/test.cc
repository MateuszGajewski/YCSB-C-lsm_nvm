//
//  ycsbc.cc
//  YCSB-C
//
//  Created by Jinglei Ren on 12/19/14.
//  Copyright (c) 2014 Jinglei Ren <jinglei@ren.systems>.
//

#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <future>
#include "core/utils.h"
#include "core/timer.h"
#include "core/client.h"
#include "core/core_workload.h"
#include "db/db_factory.h"
/*#include "core/core_workload.o"
#include "db/db_factory.o"
#include "db/level_db.o" 
#include "db/novelsm_db.o"
#include "db/redis_db.o"
#include "db/hashtable_db.o"*/

/*using namespace std;
#include "db/db_factory.h"
#include <string>
#include "db/basic_db.h"
#include "db/lock_stl_db.h"
#include "db/redis_db.h"
#include "db/tbb_rand_db.h"
#include "db/tbb_scan_db.h"
#include "db/level_db.h"
*/
#include "db/novelsm_db.h"

using namespace std;
using ycsbc::DB;
using ycsbc::DBFactory;

int main(){
ycsbc::Novel("a", "b");

}


