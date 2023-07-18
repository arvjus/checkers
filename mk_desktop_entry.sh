#!/bin/sh

for sz in 16 20 22 24 32 36 40 48 64 72 96 128 192 256; do
convert assets/checkers-big.png -resize ${sz}x${sz} /usr/share/icons/hicolor/${sz}x${sz}/apps/checkers.png
done
cp assets/checkers.png /usr/share/pixmaps 

cat <<EOF >/usr/share/applications/checkers.desktop
[Desktop Entry]
Name=Checkers
Comment=American Checkers / English Draughts
Exec=checkers
Icon=checkers
Terminal=false
Type=Application
MimeType=text/plain;
Categories=GTK;Game;
Keywords=checkers;
InitialPreference=6;
EOF
