#!/usr/bin/python
#encoding=utf-8
# -*- coding: utf-8 -*-

# Copyright (c) 2017 The Didi Corporation and The spatial_castle Authors.
# All rights reserved. Use of this source code should be governed
# by the corporation. See the AUTHORS file for names of authors.
# Author: zhanglonghanks Email: taihejin@whu.edu.cn Date: 2017-09-23

import sys
import getopt
import datetime

def Usage():
  print "usage:"
  print "  -h show this help"
  print "  -b bins number"

def Probability(b, k):
  pr = 1.0
  for i in range(2, k + 1):
    pr *= (b - i + 2) * 1.0 / b
  pr *= (k - 1) * 1.0 / b
  return pr

# 箱子的数量
bins=5
opts, args = getopt.getopt(sys.argv[1:], "hb:")
for op, value in opts:
  if op == "-b":
    bins=int(value)
  else:
    Usage();
    sys.exit(1);

# 投球的次数
tosses= bins + 1
print bins, tosses

expect = 0.0
for k in range(2, tosses + 1):
  pr = Probability(bins, k)
  expect += k * pr
  print "epect:", k, pr, expect

# stop verify
sys.exit(0);

