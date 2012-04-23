import FWCore.ParameterSet.Config as cms

process = cms.Process("GR09Repro")

#--------------------------------------------------------------------------
# MessageLogger
#--------------------------------------------------------------------------
process.load("DPGAnalysis.SiStripTools.testrepro.MessageLogger_cff")

#-------------------------------------------------------------------
# input source
#-------------------------------------------------------------------
process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1) )

process.load("DPGAnalysis.SiStripTools.testrepro.inputsource_cff")

from runfiles.RAW.raw_RUNNUMBER_cff import fileNames
process.source.fileNames = fileNames

#---------------------------------------------------------------------
# Raw to Digi: TO BE TESTED !!
#---------------------------------------------------------------------
process.load("DPGAnalysis.SiStripTools.testrepro.rawtodigi_cff")

#-------------------------------------------------
# Global Tag
#-------------------------------------------------
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = "GR09_31X_V3P::All"

#-------------------------------------------------
# Include masking only from Cabling and O2O
#-------------------------------------------------
process.load("DPGAnalysis.SiStripTools.testrepro.clonedsistripquality_cff")

#----------------------------------------------------
# Clusterizer that uses the "unbiased" SiStripQuality
#----------------------------------------------------
process.load("DPGAnalysis.SiStripTools.testrepro.calzerobiasclusters_cff")

#-------------------------------------------------
# DQM Modules
#-------------------------------------------------
process.load("DPGAnalysis.SiStripTools.testrepro.dqm_cff")
process.dqmSaver.dirName      = 'DQMDIR'

#-------------------------------------------------------------
# Digi occupancy map and unpacker bad module map
#------------------------------------------------------------
process.load("DPGAnalysis.SiStripTools.testrepro.cs_maps_cff")
process.mapout.fileName= cms.untracked.string('maps_RUNNUMBER.root')

#------------------------------------------------------------------
# Filter against APV-induced noisy events
#------------------------------------------------------------------
#process.load("DPGAnalysis.SiStripTools.testrepro.noisyevent_filters_2009_cff")
process.load("DPGAnalysis.SiStripTools.testrepro.noisyevent_filters_2009_withdefaultphase_cff")

#------------------------------------------------------------------------
# TEC bad module analyzer
#------------------------------------------------------------------------
process.load("DPGAnalysis.SiStripTools.testrepro.tecbadmodules_cff")

process.load("DPGAnalysis.SiStripTools.testrepro.sistripqualitystatistics_cff")

#----------------------------------------------------------------------
# TFileService
#------------------------------------------------------------------------
process.TFileService = cms.Service('TFileService',
                                   fileName = cms.string('histos_RUNNUMBER.root')
                                   )
#------------------------------------------------------------------------


process.p = cms.Path(process.siStripDigis*process.siPixelDigis*
                     process.calZeroBiasClusters*
                     process.offlineBeamSpot*
                     process.trackerlocalreco*
                     process.ctftracksP5 +
                     process.stat + 
                     process.APVPhases+
                     process.consecutiveHEs+ # APV phase and Event History producers
                     process.newDigisMap+process.unpackerBadListMap+ process.unpackerBadList + #occupancy and bad modules maps
#filters to be used
                    ~process.potentialTIBTECHugeEvents*
                    ~process.potentialTIBTECFrameHeaderEventsFPeak*
# DQM modules after filter
                     process.siStripFEDMonitor+
                     process.SiStripMonitorDigi+
                     process.SiStripMonitorClusterReal+
# additional filters for fake tracks
                    ~process.potentialTIBTECFrameHeaderEventsWide+
# tracking DQM modules after additional filter                     
                     process.SiStripMonitorTrack_ckf*process.TrackMon_ckf+
                     process.dqmSaver+
# this has to be the last module !
                     process.nooutevent
                     )

process.e = cms.EndPath(process.mapout)
