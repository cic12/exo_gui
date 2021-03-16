# Exoskeleton GUI

GUI and controller code template for exoskeleton control.

## Installation

A windows installation of Qt is required. The software has been developed using Desktop Qt 5.15.0 MSVC2019 64bit, so this installation is recommended. It can be downloaded [here](https://www.qt.io/download-qt-installer "Qt") and is free for open source development.

With Qt installed, the code in this repo should run straight away. The Qt project is loaded by opening the GUI.pro file.

## Usage

Before running the code, make sure you are connected to the HEBI X8-9 actuator using the Scope software.

To connect to the exoskeleton router use the network 'TP-Link_A196_5G'. The 5 GHz frequency drop packets much less often than the 2.4 GHz frequency because of the faster speed.

Recorded variables are saved as .txt files in the ./res/ directory. The HEBI actuator records a log of all available feedback variables and this is saved in the ./res/log directory.

To-do: .m file for viewing results
