#!/usr/bin/python

from nanomsg import *
import _nanomsg_ctypes as nnc

with Socket(SUB) as s:
	s.connect("ipc:///tmp/testnano")
	s.set_string_option(SUB, SUB_SUBSCRIBE, '')
	frameSize = 324*240*4
	while True:
		nnc.nn_recvmsg(s, [4, frameSize])
		# print "frameNo "+ str(frameS) + " and frame data (" + len(frame) + " bytes) received"
