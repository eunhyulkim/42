import sys

# def cgi_test(env):
print('Content-Type: text/plain')
print('')
env = "AUTH_TYPE= CONTENT_LENGTH=8 CONTENT_TYPE=text/plain GATEWAY_INTERFACE=1.1 PATH_INFO=/cgi.py PATH_TRANSLATED=/Users/jujeong/webserv/bonus/YoupiBanane QUERY_STRING= REMOTE_ADDR=127.0.0.1 REQUEST_METHOD=POST REQUEST_URI=/cgi.py SCRIPT_NAME=/Users/jujeong/webserv/bonus/YoupiBanane/cgi.py SERVER_NAME=default SERVER_PORT=8081 SERVER_PROTOCOL=HTTP/1.1 SERVER_SOFTWARE=ft_nginx/0.5"
# sys.stderr.write(env)
for i in env.split(' '):
	if (i.find("CONTENT_LENGTH")):
		tmp = i
print(tmp)
# print(env[env.find("CONTENT_LENGTH")])
# buf = sys.stdin.read(10)
# print(buf.upper())
# print('TEST')
