
#include <string>
#include <map>

class Table{
	map<string,Column> column_list(){return columns;};
	vector get_tuple(int id_number);
};

class Column{
	map<int,TYPE> id_list(){return ids;}
	void add_tuple(vector);
};

/*  This method is used for basic select_from_where commands 
	Send in "All" for select if '*' was used, if "AS"*/
Table select_from_where(string new_table_name, string select,vector<string> table_names,void(*where_func)(),map<string,string> aliases = NULL ){
	Table new_table(new_table_name); 
	if(select == "All"){
		for (int i = 0; i < table_names.size(); ++i)
		{
			/* iterate through all columns */
			map<string,Column>::iterator table_iterator;
			map<string,Column>::iterator new_table_iterator = new_table.column_list.begin();
			for (table_iterator = table_names[i].column_list().begin(); table_iterator != table_names[i].end(); table_iterator++)
			{
				Column current_column = table_iterator->second();
				/* If "AS" was used to assign the column a new name then, the new name is used */
				if(aliases != NULL && aliases.count(table_iterator->first())>0){
					new_table.add_column(aliases[table_iterator->first()]);
				}
				else{
					new_table.add_column(table_iterator->first());
				}
				Column new_column = new_table_iterator->second();
				/* Apply where condition to all elements */
				map<int,TYPE>::iterator column_iterator;//Type to be changed
				for (column_iterator = current_column.id_list().begin(); column_iterator != current_column.end(); column_iterator++)
				{
					if(where_func(column_iterator->second())){
						new_column.add_tuple(table_names[i].get_tuple(column_iterator->first())) // use id of tuple to get complete tuple and send to column COLUMN METHOD ADD_TUPLE
					}
				}
				new_table_iterator++;
			}
		}
	}
	else {
		for (int i = 0; i < table_names.size(); ++i){
			Column current_column = table_names[i].column_list()[select];
		}
	}
}

