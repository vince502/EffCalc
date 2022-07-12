#include "calculateEff.C"
//TFile* f1 = TFile::Open("/home/vince402/RunPrep_2022/EffCalc/MatchTree/JPsiEMB/v2_11_Gen_Mass/outputMatchTree_L2DoubleMuOpen_SampleType1_JPsiEMB_v2.root");
//TFile* f2 = TFile::Open("/home/vince402/RunPrep_2022/EffCalc/MatchTree/JPsiEMB/v2_11_Gen_Mass/outputMatchTree_L3DoubleMuOpen_SampleType1_JPsiEMB_v2.root");

//TFile* f1 = TFile::Open("/home/vince402/RunPrep_2022/EffCalc/MatchTree/MuonGun/LowPt_v2_11_Gen_acc/outputMatchTree_HLT_HIL2Mu0_v_SampleType3_MuGunLowPt_v2.root");
//TFile* f2 = TFile::Open("/home/vince402/RunPrep_2022/EffCalc/MatchTree/MuonGun/LowPt_v2_11_Gen_acc/outputMatchTree_HLT_HIL3Mu0_v_SampleType3_MuGunLowPt_v2.root");
//bool singleMu = true;

TFile* f1 = TFile::Open("/home/vince402/RunPrep_2022/EffCalc/MatchTree/UpsiEMB/v2_11_GENMatching/outputMatchTree_L2DoubleMuOpen_SampleType2_UpsiEMB_v2.root");
TFile* f2 = TFile::Open("/home/vince402/RunPrep_2022/EffCalc/MatchTree/UpsiEMB/v2_11_GENMatching/outputMatchTree_L3DoubleMuOpen_SampleType2_UpsiEMB_v2.root");
bool singleMu = false;

TTree* t1 = (TTree*) f1->Get("oniaTree");
TTree* t2 = (TTree*) f2->Get("oniaTree");
void getConditional(TTree* l2, TTree* l3, TH1D* hist, bool passL2, bool passL3, string obs = "dipt" );
void test_triggerCompare( double rngdo, double rngup, bool one, bool two, string obs= ""){
	TH1D* hist = new TH1D("s", "", 100, rngdo, rngup );
	getConditional(t1, t2, hist, one, two, obs);
	hist->Draw();
}

int getPassed(TTree* t0, double cut){
	return t0->GetEntries(Form("dr1  < %f && dr2 < %f", cut, cut));
};

void getConditional(TTree* l2, TTree* l3, TH1D* hist, bool passL2, bool passL3, string obs = "dipt" ){
	double cutter;
	double l2pt, l3pt;
	double l2evt, l3evt;
	double l2dr1, l2dr2;
	double l3dr1, l3dr2;
	l2->SetBranchAddress("dr1", &l2dr1);
	if( !singleMu ) l2->SetBranchAddress("dr2", &l2dr2);
	l3->SetBranchAddress("dr1", &l3dr1);
	if( !singleMu ) l3->SetBranchAddress("dr2", &l3dr2);

	l2->SetBranchAddress("dipt", &cutter);

	l2->SetBranchAddress(Form("%s", obs.c_str()), &l2pt);
	l3->SetBranchAddress(Form("%s", obs.c_str()), &l3pt);

	l2->SetBranchAddress("evtNb", &l2evt);
	l3->SetBranchAddress("evtNb", &l3evt);
	l3->BuildIndex("eventNb");

	for( auto idx : ROOT::TSeqI(l2->GetEntries()) ){
		l2->GetEntry(idx);
		int chksum = l3->GetEntryWithIndex( l2evt );
		if( chksum < 0 ) continue;
		if( cutter > 8 && !singleMu  ) continue;
		if(
			(( (l2dr1 < 0.3 && l2dr2 < 0.3 )==passL2 ) &&
			( (l3dr1 < 0.1 && l3dr2 < 0.1 )==passL3 ))||
			(singleMu && ( (l2dr1 < 0.3 )==passL2 ) &&
			( (l3dr1 < 0.1  )==passL3 ))
			) hist->Fill(l3pt); 
	};
};
