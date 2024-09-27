# pysoc
Streamline packet building with pysoc python module.
## Deps
* Python Package Installer [Pip](https://pypi.org/project/pip/)
* C Compiler for [Windows](https://visualstudio.microsoft.com/visual-cpp-build-tools/) or [Linux](https://gcc.gnu.org)
## Download
```sh 
git clone https://github.com/nmentz/pysoc.git
```
## Install
When installing python modules, it is recommended to isolate your project within a [Virtual Environment](https://docs.python.org/3/tutorial/venv.html). If anything goes wrong, you can delete the virtual environment and restart. This is not required but encouraged.
> *Note:* Windows is pretty locked down by default and wants scripts to be self-signed or signed by a CA, so you may need to run ```Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser``` in your terminal to allow the venv script to execute without a signature. Alternatively, you can [sign it yourself](https://learn.microsoft.com/en-us/powershell/module/microsoft.powershell.core/about/about_signing?view=powershell-7.4).

Be aware of your python version. ```python --version``` will usually return a version of 3.x, but not always. 
- On Linux, what version ```/bin/python``` points to (3.x or 2.x) is dependent on the package manager that installed it. Run ```ls -Flash /bin/ | grep python``` to see your python versions.
- On Windows, installing python from the Microsoft Store is recommended as that will install a modern python version. Alternatively, you can use [choco](https://chocolatey.org/install).

If you are using python 2.x then you want to use ```pip```, and for python 3.x, you want ```pip3```. This guide demonstrates pysoc installation for python 3.x so it uses pip3.
```sh 
cd pysoc
python -m venv venv
```
The virtual environment has been created, you can now enter it with ```./venv/Scripts/activate``` on Windows or ```source ./venv/Scripts/activate``` on Linux. <br> Once you're in a venv, you can safely install pysoc and its dependencies.
```sh
pip3 cache purge
pip3 install build setuptools wheel
python -m build --verbose
```
Now under ```pysoc/dist/```, there will be a file with a ```.whl``` extension. Replace ```build_name``` with the name of this file.
```sh
pip3 install dist/build_name.whl
```
Verify the installation of pysoc within your venv.
```sh
pip3 show pysoc
```
## Examples
```sh
python ./pysoc/examples/tcp_packet.py
```
