sudo gst-launch-1.0 -e v4l2src ! video/x-raw, format=\(string\)I420, width=320, height=240, framerate=\(fraction\)30/1 ! x264enc ! avimux name=avimux ! filesink location=./test.avi
