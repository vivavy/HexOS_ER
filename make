#!/usr/bin/env python3

import os, sys

if len(sys.argv) < 2:
    os.system("python3 scripts/make++.py")
    os.system("make run")
elif sys.argv[1] == "mod":
    os.system("python3 scripts/mod.py \"" + sys.argv[2] + "\"")
elif sys.argv[1] == "build":
    os.system("python3 scripts/make++.py")
elif sys.argv[1] == "run":
    os.system("make run")
else:
    print("Usage: make <command>")
    print("Commands:")
    print("  mod <module> - print module info")
    print("  build - build the project")
    print("  run - run the project")
