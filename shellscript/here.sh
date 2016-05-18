#!/bin/sh

#program to output a system information page
#limjh@corelogic.co.kr


TITLE="System Information Report for $HOSTNAME"
CURRENT_TIME=$(date +"%x%r%Z");
TIME_STAMP="Generated $CURRENT_TIME, by $USER"

count=0;
report_title() {
	local count;

echo $TITLE
echo $TIME_STAMP
}

report_uptime() {

	local count;

	cat <<- _EOF_
		$(uptime)
		_EOF_
	return
}

report_title

while [ 1  ]; do
	echo $count
#	report_uptime
	count=$((count+1))
	sleep 3
done

	echo "finished."

