# Commands for creating a self-signed certificate

## Requirement

- Create and switch to a writable directory, e.g., your `$HOME/ca` directory

  ```
  mkdir $HOME/ca
  cd $HOME/ca
  ```

  If you are unhappy with the experiments, you can simply delete everything in the `$HOME/ca` directory.

- Assume we plan to place CA-related files in `./demoCA` directory. Please run the commands to create the directory:

  ```
  mkdir -p ./demoCA/newcerts
  touch ./demoCA/index.txt
  echo 00 > ./demoCA/serial
  ```

- If you plan to use a different directory name other than `./demoCA`, modify the relevant settings in the system `/etc/ssl/openssl.cnf`. We recommend you to make a copy of that file and then modify your local copy. Once you are done, you can use the `-config` parameter to choose using your customized configuration file.

## Create the CA

- The command used to create the CA is:

  `openssl req -x509 -newkey rsa:4096 -sha256 -nodes -days 3650 -keyout zooCA_key.pem -out zooCA_cert.pem -subj "/C=TW/ST=Hsinchu/L=Hsinchu/O=zoo.ORG/OU=CA/CN=zoo Root CA"`

- Remove the `-nodes` parameter if you plan to secure your CA certificate with a password.

## Create the server key

- The command used to create the server key is:

  `openssl genrsa -out server_key.pem 2048`

## Create the signing request

- The command used to generate the signing request is:

  `openssl req -new -key server_key.pem -out server_key.csr -sha256 -subj "/C=TW/ST=Hsinchu/L=Hsinchu/O=zoo.ORG/OU=WebServer/CN=zoo.org"`

## Sign the server key

- The command used to sign the server key is:

  `openssl ca -in server_key.csr -out server_cert.pem -md sha256 -cert zooCA_cert.pem -keyfile zooCA_key.pem`

  If everything works well, the signed server certificate will be placed in `./zooCA/newcerts/00.pem`, where `00` is the serial number (in hexadecimal) of the signed certificate.

- You may merge the server key and certificate into a single file.

  `cat server_key.pem server_cert.pem > server.pem`

## Test the server certificate

- You may test the signed certificate using `openssl`:

  `openssl s_server -cert server.pem -accept 8443 -www`

  and then access the server using `curl`

  `openssl s_client -connect localhost:8443`

