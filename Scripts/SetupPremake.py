import sys
import os
from pathlib import Path

import Utils

class PremakeSetup:
    PREMAKE_VERSION = "5.0.0-beta1"
    PREMAKE_BASE_URL = f"https://github.com/premake/premake-core/releases/download/v{PREMAKE_VERSION}/premake-{PREMAKE_VERSION}-windows.zip"
    PREMAKE_LICENSE_URL = "https://raw.githubusercontent.com/premake/premake-core/master/LICENSE.txt"

    SCRIPT_DIR = Path(__file__).parent
    PREMAKE_DIRECTORY = str(SCRIPT_DIR.parent / "Programs" / "ThirdParty" / "premake" / "bin")

    @classmethod
    def Validate(cls) -> bool:
        if (not cls.CheckIfPremakeInstalled()):
            print("Premake not found.")
            return False
        print(f"Premake found in {cls.PREMAKE_DIRECTORY}.")
        return True
    
    @classmethod
    def CheckIfPremakeInstalled(cls) -> bool:
        premake_executable = Path(cls.PREMAKE_DIRECTORY) / "premake5.exe"
        if (not premake_executable.exists()):
            return cls.InstallPremake()
        return True
    
    @classmethod
    def InstallPremake(cls) -> bool:
        while True:
            reply = input(f"Premake not found. Would you like to download Premake {cls.PREMAKE_VERSION}? [Y/N]: ").strip().lower()[:1]
            if reply == 'n':
                return False
            if reply == 'y':
                break

        premake_dir = Path(cls.PREMAKE_DIRECTORY)
        try:
            premake_dir.mkdir(parents=True, exist_ok=True)
        except Exception as e:
            print(f"Failed to create directory '{premake_dir}': {e}")
            return False

        premake_zip = premake_dir / f"premake-{cls.PREMAKE_VERSION}-windows.zip"

        try:
            print(f"Downloading {cls.PREMAKE_BASE_URL} -> {premake_zip}")
            Utils.DownloadFile(cls.PREMAKE_BASE_URL, str(premake_zip))
            print("Extracting", premake_zip)
            Utils.UnzipFile(str(premake_zip), deleteZipFile=True)
            print(f"Premake {cls.PREMAKE_VERSION} has been downloaded to '{premake_dir}'")

            license_path = premake_dir / "LICENSE.txt"
            print(f"Downloading {cls.PREMAKE_LICENSE_URL} -> {license_path}")
            Utils.DownloadFile(cls.PREMAKE_LICENSE_URL, str(license_path))
            print(f"Premake License file has been downloaded to '{license_path}'")

            return True
        except Exception as e:
            print(f"Failed to install Premake: {e}")
            try:
                if premake_zip.exists():
                    premake_zip.unlink()
            except Exception:
                pass
            return False
        
if __name__ == "__main__":
    ok = PremakeSetup.Validate()
    sys.exit(0 if ok else 1)