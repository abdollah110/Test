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

void fake_Estimate_Eta_Medium() {

    TFile *data_MU_data = new TFile("Data.root");

    //**********************************************************************
    TH1D *Num_data = (TH1D*) data_MU_data->Get("FakeRate_TT_Tau_eta_After_Medium");
    TH1D *Denum_data = (TH1D*) data_MU_data->Get("FakeRate_TT_Tau_eta_Before");

    TH1D *Num_rebin_data = (TH1D*) Num_data->Rebin(25);
    TH1D *Denum_rebin_data = (TH1D*) Denum_data->Rebin(25);

    TH1D *Trg_Pt1_data = new TH1D("TrgEff vs Pt1 data", "TrgEff vs Pt1 data", 20., 0, 100);
    (*Trg_Pt1_data) = (*Num_rebin_data) / (*Denum_rebin_data);

    TGraphAsymmErrors * Trg_Pt2Er_data = new TGraphAsymmErrors(Num_rebin_data, Denum_rebin_data);
    //**********************************************************************
    TH1D *Num_data_OS = (TH1D*) data_MU_data->Get("FakeRate_OS_TT_Tau_eta_After_Medium");
    TH1D *Denum_data_OS = (TH1D*) data_MU_data->Get("FakeRate_OS_TT_Tau_eta_Before");

    TH1D *Num_rebin_data_OS = (TH1D*) Num_data_OS->Rebin(25);
    TH1D *Denum_rebin_data_OS = (TH1D*) Denum_data_OS->Rebin(25);

    TH1D *Trg_Pt1_data_OS = new TH1D("TrgEff vs Pt1 data _OS", "TrgEff vs Pt1 data _OS", 20., 0, 100);
    (*Trg_Pt1_data_OS) = (*Num_rebin_data_OS) / (*Denum_rebin_data_OS);

    TGraphAsymmErrors * Trg_Pt2Er_data_OS = new TGraphAsymmErrors(Num_rebin_data_OS, Denum_rebin_data_OS);
    //**********************************************************************

    TCanvas *MyC = new TCanvas("MyC", "MyC", 1000, 500);
    Trg_Pt1_data->SetStats(0);
    Trg_Pt1_data->SetTitle("");
    Trg_Pt1_data->SetMarkerColor(3);
    Trg_Pt1_data->SetMarkerSize(1.5);
    Trg_Pt1_data->SetMarkerStyle(20);
    Trg_Pt1_data->SetLineStyle(0);
    Trg_Pt1_data->GetYaxis()->SetRangeUser(0, .15);
    Trg_Pt1_data->GetXaxis()->SetTitle("tau eta");
    Trg_Pt1_data->GetYaxis()->SetTitle("fake rate");
    Trg_Pt1_data->Draw("P");
    Trg_Pt1_data_OS->SetMarkerColor(2);
    Trg_Pt1_data_OS->SetMarkerSize(1.5);
    Trg_Pt1_data_OS->SetMarkerStyle(24);
    Trg_Pt1_data_OS->SetLineStyle(0);
    Trg_Pt1_data_OS->Draw("Psame");
    Trg_Pt2Er_data->Draw("P");
    Trg_Pt2Er_data_OS->Draw("Psame");


    TLegend *l = new TLegend(0.5123824, 0.4959826, 0.7004702, 0.6990228, NULL, "brNDC");

    l->SetBorderSize(0);
    l->SetFillColor(0);
    l->SetTextSize(.04);
    l->AddEntry(Trg_Pt1_data, "HPS Medium Data SS", "lpf");
    l->AddEntry(Trg_Pt1_data_OS, "HPS Medium Data OS", "lpf");
    l->Draw();

    //Text in Histogram
    TLatex *t = new TLatex();
    t->SetNDC();
    t->SetTextFont(62);
    t->SetTextAlign(12);
    t->SetTextSize(0.030);
    t->DrawLatex(0.65, 0.83, "CMS Preliminary 2011");
    t->DrawLatex(0.65, 0.79, "#sqrt{s} = 7 TeV, L = 5.0 fb^{-1}");
    t->SetTextSize(0.025);


    MyC->SaveAs("Fake_estimate_eta_Medium.png");

    TFile* fOUT = new TFile("Fake_estimate_eta_Medium.root", "RECREATE");
    fOUT->cd();
    Trg_Pt2Er_data->SetName("Fake_R");
    Trg_Pt2Er_data->SetTitle("fakerate");
    Trg_Pt2Er_data->Write();
    fOUT->Close();
}

