#pragma once
#include "pset.h"
#include "util.h"
#include "Reader.h"
#include "EffCalc.h"
#include "ObjectTree.h"

#define GLB_DPT_CUT "On"

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_Gmenu_JPsiEMB_NoSPClimit_v1230_v8.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_Jpsi_Embedded_CMSSW_12_3_0_pre1_20220312.root";
//	string file_output = "output_MCJpsiEMB.root";
//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_data2018MB_NewMenu_v9.root";
//	string file_name_onia = "/home/CMS/soohwan/store/OniaTree_miniAOD_HIMBPD2_Run327237_MuonNoSel.root";
//	string file_output = "output_Data2018_newMenudRCut0p3.root";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_HIMuon_LegacyTrigger_MBPD2018.root";
//	string file_name_onia = "/home/CMS/soohwan/store/OniaTree_miniAOD_HIMBPD2_Run327237_MuonNoSel.root";
//	string file_output = "output_Data2018_LegacydR0p3.root";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_data2018MB_NewMenu_v2_6.root";
//	string file_name_onia = "/home/CMS/soohwan/store/OniaTree_miniAOD_HIMBPD2_Run327237_MuonNoSel.root";
//	string file_output = "output_Data2018_v2_6.root";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_data2018MB_NewMenu_v2_7_mod1.root";
//	string file_name_onia = "/home/CMS/soohwan/store/OniaTree_miniAOD_HIMBPD2_Run327237_MuonNoSel.root";
//	string file_output = "output_Data2018_v2_7_mod1_test.root";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_JPsi_v2_9.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_Jpsi_CMSSW_12_3_0_pre1_20220312.root";
//	string file_output = "output_JPsi_v2_9_test.root";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMuMenu_DataMBPD2_v2_11.root";
//	string file_name_onia = "/home/CMS/soohwan/store/OniaTree_miniAOD_HIMBPD2_Run327237_MuonNoSel.root";
//	string file_output = "output_Run2MBPD_v2_11_JPsiAcc.root";
//	unsigned int dType = kMCJP; string tag = "DataRun2MB";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0., 9999.}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {0., 9999.}},
//		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "DataRun2/MB_v2_11_JPsiAcc";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMuMenu_DataMBPD2_v2_11.root";
//	string file_name_onia = "/home/CMS/soohwan/store/OniaTree_miniAOD_HIMBPD2_Run327237_MuonNoSel.root";
//	string file_output = "output_Run2MBPD_v2_11_JPsiAcc.root";
//	unsigned int dType = kMCJP; string tag = "DataRun2MB";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0., 9999.}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {0., 9999.}},
//		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "DataRun2/MB_v2_11_JPsiAcc";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_dataMBPD2_MuonTriggerBase_v2_V11_wholeRange.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_miniAOD_HIMBPD2_FullRun_MuonNoSel.root";
//	string file_output = "output_Run2MBPD_full_v2_11_JPsiAcc.root";
//	unsigned int dType = kData; string tag = "DataRun2MB";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0., 9999.}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {0., 9999.}},
//		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "DataRun2/MBPD2Full_v2_11_JPsiAcc";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_data2018MB_NewMenu_v2_15.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_miniAOD_HIMBPD2_FullRun_MuonNoSel.root";
//	string file_output = "output_Run2MBPD_full_v3_15_JPsiAcc.root";
//	unsigned int dType = kData; string tag = "DataRun2MB";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0., 9999.}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {0., 9999.}},
//		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "DataRun2/MBPD2Full_v3_15_JPsiAcc";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_JPsiEMB_v2_9.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_Jpsi_Embedded_CMSSW_12_3_0_pre1_20220312.root";
//	string file_output = "output_JPsiEMB_v2_9_testNcollWeight.root";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_JPsiEMB_pTHat2_v2_9.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_JPsiEMB_pTHatMin2_MuonSelAll_CMSSW_12_3_0.root";
//	string file_output = "output_pTHat2_JPsiEMB_v2_9.root";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_JPsiEMB_pTHat2_v2_11.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_JPsiEMB_pTHatMin2_MuonSelAll_CMSSW_12_3_0.root";
//	string file_output = "output_pTHat2_JPsiEMB_v2_11_GetMatched_customFilterM2p6t03p5.root";
//	unsigned int dType = kMCJP; string tag = "JPsiEMB";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {2.6, 3.5}} };
//	std::pair<double, double> hltFilter{2.2, 4.4} ;

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_JPsiEMB_pTHat2_v2_11.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_JPsiEMB_pTHatMin2_MuonSelAll_CMSSW_12_3_0.root";
//	string file_output = "output_pTHat2_JPsiEMB_v2_11_GetMatched.root";
//	unsigned int dType = kMCJP; string tag = "JPsiEMB";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0., 999.}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {0., 9999.}},
//		{3, {0., 9999.}},
//	} ;


