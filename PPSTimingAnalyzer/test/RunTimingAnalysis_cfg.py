
import FWCore.ParameterSet.Config as cms
import copy

DORERECO = True

process = cms.Process('PPSTiming2')

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
#'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/95f508b2-40fc-442f-b30f-e26314655a8f.root'

'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/95f508b2-40fc-442f-b30f-e26314655a8f.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/b42c0bf4-1453-4f15-ae8c-bb105f39da4d.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/d513852b-6948-4b9c-8cd7-ee4039a8c222.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/d844d655-05b2-4a4f-bac3-291c10f42d67.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/bbf4af17-3303-478f-964b-82ef32b4a5c5.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/99c30c4a-44ee-4afb-a75f-386bfd5e90b5.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/5687b22f-144b-4510-b4aa-b962a57d2b5f.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/b6251b1b-124f-4c0a-8db6-293ea112b96e.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/bc7c3354-2bb4-4641-a6eb-c5342f909957.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/3e8aa496-2c5b-4ea2-8595-9566bade9d8c.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/565d687a-964a-486a-b07c-dfd9d858036b.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/aebe9496-cef7-4c01-bc08-dd620a9a2ce1.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/563253b2-9256-4b65-98fb-f85b8fe46b82.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/d4cb41ca-b84d-4144-8a17-74740fc18d03.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/909e6533-3efa-4a9d-9547-880aeda438e4.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/0846557a-955d-4070-bc4e-36df8cad0793.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/f3551306-9ff0-4f32-b8d4-f9ed7c6058d2.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/90abfdb2-6260-415e-af30-a963aa67e04f.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/046d8f86-bcb6-491c-9045-7cf7188ebfef.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/54c91fbf-8693-4800-b90c-29d5b98faaeb.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/cbfa2fbf-f76a-48da-8534-4360eb2fbe6f.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/7506853c-3169-406b-8e00-bbceac134ac0.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/b5d2019b-55ad-4b42-aefe-14a20b63219d.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/9266909b-206c-4212-97e8-a79b5d2c196a.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/55f8780e-4e9a-4e28-9fe1-9552fa4c8012.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/77885c0e-7711-4f08-ac2f-dc29375706f0.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/1dfec166-4165-4af0-aede-1fe8f0001617.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/b9c24471-9b97-426a-836d-3b567ebda60e.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/5872463f-8f3d-4ef9-b1a0-dab89c272938.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/246d7569-49d7-4209-974a-8b457acdb094.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/f0c4a34e-64f6-4004-a3d3-b5fc6f9c1d85.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/f479f941-c626-4454-81ad-93335106cca2.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/cc7195eb-f24b-422c-9e81-b273cf9f61ac.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/74183ab2-13fd-4dbb-90dc-34a4b208f7b8.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/2d602a99-45db-47be-98a8-7bd76647a876.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/24062f0e-5ba4-433f-882b-0ca28caacf9a.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/e627e8c9-1bf0-418c-8054-537aeb3a9f4b.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/606ddc48-0c6d-4b0a-a068-e087ad2e9c3d.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/26305b2a-bfb1-4c68-944c-d9767eb3949a.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/1e809732-2d78-4dcb-8d79-807507719137.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/8444f2b9-7ebb-4b92-ab74-6ccb33e2719a.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/becb9a1a-057d-4da7-b09b-d6c8c76d5902.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/69ab151e-a951-4914-b52a-fea043104a9d.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/71553e99-602e-4d87-9663-6dc5ecd42360.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/98dafe93-9a11-4267-9a51-4bea52c38389.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/bbfad9ee-df34-4630-86c7-f1d03ca4fd63.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/b1b08f9f-5cff-4cae-8599-8fd76aae4569.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/d3538270-cd7a-420e-b9a5-ad5648943e40.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/ca98338d-4f75-44ea-8528-8c0de89a5416.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/57f3703a-87d0-4875-a549-ef60c15b4a2b.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/9644b3b6-91e9-4b4e-b4f8-04f6b6acc181.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/37acf311-5c7a-402e-830f-fcaf1734f1e0.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/dab58bf9-1ead-4960-9163-857b27ee7ea2.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/caf95217-e134-4472-8255-ac64704594a8.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/d76c98ad-e19e-4005-9d4c-d384edc382f6.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/66468654-0b7d-4173-a887-bd1d66b4de58.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/1c1273c1-d0f1-4699-94bb-ee656f328aca.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/983a2d88-969c-4ae7-8a5a-e5dd594f45f3.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/8efd862c-e988-41fd-9c15-afc5ce5bc3bb.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/c4617403-3695-424d-8eff-f008524f043d.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/50e7a951-b36b-4f59-b802-619de23218af.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/9a93f615-85d9-450c-b894-2c089ee8aa3c.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/d3afacf6-343d-4c9f-8680-4b3c4e7a3590.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/42e582d5-b242-4235-83f8-4eeaa6ca4d99.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/d28713c3-1f85-40ea-9335-74f9485e2b87.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/bc9b25a1-e4e6-4a47-970b-6a1f5699049a.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/574dbd17-3db6-4f6e-a293-79638e7bde1a.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/8ffeaa4e-18e3-40f8-9e50-58d544c4b580.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/0417b990-5d80-4cf0-bffd-1ac66fde9782.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/5085c2cd-b53a-429d-a861-838601f4c6f5.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/5cf822b7-24ce-41c9-9df1-3dc2a511cf4a.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/2520000/51313cb2-d18d-493a-81eb-e4ab31c2b800.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/30000/810227f3-bc50-43a5-9f8d-f9618e20a7a2.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/410000/6e4e2df9-0f14-4815-b30e-55e34d9074e4.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/410000/5fefda5c-5eb0-4b4e-991d-13d876ee96bf.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/410000/24e0a0b2-6bcc-41ff-8e60-d4318c2b2408.root',
'/store/data/Run2023D/SpecialZeroBias2/AOD/19Jul2023-v1/410000/c85d392d-092c-4f37-9f73-df2905d1536a.root'
                        )
)


