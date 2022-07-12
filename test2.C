#include "calculateEff.C"

EffCalc calc = EffCalc("../store/openHLT_NewMumenu_MuonGunHighPt_half_v2_11.root", "../store/Oniatree_JPsiEMB_pTHatMin2_MuonSelAll_CMSSW_12_3_0.root");
TCanvas* c1 = new TCanvas();

void test2(){
	TH1D* h1 = new TH1D("pt","", 50, 0, 50);
	TH1D* h2 = new TH1D("pt2","y", 50, 0, 50);
	calc.dataType = kMCJP;
	calc.getDimu = true;
	calc.isL1 = true;
	calc.level = 3;
	calc.setTrigger("HLT_HIL1Mu0_v");
	calc.setTriggerLvl(1);
	for( auto idx : ROOT::TSeqI(30000) ){
//		calc.oniaData.GetEntry(idx);
		calc.hltData.GetEntry(idx);
//		auto res = calc.oniaData.getEventContent(true, false);
		auto res = calc.hltData.getEventContent();
//		auto res2=  filterOniaData(oniaData.getEventContent( getDimu, isL1 ));
		auto res2 = calc.hltData.filterHltData(res);
//		auto res2=  calc.filterOniaData(res);
		for( auto x : res ){
			if( x["front"].val == 1 ) continue;
//			std::cout << x["dbmu"].dmu.Y();
			h1->Fill(x["mu"].mu.Pt() );
		}
		for( auto x : res2 ){
			if( x["front"].val == 1 ) continue;
//			std::cout << x["dbmu"].dmu.Y() << ", ";
			h2->Fill(x["mu"].mu.Pt() );
			//h2->Fill(x["dbmu"].dmu.Y() );
		}
	}
	h2->SetLineColor(kRed);
	c1->cd() ;
	h1->Draw();
	h2->Draw("same");
	c1->SetLogy();
}
