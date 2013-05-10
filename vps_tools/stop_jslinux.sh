kill $(ps ax | grep websockify | head -n 1 | awk '{print $1}')
