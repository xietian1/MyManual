# Steps to Install srsLTE

##Command that may be used
* **Git Command**  
    ```
    #see all branch
  git branch -v -a
  
  #switch to commit/branch
  git checkout ***
  
  #check current branch
  git status
  
  #reset to one commit
  git reset --hard ****(commit hash value)
    ```   

* ***Git Command to push file***
    ```
  git add .
  git commit -a -m "message"
  git push origin HEAD:branchname (-f)
    ```


* **Change CPU Frequency:**  
    Performance Mode:  
    ```
    echo 'GOVERNOR="performance"' | sudo tee /etc/default/cpufrequtils
    ```  
    Powersave Mode:  
    ```
    echo 'GOVERNOR="powersave"' | sudo tee /etc/default/cpufrequtils
    ```  
    Restart Service:  
    ```
    sudo /etc/init.d/cpufrequtils restart
    ```  
* **Check CPU Frequency:**  
    ```
    lscpu | grep MHz
    ```  
* **Config Installation:**  
    ```
    sudo ldconfig
    ```  
    
    
##Install srsLTE  

* Update dependencies:
    ```
    sudo apt update
    sudo apt upgrade  //It should take a while on a fresh Ubuntu 16.04 system
    ```

* Install simcard dependencies:  
    ```
    sudo apt-get install pcscd pcsc-tools libccid libpcsclite-dev python-pyscard
    ```  
    
* Install python `requests` module:  
    ```
    sudo apt install python-pip
    sudo pip install requests
    ```
  
* Install UHD:  
    ```
    sudo apt-get install libboost-all-dev libusb-1.0-0-dev python-cheetah doxygen python-docutils g++ cmake python-setuptools python-mako
    git clone https://github.com/EttusResearch/uhd
    cd uhd 
    git checkout release_003_009_007 //We use 3.9.7 TLS version
    cd host
    mkdir build
    cd build
    cmake ../
    make -j8
    make test
    sudo make install
    sudo ldconfig
    sudo uhd_images_downloader //Download the UHD 
    ```
    
* Test UHD Installation:  
    Note that the USRP need to be connected to the desktop here.  
    ```
    sudo uhd_find_devices
    ```
    
* Install srsLTE
    ```
    sudo apt-get install cmake libfftw3-dev libmbedtls-dev libboost-program-options-dev libconfig++-dev libsctp-dev
    
    //git clone the right version
    git clone https://github.com/xietian1/SRSLTE.git
    cd SRSLTE
    git fetch
    git checkout /remotes/origin/master 
    
    mkdir build
    cd build
    cmake ../
    make -j8
    make test 
    
    sudo make install
  sudo ldconfig
    
  (option) srslte_install_configs.sh user // I usually dont't use it.
    ```



##Uninstall srsLTE
Locate the srsLTE folder first.  
    
    
    cd srsLTE/build/
    sudo make uninstall
    