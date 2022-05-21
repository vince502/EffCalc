#pragma once
#include "Reader.h"

readerBase::readerBase( std::string name_file ){
	file = TFile::Open(name_file.c_str());
};

readerBase::~readerBase(){
//	if( file ) file->Close();
};

void readerBase::setTree( std::string name_tree, std::string name_alias ="" ){
	std::string _stored_name = (name_alias.empty()) ? name_tree : name_alias; 
	map_tree[_stored_name] = (TTree*) file->Get(name_tree.c_str());
};

bool readerBase::checkBranch( std::string name_tree, std::string name_branch ){
	if( map_tree[name_tree]->FindBranch(name_branch.c_str()) == nullptr ) return false;
	return true;
};

readerHlt::readerHlt( std::string name_file ) : base( name_file) {
	base.setTree( "hltanalysis/HltTree", "HltTree");
	base.map_tree["HltTree"]->SetBranchStatus("*",0);
	base.map_tree["HltTree"]->SetBranchStatus("Run",1);
	base.map_tree["HltTree"]->SetBranchStatus("Event",1);
	base.map_tree["HltTree"]->SetBranchAddress("Run", &runNb);
	base.map_tree["HltTree"]->SetBranchAddress("Event", &eventNb);
//	vec_idx = getIndexVector();
	pts = new std::vector<Float_t>;
	etas = new std::vector<Float_t>;
	phis = new std::vector<Float_t>;
	masses = new std::vector<Float_t>;
};

readerHlt::~readerHlt(){};

void readerHlt::registerTrig( std::string _name_base_trig, std::string _name_trig = "" ){

	name_base_trig = _name_base_trig;
	nickname = ( _name_trig.empty() ) ? _name_base_trig : _name_trig;
	base.setTree( Form("hltobject/%s", _name_base_trig.c_str()) , nickname );
	isDerived = !((bool) _name_trig.empty());
	base.map_tree[nickname]->SetBranchAddress("pt", &pts);
	base.map_tree[nickname]->SetBranchAddress("eta", &etas );
	base.map_tree[nickname]->SetBranchAddress("phi", &phis);
	base.map_tree[nickname]->SetBranchAddress("mass", &masses);

	base.map_tree["HltTree"]->SetBranchStatus(_name_base_trig.c_str(),1);
	base.map_tree["HltTree"]->SetBranchAddress(_name_base_trig.c_str(), &triggered );

};

std::vector<EventData> readerHlt::getEventContent(){ 
	size_t sz = pts->size();
	std::vector<EventData> t;
	t.push_back(getEventPrimitive() );
	TLorentzVector tv;
	for( auto idx : ROOT::TSeqI(sz) ){
		tv.SetPtEtaPhiM( pts->at(idx), etas->at(idx), phis->at(idx), masses->at(idx));
		t.push_back( EventData{{"mu", content{0, std::move(tv)}}});
	}
	return std::move(t);
};

std::vector<std::pair<long, long> > readerHlt::getIndexVector(){
	std::vector<std::pair<long, long> > v;
	for( auto idx : ROOT::TSeqI(base.map_tree["HltTree"]->GetEntries()) ){
		base.map_tree["HltTree"]->GetEntry(idx);
		v.push_back(std::make_pair(static_cast<long>(idx), eventNb));
	}
	return std::move(v);
};

EventData readerHlt::getEventPrimitive(){
	return std::move(EventData{
		{"front", content{0} },
		{"Event", content{static_cast<double>(eventNb)}}, 
		{"passed", content{static_cast<double>(triggered)}}
	}
	);
};

//EventData readerHlt::getCandsContent(){
//	return EventData{"cand", TLorentzVector(pts[idx], etas[idx], phis[idx], masses[idx]};
//};

