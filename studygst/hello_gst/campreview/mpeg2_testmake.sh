gst-launch-1.0 videotestsrc pattern=9 num-buffers=3600 ! video/x-raw,format=I420, width=720, height=480 ! filesink location=sample_m2v.yuv
