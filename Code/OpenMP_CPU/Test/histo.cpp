#include<string>

void histo(int thr) {
	TH1F* histo = new TH1F("name", "name", 1000,0,0.05);
	
	std::ifstream file;
	file.open("data_THR"+std::to_string(thr)+".txt");
	while(file.good()){
		double x= 0;
		file >> x;
		histo->Fill(x);
	}

	histo->Draw();

}
