# Exoskeleton/EMG GUI

GUI and code template for exoskeleton control and EMG recording.

## Installation

A windows installation of Qt is required. The software has been developed using Desktop Qt 5.15.0 MSVC2019 64bit, so this installation is recommended. It can be downloaded [here](https://www.qt.io/download-qt-installer "Qt") and is free for open source development. With Qt installed, the code in this repo should build and run straight away. The Qt project is loaded by opening the GUI.pro file in the ./GUI directory.

A PC driver is required for the TMSi EMG amplifier. This is available with installation instructions [here](https://imperiallondon-my.sharepoint.com/:u:/g/personal/cic12_ic_ac_uk/ERn0UC_GgkpHgZjDrVl7K8YBFMaA9imkvKPAH6oOEbzsug?e=oDHNo9 "PC Driver").

## Usage

Before running the code, make sure the HEBI X8-9 actuator is connected using the Scope software. To connect the exoskeleton router use the network 'TP-Link_A196_5G'. The 5 GHz frequency drops fewer packets than the 2.4 GHz frequency.

The software can be used for the exoskeleton and EMG individually or together and this cen be set using checkboxes in the GUI. The default configuration is changed by setting the 'exo' and 'emg' variables to 1 or 0 for on/off in the testParams struct in line 9 of 'controlThread.h'. The maximum test time can also be changed here. To introduce a delay before recording begins, The Sleep() duration (in ms) can be changed in the run() function of the ControlThread class in controlThread.cpp. The control_loop() function in this class is where the control loop executes and the trajectory/control input can be programmed.

Recorded variables are saved as .txt files in the ./results/ directory. The HEBI actuator records a log of all available feedback variables and this is saved in the ./results/log directory.

The save_data.m and plot_data.m MATLAB scripts save and display the exoskeleton and EMG variables recorded in the results directory. It is important the the data is saved for each test as the recordings are overwritten. The HEBI log files are saved uniquely for each test. These should be deleted regularly if not useful.
