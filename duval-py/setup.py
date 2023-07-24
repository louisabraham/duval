from pybind11.setup_helpers import Pybind11Extension
from setuptools import setup

ext_modules = [
    Pybind11Extension(
        "duval",
        ["duval_bind.cpp"],
        cxx_std=14,
        extra_compile_args=["-O3"],
    ),
]

setup(
    name="duval",
    version="0.0.1",
    author="Louis Abraham",
    author_email="louis.abraham@yahoo.fr",
    description="A module that implements the Duval algorithm.",
    ext_modules=ext_modules,
    zip_safe=False,
)
