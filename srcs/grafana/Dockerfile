FROM alpine:latest

# We install packages
RUN apk update && apk add --no-cache --upgrade bash \
&& apk add --no-cache --repository=http://dl-cdn.alpinelinux.org/alpine/edge/main libc6-compat
RUN wget https://dl.grafana.com/oss/release/grafana-6.7.2.linux-amd64.tar.gz \
&& tar -zxvf grafana-6.7.2.linux-amd64.tar.gz && rm -rf grafana-6.7.2.linux-amd64.tar.gz

# We copy all data: users, dashboards, data sources...
COPY ./grafana.db ./grafana-6.7.2/data/
COPY entrypoint /entrypoint

#Here we go
EXPOSE 3000
ENTRYPOINT sh /entrypoint
