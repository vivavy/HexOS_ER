import os, sys


class Module:
    def __init__(self, path):
        self.path = path

        with open(path, 'r') as f:
            header = f.readline().strip().split(None, 1)[1]

        if not header[-1] in "0123456789":
            header = header[::-1].split(None, 1)[1][::-1]

        self.header = header
        
        self.name, self.desc, self.ver = self.header.split(' : ', 2)
    
    def print_info(self):
        print(
            Word("Module"),
            Name(self.name),
            Word("ver."),
            Ver(self.ver)
        )
        print()
        print("\033[1m"+self.desc+"\033[0m")
        print()


def Word(value):
    return "\033[34;1m%s\033[0m" % value


def Ver(value):
    return "\033[35;1m%s\033[0m" % value


def Err(value):
    return "\033[31;1m%s\033[0m" % value


def Name(value):
    return "\033[33;1m%s\033[0m" % value


def Sub(value):
    return "\033[37;1m%s\033[0m" % value


def Success(value):
    return "\033[32;1m%s\033[0m" % value


modules = []

for path in os.listdir('src'):
    if path.endswith('.cpp'):
        modules.append(Module("src/" + path))

for module in modules:
    if module.name == sys.argv[1]:
        module.print_info()
        sys.exit(0)
else:
    print(Err("Module not found"))
