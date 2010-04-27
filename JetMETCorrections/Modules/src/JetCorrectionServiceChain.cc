//
// Original Author:  Fedor Ratnikov
//         Created:  Dec. 28, 2006
// $Id: JetCorrectionServiceChain.cc,v 1.1 2008/02/29 22:58:45 fedor Exp $
//
//

#include "JetMETCorrections/Modules/interface/JetCorrectionServiceChain.h"

// user include files
#include "FWCore/Framework/interface/ESHandle.h"
#include "JetMETCorrections/Objects/interface/ChainedJetCorrector.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"



JetCorrectionServiceChain::JetCorrectionServiceChain (const edm::ParameterSet& fParameters) 
  : mCorrectors (fParameters.getParameter <std::vector <std::string> > ("correctors")),
    mChainCorrector (new ChainedJetCorrector ())
{
  std::string label = fParameters.getParameter <std::string> ("label");
  if (std::find (mCorrectors.begin(), mCorrectors.end(), label) != mCorrectors.end ()) {
    throw cms::Exception("Recursion is not allowed") << "JetCorrectionServiceChain: corrector " << label << " is chained to itself";
  }
  setWhatProduced (this, label);
  findingRecord <JetCorrectionsRecord> ();
}

JetCorrectionServiceChain::~JetCorrectionServiceChain () {}

boost::shared_ptr<JetCorrector> JetCorrectionServiceChain::produce( const JetCorrectionsRecord& fRecord) {
  ChainedJetCorrector* corrector = dynamic_cast<ChainedJetCorrector*> (&*mChainCorrector);
  corrector->clear ();
  for (size_t i = 0; i < mCorrectors.size (); ++i) {
    edm::ESHandle <JetCorrector> handle;
    fRecord.get (mCorrectors[i], handle);
    corrector->push_back (&*handle);
  }
  return mChainCorrector;
}
  
void JetCorrectionServiceChain::setIntervalFor(const edm::eventsetup::EventSetupRecordKey&, 
					       const edm::IOVSyncValue&, 
					       edm::ValidityInterval& fIOV) {
  fIOV = edm::ValidityInterval(edm::IOVSyncValue::beginOfTime(),edm::IOVSyncValue::endOfTime()); // anytime
}
