const unsigned char ui_script_buf[] = "\
<main>\
	<state id='0' name='LIVEVIEW' x='0' y='0' w='400' h='240' bg='#FF00FF'>\
		<button id='0' x='0' y='186' w='86' h='54' img='120' img_f='121'/>\
		<text id='1' x='78' y='218' w='310' h='15' font='1' color='#FFFFFF' align='LM'/>\
		<text id='2' x='5' y='5' w='195' h='15' font='1' color='#FFFFFF' align='LM'/>\
		<text id='3' x='210' y='5' w='185' h='15' font='1' color='#FFFFFF' align='RM'/>\
	</state>\
\
	<state id='1' name='MAINMENU' x='0' y='0' w='400' h='240' bg='1'>\
		<button id='0' x='31' y='22' w='80' h='80' img='16' img_f='17'/>\
		<button id='1' x='160' y='22' w='80' h='80' img='18' img_f='19'/>\
		<button id='2' x='289' y='22' w='80' h='80' img='20' img_f='21'/>\
		<button id='3' x='31' y='129' w='80' h='80' img='22' img_f='23'/>\
		<button id='4' x='160' y='129' w='80' h='80' img='24' img_f='25'/>\
		<button id='5' x='289' y='129' w='80' h='80' img='26' img_f='27'/>\
	</state>\
\
	<state id='2' name='PLAY-FOLDER' x='0' y='0' w='400' h='240' bg='3'>\
		<icon x='20' y='17' w='35' h='30' img='73'/>\
		<button id='0' x='25' y='105' w='80' h='59' img='74' img_f='75'/>\
		<button id='1' x='114' y='105' w='80' h='59' img='76' img_f='77'/>\
		<button id='2' x='205' y='105' w='80' h='59' img='78' img_f='79'/>\
		<button id='3' x='294' y='105' w='80' h='59' img='80' img_f='81'/>\
		<button id='4' x='300' y='13' w='86' h='34' img='5' img_f='6'/>\
	</state>\
\
	<state id='3' name='PLAY-BROWSER' x='0' y='0' w='400' h='240' bg='82'>\
		<icon x='20' y='17' w='35' h='30' img='73'/>\
		<list id='0' x='19' y='59' w='324' h='165'/>\
		<button id='1' x='353' y='61' w='29' h='26' img='11' img_f='12'/>\
		<button id='2' x='353' y='194' w='29' h='26' img='9' img_f='10'/>\
		<button id='3' x='300' y='13' w='86' h='34' img='5' img_f='6'/>\
		<text id='10' x='170' y='20' w='60' h='20' font='2' color='#FFFFFF' align='RM'/>\
		<text id='11' x='230' y='20' w='60' h='20' font='2' color='#FFFFFF' align='LM'/>\
		<text id='12' x='35' y='100' w='300' h='40' font='2' color='#FFFFFF' align='CM'/>\
	</state>\
\
	<state id='4' name='PLAY-SCREEN' x='0' y='0' w='400' h='240' bg='83'>\
		<button id='0' x='15' y='191' w='66' h='39' img='84' img_f='85'/>\
		<button id='1' x='81' y='191' w='64' h='39' img='86' img_f='87'/>\
		<button id='2' x='145' y='191' w='64' h='39' img='88' img_f='89'/>\
		<button id='3' x='209' y='191' w='66' h='39' img='92' img_f='93'/>\
		<button id='4' x='294' y='191' w='46' h='39' img='94' img_f='95'/>\
		<button id='5' x='340' y='191' w='46' h='39' img='96' img_f='97'/>\
		<button id='6' x='314' y='9' w='77' h='40' text ='1' font='1' img='98' img_f='99'/>\
		<text id='7' x='100' y='150' w='280' h='30' font='15' color='#FFFF00' align='CM'/>\
		<text id='8' x='10' y='6' w='190' h='30' font='1' color='#FFFFFF' align='LM'/>\
		<text id='9' x='210' y='6' w='90' h='30' font='1' color='#FFFFFF' align='LM'/>\
	</state>\
\
	<state id='5' name='SETUP-MAIN' x='0' y='0' w='400' h='240' bg='2'>\
		<button id='0' x='31' y='51' w='80' h='70' img='28' img_f='29'/>\
		<button id='1' x='160' y='51' w='80' h='70' img='30' img_f='31'/>\
		<button id='2' x='289' y='51' w='80' h='70' img='32' img_f='33'/>\
		<button id='3' x='31' y='145' w='80' h='70' img='34' img_f='35'/>\
		<button id='4' x='160' y='145' w='80' h='70' img='36' img_f='37'/>\
		<button id='5' x='289' y='145' w='80' h='70' img='38' img_f='39'/>\
		<button id='6' x='300' y='13' w='86' h='34' img='40' img_f='41'/>\
	</state>\
\
	<state id='6' name='SETUP-SENSOR' x='0' y='0' w='400' h='240' bg='3'>\
		<icon x='20' y='17' w='35' h='30' img='42'/>\
		<icon x='24' y='81' w='124' h='21' img='43'/>\
		<radio id='0' gr='0' x='135' y='72' w='83' h='38' img='44' img_f='45'/>\
		<radio id='1' gr='0' x='218' y='72' w='83' h='38' img='46' img_f='47'/>\
		<radio id='2' gr='0' x='298' y='72' w='83' h='38' img='48' img_f='49'/>\
		<radio id='5' gr='1' x='135' y='120' w='83' h='38' img='44' img_f='45'/>\
		<radio id='4' gr='1' x='218' y='120' w='83' h='38' img='46' img_f='47'/>\
		<radio id='3' gr='1' x='298' y='120' w='83' h='38' img='48' img_f='49'/>\
		<button id='8' x='129' y='181' w='143' h='44' img='7' img_f='8'/>\
		<button id='9' x='300' y='13' w='86' h='34' img='5' img_f='6'/>\
	</state>\
\
	<state id='7' name='SETUP-TIME' x='0' y='0' w='400' h='240' bg='51'>\
		<icon x='20' y='17' w='35' h='30' img='50'/>\
		<button id='0' x='36' y='66' w='29' h='26' img='9' img_f='10'/>\
		<button id='1' x='162' y='66' w='29' h='26' img='11' img_f='12'/>\
		<button id='2' x='209' y='66' w='29' h='26' img='9' img_f='10'/>\
		<button id='3' x='335' y='66' w='29' h='26' img='11' img_f='12'/>\
		<button id='4' x='36' y='105' w='29' h='26' img='9' img_f='10'/>\
		<button id='5' x='162' y='105' w='29' h='26' img='11' img_f='12'/>\
		<button id='6' x='209' y='105' w='29' h='26' img='9' img_f='10'/>\
		<button id='7' x='335' y='105' w='29' h='26' img='11' img_f='12'/>\
		<button id='8' x='36' y='144' w='29' h='26' img='9' img_f='10'/>\
		<button id='9' x='162' y='144' w='29' h='26' img='11' img_f='12'/>\
		<button id='10' x='209' y='144' w='29' h='26' img='9' img_f='10'/>\
		<button id='11' x='335' y='144' w='29' h='26' img='11' img_f='12'/>\
		<button id='12' x='129' y='181' w='143' h='44' img='7' img_f='8'/>\
		<button id='13' x='300' y='13' w='86' h='34' img='5' img_f='6'/>\
		<text id='20' x='80' y='64' w='70' h='30' font='4' color='#FFFFFF' align='CM'/>\
		<text id='21' x='260' y='64' w='50' h='30' font='4' color='#FFFFFF' align='CM'/>\
		<text id='22' x='90' y='102' w='50' h='30' font='4' color='#FFFFFF' align='CM'/>\
		<text id='23' x='260' y='102' w='50' h='30' font='4' color='#FFFFFF' align='CM'/>\
		<text id='24' x='90' y='141' w='50' h='30' font='4' color='#FFFFFF' align='CM'/>\
		<text id='25' x='260' y='141' w='50' h='30' font='4' color='#FFFFFF' align='CM'/>\
	</state>\
\
	<state id='8' name='SETUP-VOICE' x='0' y='0' w='400' h='240' bg='3'>\
		<icon x='20' y='17' w='35' h='30' img='52'/>\
		<icon x='24' y='80' w='21' h='69' img='53'/>\
		<radio id='1' gr='0' x='135' y='72' w='123' h='38' img='54' img_f='55'/>\
		<radio id='0' gr='0' x='258' y='72' w='126' h='38' img='56' img_f='57'/>\
		<radio id='3' gr='1' x='135' y='120' w='123' h='38' img='54' img_f='55'/>\
		<radio id='2' gr='1' x='258' y='120' w='126' h='38' img='56' img_f='57'/>\
		<button id='4' x='129' y='181' w='143' h='44' img='7' img_f='8'/>\
		<button id='5' x='300' y='13' w='86' h='34' img='5' img_f='6'/>\
	</state>\
\
	<state id='9' name='SETUP-ETC' x='0' y='0' w='400' h='240' bg='60'>\
		<icon x='20' y='17' w='35' h='30' img='58'/>\
		<icon x='24' y='81' w='21' h='69' img='59'/>\
		<button id='0' x='159' y='78' w='29' h='26' img='9' img_f='10'/>\
		<button id='1' x='343' y='78' w='29' h='26' img='11' img_f='12'/>\
		<button id='2' x='159' y='126' w='29' h='26' img='9' img_f='10'/>\
		<button id='3' x='343' y='126' w='29' h='26' img='11' img_f='12'/>\
		<button id='7' x='37' y='183' w='140' h='38' img='63' img_f='64'/>\
		<button id='6' x='213' y='181' w='143' h='44' img='7' img_f='8'/>\
		<button id='8' x='300' y='13' w='86' h='34' img='5' img_f='6'/>\
		<combo id='10' x='200' y='75' w='130' h='30' text='0' font='3' color='#FFFFFF' align='CM'/>\
		<combo id='11' x='200' y='122' w='130' h='30' text='0' font='3' color='#FFFFFF' align='CM'/>\
	</state>\
\
	<state id='10' name='SETUP-FORMAT-CONFIRM' x='0' y='0' w='400' h='240' bg='4'>\
		<icon x='20' y='17' w='35' h='30' img='65'/>\
		<button id='0' x='54' y='181' w='143' h='44' img='66' img_f='67'/>\
		<button id='1' x='202' y='181' w='143' h='44' img='68' img_f='69'/>\
	</state>\
\
	<state id='11' name='SETUP-FORMATTING' x='0' y='0' w='400' h='240' bg='4'>\
		<icon x='20' y='17' w='35' h='30' img='65'/>\
		<progress x='41' y='184' w='10' h='10' img='14' img_f='15'/>\
	</state>\
\
	<state id='12' name='SETUP-VERSION' x='0' y='0' w='400' h='240' bg='3'>\
		<icon x='20' y='17' w='35' h='30' img='72'/>\
		<button id='0' x='300' y='13' w='86' h='34' img='5' img_f='6'/>\
	</state>\
\
	<state id='13' name='FIRMWARE-CONFIRM' x='0' y='0' w='400' h='240' bg='4'>\
		<icon x='20' y='17' w='35' h='30' img='114'/>\
		<icon x='159' y='63' w='83' h='85' img='115'/>\
		<button id='0' x='54' y='181' w='174' h='143' img='116' img_f='117'/>\
		<button id='1' x='202' y='181' w='174' h='143' img='68' img_f='69'/>\
	</state>\
\
	<state id='14' name='FIRMWARE-FAIL' x='0' y='0' w='400' h='240' bg='4'>\
		<icon x='20' y='17' w='35' h='30' img='118'/>\
		<icon x='159' y='63' w='83' h='85' img='119'/>\
	</state>\
\
	<state id='15' name='FIRMWARE-UPDATING' x='0' y='0' w='400' h='240' bg='4'>\
		<icon x='20' y='17' w='35' h='30' img='114'/>\
		<progress x='41' y='184' w='10' h='10' img='14' img_f='15'/>\
	</state>\
\
	<state id='16' name='POPUP-PARK-ENTER' x='0' y='0' w='400' h='240' bg='4'>\
		<icon x='20' y='17' w='35' h='30' img='109'/>\
		<icon x='159' y='63' w='83' h='85' img='110'/>\
	</state>\
\
	<state id='17' name='POPUP-PARK-LEAVE' x='0' y='0' w='400' h='240' bg='4'>\
		<icon x='20' y='17' w='35' h='30' img='111'/>\
		<icon x='159' y='63' w='83' h='85' img='112'/>\
	</state>\
	\
	<state id='18' name='POPUP-PARK-EVENT' x='0' y='0' w='400' h='240' bg='4'>\
		<icon x='20' y='17' w='35' h='30' img='100'/>\
		<icon x='159' y='63' w='83' h='85' img='113'/>\
	</state>\
	\
	<state id='19' name='POPUP-REC-INIT' x='0' y='0' w='400' h='240' bg='4'>\
		<icon x='20' y='17' w='35' h='30' img='100'/>\
		<icon x='159' y='63' w='83' h='85' img='101'/>\
	</state>\
\
	<state id='20' name='POPUP-REC-STOP' x='0' y='0' w='400' h='240' bg='4'>\
		<icon x='20' y='17' w='35' h='30' img='107'/>\
		<icon x='159' y='63' w='83' h='85' img='108'/>\
	</state>\
\
	<state id='21' name='POPUP-REC-RESUME' x='0' y='0' w='400' h='240' bg='4'>\
		<icon x='20' y='17' w='35' h='30' img='102'/>\
		<icon x='159' y='63' w='83' h='85' img='103'/>\
	</state>\
\
	<state id='22' name='POPUP-REARCAM-ERR' x='0' y='0' w='400' h='240' bg='4'>\
		<icon x='20' y='17' w='35' h='30' img='105'/>\
		<icon x='159' y='63' w='83' h='85' img='106'/>\
	</state>\
\
	<state id='23' name='POPUP-SD-CHECK' x='0' y='0' w='400' h='240' bg='4'>\
		<icon x='20' y='17' w='35' h='30' img='65'/>\
		<icon x='159' y='63' w='83' h='85' img='104'/>\
	</state>\
\
	<state id='24' name='POPUP-SD-ERROR' x='0' y='0' w='400' h='240' bg='4'>\
		<icon x='20' y='17' w='35' h='30' img='65'/>\
		<icon x='159' y='63' w='83' h='85' img='104'/>\
	</state>\
\
	<state id='25' name='POPUP-NO-GPS' x='0' y='0' w='FIT' h='FIT' bg='102'>\
		<icon x='10' y='10' w='94' h='20' img='141'/>\
		<icon x='154' y='82' w='172' h='18' img='136'/>\
		<icon x='200' y='140' w='80' h='62' img='103'/>\
		<button id='0' x='364' y='0' w='116' h='38' img='123' img_f='124'/>\
	</state>\
\
	<state id='26' name='POPUP-NO-LDWS-DATA' x='0' y='0' w='FIT' h='FIT' bg='102'>\
		<icon x='110' y='80' w='256' h='20' img='135'/>\
		<icon x='200' y='140' w='80' h='62' img='103'/>\
	</state>\
\
	<state id='27' name='LDWS-SELECT-CAR' x='0' y='0' w='FIT' h='FIT' bg='102'>\
		<icon x='10' y='10' w='94' h='20' img='141'/>\
		<icon x='138' y='74' w='204' h='18' img='127'/>\
		<button id='1' x='100' y='124' w='130' h='170' img='128' img_f='129'/>\
		<button id='2' x='251' y='124' w='130' h='170' img='130' img_f='131'/>\
		<button id='3' x='364' y='0' w='116' h='38' img='123' img_f='124'/>\
	</state>\
\
	<state id='28' name='LDWS-SETUP' x='0' y='0' w='FIT' h='FIT' bg='#FF00FF'>\
		<icon x='0' y='0' w='480' h='128' img='132'/>\
		<button id='0' x='390' y='44' w='84' h='40' img='133' img_f='134'/>\
	</state>\
\
	<state id='29' name='CALIBRATION' x='0' y='0' w='400' h='240' bg='#0'>\
		<button id='0' x='5' y='190' w='80' h='45' text='0' font='3'/>\
		<button id='1' x='160' y='190' w='80' h='45' text='1' font='3'/>\
		<button id='2' x='315' y='190' w='80' h='45' text='10' font='3'/>\
	</state>\
\
	<state id='30' name='BOOT' x='0' y='0' w='FIT' h='FIT' bg='#0'/>\
	<state id='31' name='MODE_CHANGE' x='0' y='0' w='FIT' h='FIT' bg='#0'/>	\
	<state id='32' name='TEST' x='0' y='0' w='FIT' h='FIT' bg='#0'/>\
	<state id='33' name='TESTADC' x='0' y='0' w='FIT' h='FIT' bg='#0'/>\
	\
	<state id='34' name='TESTLCD' x='0' y='0' w='FIT' h='FIT' bg='#0'>\
		<text id='1' x='160' y='190' w='120' h='30' font='3' color='#FFFFFF' align='LM'/>\
	</state>\
	\
	<state id='35' name='POPUP-TIME-MENU' x='0' y='0' w='400' h='240' bg='4'>\
		<icon x='20' y='17' w='35' h='30' img='100'/>\
		<icon x='159' y='63' w='83' h='85' img='101'/>\
	</state>\
</main>\
";