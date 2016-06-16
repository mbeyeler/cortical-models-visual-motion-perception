// ------------------------------------ RUN STATE ------------------------------------ //
// associate PoissonRate container with group gIn
PoissonRate poissonIn(nNeur.N);
sim.setSpikeRate(gIn, &poissonIn);

// run the network repeatedly for 1s (1*1000 + 0 ms) with different Poisson input
for (int i=1; i<=10; ++i) {
    // update Poisson mean firing rate
    float inputRateHz = i * 10.0f;
    poissonIn.setRates(inputRateHz);

    // run for 1 second, record spikes
    spkOut->startRecording();
    sim.runNetwork(1, 0);
    spkOut->stopRecording();
    
    // print summary of spike information
    spkOut->print();
    
    // return the percent of neurons with firing rates from 0 to 5 Hz
    spikeMon->getPercentNeuronsWithFiringRate(0.0, 5.0);
}