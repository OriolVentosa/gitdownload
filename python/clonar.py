import git
import os
import shutil
import time

proba=1

while(proba==1):
    
    fitxer = open("/home/oriol/gitdownload/python/descarregar.txt", "r")
    
    link = fitxer.readline()
    
    if(link.find("/tree/master/")!=-1):
        
        repositori=link.split("/tree/master/")[0]
        carpeta=link.split("/tree/master/")[1]
        nom = repositori.split('/')[4]
                
        server= "/home/oriol/gitdownload/python"
        repositori=repositori + ".git"
        git.Git(server).clone(repositori)
        
        print nom
        print carpeta

        abans= nom+'/'+carpeta
        abans= abans.split('\n')[0]
        despres=carpeta
        
        os.chdir("/home/oriol/gitdownload/python")
        
        time.sleep(5)
        
        print abans
        
        os.rename(abans,despres)
        shutil.rmtree(nom)
        proba=0

print "he sortit"