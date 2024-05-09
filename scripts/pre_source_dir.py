Import("env")

import glob
import os

def FindInoNodes(env):
    src_dir = glob.escape(env.subst("$PROJECT_SRC_DIR"))
    src_filter = env.get("SRC_FILTER",[]);
    
    pathnames=set()
    [pathnames.add(os.path.join(src_dir,os.path.dirname(i))) for i in env.MatchSourceFiles(src_dir,src_filter,["ino"])]
      
    nodes = []    
    [nodes.extend(env.Glob(os.path.join(src_dir,pathname,"*.ino"))) for pathname in pathnames]

    #for pathname in pathnames:
     #   print(os.path.join(src_dir,pathname,"*.ino"))
      #  nodes+=env.Glob(os.path.join(src_dir,pathname,"*.ino"))
  #  
   # for node in nodes:
    #    print(node)    
    return nodes

env.AddMethod(FindInoNodes)
