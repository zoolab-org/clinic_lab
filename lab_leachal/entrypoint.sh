#!/bin/sh
KEYLEN=$((16 + RANDOM % 16))
dd if=/dev/urandom of=/SECRET bs=1 count=$KEYLEN
PHP=`find /etc -name 'php[0-9]*' -type d | awk -F/ '{print $3}'`
/usr/sbin/php-fpm${PHP#php} --fpm-config /etc/$PHP/php-fpm.conf
exec /usr/sbin/nginx -c /nginx.php.conf -g 'daemon off;'
