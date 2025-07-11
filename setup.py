# setup.py
from skbuild import setup

setup(
    name="tess",
    version="1.0.0.3",
    packages=["tess"],
    package_data={"tess": ["bin/*"]},
    # ────────────────────────────────────────────┐
    cmake_source_dir=".",                         #│  ← where your top‐level CMakeLists.txt lives
    cmake_install_dir="tess",                   
    # ────────────────────────────────────────────┘ │  ← install into tess/bin/...
    cmake_args=["-DCMAKE_BUILD_TYPE=Release"],
)
