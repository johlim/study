#!/usr/bin/perl
use strict;
my $data;
my $linenumber=-1;
my @cline;
my $dur;
my $string;
while (<>) {

next unless $_ =~ m/WRITE|CMD/;
#next unless $_ =~ m/Device Driver Init Done!!/;
#next unless $_ =~ m/\-BboxAppGetRecFileName2/;
#print $linenumber , $_;
	$linenumber = $linenumber+1;
	@cline = split / /, $_;
	if ( $cline[6] > 10 )
	{
	print "**",$cline[2],"\t", $cline[3], " ",$cline[4], "\t,", $cline[6],"\t,", $cline[16];
	}
	elsif (  $cline[7] > 200 )
	{
	print "*",$cline[2],"\t", $cline[3], " ",$cline[4], "\t,", $cline[6],"\t,", $cline[16];
	}
	else
	{
	print $cline[2],"\t", $cline[3], " ",$cline[4], "\t,", $cline[6],"\t,", $cline[16];
	}
#print $1, "\n";

}

__DATA__
EVENT_TYPE_INVALID = -1
, EVENT_TYPE_BUTTON_CAPTURE=0
, EVENT_TYPE_BUTTON_EVENT=1
, EVENT_TYPE_G_SENSOR_LEVEL1=2
, EVENT_TYPE_G_SENSOR_LEVEL2=3
, EVENT_TYPE_POWER_FAIL=4
, EVENT_TYPE_ADC_EVENT=5

, EVENT_TYPE_SDC_ENABLED=6
, EVENT_TYPE_SDC_DISABLED=7
, EVENT_TYPE_GPS_RCV

, EVENT_TYPE_SOUND_PLAY // pcm or mp3

///< message from/to file manager
, EVENT_TYPE_BLACKBOX_DELETE_FILE
, EVENT_TYPE_BLACKBOX_SCAN_FILE
, EVENT_TYPE_BLACKBOX_RESCAN_FILE
, EVENT_TYPE_BLACKBOX_SCAN_FILE_DONE

///< messages from blackbox callback function
, EVENT_TYPE_BLACKBOX_APP_START
, EVENT_TYPE_BLACKBOX_APP_STOP
, EVENT_TYPE_BLACKBOX_APP_CAPTURE_DONE
, EVENT_TYPE_BLACKBOX_APP_SAVE_DONE
, EVENT_TYPE_BLACKBOX_INFINITE_RECORDING_DONE
, EVENT_TYPE_BLACKBOX_EVENT_RECORDING_DONE
, EVENT_TYPE_BLACKBOX_DELETE_JPEG_FILE
, EVENT_TYPE_BLACKBOX_MD_MOTION
, EVENT_TYPE_BLACKBOX_MD_NOMOTION
, EVENT_TYPE_BLACKBOX_INTERNAL_ERR

///< messages from player callback function
, EVENT_TYPE_PLAYER_APP_START
, EVENT_TYPE_PLAYER_APP_STOP
, EVENT_TYPE_PLAYER_APP_RESUME
, EVENT_TYPE_PLAYER_APP_PAUSE
, EVENT_TYPE_PLAYER_APP_PAUSED
, EVENT_TYPE_PLAYER_APP_STATUS
///< messages from camcorder callback function
, EVENT_TYPE_CAMCORDER_APP_START
, EVENT_TYPE_CAMCORDER_APP_STOP
, EVENT_TYPE_CAMCORDER_APP_CAPTURE_DONE
, EVENT_TYPE_CAMCORDER_APP_SAVE_DONE
, EVENT_TYPE_CAMCORDER_APP_TIMER_STOP
, EVENT_TYPE_CAMCORDER_APP_STATUS
///< messages from imageviewer callback function
, EVENT_TYPE_IMAGEVIEWER_APP_START
, EVENT_TYPE_IMAGEVIEWER_APP_STOP
, EVENT_TYPE_IMAGEVIEWER_APP_STATUS
///< usb messages
, EVENT_TYPE_USB_REMOVE
, EVENT_TYPE_USB_ATTACH
///< message from user application
, EVENT_TYPE_TVOUT_CONNECTED
, EVENT_TYPE_TVOUT_REMOVED

, EVENT_TYPE_MEDIA_WARNING
, EVENT_TYPE_MEDIA_ERROR
, EVENT_TYPE_BLACKBOX_LIVEVIEW_SEL
, EVENT_TYPE_AV_CHECK
, EVENT_TYPE_EXTCAM_DETECT
, EVENT_TYPE_SENSOR_LIGHT_CHANGE
, EVENT_TYPE_TP_TOUCH
, EVENT_TYPE_MAX