readerOnia::readerOnia( std::string name_file ) : base( name_file ){
	std::cout << "initializing Onia" << std::endl;
	base.setTree( "hionia/myTree", "myTree" );

//	vec_idx = getIndexVector();

	Reco_mu_4mom = new TClonesArray("TLorentzVector", maxCloneArraySize);
	Reco_QQ_4mom = new TClonesArray("TLorentzVector", maxCloneArraySize);
	Reco_mu_L1_4mom = new TClonesArray("TLorentzVector", maxCloneArraySize);
	std::cout << "initialized Onia" << std::endl;
	base.map_tree["myTree"]->SetBranchStatus("*", 0);
	base.map_tree["myTree"]->SetBranchStatus("eventNb", 1);
	base.map_tree["myTree"]->SetBranchStatus("Centrality", 1);
	base.map_tree["myTree"]->SetBranchStatus("SumET_HF", 1);
	base.map_tree["myTree"]->SetBranchStatus("Reco_mu_size", 1);
	base.map_tree["myTree"]->SetBranchStatus("Reco_QQ_size", 1);
	base.map_tree["myTree"]->SetBranchStatus("Reco_QQ_mupl_idx", 1);
	base.map_tree["myTree"]->SetBranchStatus("Reco_QQ_mumi_idx", 1);
	base.map_tree["myTree"]->SetBranchStatus("Reco_mu_nTrkWMea", 1);
	base.map_tree["myTree"]->SetBranchStatus("Reco_mu_nPixWMea", 1);
	base.map_tree["myTree"]->SetBranchStatus("Reco_mu_SelectionType", 1);
	base.map_tree["myTree"]->SetBranchStatus("Reco_mu_dxy", 1);
	base.map_tree["myTree"]->SetBranchStatus("Reco_mu_dz", 1);
	base.map_tree["myTree"]->SetBranchStatus("Reco_QQ_VtxProb", 1);
	base.map_tree["myTree"]->SetBranchStatus("Reco_mu_4mom", 1);
	base.map_tree["myTree"]->SetBranchStatus("Reco_mu_L1_4mom", 1);
	base.map_tree["myTree"]->SetBranchStatus("Reco_QQ_4mom", 1);
	base.map_tree["myTree"]->SetBranchAddress("eventNb", &eventNb);
	base.map_tree["myTree"]->SetBranchAddress("Centrality", &Centrality);
	base.map_tree["myTree"]->SetBranchAddress("SumET_HF", &SumET_HF);
	base.map_tree["myTree"]->SetBranchAddress("Reco_mu_size", &Reco_mu_size);
//	base.map_tree["myTree"]->SetBranchAddress("Reco_mu_whichGen", &Reco_mu_whichGen);
	base.map_tree["myTree"]->SetBranchAddress("Reco_QQ_size", &Reco_QQ_size);
	base.map_tree["myTree"]->SetBranchAddress("Reco_QQ_mupl_idx", &Reco_QQ_mupl_idx);
	base.map_tree["myTree"]->SetBranchAddress("Reco_QQ_mumi_idx", &Reco_QQ_mumi_idx);
	base.map_tree["myTree"]->SetBranchAddress("Reco_mu_nTrkWMea", &Reco_mu_nTrkWMea);
	base.map_tree["myTree"]->SetBranchAddress("Reco_mu_nPixWMea", &Reco_mu_nPixWMea);
	base.map_tree["myTree"]->SetBranchAddress("Reco_mu_SelectionType", &Reco_mu_SelectionType);
	base.map_tree["myTree"]->SetBranchAddress("Reco_mu_dxy", &Reco_mu_dxy);
	base.map_tree["myTree"]->SetBranchAddress("Reco_mu_dz", &Reco_mu_dz);
	base.map_tree["myTree"]->SetBranchAddress("Reco_QQ_VtxProb", &Reco_QQ_VtxProb);
	base.map_tree["myTree"]->SetBranchAddress("Reco_mu_4mom", &(Reco_mu_4mom));
	base.map_tree["myTree"]->SetBranchAddress("Reco_mu_L1_4mom", &(Reco_mu_L1_4mom));
	base.map_tree["myTree"]->SetBranchAddress("Reco_QQ_4mom", &(Reco_QQ_4mom));

//	base.map_tree["myTree"]->SetBranchAddress(&ZX, "ZX");

	base.map_tree["myTree"]->BuildIndex("eventNb");
};

readerOnia::~readerOnia(){
//	if( base.file ) base.file->Close();
};

std::vector<EventData> readerOnia::getEventContent(bool getDimu, bool isL1){
	std::vector<EventData> t, s;
	EventData tfront = {{"front", content{1}}, {"eventNb", content{static_cast<double>(eventNb)}}, 
		{"Centrality", content{static_cast<double>(Centrality)}},
		{"SumET_HF", content{SumET_HF}},
		{"Reco_mu_size", content{static_cast<double>(Reco_mu_size)}},
		{"Reco_QQ_size", content{static_cast<double>(Reco_QQ_size)} }
	};
	t.push_back(tfront);
	s = getMuonsContent(getDimu, isL1);
	t.insert(t.end(), std::make_move_iterator(s.begin()), std::make_move_iterator(s.end()) );
	return std::move(t);
};

