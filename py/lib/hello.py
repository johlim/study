from configparser import ConfigParser
config = ConfigParser()
config.read('config.ini')
config.sections()
config.options('USER_A')
'USER_A' in config
config.get('USER_A','group')
config.get('USER_A','limit')

