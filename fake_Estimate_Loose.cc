#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBrowser.h"
#include "TH1.h"
#include "TH2.h"
#include "TRandom.h"
#include "iostream.h"
#include "TCanvas.h"
#include "math.h"
#include "TGaxis.h"
#include "TLegend.h"
#include "TInterpreter.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TFile.h"
#include "TH2.h"
#include "TNtuple.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TFrame.h"
#include "TSystem.h"
#include "TInterpreter.h"

void fake_Estimate_Loose() {

    TFile *data_MU_data = new TFile("Data.root");

    TH1D *Num_data = (TH1D*) data_MU_data->Get("FakeRate_TT_Tau_Pt_After_Medium");
    TH1D *Denum_data = (TH1D*) data_MU_data->Get("FakeRate_TT_Tau_Pt_Before");
                                                  
    TH1D *Num_rebin_data = (TH1D*) Num_data->Rebin(5);
    TH1D *Denum_rebin_data = (TH1D*) Denum_data->Rebin(5);

    TH1D *Trg_Pt1_data = new TH1D("TrgEff vs Pt1 data", "TrgEff vs Pt1 data", 20., 0, 100);
    (*Trg_Pt1_data) = (*Num_rebin_data) / (*Denum_rebin_data);

    TGraphAsymmErrors * Trg_Pt2Er_data = new TGraphAsymmErrors(Num_rebin_data, Denum_rebin_data);

    TCanvas *MyC = new TCanvas("MyC", "MyC", 1000, 500);
    Trg_Pt1_data->SetMarkerColor(3);
    Trg_Pt1_data->SetMarkerSize(1.5);
    Trg_Pt1_data->SetMarkerStyle(20);
    Trg_Pt1_data->SetLineStyle(0);
    Trg_Pt1_data->Draw("P");
    Trg_Pt2Er_data->Draw("P");
    MyC->SaveAs("Fake_estimate_Loose.png");
    MyC->SaveAs("Fake_estimate_Loose.pdf");
    
    cout<<"**************************************************************************"<<endl;
    cout<<"**************************    Tau Fake Rate *************************"<<endl;
    cout<<"**************************************************************************"<<endl;
    cout<< "Tau loose FR=  " << Num_rebin_data->GetEntries()<< "/"<< Denum_rebin_data->GetEntries()<<  "  =  "<<Num_rebin_data->GetEntries()*1.0 / Denum_rebin_data->GetEntries()<<endl;
    cout<<"**************************************************************************"<<endl;


    TFile* fOUT = new TFile("Fake_estimate_Loose.root", "RECREATE");
    fOUT->cd();
    Trg_Pt2Er_data->SetName("Fake_R");
    Trg_Pt2Er_data->SetTitle("fakerate");
    Trg_Pt2Er_data->Write();
    fOUT->Close();
}

