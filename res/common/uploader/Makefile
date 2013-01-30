# Copyright (C) 2012  Unison Networks Ltd
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

SOURCES := $(wildcard *.cpp)
HEADERS := $(wildcard *.hpp)
LIBS := -lusb-1.0 -lpthread

OBJS := $(patsubst %.cpp,%.o,$(SOURCES))

TARGET := uploader

LDFLAGS += $(LIBS)

$(TARGET) : $(OBJS) $(HEADERS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

.PHONY : all
all : $(TARGET)

.PHONY : clean
clean :
	rm *.o
	rm $(TARGET)

#ALL DONE.
