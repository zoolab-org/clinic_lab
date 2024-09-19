# Password Crack Lab

## Create the runtime environment

`make docker-build`

## Invoke the runtime environment

`make docker-run`

Please note that (1) the default user in the runtime is `root` - use it with care!, and (2) the `./samples` directory is mapped into `/workdir` in the runtime environment.

The runtime docker instance ***will be deleted automatically*** after you quit from the runtime. If you want to preserve files generated in the runtime, please put them in the `/workdir` directory.

## Sample commands to generate password-protected sample files

- ZIP archive: `zip -ur9e sample.zip files ...`
- SSH RSA key: `ssh-keygen -f ./id_rsa -t rsa`

## Procedures

1. Unpack `rockyou` dictionary file by running the `gzip -d /usr/share/wordlists/rockyou.txt.gz` command.

2. Convert a password-protected file to a compatible format that can be processed by *john*

   ```
   zip2john sample.zip > /tmp/sample.txt
   ssh2john id_rsa > /tmp/sample.txt
   unshadow ./passwd.txt ./shadow.txt > /tmp/sample.txt
   ```

3. Crack the password using *john* (Examples)

   ```
   john --rules --wordlist=/usr/share/wordlists/rockyou.txt /tmp/sample.txt
   john --incremental=digits ./sample.txt
   ```

4. Relevant commands

   Many other format conversion tools are available at `/usr/bin/*2john` and `/usr/sbin/*2john*`.

   You may also have a look at the introduction offered by [Kali Linux](https://www.kali.org/tools/john/).

