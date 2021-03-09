double fun(Double_t *xx, Double_t *par){
	Double_t x = xx[0];
	//Double_t f = par[1] * TMath::ASinH( x/par[0]/2 * TMath::CosH(par[0]/2/par[1]) );
	Double_t f = par[2] * par[1] * TMath::ASinH( x/par[0]/2 * TMath::CosH(par[0]/2/par[1]) );
	return f;
}


void draw(TString name, double cell_size, double min, double max){

	TString chainname = name+".root";
	TString plotname = name+"_cor.pdf";	

	TChain* oldtree = new TChain("Res");
	oldtree->Add("../../data/"+chainname);

	Int_t nbin = 40;
	double x[nbin];
	double x_err[nbin];
	double y[nbin];
	double y_err[nbin];

	for(int i=0; i<40; i++){
		TH1F* tmp = new TH1F("tmp","tmp",80,-1*cell_size/2.,cell_size/2.);
		y[i] = -1*cell_size/2 + 0.5*cell_size/nbin + i*cell_size/nbin;
		y_err[i] = 0;
		TString cut = Form("x_True_Cell>%f && x_True_Cell<%f",-1*cell_size/2+i*cell_size/nbin, -1*cell_size/2+(i+1)*cell_size/nbin);
		cout << "cut: " << cut << endl;
		TTree* mytree = oldtree->CopyTree(cut);
		cout << "entries: " << mytree->GetEntries() << endl;
		mytree->Project("tmp","x_Rec_Cell");
		x[i] = tmp->GetMean();			
		x_err[i]= tmp->GetStdDev();
		cout << "x: " << x[i] << "   y: " << y[i] << endl;
		delete tmp;
	}

	TCanvas *c1 = new TCanvas("c1","relation between x_Rec and x_True",200,10,500,400);
	//TGraph* gr = new TGraphErrors(nbin,x,y,x_err,y_err);
	TGraph* gr = new TGraph(nbin,x,y);

	TF1* f = new TF1("f",fun,min,max,3);
	f->FixParameter(0,cell_size);
	f->SetParameter(1,3);
	f->SetParameter(2,1);
	f->SetLineColor(kBlue);

	TFitResultPtr r = gr->Fit("f","S B E");
	std::cout << "par0: " << f->GetParameter(0) << "  par1: " << f->GetParameter(1) << std::endl;

	gr->SetTitle("S correction " +name);
	gr->GetXaxis()->SetTitle("x rec cluster position/[mm]");
	gr->GetYaxis()->SetTitle("x true hit position/[mm]");
	gr->SetMarkerStyle(21);
	gr->SetLineColor(2);
	gr->Draw("ALP");
	f->Draw("same");

	auto legend = new TLegend(0.15,0.7,0.55,0.92);
	legend->AddEntry("f"," f #bullet b #bullet asinh( #frac{x}{#Delta} cosh #frac{#Delta}{b})  ","l");
	//legend->AddEntry("gr",Form("b=%.6f; f=%.6f",f->GetParameter(1),f->GetParameter(2)),"l");
	legend->AddEntry((TObject*)0, Form("b=%.2f; f=%.2f",f->GetParameter(1),f->GetParameter(2)), "");
	legend->Draw();


	c1->SaveAs(plotname);
	
}
void correction(){
	gROOT->ProcessLine(".x ~/old_home/lhcbStyle.C");
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0); 	

	draw("inner",40.4,-15,15);
	draw("middle",60.6,-20,20);
	draw("outter",121.2,-31,31);
}


