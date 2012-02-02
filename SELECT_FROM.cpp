
#include <string>
#include <map>

using namespace std;

typedef vector<void*> tuple;

/*
// return vector of ids of tuples that satisfy condition od IN, check for if empty to create bool value
vector<int> in_operator(string tuple, Table relation);

//checks if table exists
bool exists_operator (Table relation)

//merge lists, can check for if empty to create bool value
vector<int> and_operator(vector<int> first_list,vector<int> second_list)

//intersect lists, can check for if empty to create bool value
vector<int> or_operator(vector<int> first_list, vector<int> second_list)

//return vector of ids of tuples that satisfy condition of NOT, check for empty to create bool value
vector<int> not_operator()

//return vector of ids of tuples that satisfy condition of ALL, check for empty to create bool value
vector<int> all_operator(string tuple, Table relation, void(*operation_func)()) 

//return vector of ids of tuples that satisfy condition of ANY, check for empty to create bool value
vector<int> any_operator(string tuple, Table relation, void(*operation_func)())
*/
class Type_wrapper{
	public:
		Type_wrapper(void* )
};


template <class T>
class Column{

	//typedef T type;
	map<int,T> ids;
	map<int,T> id_list(){return ids;}
	T column_type(){return T;}//**NOT DONE ** Type not right
	void add_entry(int id, T value){ids[id] = value;}

};

class Table{

	map<string,Column<TYPE_OF_COLUMN>> column_list(){return columns;} // ** NOT DONE ** TYPE PROBLEM
	/* create a tuple by wrapping each element in a Type_wrapper which will allow all types to be supported */
	tuple get_tuple(int id_number){
		tuple result;
		for (int i = 0; i < columns.size(); ++i){
			result.push_back((void*) new Type_wrapper(columns[i].id_list()[id_number]));
		}
		return result;
	};
	void add_tuple(tuple new_tuple){
		for (int i = 0; i < new_tuple.size(); ++i){
			
		}
	}; //** NOT DONE ** NEED TO FIGURE OUT THIS TYPE STUFF
};

/*  This method is used for basic select_from_where commands 
	Send in a vector containing "All" for select if '*' was used, if "AS"*/
Table select_from_where(string new_table_name, vector<string> select,vector<string> table_names,void(*where_func)(),map<string,string> aliases = NULL ){
	Table new_table(new_table_name); 
	vector<int> ids_to_copy;
	if(select[0] == "All"){
		for (int i = 0; i < table_names.size(); ++i){
			/* iterate through all columns */
			map<string,Column>::iterator table_iterator;
			map<string,Column>::iterator new_table_iterator = new_table.column_list.begin();
			/* Add all columns to new table that will be needed */
			for (table_iterator = database.table_list()[table_names[i]].column_list().begin(); 
					table_iterator != database.table_list()[table_names[i]].column_list().end();
					table_iterator++)
			{
				Column current_column = table_iterator->second();
				/* If "AS" was used to assign the column a new name then, the new name is used */
				if(aliases != NULL && aliases.count(table_iterator->first())>0){
					new_table.add_column(aliases[table_iterator->first()]);
				}
				else{
					new_table.add_column(table_iterator->first());
				}
				new_table_iterator++;
			}
			//new_table_iterator = new_table.column_list.begin();
			/* find row ids to be copied to new table */
			for (table_iterator = database.table_list()[table_names[i]].column_list().begin(); 
					table_iterator != database.table_list()[table_names[i]].column_list().end(); 
					table_iterator++)
			{
				Column current_column = table_iterator->second();
				/* Apply where condition to all elements */
				//map<int,void*>::iterator column_iterator;//** NOT DONE ** Type to be changed
				for (column_iterator = current_column.id_list().begin(); column_iterator != current_column.id_list().end(); column_iterator++){
					//if(where_func(column_iterator->second())){
						//new_table.add_tuple(database.table_list()[table_names[i]].get_tuple(column_iterator->first())) // use id of tuple to get complete tuple and send to column COLUMN METHOD ADD_TUPLE
						//map<int,void*>::iterator new_column_iterator = ;//** NOT DONE ** Type to be changed
						ids_to_copy.push_back(column_iterator->first());

					//}
				}
				new_table_iterator++;
			}
			/* add data to new table */
			new_table_iterator = new_table.column_list.begin();
			for (table_iterator = database.table_list()[table_names[i]].column_list().begin(); 
					table_iterator != database.table_list()[table_names[i]].column_list().end(); 
					table_iterator++)
			{
				Column current_column = table_iterator->second();
				Column new_table_column = new_table_iterator->second();
				for(int i = 0; i < ids_to_copy.size(); i++){
					new_table_column.add_entry(i,curent_colomn[ids_to_copy[i]]) 
				}
				new_table_iterator++;
			}
		}
	}
	else {
		for (int i = 0; i < table_names.size(); ++i){
			/* Add all columns to new table that will be needed */
			for(int j = 0; j< select.size(); ++j){
				Column current_column = database.table_list()[table_names[i]].column_list()[select[j]];
				/* If "AS" was used to assign the column a new name then, the new name is used */
				if(aliases != NULL && aliases.count(select[j])>0){
					new_table.add_column(aliases[select[j]]);
					new_column = new_table.column_list()[aliases[select[j]]];
				}
				else{
					new_table.add_column(select[j]);
					new_column = new_table.column_list()[select[j]];
				}
			}
			for(int j = 0; j< select.size(); ++j){
				Column current_column = database.table_list()[table_names[i]].column_list()[select[j]];
				for (int k = 0; k < current_column.id_list().size(); ++k){
					if(where_func(current_column.id_list()[k])){
						new_table.add_tuple(table_names.get_tuple());
					}
				}
			}
		}
	}
}

