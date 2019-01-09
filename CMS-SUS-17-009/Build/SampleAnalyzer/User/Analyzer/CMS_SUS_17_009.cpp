#include "SampleAnalyzer/User/Analyzer/CMS_SUS_17_009.h"
using namespace MA5;
using namespace std;

// This function return the DeltaR (code radius) used by the isolation requirement for leptons 
double DeltaR_MiniIso(const RecLeptonFormat* thisLepton) 
{ double DeltaR;
  double pT = thisLepton->momentum().Pt();
  if      (pT <= 50.0 )                { DeltaR = 0.2     ; }
  else if (pT > 50.0 and pT <= 200.0 ) { DeltaR = 10.0/pT ; }
  else if (pT > 200.0 )                { DeltaR = 0.05    ; }
  return DeltaR;
}

template<typename T1> void OverlapRmvPT(std::vector<const T1*> &, const double &);
template<typename T1> void OverlapDoubleRmv(std::vector<const T1*> &, const double &);
template<typename T1, typename T2> void OverlapRmv(std::vector<const T1*> &,std::vector<const T2*>, const double &);
template<typename T1,typename T2> void OverlapDoubleRmv(std::vector<const T1*> &, std::vector<const T2*> &, const double &);
template<typename T1> void KillResonances(std::vector<const T1*> &, const double &);


double MuonEff_OCSF (double pt, double eta)
{ double W=1 ;
  if   (pt <= 20)                                                 { W = 0;     }
  else if    (pt>20 && pt <= 25 && eta <=0.9                   )       { W = 0.869 ; }
  else if    (pt>20 && pt <= 25 && eta >0.9   && eta <= 1.2    )       { W = 0.857 ; }
  else if    (pt>20 && pt <= 25 && eta >1.2 && eta <= 2.1      )       { W = 0.891 ; }
  else if    (pt>20 && pt <= 25 && eta >2.1 && eta <= 2.4      )       { W = 0.803 ; }
  else if    (pt>25 && pt <= 30 && eta <=0.9                   )       { W = 0.889 ; }
  else if    (pt>25 && pt <= 30 && eta >0.9   && eta <= 1.2    )       { W = 0.880 ; }
  else if    (pt>25 && pt <= 30 && eta >1.2 && eta <= 2.1      )       { W = 0.894 ; }
  else if    (pt>25 && pt <= 30 && eta >2.1 && eta <= 2.4      )       { W = 0.818 ; }
  else if    (pt>30 && pt <= 40 && eta <=0.9                   )       { W = 0.910 ; }
  else if    (pt>30 && pt <= 40 && eta >0.9   && eta <= 1.2    )       { W = 0.893 ; }
  else if    (pt>30 && pt <= 40 && eta >1.2 && eta <= 2.1      )       { W = 0.901 ; }
  else if    (pt>30 && pt <= 40 && eta >2.1 && eta <= 2.4      )       { W = 0.817 ; } 
  else if    (pt>40 && pt <= 50 && eta <=0.9                   )       { W = 0.929 ; }
  else if    (pt>40 && pt <= 50 && eta >0.9   && eta <= 1.2    )       { W = 0.937 ; }
  else if    (pt>40 && pt <= 50 && eta >1.2 && eta <= 2.1      )       { W = 0.912 ; }
  else if    (pt>40 && pt <= 50 && eta >2.1 && eta <= 2.4      )       { W = 0.855 ; } 
  else if    (pt>40 && pt <= 50 && eta <=0.9                   )       { W = 0.930 ; }
  else if    (pt>40 && pt <= 50 && eta >0.9   && eta <= 1.2    )       { W = 0.930 ; }
  else if    (pt>40 && pt <= 50 && eta >1.2 && eta <= 2.1      )       { W = 0.927 ; }
  else if    (pt>40 && pt <= 50 && eta >2.1 && eta <= 2.4      )       { W = 0.869 ; } 

  return W; }

