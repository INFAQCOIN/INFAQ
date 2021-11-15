
Debian
====================
This directory contains files used to package infaqcoind/infaqcoin-qt
for Debian-based Linux systems. If you compile infaqcoind/infaqcoin-qt yourself, there are some useful files here.

## infaqcoin: URI support ##


infaqcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install infaqcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your infaqcoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/infaqcoin128.png` to `/usr/share/pixmaps`

infaqcoin-qt.protocol (KDE)

