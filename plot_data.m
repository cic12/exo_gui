% Script displays data loaded from the data directory
h = figure(1);clf
t = tiledlayout('flow');
t.TileSpacing = 'none';
t.Padding = 'none';

nexttile
hold on
plot(tvec,xvec);
plot(tvec,xdes);
legend theta theta_{des}
title 'exo position'

nexttile
hold on
plot(tvec,uvec);
plot(tvec,udes);
legend tau_e tau_{e,cmd}
title 'exo torque'

nexttile
hold on
plot(tvec,hebi_quat);
ylim([-1 1])
title 'hebi quat'
legend qw qx qy qz

nexttile
hold on
plot(tvec,emg);
title 'emg signal'
legend e1 e2 e3 e4

nexttile
hold on
plot(aivec);
title 'analog in (2048 Hz)'
legend ai1 ai2 ai3 ai4