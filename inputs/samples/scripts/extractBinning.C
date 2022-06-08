#include "GenericToolbox.Root.h"

std::string inputFilePath{"./MultiPiPhotonProton_PolyBins_BANFFTH2Ds_v3.root"};
std::string outFolder{"../binning"};


std::string makeBinning(TH2Poly* h_);

void extractBinning(){

  auto* fBinning = TFile::Open(inputFilePath.c_str());
  auto histList = GenericToolbox::getListOfObjectFromTDirectory(fBinning, "TH2Poly");

  GenericToolbox::mkdirPath(outFolder);

  for( auto& hist : histList ){
    std::string outFile = outFolder + "/" + hist->GetName() + ".txt";
    std::cout << "Generating: " << outFile << std::endl;
    GenericToolbox::dumpStringInFile(outFile, makeBinning((TH2Poly*)hist));
  }

}


std::string makeBinning(TH2Poly* h_){
  std::stringstream ss;
  ss << "variables: Pmu Pmu CosThetamu CosThetamu" << std::endl;

  for( int iBin = 0 ; iBin < h_->GetBins()->GetEntries() ; iBin++ ){
    auto* bin = (TH2PolyBin*) h_->GetBins()->At(iBin);
    bin->Print("ALL");
    ss << bin->GetXMin() << " ";
    ss << bin->GetXMax() << " ";
    ss << bin->GetYMin() << " ";
    ss << bin->GetYMax() << std::endl;
  }

  return ss.str();
}
