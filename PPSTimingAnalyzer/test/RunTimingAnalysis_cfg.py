
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




process.source = cms.Source ("PoolSource",
                             fileNames = cms.untracked.vstring(
                                 'file:/eos/cms/tier0/store/data/Run2022C/EphemeralZeroBias7/AOD/PromptReco-v1/000/355/933/00000/0456dc66-6b77-4776-9920-06391c894166.root',
                                 'file:/eos/cms/tier0/store/data/Run2022C/EphemeralZeroBias7/AOD/PromptReco-v1/000/355/933/00000/30a9992f-ee6a-45f3-95e7-09c727ee2d2e.root',
                                 'file:/eos/cms/tier0/store/data/Run2022C/EphemeralZeroBias7/AOD/PromptReco-v1/000/355/933/00000/3dc0d11c-a7ad-425c-8ac3-7fe0a85ddaaa.root',
                                 'file:/eos/cms/tier0/store/data/Run2022C/EphemeralZeroBias7/AOD/PromptReco-v1/000/355/933/00000/4000fdc0-e6da-4f57-a697-d31e3e1205df.root',
                                 'file:/eos/cms/tier0/store/data/Run2022C/EphemeralZeroBias7/AOD/PromptReco-v1/000/355/933/00000/47d78202-01ef-47ae-80c4-b3dacfdedae3.root',
                                 'file:/eos/cms/tier0/store/data/Run2022C/EphemeralZeroBias7/AOD/PromptReco-v1/000/355/933/00000/56c41701-31c1-4891-b02c-0d686b18deb7.root',
                                 'file:/eos/cms/tier0/store/data/Run2022C/EphemeralZeroBias7/AOD/PromptReco-v1/000/355/933/00000/7704b9c8-49c3-437b-a76f-aef10bf502c7.root',
                                 'file:/eos/cms/tier0/store/data/Run2022C/EphemeralZeroBias7/AOD/PromptReco-v1/000/355/933/00000/7c2bba95-e2de-4555-b924-cf1917bbb248.root',
                                 'file:/eos/cms/tier0/store/data/Run2022C/EphemeralZeroBias7/AOD/PromptReco-v1/000/355/933/00000/839f2f89-db12-41f6-b8ed-84be41e994d1.root',
                                 'file:/eos/cms/tier0/store/data/Run2022C/EphemeralZeroBias7/AOD/PromptReco-v1/000/355/933/00000/84f26a48-3151-4f74-9ff7-428fa6732670.root',
                                 'file:/eos/cms/tier0/store/data/Run2022C/EphemeralZeroBias7/AOD/PromptReco-v1/000/355/933/00000/883aa5f9-e5f9-4636-85e7-73c19b9f4b87.root',
                                 'file:/eos/cms/tier0/store/data/Run2022C/EphemeralZeroBias7/AOD/PromptReco-v1/000/355/933/00000/8dde7df2-888c-4962-b671-1339bfddf4e8.root',
                                 'file:/eos/cms/tier0/store/data/Run2022C/EphemeralZeroBias7/AOD/PromptReco-v1/000/355/933/00000/8f56d362-f7e7-401c-a14b-79fa14028c6f.root',
                                 'file:/eos/cms/tier0/store/data/Run2022C/EphemeralZeroBias7/AOD/PromptReco-v1/000/355/933/00000/b9d431cb-c683-46a2-bf4d-bd64cab89251.root',
                                 'file:/eos/cms/tier0/store/data/Run2022C/EphemeralZeroBias7/AOD/PromptReco-v1/000/355/933/00000/ba0872c1-8a24-4257-8e21-4f2a2fced27a.root',
                                 'file:/eos/cms/tier0/store/data/Run2022C/EphemeralZeroBias7/AOD/PromptReco-v1/000/355/933/00000/d901b2b4-ee54-443a-acbe-a29135c45478.root',
                                 'file:/eos/cms/tier0/store/data/Run2022C/EphemeralZeroBias7/AOD/PromptReco-v1/000/355/933/00000/e9683227-f9eb-49cb-9c7f-e54df62e5e4c.root',
                                 'file:/eos/cms/tier0/store/data/Run2022C/EphemeralZeroBias7/AOD/PromptReco-v1/000/355/933/00000/ede1f200-bbf1-45fe-b5e1-fedafac96466.root',
                                 'file:/eos/cms/tier0/store/data/Run2022C/EphemeralZeroBias7/AOD/PromptReco-v1/000/355/933/00000/f18ade9e-a251-4655-961b-dca5f6f2d5a8.root',
                                 'file:/eos/cms/tier0/store/data/Run2022C/EphemeralZeroBias7/AOD/PromptReco-v1/000/355/933/00000/f94939f0-16cb-4627-978b-cde4d6f6ec0e.root',
                                 'file:/eos/cms/tier0/store/data/Run2022C/EphemeralZeroBias7/AOD/PromptReco-v1/000/355/933/00000/f94b2c62-7b13-4531-98c3-b0d27c3b68c9.root'

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
    maxVertices = cms.uint32(1),
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

