
#!/bin/sh

if [ -f ./core_consol ]; then 
	echo "core_test is found"
	chmod a+x ./core_test
	./core_test &
else

	if [ -f ./limjh ]; then
		echo "limjh is found"
	else
	echo "limjh not found"
	fi

fi

