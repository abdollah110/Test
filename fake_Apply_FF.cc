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

Double_t fitFunction(Double_t x, Double_t par0, Double_t par1, Double_t par2) {
    return par0 + par1 * (TMath::Exp(par2 * x));
}

void fake_Apply_FF() {

    TFile *Wtnu = new TFile("Data.root");

    TFile *medium_Fake = new TFile("Fake_fit_Medium.root");
    TH1D *fake_Medium = (TH1D*) medium_Fake->Get("FitVar_FitError");
    double fake_medium_tau[6];
    for (int j = 0; j < 6; j++) {
        fake_medium_tau[j] = fake_Medium->GetBinContent(j + 1);
        //        cout << "fake_medium_tau[" << j << "]" << fake_medium_tau[j] << endl;
    }

    TFile *loose_Fake = new TFile("Fake_fit_Loose.root");
    TH1D *fake_Loose = (TH1D*) loose_Fake->Get("FitVar_FitError");
    double fake_loose_tau[6];
    for (int j = 0; j < 6; j++) {
        fake_loose_tau[j] = fake_Loose->GetBinContent(j + 1);
    }

    TFile *ele_Fake = new TFile("Fake_Electron.root");
    TH1D *fake_Ele = (TH1D*) ele_Fake->Get("fakeRate_Electron");
    double fake_electron[2];
    for (int j = 0; j < 2; j++) {
        fake_electron[j] = fake_Ele->GetBinContent(j + 1);
    }

    TFile *mu_Fake = new TFile("Fake_Muon.root");
    TH1D *fake_Mu = (TH1D*) mu_Fake->Get("fakeRate_Muon");
    double fake_muon[2];
    for (int j = 0; j < 2; j++) {
        fake_muon[j] = fake_Mu->GetBinContent(j + 1);
    }












    //*****************************************************************************************
    double result_FF[8] = {0};
    double result_FF_Err[8] = {0};
    double result_FF_Num[8] = {0};
    //*****************************************************************************************
    //*****************************************************************************************
    const char * array[] = {"FakeRate_MMTT_apply_ff", "FakeRate_EETT_apply_ff"};
    for (int g = 0; g < 2; g++) {
        TH2D *Pt_Met_Sig = (TH2D*) Wtnu->Get(array[g]);
        double estimate = 0;

        for (int i = 10; i < Pt_Met_Sig->GetNbinsX(); i++) {
            for (int j = 10; j < Pt_Met_Sig->GetNbinsY(); j++) {

                double Value = Pt_Met_Sig->GetBinContent(i + 1, j + 1);
                double FrateX = fitFunction(0.5 + i, fake_medium_tau[0], fake_medium_tau[2], fake_medium_tau[4]);
                double FrateY = fitFunction(0.5 + j, fake_medium_tau[0], fake_medium_tau[2], fake_medium_tau[4]);

                double Frate = Value * (FrateX * FrateY) / ((1 - FrateX) * (1-FrateY));
                estimate += Frate;

            }
        }
        cout << "Estimate " << array[g] << "   " << estimate << "  +-   " << estimate * sqrt(Pt_Met_Sig->GetEntries()) / Pt_Met_Sig->GetEntries() << " (" << Pt_Met_Sig->GetEntries() << ") " << endl;

        result_FF[g] = estimate;
        result_FF_Err[g] = estimate * sqrt(Pt_Met_Sig->GetEntries()) / Pt_Met_Sig->GetEntries();
        result_FF_Num[g] = Pt_Met_Sig->GetEntries();
    }
    //*****************************************************************************************
    //*****************************************************************************************
    const char * array[] = {"FakeRate_MMMT_apply_ff", "FakeRate_EEMT_apply_ff"};
    for (int g = 0; g < 2; g++) {
        TH2D *Pt_Met_Sig = (TH2D*) Wtnu->Get(array[g]);
        double estimate = 0;

        for (int i = 10; i < Pt_Met_Sig->GetNbinsX(); i++) {
            for (int j = 10; j < Pt_Met_Sig->GetNbinsY(); j++) {

                double Value = Pt_Met_Sig->GetBinContent(i + 1, j + 1);
                double FrateX = fitFunction(0.5 + i, fake_loose_tau[0], fake_loose_tau[2], fake_loose_tau[4]);
                double FrateY = fake_muon[1];

                double Frate = Value * (FrateX * FrateY) / ((1 - FrateX) * (1-FrateY));
                estimate += Frate;

            }
        }
        cout << "Estimate " << array[g] << "   " << estimate << "  +-   " << estimate * sqrt(Pt_Met_Sig->GetEntries()) / Pt_Met_Sig->GetEntries() << " (" << Pt_Met_Sig->GetEntries() << ") " << endl;
        result_FF[g + 2] = estimate;
        result_FF_Err[ g + 2] = estimate * sqrt(Pt_Met_Sig->GetEntries()) / Pt_Met_Sig->GetEntries();
        result_FF_Num[ g + 2] =  Pt_Met_Sig->GetEntries();
    }
    //*****************************************************************************************
    //*****************************************************************************************
    const char * array[] = {"FakeRate_MMET_apply_ff", "FakeRate_EEET_apply_ff"};
    for (int g = 0; g < 2; g++) {
        TH2D *Pt_Met_Sig = (TH2D*) Wtnu->Get(array[g]);
        double estimate = 0;

        for (int i = 10; i < Pt_Met_Sig->GetNbinsX(); i++) {
            for (int j = 10; j < Pt_Met_Sig->GetNbinsY(); j++) {

                double Value = Pt_Met_Sig->GetBinContent(i + 1, j + 1);
                double FrateX = fitFunction(0.5 + i, fake_loose_tau[0], fake_loose_tau[2], fake_loose_tau[4]);
                double FrateY = fake_electron[1];

                double Frate = Value * (FrateX * FrateY) / ((1 - FrateX) * (1-FrateY));
                estimate += Frate;

            }
        }
        cout << "Estimate " << array[g] << "   " << estimate << "  +-   " << estimate * sqrt(Pt_Met_Sig->GetEntries()) / Pt_Met_Sig->GetEntries() << " (" << Pt_Met_Sig->GetEntries() << ") " << endl;
        result_FF[g + 4] = estimate;
        result_FF_Err[g + 4] = estimate * sqrt(Pt_Met_Sig->GetEntries()) / Pt_Met_Sig->GetEntries();
        result_FF_Num[g + 4] =  Pt_Met_Sig->GetEntries();
    }
    //*****************************************************************************************
    //*****************************************************************************************
    const char * array[] = {"FakeRate_MMME_apply_ff", "FakeRate_EEEM_apply_ff"};
    for (int g = 0; g < 2; g++) {
        TH2D *Pt_Met_Sig = (TH2D*) Wtnu->Get(array[g]);

        double FrateX = fake_electron[0];
        double FrateY = fake_muon[0];

        double estimate = Pt_Met_Sig->GetEntries() * (FrateX * FrateY) / ((1 - FrateX) * (1-FrateY));


        cout << "Estimate " << array[g] << "   " << estimate << "  +-   " << estimate * sqrt(Pt_Met_Sig->GetEntries()) / Pt_Met_Sig->GetEntries() << " (" << Pt_Met_Sig->GetEntries() << ") " << endl;
        result_FF[g + 6] = estimate;
        result_FF_Err[g + 6] = estimate * sqrt(Pt_Met_Sig->GetEntries()) / Pt_Met_Sig->GetEntries();
        result_FF_Num[g + 6] =  Pt_Met_Sig->GetEntries();
    }
    //*****************************************************************************************
    //*****************************************************************************************

    TFile * F_Result_FF = new TFile("Result_FF.root", "RECREATE");
    F_Result_FF->cd();
    TH1D * res = new TH1D("result", "", 8, 0, 8);
    TH1D * res_err = new TH1D("result_err", "", 8, 0, 8);
    TH1D * res_num = new TH1D("result_num", "", 8, 0, 8);

    for (int j = 0; j < 8; j++) {

        res->SetBinContent(j+1, result_FF[j]);
        res_err->SetBinContent(j+1, result_FF_Err[j]);
        res_num->SetBinContent(j+1, result_FF_Num[j]);
    }

    F_Result_FF->Write();
    F_Result_FF->Close();
}


