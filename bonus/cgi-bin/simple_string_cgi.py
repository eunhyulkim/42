import sys

def cgi(env):
	content_length = 0
	for i in env.split(' '):
		if (i.find("CONTENT_LENGTH=") != -1):
			tmp = i
			content_length = int(tmp[15:])
	buf = sys.stdin.read(content_length)
	print('Content-Type: text/plain')
	print('')
	print('CGI TEST')
	print(buf.upper())
