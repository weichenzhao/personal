#!/bin/bash
echo "6" > /proc/sys/kernel/printk
/sbin/modprobe openvswitch
ovsdb-server --remote=punix:/usr/local/var/run/openvswitch/db.sock \
             --remote=db:Open_vSwitch,Open_vSwitch,manager_options \
             --private-key=db:Open_vSwitch,SSL,private_key \
             --certificate=db:Open_vSwitch,SSL,certificate \
             --bootstrap-ca-cert=db:Open_vSwitch,SSL,ca_cert \
             --pidfile --detach

ovs-vsctl --no-wait init

ovs-vswitchd --pidfile --detach

ovs-vsctl add-br br0
#ovs-vsctl add-port br0 eth0
#ovs-vsctl add-port br0 vif1.0
