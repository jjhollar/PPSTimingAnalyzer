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