//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_JPsiEMB_pTHat2_v3_5.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_JPsiEMB_pTHatMin2_MuonSelAll_CMSSW_12_3_0.root";
//	string file_output = Form("output_pTHat2_JPsiEMB_v3_5_GenMatched_customFilterM2p6t03p5_hltMass_dPt%s_SumET.root", GLB_DPT_CUT);
//	unsigned int dType = kMCJP; string tag = "JPsiEMB";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {2.6, 3.5}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {1.0, 6.5}},
//		{3, {2.0, 4.0}},
//	} ;
//	static string SUBDIR= "JPsiEMB/v3_5_Gen_Mass";


//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_JPsiEMB_pTHat2_v2_11.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_JPsiEMB_pTHatMin2_MuonSelAll_CMSSW_12_3_0.root";
//	string file_output = "output_pTHat2_JPsiEMB_v2_11_GenMatched_fakeL1.root";
//	unsigned int dType = kMCJP; string tag = "JPsiEMB";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0., 100.}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {0., 9999.}},
//		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "JPsiEMB/v2_11_Gen_Mass";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_JPsiEMB_pTHat2_v2_11_mod2.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_JPsiEMB_pTHatMin2_MuonSelAll_CMSSW_12_3_0.root";
//	string file_output = Form("output_pTHat2_JPsiEMB_v2_11_mod2_GenMatched_fakeL1_dPt_%s.root", GLB_DPT_CUT);
//	unsigned int dType = kMCJP; string tag = "JPsiEMB";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0., 100.}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {0., 9999.}},
//		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "JPsiEMB/v2_11_Gen_Mass";


//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_JPsi_pTHat2_v2_17.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_JPsi_pTHatMin2_CMSSW_12_3_0.root";
//	string file_output = Form("output_pTHat2_JPsi_v2_17_GenMatched_hltMassCut_dPt_%s.root", GLB_DPT_CUT);
//	unsigned int dType = kMCJP; string tag = "JPsi";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {2.6, 3.5}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {1., 6.5}},
//		{3, {2., 4.}},
//	} ;
//	static string SUBDIR= "JPsi/v2_11_Gen_Mass";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_JPsi_pTHat2_v2_19_mod2.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_JPsi_pTHatMin2_CMSSW_12_3_0.root";
//	string file_output = Form("output_pTHat2_JPsi_v2_19_GenMatched_hltMassCut_NOdRdPt_%s_v6.root", GLB_DPT_CUT);
//	unsigned int dType = kMCJP; string tag = "JPsi";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {2.6, 3.5}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {1., 6.5}},
//		{3, {2., 4.5}},
////		{1, {0., 9999.}},
////		{2, {0., 9999.}},
////		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "JPsi/v2_19_Gen_Mass_v5";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_JPsi_pTHat2_v1_7.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_JPsi_pTHatMin2_CMSSW_12_3_0.root";
//	string file_output = Form("output_pTHat2_JPsi_v3_7_GenMatched_hltMassCut_dPt_%s_v6.root", GLB_DPT_CUT);
//	unsigned int dType = kMCJP; string tag = "JPsi";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {2.6, 3.5}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {1., 6.5}},
//		{3, {2., 4.5}},
////		{1, {0., 9999.}},
////		{2, {0., 9999.}},
////		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "JPsi/v3_7_Gen_Mass_NOdRdPt";

	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_JPsi_pTHat2_v1_8_mod1.root";
	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_JPsi_pTHatMin2_CMSSW_12_3_0.root";
	string file_output = Form("output_pTHat2_JPsi_v3_8_GenMatched_hltMassCut_dPt_%s_v6.root", GLB_DPT_CUT);
	unsigned int dType = kMCJP; string tag = "JPsi";
	std::map<string, std::pair<double, double> > oniaFilter{{"m", {2.6, 3.5}} };
	std::map<int, std::pair<double, double> > hltFilter{ 
		{1, {0., 9999.}},
		{2, {1., 6.5}},
		{3, {2., 4.5}},
//		{1, {0., 9999.}},
//		{2, {0., 9999.}},
//		{3, {0., 9999.}},
	} ;
	static string SUBDIR= "JPsi/v3_8_Gen";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_JPsiEMB_pTHat2_v1_7.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_JPsiEMB_pTHatMin2_MuonSelAll_CMSSW_12_3_0.root";
