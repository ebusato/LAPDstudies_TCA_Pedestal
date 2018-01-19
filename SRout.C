
void SRout() {
  gStyle->SetPadGridX(1);
  gStyle->SetPadGridY(1);

  TFile* f = new TFile("/home/ebusato/Travail/gowork2/src/gitlab.in2p3.fr/avirm/analysis-go/dpgatca/godaq/file.root", "read");
  f->Print();
  TTree* t = (TTree*) f->Get("tree");

  TCanvas* c = new TCanvas("c", "c", 800, 1200);
  int nrows = 6;
  int ncols = 2;
  c->Divide(ncols,nrows);
  for(int i=1; i<=ncols*nrows; i++) {
    c->cd(i);
    gPad->SetTopMargin(0);
    gPad->SetBottomMargin(0.15);
    TString cut("Evt == ");
    cut+=i;
    cout << cut << endl;
    if(i%2!=0) {  
      t->Draw("Pulse[0]:SampleTimes", cut.Data());
    } else {
      t->Draw("Pulse[0]:CapaId[0]", cut.Data());
    }
  }
}
