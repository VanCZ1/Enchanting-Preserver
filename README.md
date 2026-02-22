# Enchanting-Preserver
An SKSE plugin that allows players to learn enchantments without destroying items.  
Built with [CommonLibSSE-NG](https://github.com/alandtse/CommonLibVR).

# Requirements
* [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
	* Desktop development with C++
* [CMake](https://cmake.org/)
	* Add to your `PATH`
* [vcpkg](https://github.com/microsoft/vcpkg)
	1. Clone the repository
	2. Run `bootstrap-vcpkg.bat` in the `vcpkg` folder
	3. Add a system environment variable:
		* Name: `VCPKG_ROOT`
		* Value: path to your `vcpkg` folder

# Building
```
git clone https://github.com/VanCZ1/Enchanting-Preserver.git
cd Enchanting-Preserver
git submodule update --init --recursive
```

```
cmake --preset release-msvc
cmake --build --preset release-msvc
```

# Credits
Thanks to SKSE team and the open source community.  
Some of the files in the project references the following authors:
* [powerof3](https://github.com/powerof3)
* [Monitor221hz](https://github.com/Monitor221hz)
* [QTR-Modding](https://github.com/QTR-Modding)
* [elzart](https://github.com/elzart)
