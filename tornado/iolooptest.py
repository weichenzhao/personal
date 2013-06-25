import errno
import functools
import tornado.ioloop as ioloop
import tornado.iostream as iostream
import socket
import openflow_header as of

def connection_ready(sock, fd, events):
    while True:
        try:
            connection, address = sock.accept()
        except socket.error, e:
            if e.args[0] not in (errno.EWOULDBLOCK, errno.EAGAIN):
                raise
            return
        connection.setblocking(0)
        handle_connection(connection, address)
        stream = iostream.IOStream(connection)
        print stream
        stream.read_bytes(1024, print_on_screen)
        msg = of.ofp_header()
        #msg.show()
        stream.write(str(msg))
        print "send OFP_HELLO"

def print_on_screen(data):
    print "received something"
    print data

def handle_connection(connection, address):
        print "1 connection,", connection, address

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.setblocking(0)
sock.bind(("", 6633))
sock.listen(6633)

io_loop = ioloop.IOLoop.instance()
callback = functools.partial(connection_ready, sock)
io_loop.add_handler(sock.fileno(), callback, io_loop.READ)
io_loop.start()
