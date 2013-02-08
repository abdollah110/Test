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

void fake_Estimate_Electron_Compare() {

    TFile *data_MU_data = new TFile("Data_tot.root");
    TFile *data_Mu_11 = new TFile("Data12D.root");

    //        TH1D *Num_data_loose = (TH1D*) data_MU_data->Get("FakeRate_Electron_Loose_After");
    //        TH1D *Num_data_tight = (TH1D*) data_MU_data->Get("FakeRate_Electron_Tight_After");
    //        TH1D *Denum_data = (TH1D*) data_MU_data->Get("FakeRate_Electron_Before");
    TH1D *Num_data_loose = (TH1D*) data_MU_data->Get("FakeRate_ET_Electron_Loose_After_0");
    TH1D *Num_data_tight = (TH1D*) data_MU_data->Get("FakeRate_ET_Electron_Tight_After_0");
    TH1D *Denum_data = (TH1D*) data_MU_data->Get("FakeRate_ET_Electron_Pt_Before_0");
    TH1D *Num_data_loose11 = (TH1D*) data_Mu_11->Get("FakeRate_ET_Electron_Loose_After_0");
    TH1D *Num_data_tight11 = (TH1D*) data_Mu_11->Get("FakeRate_ET_Electron_Tight_After_0");
    TH1D *Denum_data11 = (TH1D*) data_Mu_11->Get("FakeRate_ET_Electron_Pt_Before_0");


    TH1D *Num_rebin_data_loose = (TH1D*) Num_data_loose->Rebin(10);
    TH1D *Num_rebin_data_tight = (TH1D*) Num_data_tight->Rebin(10);
    TH1D *DeNum_rebin_data = (TH1D*) Denum_data->Rebin(10);
    TH1D *Num_rebin_data_loose11 = (TH1D*) Num_data_loose11->Rebin(10);
    TH1D *Num_rebin_data_tight11 = (TH1D*) Num_data_tight11->Rebin(10);
    TH1D *DeNum_rebin_data11 = (TH1D*) Denum_data11->Rebin(10);

    TH1D *Trg_Pt1_data = new TH1D("TrgEff vs Pt1 data", "TrgEff vs Pt1 data", 20., 0, 100);
    (*Trg_Pt1_data) = (*Num_rebin_data_loose) / (*DeNum_rebin_data);
    TH1D *Trg_Pt1_data11 = new TH1D("TrgEff vs Pt1 data11", "TrgEff vs Pt1 data11", 20., 0, 100);
    (*Trg_Pt1_data11) = (*Num_rebin_data_loose11) / (*DeNum_rebin_data11);

    TGraphAsymmErrors * Trg_Pt2Er_data = new TGraphAsymmErrors(Num_rebin_data_loose, DeNum_rebin_data);
    TGraphAsymmErrors * Trg_Pt2Er_data11 = new TGraphAsymmErrors(Num_rebin_data_loose11, DeNum_rebin_data11);

    TCanvas *MyC = new TCanvas("MyC", "MyC", 600, 600);
    Trg_Pt1_data->SetMarkerColor(3);
    Trg_Pt1_data->SetStats(0);
    Trg_Pt1_data->SetTitle("");
    Trg_Pt1_data->SetMarkerSize(1.5);
    Trg_Pt1_data->SetMarkerStyle(20);
    Trg_Pt1_data->SetLineStyle(0);
    Trg_Pt1_data->SetMarkerColor(3);
    Trg_Pt1_data->SetMarkerSize(1.4);
    Trg_Pt1_data->SetMarkerStyle(20);
    Trg_Pt1_data->SetMarkerStyle(20);
    Trg_Pt1_data->GetXaxis()->SetTitle("Lep. Pt [GeV]");
    Trg_Pt1_data->GetXaxis()->SetTitleOffset(0.8);
    Trg_Pt1_data->GetXaxis()->SetTitleSize(0.05);
    Trg_Pt1_data->GetYaxis()->SetTitle("Fake Rate");
    Trg_Pt1_data->GetYaxis()->SetRangeUser(0, 0.30);
    Trg_Pt1_data->GetXaxis()->SetRangeUser(0, 59);
    Trg_Pt1_data->GetYaxis()->SetTitleOffset(1.0);
    Trg_Pt1_data->GetYaxis()->SetTitleSize(0.05);
    Trg_Pt1_data->GetYaxis()->SetLabelSize(0.03);
    Trg_Pt1_data->Draw("P");
    Trg_Pt2Er_data->Draw("P");

    Trg_Pt1_data11->SetMarkerColor(2);
    Trg_Pt1_data11->SetStats(0);
    Trg_Pt1_data11->SetTitle("");
    Trg_Pt1_data11->SetMarkerSize(1.5);
    Trg_Pt1_data11->SetMarkerStyle(20);
    Trg_Pt1_data11->SetLineStyle(0);
    Trg_Pt1_data11->SetMarkerColor(2);
    Trg_Pt1_data11->SetMarkerSize(1.4);
    Trg_Pt1_data11->SetMarkerStyle(22);
    Trg_Pt1_data11->GetXaxis()->SetTitle(" Pt [GeV]");
    Trg_Pt1_data11->GetXaxis()->SetTitleOffset(0.8);
    Trg_Pt1_data11->GetXaxis()->SetTitleSize(0.05);
    Trg_Pt1_data11->GetYaxis()->SetTitle("Fake Rate");
    Trg_Pt1_data11->GetYaxis()->SetRangeUser(0, 0.30);
    Trg_Pt1_data11->GetXaxis()->SetRangeUser(0, 50);
    Trg_Pt1_data11->GetYaxis()->SetTitleOffset(0.8);
    Trg_Pt1_data11->GetYaxis()->SetTitleSize(0.05);

    Trg_Pt1_data11->Draw("Psame");
    Trg_Pt2Er_data11->Draw("Psame");

    TLatex * tex = new TLatex(50, 0.6, "Loose Electron fake rate (Data)");
    tex->SetTextSize(0.04);
    tex->Draw();

    TLegend *l = new TLegend(0.50, 0.40, 0.7004702, 0.5990228, NULL, "brNDC");
    l->SetBorderSize(0);
    l->SetFillColor(0);
    l->SetTextSize(.04);
    l->AddEntry(Trg_Pt1_data, "Data 2012 A+B+C ", "lpf");
    l->AddEntry(Trg_Pt1_data11, "Data 2012 D ", "lpf");
    l->Draw();


    //Text in Histogram
    TLatex *t = new TLatex();
    t->SetNDC();
    t->SetTextFont(62);
    t->SetTextAlign(12);
    t->SetTextSize(0.040);
    t->DrawLatex(0.50, 0.85, "CMS Preliminary ");
    t->DrawLatex(0.50, 0.75, "Electron Fake Rate");
    t->SetTextSize(0.025);
    MyC->SaveAs("Fake_estimate_Electron.png");
    MyC->SaveAs("Fake_estimate_Electron.pdf");


    TFile *varPar = new TFile("Fake_Electron.root", "RECREATE");
    varPar->cd();

    TH1F * FitVar_FitError = new TH1F("fakeRate_Electron", "fakeRate_Electron", 6, 0, 6);
    FitVar_FitError->SetBinContent(1, Num_rebin_data_loose->GetEntries()*1.0 / DeNum_rebin_data->GetEntries());
    FitVar_FitError->SetBinContent(2, Num_rebin_data_tight->GetEntries()*1.0 / DeNum_rebin_data->GetEntries());
    cout << "**************************************************************************" << endl;
    cout << "**************************    mu Fake Rate  ******************************" << endl;
    cout << "**************************************************************************" << endl;
    cout << "mu loose FR=  " << Num_rebin_data_loose->GetEntries() << "/" << DeNum_rebin_data->GetEntries() << "  =  " << Num_rebin_data_loose->GetEntries()*1.0 / DeNum_rebin_data->GetEntries() << endl;
    cout << "mu tight FR=  " << Num_rebin_data_tight->GetEntries() << "/" << DeNum_rebin_data->GetEntries() << "  =  " << Num_rebin_data_tight->GetEntries()*1.0 / DeNum_rebin_data->GetEntries() << endl;
    cout << "**************************************************************************" << endl;

    varPar->Write();
    varPar->Close();


    TFile* fOUT = new TFile("Fake_estimate_Electron.root", "RECREATE");
    fOUT->cd();
    Trg_Pt2Er_data->SetName("Fake_R");
    Trg_Pt2Er_data->SetTitle("fakerate");
    Trg_Pt2Er_data->Write();
    fOUT->Close();

}

