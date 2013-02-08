#include <TGraph.h>
#include "TRandom.h"
#include "iostream.h"
#include "TCanvas.h"
#include "TMath.h"
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
#include <sstream>
#include <ostream>
#include <iomanip>

double fitFunction(double x, double par0, double par1, double par2) {
    return par0 + par1 * (TMath::Exp(par2 * x));
}

void fake_Uncertainty_Loose() {

    TFile *data = new TFile("Data.root");

    TFile *loose_Fake = new TFile("Fake_fit_Loose.root");
    TH1D *fake_Loose = (TH1D*) loose_Fake->Get("FitVar_FitError");
    double fake_loose_tau[6];
    for (int j = 0; j < 6; j++) {
        fake_loose_tau[j] = fake_Loose->GetBinContent(j + 1);
    }




    TCanvas *c1 = new TCanvas("c1", "A Simple Graph Example", 600, 600);
    c1->SetFillColor(0);
    c1->SetBorderSize(2);
    c1->SetFrameBorderMode(0);



    TH1 *frame = new TH1F("frame", "", 100, 0, 100);
    frame->SetDirectory(0);
    frame->SetStats(0);
    frame->GetXaxis()->SetTitle("p_{T}^{#tau}  [GeV]");
    frame->GetXaxis()->SetTitleSize(0.04);
    frame->GetXaxis()->SetTickLength(0.02);
    frame->GetXaxis()->SetLabelSize(0.03);
    frame->GetYaxis()->SetTitle("fake rate");
    frame->GetYaxis()->SetTitleSize(0.05);
    frame->GetYaxis()->SetTitleOffset(0.8);
    frame->GetYaxis()->SetMoreLogLabels();
    frame->GetYaxis()->SetLabelSize(0.03);
    frame->GetYaxis()->SetRangeUser(0, 0.11);
    frame->Draw(" ");


    const Int_t n = 100;
    Double_t x[n], y[n], ymax[n], ymax_0[n], ymax_1[n], ymax_2[n], ymin[n], ymin_0[n], ymin_1[n], ymin_2[n];
    for (Int_t i = 0; i < n; i++) {
        x[i] = i;



        y[i] = fitFunction(i, fake_loose_tau[0], fake_loose_tau[2], fake_loose_tau[4]);

        ymax_0[i] = fitFunction(i, fake_loose_tau[0] + fake_loose_tau[1], fake_loose_tau[2], fake_loose_tau[4]);
        ymax_1[i] = fitFunction(i, fake_loose_tau[0], fake_loose_tau[2] + fake_loose_tau[3], fake_loose_tau[4]);
        ymax_2[i] = fitFunction(i, fake_loose_tau[0], fake_loose_tau[2], fake_loose_tau[4] + fake_loose_tau[5]);
        ymax[i] = y[i] + sqrt(pow(ymax_0[i] - y[i], 2) + pow(ymax_1[i] - y[i], 2) + pow(ymax_2[i] - y[i], 2));


        ymin_0[i] = fitFunction(i, fake_loose_tau[0] - fake_loose_tau[1], fake_loose_tau[2], fake_loose_tau[4]);
        ymin_1[i] = fitFunction(i, fake_loose_tau[0], fake_loose_tau[2] - fake_loose_tau[3], fake_loose_tau[4]);
        ymin_2[i] = fitFunction(i, fake_loose_tau[0], fake_loose_tau[2], fake_loose_tau[4] - fake_loose_tau[5]);
        ymin[i] = y[i] - sqrt(pow(ymin_0[i] - y[i], 2) + pow(ymin_1[i] - y[i], 2) + pow(ymin_2[i] - y[i], 2));

//        cout << (ymax[i] - y[i]) / y[i] << "\t";
//        cout << (ymin[i] - y[i]) / y[i] << endl;

    }



    TGraph *grmax = new TGraph(n, x, ymax);
    TGraph *grmin = new TGraph(n, x, ymin);
    TGraph *gr = new TGraph(n, x, y);
    TGraph *grshade = new TGraph(2 * n);

    for (int i = 0; i < 100; i++) {

        grshade->SetPoint(i, x[i], ymax[i]);
        grshade->SetPoint(n + i, x[n - i - 1], ymin[n - i - 1]);
        //        i=i-10;
    }



    Int_t ci; // for color index setting
    ci = TColor::GetColor("#32c3ff");

    grshade->SetLineWidth(0);
    grshade->SetFillColor(ci);
    grshade->SetFillStyle(3008);



    grshade->Draw("f");


    grmin->SetLineWidth(0);
    grmin->SetLineColor(0);
    //    grmin->Draw("l");

    grmax->SetLineWidth(0);
    grmax->SetLineColor(0);
    //    grmax->Draw("l");



    gr->SetLineWidth(2);
    gr->SetMarkerSize(0);
    gr->Draw("CP");


    TFile *fIN = new TFile("Fake_estimate_Loose.root");
    TGraphAsymmErrors * Fake_R = (TGraphAsymmErrors*) fIN->Get("Fake_R");



    //    hpx_data->SetMarkerSize(1.2);
    Fake_R->SetMarkerSize(1.2);
    Fake_R->SetMarkerStyle(20);
    Fake_R->SetMarkerColor(2);
    Fake_R->Draw("OINEP");

    TLegend *l = new TLegend(0.5, 0.44, 0.7, 0.55, NULL, "brNDC");

    l->SetBorderSize(0);
    l->SetFillColor(0);
    l->SetTextSize(.04);
    l->AddEntry(Fake_R, "HPS Medium Data", "lpf");
    l->AddEntry(grshade, "Fit Uncertainty", "f");
    l->Draw();


    TLatex *t = new TLatex();
    t->SetNDC();
    t->SetTextFont(62);
    t->SetTextAlign(12);
    t->SetTextSize(0.040);
    t->DrawLatex(0.50, 0.78, "CMS Preliminary 2012");
    t->DrawLatex(0.50, 0.73, "#sqrt{s} = 8 TeV, L = 12 fb^{-1}");
    t->SetTextSize(0.025);
 

    c1->SaveAs("Fake_Uncertainty_Loose.png");
    c1->SaveAs("Fake_Uncertainty_Loose.pdf");






}


