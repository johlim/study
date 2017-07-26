gst-launch-1.0 videotestsrc ! 'video/x-raw, format=(string)I420, width=(int)320, height=(int)240' ! nvvidconv ! 'video/x-raw(memory:NVMM), width=(int)320, height=(int)240, format=(string)I420' ! rgbdemux ! fakesink

#gst-launch-1.0 videotestsrc ! 'video/x-raw, format=(string)I420, width=(int)1280, height=(int)720' ! nvvidconv ! 'video/x-raw(memory:NVMM), width=(int)640, height=(int)480' ! omxh264enc ! 'video/x-h264, stream-format=(string)byte-stream' ! h264parse ! qtmux ! fakesink

#gst-launch-1.0 audiotestsrc ! 'audio/x-raw, format=(string)S16LE, layout=(string)interleaved, rate=(int)16000, channels=(int)1' ! voamrwbenc ! qtmux ! filesink location=test.mp4 -e

#gst-launch-1.0 nvcamerasrc fpsRange="30 30" ! 'video/x-raw(memory:NVMM), width=(int)320, height=(int)240, format=(string)I420, framerate=(fraction)30/1' ! tee name=src1 ! queue ! nvivafilter cuda-process=true customer-lib-name="libnvsample_cudaprocess.so" !  'video/x-raw(memory:NVMM), format=(string)NV12' ! nvoverlaysink src1. ! rgbdemux frametype=TRUE ! tee name=src2 ! queue ! vgaratio ! fakesink src2. ! queue ! vgagoldfilter ! fakesink src2. ! queue ! vgahorizontaledge ! fakesink  src2. ! queue ! vgathreshold ! fakesink


#gst-launch-1.0 nvcamerasrc fpsRange="30 30" ! 'video/x-raw(memory:NVMM), width=(int)320, height=(int)240, format=(string)I420, framerate=(fraction)30/1' ! tee name=src2 ! queue ! nvivafilter cuda-process=true customer-lib-name="libnvsample_cudaprocess.so" !  'video/x-raw(memory:NVMM), format=(string)NV12' ! nvoverlaysink

#gst-launch-1.0 videotestsrc ! tee name=src2 ! queue ! vgagoldfilter ! fakesink src2. ! queue ! vgathreshold ! fakesink
