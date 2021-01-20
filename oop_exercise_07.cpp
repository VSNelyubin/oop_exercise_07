// Written by VSNelyubin, m80-206b-19, Original Code, do not steal!

#include <string>

#include <fstream>

#include <iostream>

#include <cmath>

#include <iomanip>

#include <stdio.h>

#include <stdlib.h>

#include <vector>

double dabs(double a){
	if(a<0){return -a;}
	return a;
}

template <class T>
double dist(std::pair<T,T> a,std::pair<T,T> b){
	double rez=std::pow((double)a.first-(double)b.first,2);
	rez+=std::pow((double)a.second-(double)b.second,2);
	return std::sqrt(rez);
}

template <class T>
class Figure{
	public:	std::pair<T,T>*cord;
	int verNum;
	Figure(int vern){
		verNum=vern;
		cord=new std::pair<T,T>[vern];
	}
	~Figure(){
		delete[] cord;
	}
};

template <class T>
bool checkEven(Figure<T>*ta){
    if(ta->verNum<3){return true;}
    double rez=dist(ta->cord[0],ta->cord[ta->verNum-1]);
    for(int arei=1;arei<ta->verNum;arei++){
        if(rez!=dist(ta->cord[arei],ta->cord[arei-1])){return false;}
    }
	rez=dist(ta->cord[0],ta->cord[ta->verNum-2]);
	if(rez!=dist(ta->cord[1],ta->cord[ta->verNum-1])){return false;}
    for(int arei=2;arei<ta->verNum;arei++){
        if(rez!=dist(ta->cord[arei],ta->cord[arei-2])){return false;}
    }

    return true;
}


template <class T>
double figArea(Figure<T>*ta){
	if(ta->verNum<3){return 0;}
	double rez,res=0;
	for(int arei=2;arei<ta->verNum;arei++){
		rez=ta->cord[0].first*(ta->cord[arei-1].second-ta->cord[arei].second);
		rez+=ta->cord[arei-1].first*(ta->cord[arei].second-ta->cord[0].second);
		rez+=ta->cord[arei].first*(ta->cord[0].second-ta->cord[arei-1].second);
		res+=dabs(rez/2);
	}
	return res;
}

template <class T>
std::pair<double,double> finCenter(Figure<T>*t){
	std::pair<double,double>rez;
	rez.first=0;rez.second=0;
	for(int arei=0;arei<t->verNum;arei++){
		rez.first+=(double)t->cord[arei].first;
		rez.second+=(double)t->cord[arei].second;
	}
	rez.first=rez.first/(double)t->verNum;
	rez.second=rez.second/(double)t->verNum;
	return rez;
}

template <class T>
std::ostream& operator << (std::ostream & out, Figure<T> &c) {
        for(int arei=0;arei<c.verNum;arei++){
                out<<c.cord[arei].first<<" : "<<c.cord[arei].second<<"\n";
        }
        return out;
}

template <class T>
std::istream& operator >> (std::istream & out, Figure<T> &c) {
        for(int arei=0;arei<c.verNum;arei++){
                out>>c.cord[arei].first>>c.cord[arei].second;
        }
		if(!checkEven(&c)){std::cout<<"figure sides are not even\n";}
        return out;
}

template <class T>
void prent(Figure<T> *c) {
        std::cout<<*c;
}

template <class T>
class pent : public Figure<T> { //XD public figure
        public:
        	pent():Figure<T>(5){
        }
};
template <class T>
class hex : public Figure<T> { //XD public figure
        public:
        	hex():Figure<T>(6){
        }
};
template <class T>
class oct : public Figure<T> { //XD public figure
        public:
        	oct():Figure<T>(8){
        }
};

int round2(double a){
	double r=a;
	r=r+0.5-(r<0);
	return (int)r;
}

