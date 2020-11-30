void phiplot()
{
  TFile *f = new TFile("13TeV_CR0_RHoff.root");
  TTree *tree = (TTree*)f->Get("pytree2040");
  Int_t entries = tree->GetEntries();

  const Int_t maxTrack = 40;

  Int_t ntrack = 0;
  Double_t pT[maxTrack];
  Double_t eta[maxTrack];
  Double_t rap[maxTrack];
  Double_t phi[maxTrack];

  tree->SetBranchAddress("ntrack",&ntrack);
  tree->SetBranchAddress("phi",&phi);
  tree->SetBranchAddress("pT",&pT);
  tree->SetBranchAddress("eta",&eta);

  Double_t maxpt = 0;
  Int_t maxptntrk = 0;

  for(Int_t i = 0; i<entries; i++)
  {
    tree->GetEntry(i);
    for(Int_t j = 0; j++<ntrack; j++)
    {
      if(pT[j]>maxpt)
      {
        maxpt = pT[j];
        maxptntrk = ntrack;
      }
    }
  }

  Double_t phimax = phi[maxptntrk];

  std::cout<<"max pt = "<<maxpt<<endl<<"corres ntrack = "<<maxptntrk<<endl;
  std::cout<<"corres phi = "<<phimax<<endl;

  TCanvas *c1 = new TCanvas("c1", "Delta Phi distribution", 500, 500);

  TH1D *delphi = new TH1D("delphi", "Delta Phi dist", 1000, -10, 10);

  for(Int_t i = 0; i<entries; i++)
  {
    tree->GetEntry(i);
    for(Int_t j = 0; j++<ntrack; j++)
    {
      Double_t dphi = phi[j] - phimax;
      delphi->Fill(dphi);
    }
  }

  delphi->Draw();
}