std::vector<EventData> readerOnia::getMuonsContent( bool getDimu, bool isL1){
	std::vector<EventData> t;
	auto mu_4mom = ( isL1 ) ? Reco_mu_L1_4mom : Reco_mu_4mom;
	if( getDimu ){
		totQQ += (int) Reco_QQ_size;
		for( auto idx : ROOT::TSeqI( Reco_QQ_size ) ){
			t.push_back( EventData{{"dbmu", content{0, 
					TLorentzVector(std::move(*((TLorentzVector*) mu_4mom->At(Reco_QQ_mupl_idx[idx])))),
					TLorentzVector(std::move(*((TLorentzVector*)mu_4mom->At(Reco_QQ_mumi_idx[idx])))), 
					TLorentzVector(std::move(*((TLorentzVector*)Reco_QQ_4mom->At(idx))))}
				}, 
				{"Trk1", content{static_cast<double>(std::move(Reco_mu_nTrkWMea[Reco_QQ_mupl_idx[idx]]))}}, 
				{"Trk2", content{static_cast<double>(std::move(Reco_mu_nTrkWMea[Reco_QQ_mumi_idx[idx]]))}}, 
				{"Pix1", content{static_cast<double>(std::move(Reco_mu_nPixWMea[Reco_QQ_mupl_idx[idx]]))}}, 
				{"Pix2", content{static_cast<double>(std::move(Reco_mu_nPixWMea[Reco_QQ_mumi_idx[idx]]))}}, 
				{"dxy1", content{std::move(Reco_mu_dxy[Reco_QQ_mupl_idx[idx]])}}, 
				{"dxy2", content{std::move(Reco_mu_dxy[Reco_QQ_mumi_idx[idx]])}}, 
				{"dz1", content{std::move(Reco_mu_dz[Reco_QQ_mupl_idx[idx]])}}, 
				{"dz2", content{std::move(Reco_mu_dz[Reco_QQ_mumi_idx[idx]])}}, 
				{"QQVtxProb", content{std::move(Reco_QQ_VtxProb[idx])}} 
			} 
			);
		}
	}
	else {
		for( auto idx : ROOT::TSeqI(Reco_mu_size) ){
			t.push_back( EventData{{"mu", content{0, 
					TLorentzVector(std::move(*((TLorentzVector*)mu_4mom->At(idx))))}
				}, 
				{"Trk1", content{static_cast<double>(std::move(Reco_mu_nTrkWMea[idx]))}},
				{"Pix1", content{static_cast<double>(std::move(Reco_mu_nPixWMea[idx]))}},
				{"dxy1", content{Reco_mu_dxy[idx]}},
				{"dz1", content{Reco_mu_dz[idx]}}
			} 
			);
		}
	};
	return std::move(t);
};

std::vector<std::pair<long, long> > readerOnia::getIndexVector(){
	std::vector<std::pair<long, long> > v ={};
	base.map_tree["myTree"]->SetBranchStatus("*", 0);
	base.map_tree["myTree"]->SetBranchStatus("eventNb", 1);
	base.map_tree["myTree"]->SetBranchAddress("eventNb", &eventNb);
	for( auto idx : ROOT::TSeqU(base.map_tree["myTree"]->GetEntries())){
		base.map_tree["myTree"]->GetEntry(idx);
		v.push_back(std::make_pair(idx, eventNb) );	
	}
	return std::move(v);

};

void readerOnia::checkArray(){
	std::cout << "Reco_QQ_size: " << Reco_QQ_size<< std::endl;
	std::cout << "Reco_QQ_4mom size: " << Reco_QQ_4mom->LastIndex() << std::endl;
	std::cout << "Reco_mu_size: " << Reco_mu_size<< std::endl;
	std::cout << "Reco_mu_4mom size: " << Reco_mu_4mom->LastIndex() << std::endl;
	std::cout << "Reco_mu_L1_4mom size: " << Reco_mu_L1_4mom->LastIndex() <<std::endl;
};







