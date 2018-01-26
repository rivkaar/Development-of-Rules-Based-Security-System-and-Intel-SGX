In order to enable decompilation with Retargble decompiler in this project,the following command must be done:

Install retdec-cpp library on windows with visual studio 2015:

- download and install Boost 1.59.0 and OpenSSL 1.0.2d (rename the installed directories to C:\Boost and
C:\OpenSSL-Win64):

        https://sourceforge.net/projects/boost/files/boost-binaries/1.59.0/boost_1_59_0-msvc-14.0-64.exe/download
        https://www.npcglib.org/~stathis/downloads/openssl-1.0.2d-vs2015.7z

 Note: The build does not yet work with Boost 1.66.0 or OpenSSL 1.1.


- clone retdec-cpp and run cmake:
	git clone https://github.com/s3rvac/retdec-cpp
	cd retdec-cpp
	mkdir build
	cd build
	cmake .. -G"Visual Studio 14 2015 Win64" -DCMAKE_INSTALL_PREFIX=install

- build and install the project via Visual Studio :
	* open the generated retdec-cpp.sln file. 
	* right-click on ALL_BUILD -> Build .
	* right-clicked on INSTALL -> Build.

  retdec-cpp should now be installed in retdec-cpp/build/install.