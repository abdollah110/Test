#include "TGraph.h"
#include "TGraphErrors.h"
#include <fstream>
#include <iostream>
#include <TFile.h>
#include <ostream>
#include <time.h>
#include <TF1.h>
#include <TPad.h>
#include <TGraphAsymmErrors.h>
#include <TPave.h>
#include <TCanvas.h>
#include <TAttAxis.h>
#include "TMath.h"

Double_t fitFunction(Double_t *x, Double_t *par) {
    return par[0] + par[1]*(TMath::Exp(par[2] * x[0]));
}

const int nPar = 3; // number of parameters in the fit

void fake_Fit_Loose_Compare() {
    TFile* fIN = new TFile("Fake_estimate_Loose_12ABC.root");
//    TFile* fIN_MC = TFile::Open("Fake_estimate_Loose_11.root");
    TFile* fIN_2012 = TFile::Open("Fake_estimate_Loose_12D.root");

    Double_t fitRangeMin = 15,
            fitRangeMax = 80;



    TF1* theFit = new TF1("theFit", fitFunction, fitRangeMin, fitRangeMax, nPar);
//    TF1* theFit_MC = new TF1("theFit_MC", fitFunction, fitRangeMin, fitRangeMax, nPar);
    TF1* theFit_2012 = new TF1("theFit_2012", fitFunction, fitRangeMin, fitRangeMax, nPar);

    theFit->SetParameter(0, 0.012);
    theFit->SetParameter(1, 0.18);
    theFit->SetParameter(2, -0.095);

//    theFit_MC->SetParameter(0, 0.012);
//    theFit_MC->SetParameter(1, 0.18);
//    theFit_MC->SetParameter(2, -0.095);

    theFit_2012->SetParameter(0, 0.012);
    theFit_2012->SetParameter(1, 0.18);
    theFit_2012->SetParameter(2, -0.095);


    TCanvas* canvas = new TCanvas("canvas", "", 600, 600);
    canvas->SetFillColor(0);
    canvas->SetTitle("0");


    canvas->cd(1);
    TGraphAsymmErrors * Fake_R_12AB = (TGraphAsymmErrors*) fIN->Get("Fake_R_12ABC");
//    TGraphAsymmErrors * Fake_R_11 = (TGraphAsymmErrors*) fIN_MC->Get("Fake_R_11");
    TGraphAsymmErrors * Fake_R_12C = (TGraphAsymmErrors*) fIN_2012->Get("Fake_R_12D");

    Fake_R_12AB->SetMarkerColor(2);
    Fake_R_12AB->SetMarkerSize(1.4);
    Fake_R_12AB->SetMarkerStyle(20);
    Fake_R_12AB->SetTitle("");
    Fake_R_12AB->GetXaxis()->SetTitle("#tau Pt [GeV]");
    Fake_R_12AB->GetXaxis()->SetTitleOffset(1);
    Fake_R_12AB->GetXaxis()->SetTitleSize(0.05);
    Fake_R_12AB->GetXaxis()->SetLabelSize(0.04);
    Fake_R_12AB->GetYaxis()->SetLabelSize(0.03);
    Fake_R_12AB->GetYaxis()->SetTitle("Fake Rate");
    Fake_R_12AB->GetYaxis()->SetRangeUser(0, 0.101);
    Fake_R_12AB->GetXaxis()->SetRangeUser(0, 90);
    Fake_R_12AB->GetYaxis()->SetTitleOffset(1.0);
    Fake_R_12AB->GetYaxis()->SetTitleSize(0.05);
    Fake_R_12AB->Draw("PAE");

//    Fake_R_11->SetMarkerColor(4);
//    Fake_R_11->SetMarkerSize(1.4);
//    Fake_R_11->SetMarkerStyle(24);
//    Fake_R_11->GetXaxis()->SetTitle("#tau Pt [GeV]");
//    Fake_R_11->GetXaxis()->SetTitleOffset(1);
//    Fake_R_11->GetXaxis()->SetTitleSize(0.05);
//    Fake_R_11->GetYaxis()->SetTitle("Fake Rate");
//    Fake_R_11->GetYaxis()->SetRangeUser(0, 0.101);
//    Fake_R_11->GetYaxis()->SetTitleOffset(1.3);
//    Fake_R_11->GetYaxis()->SetTitleSize(0.05);
//    Fake_R_11->Draw("PSAME");

    Fake_R_12C->SetMarkerColor(3);
    Fake_R_12C->SetMarkerSize(1.4);
    Fake_R_12C->SetMarkerStyle(23);
    Fake_R_12C->GetXaxis()->SetTitle("#tau Pt [GeV]");
    Fake_R_12C->GetXaxis()->SetTitleOffset(1);
    Fake_R_12C->GetXaxis()->SetTitleSize(0.05);
    Fake_R_12C->GetYaxis()->SetTitle("Fake Rate");
    Fake_R_12C->GetYaxis()->SetRangeUser(0, 0.101);
    Fake_R_12C->GetYaxis()->SetTitleOffset(1.2);
    Fake_R_12C->GetYaxis()->SetTitleSize(0.05);
    Fake_R_12C->Draw("PSAME");

    Fake_R_12AB->Fit("theFit", "R0");
    theFit->SetRange(15, 80);
    theFit->SetLineColor(kRed);
    theFit->SetLineWidth(2);
    theFit->Draw("SAME");

//    Fake_R_11->Fit("theFit_MC", "R0");
//    theFit_MC->SetRange(15, 80);
//    theFit_MC->SetLineColor(kBlue);
//    theFit_MC->SetLineWidth(2);
//    theFit_MC->Draw("SAME");

    Fake_R_12C->Fit("theFit_2012", "R0");
    theFit_2012->SetRange(15, 80);
    theFit_2012->SetLineColor(kGreen);
    theFit_2012->SetLineWidth(2);
    theFit_2012->Draw("SAME");


    TLegend *l = new TLegend(0.50, 0.50, 0.7004702, 0.6990228, NULL, "brNDC");

    l->SetBorderSize(0);
    l->SetFillColor(0);
    l->SetTextSize(.04);
    l->AddEntry(Fake_R_12C, "Data 2012 D", "lpf");
    l->AddEntry(Fake_R_12AB, "Data 2012 A+B+C", "lpf");
//    l->AddEntry(Fake_R_11, "Data 2011", "lpf");


    l->Draw();

    //Text in Histogram
    TLatex *t = new TLatex();
    t->SetNDC();
    t->SetTextFont(62);
    t->SetTextAlign(12);
    t->SetTextSize(0.040);
    t->DrawLatex(0.50, 0.83, "CMS Preliminary");
    t->SetTextSize(0.030);
    t->DrawLatex(0.50, 0.75, "(Medium Comb. Isolation)");
    t->SetTextSize(0.025);

    canvas->SaveAs("Fake_fit_Loose_Compare.png");
    canvas->SaveAs("Fake_fit_Loose_Compare.pdf");



}
