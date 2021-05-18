FROM alpine
ARG IP

# We install packages
RUN apk update && apk add wget && mkdir /www \
&& apk add php7 php7-fpm php7-opcache php7-gd php7-mysqli php7-zlib php7-curl php7-mbstring php7-json php7-session

RUN apk add mysql-client

# We get the last version of Wordpress and uncompress it
COPY ./latest.tar.gz ./latest.tar.gz
RUN tar -xvf latest.tar.gz \
&& mv www/* /www \
&& rm -rf /var/cache/apk/*

# Here we go
COPY wordpress_dump-target.sql /wordpress-dump.sql
COPY entrypoint /entrypoint

EXPOSE 5050
ENTRYPOINT sh /entrypoint