double ElectronEff_OCSF (double pt, double eta)
{ double W=1 ;
  if   (pt <= 20)                                                      { W = 0;     }
  else if    (pt>20 && pt <= 25 && eta <=0.8                   )       { W = 0.619 ; }
  else if    (pt>20 && pt <= 25 && eta >0.8   && eta <= 1.442  )       { W = 0.625 ; }
  else if    (pt>20 && pt <= 25 && eta >1.442 && eta <= 1.556  )       { W = 0.338 ; }
  else if    (pt>20 && pt <= 25 && eta >1.556 && eta <= 2.0    )       { W = 0.576 ; }
  else if    (pt>20 && pt <= 25 && eta >2.0 && eta <= 2.5      )       { W = 0.440 ; }

  else if    (pt>25 && pt <= 30 && eta <=0.8                   )       { W = 0.669 ; }
  else if    (pt>25 && pt <= 30 && eta >0.8   && eta <= 1.442  )       { W = 0.658 ; }
  else if    (pt>25 && pt <= 30 && eta >1.442 && eta <= 1.556  )       { W = 0.372 ; }
  else if    (pt>25 && pt <= 30 && eta >1.556 && eta <= 2.0    )       { W = 0.531 ; }
  else if    (pt>25 && pt <= 30 && eta >2.0 && eta <= 2.5      )       { W = 0.527 ; }

  else if    (pt>30 && pt <= 40 && eta <=0.8                   )       { W = 0.585 ; }
  else if    (pt>30 && pt <= 40 && eta >0.8   && eta <= 1.442  )       { W = 0.614 ; }
  else if    (pt>30 && pt <= 40 && eta >1.442 && eta <= 1.556  )       { W = 0.360 ; }
  else if    (pt>30 && pt <= 40 && eta >1.556 && eta <= 2.0    )       { W = 0.720 ; }
  else if    (pt>30 && pt <= 40 && eta >2.0 && eta <= 2.5      )       { W = 0.700 ; }

  else if    (pt>40 && pt <= 50 && eta <=0.8                   )       { W = 0.737 ; }
  else if    (pt>40 && pt <= 50 && eta >0.8   && eta <= 1.442  )       { W = 0.712 ; }
  else if    (pt>40 && pt <= 50 && eta >1.442 && eta <= 1.556  )       { W = 0.365 ; }
  else if    (pt>40 && pt <= 50 && eta >1.556 && eta <= 2.0    )       { W = 0.644 ; }
  else if    (pt>40 && pt <= 50 && eta >2.0 && eta <= 2.5      )       { W = 0.606 ; }



  else if    (pt>40 && pt <= 50 && eta <=0.8                   )       { W = 0.648 ; }
  else if    (pt>40 && pt <= 50 && eta >0.8   && eta <= 1.442  )       { W = 0.712 ; }
  else if    (pt>40 && pt <= 50 && eta >1.442 && eta <= 1.556  )       { W = 0.416 ; }
  else if    (pt>40 && pt <= 50 && eta >1.556 && eta <= 2.0    )       { W = 0.793 ; }
  else if    (pt>40 && pt <= 50 && eta >2.0 && eta <= 2.5      )       { W = 0.790 ; }

  return W; }




// -----------------------------------------------------------------------------
// Initialize
// function called one time at the beginning of the analysis
// -----------------------------------------------------------------------------
bool CMS_SUS_17_009::Initialize(const MA5::Configuration& cfg, const std::map<std::string,std::string>& parameters)
{
  cout << "BEGIN Initialization" << endl;
  cout << "BEGIN Finalization" << endl;
  // saving histos                                                                                                                                                                   
  cout << "END   Finalization" << endl;

  // Defintion of the 4 Signal Regions                                                                                                                                              

  Manager()->AddRegionSelection("SR_pTmiss_100-150");
  Manager()->AddRegionSelection("SR_pTmiss_150-225");
  Manager()->AddRegionSelection("SR_pTmiss_225-300");
  Manager()->AddRegionSelection("SR_pTmiss_300");

  // Definition of the Cuts common to all SRs                                                                                                                                        

  Manager()->AddCut("OCSF==2")           ;
  Manager()->AddCut("m(ll)>20")          ; // HT = scalar sum of jets pt>30 GeV                                                                                                   
  Manager()->AddCut("m(ll)<76_or_>106")  ; // HTM = magnitude of the the vector HTMiss, i.e. negative of the vector sum of all jets pt within |eta|<5                             
  Manager()->AddCut("Jet_Veto")          ; // No isolated muons with pt>10 GeV                                                                                                    
  //Manager()->AddCut("NoThirdLepton")     ; // No isolated muons tracks                                                                                                            
  Manager()->AddCut("MT2(ll)>90")        ; // No isolated electron with pt>10 GeV                                                                                                  

  //                                                                                                                                                                       
  string SR1[] = {"SR_pTmiss_100-150"} ;
  string SR2[] = {"SR_pTmiss_150-225"} ;
  string SR3[] = {"SR_pTmiss_225-300"} ;
  string SR4[] = {"SR_pTmiss_300"} ;

 
  Manager()->AddCut("pTmiss_100-150" , SR1)        ; // isolated electron with pt>10 GeV                                                                          
  Manager()->AddCut("pTmiss_150-225" , SR2)        ; // isolated electron with pt>10 GeV                                                                          
  Manager()->AddCut("pTmiss_225-300" , SR3)        ; // isolated electron with pt>10 GeV                                                                           
  Manager()->AddCut("pTmiss_300"     , SR4)        ; // isolated electron with pt>10 GeV                                                                             
             



  // initialize variables, histos
  cout << "END   Initialization" << endl;
  return true;
}

