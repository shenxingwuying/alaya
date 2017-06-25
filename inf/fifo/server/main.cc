/*****************************************************************
 *
 *  Copyright (c) 2016 shenxingwuying. All Rights Reserved
 *
 *****************************************************************/


/**
 * @file: main.cc
 * @author: duyuqi(shenxingwuying@gmail.com)
 * @date: 2016-05-12
 * @brief: 
 *
 */

#include "WritableFile.h"

int main(int argc, char* argv[]) {
    PosixWritableFile file("test.txt");
    //file.Append("abc\n");
    //file.Append("123\n");
    int i = 0;
    std::string str("");
    char buff[1024] = {0};
    while (true) {
        snprintf(buff, 1024, "my_test_key_%d\n", i);
        file.Append(buff);
        memset(buff, 0, 1024);
        i++;
    }
//    file.Flush();
    file.Append("abc_end\n");
    file.Append("123_end\n");
//    file.Close();
    return 0;
}


/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
