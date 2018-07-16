import time
import BaseHTTPServer
import os
import shutil


class MyHandler(BaseHTTPServer.BaseHTTPRequestHandler):
    def do_HEAD(s):
        s.send_response(200)
        s.send_header("Content-type", "text/html")
        s.end_headers()
    def do_GET(s):
        """Respond to a GET request."""
        
        print '\n' + s.path + '\n'
        s.send_response(200)
        s.send_header("Content-type", "application/zip")
        s.end_headers()
        
        with open('/home/oriol/gitdownload/webserver' + s.path, 'utf-8') as file: 
            s.wfile.write(file.read())
        
        

if __name__ == '__main__':
    

    HOST_NAME = 'hosty' # !!!REMEMBER TO CHANGE THIS!!!
    PORT_NUMBER = 80 # Maybe set this to 9000.
    server_class = BaseHTTPServer.HTTPServer
    httpd = server_class(('localhost', 60), MyHandler)
    print time.asctime(), "Server Starts - %s:%s" % (HOST_NAME, PORT_NUMBER)
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    httpd.server_close()
    print time.asctime(), "Server Stops - %s:%s" % (HOST_NAME, PORT_NUMBER)