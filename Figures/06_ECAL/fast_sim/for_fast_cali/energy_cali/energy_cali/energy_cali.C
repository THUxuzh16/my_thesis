
void draw(TString name, double cell_size, double min, double max){

	gROOT->ProcessLine(".x ~/lhcbStyle.C");
	gStyle->SetOptStat(0);
 

	TString chainname = name+".root";
	TString plotname = name+"_energy.pdf";	

	TChain* oldtree = new TChain("Res");
	oldtree->Add("../../data/"+chainname);

	TCanvas *c1 = new TCanvas("c1","energy bias",500,400);

	TH1F* h = new TH1F("h","h",100,-0.15,0.15);
	oldtree->Project("h","pDiff/pGen");
	h->GetXaxis()->SetTitle("(E_{rec}-E_{gen})/E_{gen}");

	//gr->GetYaxis()->SetTitle("x true hit position/[mm]");
	//h->SetMarkerStyle(21);
	//h->SetLineColor(2);
	h->Draw("H");
	
	TLine *line = new TLine(h->GetMean(),0,h->GetMean(),1.05*h->GetMaximum());
	line->SetLineColor(2);
	line->Draw("same");

	auto legend = new TLegend(0.6,0.75,0.9,0.85);
	legend->SetHeader(name+" region:");
	legend->AddEntry("h", Form("bias is: %.5f",h->GetMean()) ,"l");
	//legend->AddEntry("gr",Form("b=%.6f; f=%.6f",f->GetParameter(1),f->GetParameter(2)),"l");
	//legend->AddEntry((TObject*)0, Form("b=%.6f; f=%.6f",f->GetParameter(1),f->GetParameter(2)), "");
	legend->Draw();

	c1->SaveAs(plotname);
	
}
void energy_cali(){
	draw("inner",40.4,-15,15);
	draw("middle",60.6,-20,20);
	draw("outter",121.2,-31,31);
}


