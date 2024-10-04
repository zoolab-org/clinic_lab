#!/bin/sh

if [ -e ./ca ]; then
	echo 'Directory ./ca already exists. Are you sure?'
	exit 1
fi

mkdir ./ca
cd ./ca

# setup CA working directory
mkdir -p ./demoCA/newcerts
touch ./demoCA/index.txt
echo 00 > ./demoCA/serial

# setup CA
openssl req -x509 -newkey rsa:4096 -sha256 -nodes -days 3650 \
	-keyout zooCA_key.pem -out zooCA_cert.pem \
	-subj "/C=TW/ST=Hsinchu/L=Hsinchu/O=zoo.ORG/OU=CA/CN=zoo Root CA"

# generate server key and signing request
openssl genrsa -out server_key.pem 2048
openssl req -new -key server_key.pem -out server_key.csr -sha256 \
	-subj "/C=TW/ST=Hsinchu/L=Hsinchu/O=zoo.ORG/OU=WebServer/CN=zoo.org"

# sign the signing request
openssl ca -batch -in server_key.csr -out server_cert.pem \
	-md sha256 -cert zooCA_cert.pem -keyfile zooCA_key.pem

# merge server key and certificate
cat server_key.pem server_cert.pem > server.pem

