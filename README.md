# 221e MULTISENSOR INERTIAL CHAMALEON V2 DRIVER FOR ROS

The official ROS driver for the 221e Multisensor InerTial CHamaleon (MITCH) V2 device.

Package available for:
- ROS Noetic - Ubuntu 20.04;
- ROS Noetic - Windows 10.

## 1 - Installation

***Step 1 : Install the ROS distribution***

a) Ubuntu: 
- Install [ROS Noetic](http://wiki.ros.org/noetic/Installation/Ubuntu) on [Ubuntu 20.04](https://www.ubuntu-it.org/download);

b) Windows: 
- Install [ROS Noetic](https://wiki.ros.org/Installation/Windows) on Windows 10;

If you are exploiting Windows, we assume you are using [Microsoft Visual Studio 2019](https://docs.microsoft.com/en-us/visualstudio/releases/2019/release-notes). Remember to
- include the "Desktop development with C++" workload;
- in the Individual Components, select "Windows 10 SDK". 

Moreover, remember to start your installation routine from the ROS command short cut.

***Step 2: Install lib221e***

lib221e is the C++ library for the 221e Communication Protocol. Follow the installation instructions available [here](https://github.com/221eROS/lib221e.git).

You can use git from Command Line. Otherwise, several free and commercial GUI tools are available. E.g., for the Windows platform, you can download a GUI from [here](https://www.git-scm.com/downloads/guis).

In the same way, in Windows, you can install your library via [Visual Studio](https://visualstudio.microsoft.com/it/downloads/) [installed in step 1(b)]. A possible installation procedure follows:
- open Visual Studio with administrator privileges;
- choose to open up your library from your local folder;
- open the ```Developer Command Prompt``` from ```Visual Studio-->Tools-->Command Line```;
- launch ```cmake ..```;
- launch ```cmake --build . --target INSTALL --config Release```.


***Step 3 : Create a [Catkin](http://wiki.ros.org/catkin#Installing_catkin) Workspace***

a) Ubuntu:

Open a terminal. From the ```home``` directory:

```sh
$ mkdir -p ~/catkin_ws/src
$ cd ~/catkin_ws/
$ catkin_init_workspace
$ echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc
$ source ~/.bashrc
```
Other details are available [here](http://wiki.ros.org/catkin/Tutorials/create_a_workspace).

b) Windows:

Open your ROS short cut terminal. In your ```c:\``` directory:

```sh
$ mkdir c:\catkin_ws\src
$ cd c:\catkin_ws
$ catkin_make
$ devel\setup.bat
```
Other details are available [here](https://github.com/Brabalawuka/RosOnWindows).

You can decide to locate your workspace in other directories.

If you need the Ninja build tool, go to the [releases page](https://github.com/ninja-build/ninja/releases) and download a suitable binary for Windows. Place ```ninja.exe``` in a suitable spot, e.g., ```C:\Ninja```. Make sure that CMake can find ```ninja.exe``` by adding ```C:\Ninja``` to your ```%PATH%```.

***Step 4: Clone mitch_v2_driver in your Catkin Workspace

a) Ubuntu:
```sh
$ cd ~/catkin_ws/src/
$ git clone https://github.com/221eROS/mitch_v2_driver.git
$ catkin_make
```

b) Windows:
```sh
$ cd c:\catkin_ws\src
$ git clone https://github.com/221eROS/mitch_v2_driver.git
$ cd ..
$ catkin_make
```
## 2 - ROS for Windows: additional tips for Visual Studio 2019 [No mandatory!]

- We suppose you have already installed Visual Studio 2019in step 1(b);
- From the ROS shortcut of Step 1(b), enter ```devenv``` to start your Visual Studio IDE; 
- Choose to open up your catkin workspace from your local folder;
- As Visual Studio is using different settings for CMake projects, we need to configure the CMake file. Thus, click ```Project --> CMake Settings for Project``` and edit the JSON version of your Cmake settings file as follows:

```sh
{
  "configurations": [
    {
      "name": "x64-Debug",
      "generator": "Ninja",
      "configurationType": "RelWithDebInfo",
      "inheritEnvironments": [ "msvc_x64_x64" ],
      "buildRoot": "C:\\catkin_ws\\build",
      "installRoot": "C:\\catkin_ws\\install",
      "cmakeCommandArgs": "DCATKIN_DEVEL_PREFIX=C:\\catkin_ws\\devel",
      "ctestCommandArgs": ""
    }
  ]
}
```
In this way, Cmaking and building your project from Visual Studio will be equal to a catkin_make outside the Visual Studio environment. 
You can also open the Command Line directly from the Visual Studio ```Tools``` button.

## 3 - Usage 

### a) Device connection
Switch on your MITCH V2 device. From your catkin workspace, launch the following command to connect to your sensor and enable its ROS node:
```sh
$ roslaunch mitch_v2_driver mitch_v2.launch
```
Among others, this launch file allows you to set:
- port name (Default: COM4);
- baudrate (Default: 115200).

### b) Device shutdown
Assuming the ROS node of your MITCH V2 sensor is active [step 3(a)], launch the following command to switch off your device:
```sh
$ roslaunch mitch_v2_driver shutdown.launch
```

### c) Battery charge and voltage

Assuming the ROS node of your MITCH V2 sensor is active [step 3(a)], type the following command from your catkin workspace:
```sh
$ roslaunch v battery.launch
```
The node will send back the battery charge, its voltage, or both depending on whether the arguments *charge* and *voltage* are set to *true*.


