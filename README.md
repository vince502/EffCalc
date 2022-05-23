Efficiency Calculator for run3 muon trigger kinematic derivatives.
The EffCalc class, defined in `EffCalc.h` which wraps the Oniatree and HLT bitanalyzer output reader (defined in `Reader.h`) as a single trigger efficiency calculator. The `calculateEff.C` macro shows how to input multipple triggers simulteneously by mapping to multithread worker,

```bash
root -l -b -q 'calculateEff.C'
```

The `calculateHLT.C` macro fills the efficiency code and one can extract the counts by calling the `GetPassedHistogram()` of that object. 
