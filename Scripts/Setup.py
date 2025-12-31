import os
import subprocess
import platform

from SetupPython import PythonSetup

PythonSetup.Validate()

from SetupPremake import PremakeSetup
script_dir = os.path.dirname(__file__)
repo_root = os.path.abspath(os.path.join(script_dir, '..'))
os.chdir(repo_root)

IsPremakeInstalled = PremakeSetup.Validate()

print("\nUpdating submodules...")
subprocess.call(['git', 'submodule', 'update', '--init', '--recursive'])

if IsPremakeInstalled:
    if platform.system() == "Windows":
        print("\nGenerating project files with Premake...")
        subprocess.call([os.path.abspath("./Scripts/GenerateProjects.bat"), "nopause"])
    print("\nSetup completed.")
else:
    print("\nSetup incomplete due to missing Premake.")