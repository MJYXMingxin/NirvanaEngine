import sys
import os
import winreg
import shutil
import requests
import time
import urllib
from typing import Optional, Union, Iterable
from zipfile import ZipFile, ZipInfo

def GetSystemEnvironmentVariable(name: str) -> Optional[str]:
    key = winreg.CreateKey(winreg.HKEY_LOCAL_MACHINE, r"System\CurrentControlSet\Control\Session Manager\Environment")
    try:
        return winreg.QueryValueEx(key, name)[0]
    except Exception:
        return None

def GetUserEnvironmentVariable(name: str) -> Optional[str]:
    key = winreg.CreateKey(winreg.HKEY_CURRENT_USER, r"Environment")
    try:
        return winreg.QueryValueEx(key, name)[0]
    except Exception:
        return None

def DownloadFile(url: Union[str, Iterable[str]], filepath: str, timeout: int = 30):
    """
    Download a file from a URL or list of fallback URLs.
    Uses a temporary .part file and moves it into place on success.
    Raises on failure.
    """
    # normalize url list
    urls = [url] if isinstance(url, str) else list(url)
    if not urls:
        raise ValueError("Argument 'url' must be a string or a non-empty iterable of strings")

    filepath = os.path.abspath(filepath)
    os.makedirs(os.path.dirname(filepath), exist_ok=True)
    tmp_path = filepath + ".part"

    last_exc = None
    for u in urls:
        try:
            _download_single(u, tmp_path, timeout)
            # move into final location (atomic on same filesystem)
            shutil.move(tmp_path, filepath)
            return
        except Exception as e:
            last_exc = e
            try:
                if os.path.exists(tmp_path):
                    os.remove(tmp_path)
            except OSError:
                pass
            print(f"Download failed for {u}: {e}. Trying next option..." if len(urls) > 1 else f"Download failed: {e}")
            continue

    # If we reach here, all attempts failed
    raise last_exc if last_exc is not None else ValueError(f"Failed to download {filepath}")

def _download_single(url: str, tmp_path: str, timeout: int):
    headers = {
        'User-Agent': "Mozilla/5.0 (Windows NT) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117 Safari/537.36"
    }
    # stream the response and write to tmp file
    with requests.get(url, headers=headers, stream=True, timeout=timeout) as response:
        try:
            response.raise_for_status()
        except requests.exceptions.RequestException as e:
            raise

        total = response.headers.get('content-length')
        total_int = int(total) if total and total.isdigit() else None

        # choose chunk size: ~64KB or a segment of total
        chunk_size = 64 * 1024
        if total_int:
            chunk_size = max(8 * 1024, min(chunk_size, total_int // 100 or chunk_size))

        downloaded = 0
        start_time = time.time()
        with open(tmp_path, 'wb') as f:
            if total_int is None:
                # unknown size: write everything without progress bar of percentage
                for chunk in response.iter_content(chunk_size=chunk_size):
                    if chunk:
                        f.write(chunk)
                elapsed = time.time() - start_time
                print(f"Downloaded (size unknown) in {elapsed:.2f}s")
                return

            for chunk in response.iter_content(chunk_size=chunk_size):
                if not chunk:
                    continue
                f.write(chunk)
                downloaded += len(chunk)

                # compute progress
                try:
                    percentage = downloaded / total_int * 100
                    done = int(50 * downloaded / total_int)
                except ZeroDivisionError:
                    percentage = 100.0
                    done = 50

                elapsed = time.time() - start_time
                avg_kb_s = (downloaded / 1024) / elapsed if elapsed > 0 else 0.0
                if avg_kb_s > 1024:
                    speed_str = f"{avg_kb_s/1024:.2f} MB/s"
                else:
                    speed_str = f"{avg_kb_s:.2f} KB/s"

                sys.stdout.write(f"\r[{'█'*done}{'.'*(50-done)}] {percentage:6.2f}% ({speed_str})     ")
                sys.stdout.flush()
        sys.stdout.write("\n")

def UnzipFile(filepath: str, deleteZipFile: bool = True):
    """
    Extract zip file with progress. Skips files that already exist with same size.
    """
    zip_path = os.path.abspath(filepath)
    dest_dir = os.path.dirname(zip_path)

    with ZipFile(zip_path, 'r') as zf:
        infos = zf.infolist()
        # filter out directory entries (file_size == 0 but could be real empty file)
        total_size = sum(info.file_size for info in infos)
        if total_size == 0:
            # fallback: extract all without progress
            zf.extractall(path=dest_dir)
            if deleteZipFile:
                try:
                    os.remove(zip_path)
                except OSError:
                    pass
            return

        extracted = 0
        start_time = time.time()
        for info in infos:
            # construct destination path safely
            dest_path = os.path.abspath(os.path.join(dest_dir, info.filename))
            os.makedirs(os.path.dirname(dest_path), exist_ok=True)

            # If file exists and size matches, skip
            if os.path.exists(dest_path) and os.path.getsize(dest_path) == info.file_size and info.file_size > 0:
                # consider as already extracted
                extracted += info.file_size
            else:
                # extract this member
                zf.extract(info, path=dest_dir) if isinstance(info, ZipInfo) else zf.extract(info.filename, path=dest_dir)
                extracted += info.file_size

            # progress
            try:
                done = int(50 * extracted / total_size)
                percentage = extracted / total_size * 100
            except ZeroDivisionError:
                done = 50
                percentage = 100.0

            elapsed = time.time() - start_time
            avg_kb_s = (extracted / 1024) / elapsed if elapsed > 0 else 0.0
            speed_str = f"{avg_kb_s/1024:.2f} MB/s" if avg_kb_s > 1024 else f"{avg_kb_s:.2f} KB/s"

            sys.stdout.write(f"\r[{'█'*done}{'.'*(50-done)}] {percentage:6.2f}% ({speed_str})     ")
            sys.stdout.flush()

    sys.stdout.write("\n")
    if deleteZipFile:
        try:
            os.remove(zip_path)
        except OSError:
            pass