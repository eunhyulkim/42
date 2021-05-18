import sys

def cgi(env):
	content_length = 0
	method = ""
	intra_id = ""
	query_string = [""]
	envp = env.split(' ')

	for i in envp:
		if i.find("REQUEST_METHOD") != -1:
			method = i[15:]
		elif i.find("CONTENT_LENGTH") != -1:
			content_length = int(i[15:])
		elif i.find("QUERY_STRING") != -1:
			query_string = i[13:].split('&')

	if content_length != -1:
		buf = sys.stdin.read(content_length)
	if method != "GET":
		print("Status: 404")
		return
	for j in query_string:
		if j.split('=')[0] == "intra_id":
			intra_id = j.split('=')[1]
			print("Status: 301\r")
			print("Location: http://127.0.0.1:8080/story/" + intra_id + ".html")
			print("")
			return
	