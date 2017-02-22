cd ~/

echo "export PATH=/home/`whoami`/GST/bin:$PATH" >> ~/.profile
echo "export LD_LIBRARY_PATH=/home/`whoami`/GST/lib" >> ~/.profile
echo "export GST_PLUGIN_PATH=/home/`whoami`/GST/lib/gstreamer-1.0" >> ~/.profile
source ~/.profile
