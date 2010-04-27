import FWCore.ParameterSet.Config as cms

FedChannelDigis = cms.EDProducer("SiStripRawToDigiModule",
    ProductLabel      = cms.InputTag('source'),
    CreateDigis       = cms.untracked.bool(True),
    AppendedBytes     = cms.int32(0),
    UseDaqRegister    = cms.bool(True),
    UseFedKey         = cms.bool(True),
    UnpackBadChannels = cms.bool(False),
    MarkModulesOnMissingFeds = cms.bool(True),
    TriggerFedId      = cms.int32(-1),
    DoAllCorruptBufferChecks = cms.bool(False),
    #FedEventDumpFreq  = cms.untracked.int32(0),
    #FedBufferDumpFreq = cms.untracked.int32(0),
    #Quiet             = cms.untracked.bool(False)
)