/* This functions implements SUM which sums up all the elements in the selected columns */
template <class T> 
T select_sum(string select, string table_name){ 
	T sums; 
	/* gives the map of ids to values for the selected column */
	map<int,T> column_map =  database.table_list()[table_name].column_list()[select];
	map<int,T>::iterator column_iterator;
	/* add all values in the column together */
	for (column_iterator = column_map.begin(); column_iterator != column_map.end(); i++){
		sum += column_iterator->second();
	}
	return sum;
}

/* This function implements COUNT which counts the number of rows in which the value in the selected
	column matches the desired object, for length of whole column send "All" as compare_to_object */
template <class T>
int select_count(string select, string table_name,T compare_to_object){
	if(compare_to_object == "All"){
		return database.table_list()[table_name].column_list()[select].id_list().size();
	}
	int count;
	/* gives the map of ids to values for the selected column */
	map<int,T> column_map =  database.table_list()[table_name].column_list()[select].id_list();
	map<int,T>::iterator column_iterator;
	/* count number of rows that match */
	for (column_iterator = column_map.begin(); column_iterator != column_map.end(); i++){
		if(column_iterator->second() == compare_to_object){
			count++;
		}
	}
	return count;
}

/* This function implements MIN which find the minimum value in a column */
template <class T>
T select_min(string select, string table_name){ 
	T min; 
	/* gives the map of ids to values for the selected column */
	map<int,T> column_map =  database.table_list()[table_name].column_list()[select].id_list();
	map<int,T>::iterator column_iterator;
	/* find min value*/
	for (column_iterator = column_map.begin(); column_iterator != column_map.end(); i++){
		if(column_iterator->second() < min){
			min = column_iterator->second();
		}
	}
	return min;
}

/* This function implements MAX which find the maximum value in a column */
template <class T> 
T select_MAX(string select, string table_name){
	T max;
	/* gives the map of ids to values for the selected column */
	map<int,T> column_map =  database.table_list()[table_name].column_list()[select].id_list();
	map<int,T>::iterator column_iterator;
	/* find max value*/
	for (column_iterator = column_map.begin(); column_iterator != column_map.end(); i++){
		if(column_iterator->second() > max){
			max = column_iterator->second();
		}
	}
	return max;
}