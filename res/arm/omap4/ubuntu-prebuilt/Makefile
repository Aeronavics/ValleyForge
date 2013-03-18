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
# MAKEFILE FOR CREATING UBUNTU IMAGES FOR ARM TARGETS, FROM PREBUILT BINARIES.
#
#	Author:		Edwin Hayes
#
#	Created:	18th Mar 2013
#

# VARIABLES.

IMAGE_PATH=BUILD_INSERTS_IMAGE_PATH_HERE

IMAGEFILE=${IMAGE_PATH}/image.img.gz

# PSEUDO TARGETS.

.PHONY: all image download_files

all : image

image : ${IMAGEFILE}

# Download recent copies of all the relevant files from the Ubuntu servers.
download_files :
	@echo "******** Fetching latest copy of files from server. ********"
	wget -N	"http://cdimage.ubuntu.com/releases/12.04/release/ubuntu-12.04-preinstalled-desktop-armhf+omap4.img.gz"
#	wget -N "http://cdimage.ubuntu.com/daily-preinstalled/current/raring-preinstalled-desktop-armhf+nexus7.img.gz"
#	cp -sf "${IMAGE_PATH}/raring-preinstalled-desktop-armhf+nexus7.img.gz" ${IMAGE_PATH}/image.img.gz
	cp -sf "${IMAGE_PATH}/ubuntu-12.04-preinstalled-desktop-armhf+omap4.img.gz" ${IMAGE_PATH}/image.img.gz

# REAL TARGETS.

# To produce the filesystem, download it from the Ubuntu website.
${IMAGEFILE} : download_files

