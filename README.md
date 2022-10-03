# PPSTimingAnalyzer

---------------------------------------------------
Producing ntuples from AOD (tested in CMSSW_12_4_6)
---------------------------------------------------

cmsrel CMSSW_12_4_6

cd CMSSW_12_4_6/src

cmsenv

git clone git@github.com:jjhollar/PPSTimingAnalyzer.git

git clone git@github.com:jjhollar/RecoPPS.git

scram b

cd PPSTimingAnalyzer/PPSTimingAnalyzer/test

cmsRun RunTimingAnalysis_cfg.py

   * By default, this does a re-RECO on-the-fly from the AOD, and keeps only events with 1 vertex.
     The re-RECO applies more recent time alignment corrections, and also performs the special 2-plane 
     pixel track reconstruction for the 220m stations. 
     To change this to use the existing collections from the AOD, see the comments in the cfg file.

---------------------------------------------------
Macros for producing histograms and resolution fits
---------------------------------------------------

   * To run over the ntuples output by the step above, apply an event 
     selection similar to the 2018 timing studies (=1 low-multiplicity vertex in the CMS tracker, 
     and 1 proton track+timing measurement on each arm of PPS), and output histograms: 

cd CMSSW_12_4_6/src/PPSTimingAnalyzer/PPSTimingAnalyzer/macros

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

   * For proton tracking, only the 210m pixel stations are considered by default in the macro.
     With the 2-plane tracking, the 220m pixels could also be included.

   * In the fitting macro, all the initial values, ranges, and event-mixing background parameters are just copied 
     from 2018 and will need to be updated