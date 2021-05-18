FROM alpine

#UPDATE
RUN apk update
RUN apk upgrade

RUN apk add --update openssh

#INSTALL NGINX
RUN apk add --update nginx

#SSH keys setting
COPY ssh/sshd_config /sshd_config
COPY ssh/id_rsa.pub /authorized_keys
COPY ssh/id_rsa /etc/ssh/ssh_host_rsa_key

#SSL keys setting
COPY ssl/nginx.crt /etc/nginx/ssl/nginx.crt
COPY ssl/nginx.key /etc/nginx/ssl/nginx.key

#Nginx setup
COPY nginx.conf /etc/nginx/nginx.conf
RUN mkdir -p usr/share/nginx
COPY html usr/share/nginx/html

#Entrypoint
COPY entrypoint /entrypoint

ENTRYPOINT sh /entrypoint

EXPOSE 443 80 30022
