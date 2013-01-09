#! /usr/bin/env python

if __name__ == '__main__':
  import generate_moc
  raise SystemExit(generate_moc.main())

import os
from subprocess import call

def gen_moc():
  workDir = os.getcwd()
  dirList = os.listdir(workDir)

  for files in 	dirList:
    if files.endswith(".h"):
      print files
      outp = "moc_" + files[:-2] + ".cpp"
      print outp
      call(["moc", files, "-o", outp])

def gen_uic():
  workDir = os.getcwd()
  dirList = os.listdir(workDir)

  for files in 	dirList:
    if files.endswith(".ui"):
      print files
      outp = "ui_" + files[:-3] + ".hpp" #cut .ui add .h
      print outp
      call(["uic", files, "-o", outp])

def main():
  gen_moc()
  gen_uic()