# Copied from https://github.com/cms-sw/cmssw/blob/master/CalibPPS/TimingCalibration/test/DiamondCalibrationWorker_cfg.py#L23-34
# Attempting to pickup new time-walk calibrations from sqlite file, for on-the-fly re-reco
if DORERECO == True:
    process.load('Configuration.StandardSequences.Services_cff')
    process.load('Configuration.EventContent.EventContent_cff')
    process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
    from Configuration.AlCa.GlobalTag import GlobalTag
    from Configuration.AlCa.autoCond import autoCond
    process.GlobalTag = GlobalTag(process.GlobalTag, autoCond['run3_data_prompt'], '')
    #process.GlobalTag.globaltag = '126X_dataRun3_v2'
    process.load("EventFilter.CTPPSRawToDigi.ctppsRawToDigi_cff")
    process.load("RecoPPS.Configuration.recoCTPPS_cff")

    process.load('CondCore.CondDB.CondDB_cfi')
    process.CondDB.connect = 'sqlite_file:ppsDiamondTiming_calibration369956.sqlite' # SQLite input
    process.PoolDBESSource = cms.ESSource('PoolDBESSource',
                                          process.CondDB,
                                          DumpStats = cms.untracked.bool(True),
                                          toGet = cms.VPSet(
                                              cms.PSet(
                                                  record = cms.string('PPSTimingCalibrationRcd'),
                                                  tag = cms.string('DiamondTimingCalibration')
                                              )
                                          )
                                      )


# JH - rerun reco sequence with new timing calibrations, using empty tag according to Chris+Giovanni
if DORERECO == True:
    process.load("RecoPPS.Configuration.recoCTPPS_cff")
    process.ctppsDiamondRecHits.timingCalibrationTag = ("")

# JH - for rerunning reco, specify the new collections are used everywhere
if DORERECO == True:
    process.ctppsDiamondLocalTracks.recHitsTag = cms.InputTag("ctppsDiamondRecHits","","PPSTiming2")
    process.ctppsLocalTrackLiteProducer.tagDiamondTrack = cms.InputTag("ctppsDiamondLocalTracks","","PPSTiming2")
    process.ctppsProtons.tagLocalTrackLite = cms.InputTag("ctppsLocalTrackLiteProducer","","PPSTiming2")
    process.ctppsLocalTrackLiteProducer.includeDiamonds = cms.bool(True)
    process.ctppsLocalTrackLiteProducer.includePixels = cms.bool(True)

if DORERECO == True:
    process.mydiamonds = cms.EDAnalyzer(
        'PPSTimingAnalyzer',
        #    lhcInfoLabel = cms.string(''),
        verticesTag = cms.InputTag('offlinePrimaryVertices'),
        tracksTag = cms.InputTag('generalTracks'),
        # Take PPS information from on-the-fly re-RECO
        #
        tagDiamondRecHits = cms.InputTag("ctppsDiamondRecHits","","PPSTiming2"),                                               
        tagTrackLites = cms.InputTag( "ctppsLocalTrackLiteProducer", "", "PPSTiming2"), 
        ppsRecoProtonSingleRPTag = cms.InputTag("ctppsProtons", "singleRP", "PPSTiming2"),
        ppsRecoProtonMultiRPTag = cms.InputTag("ctppsProtons", "multiRP", "PPSTiming2"),
        maxVertices = cms.uint32(1),
        outfilename = cms.untracked.string( "output_ZeroBias.root" )
    )
else:
    process.mydiamonds = cms.EDAnalyzer(
        'PPSTimingAnalyzer',
        #    lhcInfoLabel = cms.string(''),                                                                                                                                       
        verticesTag = cms.InputTag('offlinePrimaryVertices'),
        tracksTag = cms.InputTag('generalTracks'),
        # Take PPS information from the existing Prompt RECO AOD                                                                                                                  
        #                                                                                                                                                                         
        tagDiamondRecHits = cms.InputTag("ctppsDiamondRecHits"),                                                                                                                  
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

if DORERECO == True:
    process.ALL = cms.Path(
        process.hltFilter * 
        # Re-run the PPS local+proton timing reconstruction starting from AOD
        process.ctppsDiamondRecHits *
        process.ctppsDiamondLocalTracks *
        process.ctppsPixelLocalTracks * 
        process.ctppsLocalTrackLiteProducer *
        process.ctppsProtons *
        process.mydiamonds 
    )
else:
    process.ALL = cms.Path(
        process.hltFilter *
        process.mydiamonds
    )

process.schedule = cms.Schedule(process.ALL)

#print(process.dumpPython())
