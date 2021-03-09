
void draw(TString name, double cell_size, double min, double max){

	gROOT->ProcessLine(".x ~/lhcbStyle.C");
	gStyle->SetOptStat(0);

	TString chainname = name+".root";
	TString plotname = name+"_res.pdf";	

	TChain* oldtree = new TChain("Res");
	oldtree->Add("../../data/"+chainname);
	
	TH1F* h_before = new TH1F("h_before","h_before",50, min, max);
	oldtree->Project("h_before","x_Rec_Cell-x_True_Cell");
	TH1F* h_after = new TH1F("h_after","compare resolution",50, min, max);
	oldtree->Project("h_after","x_Cali_Cell-x_True_Cell");

	TCanvas *c1 = new TCanvas("c1","c1",200,10,500,400);

	h_after->SetLineColor(kRed);
	h_after->SetTitle("position resolution "+name);
	h_after->GetXaxis()->SetTitle("x_Rec-xTrue/[mm]");
	h_before->SetLineColor(kBlue);

	h_after->Draw("e1");
	h_before->Draw("e1 same");

	auto legend = new TLegend(0.14,0.6,0.45,0.9);
	legend->SetHeader(name + " region");
	legend->AddEntry("h_after","After Cali","l");
	legend->AddEntry("h_before","Before Cali","l");
	legend->Draw();

	c1->SaveAs(plotname);
}
void compare(){
	gROOT->ProcessLine(".x ~/old_home/lhcbStyle.C");
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0); 	
	draw("inner",40.4,-20.2/2,20.2/2);
	draw("middle",60.6,-40.4/2,40.4/2);
	draw("outter",121.2,-40.4,40.4);
}


