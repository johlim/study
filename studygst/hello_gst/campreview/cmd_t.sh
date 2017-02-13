gst-launch-1.0 filesrc location="sample_staticimage.m2v" ! typefind ! queue ! fakesink

#tsdemux name=demux demux. ! queue ! fakesink
#mpeg2dec ! fakesink
#demux. ! ’audio/mpeg’ ! queue ! avdec ! volume volume=5 ! alsasink
