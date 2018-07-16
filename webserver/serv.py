import httpserver
import SimpleHTTPServer
import BaseHTTPServer
import time
import zipfile

import git
import os
import shutil

class MyHandler(BaseHTTPServer.BaseHTTPRequestHandler):
    
    def do_GET(s):
        cami = s.path
        
        if cami.find("%2Ftree%2Fmaster")!=-1:
            
            cami2 = cami
        
            print cami2
            
            a = cami2.split('%3A')

            cami2 = a[0] + ':' + a[1]

            a = cami2.split('%2F')

            b= ''
            for x in range(0,len(a)):
                if x != 0:
                    b = b + '/' + a[x]
                else:
                    b = a[x]
                    
            cami2 = b
            
            link = cami2.split("?link=")[1]
            repositori=link.split("/tree/master/")[0]
            carpeta=link.split("/tree/master/")[1]
            nom = repositori.split('/')[4]
            
            
            server= "/home/oriol/gitdownload/webserver"
            repositori=repositori + ".git"
            git.Git(server).clone(repositori) #buscar maneres per no petar el programa mirant que retorna quan git falla
            
            print (nom)
            print (carpeta)

            abans= nom+'/'+carpeta
            despres=carpeta
            
            os.chdir("/home/oriol/gitdownload/webserver") #buscar maneres per no petar el programa quan os falla
            
            print (abans)
            
            os.rename(abans,despres)
            shutil.rmtree(nom)
                            
            s.send_response(200)
            s.send_header("Content-type", "application/zip")
            s.end_headers()
            
            os.chdir("/home/oriol/gitdownload/webserver")
            shutil.make_archive(despres , 'zip', despres )
            
            with open('/home/oriol/gitdownload/webserver/'+despres+'.zip','rb') as file: 
                s.wfile.write(file.read())
            
            
                
        else:
            
            if cami == '/':
                s.path = '/index.html'
                
            try:
                file_to_open = open(self.path[1:]).read()
                s.send_response(200)
            except:
                file_to_open = "file not found"
                s.send_response(404)
            
            s.end_headers()
            
            with open('/home/oriol/gitdownload/webserver' + cami, 'r') as file: 
                s.wfile.write(file.read())
        
        

    
if __name__ == '__main__':
    

    HOST_NAME = 'hosty' # !!!REMEMBER TO CHANGE THIS!!!
    PORT_NUMBER = 210 # Maybe set this to 9000.
    server_class = BaseHTTPServer.HTTPServer
    httpd = server_class(('localhost', 1600), MyHandler)
    print time.asctime(), "Server Starts - %s:%s" % (HOST_NAME, PORT_NUMBER)
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    httpd.server_close()
    print time.asctime(), "Server Stops - %s:%s" % (HOST_NAME, PORT_NUMBER)