//	string file_output = Form("output_pTHat2_JPsiEMB_v3_7_GenMatched_hltMassCut_dPt_%s_v6.root", GLB_DPT_CUT);
//	unsigned int dType = kMCJP; string tag = "JPsi";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {2.6, 3.5}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {1., 6.5}},
//		{3, {2., 4.5}},
////		{1, {0., 9999.}},
////		{2, {0., 9999.}},
////		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "JPsiEMB/v3_7_Gen_Mass";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_Upsilon_v1_7.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_Upsilon_MuonSelAll_CMSSW_12_3_0.root";
//	string file_output = Form("output_Upsilon_v3_7_GenMatched_hltMassCut_dPt_%s_v6.root", GLB_DPT_CUT);
//	unsigned int dType = kMCUp; string tag = "Upsi";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {7, 15}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
////		{1, {0., 9999.}},
////		{2, {1., 6.5}},
////		{3, {2., 4.5}},
//		{1, {0., 9999.}},
//		{2, {0., 9999.}},
//		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "Upsi/v3_7_Gen_Mass";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_UpsilonEMB_v1_7.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_UpsilonEMB_MuonSelAll_CMSSW_12_3_0_220629_v2.root";
//	string file_output = Form("output_UpsilonEMB_v3_7_GenMatched_hltMassCut_dPt_%s_v6.root", GLB_DPT_CUT);
//	unsigned int dType = kMCUp; string tag = "Upsi";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {7, 15}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
////		{1, {0., 9999.}},
////		{2, {1., 6.5}},
////		{3, {2., 4.5}},
//		{1, {0., 9999.}},
//		{2, {0., 9999.}},
//		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "UpsiEMB/v3_7_Gen_Mass";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_JPsiEMB_pTHat2_v2_11_mod1.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_JPsiEMB_pTHatMin2_MuonSelAll_CMSSW_12_3_0.root";
//	string file_output = "output_pTHat2_JPsiEMB_v2_11_mod1_GetMatched_customFilterM2p6t03p5.root";
//	unsigned int dType = kMCJP;
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {2.6, 3.5}} };
//	std::pair<double, double> hltFilter{2.2, 4.4} ;

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_MuonGunLowPt_v2_11.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_SingleMuPt_0p5_3_MuonSelAll_CMSSW_12_3_0.root";
//	string file_output = "output_MuonGunLowPt_v2_11.root";
//  unsigned int dType = kMCmu; string tag = "MuGunLowPt";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0.0, 9999.}} };
//	std::pair<double, double> hltFilter{0.0, 9999.} ;

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_MuonGunHighPt_half_v2_11.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_SingleMuPt_3_100_MuonSelAll_CMSSW_12_3_0_220519.root";
//	string file_output = "output_MuonGunHighPt_v2_11.root";
//	unsigned int dType = kMCmu; string tag = "MuGunHighPt";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0.0, 9999.}} };
//	std::pair<double, double> hltFilter{0.0, 9999.} ;

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_MuonGunHighPt_half_v2_11.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_SingleMuPt_3_100_MuonSelAll_CMSSW_12_3_0_220519.root";
//	string file_output = "output_MuonGunHighPt_Gen_acc_finePt_v2_11.root";
//	unsigned int dType = kMCmu; string tag = "MuGunHighPt";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0.0, 9999.}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {0., 9999.}},
//		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "MuonGun/HighPt_v2_11_Gen_acc";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_MuonGunLowPt_v2_11.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_SingleMuPt_0p5_3_MuonSelAll_CMSSW_12_3_0.root";
//	string file_output = "output_MuonGunLowPt_Gen_acc_finePt_v2_11.root";
//  unsigned int dType = kMCmu; string tag = "MuGunLowPt";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0.0, 9999.}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {0., 9999.}},
//		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "MuonGun/LowPt_v2_11_Gen_acc";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_MuonGunHighPt_half_v2_11_mod2.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_SingleMuPt_3_100_MuonSelAll_CMSSW_12_3_0_220519.root";
//	string file_output = "output_MuonGunHighPt_Gen_acc_finePt_v2_11.root";
//	unsigned int dType = kMCmu; string tag = "MuGunHighPt";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0.0, 9999.}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {0., 9999.}},
//		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "MuonGun/HighPt_v2_11_Gen_acc";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_MuonGunLowPt_v2_11_mod2.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_SingleMuPt_0p5_3_MuonSelAll_CMSSW_12_3_0.root";
//	string file_output = "output_MuonGunLowPt_Gen_acc_finePt_v2_11.root";
//  unsigned int dType = kMCmu; string tag = "MuGunLowPt";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0.0, 9999.}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {0., 9999.}},
//		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "MuonGun/LowPt_v2_11_Gen_acc";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_MuonGunEMBLowPt_v2_11.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_SingleMuPtEMB_0p5_3_MuonSelAll_CMSSW_12_3_0.root";
//	string file_output = "output_MuonGunEMBLowPt_Gen_acc_finePt_v2_11.root";
//	unsigned int dType = kMCmu; string tag = "MuGunEMBLowPt";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0.0, 9999.}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {0., 9999.}},
//		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "MuonGunEMB/LowPt_v2_11_GENMatching";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_MuonGunHighEMBPt_half_v2_11.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_SingleMuPtEMB_3_100_MuonSelAll_CMSSW_12_3_0.root";
//	string file_output = "output_MuonGunEMBHighPt_Gen_acc_finePt_v2_11.root";
//	unsigned int dType = kMCmu; string tag = "MuGunEMBHighPt";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0.0, 9999.}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {0., 9999.}},
//		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "MuonGunEMB/HighPt_v2_11_GENMatching";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_MuonGunEMBLowPt_v2_11_mod2.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_SingleMuPtEMB_0p5_3_MuonSelAll_CMSSW_12_3_0.root";
//	string file_output = "output_MuonGunEMBLowPt_Gen_acc_finePt_v2_11.root";
//	unsigned int dType = kMCmu; string tag = "MuGunEMBLowPt";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0.0, 9999.}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {0., 9999.}},
//		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "MuonGunEMB/LowPt_v2_11_GENMatching";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_MuonGunHighEMBPt_half_v2_11_mod2.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_SingleMuPtEMB_3_100_MuonSelAll_CMSSW_12_3_0.root";
//	string file_output = "output_MuonGunEMBHighPt_Gen_acc_finePt_v2_11.root";
//	unsigned int dType = kMCmu; string tag = "MuGunEMBHighPt";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0.0, 9999.}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {0., 9999.}},
//		{3, {0., 9999.}},
//	} ;
//	static string SUBDIR= "MuonGunEMB/HighPt_v2_11_GENMatching";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_UpsiEMB_v2_11.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_UpsilonEMB_MuonSelAll_CMSSW_12_3_0_220629_v2.root";
//	string file_output = "output_UpsiEMB_v2_11_OniaM8to10_GENMatched_accPt4.root";
//	unsigned int dType = kMCUp; string tag = "UpsiEMB";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {8., 10.}} };
//	std::pair<double, double> hltFilter{0, 999.} ;

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_UpsiEMB_v2_11.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_UpsilonEMB_MuonSelAll_CMSSW_12_3_0_220629_v2.root";
//	string file_output = "output_UpsiEMB_v2_11_GENMatched_accPt4_hltMass.root";
//	unsigned int dType = kMCUp; string tag = "UpsiEMB";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0., 9999.}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {7., 11.}},
//		{3, {8., 10.}},
//	} ;

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_UpsiEMB_v2_11.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_UpsilonEMB_MuonSelAll_CMSSW_12_3_0_220629_v2.root";
//	string file_output = "output_UpsiEMB_v2_11_GENMatched_accJpsi_hltMass.root";
//	unsigned int dType = kMCJP; string tag = "UpsiEMB";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0., 9999.}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {7., 11.}},
//		{3, {8., 10.}},
//	} ;
//	static string SUBDIR= "UpsiEMB/v2_11_GENMatching";

//	string file_name_hlt = "/home/CMS/soohwan/store/openHLT_NewMumenu_UpsiEMB_v2_11.root";
//	string file_name_onia = "/home/CMS/soohwan/store/Oniatree_UpsilonEMB_MuonSelAll_CMSSW_12_3_0_220629_v2.root";
//	string file_output = "output_UpsiEMB_v2_11_GENMatched_accJpsi_muSize2.root";
//	unsigned int dType = kMCJP; string tag = "UpsiEMB";
//	std::map<string, std::pair<double, double> > oniaFilter{{"m", {0., 9999.}} };
//	std::map<int, std::pair<double, double> > hltFilter{ 
//		{1, {0., 9999.}},
//		{2, {7., 11.}},
//		{3, {8., 10.}},
//	} ;
//	static string SUBDIR= "UpsiEMB/v2_11_GENMatching";
