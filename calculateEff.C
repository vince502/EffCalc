#pragma once

#include "TGraph.h"
#include <ROOT/TProcessExecutor.hxx>
#include <thread>
#include <future>
#include <execution>
#include "Reader.cc"
#include "EffCalc.cc"

static int UseNCores = 20;

void calculateEff(){
	string file_name_hlt = "../store/openHLT_Gmenu_JPsiEMB_NoL1IONoSPClimit_v1230_v8.root";
	string file_name_onia = "../store/Oniatree_Jpsi_Embedded_CMSSW_12_3_0_pre1_20220312.root";

	//std::vector<sstd::string> v_names = {"HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v", "HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_v", "HLT_HIL1DoubleMuOpen_v", "HLT_HIL2DoubleMuOpen_v", "HLT_HIL3DoubleMuOpen_v"};
//	std::vector<std::string> v_names = { "HLT_HIL1DoubleMu0_Open_v", "HLT_HIL2DoubleMu0_Open_v", "HLT_HIL3DoubleMu0_Open_v"};
//	std::vector<std::string> v_names = { "HLT_HIL1DoubleMuOpen_v", "HLT_HIL2DoubleMuOpen_v", "HLT_HIL3DoubleMuOpen_v"};
	std::vector<std::string> v_names = { "HLT_HIL1DoubleMuOpen_v","HLT_HIL2Mu0_L1DoubleMu0_v"};
	std::vector<std::string> v_names2 = { "HLT_HIL1DoubleMu0_Open_v", "HLT_HIL2DoubleMu0_Open_v", "HLT_HIL3DoubleMu0_Open_v"};
	auto trigAttr = [v_names](int idx){
		bool l1 = false;
		bool dmu =false;
		std::string _trig = v_names[idx];
		if( _trig.find("Double") != std::string::npos) dmu = true;
		if( _trig.find("HIL1") != std::string::npos) l1 = true;
		return std::make_pair(dmu, l1);
	};
	
//	EffCalc calc = EffCalc( file_name_hlt, file_name_onia );

	//Enable MultiThreading, the thread executor creates threads per trigger and make use of the available CPU cores
	ROOT::EnableImplicitMT(UseNCores);
	ROOT::TThreadExecutor mpe(v_names.size());

	//Define cuts
	std::vector<double> cuts;
	for(auto idx : ROOT::TSeqI(31)){
		cuts.push_back(0.5 *(double) idx);
	}

	//Run calculator
	int max_events = 1e+7;
	TH1::AddDirectory(false);
	auto extractEffs = [=](int idx){
		EffCalc calc = EffCalc( file_name_hlt, file_name_onia );
		calc.setTrigger(v_names[idx]);
		calc.init(trigAttr(idx));
		calc.evalAll(max_events);
		std::cout << "init done Loop!" << std::endl;
		
		return calc.getEfficiencies();
	};

	//Result container
	std::map< string, std::unordered_map<string, TEfficiency*> >result_map;
	std::map<string, TGraph*> graps;

	//Map results
	const auto& res = mpe.Map(extractEffs, ROOT::TSeqI(v_names.size()));
//	auto res= extractEffs(0);

	std::cout << "Run Fin" << std::endl;
	TFile* output = new TFile("output.root", "recreate");
	output->cd();
	for( auto idx : res ){
		output->mkdir(idx.first.c_str());
		output->cd(idx.first.c_str());
		for( auto plotp : idx.second){
			plotp.second->Write();
		}
		output->cd("/");
		result_map[idx.first] = idx.second;
	}
	output->Close();
	

	std::cout << "Draw" << std::endl;
	result_map["HLT_HIL1DoubleMuOpen_v"]["pt"]->Draw();

};
