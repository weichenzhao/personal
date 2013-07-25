#!/bin/bash
PROCESS="`ps aux | grep 'ssh -fnN -D 8080' | awk '{print $11}'`"
NUM="`ps aux | grep 'ssh -fnN -D 8080' | wc -l`"
#echo $NUM
if [ $NUM = "2" ] ; then
  echo 'already running follow process:'
  echo $PROCESS
  if [ "$1"x = "-k"x ] ; then
    all=`ps aux | grep 'ssh -fnN -D 8080' | awk '{print $2}'`
    ssh_no=`echo $all | awk '{print $1}'`
    sudo kill $ssh_no
  fi
elif [ $NUM = "1" ] ; then
  echo 'starting...'
  ssh -fnN -D 8080 'richard@richardzhao.me'
else
  echo 'Not sure what is happening with following process:'
  echo $PROCESS
fi
