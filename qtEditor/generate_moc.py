#! /usr/bin/env python

if __name__ == '__main__':
  import generate_moc
  raise SystemExit(generate_moc.main())

import os
import shutil
from subprocess import call

def gen_moc():
  workDir = os.getcwd() + "/Gui"
  print workDir
  dirList = os.listdir(workDir)

  for files in 	dirList:
    if files.endswith(".h"):
      print files
      outp = "moc_" + files[:-2] + ".cpp"
      print outp
      affected = "./Gui/" + files
      call(["moc", affected, "-o", outp])
      #os.rename(outp, "./Gui/" + outp)
      l = -1
      f = open(outp)
      lines = f.readlines()
      f.close()
      for line in lines:
        if line[0] == '#':
            break;
        l = l + 1

      if l >= 0:
        f = open(outp, 'w');
        lines[l] = '\n#include "EdPrec.h"\n'
        f.writelines(lines)
        f.close()
      
      shutil.move(outp, "./Gui/" + outp)

def gen_uic():
  workDir = os.getcwd() + "/Gui"
  dirList = os.listdir(workDir)

  for files in 	dirList:
    if files.endswith(".ui"):
      print files
      outp = "ui_" + files[:-3] + ".hpp" #cut .ui add .h
      #print outp
      affected = "./Gui/" + files
      call(["uic", affected, "-o", outp])
      #os.rename(outp, "./Gui/" + outp)
      shutil.move(outp, "./Gui/" + outp)

def main():
  gen_moc()
  gen_uic()

