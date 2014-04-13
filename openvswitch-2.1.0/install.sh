#!/bin/bash
./boot.sh
./configure --with-linux=/lib/modules/`uname -r`/build
make
sudo make install
sudo make modules_install
#/sbin/modprobe openvswitch 
mkdir -p /usr/local/etc/openvswitch
ovsdb-tool create /usr/local/etc/openvswitch/conf.db vswitchd/vswitch.ovsschema
