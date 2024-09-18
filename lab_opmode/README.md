# Lab for Demonstrating ECB Encryption Weakness

## Create the runtime environment

`make docker-build`

## Invoke the runtime environment

`make docker-run`

Please note that the current working directory is mapped into `/workdir` in the runtime environment.

The following commands can be used in the runtime environment.

## List formats supported by ImageMagick

`magick -list format`

## Get image information

`magick identify tux.png`

## Convert an image to RGB format

`convert tux.png -interlace plane rgb:tux.raw`

## Encrypt the penguin, and extract encrypted pixels

```
openssl enc -e -aes-128-ecb -pbkdf2 -in tux.raw -out tux.enc
dd if=tux.enc bs=32 skip=1 of=tux.enc.raw
```

## Comvert an encrypted RGB raw image to a PNG

`convert -interlace plane -depth 8 -size 1536x1536 rgb:tux.enc.raw tux.enc.png`
