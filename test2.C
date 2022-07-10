#include "calculateEff.C"

EffCalc calc = EffCalc("../store/openHLT_Gmenu_JPsiEMB_NoSPClimit_v1230_v8.root", "../store/Oniatree_JPsiEMB_pTHatMin2_MuonSelAll_CMSSW_12_3_0.root");
TCanvas* c1 = new TCanvas();

void test2(){
	TH1D* h1 = new TH1D("y","y", 2480, -124,124);
	TH1D* h2 = new TH1D("y1","y", 2480, -124,124);
	calc.dataType = kMCJP;
	calc.getDimu = true;
	calc.isL1 = false;
	calc.level = 3;
	for( auto idx : ROOT::TSeqI(300000) ){
		calc.oniaData.GetEntry(idx);
		auto res = calc.oniaData.getEventContent(true, false);
//		auto res2=  filterOniaData(oniaData.getEventContent( getDimu, isL1 ));
		auto res2=  calc.filterOniaData(res);
		for( auto x : res ){
			if( x["front"].val == 1 ) continue;
//			std::cout << x["dbmu"].dmu.Y();
			h1->Fill(x["dbmu"].dmu.Y() );
		}
		for( auto x : res2 ){
			if( x["front"].val == 1 ) continue;
//			std::cout << x["dbmu"].dmu.Y() << ", ";
			h2->Fill(x["dbmu"].dmu.Y() );
		}
	}
	h2->SetLineColor(kRed);
	c1->cd() ;
	h1->Draw();
	h2->Draw("same");
	c1->SetLogy();
}
