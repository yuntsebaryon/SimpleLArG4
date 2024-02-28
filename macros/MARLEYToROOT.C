#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

std::vector<int> vpdg;
std::vector<double> vE;
std::vector<double> vpx;
std::vector<double> vpy;
std::vector<double> vpz;
std::vector<double> vm;

void MARLEYToROOT(std::string infile = "events.ascii", TString outfile = "in_MARLEY.root")
{
  float event = 0;

  TTree *t = new TTree();

  t->Branch("event",event);
  t->Branch("pdg",&vpdg);
  t->Branch("E",&vE);
  t->Branch("px",&vpx);
  t->Branch("py",&vpy);
  t->Branch("pz",&vpz);
  t->Branch("m",&vm);


  std::ifstream ifs;
  ifs.open(infile);

  std::string line;

  while (std::getline(ifs,line)){
    if (line.length() < 5) continue;

    int pdg;
    double E, px, py, pz, m;

    std::cout << "Start " << line << std::endl;

    std::size_t pos = line.find(" ");
    if (pos > 40) continue;
    //if (pos == 1) continue;
    
    if (pos==1 && line.substr(0,2)=="2 "){
      std::cout << "have a new " << std::endl;
      if (vE.size()>0){
	event = t->GetEntries();
	t->Fill();
      }

      vpdg.clear();
      vE.clear();
      vpx.clear();
      vpy.clear();
      vpz.clear();
      vm.clear();

    }
    if (pos==1) continue;


    pdg = std::stod(line.substr(0,pos));
    line = line.substr(pos+1,line.length()-pos);

    pos = line.find(" ");
    E = std::stod(line.substr(0,pos));
    line = line.substr(pos+1,line.length()-pos);

    pos = line.find(" ");
    px = std::stod(line.substr(0,pos));
    line = line.substr(pos+1,line.length()-pos);

    pos = line.find(" ");
    py = std::stod(line.substr(0,pos));
    line = line.substr(pos+1,line.length()-pos);

    pos = line.find(" ");
    pz = std::stod(line.substr(0,pos));
    line = line.substr(pos+1,line.length()-pos);

    pos = line.find(" ");
    m = std::stod(line.substr(0,pos));
    line = line.substr(pos+1,line.length()-pos);

    std::cout << pdg << std::endl;
    std::cout << vpdg.size() << std::endl;
    std::cout << "End " << event << "  " << pdg << "  " << E << "  " << px << "  " << py << "   " << pz << "  " << m << std::endl;

    if (pdg == 12 || pdg == 11 || pdg == 22 || pdg == 2212 || pdg==2112){
      vpdg.push_back(pdg);
      vE.push_back(E);
      vpx.push_back(px);
      vpy.push_back(py);
      vpz.push_back(pz);
      vm.push_back(m);
    }
  }

  if (vE.size()>0){
	  event = t->GetEntries();
	  t->Fill();
  }

  vpdg.clear();
  vE.clear();
  vpx.clear();
  vpy.clear();
  vpz.clear();
  vm.clear();

  TFile *out = new TFile(outfile, "recreate");
  t->Write("kin");

}
