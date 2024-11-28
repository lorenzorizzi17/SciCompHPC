 
 void graph(){
     int const NTHR = 10;
 
     int thr[NTHR]={1,2,3,4,5,6,7,8,9,10};
     TGraph* g[3];
     g[0] = new TGraph("linked.txt", "%lg %lg");
      g[1] = new TGraph("linked_opt1.txt", "%lg %lg");
 g[2] = new TGraph("linked_opt2.txt", "%lg %lg");

     g[0]->SetMarkerSize(.5);
     g[0]->SetLineWidth(2);
     g[0]->SetLineColor(2);
     g[0]->Draw();
     g[0]->SetMaximum(16);
     g[0]->SetMinimum(0);
     for(int i = 1; i < 3; i++){
      g[i]->SetMarkerSize(.5);
      g[i]->SetMarkerStyle(21);
      g[i]->SetLineWidth(2);
     g[i]->SetLineColor(i+2);
         g[i]->Draw("Same");
     }
 TLegend* leg = new TLegend(0.1,0.6,0.48,0.8);
     leg->AddEntry(g[0], "linked");
     leg->AddEntry(g[1], "linked_opt1");
     leg->AddEntry(g[2], "linked_opt2");
     leg->Draw();
 }


