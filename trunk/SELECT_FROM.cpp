
#include <string>
#include <map>

class Table{
	
};

class Column{
	
};

/* Send in "ALL" for select if '*' was used, if "AS"*/
Table select_from_where(string select,vector<string> table_names,void(*where_func)(),map<string,string> aliases = NULL ){
	Table new_table(""); //NOT DONE FIGURE OUT NEW TABLE NAME
	if(select == "ALL"){
		for (int i = 0; i < table_names.size(); ++i)
		{
			/* iterate through all columns */
			map<string,Column>::iterator table_iterator;
			map<string,Column>::iterator new_table_iterator = new_table.begin();
			for (table_iterator = table_names[i].begin(); table_iterator != table_names[i].end(); table_iterator++)
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
				map<int,TYPE>::iterator column_iterator;
				for (column_iterator = current_column.begin(); column_iterator != current_column.end(); column_iterator++)
				{
					if(where_func(column_iterator->second())){
						new_column.add_tuple(column_iterator->first()) // send id of tuple to new tables column to be added COLUMN METHOD ADD_TUPLE
					}
				}
				new_table_iterator++;
			}

		}
	}
	else {
		
	}
}

