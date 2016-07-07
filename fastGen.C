#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Riostream.h>
#include <TGrid.h>
#include <TFile.h>
#include <TH1F.h>
#include <TStopwatch.h>
#include <TDatime.h>
#include <TRandom.h>
#include <TDatabasePDG.h>
#include <TParticle.h>
#include <TArrayI.h>
#include <TTree.h>
#include <TPDGCode.h>
#include "AliGenerator.h"
#include "AliPDG.h"
#include "AliRunLoader.h"
#include "AliRun.h"
#include "AliStack.h"
#include "AliHeader.h"
#include "AliGenTunedOnPbPb.h"
#endif

static int seed = 0;

AliGenerator* tuned(){
  AliGenTunedOnPbPb *generator = new AliGenTunedOnPbPb();
  generator->SetCentralityRange(0,10);
  generator->SetYmax(1.);

  TFile *fileT = TFile::Open("inputFor010.root");
  printf("fileT = %p\n", fileT);

  generator->SetSpectrum(AliGenTunedOnPbPb::kPiPlus     ,((TH1*) fileT->Get("hpi010")));
  generator->SetSpectrum(AliGenTunedOnPbPb::kPiMinus    ,((TH1*) fileT->Get("hpi010")));
//  generator->SetSpectrum(AliGenTunedOnPbPb::kPi0        ,((TH1*) fileT->Get("hpi010")));
  generator->SetSpectrum(AliGenTunedOnPbPb::kKaonPlus   ,((TH1*) fileT->Get("hka010")));
  generator->SetSpectrum(AliGenTunedOnPbPb::kKaonMinus  ,((TH1*) fileT->Get("hka010")));
//  generator->SetSpectrum(AliGenTunedOnPbPb::kKaon0      ,((TH1*) fileT->Get("hka010")));
  generator->SetSpectrum(AliGenTunedOnPbPb::kProton     ,((TH1*) fileT->Get("hpr010")));
  generator->SetSpectrum(AliGenTunedOnPbPb::kAntiProton ,((TH1*) fileT->Get("hpr010")));
  generator->SetSpectrum(AliGenTunedOnPbPb::kNeutron    ,((TH1*) fileT->Get("hpr010")));
  generator->SetSpectrum(AliGenTunedOnPbPb::kAntiNeutron,((TH1*) fileT->Get("hpr010")));
/*  generator->SetSpectrum(AliGenTunedOnPbPb::kLambda     ,((TH1*) fileT->Get("hla010")));
  generator->SetSpectrum(AliGenTunedOnPbPb::kAntiLambda ,((TH1*) fileT->Get("hla010")));
  generator->SetSpectrum(AliGenTunedOnPbPb::kPhi        ,((TH1*) fileT->Get("hphi010")));
  generator->SetSpectrum(AliGenTunedOnPbPb::kXi         ,((TH1*) fileT->Get("hxi010")));
  generator->SetSpectrum(AliGenTunedOnPbPb::kAntiXi     ,((TH1*) fileT->Get("hxi010")));
  generator->SetSpectrum(AliGenTunedOnPbPb::kOmega      ,((TH1*) fileT->Get("hom010")));
  generator->SetSpectrum(AliGenTunedOnPbPb::kAntiOmega  ,((TH1*) fileT->Get("hom010")));*/
  generator->SetV2(AliGenTunedOnPbPb::kPiPlus     ,((TH1*) fileT->Get("hpi010v2")));
  generator->SetV2(AliGenTunedOnPbPb::kPiMinus    ,((TH1*) fileT->Get("hpi010v2")));
//  generator->SetV2(AliGenTunedOnPbPb::kPi0        ,((TH1*) fileT->Get("hpi010v2")));
  generator->SetV2(AliGenTunedOnPbPb::kKaonPlus   ,((TH1*) fileT->Get("hka010v2")));
  generator->SetV2(AliGenTunedOnPbPb::kKaonMinus  ,((TH1*) fileT->Get("hka010v2")));
//  generator->SetV2(AliGenTunedOnPbPb::kKaon0      ,((TH1*) fileT->Get("hka010v2")));
  generator->SetV2(AliGenTunedOnPbPb::kProton     ,((TH1*) fileT->Get("hpr010v2")));
  generator->SetV2(AliGenTunedOnPbPb::kAntiProton ,((TH1*) fileT->Get("hpr010v2")));
  generator->SetV2(AliGenTunedOnPbPb::kNeutron    ,((TH1*) fileT->Get("hpr010v2")));
  generator->SetV2(AliGenTunedOnPbPb::kAntiNeutron,((TH1*) fileT->Get("hpr010v2")));
/*  generator->SetV2(AliGenTunedOnPbPb::kLambda     ,((TH1*) fileT->Get("hla010v2")));
  generator->SetV2(AliGenTunedOnPbPb::kAntiLambda ,((TH1*) fileT->Get("hla010v2")));
  generator->SetV2(AliGenTunedOnPbPb::kPhi        ,((TH1*) fileT->Get("hphi010v2")));
  generator->SetV2(AliGenTunedOnPbPb::kXi         ,((TH1*) fileT->Get("hxi010v2")));
  generator->SetV2(AliGenTunedOnPbPb::kAntiXi     ,((TH1*) fileT->Get("hxi010v2")));
  generator->SetV2(AliGenTunedOnPbPb::kOmega      ,((TH1*) fileT->Get("hom010v2")));
  generator->SetV2(AliGenTunedOnPbPb::kAntiOmega  ,((TH1*) fileT->Get("hom010v2")));*/
  return generator;
}

void fastGen(int nev = 100, const char* filename = "galice.root"){
  // Get settings from environment variables
  if (gSystem->Getenv("CONFIG_SEED")) {
    seed = atoi(gSystem->Getenv("CONFIG_SEED"));
  }

  gRandom->SetSeed(seed);

  AliPDG::AddParticlesToPdgDataBase();
  TDatabasePDG::Instance();

  // Run loader
  AliRunLoader* rl = AliRunLoader::Open(filename,"FASTRUN","recreate");
  rl->SetCompressionLevel(2);
  rl->SetNumberOfEventsPerFile(nev);
  rl->LoadKinematics("RECREATE");
  rl->MakeTree("E");
  rl->SetNumberOfEventsPerRun(nev);
  gAlice->SetRunLoader(rl);

  // Create stack
  rl->MakeStack();
  AliStack* stack = rl->Stack();

  // Header
  AliHeader* header = rl->GetHeader();

  AliGenerator *genHi = tuned();

  genHi->Print();
  genHi->Init();

  rl->CdGAFile();

  TStopwatch timer;
  timer.Start();
  for (int iev = 0; iev < nev; iev++) {
    cout <<"Event number "<< iev << endl;
    //  Initialize event
    header->Reset(0,iev);
    rl->SetEventNumber(iev);
    stack->Reset();
    rl->MakeTree("K");
    genHi->Generate();
    header->SetNprimary(stack->GetNprimary());
    header->SetNtrack(stack->GetNtrack());
    stack->FinishEvent();
    header->SetStack(stack);
    rl->TreeE()->Fill();
    rl->WriteKinematics("OVERWRITE");
  } // event loop
  timer.Stop();
  timer.Print();
  genHi->FinishRun();
  rl->WriteHeader("OVERWRITE");
  genHi->Write();
  rl->Write();
}


