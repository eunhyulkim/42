FROM alpine

RUN apk add --update mysql && rm -f /var/cache/apk/*

#'my.cnf' is real mysql config file name
COPY my.cnf /etc/mysql/my.cnf
COPY entrypoint /entrypoint

RUN mkdir /app

EXPOSE 3306
CMD sh /entrypoint
