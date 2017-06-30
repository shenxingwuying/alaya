#!/usr/bin/env python
# -*- coding: utf-8 -*-

#######################################################################
# Copyright (c) 2017 shenxingwuying. All Rights Reserved
#######################################################################

# @file: get_a_url.py
# @author: duyuqi(shenxingwuying@gmail.com)
# @date: 2017-06-30
# @brief: 

import urllib2


the_url = "http://www.baidu.com"
response = urllib2.urlopen(the_url)
print "geturl:"+response.geturl()
print "info:{0}".format(response.info())
print "getcode:{0}".format(response.getcode())

print response.read()
print "===================================="
print "===================================="
print "=============start 2================"
print "===================================="
print "===================================="
request = urllib2.Request(the_url)
urllib2.urlopen
print request.get_data()



request = urllib2.Request(the_url)

# vim: set expandtab ts=4 sw=4 sts=4 tw=100: #
