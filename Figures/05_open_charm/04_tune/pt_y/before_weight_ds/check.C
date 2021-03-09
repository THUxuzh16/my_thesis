
void compare(const char* var,double min,double max,int bin,TString xTitle, TString yTitle ){

   gROOT->ProcessLine(".x ~/lhcbStyle.C");
   gStyle->SetOptStat(0);

   TString name = var;
   TChain* mc = new TChain("DecayTree");
   mc->Add("/home/xuzh/work/PentaQuark/New_Lb2Lc/RootFiles/Lb2LcDs/mc/down11/Lb2LcDs_pre_clone_BDTG.root");
   mc->Add("/home/xuzh/work/PentaQuark/New_Lb2Lc/RootFiles/Lb2LcDs/mc/up11/Lb2LcDs_pre_clone_BDTG.root");
   mc->Add("/home/xuzh/work/PentaQuark/New_Lb2Lc/RootFiles/Lb2LcDs/mc/down12/Lb2LcDs_pre_clone_BDTG.root");
   mc->Add("/home/xuzh/work/PentaQuark/New_Lb2Lc/RootFiles/Lb2LcDs/mc/up12/Lb2LcDs_pre_clone_BDTG.root");
   TChain* data = new TChain("DecayTree");
   data->Add("/home/xuzh/work/PentaQuark/New_Lb2Lc/RootFiles/Lb2LcDs/data/with_weight/Lb2LcDs_pre_clone_mul_BDTG_weight.root");

   TCanvas* c = new TCanvas("c","c",800,600);

   TH1F* h1 = new TH1F(name+"_mc",name,bin,min,max);
   h1->SetMinimum(0);
   mc->Project(name+"_mc",name,"Lb_L0HadronDecision_TOS == 1");
   h1->SetLineColor(2);
   h1->GetXaxis()->SetTitle(xTitle);
   h1->GetYaxis()->SetTitle(yTitle);
   h1->Sumw2();
   h1->Scale(1./h1->Integral());
   h1->Draw();
   h1->SetMinimum(0);


   TH1F* h2 = new TH1F(name+"_data",name,bin,min,max);
   data->Project(name+"_data",name,"Sweight_sig");
   h2->SetLineColor(4);
   h2->Sumw2();
   h2->Scale(1./h2->Integral());
   h2->Draw("same");


   TLegend *le = new TLegend(0.7,0.9,0.9,0.7);
   le->AddEntry(h1,"MC","l");
   le->AddEntry(h2,"data","l");
//   le->Draw();

   c->SaveAs(name+".pdf");

   delete c;
   delete h1;
   delete h2;
   delete mc;
   delete data;

}


void check(){

 compare("Lb_PT",0,45000,20,"p_{T} of #Lambda_{b}^{0}","");
 compare("Lb_y",2,6,8,"y","");

 compare("nTracks",0,600,6,"nTracks","");
 
#if 0
 compare("mkp",1400,2200,10,"mass of K and p","");
 compare("mkpi",600,1400,10,"mass of K and #pi","");

 compare("cosTheta",-1,1,15,"cos#theta","");
 compare("phi",-3.14,3.14,8,"#phi","");
 compare("cosTheta_pk",-1,1,15,"cos#theta_{pK}","");
 compare("phi_pk",-3.14,3.14,8,"#phi_{pK}","");


 compare("LbKpPi_M",600,1500,20,"m(K^{+}#pi from #Lambda_{b})","");
 compare("LbKpKmPi_M",1930,2000,20,"m(K^{+}K^{-}#pi from #Lambda_{b})","");

#endif

}





