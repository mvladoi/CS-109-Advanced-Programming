
#include "fact.h"



vector<string> * Fact::get_param(size_t index){

    size_t factSize = fact_instance.size();
	if(index < 0 || index > factSize){
		return NULL;
	}
	return fact_instance[index];


}



//constructor
Fact::Fact(string in_name){
	name = in_name;
}





string Fact::get_name(){
	return name;

}




//we are assuming that all the fact
//instances have the same number of parameters.
//if assumption is not right, we might need a loop for all the params.

int Fact::num_of_params(){
	return get_param(0)->size();


}



size_t Fact::num_of_instance(){
return fact_instance.size();
}





void Fact::new_instance(vector<string> *params){
	fact_instance.push_back(params);
}






string Fact::toString(){
	  string s = "";

	for(size_t i = 0; i < fact_instance.size(); i++){
        s+= "FACT ";
		s += name + "(";

		for(size_t j = 0; j < fact_instance[i]->size(); j++){
			s += fact_instance[i]->at(j);
			if(j < fact_instance[i]->size() - 1){
				s += ",";
			}

		}
		s += ")\n";
	}

	return s;
}

vector<string>* Fact::operator[](size_t pos){
	vector<string> * temp = get_param(pos);
	return temp;


}


Fact::~Fact(){}


