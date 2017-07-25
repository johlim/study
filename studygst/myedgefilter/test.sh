#!/bin/sh

gst-launch-1.0 videotestsrc blocksize=115200 ! video/x-bayer, format=\(string\)rggb , width=320, height=240, framerate=\(fraction\)30/1 ! bayer2rgb ! videoconvert ! fakesink
#gst-launch-1.0 videotestsrc blocksize=115200 ! video/x-raw, format=\(string\)I420 , width=320, height=240, framerate=\(fraction\)30/1 ! myedgefilter ! videoconvert ! ximagesink

