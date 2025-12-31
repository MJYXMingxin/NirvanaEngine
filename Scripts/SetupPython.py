import sys
import subprocess
import importlib.util as importlib_util
from typing import Sequence

class PythonSetup:
    @classmethod
    def Validate(cls, required_packages: Sequence[str] = ("requests",)) -> bool:
        """Validate Python environment and required packages."""
        if not cls.__validate_python():
            return False

        for package_name in required_packages:
            if not cls.__validate_package(package_name):
                return False
        return True

    @classmethod
    def __validate_python(cls, version_major: int = 3, version_minor: int = 3) -> bool:
        vi = sys.version_info
        print(f"Python version {vi.major}.{vi.minor}.{vi.micro} detected.")
        if vi.major < version_major or (vi.major == version_major and vi.minor < version_minor):
            print(f"Python version too low, expected {version_major}.{version_minor} or higher.")
            return False
        return True

    @classmethod
    def __validate_package(cls, package_name: str) -> bool:
        if importlib_util.find_spec(package_name) is None:
            return cls.__install_package(package_name)
        return True

    @classmethod
    def __install_package(cls, package_name: str) -> bool:
        """Interactive installation package; use the current interpreter's pip to install and then verify again."""
        while True:
            reply = input(f"Would you like to install Python package '{package_name}'? [Y/N]: ").strip().lower()[:1]
            if reply == 'n':
                return False
            if reply == 'y':
                break

        print(f"Installing {package_name}...")
        cmd = [sys.executable, '-m', 'pip', 'install', package_name]
        try:
            subprocess.run(cmd, check=True)
        except subprocess.CalledProcessError as e:
            print(f"Failed to install {package_name}: {e}")
            return False
        except Exception as e:
            print(f"Unexpected error while installing {package_name}: {e}")
            return False

        return cls.__validate_package(package_name)

if __name__ == "__main__":
    ok = PythonSetup.Validate()
    sys.exit(0 if ok else 1)