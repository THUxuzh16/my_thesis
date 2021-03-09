
void compare(const char* var,double min,double max,int bin,TString xTitle, TString yTitle, bool legend ){

   gROOT->ProcessLine(".x ~/lhcbStyle.C");
   gStyle->SetOptStat(0);

   TString name = var;
   TChain* mc = new TChain("DecayTree");
   mc->Add("/home/xuzh/work/PentaQuark/New_Lb2Lc/RootFiles/Lb2Lckkpi/mc/down11/Lb2Lckkpi_pre_clone_BDTG_pty_ntrack_dalitz_poli.root");
   mc->Add("/home/xuzh/work/PentaQuark/New_Lb2Lc/RootFiles/Lb2Lckkpi/mc/up11/Lb2Lckkpi_pre_clone_BDTG_pty_ntrack_dalitz_poli.root");
   mc->Add("/home/xuzh/work/PentaQuark/New_Lb2Lc/RootFiles/Lb2Lckkpi/mc/down12/Lb2Lckkpi_pre_clone_BDTG_pty_ntrack_dalitz_poli.root");
   mc->Add("/home/xuzh/work/PentaQuark/New_Lb2Lc/RootFiles/Lb2Lckkpi/mc/up12/Lb2Lckkpi_pre_clone_BDTG_pty_ntrack_dalitz_poli.root");
   TChain* data = new TChain("DecayTree");
   data->Add("/home/xuzh/work/PentaQuark/New_Lb2Lc/RootFiles/Lb2Lckkpi/data/with_weight/Lb2Lckkpi_pre_clone_mul_BDTG_weight.root");

   TCanvas* c = new TCanvas("c","c",800,600);

   TH1F* h1 = new TH1F(name+"_mc",name,bin,min,max);
   h1->SetMinimum(0);
   mc->Project(name+"_mc",name,"weight");
   h1->SetLineColor(2);
   h1->GetXaxis()->SetTitle(xTitle);
   h1->GetYaxis()->SetTitle(yTitle);
   h1->Sumw2();
   h1->Scale(1./h1->Integral());
   //h1->Draw();
   h1->SetMinimum(0);


   TH1F* h2 = new TH1F(name+"_data",name,bin,min,max);
   data->Project(name+"_data",name,"Sweight_sig");
   h2->SetLineColor(4);
   h2->GetXaxis()->SetTitle(xTitle);
   h2->GetYaxis()->SetTitle(yTitle);
   h2->Sumw2();
   h2->SetMinimum(0);
   h2->Scale(1./h2->Integral());
   h2->Draw("");
   h1->Draw("same");


   TLegend *le = new TLegend(0.7,0.9,0.9,0.7);
   le->AddEntry(h1,"MC","l");
   le->AddEntry(h2,"data","l");
   if (legend == true){
	le->Draw();
   }

   c->SaveAs(name+".pdf");

   delete c;
   delete h1;
   delete h2;
   delete mc;
   delete data;
   delete le;
}


void check(){

 compare("Lb_PT",500,40000,10,"p_{T} of #Lambda_{b}^{0}","",1);
 compare("Lb_y",2,6,10,"y","",0);

 compare("nTracks",0,600,6,"nTracks","",0);
 
 compare("mkp",1400,2200,10,"mass of K and p","",0);
 compare("mkpi",600,1400,10,"mass of K and #pi","",0);

 compare("cosTheta",-1,1,15,"cos#theta","",0);
 compare("phi",-3.14,3.14,8,"#phi","",0);
 compare("cosTheta_pk",-1,1,15,"cos#theta_{pK}","",0);
 compare("phi_pk",-3.14,3.14,8,"#phi_{pK}","",0);

 compare("MLP",0.2,1,7,"MLP","",0);

 compare("LbKpPi_M",600,2500,10,"m(K^{+}#pi from #Lambda_{b})","",0);
 compare("LbKpKmPi_M",1100,3200,10,"m(K^{+}K^{-}#pi from #Lambda_{b})","",0);

}





