#!/usr/bin/python
# -*- coding:utf-8 -*-
import os
import sys
import time
import win32service
import win32serviceutil
import win32event
import servicemanager

class Daemon:
	execute = [
		'private_server.py',
		'private_api.py 220.95.208.244 8080',
		'private_api.py 10.10.1.12 8080'
	]
	command = 'start python.exe '\
			+ os.path.dirname(os.path.abspath(__file__))\
			+ str('\\')

	def run(self):
		for e in self.execute:
			os.popen(self.command + e, "r")

class ServiceDispatcher(win32serviceutil.ServiceFramework):
	_svc_name_ = 'PrivateServer'
	_svc_display_name_ = 'PrivateServer'

	def __init__(self, args):
		win32serviceutil.ServiceFramework.__init__(self, args)
		self.haltEvent = win32event.CreateEvent(None, 0, 0, None)

	def SvcStop(self):
		self.ReportServiceStatus(win32service.SERVICE_STOP_PENDING)
		win32event.SetEvent(self.haltEvent)
		os.popen('TASKKILL /IM '+str('python.exe')+' /F')

	def SvcDoRun(self):
		servicemanager.LogMsg(servicemanager.EVENTLOG_INFORMATION_TYPE,\
							servicemanager.PYS_SERVICE_STARTED,\
							(self._svc_name_, "")\
		)
		daemon = Daemon()
		daemon.run()
		win32event.WaitForSingleObject(self.haltEvent, win32event.INFINITE)

if __name__ == '__main__':
	win32serviceutil.HandleCommandLine(ServiceDispatcher)
