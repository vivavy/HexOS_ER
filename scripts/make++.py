import os, sys, json, time, shutil, re

CXXFLAGS = \
	"-Wbuiltin-declaration-mismatch" \
	" -m32" \
	" -nostdlib" \
	" -fno-builtin" \
	" -fno-stack-protector" \
	" -fno-exceptions" \
	" -fno-rtti" \
	" -g" \
	" -O0" \
	" -std=c++20" \
	" -Iinc" \
	" -fno-use-cxa-atexit" \
    " -Xassembler --32"

LOG = "/tmp/hexos-build-output.txt"

global elapsed
elapsed = 0


class Module:
    def __init__(self, path):
        self.path = path
        self.target = None

        with open(path, 'r') as f:
            header = f.readline().strip().split(None, 1)[1]

        if not header[-1] in "0123456789":
            header = header[::-1].split(None, 1)[1][::-1]

        self.header = header
        
        self.name, self.desc, self.ver = self.header.split(' : ', 2)
    
    def print_build(self):
        print(
            Word("Building module:"),
            Name(self.name),
            Word("ver."),
            Ver(self.ver)
        )


class Timer:
    def __init__(self, stage: str):
        self.start = None
        self.stage = stage
        self.error = False

    def __enter__(self):
        self.start = time.time()
        return self

    def __exit__(self, type, value, traceback):
        now = time.time()
        global elapsed
        elapsed += now - self.start
        if self.error:
            prettyExit(self.stage)
        print(
            "   ",
            Word("Time elapsed:"),
            Name(round(now - self.start, 2)),
            Word("seconds"),
            "\n"
        )


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


def checkError(fn = None):
    # print(open(LOG).read())
    if fn is None and "err" in open(LOG).read():
        print(Err("Task failed"))
        print(Err("Output:"))
        with open(LOG) as f:
            print(f.read())
        return True
    elif fn is not None:
        if fn(open(LOG).read()):
            print(Err("Task failed"))
            print(Err("Output:"))
            with open(LOG) as f:
                print(f.read())
            return True
    return False


def prettyExit(stage: str):
    print(Err("Build failed on stage:"), Name(stage))
    sys.exit(1)


def parse_version(version: str):
    # Парсинг версии, извлекая major, minor, patch и rev
    match = re.match(r'(\d+)\.(\d+)\.(\d+)-rev(\d+)', version)
    if not match:
        raise ValueError(f"Invalid version format: {version}")
    return tuple(map(int, match.groups()))

def get_latest_version(versions: list) -> str:
    # Парсинг всех версий
    parsed_versions = [parse_version(v) for v in versions]
    # Сортировка версий по major, minor, patch, игнорируя rev
    parsed_versions.sort(key=lambda v: (v[0], v[1], v[2]), reverse=True)
    # Форматирование самой новой версии обратно в строку
    latest_version = parsed_versions[0]
    return f"{latest_version[0]}.{latest_version[1]}.{latest_version[2]}-rev{latest_version[3]}"


if not os.getenv('DONT_CLEAR'):
    os.system('clear')

if os.path.exists('build'):
   shutil.rmtree('build')
os.mkdir('build')

with open(LOG, "w") as f:
    f.write("")

print("\033[1;32m========================================")
print("|   HexOS Building System ver. 0.2.1   |")
print("========================================\033[0m\n\n")

data = json.load(open('metainf.json'))
name = data['name']
dist_name = data['dist-name']
arch = data['arch']
min_cpu = data['min_cpu']
min_mem = data['min_mem']

"""print("\033[34;1mName:\033[0m\t\t\t\033[1;33m%s\033[0m" % name)
print("\033[34;1mDist-Name:\033[0m\t\t\033[1;33m%s\033[0m" % dist_name)
print("\033[34;1mArch:\033[0m\t\t\t\033[1;33m%s\033[0m" % arch)
print("\033[34;1mMin required CPU:\033[0m\t\033[1;33m%s\033[0m" % min_cpu)
print("\033[34;1mMin required Memory:\033[0m\t\033[1;33m%s\033[0m" % min_mem)
print("")"""

versions = []

for module in os.listdir('src'):
    module = Module("src/" + module)
    versions.append(module.ver)

ver = get_latest_version(versions)

with open('src/version.cpp', 'w') as f:
    f.write(
f"""// Version : Version information container : 0.0.1-rev0

#include <version.h>

const char *VERSION = \"{ver}\";
""")


print(
    Word("Distribution:"),
    Name(name + " " + dist_name),
    Word("ver."),
    Ver(ver),
    Word("for"),
    Name(min_cpu) +
    Word("+ (" + arch + ")"),
    "\n"
)

module = Module('asm/boot.S')
module.target = "build/boot.o"
with Timer(f"Building {module.name}") as t:
    module.print_build()
    os.system(f"i686-elf-as --32 -o build/boot.o asm/boot.S 2> {LOG}")
    t.error = checkError(lambda x: x)

cpp_modules = []

for path in os.listdir('src'):
    if path.endswith('.cpp'):
        cpp_modules.append(Module("src/" + path))
        cpp_modules[-1].target = "build/" + os.path.splitext(
            os.path.basename(cpp_modules[-1].path))[0]+".o"

cpp_modules = [module] + cpp_modules

for module in cpp_modules:
    with Timer("Building " + module.name) as t:
        module.print_build()
        os.system("i686-elf-g++ %s -s -c -o %s %s 2>%s" %
                (CXXFLAGS,
                "build/" + os.path.splitext(
                    os.path.basename(module.path))[0]+".o",
                module.path, LOG))
        t.error = checkError()


def ld_check(output: str):
    for line in output.splitlines():
        if "warning" not in line:
            return True
    return False


def full_ld_check(output):
    return ld_check(output) and not os.path.exists("build/kernel.elf")


with Timer("Linking") as t:
    print(
        Word("Linking"),
        Name(str(len(cpp_modules) + 1)),
        Word("modules")
    )
    # print(*[m.target for m in cpp_modules])
    os.system(f"i686-elf-ld -o build/kernel.elf -T linker.ld {' '.join(m.target for m in cpp_modules)} 2> {LOG}")
    t.error = checkError(full_ld_check)

with Timer("Creating ISO image") as t:
    print(Word("Creating ISO image"))
    os.system("mkdir -p build/iso/boot/grub build/iso/boot/grub"
              f" build/iso/sys > {LOG} 2> {LOG}")
    os.system(f"cp build/kernel.elf build/iso/sys 2> {LOG}")
    os.system(f"cp grub.cfg build/iso/boot/grub 2> {LOG}")
    os.system(f"grub-mkrescue -o hexos.iso build/iso 2> {LOG}")
    t.error = checkError()

print(Word("ISO image stored in \"") + Name("hexos.iso") + Word("\""))
os.system("rm -rf build")
print()
print(Word("Build successful, took"), Name(str(round(elapsed, 2))), Word("seconds"))
print()
