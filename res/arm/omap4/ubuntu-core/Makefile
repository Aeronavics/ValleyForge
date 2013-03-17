#	Copyright (C) 2011  Unison Networks Ltd
#
#	This program is free software: you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation, either version 3 of the License, or
#	(at your option) any later version.
#
#	This program is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with this program.  If not, see <http://www.gnu.org/licenses/>.

#
# MAKEFILE FOR CREATING UBUNTU IMAGES FOR ARM TARGETS.
#
#	Author:		Edwin Hayes
#
#	Created:	3rd Jan 2013
#

# NOTE - This is basically a copy of the method described at www.omappedia.org/wiki/OMAP_Ubuntu_Core.

# VARIABLES.

IMAGE_PATH=BUILD_INSERTS_IMAGE_PATH_HERE

FILESYSTEM=${IMAGE_PATH}/filesystem.tar.gz
MLO=${IMAGE_PATH}/MLO
UBOOT=${IMAGE_PATH}/u-boot.img
UIMAGE=${IMAGE_PATH}/uImage
BSCRIPT=${IMAGE_PATH}/boot.scr

# PSEUDO TARGETS.

.PHONY: all filesystem bootloader download_files

all : filesystem bootloader

filesystem : ${FILESYSTEM}

bootloader : ${MLO} ${UBOOT} ${UIMAGE} ${BSCRIPT}

# Download recent copies of all the relevant files from the Ubuntu servers.
download_files :
	@echo "******** Fetching latest copy of files from server. ********"
	wget -N "http://cdimage.ubuntu.com/ubuntu-core/releases/12.04/release/ubuntu-core-12.04.1-core-armhf.tar.gz"
	cp -sf ${IMAGE_PATH}/ubuntu-core-12.04.1-core-armhf.tar.gz ${IMAGE_PATH}/filesystem.tar.gz
	wget -N "http://ports.ubuntu.com/ubuntu-ports/dists/precise/main/installer-armhf/current/images/omap4/netboot/MLO"
	@#cp -sf ${IMAGE_PATH}/MLO ${IMAGE_PATH}/MLO
	wget -N "http://ports.ubuntu.com/ubuntu-ports/dists/precise/main/installer-armhf/current/images/omap4/netboot/u-boot.bin"
	cp -sf ${IMAGE_PATH}/u-boot.bin ${IMAGE_PATH}/u-boot.img
	wget -N "http://ports.ubuntu.com/ubuntu-ports/dists/precise/main/installer-armhf/current/images/omap4/netboot/uImage"
	@#cp -sf ${IMAGE_PATH}/uImage ${IMAGE_PATH}/uImage

# REAL TARGETS.

# To produce the filesystem, download it from the Ubuntu website.
${FILESYSTEM} : download_files

# To produce the first stage bootloader, download it from the Ubuntu website.
${MLO} : download_files

# To produce the second state bootloader, download it from the Ubuntu website.
${UBOOT} : download_files

# To produce the kernel image, download it from the Ubuntu website.
${UIMAGE} : download_files

# To produce the boot script, make an image from the matching source file.
${BSCRIPT} : ${BSCRIPT}.src
	@echo "******** Making boot script image. ********"
	mkimage -A arm -T script -C none -n "Boot Image" -d $^ $@

# To produce the boot script source, dump the required contents to a text file.
${BSCRIPT}.src :
	@echo "******** Making boot script. ********"
	echo "fatload mmc 0:1 0x80000000 uImage" > $@
	echo "setenv bootargs rw vram=32M fixrtc mem=1G@0x80000000 root=/dev/mmcblk0p2 console=ttyO2,115200n8 rootwait" >> $@
	echo "bootm 0x80000000" >> $@

