from http.server import HTTPServer, BaseHTTPRequestHandler

import git
import os
import shutil

class Serv(BaseHTTPRequestHandler):
    
    def do_GET(self):
        var cami = self.path
        if cami.find("/tree/master/")!=-1:
            link = cami.split("?link=")[1]
            repositori=link.split("/tree/master/")[0]
            carpeta=link.split("/tree/master/")[1]
            nom = repositori.split('/')[4]
                
            server= "/home/oriol/gitdownload/webserver"
            repositori=repositori + ".git"
            git.Git(server).clone(repositori) #buscar maneres per no petar el programa mirant que retorna quan git falla
            
            print nom
            print carpeta

            abans= nom+'/'+carpeta
            abans= abans.split('\n')[0]
            despres=carpeta
            
            os.chdir("/home/oriol/gitdownload/webserver") #buscar maneres per no petar el programa quan os falla
            
            print abans
            
            os.rename(abans,despres)
            shutil.rmtree(nom)
            
            with open(despres, 'rb') as f:
                
                self.send_response(200)
                self.send_header("Content-type", 'application/octet-stream')
                self.send_header("Content-Disposition", 'attachment; filename="{}"'.format(os.path.basename(despres))) #ultim parametre lloc on esta al fitxer
                fs=os.fstat(f.fileno())
                self.send_header("Content-Lenght", str(fs.st_size))
                self.end_headers()
                shutil.copyfileobj(f, self.wfile)

        if cami == '/':
            self.path = '/index.html'
            
        try:
            file_to_open = open(self.path[1:]).read()
            self.send_response(200)
        except:
            file_to_open = "file not found"
            self.send_response(404)
        self.end_headers()
        self.wfile.write(bytes(file_to_open, 'utf-8'))

if __name__== '__main__':
    
    httpd = HTTPServer(('localhost', 8080), Serv)
    
    try:
        httpd.serve_forever()
    except KeyboardInterrupt:
        pass
    
    httpd.server_close()
    
    print "Servidor parat\n"