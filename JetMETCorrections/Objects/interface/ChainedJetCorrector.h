//
// Original Author:  Fedor Ratnikov Dec 27, 2006
// $Id: JetCorrector.h,v 1.4 2007/11/01 21:54:48 fedor Exp $
//
// Correction which chains other corrections
//
#ifndef ChainedJetCorrector_h
#define ChainedJetCorrector_h

#include "boost/shared_ptr.hpp"
#include <vector>

#include "JetMETCorrections/Objects/interface/JetCorrector.h"


class ChainedJetCorrector : public JetCorrector {
 public:
  ChainedJetCorrector (){}
  virtual ~ChainedJetCorrector (){}
  
  virtual double correction (const JetCorrector::LorentzVector& fJet) const;
  virtual double correction (const reco::Jet& fJet) const;
  virtual double correction (const reco::Jet& fJet, const edm::Event& fEvent, const edm::EventSetup& fSetup) const;
	
  virtual bool eventRequired () const;
	  
  void push_back (const JetCorrector* fCorrector) {mCorrectors.push_back (fCorrector);}
  void clear () {mCorrectors.clear ();}
	  
 private:
  std::vector <const JetCorrector*> mCorrectors;
};

#endif
