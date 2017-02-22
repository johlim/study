echo "export PKG_CONFIG_PATH=/home/`whoami`/GST/lib/pkgconfig:/usr/lib/pkgconfig:/usr/local/lib/pkgconfig:$PKG_CONFIG_PATH" >> ~/.profile
source ~/.profile
ROOT=`pwd`
cd orc-0.4.26/
./configure --prefix=/home/`whoami`/GST
cd $ROOT
cd gst-plugins-base-1.10.0
./configure --prefix=/home/`whoami`/GST
cd $ROOT
cd gst-plugins-good-1.10.0
./configure --prefix=/home/`whoami`/GST
cd $ROOT
cd gst-plugins-ugly-1.10.0
./configure --prefix=/home/`whoami`/GST --disable-realmedia
cd $ROOT
cd gst-omx-1.10.0
./configure --prefix=/home/`whoami`/GST --with-omx-header-path=/opt/vc/include/IL --with-omx-target=generic
cd $ROOT
cd gst-rtsp-server-1.10.0
./configure --prefix=/home/`whoami`/GST
#./configure --prefix=/home/limjh/GST --enable-gtk-doc  --enable-docbook
