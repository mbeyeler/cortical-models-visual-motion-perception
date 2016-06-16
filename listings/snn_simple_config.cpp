#include <carlsim.h>

// ---------------------------------- CONFIG STATE ----------------------------------- //
CARLsim sim("basic", CPU_MODE, USER);

// create groups
Grid3D grpSize(10, 10, 5); // 10x10x5 neurons in each group
int gIn = sim.createSpikeGeneratorGroup("input", nNeur, EXCITATORY_NEURON);
int gOut = sim.createGroup("output", nNeur, EXCITATORY_NEURON);
sim.setNeuronParameters(gOut, 0.02f, 0.2f, -65.0f, 8.0f); // RS

// connect input to output group
sim.connect(gIn, gOut, "gaussian", RangeWeight(0.01f), 0.1f, RangeDelay(1, 20), 
    RadiusRF(3, 3, 3), SYN_PLASTIC);

// enable STDP on all incoming synapses to gExc
float alphaPlus = 0.1f, tauPlus = 20.0f, alphaMinus = 0.1f, tauMinus = 20.0f;
sim.setESTDP(gOut, true, STANDARD, ExpCurve(alphaPlus, tauPlus, -alphaMinus, tauMinus));

// disable conductances to run CUBA mode
sim.setConductances(false);