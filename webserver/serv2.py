import httpserver
import BaseHTTPServer

import git
import os
import shutil

class Serv(BaseHTTPServer.BaseHTTPRequestHandler):

    def do_GET(s):
        cami = s.path
        if cami == '/':
            s.path = '/index.html'
            
        try:
            file_to_open = open(self.path[1:]).read()
            s.send_response(200)
        except:
            file_to_open = "file not found"
            s.send_response(404)
        print 'paquet rebut'
        
        s.end_headers()
        s.wfile.write(bytes(file_to_open, 'utf-8'))
        
service=BaseHTTPServer.HTTPServer(('localhost', 8080), Serv)

service.serve_forever()