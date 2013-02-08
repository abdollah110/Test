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

void fake_Estimate_Electron() {

    TFile *data_Ele_data = new TFile("Data.root");


//    TH1D *Num_data_loose = (TH1D*) data_Ele_data->Get("FakeRate_Electron_Loose_After");
//    TH1D *Num_data_tight = (TH1D*) data_Ele_data->Get("FakeRate_Electron_Tight_After");
//    TH1D *Denum_data = (TH1D*) data_Ele_data->Get("FakeRate_Electron_Before");


    
    TH1D *Num_data_loose = (TH1D*) data_Ele_data->Get("FakeRate_ET_Electron_Loose_After_0");
    TH1D *Num_data_tight = (TH1D*) data_Ele_data->Get("FakeRate_ET_Electron_Tight_After_0");
    TH1D *Denum_data = (TH1D*) data_Ele_data->Get("FakeRate_ET_Electron_Pt_Before_0");


    TH1D *Num_rebin_data_loose = (TH1D*) Num_data_loose->Rebin(10);
    TH1D *Num_rebin_data_tight = (TH1D*) Num_data_tight->Rebin(10);
    TH1D *DeNum_rebin_data = (TH1D*) Denum_data->Rebin(10);

    TH1D *Trg_Pt1_data = new TH1D("TrgEff vs Pt1 data", "TrgEff vs Pt1 data", 20., 0, 100);
    (*Trg_Pt1_data) = (*Num_rebin_data_loose) / (*DeNum_rebin_data);

    TGraphAsymmErrors * Trg_Pt2Er_data = new TGraphAsymmErrors(Num_rebin_data_loose, DeNum_rebin_data);

    TCanvas *MyC = new TCanvas("MyC", "MyC", 800, 500);
    Trg_Pt1_data->SetMarkerColor(3);
    Trg_Pt1_data->SetStats(0);
    Trg_Pt1_data->SetTitle("");
    Trg_Pt1_data->SetMarkerSize(1.5);
    Trg_Pt1_data->SetMarkerStyle(20);
    Trg_Pt1_data->SetLineStyle(0);
    Trg_Pt1_data->SetMarkerColor(3);
    Trg_Pt1_data->SetMarkerSize(1.4);
    Trg_Pt1_data->SetMarkerStyle(20);
    Trg_Pt1_data->GetXaxis()->SetTitle(" Pt [GeV]");
    Trg_Pt1_data->GetXaxis()->SetTitleOffset(0.8);
    Trg_Pt1_data->GetXaxis()->SetTitleSize(0.05);
    Trg_Pt1_data->GetYaxis()->SetTitle("Fake Rate");
    Trg_Pt1_data->GetYaxis()->SetRangeUser(0, 1);
    Trg_Pt1_data->GetXaxis()->SetRangeUser(0, 100);
    Trg_Pt1_data->GetYaxis()->SetTitleOffset(0.8);
    Trg_Pt1_data->GetYaxis()->SetTitleSize(0.05);
    Trg_Pt1_data->Draw("P");
    Trg_Pt2Er_data->Draw("P");

    TLatex * tex = new TLatex(50, 0.6, "Loose Electron fake rate ");
    tex->SetTextSize(0.04);
    tex->Draw();

   //Text in Histogram
    TLatex *t = new TLatex();
    t->SetNDC();
    t->SetTextFont(62);
    t->SetTextAlign(12);
    t->SetTextSize(0.040);
    t->DrawLatex(0.65, 0.90, "CMS Preliminary 2011");
    t->DrawLatex(0.65, 0.83, "#sqrt{s} = 7 TeV, L = 5.0 fb^{-1}");
    t->SetTextSize(0.025);

    MyC->SaveAs("Fake_estimate_Electron.png");
    MyC->SaveAs("Fake_estimate_Electron.pdf");




    TFile *varPar = new TFile("Fake_Electron.root", "RECREATE");
    varPar->cd();

    TH1F * FitVar_FitError = new TH1F("fakeRate_Electron", "fakeRate_Electron", 6, 0, 6);
    FitVar_FitError->SetBinContent(1, Num_rebin_data_loose->GetEntries()*1.0 / DeNum_rebin_data->GetEntries());
    FitVar_FitError->SetBinContent(2, Num_rebin_data_tight->GetEntries()*1.0 / DeNum_rebin_data->GetEntries());
    cout<<"**************************************************************************"<<endl;
    cout<<"**************************    electron Fake Rate *************************"<<endl;
    cout<<"**************************************************************************"<<endl;
    cout<< "electron loose FR=  " << Num_rebin_data_loose->GetEntries()<< "/"<< DeNum_rebin_data->GetEntries()<<  "  =  "<<Num_rebin_data_loose->GetEntries()*1.0 / DeNum_rebin_data->GetEntries()<<endl;
    cout<< "electron tight FR=  " << Num_rebin_data_tight->GetEntries()<< "/"<< DeNum_rebin_data->GetEntries()<<"  =  " << Num_rebin_data_tight->GetEntries()*1.0 / DeNum_rebin_data->GetEntries()<<endl;
    cout<<"**************************************************************************"<<endl;


    varPar->Write();
    varPar->Close();


    TFile* fOUT = new TFile("Fake_estimate_Electron.root", "RECREATE");
    fOUT->cd();
    Trg_Pt2Er_data->SetName("Fake_R");
    Trg_Pt2Er_data->SetTitle("fakerate");
    Trg_Pt2Er_data->Write();
    fOUT->Close();

}

