import gzip
import zipfile
import os
import shutil

os.chdir("/home/oriol/gitdownload/webserver")
shutil.make_archive('eee', 'zip', 'eee' )