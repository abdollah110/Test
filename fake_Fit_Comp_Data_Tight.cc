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
#include "TMath.h"

Double_t fitFunction(Double_t *x, Double_t *par) {
    return par[0] + par[1]*(TMath::Exp(par[2] * x[0]));
}

const int nPar = 3; // number of parameters in the fit

void fake_Fit_Comp_Data_Tight() {
    TFile* fIN = new TFile("Fake_estimate_Medium.root");
    TFile* fIN_MC = TFile::Open("Fake_estimate_Medium_MC.root");
    //    fIN->ls();
    //    fIN_MC->ls();

    Double_t fitRangeMin = 10,
            fitRangeMax = 80;



    TF1* theFit = new TF1("theFit", fitFunction, fitRangeMin, fitRangeMax, nPar);
    TF1* theFit_MC = new TF1("theFit_MC", fitFunction, fitRangeMin, fitRangeMax, nPar);

    theFit->SetParameter(0, 0.012);
    theFit->SetParameter(1, 0.18);
    theFit->SetParameter(2, -0.095);

    theFit_MC->SetParameter(0, 0.012);
    theFit_MC->SetParameter(1, 0.18);
    theFit_MC->SetParameter(2, -0.095);
    //    theFit->SetParLimits(0, 0.2, 1.);
    //    theFit->SetParLimits(0, 0.95, 1.);


    TCanvas* canvas = new TCanvas("canvas", "", 600, 600);
    canvas->SetFillColor(0);
    canvas->SetTitle("0");

    //    setTDRStyle();


    canvas->cd(1);
    TGraphAsymmErrors * Fake_R = (TGraphAsymmErrors*) fIN->Get("Fake_R");
    TGraphAsymmErrors * Fake_R_MC = (TGraphAsymmErrors*) fIN_MC->Get("Fake_R_MC");

    Fake_R->SetMarkerColor(2);
    Fake_R->SetMarkerSize(1.4);
    Fake_R->SetMarkerStyle(20);
    Fake_R->SetTitle("");
    Fake_R->GetXaxis()->SetTitle("#tau Pt [GeV]");
    Fake_R->GetXaxis()->SetTitleOffset(1);
    Fake_R->GetXaxis()->SetTitleSize(0.05);
    Fake_R->GetYaxis()->SetTitle("Fake Rate");
    Fake_R->GetYaxis()->SetRangeUser(0, 0.101);
    Fake_R->GetXaxis()->SetRangeUser(0, 100);
    Fake_R->GetYaxis()->SetTitleOffset(1.3);
    Fake_R->GetYaxis()->SetTitleSize(0.05);
    Fake_R->GetYaxis()->SetLabelSize(0.04);
    Fake_R->Draw("PAE");

    Fake_R_MC->SetMarkerColor(4);
    Fake_R_MC->SetMarkerSize(1.4);
    Fake_R_MC->SetMarkerStyle(24);
    Fake_R_MC->GetXaxis()->SetTitle("#tau Pt [GeV]");
    Fake_R_MC->GetXaxis()->SetTitleOffset(1);
    Fake_R_MC->GetXaxis()->SetTitleSize(0.05);
    Fake_R_MC->GetYaxis()->SetTitle("Fake Rate");
    Fake_R_MC->GetYaxis()->SetRangeUser(0, 0.101);
    Fake_R_MC->GetYaxis()->SetTitleOffset(1.3);
    Fake_R_MC->GetYaxis()->SetTitleSize(0.05);
    Fake_R_MC->Draw("PSAME");

    Fake_R->Fit("theFit", "R0");
    theFit->SetRange(15, 80);
    theFit->SetLineColor(kRed);
    theFit->SetLineWidth(2);
    theFit->Draw("SAME");

    Fake_R_MC->Fit("theFit_MC", "R0");
    theFit_MC->SetRange(15, 80);
    theFit_MC->SetLineColor(kBlue);
    theFit_MC->SetLineWidth(2);
    theFit_MC->Draw("SAME");

    //    TLatex * tex = new TLatex(63, 0.06, "HPS Loose (Data)");
    //    tex->SetTextSize(0.05);
    //    tex->SetTextColor(2);
    //    tex->Draw();

    TLegend *l = new TLegend(0.4123824, 0.4959826, 0.7004702, 0.6990228, NULL, "brNDC");

    l->SetBorderSize(0);
    l->SetFillColor(0);
    l->SetTextSize(.04);
       l->AddEntry(Fake_R_MC, "Tight Comb.  Data 2012", "lpf");
    l->AddEntry(Fake_R, "Tight Comb.  Data 2011", "lpf");
    l->Draw();

    //Text in Histogram
    TLatex *t = new TLatex();
    t->SetNDC();
    t->SetTextFont(62);
    t->SetTextAlign(12);
    t->SetTextSize(0.040);
    t->DrawLatex(0.65, 0.83, "CMS Preliminary");
//    t->DrawLatex(0.65, 0.79, "#sqrt{s} = 7 TeV, L = 5.0 fb^{-1}");
    t->SetTextSize(0.025);

    canvas->SaveAs("Fake_fit_Com_Tight.png");
    canvas->SaveAs("Fake_fit_Com_Tight.pdf");

    //    TFile *varPar = new TFile("Fake_fit_Loose.root", "RECREATE");
    //    varPar->cd();
    //
    //    TH1F * FitVar_FitError = new TH1F("FitVar_FitError", "FitVar_FitError", 6, 0, 6);
    //    Double_t TauLegParameters[nPar];
    //    theFit->GetParameters(TauLegParameters);
    //    for (int i = 0; i < nPar; i++) {
    //        cout << "par" << i << " = " << TauLegParameters[i] << endl;
    //        cout << "par" << i << " = " << theFit->GetParError(i) << endl;
    //        FitVar_FitError->SetBinContent((2 * i + 1), TauLegParameters[i]);
    //        FitVar_FitError->SetBinContent((2 * i + 2), theFit->GetParError(i));
    //    }
    //    varPar->Write();
    //    varPar->Close();

}
