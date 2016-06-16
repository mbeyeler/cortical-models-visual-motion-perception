// ---------------------------------- SETUP STATE ------------------------------------ //
sim.setupNetwork();
SpikeMonitor* spkOut = sim.setSpikeMonitor(gOut, "DEFAULT");
sim.setConnectionMonitor(gIn, gOut, "DEFAULT");