#!/usr/bin/env python
# -*- coding: utf-8 -*-

#######################################################################
# Copyright (c) 2017 shenxingwuying. All Rights Reserved
#######################################################################

# @file: config.py
# @author: duyuqi(shenxingwuying@gmail.com)
# @date: 2017-06-28
# @brief: 

import os
import ConfigParse

abs_file_path = os.path.abspath(__file__)
abs_dir_path = os.path.dirname(__file__)


class ConfigureFile(object):
    def __init__(self, file_name):
        self.file_name = "{0}/conf/{1}.conf".format(abs_dir_path, file_name)
        self.conf = ConfigParser.ConfigParser()
        self.conf.read(self.file_name)

    def get_key(self, sector, key):
        return self.conf.get(sector, key)

    def set_key_value(self, sector, key, value):
        self.conf.set(sector, key, value)
        self.flush()

    def flush(self):
        self.conf.write(open(self.file_name, "w"))

class Configure(object):
    def __init__(self, config_file):
        self.config_file = config_file
        self.url_list_file = config_file.get_key("spider", "url_list_file")
        self.output_directory = config_file.get_key("spider", "output_directory")
        self.max_depth = config_file.get_key("spider", "max_depth")
        self.crawl_interval = config_file.get_key("spider", "crawl_interval")
        self.crawl_timeout = config_file.get_key("spider", "crawl_timeout")
        self.target_url = config_file.get_key("spider", "target_url")
        self.thread_count = config_file.get_key("spider", "thread_count")
    def __str__(self):
        return self.config_file

# vim: set expandtab ts=4 sw=4 sts=4 tw=100: #
