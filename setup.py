from setuptools import setup, Extension

module = Extension('pysoc', sources=['source/pysoc.c'])

setup(
    name='pysoc',
    ext_modules=[module],
)