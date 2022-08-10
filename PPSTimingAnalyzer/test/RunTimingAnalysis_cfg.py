
import FWCore.ParameterSet.Config as cms
import copy

process = cms.Process('PPSTiming')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 1000



#process.source = cms.Source("EmptyIOVSource",
#    timetype = cms.string('runnumber'),
#    firstValue = cms.uint64(1),
#    lastValue = cms.uint64(1),
#    interval = cms.uint64(1)
#)

process.source = cms.Source ("PoolSource",
                             fileNames = cms.untracked.vstring(
                                 'file:/eos/cms/tier0/store/data/Run2022C/EphemeralZeroBias7/AOD/PromptReco-v1/000/355/933/00000/f94939f0-16cb-4627-978b-cde4d6f6ec0e.root'
        )
                             )

process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
# 2022 prompt: to be updated
process.GlobalTag = GlobalTag(process.GlobalTag, "124X_dataRun3_Prompt_v4") 

# local RP reconstruction chain with standard settings                                                                                              

process.mydiamonds = cms.EDAnalyzer(
    'PPSTimingAnalyzer',
    tagDiamondRecHits = cms.InputTag("ctppsDiamondRecHits"),
#    lhcInfoLabel = cms.string(''),
    verticesTag = cms.InputTag('offlinePrimaryVertices'),
    tracksTag = cms.InputTag('generalTracks'),
    tagTrackLites = cms.InputTag( "ctppsLocalTrackLiteProducer"),
    ppsRecoProtonSingleRPTag = cms.InputTag("ctppsProtons", "singleRP"),
    ppsRecoProtonMultiRPTag = cms.InputTag("ctppsProtons", "multiRP"),
    maxVertices = cms.uint32(10),
    outfilename = cms.untracked.string( "output_ZeroBias.root" )
)

# Trigger                                                                                                                  
from HLTrigger.HLTfilters.hltHighLevel_cfi import *
process.hltFilter = copy.deepcopy(hltHighLevel)
process.hltFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
process.hltFilter.HLTPaths = ['HLT_EphemeralZeroBias_*']

process.ALL = cms.Path(
#   for data:
    process.hltFilter * 
    process.mydiamonds 
                       )

process.schedule = cms.Schedule(process.ALL)