class screen{
public:
	int*pxl;
	int ss;
	screen(int s){
		ss=s;
		pxl=new int[s*s];
	}
	void clear(){
		for(int i=0;i<ss*ss;i++){
			pxl[i]=0;
		}
	}
	void draw(){
		std::cout<<"\n";
		std::cout<<" ";
		for(int i=0;i<ss;i++){
			std::cout<<"--";
//			if(i<10){std::cout<<" ";}
//			std::cout<<i;
		}
		std::cout<<" \n";
		for(int i=0;i<ss;i++){
			std::cout<<"|";
			for(int j=0;j<ss;j++){
				if(pxl[j+i*ss]==0){std::cout<<"  ";}
				if(pxl[j+i*ss]==1){std::cout<<"░░";}
				if(pxl[j+i*ss]==2){std::cout<<"▒▒";}
                                if(pxl[j+i*ss]==3){std::cout<<"▓▓";}
				if(pxl[j+i*ss]>=4){std::cout<<"██";}
			}
			std::cout<<"|"<<"\n";
		}
		std::cout<<" ";
                for(int i=0;i<ss;i++){std::cout<<"--";}
                std::cout<<" \n";
	}
	template <class T>
	void addline(std::pair<T,T>a,std::pair<T,T>b){
		int scl=5;
		int dx,dy,h,mi,ma;
		int af,as,bf,bs;
		af=round2((double)a.first*(double)ss/scl/2+ss/2);
		as=round2((double)a.second*(double)ss/scl/2+ss/2);
		bf=round2((double)b.first*(double)ss/scl/2+ss/2);
		bs=round2((double)b.second*(double)ss/scl/2+ss/2);
		double h2;
		dx=af-bf;if(dx<0){dx*=-1;}
		dy=as-bs;if(dy<0){dy*=-1;}
		if(dx>dy){
			mi=1;if(bf<af){mi=-1;}
			for(int j=af;j!=bf;j+=mi){
				if((j>=0)&&(j<ss)){
					h2=(bs-as)/(double)(bf-af)*(j-af);
					h=round(as+h2);
					if((h>=0)&&(h<ss)){
						pxl[j+h*ss]++;
					}
				}
			}
		}
		else{
			mi=1;if(bs<as){mi=-1;}
                        for(int j=as;j!=bs;j+=mi){
                                if((j>=0)&&(j<ss)){
                                        h2=(bf-af)/(double)(bs-as)*(j-as);
                                        h=round(af+h2);
                                        if((h>=0)&&(h<ss)){
                                                pxl[h+j*ss]++;
                                        }
                                }
                        }
		}
	}
};

template <class T>
void figtosurf(Figure<T>*ta,screen*sf){
    if(ta->verNum<2){return;}
    sf->addline(ta->cord[0],ta->cord[ta->verNum-1]);
    for(int arei=1;arei<ta->verNum;arei++){
        sf->addline(ta->cord[arei],ta->cord[arei-1]);
    }
}

template <class T>
void saev(Figure<T>*ta,std::ofstream &outf){
	if(ta->verNum==5){outf<<'p';}
	if(ta->verNum==6){outf<<'h';}
	if(ta->verNum==8){outf<<'o';}
	for(int i=0;i<ta->verNum;i++){
		outf<<' '<<ta->cord[i].first<<' '<<ta->cord[i].second;
	}
	outf<<'\n';
}

int main(){
	screen *sc=new screen(50);
	//sc->draw();
	std::vector<Figure<int>*> arr;
	pent<int>*a;
	hex<int>*b;
	oct<int>*c;
	int l,i=0;
	char fgt;
	std::ofstream saveto;
	std::ifstream loadfrom;
	FILE*strem;
	std::string fname;
	while(std::cin>>fgt){
//std::cin>>fgt;
		if(fgt=='p'){
			a=new pent<int>;
			std::cin>>*a;
			arr.push_back(a);
			l=1;
			i++;
		}
		else if(fgt=='h'){
			b=new hex<int>;
			std::cin>>*b;
			arr.push_back(b);
			l=2;
			i++;
		}
                else if(fgt=='o'){
                        c=new oct<int>;
                        std::cin>>*c;
                        arr.push_back(c);
			l=3;
			i++;
		}
		else if(fgt=='u'){
			if((l!=0)&&(l<4)){
				arr.pop_back();
				l+=3;
				i--;
			}
			else{
				if(l==4){arr.push_back(a);}
				if(l==5){arr.push_back(b);}
				if(l==6){arr.push_back(c);}
				i++;
			}
		}
		else if(fgt=='d'){
			sc->clear();
			for(int j=0;j<i;j++){
	                	figtosurf<int>(arr[j],&*sc);
		        }
		        sc->draw();
		}
		else if(fgt=='t'){
                        for(int j=0;j<i;j++){
                                std::cout<<*(arr[j])<<"\n";
                        }
                }
		else if(fgt=='s'){
			std::cin>>fname;
			saveto.open(fname);
			//strem=std::fopen(fname,"w");//.open(fname);
			for(int j=0;j<i;j++){
                                saev<int>(arr[j],saveto);
                        }
			saveto.close();
//			std::fclose(strem);
		}
		else if(fgt=='l'){
                        std::cin>>fname;
			//strem=std::fopen(name,"r");
                        loadfrom.open(fname);
                        while(loadfrom>>fgt){
                                if(fgt=='p'){
		                        a=new pent<int>;
		                        loadfrom>>*a;
		                        arr.push_back(a);
		                        i++;
		                }
		                else if(fgt=='h'){
		                        b=new hex<int>;
		                        loadfrom>>*b;
//					strem>>*b;
		                        arr.push_back(b);
		                        i++;
		                }
		                else if(fgt=='o'){
		                        c=new oct<int>;
					loadfrom>>*c;
//		                        strem>>*c;
	        	                arr.push_back(c);
	                	        i++;
	                	}
                        }
			loadfrom.close();
//                        std::fclose(strem);
			l=0;
                }
		else{
			i--;
			std::cout<<"please specify what you are doing: p - add pentagon, h - add hexagon, o - add octagon.\n";
			std::cout<<"u - undo last action (using twice in a row will cause a REDO)\n";
			std::cout<<"d - draw the screen. t - print data. s - save to file, l - load file\n";
		}
	}
	return 0;
}
