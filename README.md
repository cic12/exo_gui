# Exoskeleton GUI

GUI and controller code template for exoskeleton control and EMG recording.

## Installation

A windows installation of Qt is required. The software has been developed using Desktop Qt 5.15.0 MSVC2019 64bit, so this installation is recommended. It can be downloaded [here](https://www.qt.io/download-qt-installer "Qt") and is free for open source development. With Qt installed, the code in this repo should build and run straight away. The Qt project is loaded by opening the GUI.pro file.

A PC driver is requed for the TMSi EMG amplifier to function. This is available with installation instructions [here](https://imperiallondon-my.sharepoint.com/:u:/g/personal/cic12_ic_ac_uk/ERn0UC_GgkpHgZjDrVl7K8YBFMaA9imkvKPAH6oOEbzsug?e=oDHNo9).

## Usage

Before running the code, make sure you are connected to the HEBI X8-9 actuator using the Scope software.

To connect to the exoskeleton router use the network 'TP-Link_A196_5G'. The 5 GHz frequency drop packets much less often than the 2.4 GHz frequency because of the faster speed.

The software can be used for the exoskeleton and EMG individually or for the two together. The default configuration is changed by setting the 'exo' and 'emg' variables to 1 or 0 for on/off in the testParams struct in line 9 of the 'controlThread.h' file. Here the maximum test time can also be changed.

Recorded variables are saved as .txt files in the ./results/ directory. The HEBI actuator records a log of all available feedback variables and this is saved in the ./results/log directory.

The save_data.m and plot_data.m MATLAB scripts save and display the exoskeleton and EMG variables recorded in the results directory. It is important the the data is saved for each test as the recordings are overwritten. The HEBI log files are saved uniquely for each test. These should be deleted regularly if not useful.
