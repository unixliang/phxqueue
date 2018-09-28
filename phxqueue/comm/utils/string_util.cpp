/*
Tencent is pleased to support the open source community by making PhxQueue available.
Copyright (C) 2017 THL A29 Limited, a Tencent company. All rights reserved.
Licensed under the BSD 3-Clause License (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

<https://opensource.org/licenses/BSD-3-Clause>

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
*/



#include <string>

#include "phxqueue/comm/utils/string_util.h"


namespace phxqueue {

namespace comm {

namespace utils {


using namespace std;


void StrSplitList(const string &str, const string &delimiters, vector<std::string> &results) {
    results.clear();
    auto last = 0;
    auto found = str.find_first_of(delimiters);
    while (string::npos != found) {
        auto r = str.substr(last, found - last);
        last = found + 1;
        found = str.find_first_of(delimiters, last);
        if (!r.empty()) results.push_back(r);
    }
    auto r = str.substr(last);
    if (!r.empty()) results.push_back(r);
}


}  // namespace utils

}  // namespace comm

}  // namespace phxqueue


//gzrd_Lib_CPP_Version_ID--start
#ifndef GZRD_SVN_ATTR
#define GZRD_SVN_ATTR "0"
#endif
static char gzrd_Lib_CPP_Version_ID[] __attribute__((used))="$HeadURL$ $Id$ " GZRD_SVN_ATTR "__file__";
// gzrd_Lib_CPP_Version_ID--end

