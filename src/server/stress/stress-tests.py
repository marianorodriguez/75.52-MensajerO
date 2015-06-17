#!/usr/bin/env python

import urllib2, json, base64
import threading

def signUpRequest(username):
	serverUrl = "http://localhost:8081/signUp"
	baseData = json.dumps({'username': username, 'password':'1m4p455w0rD___'})
	postData = "package=" + base64.b64encode(baseData)

	response = urllib2.urlopen(serverUrl, postData)

	print base64.b64decode(response.readline())

def main():
	requestThreads = list()
	threadNum = 2000
	print "Creando " + str(threadNum) + " hilos"
	for i in range(0, threadNum):
		username = "test" + str(i)
		thread = threading.Thread(target=signUpRequest, args=(username, ))
		requestThreads.append(thread)
	print "Iniciando hilos"
	for i in range(0, threadNum):
		requestThreads[i].start()
	print "joineando hilos"
	for i in range(0, threadNum):
		requestThreads[i].join()
	print "Terminado"

main()
