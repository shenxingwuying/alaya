/*****************************************************************
 *
 *  Copyright (c) 2016 KingSoft.com, Inc. All Rights Reserved
 *
 *****************************************************************/


/**
 * @file: singleton.h
 * @author: duyuqi(duyuqi@kingsoft.com)
 * @date: 2016-04-06
 * @brief:
 *
 */

#ifndef ALAYA_PATTERN_SINGTON_H
#define ALAYA_PATTERN_SINGTON_H

#define SINGTON_PATTERN(classname)             \
    public:                                    \
        static classname Instance() {          \
            if (NULL != name) {                \
                return name;                   \
            }                                   \
            name = new classname();             \
            return name;                        \
        }                                       \                                        \
        static bool isCreated() {               \
            return (NULL != name);              \
        }                                       \
    protected:                                  \
        classname* name;                        \
    private:                                    \




class A {
    SINGTON_PATTERN(A);

}
#endif
