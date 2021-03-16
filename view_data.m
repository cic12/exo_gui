clear;clc

% Import data
aivec = readmatrix('results/aivec.txt'); % Raw analog EMG signals (2048 Hz)
emg = readmatrix('results/emg.txt'); % Processed EMG signals (500 Hz)
tvec = readmatrix('results/tvec.txt'); % Time (s)
udes = readmatrix('results/udes.txt'); % Demanded control input torque (Nm)
uvec = readmatrix('results/uvec.txt'); % Measured joint torque (Nm)
xdes = readmatrix('results/xdesvec.txt'); % Desired joint position (rad)
xvec = readmatrix('results/xvec.txt'); % Measured joint position (rad)
hebi_quat = readmatrix('results/hebi_quat.txt'); % Actuator (thigh) orientation quaternion

% Label and save if test name is not blank
timestamp = datestr(now,'yyyy-mm-dd_HH.MM.SS');
activity = input('Test name (leave blank to view results without saving): ','s');
if ~isequal(activity,'')
    save(strcat('data/','data_file_',timestamp,'_',activity,'.mat'))
end

% Display data
plot_data