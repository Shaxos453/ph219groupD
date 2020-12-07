
void d2N_away_6080()
{
  TFile *f = new TFile("13TeV_CR0_RHoff.root"); //opens file 13TeV_CR0_RHoff.root
  TTree *tree = (TTree*)f->Get("pytree6080"); //opens tree of multiplicity class 20-40
  Int_t entries = tree->GetEntries(); /*gets no. of entries in the tree (total
                                        occurences of ntrack)*/

  const Int_t maxTrack = 200; //sets maximum number of tracks to 40
  //since the max number of tracks in this multiplicity class 20-40 is 40

  Int_t ntrack = 0; //declares and initialises ntrack value to 0
  Double_t pT[maxTrack]; //declaring arrays of maximum ntrack value length
  Double_t eta[maxTrack];
  Double_t phi[maxTrack];

  //setting the branches for each variable we declared previously
  tree->SetBranchAddress("ntrack",&ntrack);
  tree->SetBranchAddress("phi",&phi);
  tree->SetBranchAddress("pT",&pT);
  tree->SetBranchAddress("eta",&eta);

  //initialising the variables for maximum pT and corresponding ntrack
  // and corresponding phi value for that maximum pT
  Double_t maxpt = 0;
  Double_t phimax = 0;
  Double_t N=0;
  Double_t dphi = 0; //declaring variable to store difference in phi


  //creating a canvas for the histogram of size 500px * 500px
  TCanvas *c2 = new TCanvas("c2", "Average number density for away region", 750, 400);

  Double_t minp=1;
  Double_t maxp=6;
  TH2D * d2N = new TH2D("d2N", "Avg. number density",20,minp,maxp,20,2,7);
  for(Int_t i = 0; i<entries; i++) //going through all ntrack entries
  {
    tree->GetEntry(i); //getting all values of ntrack, phi, eta and pT for that entry
    maxpt = 0;
    phimax = 0;
    N=0;
    for(Int_t j = 0; j<ntrack; j++) //going through all ntracks in that entry
    {
      if(pT[j]>maxpt) //finding max value of pT in the multiplicity class
      {
        maxpt = pT[j];
        phimax = phi[j];
      }
    }
    for(Int_t j = 0; j<ntrack; j++)
    {
        dphi = abs(phimax - phi[j]); //dphi is absolute difference between phi[j] and phimax
        if(dphi>TMath::Pi())
        {
            dphi = 2*TMath::Pi() - dphi; /*if the difference goes over 2pi then we
            bring it back to range (0 to pi)*/
        }
        if(dphi<TMath::Pi() && dphi>2*TMath::Pi()/3 && abs(eta[j])<2.5)//selecting region and making eta cut
        {
            N++;
        }  
    }
    N=N/(5*TMath::Pi()/3);//Dividing by area of region
    
    d2N->Fill(maxpt,N);
}
//d2N->Draw("LEGO");
  TProfile* final = d2N->ProfileX(); //for given x value, plots mean y value
  final->SetStats(0);
  Int_t check=0;
  for(Int_t i=1; i<21; i++)//to get rid of bins for which y=0
  {
    if(final->GetBinContent(i) == 0)
    {
      check++;
    }
    else
    {
      break;
    }
  }
  final->GetXaxis()->SetRangeUser((((maxp-minp)/20)*check)+minp, maxp);
  //final->SetMinimum(0);
  final->SetLineColor(2);
  final->SetLineWidth(3);
  final->GetXaxis()->SetLabelSize(0.035);
  final->GetYaxis()->SetLabelSize(0.035);
  final->SetTitle("Away region (60-80)");
  final->GetXaxis()->SetTitle("pT_{lead}");
  final->GetXaxis()->SetTitleSize(0.04);
  final->GetXaxis()->CenterTitle();
  final->GetYaxis()->SetTitle("Average number density");
  final->GetYaxis()->SetTitleSize(0.04);
  final->GetYaxis()->CenterTitle();
  final->Draw("HIST");
  c2->SaveAs("d2N_away_6080.pdf");
}