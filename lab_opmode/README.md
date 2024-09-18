
## List formats supports by ImageMagick

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

