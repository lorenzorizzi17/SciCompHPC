


void graph(){
    int const NTHR = 10;

    int thr[NTHR]={1,2,3,4,5,6,7,8,9,10};
    TGraph* g[NTHR];
    for(int i = 0; i < NTHR; i++){
        std::string s = "time_"+std::to_string(*(thr+i))+".txt";
        g[i] = new TGraph(s.c_str(), "%lg %lg");
    }
    g[0]->SetMarkerSize(.5);
    g[0]->SetLineWidth(2);
    g[0]->SetLineColor(2);
    g[0]->Draw();
    g[0]->SetMaximum(0.12);
    g[0]->SetMinimum(0);
    for(int i = 1; i < NTHR; i++){
     g[i]->SetMarkerSize(.5);
     g[i]->SetMarkerStyle(21);
     g[i]->SetLineWidth(2);
    g[i]->SetLineColor(i+2);
        g[i]->Draw("Same"); 
    }
TLegend* leg = new TLegend(0.1,0.6,0.48,0.8);
    for(int i = 0; i< NTHR; i++){
    leg->AddEntry(g[i], (std::to_string(*(thr+i))+" threads").c_str());
    }
    leg->Draw();
}
