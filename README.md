## "Network Programming" repo.

NOTE: This code works ONLY with Linux an macOS. There is no support for Windows.

### HOW-TO setup your system
Compiler: be sure to have at least g++ 5.4 or a newer version. 
(You can check by typing in your shell `g++ -v`.)
Install the following packages, by typing in your shell:
* if Debian-based, such as (X/K)Ubuntu, Mint, ect:
```
sudo apt-get install build-essential autoconf automake libxmu-dev libx11-dev libxmu-dev libxmu-headers libxt-dev libtool
```
* if Red-Hat-based (Fedora, CentOS):
```
dnf groupinstall "C Development Tools and Libraries"
dnf install gcc-fortran libXmu-devel libX11-devel patch patchutils
``` 
* if on macOS, you need something like `brew` and Xcode (see [this guide](https://paolozaino.wordpress.com/2015/05/05/how-to-install-and-use-autotools-on-mac-os-x/) for more details). Then run
```
brew install autoconf
brew install automake
brew install libtool
```

### HOW-TO get and compile the code:
* open a shell
* clone the Github repo (with HTTPS) by typing:
```
git clone https://github.com/neu-eece-5698-network-programming/homework.git
```
* go to the installer directory, by typing:
```
cd network-programming/autotools-structure/
```
* install the code, by typing:
```
./installer.sh -p /tmp -t 1
```
You can substitute /tmp with a folder of your choice, e.g., your home folder. You need an absolute path.


### Advanced usage

Notes on the installer:
* the `installer.sh` script is provided with the following options:
	```
	OPTIONS:
	   -h    Show this message
	   -p    Prefix Path
	   -t    Test enable (1) or disable (0, default)
	   -c    clean repository
	```

Notes on GIT:

* HOWTO clone the repo (with HTTPS):
```
git clone https://github.com/neu-eece-5698-network-programming/homework.git
```
Please do not push on this repo.
