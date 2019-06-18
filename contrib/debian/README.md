
Debian
====================
This directory contains files used to package bitcoinpayd/bitcoinpay-qt
for Debian-based Linux systems. If you compile bitcoinpayd/bitcoinpay-qt yourself, there are some useful files here.

## bitcoinpay: URI support ##


bitcoinpay-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install bitcoinpay-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your bitcoinpayqt binary to `/usr/bin`
and the `../../share/pixmaps/bitcoinpay128.png` to `/usr/share/pixmaps`

bitcoinpay-qt.protocol (KDE)

