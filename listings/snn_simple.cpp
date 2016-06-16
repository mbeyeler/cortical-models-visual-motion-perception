#include <carlsim.h>

int main(int argc, const char* argv[]) {
    // -------------------------------- CONFIG STATE --------------------------------- //
    CARLsim sim("basic", CPU_MODE, USER);

    Grid3D grpSize(10, 10, 5); // 10x10x5 neurons in each group
    PoissonRate in(nNeur.N);   // spike containter for SpikeGenerator group

    // create groups
    int gIn = sim.createSpikeGeneratorGroup("input", nNeur, EXCITATORY_NEURON);
    int gOut = sim.createGroup("output", nNeur, EXCITATORY_NEURON);
    sim.setNeuronParameters(gOut, 0.02f, 0.2f, -65.0f, 8.0f); // RS

    // connect input to output group
    sim.connect(gIn, gOut, "gaussian", RangeWeight(0.01f), 0.1f, RangeDelay(1, 20), 
        RadiusRF(3, 3, 3), SYN_FIXED);

    // enable COBA mode with default time decay constants
    sim.setConductances(true);

    // -------------------------------- SETUP STATE ---------------------------------- //
    sim.setupNetwork();
    sim.setSpikeMonitor(gOut, "DEFAULT");
    sim.setConnectionMonitor(gIn, gOut, "DEFAULT");

    // associate PoissonRate container with group gIn
    sim.setSpikeRate(gIn, &in);

    // ---------------------------------- RUN STATE ---------------------------------- //
    // run the network repeatedly for 1s (1*1000 + 0 ms) with different Poisson input
    for (int i=1; i<=10; ++i) {
        // update Poisson mean firing rate
        float inputRateHz = i * 10.0f;
        in.setRates(inputRateHz);

        // run for 1 second
        sim.runNetwork(1, 0);
    }

    return 0;
}