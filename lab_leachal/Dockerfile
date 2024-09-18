FROM alpine:3.20

ENTRYPOINT [ "/sbin/tini", "-g", "--" ]
CMD [ "/entrypoint.sh" ]
EXPOSE 80

COPY entrypoint.sh /
RUN chmod 755 /entrypoint.sh

RUN apk update && apk upgrade && apk add tini \
		nginx php83 php83-fpm php83-opcache php83-gd php83-zip php83-curl php83-mysqli
RUN mkdir -p /run/nginx
