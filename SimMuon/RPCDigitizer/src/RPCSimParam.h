#ifndef RPCDigitizer_RPCSimParam_h
#define RPCDigitizer_RPCSimParam_h

/** \class RPCSimParam
 *   Class for the RPC strip response simulation based
 *   on a parametrized model (ORCA-based)
 *
 *  \author Marcello Maggi -- INFN Bari
 */
#include "SimMuon/RPCDigitizer/src/RPCSim.h"
#include <FWCore/Framework/interface/EventSetup.h>
#include "SimMuon/RPCDigitizer/src/RPCSynchronizer.h"

class RPCGeometry;

namespace CLHEP {
  class HepRandomEngine;
  class RandFlat;
  class RandPoissonQ;
}

class RPCSimParam : public RPCSim
{
 public:
  RPCSimParam(const edm::ParameterSet& config);
  ~RPCSimParam();

  void simulate(const RPCRoll* roll,
		const edm::PSimHitContainer& rpcHits);

  void simulateNoise(const RPCRoll*);

  void setRandomEngine(CLHEP::HepRandomEngine& eng);

 private:
  void init(){};
 private:
  double aveEff;
  double aveCls;
  double resRPC;
  double timOff;
  double dtimCs;
  double resEle;
  double sspeed;
  double lbGate;
  bool rpcdigiprint;

  int N_hits;
  int nbxing;
  double rate;
  double gate;

  RPCSynchronizer* _rpcSync;

  //  CLHEP::HepRandomEngine* rndEngine;
  CLHEP::RandFlat* flatDistribution_;
  CLHEP::RandFlat* flatDistribution1;                                                                                                                                                              
  CLHEP::RandFlat* flatDistribution2;          
  CLHEP::RandPoissonQ *poissonDistribution;    
};
#endif
