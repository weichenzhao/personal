#!/bin/bash
case $1 in
        start)
			echo "start"
            ;;
         
        stop)
            exit 0
            ;;
        *)
            echo $"Usage: $0 {start|stop|restart|condrestart|status}"
            exit 1
esac
