env = "CONTENT_LENGTH=14 HELLO=24 ABC=DE"
content_length = 0
envp = env.split(' ')
method = envp["REQUEST_METHOD"]
if envp["CONTENT_LENGTH"] != -1:
    tmp = envp["CONTENT_LENGTH"]
    content_length = int(tmp[15:])
    buf = sys.stdin.read(content_length)
    print('Content-Type: text/plain')
    print('')
    print('CGI TEST')
    print('hoho')
    print(method)
    print(buf.upper())
