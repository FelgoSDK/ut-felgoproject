message(--------------------)
message(--------------------)
message(-- felgo-for-ubuntu-touch.pri)

# Prepare Ubuntu Touch
load(ubuntu-click)

# Override TARGET so the output executable is always same
# --> In *.desktop file always same Exec line: Exec=./app.run
DEFAULT_TARGET = $$TARGET
TARGET = app.run

expected_project_root_dir = $$absolute_path($$PWD/../..)  # PWD = where felgo-ubuntu-touch.pri resides
exists ($${expected_project_root_dir}/manifest.json.in) {
  UBUNTU_MANIFEST_FILE = $${expected_project_root_dir}/manifest.json.in
  OTHER_FILES += $${expected_project_root_dir}/manifest.json
}
exists ($${expected_project_root_dir}/manifest.apparmor) {
  OTHER_FILES += $${expected_project_root_dir}/manifest.apparmor
}
exists ($${expected_project_root_dir}/manifest.desktop) {
  OTHER_FILES += $${expected_project_root_dir}/manifest.desktop
}

# Not only build but also install the built target into the root of the dist directory
target.path = /
INSTALLS+=target

# Enable felgo
CONFIG += felgo

# Determine libraries to load
ARCH_UT                           = amd64
linux-aarch64-gnu-g++:    ARCH_UT = arm64
ubuntu-arm-gnueabihf-g++: ARCH_UT = armhf

# QtQuick.Controls v1
OTHER_FILES += $$absolute_path($$PWD/../Qt/$${QT_VERSION}/$${ARCH_UT}/qml)


LOCAL_FELGO_PLATFORM_LIBRARY_PATH = $$absolute_path($$PWD/$${QT_VERSION}/$${ARCH_UT})
_LOCAL_FELGO_PLATFORM_LIBRARY_PATH = $$LOCAL_FELGO_PLATFORM_LIBRARY_PATH
include($$LOCAL_FELGO_PLATFORM_LIBRARY_PATH/mkspecs/features/felgo.prf)


config_files.path = /
config_files.files += $${OTHER_FILES}
message($$config_files.files)
INSTALLS+=config_files


message(-- END felgo-for-ubuntu-touch.pri)
message(--------------------)
message(--------------------)
