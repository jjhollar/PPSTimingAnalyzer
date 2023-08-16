# PPSTimingAnalyzer

---------------------------------------------------
Producing ntuples from AOD (tested in CMSSW_13_0_9)
 - Updated August 11, 2023 for 2023 Low-PU data
---------------------------------------------------

cmsrel CMSSW_13_0_9

cd CMSSW_13_0_9/src

cmsenv

git clone git@github.com:jjhollar/PPSTimingAnalyzer.git

git clone git@github.com:jjhollar/RecoPPS.git

scram b

cd PPSTimingAnalyzer/PPSTimingAnalyzer/test

cmsRun RunTimingAnalysis_cfg.py

   * By default, this does a re-RECO on-the-fly from the AOD, and keeps only events with 1 vertex.
     To change this to use the existing collections from the AOD, set "DORERECO = False". 
     To pick up new test calibrations from an sqlite file, see the comments in the cfg file

---------------------------------------------------
Macros for producing histograms and resolution fits
---------------------------------------------------

   * To run over the ntuples output by the step above, apply an event 
     selection similar to the 2018 timing studies (=1 low-multiplicity vertex in the CMS tracker, 
     and 1 proton track+timing measurement on each arm of PPS), and output histograms: 

cd CMSSW_13_0_9/src/PPSTimingAnalyzer/PPSTimingAnalyzer/macros

root -l TimingAnalysisMacro.C

[0] TimingAnalysisMacro t

[1] t.Loop()

   * The list of ntuples to run over is defined in TimingAnalysisMacro.h

   * A simple fitting macro used for 2018 studies can run on the histograms, and produce the vertex resolution 
     fit derived from the PPS timing measurements:

PPSTimingAnalyzer/PPSTimingAnalyzer/macros/FitSpaceResFromTiming.C

---------------------------------------------------
Notes
---------------------------------------------------

   * For commissioning, the macros are currently set up to work using local ("Lite") PPS tracks, rather than the full 
     proton object. The list of ntuples to run over is defined in TimingAnalysisMacro.h

   * Previously in 2022 the 220m pixel stations were ignored due to problems. Now the macro requires 
     pixel tracks in both 210+220. In order to go back to 2022 data, this should be changed. 

   * The macro now considers both cylindrical and box timing RPs. For the 2-arm selection, currently 
     the time difference is made separately for the combinations cylindrical-cylindrical and box-box. 
     When running on 2022 or older data, the box stations did not exist so these values will not be filled.     

   * In the fitting macro, all the initial values, ranges, and event-mixing background parameters are just copied 
     from 2018 and will need to be updated