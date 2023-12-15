import gzip, pkg_resources

Import("env")

required_pkgs = {'dulwich'}
installed_pkgs = {pkg.key for pkg in pkg_resources.working_set}
missing_pkgs = required_pkgs - installed_pkgs

if missing_pkgs:
    env.Execute('$PYTHONEXE -m pip install dulwich --global-option="--pure" --use-pep517')

from dulwich import porcelain
from dulwich.repo import Repo

def get_firmware_specifier_build_flag():
    build_version = porcelain.describe('.')  # '.' refers to the repository root dir
    build_flag = "-D AUTO_VERSION=\\\"" + build_version + "\\\""
    print ("Firmware Revision: " + build_version)
    return (build_flag)

def get_flash_size():
    flash_size = int(env.BoardConfig().get("upload.maximum_size")/1024/1024)
    build_flag = "-D ESP_FLASH_SIZE=" + str(flash_size)
    print ("ESP Flash Size: " + str(flash_size))
    return (build_flag)

env.Append(
    BUILD_FLAGS=[get_flash_size()]
)

