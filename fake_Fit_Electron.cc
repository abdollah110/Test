#include "TGraph.h"
#include "TGraphErrors.h"
#include <fstream>
#include <iostream>
#include <ostream>
#include <time.h>
#include <TF1.h>
#include "TMath.h"

Double_t fitFunction(Double_t *x, Double_t *par) {
//    return par[0] + par[1]*(TMath::Exp(par[2] * x[0]));
    return par[0] ;
}

const int nPar = 1; // number of parameters in the fit

void fake_Fit_Electron() {
    TFile* fIN = TFile::Open("Fake_estimate_Electron.root");
    fIN->ls();

    Double_t fitRangeMin = 10,
            fitRangeMax = 90;



    TF1* theFit = new TF1("theFit", fitFunction, fitRangeMin, fitRangeMax, nPar);

    theFit->SetParameter(0, 0.012);
    theFit->SetParameter(1, 0.18);
    theFit->SetParameter(2, -0.095);
    //    theFit->SetParLimits(0, 0.2, 1.);
    //    theFit->SetParLimits(0, 0.95, 1.);


    TCanvas* canvas = new TCanvas("canvas", "", 700, 500);
    canvas->SetFillColor(0);

//    setTDRStyle();


    canvas->cd(1);

    Fake_R->SetMarkerColor(3);
    Fake_R->SetMarkerSize(1.4);
    Fake_R->SetMarkerStyle(20);
    Fake_R->GetXaxis()->SetTitle("#tau Pt [GeV]");
    Fake_R->GetXaxis()->SetTitleOffset(1);
    Fake_R->GetXaxis()->SetTitleSize(0.05);
    Fake_R->GetYaxis()->SetTitle("Fake Rate");
    Fake_R->GetYaxis()->SetRangeUser(0, 1);
    Fake_R->GetYaxis()->SetTitleOffset(1.3);
    Fake_R->GetYaxis()->SetTitleSize(0.05);
    Fake_R->Draw("PAE");

    Fake_R->Fit("theFit", "R0");
    theFit->SetRange(10, 100);
    theFit->SetLineColor(kRed);
    theFit->SetLineWidth(2);
    theFit->Draw("SAME");
    canvas->Write("Fake_fit_Loose.png");

    TLatex * tex = new TLatex(63, 0.06, "Electron fake rate (Data)");
    tex->SetTextSize(0.05);
    tex->Draw();


    TFile *varPar = new TFile("Fake_fit_Electron.root", "RECREATE");
    varPar->cd();

    TH1F * FitVar_FitError = new TH1F("FitVar_FitError", "FitVar_FitError", 6, 0, 6);
    Double_t TauLegParameters[nPar];
    theFit->GetParameters(TauLegParameters);
    for (int i = 0; i < nPar; i++) {
        cout << "par" << i << " = " << TauLegParameters[i] << endl;
        cout << "par" << i << " = " << theFit->GetParError(i) << endl;
        FitVar_FitError->SetBinContent((2 * i + 1), TauLegParameters[i]);
        FitVar_FitError->SetBinContent((2 * i + 2), theFit->GetParError(i));
    }
    varPar->Write();
    varPar->Close();

}
