import sys

def readGeneral(content_length):
	buf = sys.stdin.read(content_length)
	return buf

def readChunked():
	buf = ""
	token = int(sys.stdin.readline(), 16)
	while token != 0:
		buf += sys.stdin.read(token)
		bufchar = sys.stdin.read(1)
		if bufchar != '\n':
			sys.stdin.read(1)
		token = int(sys.stdin.readline(), 16)
	bufchar = sys.stdin.read(1)
	if bufchar != '\n':
		sys.stdin.read(1)
	return buf

def cgi(env):
	content_length = 0
	method = ""
	intra_id = ""
	query_string = [""]
	envp = env.split(' ')
	body = ""
	for i in envp:
		if i.find("CONTENT_LENGTH") != -1:
			content_length = int(i[15:])

	print("Status: 200")
	print("Content-Type: text/html")
	print("")
	if content_length != -1:
		body = readGeneral(content_length)
	else:
		body = readChunked()
	querys = body.split('&')
	intra_id = ""
	introduce = ""
	nick = ""
	guild = ""
	for query in querys:
		tokens = query.split('=')
		if tokens[0] == "intra_id":
			intra_id = tokens[1]
		elif tokens[0] == "introduce":
			introduce = tokens[1]
		elif tokens[0] == "nick":
			nick = tokens[1]
		elif tokens[0] == "guild":
			guild = tokens[1]
	f = open("/Users/gim-eunhyul/42seoul/subject/webserv/bonus/HelloService/story/template.html", "rt")
	string = f.read()
	string = string.replace("#ID", intra_id)
	string = string.replace("#DES", introduce)
	string = string.replace("#NICK", nick)
	string = string.replace("#GUILD", guild)
	w = open("/Users/gim-eunhyul/42seoul/subject/webserv/bonus/HelloService/story/" + intra_id + ".html", "wt")
	w.write(string)
	print(string)
