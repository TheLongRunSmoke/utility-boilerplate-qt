#!/bin/bash
# Convert svg to ico.
convert icon.svg -density 300 -resize 256x256 -fuzz 10% -transparent white icon-256.png
convert icon.svg -density 300 -resize 192x192 -fuzz 10% -transparent white icon-192.png
convert icon.svg -density 300 -resize 32x32 -fuzz 10% -transparent white icon-32.png
convert icon.svg -density 300 -resize 16x16 -fuzz 10% -transparent white icon-16.png
convert icon-16.png icon-32.png icon-192.png icon-256.png icon.ico
rm icon-16.png icon-32.png icon-192.png icon-256.png