// -----------------------------------------------------------------------------
// Finalize
// function called one time at the end of the analysis
// -----------------------------------------------------------------------------
void CMS_SUS_17_009::Finalize(const SampleFormat& summary, const std::vector<SampleFormat>& files)
{
  cout << "BEGIN Finalization" << endl;
  // saving histos
  cout << "END   Finalization" << endl;

}

// -----------------------------------------------------------------------------
// Execute
// function called each time one event is read
// -----------------------------------------------------------------------------
bool CMS_SUS_17_009::Execute(SampleFormat& sample, const EventFormat& event)
{

  double myEventWeight = 1;
  Manager()->InitializeForNewEvent(myEventWeight); 
  vector<const RecLeptonFormat*> electrons, muons, isoElectrons, isoMuons, signalLeptons      ; // isolated electrons and muons (probably non isolated are not necessary...) 
  vector<const RecJetFormat*>    signalJets                   ; // jets, bjets, large eta jets
  vector<const RecTrackFormat*>  electronIsoTracks, muonIsoTracks, isoTracks ; // tracks, tracks identified as electons, and as muons
    
  // **********************************************
  // **** Objects Selection and Reconstruction ****   
  // **********************************************

  // Using the method from CMS-B2G-14-004 for isolation

  // Selecting MUONS
  for(unsigned int i=0; i<event.rec()->muons().size(); i++)
    {  const RecLeptonFormat *thisMuon = &(event.rec()->muons()[i]);
      //       double pt = thisMuon->momentum().Pt() , eta =  thisMuon->momentum().Eta() ;
      double pt = thisMuon->pt() , eta =  thisMuon->momentum().Eta() ;
      if (!( fabs(eta) < 1.4 && fabs(eta) < 1.6 && fabs(eta) < 2.4)) continue; // Leptons must satsisfy eta<2.4 and 1.4 < eta < 1.6
      muons.push_back(thisMuon);
      double IsoCone    = DeltaR_MiniIso(thisMuon);         // selecting the proper Radius
      double ChargedSum = PHYSICS->Isol->eflow->sumIsolation(thisMuon,event.rec() , IsoCone ,0.,IsolationEFlow::TRACK_COMPONENT);
      double NeutralSum = PHYSICS->Isol->eflow->sumIsolation(thisMuon,event.rec() , IsoCone ,0.,IsolationEFlow::NEUTRAL_COMPONENT); // There must be a bug inside MA5!!!
      double PhotonSum  = PHYSICS->Isol->eflow->sumIsolation(thisMuon,event.rec() , IsoCone ,0.,IsolationEFlow::PHOTON_COMPONENT);
      double All        = PHYSICS->Isol->eflow->sumIsolation(thisMuon,event.rec() , IsoCone ,0.,IsolationEFlow::ALL_COMPONENTS);      
      
      double Isolation     = (All)/pt ;
      //      cout << "MU_pt:" <<pt <<"  Cone:"<<IsoCone <<"  ChargedSum:"<<ChargedSum<<"  Neutral:"<<NeutralSum <<"  All:"<< All << endl << endl;    
      if (Isolation < 0.2) {
        //        cout << "This muon is isolated! Pt, cone, sum, isolation: " << pt << " " <<  IsoCone << " " << All << " " << Isolation <<  endl; 
        isoMuons.push_back(thisMuon); 
        signalLeptons.push_back(thisMuon);}
      //else if (Isolation > 0.2) {
      //  cout << " ********** this Muon is not isolated! Pt, cone, sum, isolation: " << pt << " " <<  IsoCone << " " << All << " " << Isolation <<  endl; }

    }


  for(unsigned int i=0; i<event.rec()->electrons().size(); i++)
    {  const RecLeptonFormat *thisElectron = &(event.rec()->electrons()[i]);
      double pt = thisElectron->pt() , eta =  thisElectron->momentum().Eta() ;
      if (!( fabs(eta) < 1.4 && fabs(eta) < 1.6 && fabs(eta) < 2.4)) continue; // Leptons must satsisfy eta<2.4 and 1.4 < eta < 1.6                                               
      electrons.push_back(thisElectron);
      double IsoCone    = DeltaR_MiniIso(thisElectron);         // selecting the proper Radius                                                        
      double ChargedSum = PHYSICS->Isol->eflow->sumIsolation(thisElectron,event.rec() , IsoCone ,0.,IsolationEFlow::TRACK_COMPONENT);
      double NeutralSum = PHYSICS->Isol->eflow->sumIsolation(thisElectron,event.rec() , IsoCone ,0.,IsolationEFlow::NEUTRAL_COMPONENT);
      double PhotonSum  = PHYSICS->Isol->eflow->sumIsolation(thisElectron,event.rec() , IsoCone ,0.,IsolationEFlow::PHOTON_COMPONENT);
      double All        = PHYSICS->Isol->eflow->sumIsolation(thisElectron,event.rec() , IsoCone ,0.,IsolationEFlow::ALL_COMPONENTS); // 
      // wrong def? PHYSICS->Isol->eflow->sumIsolation(thisElectron,event.rec() , IsoCone ,0.,IsolationEFlow::PHOTON_COMPONENT); 
      double Isolation  = All/pt;
      //      cout << "EL_pt:" <<pt <<"  Cone:"<<IsoCone <<"  ChargedSum:"<<ChargedSum<<"  Neutral:"<<NeutralSum <<"  All:"<< All << endl << endl;

      if (Isolation < 0.1) {
	// cout << "yeah one electron is isolated! " << endl;
	isoElectrons.push_back(thisElectron);
        signalLeptons.push_back(thisElectron); }
      //else if (Isolation > 0.1) { 
	//cout << "this Electron is not isolated! Pt, cone, sum, isolation: " << pt << " " <<  IsoCone << " " << All << " " << Isolation <<  endl; }
    }


  // Selecting JETS
  for(unsigned int i=0; i<event.rec()->jets().size(); i++)
    {  const RecJetFormat *thisJet= &(event.rec()->jets()[i]);
      double pT = thisJet->momentum().Pt() , eta =  thisJet->momentum().Eta() ;
      if (pT > 30 and fabs(eta) < 2.4 )
	{ signalJets.push_back(thisJet);    }

  SORTER->sort(isoMuons);
  SORTER->sort(isoElectrons);
  SORTER->sort(signalLeptons);

  
  // Check these two...

  OverlapRmv(signalJets,isoElectrons,0.4);
  OverlapRmv(signalJets,isoMuons,0.4);
  OverlapRmv(signalJets,signalJets,0.1);
  OverlapRmv(isoElectrons,isoMuons,0.1);



  // sort signal leptons by pT
  SORTER->sort(signalLeptons);

  // 2 OS leptons with pT > 35 GeV and > 20 GeV
  int NumEl = isoElectrons.size();
  int NumMu = isoMuons.size();
 
  //bool OCSF = (NumEl + NumMu == 2);
  bool two_lep = signalLeptons.size() == 2 ;
  bool OC;
  bool lep_pt;

  if (two_lep) { 
      OC      = signalLeptons[0]->charge() != signalLeptons[1]->charge() ; 
      lep_pt  = signalLeptons[0]->pt() > 50. && signalLeptons[1]->pt() > 20. ;
                }
  else { return 0; }


  //bool lep_pt  = signalLeptons[0]->pt() > 50. && signalLeptons[1]->pt() > 20. ;

  bool OCSF = two_lep && OC && lep_pt ;
  
  //  if(!Manager()->ApplyCut(OCSF, "OCSF==2")) return true;
  
  //cout << "signalLeptons size" << signalLeptons.size() << endl;
  // Applying the lepton efficiencies: reweighing the event

  double pt_1  = signalLeptons[0]->pt() ;
  double eta_1 = abs( signalLeptons[0]->eta() );
  double pt_2  = signalLeptons[1]->pt() ;
  double eta_2 = abs( signalLeptons[1]->eta() );

  
  if (NumEl ==2) {
      double w_1 = ElectronEff_OCSF(pt_1 , eta_1);
      double w_2 = ElectronEff_OCSF(pt_2 , eta_2);
      Manager()->SetCurrentEventWeight(w_1 * w_2); }

  if (NumMu ==2) {
      double w_1 = MuonEff_OCSF(pt_1 , eta_1);
      double w_2 = MuonEff_OCSF(pt_2 , eta_2);
      Manager()->SetCurrentEventWeight(w_1 * w_2); }

  if(!Manager()->ApplyCut(OCSF, "OCSF==2")) return true;

  // Cut on the invariand mass of the dilepton pair
  double mll = (signalLeptons[0]->momentum() + signalLeptons[1]->momentum()).M();

  if(!Manager()->ApplyCut( mll > 20.0,              "m(ll)>20"))         return true;
  if(!Manager()->ApplyCut( (mll < 76.0 or mll > 106), "m(ll)<76_or_>106")) return true;                                                                                                   
  // Jet veto
  int Njet = signalJets.size() ;                 
  if(!Manager()->ApplyCut(Njet ==0, "Jet_Veto")) return true;

  // Cut on the mT2 of the lepton pair , mT2_ll > 90
  
  double mT2_ll = PHYSICS->Transverse->MT2(signalLeptons[0], signalLeptons[1], event.rec()->MET(), 0.);

  if(!Manager()->ApplyCut(mT2_ll > 90., "MT2(ll)>90")) return true;


  // Binning in MET for the 4 different Signal Regions

  MALorentzVector pTmiss = event.rec()->MET().momentum();
  double MET = pTmiss.Pt();

 
  //cout << "Some events survive with MET  " << MET << endl ;

  /*
  Manager()->AddRegionSelection("pTmiss[100-150)");
  Manager()->AddRegionSelection("pTmiss[150-225)");
  Manager()->AddRegionSelection("pTmiss[225-300]");
  Manager()->AddRegionSelection("pTmiss>=300");
  */
  

  if ( !Manager()->ApplyCut(MET >= 100.0 && MET < 150.0  ,              "pTmiss_100-150") ) return true;  
  cout << "Surviving SR 1 " << MET << endl;
  if ( !Manager()->ApplyCut(MET >= 150.0 && MET < 225.0  ,              "pTmiss_150-225") ) return true;
  cout << "Surviving SR 2 " << MET << endl;
  if ( !Manager()->ApplyCut(MET >= 225.0 && MET <= 300.0 ,              "pTmiss_225-300") )return true; 
  cout << "Surviving SR 3 " << MET << endl;
  if ( !Manager()->ApplyCut(MET > 300.0                 ,              "pTmiss_300"    ) )return true;  
  cout << "Surviving SR 4 " << MET << endl;
  


  /*
  Manager()->ApplyCut( (MET >= 100.0 && MET < 150.0)  ,              "pTmiss_100-150");
  cout << "Surviving SR 1 " << MET << endl;
  Manager()->ApplyCut( (MET >= 150.0 && MET < 225.0)  ,              "pTmiss_150-225");
  cout << "Surviving SR 2 " << MET << endl;
  Manager()->ApplyCut( (MET >= 225.0 && MET <= 300.0) ,              "pTmiss_225-300");
  cout << "Surviving SR 3 " << MET << endl;
  Manager()->ApplyCut( (MET > 300.0 )                 ,              "pTmiss_300"    );
  cout << "Surviving SR 4 " << MET << endl;
  */

  return true;

}

}


// remove object v1 if overlap
template<typename T1, typename T2> void OverlapRmv(std::vector<const T1*> &v1,
						   std::vector<const T2*> v2, const double &dr)
{
  for(int i=v1.size()-1; i>=0; i--)
    for(unsigned int j=0; j<v2.size(); j++)
      if(v1[i]->dr(v2[j])<dr)
	{
	  v1.erase(v1.begin()+i);
	  break;
	}
  return;
}

