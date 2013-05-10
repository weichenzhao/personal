#!/bin/bash

USER="richard" #用户名
PASSWORD="lekvbzrd159753" #密码
DBNAME="richardzhao" #数据库名称
TABLENAME="wp_statpress" #数据库中表的名称
FILENAME=[MySQL_Data_Statepress]
DATE=`date +%Y-%m-%d,%H%M`
FILE="$DATE""$FILENAME"
mkdir $FILE
cd $FILE

mysql -u $USER -p$PASSWORD $DBNAME -e "use $DBNAME"
mysql -u $USER -p$PASSWORD $DBNAME -e "select id from $TABLENAME;" > 01-id.txt
mysql -u $USER -p$PASSWORD $DBNAME -e "select date from $TABLENAME;" > 02-date.txt
mysql -u $USER -p$PASSWORD $DBNAME -e "select time from $TABLENAME;" > 03-time.txt
mysql -u $USER -p$PASSWORD $DBNAME -e "select ip from $TABLENAME;" > 04-ip.txt
mysql -u $USER -p$PASSWORD $DBNAME -e "select urlrequested from $TABLENAME;" > 05-urlrequested.txt
mysql -u $USER -p$PASSWORD $DBNAME -e "select statuscode from $TABLENAME;" > 06-statuscode.txt
mysql -u $USER -p$PASSWORD $DBNAME -e "select agent from $TABLENAME;" > 07-agent.txt
mysql -u $USER -p$PASSWORD $DBNAME -e "select referrer from $TABLENAME;" > 08-referrer.txt
mysql -u $USER -p$PASSWORD $DBNAME -e "select search from $TABLENAME;" > 09-search.txt
mysql -u $USER -p$PASSWORD $DBNAME -e "select nation from $TABLENAME;" > 10-nation.txt
mysql -u $USER -p$PASSWORD $DBNAME -e "select os from $TABLENAME;" > 11-os.txt
mysql -u $USER -p$PASSWORD $DBNAME -e "select browser from $TABLENAME;" > 12-browser.txt
mysql -u $USER -p$PASSWORD $DBNAME -e "select searchengine from $TABLENAME;" > 13-searchengine.txt
mysql -u $USER -p$PASSWORD $DBNAME -e "select spider from $TABLENAME;" > 14-spider.txt
mysql -u $USER -p$PASSWORD $DBNAME -e "select feed from $TABLENAME;" > 15-feed.txt
mysql -u $USER -p$PASSWORD $DBNAME -e "select user from $TABLENAME;" > 16-user.txt
mysql -u $USER -p$PASSWORD $DBNAME -e "select timestamp from $TABLENAME;" > 17-timestamp.txt
mysql -u $USER -p$PASSWORD $DBNAME -e "select ptype from $TABLENAME;" > 18-ptype.txt
mysql -u $USER -p$PASSWORD $DBNAME -e "select pvalue from $TABLENAME;" > 19-pvalue.txt
#mysql -u $USER -p$PASSWORD $DBNAME -e "select id from $TABLENAME;" > /home/richard/sql_info\[2012-12-16\,1322\]/id.txt
#mysql -u $USER -p$PASSWORD $DBNAME -e "show columns from $TABLENAME;"

cd ..
