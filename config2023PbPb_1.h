#pragma once
#include "pset.h"
#include "util.h"
#include "Reader.h"
#include "EffCalc.h"
#include "ObjectTree.h"

#define GLB_DPT_CUT "On"
	std::map<string, std::pair<double, double> > oniaFilterJPsi{{"m", {2.6, 3.5}} };
	std::map<string, std::pair<double, double> > oniaFilterUpsilon{{"m", {8.5,10.5}} };
	std::map<int, std::pair<double, double> > hltPtFilter{
		{1, { 0., 0.}},
		{2, { 2.8, 2.8}},
		{3, { 2., 2.}},
	};


	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_2023HIMuonPbPb_JPsi_v0_1.root";
	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_126X_MC_miniAOD_PYTHIA_Jpsi.root";
	string file_output = Form("output_JPsiEMB126X_v0_1_GenMatched_hltMassCut_dPt_%s_v1_iter0_1.root", GLB_DPT_CUT);
	unsigned int dType = kMCJP; string tag = "JPsi";

	std::map<string, std::pair<double, double> > oniaFilter{{"m", {2.6, 3.5}} };
	std::map<int, std::pair<double, double> > hltFilter{ 
		{1, {0., 9999.}},
		{2, {0., 9999.}},
		{3, {0., 9999.}},
	} ;
	static string SUBDIR= "PbPb2023/JPsiEMB/v0_1_Gen_1";




