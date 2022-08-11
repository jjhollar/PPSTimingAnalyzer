# PPSTimingAnalyzer

---------------------------------------------------
Producing ntuples from AOD (tested in CMSSW_12_4_6)
---------------------------------------------------

cmsrel CMSSW_12_4_6

cd CMSSW_12_4_6/src

cmsrel

git clone git@github.com:jjhollar/PPSTimingAnalyzer.git

cd PPSTimingAnalyzer

scram b

cd PPSTimingAnalyzer/PPSTimingAnalyzer/test

cmsRun RunTimingAnalysis_cfg.py

   * By default, this runs on existing collections from the AOD, and keeps only events with 1 vertex. 
     To change this to re-RECO on-the-fly from the AOD, see the comments in the cfg file.

---------------------------------------------------
Macros for producing plots and resolution fits
---------------------------------------------------

   * To run over the ntuples output by the step above, apply an event 
     selection similar to the 2018 timing studies, and output histograms: 

cd CMSSW_12_4_6/src/PPSTimingAnalyzer/PPSTimingAnalyzer/macros

root -l TimingAnalysisMacro.C

[0] TimingAnalysisMacro t

[1] t.Loop()

   * For commissioning, this is temporarily set to work using local ("Lite") PPS tracks, rather than the full 
     proton object. The list of ntuples to run over is defined in TimingAnalysisMacro.h

   * Finally, a simple fitting macro can run on the histograms, and produce a vertex resolution based 
     on the timing measurements: 

PPSTimingAnalyzer/PPSTimingAnalyzer/macros/FitSpaceResFromTiming.C  
