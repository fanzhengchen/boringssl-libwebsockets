#!/bin/sh

javah -o ./app/src/main/cpp/ww.h \
	-classpath ./app/build/intermediates/classes/debug \
	mark.com.boringssl.JNI

