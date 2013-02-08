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

void final_Results() {




    TFile *FF = new TFile("Result_FF.root");
    TH1D *ff_res = (TH1D*) FF->Get("result");
    TH1D *ff_res_err = (TH1D*) FF->Get("result_err");
    TH1D *ff_res_num = (TH1D*) FF->Get("result_num");

    TFile *FP = new TFile("Result_FP.root");
    TH1D *fp_res = (TH1D*) FP->Get("result");
    TH1D *fp_res_err = (TH1D*) FP->Get("result_err");
    TH1D *fp_res_num = (TH1D*) FP->Get("result_num");

    TFile *PF = new TFile("Result_PF.root");
    TH1D *pf_res = (TH1D*) PF->Get("result");
    TH1D *pf_res_err = (TH1D*) PF->Get("result_err");
    TH1D *pf_res_num = (TH1D*) PF->Get("result_num");

    cout.setf(ios::fixed,ios::floatfield);
cout.precision(2);

   //***************************

cout<<"\n\n"<<"\\begin{table}[htbp]"<<endl;
cout<<"\\centering"<<endl;
cout<<"\\caption{ events}"<<endl;
cout<<"\\label{table:events}"<<endl;
cout<<"\\begin{tabular}{|c|c|c|c|c| }"<<endl;
cout<<"\\hline"<<endl;
cout<<" channel & Cat0 & Cat1 & Cat2 &  1+2-0" <<  " \\\\" <<endl;
cout<<"\\hline"<<endl;

char * array[8] = {"mmtt", "eett", "mmmt", "eemt", "mmet", "eeet", "mmme", "eeem"};

    double Total_Cen_Val = 0;
    double Total_Error = 0;

    for (int i = 0; i < 8; i++) {
        double cen_val = fp_res->GetBinContent(i + 1) + pf_res->GetBinContent(i + 1) - ff_res->GetBinContent(i + 1);
        double err = sqrt(pow(fp_res_err->GetBinContent(i + 1), 2) + pow(pf_res_err->GetBinContent(i + 1), 2) + pow(ff_res_err->GetBinContent(i + 1), 2));

        Total_Cen_Val +=  cen_val;
        Total_Error +=  pow(err, 2);

        cout << array[i]<<"&"<< ff_res->GetBinContent(i + 1)<<"(" <<(int)ff_res_num->GetBinContent(i + 1) << ")"<<"&"<< fp_res->GetBinContent(i + 1)<<"(" <<(int)fp_res_num->GetBinContent(i + 1) << ")"<<"&"<<pf_res->GetBinContent(i + 1)<<"(" <<(int)pf_res_num->GetBinContent(i + 1) << ")"<<"&" <<cen_val<<" "<< "   +-   " << err<<" \\\\ "  << endl;
    }
cout<<"\\hline"<<endl;
cout<<"\\end{tabular}"<<endl;
cout<<"\\end{table}"<<endl<<endl<<endl;

    cout << "***************************************" << endl;
    cout << "Total Reducible background = " << Total_Cen_Val << "  +-  " << sqrt(Total_Error) << endl;
    cout << "***************************************" << endl;


}


